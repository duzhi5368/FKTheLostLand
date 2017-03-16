/**
*	created:		2013-5-10   2:59
*	filename: 		FKCClientSocket
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <winsock2.h>
#include "FKThreadRoute.h"
#include "FKClientSocket.h"
#include "FKAPIProxy.h"
#ifdef _DEBUG
#define __USE_MALLOC		// 解决SGL STL内存假泄露问题
#endif
#include <list>
#include "FKFunc.h"
//------------------------------------------------------------------------
struct ITrace;
//------------------------------------------------------------------------
class CClientSocket : public IClientSocket,public IEventSink , public ITimerEventSink
{
	enum EnumSocketState
	{
		stateClosed = 0,			/*连接已经关闭*/
		stateReqConnect = 1			/*应用层发起连接，但通讯线程还没有发起连接*/,
		stateConnecting = 2			/*通讯层正在异步连接*/,
		stateConnected = 3			/*连接成功*/,
		stateConnectClosing = 4		/*连接正在关闭*/
	};
public:
	CClientSocket();
	~CClientSocket();
public:
	BOOL	DoConnect(LPCSTR szServerAddress, WORD wServerPort,NET_PROXY_OPTION* pProxyOption);
	BOOL	StartupSocket();
	void	OnFD_WRITE();
	int		DoSend(WSABUF& wsabuf,DWORD& dwByteSent);
	void	ShowSocketError(char *szErrorMsg, int nErrorCode);
	void	ShowConnectError(char *szErrorMsg, int nErrorCode);
	BOOL	GetIP(char *szName,struct in_addr *pAddr);

	void	Close();
	BOOL	Create(DWORD dwSocketID,IClientSocketSink *pSink,IThreadRoute *pThreadRoute, ITrace* pTrace,BOOL bInSameThread);
public:
	// 当前通道标识
	virtual DWORD GetSocketID(){
		return m_dwSocketID;
	}

	// 发起连接，当收到OnConnectOK()时，表示连接成功，收到OnConnectError()时表示连接失败
	// 在用户线程中被执行
	virtual BOOL Connect(LPCSTR szServerAddress, WORD wServerPort,NET_PROXY_OPTION* pProxyOption = NULL);

	// 关闭此连接，下次可以再次调用Connect()发起连接
	// 用户线程中被执行
	virtual BOOL CloseConnect();

	// 先立即发送，数据发不通时才将数据放入发送队列等待下次发送
	// 如果发送失败，应立即关闭连接
	// 在IThreadRoute中执行
	virtual int Send(LPCSTR buf,int nLen);

	// 接收数据
	// 在用户线程中被执行
	virtual BOOL Recv(int nBufLen,/*out*/char* buf,/*out*/int& nLen);


	// 查询当前是否在连接状态
	// 在用户线程中被执行
	virtual BOOL IsConnected(){
		return m_ConnectState == stateConnected;
	}

	virtual BOOL ioctrl(DWORD dwCmd,DWORD dwParam,/*out*/void* pData)
	{
		switch(dwCmd)
		{
		case IClientSocket::setMaxSendQueueCount:
			if(m_nMaxSendQueueCount <= 0 || m_nMaxSendQueueCount > 10000000)
				return FALSE;
			if(pData)
				*(int*)pData = m_nMaxSendQueueCount;
			m_nMaxSendQueueCount = dwParam;
			return TRUE;
		case IClientSocket::getMaxSendQueueCount:
			if(pData == NULL)
				return FALSE;
			*(int*)pData = m_nMaxSendQueueCount;
			return TRUE;
		case IClientSocket::getSocketHandle:
			if( pData == NULL )
				return FALSE;
			*(SOCKET *)pData = m_SocketClient;
			return TRUE;
		}
		return FALSE;
	}
	// 释放对象
	virtual void Release(){
		Close();
		delete this;
	}

	virtual void GotoNextState(IClientSocketSink* pSink){
		m_pSink = pSink;
	}
public:
	virtual void	OnEvent(DWORD dwEventID);
	virtual DWORD	OnTimer(DWORD dwTimerID,DWORD dwParam);
private:
	void ClearSocketData();
	BOOL IsClosed(){
		return m_ConnectState == stateClosed;
	}
private:
	int						m_ConnectState;		// 是否已经连接，注：连接状态有同时通讯线程和应用层线程同时改变的问题
	DWORD					m_dwCommEventID;
	DWORD					m_dwTimerEventID;
	DWORD					m_dwConnectEventID;	// 在线程中
	SOCKET					m_SocketClient;
	HANDLE					m_hRefCommEvent;
	char					m_szServerAddress[MAX_PATH];
	WORD					m_wServerPort;
	NET_PROXY_OPTION		m_ProxyOption;
	DWORD					m_dwSocketID;
	IThreadRoute*			m_pThreadRoute;
	IClientSocketSink*		m_pSink;
	ITrace*					m_pTrace;
	HANDLE					m_hOverlapedEvent;

	std::list<WSABUF>		m_SendQueue;
	CCriticalSectionLock	m_LockClientSocketContext;	// 有两个线程访问的ClientSocket资源都用此来互斥
	int						m_nMaxSendQueueCount;
	static	int				m_nWSAStartupRefCount;
};
//------------------------------------------------------------------------