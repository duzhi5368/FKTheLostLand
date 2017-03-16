/**
*	created:		2013-5-10   3:05
*	filename: 		FKCClientSocket
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/Network/FKCClientSocket.h"
#include "../../Include/FKITrace.h"
#include "../../Include/IFKFileSystem.h"
#include "../../Include/ResMgr/ResMgrCommon.h"
//------------------------------------------------------------------------
#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif
//------------------------------------------------------------------------
// 低于0x100的为有效消息，用于与WSAGetLastError()返回消息区别
#define MSG_ERROR_MSG			0x100	// 在CNetLink::m_szLastInfo含有最近的错误信息
#define TIMER_CHECK_SEND_QUEUE	100		// 定时检查是否再次发送数据包，
//------------------------------------------------------------------------
/*										
	暂不必实现

	TIMER_CHECK_SEND_QUEUE打算解决这个问题：
		FD_WRITE到达和发送队列是否为空这两个信号可能不统一，导致发送队列中有包，
		FD_WRITE事件来过一次，再也不来了，而发送队列不停地增加。这在理论上不可能
		另外一个作用是通讯层定时处理一些事件
	
*/
//------------------------------------------------------------------------
int CClientSocket::m_nWSAStartupRefCount = 0;
//------------------------------------------------------------------------
CClientSocket::CClientSocket()
{
	m_ConnectState = stateClosed;

	m_dwCommEventID = INVALID_EVENT_ID;
	m_dwTimerEventID = INVALID_EVENT_ID;
	m_dwConnectEventID = INVALID_EVENT_ID;
	m_hRefCommEvent = NULL;

	m_SocketClient = INVALID_SOCKET;
	m_szServerAddress[0] = 0;
	m_wServerPort = -1;

	m_dwSocketID = INVALID_SOCKET_ID;
	m_pThreadRoute = NULL;
	m_pSink = NULL;
	m_pTrace = NULL;

	m_nMaxSendQueueCount = 10000;

	m_hOverlapedEvent = (WSAEVENT)CreateEvent(NULL,FALSE,FALSE,NULL);
}
//------------------------------------------------------------------------
CClientSocket::~CClientSocket()
{
	if(m_hOverlapedEvent)
		CloseHandle(m_hOverlapedEvent);
}
//------------------------------------------------------------------------
extern "C" BOOL CreateClientSocket(DWORD dwSocketID,IClientSocketSink *pSink,IThreadRoute *pThreadRoute, ITrace* pTrace,BOOL bInSameThread,/*out*/IClientSocket** ppClientSocket)
{
	if(ppClientSocket == NULL)
		return FALSE;
	CClientSocket *pSocket = new CClientSocket();
	if(pSocket == NULL)
		return FALSE;
	if(!pSocket->Create(dwSocketID,pSink,pThreadRoute,pTrace,bInSameThread))
	{
		DebugMsgLn(L"Error : CLinkProxyWnd::AddSocket() : Can not create CClientSocket");
		delete pSocket;
		return FALSE;
	}
	*ppClientSocket = static_cast<IClientSocket*>(pSocket);
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CClientSocket::StartupSocket()
{
	m_nWSAStartupRefCount++;
	if(m_nWSAStartupRefCount > 1)
		return TRUE;
	WSADATA WSAData;
	int  retv = WSAStartup(0x0202,&WSAData);
	if(retv == SOCKET_ERROR)
	{
		TraceLn("初始化 Winsock2 失败!");
		m_nWSAStartupRefCount--;
		return FALSE;
	}
	if( (WSAData.wHighVersion & 0xFF00) != 0x0200)
	{
		TraceLn("Windows Socket 版本太低!");
		m_nWSAStartupRefCount--;
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
void DumpData(LPCSTR szDataName,LPCSTR buf, int nLen)
{
	if(buf == NULL)
		return;
	wchar_t str[4096] = L"",temp[1024] = L"";
	for(int i = 0; i < nLen; i++)
	{
		wsprintf(temp,L"%02X ", (BYTE)buf[i]);
		wcscat(str,temp);
	}
	DebugMsgLn(str);
}
//------------------------------------------------------------------------
// 关闭此连接，下次可以再次调用OpenLink()发起连接
BOOL CClientSocket::CloseConnect()
{
	ClearSocketData(); 
	return TRUE;
}
//------------------------------------------------------------------------
// bInSameThread用于优化，当已经知道是同一线程互调时，不必使用同步锁
BOOL CClientSocket::Create(DWORD dwSocketID,IClientSocketSink *pSink,IThreadRoute *pThreadRoute, ITrace* pTrace,BOOL bInSameThread)
{
	Assert(pSink != NULL);
	Assert(pThreadRoute != NULL);

	if(!StartupSocket())
		return FALSE;

	m_dwSocketID = dwSocketID;  
	m_pThreadRoute = pThreadRoute;
	m_pSink = pSink;

	m_LockClientSocketContext.SetNoneLock(bInSameThread);

	Assert(m_pThreadRoute->AddEvent(static_cast<IEventSink*>(this),m_dwCommEventID));
	m_hRefCommEvent = m_pThreadRoute->GetEventHandle(m_dwCommEventID);
	Assert(m_hRefCommEvent != NULL);
	return TRUE;
}
//------------------------------------------------------------------------
// 清除Create创建的资源
void CClientSocket::Close()
{
	ClearSocketData();
	if(m_pThreadRoute && m_dwCommEventID != INVALID_EVENT_ID)
	{
		m_pThreadRoute->RemoveEvent(m_dwCommEventID);
		m_dwCommEventID = INVALID_EVENT_ID;
		m_pThreadRoute = NULL;
	}
	m_nWSAStartupRefCount--;
}
//------------------------------------------------------------------------
// 功能：连接服务器，与CloseConnect配对
// 发起连接，连接结果：当收到OnConnectOK()时，表示连接成功，收到OnConnectError()时表示连接失败
// 返回：用户可忽略返回结果
BOOL CClientSocket::Connect(LPCSTR szServerAddress, WORD wServerPort,NET_PROXY_OPTION* pProxyOption)
{
	ClearSocketData();
	Assert(szServerAddress != NULL);
	lstrcpynA(m_szServerAddress,szServerAddress,MAX_PATH);
	m_wServerPort = wServerPort;
	if(pProxyOption)
		memcpy(&m_ProxyOption,pProxyOption,sizeof(NET_PROXY_OPTION));

	// 因为域名解析和连接速度很慢，所以将连接过程改在通讯线程中执行
	m_ConnectState = stateReqConnect;
	SetEvent(m_hRefCommEvent);
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CClientSocket::GetIP(char *szName, in_addr *pAddr)
{
	Assert(szName != NULL);
	Assert(pAddr != NULL);
	int nPointCount = 0;int len = strlen(szName);
	int i = 0;
	for( ; i < len; i++)
	{
		if(szName[i] == '.')
			nPointCount++;
		else if(!isdigit(szName[i]))
			break;
	}
	if(nPointCount < 3 || i < len)	// not IP Address
	{
		struct hostent *hp = NULL;
		hp = gethostbyname(szName);
		if (hp == NULL ) 
		{
			char szMsg[1024];
			wsprintfA(szMsg,"解析服务器名:%s出错",szName);
			ShowConnectError(szMsg,0);
			return FALSE;
		}
		memcpy(pAddr,hp->h_addr,hp->h_length);
	}
	else
	{
		int ip[128];BYTE *p = (BYTE*)pAddr;
		sscanf(szName,"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);
		for( i = 0; i < 4; i++)
			p[i] = (BYTE)ip[i];
	}
	return TRUE;
}
//------------------------------------------------------------------------
// 连接时发生错误
void CClientSocket::ShowConnectError(char *szErrorMsg, int nErrorCode)
{
	if(m_pSink)
		m_pSink->OnConnectError(m_dwSocketID,szErrorMsg,nErrorCode);

	ClearSocketData();
}
//------------------------------------------------------------------------
//　连接成功以后发生错误
void CClientSocket::ShowSocketError(char *szErrorMsg, int nErrorCode)
{
	if(!IsClosed())
	{ // 如果当前连接实际上已经断开，错误消息不必再传递出去
		if(m_pSink)
			m_pSink->OnConnectClose(m_dwSocketID,szErrorMsg,nErrorCode);
		// 因为连接断开时可能数据还有效，给应用层一个收数据的机会，所以暂不清除数据
	}
}
//------------------------------------------------------------------------
void CClientSocket::OnEvent(DWORD dwEventID)
{
	if(dwEventID != m_dwCommEventID)
		return;

	if(m_ConnectState == stateReqConnect)
	{ // 正在请求连接
		m_ConnectState = stateConnecting;
		DoConnect(m_szServerAddress,m_wServerPort,&m_ProxyOption);
		return;
	}

	WSANETWORKEVENTS	events;
	int retv = WSAEnumNetworkEvents(m_SocketClient , m_hRefCommEvent,&events);
	if(retv == SOCKET_ERROR)
	{
		ShowSocketError("EnumNetworkEvent failed",WSAGetLastError());
		return;
	}
	if(events.lNetworkEvents == 0)
		return;
	long lEvents = events.lNetworkEvents;
	if(lEvents & FD_CONNECT)
	{
		int nErrorCode = events.iErrorCode[FD_CONNECT_BIT];
		if(nErrorCode == 0)
		{
			m_ConnectState = stateConnected;
			m_pSink->OnConnectOK(m_dwSocketID);
		}
		else
		{
			ShowConnectError("服务器地址不正确或服务器不在运行，请稍候再试",nErrorCode);
			return;
		}
	}
	if(!IsConnected())
	{
#ifdef _DEBUG
		wchar_t buf[1024];
		wsprintf(buf,L"Warn : CClientSocket::OnEvent() : socket[%d] is not connected now\n",m_dwSocketID);
		OutputDebugString(buf);
#endif
		return;
	}
	if(lEvents & FD_READ)
	{
		int nErrorCode = events.iErrorCode[FD_READ_BIT];
		if(nErrorCode != 0)
			ShowConnectError("接收数据出错",nErrorCode);
		else
			m_pSink->OnDataArrived(m_dwSocketID);
	}
	if(lEvents & FD_WRITE)
	{
		int nErrorCode = events.iErrorCode[FD_WRITE_BIT];
		if(nErrorCode != 0)
			ShowConnectError("发送数据出错",nErrorCode);
		else
			OnFD_WRITE();

	}
	if(lEvents & FD_CLOSE)
	{
		ShowSocketError("与服务器失去联系",0);
	}
}
//------------------------------------------------------------------------
BOOL CClientSocket::Recv(int nBufLen,/*out*/char* buf,/*out*/int& nLen)
{
	int retv = recv(m_SocketClient,buf,nBufLen,0);
	if(retv == 0)
	{
		ShowSocketError("接收数据时对方关闭连接",0);
		return FALSE;
	}
	else if(retv == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK)	// 当前接收不到数据
		{
			nLen = 0;							// 没有接收到数据
			return TRUE;
		}
		ShowSocketError("接收数据出错",WSAGetLastError());
		return FALSE;
	}
	nLen = retv;
	return TRUE;
}
//------------------------------------------------------------------------
DWORD CClientSocket::OnTimer(DWORD dwTimerID,DWORD dwParam)
{
	OnFD_WRITE();
	return  0;
}
//------------------------------------------------------------------------
// 先立即发送，数据发不通时才将数据放入发送队列等待下次发送
int CClientSocket::Send(LPCSTR buf,int nLen)
{
	m_LockClientSocketContext.Lock();
	if(!IsConnected())
	{
		m_LockClientSocketContext.Unlock();
		return FALSE;
	}
	Assert(buf != NULL);
	Assert(nLen > 0 && nLen <= MAX_SOCKET_RAW_DATA_LEN);

	// 如果队列不为空，则不能立即发送，而是放队列中等待FD_WRITE事件到达时才能发送
	if(m_SendQueue.size() > m_nMaxSendQueueCount)	// 如果此连接累积包太多，关闭此连接
	{
		m_LockClientSocketContext.Unlock();
		ShowSocketError("数据包累积过多，关闭当前连接",0);
		return FALSE;
	}
	WSABUF wsabuf;
	wsabuf.len = nLen;

	if(m_SendQueue.empty())
	{
		wsabuf.buf = (char*)buf;
		DWORD dwByteSent = 0;
		DWORD dwReturn =  DoSend(wsabuf,dwByteSent);
		if(dwReturn == 0)
		{
			m_LockClientSocketContext.Unlock();
			return TRUE;
		}
		else if(dwReturn == WSA_IO_INCOMPLETE)
		{
			nLen = nLen - dwByteSent;
			if(nLen <= 0)
			{
				m_LockClientSocketContext.Unlock();
				return TRUE;
			}
			wsabuf.buf = MyAllocMemory(nLen);
			if(wsabuf.buf == NULL)
			{
				m_LockClientSocketContext.Unlock();
				ShowSocketError("发送数据时内存不足",0);
				return FALSE;
			}
			wsabuf.len = nLen;
			memcpy(wsabuf.buf,buf + dwByteSent,nLen);
			m_SendQueue.push_back(wsabuf);
			m_LockClientSocketContext.Unlock();
			return WSA_IO_INCOMPLETE;
		}
		if(dwReturn == SOCKET_ERROR)
		{
			m_LockClientSocketContext.Unlock();
			ShowSocketError("发送数据失败",WSAGetLastError());
			return FALSE;
		}
	}
	else
	{
		wsabuf.buf = MyAllocMemory(nLen);
		if(wsabuf.buf == NULL)
		{
			m_LockClientSocketContext.Unlock();
			ShowSocketError("发送数据时内存不足",0);
			return FALSE;
		}
		memcpy(wsabuf.buf,buf,nLen);
		m_SendQueue.push_back(wsabuf);
		m_LockClientSocketContext.Unlock();
		return WSA_IO_INCOMPLETE;
	}
	return FALSE;
}
//------------------------------------------------------------------------
// 返回:
//		WSA_IO_INCOMPLETE	: 当前不能再发送，需要数据缓冲到队列
//		SOCKET_ERROR		: 发送失败
//		0					: 发送成功
int CClientSocket::DoSend(WSABUF& wsabuf,DWORD& dwByteSent)
{
	//WSAOVERLAPPED	Overlapped;
	//Overlapped.hEvent = NULL;//(WSAEVENT)m_hOverlapedEvent;
	//int retv = WSASend(m_SocketClient,&wsabuf,1,&dwByteSent,0,&Overlapped,NULL);
	//int retv = WSASend(m_SocketClient,&wsabuf,1,&dwByteSent,0,NULL,SendCompletionROUTINE);
	//int retv = WSASend(m_SocketClient,&wsabuf,1,&dwByteSent,0,NULL,NULL);
	//............

	int retv = send(m_SocketClient,wsabuf.buf,wsabuf.len,0);
	if(retv == SOCKET_ERROR)
	{
		int nErrorCode = WSAGetLastError();
		if(nErrorCode == WSA_IO_PENDING)// 已经递交到socket层的缓冲中，但未立即发送出去
			return 0;
		else if(nErrorCode == WSAEWOULDBLOCK)
		{
#ifdef _DEBUG
			OutputDebugString(L"Warn : CClientSocket::DoSend() : WSAEWOULDBLOCK\r\n");
#endif
			return WSA_IO_INCOMPLETE;	// 本次不能发送出去，等待FD_WRITE事件到达再发送
		}
		else
		{
#if defined(_DEBUG)
			OutputDebugString(L"发送数据失败\r\n");
#endif
			return SOCKET_ERROR;
		}
	}
	else 
		dwByteSent = (DWORD)retv;
	return 0;
}
//------------------------------------------------------------------------
// 有数据发送，队列中有数据否？检测发送缓冲区是否有数据发送
// 收到FD_WRITE事件，检查是否有数据需要发送
void CClientSocket::OnFD_WRITE()
{
	if(!IsConnected())
		return;
	m_LockClientSocketContext.Lock();
	while(!m_SendQueue.empty())
	{
		WSABUF& wsabuf = m_SendQueue.front();
		DWORD dwByteSent = 0;
		DWORD dwReturn = DoSend(wsabuf,dwByteSent);
		if(dwReturn == 0)
		{ // 发送成功
			if(dwByteSent < wsabuf.len)
			{ // 没有发送完成，此结点不删除
				if(dwByteSent > 0)
				{
					memmove(wsabuf.buf,wsabuf.buf + dwByteSent,wsabuf.len - dwByteSent);
					wsabuf.len -= dwByteSent;
				}
				break; // 此次没有全部发送完，不再发送
			}
			else
			{
				delete wsabuf.buf;
				m_SendQueue.pop_front();
			}
		}
		else if(dwReturn == WSA_IO_INCOMPLETE) // socket返回WSAEWOULDBLOCK，不能再发等待下次机会
			break;
		else if(dwReturn == SOCKET_ERROR)
		{// 发送失败
			m_LockClientSocketContext.Unlock();
			ShowSocketError("发送数据失败",WSAGetLastError());
			return;
		}
	}
	m_LockClientSocketContext.Unlock();
}
//------------------------------------------------------------------------
void CClientSocket::ClearSocketData()
{
	m_LockClientSocketContext.Lock();
	m_ConnectState = stateClosed;
	if(m_SocketClient != INVALID_SOCKET)
	{
		closesocket(m_SocketClient);
		m_SocketClient = INVALID_SOCKET;
	}
	while(m_SendQueue.size () != 0)
	{
		WSABUF& wsabuf = m_SendQueue.front();
		if(wsabuf.buf)
			delete wsabuf.buf;
		m_SendQueue.pop_front();
	}
	m_LockClientSocketContext.Unlock();	
}
//------------------------------------------------------------------------
BOOL CClientSocket::DoConnect(LPCSTR szServerAddress, WORD wServerPort, NET_PROXY_OPTION *pProxyOption)
{
	struct sockaddr_in ServerAddress;
	memset(&ServerAddress,0,sizeof(ServerAddress));
	if(!GetIP(m_szServerAddress,&ServerAddress.sin_addr))
		return FALSE;
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(m_wServerPort);

	struct sockaddr_in ProxyServerAddress;
	memset(&ProxyServerAddress,0,sizeof(ProxyServerAddress));
	int retv = 0;

	try
	{
		m_SocketClient = WSASocket(AF_INET ,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
		if(m_SocketClient == INVALID_SOCKET)
			throw "WSASocket() error";
		
		BOOL bAlive = TRUE;
		if(setsockopt(m_SocketClient,SOL_SOCKET,SO_KEEPALIVE,(char*)&bAlive,sizeof(BOOL)))
		{
			closesocket(m_SocketClient);
			TraceLn("CListenThread::Start error,setsockopt failed");
			return FALSE;
		}
		
		int nBufSize=65535;//不用系统缓存区
		if(setsockopt(m_SocketClient,SOL_SOCKET,SO_SNDBUF,(char*)&nBufSize,sizeof(int)))
		{
			closesocket(m_SocketClient);
			TraceLn("CListenThread::Start error,setsockopt failed");
			return FALSE;
		}

		if(!m_ProxyOption.bEnableProxy)
		{
			retv = WSAConnect(m_SocketClient , (struct sockaddr*)&ServerAddress,sizeof(ServerAddress),NULL,NULL,NULL,NULL);
			TraceLn("!!!WSAConnect!!! CClientSocket::DoConnect  1  IP = %s port = %d", szServerAddress, wServerPort);
			if(retv == SOCKET_ERROR)
			{
				if(WSAGetLastError() != WSAEWOULDBLOCK)
				{
					ShowConnectError("无法连接服务器",WSAGetLastError());
					return FALSE;
				}
			}
			int retv = WSAEventSelect(m_SocketClient,m_hRefCommEvent,FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
			if(retv != 0)
				throw "WSAEventSelect() error";
			return TRUE;
		}
		
	}
	catch(char* szMsg)
	{
		ShowConnectError(szMsg,0);
		return FALSE;
	}

	// 代理服务器模式
	if(!GetIP(m_ProxyOption.szProxyServerName,&ProxyServerAddress.sin_addr))
		return FALSE;

	ProxyServerAddress.sin_family = AF_INET;
	ProxyServerAddress.sin_port = htons(m_ProxyOption.wProxyPort);

	WSASetLastError(0);
	DWORD arg = 0;
	retv = ioctlsocket(m_SocketClient,FIONBIO,&arg);		// 有代理服务器时设为Blocking方式
	if(retv != 0)
	{
		ShowConnectError("ioctlsocket() error",WSAGetLastError());
		return FALSE;
	}
	retv = WSAConnect(m_SocketClient , (struct sockaddr*)&ProxyServerAddress,sizeof(ProxyServerAddress),NULL,NULL,NULL,NULL);
	TraceLn("!!!WSAConnect!!! CClientSocket::DoConnect  2  IP = %s port = %d", szServerAddress, wServerPort);
	if(retv == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSAEWOULDBLOCK)
		{
			ShowConnectError("与代理服务器连接出错",0);
			return FALSE;
		}
	}

	WSASetLastError(0);	// 清空当前SOCKET的出错信息

	// 以下为在socks4和socks5选项时，与代理服务器间的通讯
	char buf[4096];
	int nOff = 0;
	if(m_ProxyOption.socksType == proxy5)
	{ // 1、请求代理服务器服务方式，包括：无密码方式和需密码方式
		//DebugMsgLn("Connect '%s' via proxy server '%s' by sock5",m_szServerAlias,m_szProxyServer);
		buf[nOff++] = 5;	// ver
		buf[nOff++] = 1;	// method count
		buf[nOff++] = m_ProxyOption.szProxyUserName[0] == 0 ? 0 : 2;	// method
		DumpData("Reqest methods : ",buf,nOff);
		if(send(m_SocketClient,buf,nOff,0) != nOff)
		{
			ShowConnectError("请求代理服务器失败",0);
			return FALSE;
		}
		if(recv(m_SocketClient,buf,2,0) != 2)
		{
			ShowConnectError("接收代理服务器应答失败",0);
			return FALSE;
		}
		DumpData("Server reply Reqest methods : ",buf,2);
		if(buf[0] != 5)
		{
			ShowConnectError("接收代理服务器应答失败,Error 1",MSG_ERROR_MSG);
			return FALSE;
		}
		if(buf[1] != 0 && buf[1] != 2)
		{
			ShowConnectError("代理服务器拒绝请求",MSG_ERROR_MSG);
			return FALSE;
		}
		int nOff = 0;
		if(buf[1] == 2)
		{
			// 2、身份验证请求
		   /*+----+------+----------+------+----------+
		   |VER | ULEN |  UNAME   | PLEN |  PASSWD  |
		   +----+------+----------+------+----------+
		   | 1  |  1   | 1 to 255 |  1   | 1 to 255 |
		   +----+------+----------+------+----------+*/
			// version of the subnegotiation = 1
			buf[nOff++] = 1; 
			int nStrLen = strlen(m_ProxyOption.szProxyUserName);
			buf[nOff++] = (char)nStrLen;
			memcpy(buf + nOff,m_ProxyOption.szProxyUserName,nStrLen);
			nOff += nStrLen;

			nStrLen = strlen(m_ProxyOption.szProxyPassword);
			buf[nOff++] = (char)nStrLen;
			memcpy(buf + nOff,m_ProxyOption.szProxyPassword,nStrLen);
			nOff += nStrLen;

			DebugMsgLn(L"Request authority : User(%s) and Password(%s)",m_ProxyOption.szProxyUserName,m_ProxyOption.szProxyPassword);

			if(send(m_SocketClient,buf,nOff,0) != nOff)
			{
				ShowConnectError("向代理服务器发送身份验证失败",0);
				return FALSE;
			}

			if(recv(m_SocketClient,buf,2,0) != 2)
			{
				ShowConnectError("接收代理服务器身份验证应答失败",MSG_ERROR_MSG);
				return FALSE;
			}
			DumpData("Server reply Reqest authority : ",buf,2);
			
			// 3、proxy 应答身份验证请求
			/*+----+--------+
			|VER | STATUS |
			+----+--------+
			| 1  |   1    |
			+----+--------+*/
			// version of the subnegotiation = 1
			if(buf[0] != 1)
			{
				ShowConnectError("您的通往代理服务器的身份可能有错",MSG_ERROR_MSG);
				return FALSE;
			}
			if(buf[1] != 0)
			{
				ShowConnectError("请重新输入您通向代理服务器的用户名和密码",MSG_ERROR_MSG);
				return FALSE;
			}
		}
		
		// 2、请求连接远程服务器
		/*+----+-----+-------+------+----------+--------+
		|VER | CMD |  RSV  | ATYP | DST.ADDR | DST.PORT |
		+----+-----+-------+------+----------+----------+
		| 1  |  1  | X'00' |  1   | Variable |    2     |
		+----+-----+-------+------+----------+----------*/
		nOff = 0;
		buf[nOff++] = 5;	// ver
		buf[nOff++] = 1;	// connect;
		buf[nOff++] = 0;	// RSV
		buf[nOff++] = 1;	// Adress type : IP V4
		memcpy(buf + nOff,(char*)&ServerAddress.sin_addr,4);
		nOff += 4;
		*(WORD*)(buf + nOff) = ServerAddress.sin_port;
		nOff += 2;

		DumpData("Reqest connect : ",buf,nOff);
		if(send(m_SocketClient,buf,nOff,0) != nOff)
		{
			ShowConnectError("请求代理服务器与远程连接失败",0);
			return FALSE;
		}
		
		// 接收PROXY对connect的reply
		// reply的数据结构与connect请求的一样
		if(recv(m_SocketClient,buf,4,0) != 4)
		{
			ShowConnectError("接收代理服务器对于连接的应答失败",0);
			return FALSE;
		}
		DumpData("Server reply Reqest connect : ",buf,4);

		if(buf[0] != 5)
		{
			ShowConnectError("接收代理服务器对于连接的应答失败,Error 1",MSG_ERROR_MSG);
			return FALSE;
		}
		if(buf[1] != 0)
		{
			ShowConnectError("代理服务器拒绝向远程连接的请求",MSG_ERROR_MSG);
			return FALSE;
		}

		int nLeftDataLen = buf[3] == 1 ? 6 : buf[4] + 2;
		if(recv(m_SocketClient,buf,nLeftDataLen,0) != nLeftDataLen)
		{
			ShowConnectError("接收代理服务器数据过程中出现异常,Error 1",0);
			return FALSE;
		}
		DumpData("Server reply Reqest connect, other data : ",buf,nLeftDataLen);
	}
	else if(m_ProxyOption.socksType == proxy4)
	{
	   /*----+----+----+----+----+----+----+----+----+----+....+----+
		|VER | CMD| DSTPORT |      DSTIP        | USERID       |NULL|
		+----+----+----+----+----+----+----+----+----+----+....+----*/
		//DebugMsgLn("Connect '%s' via proxy server '%s' by sock4 on port = %d",m_szServerName,m_szProxyServer,m_wProxyPort);
		int nOff = 0;
		buf[nOff++] = 4;	// VER
		buf[nOff++] = 1;	// connect
		*(WORD*)(buf + nOff) = ServerAddress.sin_port;
		nOff += 2;
		memcpy(buf + nOff,(char*)&ServerAddress.sin_addr,4);
		nOff += 4;
		buf[nOff++] = 0;	// no userid

		DumpData("Reqest connect : ",buf,nOff);
		if(send(m_SocketClient,buf,nOff,0) != nOff)
		{
			ShowConnectError("请求代理服务器与远程连接失败",0);
			return FALSE;
		}
		if(recv(m_SocketClient,buf,8,0) != 8)
		{
			ShowConnectError("接收代理服务器对于连接的应答失败",0);
			return FALSE;
		}
		DumpData("Server reply Reqest connetct : ",buf,8);
		if(buf[0] != 0)		// the version of the reply code
		{
			ShowConnectError("接收代理服务器对于连接的应答失败",MSG_ERROR_MSG);
			return FALSE;
		}
		if(buf[1] != 90)	// request granted
		{
			ShowConnectError("代理服务器拒绝连接或连接失败",MSG_ERROR_MSG);
			return FALSE;
		}
	}

	// 3、设为正常的NonBlocking方式
	WSAEventSelect(m_SocketClient , m_hRefCommEvent, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	return TRUE;
}
//------------------------------------------------------------------------