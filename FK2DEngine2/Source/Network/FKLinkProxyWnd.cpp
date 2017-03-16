/**
*	created:		2013-5-10   6:27
*	filename: 		FKLinkProxyWnd
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
/*
 * 功能：管理多个IClientSocket连接
 *		 如果设置为多线程方式，可以选择经由一个临时的wnd负责消息同步或通过队列缓冲方式实现同步
 * 注意：此为多连接管理器，不管理每个连接的加密和封包层
 * 用例：
 *		1、服务器间通讯时，通讯线程和主线程是在一起的，采取直接回调方式可获取最高性能
 *		2、如果通讯线程和主线程不属于同一个线程，则需要借助CLinkProxyWnd实现同步问题
 * 说明：1、IClientSink的几个接口总是在IThreadRoute中被调用，而AddSocket()和RemoveSocket()
 *		 可能在另一个线程中被调用，所以可能存在访问m_SocketBuf的线程同步问题，外部调用
 *		 必须保证RemoveSocket时没有与此socket相关的事件发生，即此socket已经关闭掉了，
 *		 这是从效率角度考虑的，不必对每次事件响应都进行对m_SocketBuf锁定
 *		2、用户执行RemoveSocket()关闭连接，而不是IClientSocket->CloseConnect()，但异常连接断开时CLinkProxyWnd自动完成RemoveSocket()操作
 *		3、暂不实现低效的队列数据包缓存方式
 * 修改：
 *		1、删除连接时，应用层负执行pClientSocket->Release()操作
 */
//------------------------------------------------------------------------
#include <atlbase.h>
#include <atlwin.h>
#include "../../Include/Network/FKThreadRoute.h"
#include "../../Include/Network/FKClientSocket.h"
#include "../../Include/Network/FKCClientSocket.h"
#include "../../Include/Network/FKLinkProxyWnd.h"
#include "../../Include/Network/FKFunc.h"
#include "../../Include/ResMgr/ResMgrCommon.h"
//------------------------------------------------------------------------
#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif
//------------------------------------------------------------------------
CLinkProxyWnd::CLinkProxyWnd()
{
	m_nBufLoopIndex = 0;
	m_nSocketCount = 0;

	m_pThreadRoute = NULL;
	m_pTrace = NULL;

	m_bInSameThread = FALSE;
	m_bSyncByWnd = TRUE;
}
//------------------------------------------------------------------------
// 多线程队列方式暂不支持
extern "C" BOOL CreateLinkProxyWnd(IThreadRoute *pThreadRoute,ITrace* pTrace,BOOL bSyncByWnd,BOOL bInSameThread,ILinkProxy** ppLinkProxy)
{
	if(!bInSameThread && !bSyncByWnd)
	{
		TraceLn("Error : CreateLinkProxyWnd() : this thread mode is not be supported now!");
		return FALSE;
	}
	try
	{
		if(pThreadRoute == NULL)
			throw "param error";

		CLinkProxyWnd* pProxyWnd = new CLinkProxyWnd();
		if(pProxyWnd == NULL)
			throw "No Memory";
		if(!pProxyWnd->Create(pThreadRoute,pTrace,bSyncByWnd,bInSameThread))
			throw "Create wnd failed";
		*ppLinkProxy = static_cast<ILinkProxy*>(pProxyWnd);
		return TRUE;
	}
	catch(LPCSTR szMsg)
	{
		TraceLn("Error : CreateLinkProxy() : %s",szMsg);
		return FALSE;
	}
}
//------------------------------------------------------------------------
BOOL CLinkProxyWnd::CreateWnd()
{
	//RECT rect = {0,0,400,400};
	//m_hWnd = CWindowImpl<CLinkProxyWnd>::Create(NULL,rect,NULL,WS_POPUP);
	//return m_hWnd != NULL;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CLinkProxyWnd::Create(IThreadRoute *pThreadRoute,ITrace* pTrace,BOOL bSyncByWnd,BOOL bInSameThread)
{
#ifdef _DEBUG
	// 暂时始终开启锁 FreeKnight
	// m_LockSocketBuf.SetNoneLock(bInSameThread);
#endif

	m_pThreadRoute = pThreadRoute;
	m_pTrace = pTrace;
	m_bInSameThread = bInSameThread;
	m_bSyncByWnd = bSyncByWnd;
	if(bSyncByWnd)
		return CreateWnd();
	return TRUE;
}
//------------------------------------------------------------------------
// 注：被通讯线程回调，与wnd不是同一个线程
// 输入：dwSocketID	：在CLinkProxyWnd中定义为socket在m_SocketBuf中的索引
// 注：
//		应用层收到此消息以后需要调用CLinkProxyWnd::RemoveSocket()删除此socket对象
void CLinkProxyWnd::OnConnectError(DWORD dwSocketID,LPCSTR szMsg,DWORD dwErrorCode)
{
	m_LockSocketBuf.Lock();
	if(!IsValidSocketIndex(dwSocketID))
	{
		m_LockSocketBuf.Unlock();
		DebugMsgLn(L"Error : CLinkProxyWnd::OnConnectError() : invalid socket index = %d",dwSocketID);
		return;
	}
	SocketInfo& skt = m_SocketBuf[dwSocketID];
	if(m_bInSameThread)
	{
		skt.pSink->OnConnectError(skt.dwSocketID,szMsg,dwErrorCode);
	}
	else if(m_bSyncByWnd)
	{
		LINK_NOTE *pNode = new LINK_NOTE(dwSocketID,szMsg,strlen(szMsg) + 1,dwErrorCode);
		if(pNode)
			::PostMessage(m_hWnd,WM_LINK_MSG,linkConnectError,(LPARAM)pNode);
	}
	else
	{
		// not supported now
		//.......
	}
	m_LockSocketBuf.Unlock();
}
//------------------------------------------------------------------------
// 注：被通讯线程回调，与wnd不是同一个线程
// 输入：dwSocketID	：在CLinkProxyWnd中定义为socket在m_SocketBuf中的索引
void CLinkProxyWnd::OnConnectOK(DWORD dwSocketID)
{
	m_LockSocketBuf.Lock();
	if(!IsValidSocketIndex(dwSocketID))
	{
		m_LockSocketBuf.Unlock();
		DebugMsgLn(L"Error : CLinkProxyWnd::OnConnectOK() : invalid socket index = %d",dwSocketID);
		return;
	}
	SocketInfo& skt = m_SocketBuf[dwSocketID];
	if(m_bInSameThread)
		skt.pSink->OnConnectOK(skt.dwSocketID);
	else if(m_bSyncByWnd)
	{
		LINK_NOTE *pNode = new LINK_NOTE(dwSocketID,NULL,0,0);
		if(pNode)
			::PostMessage(m_hWnd,WM_LINK_MSG,linkConnectOK,(LPARAM)pNode);
	}
	m_LockSocketBuf.Unlock();
}
//------------------------------------------------------------------------
// 注：被通讯线程回调，与wnd不是同一个线程
// 输入：dwSocketID	：在CLinkProxyWnd中定义为socket在m_SocketBuf中的索引
void CLinkProxyWnd::OnConnectClose(DWORD dwSocketID,LPCSTR szMsg,DWORD dwErrorCode)
{
	m_LockSocketBuf.Lock();
	if(!IsValidSocketIndex(dwSocketID))
	{
		DebugMsgLn(L"Error : CLinkProxyWnd::OnConnectClose() : invalid socket index = %d",dwSocketID);
		m_LockSocketBuf.Unlock();
		return;
	}
	SocketInfo& skt = m_SocketBuf[dwSocketID];
	if(m_bInSameThread)
	{
		skt.pSink->OnConnectClose(skt.dwSocketID,szMsg,dwErrorCode);
	}
	else if(m_bSyncByWnd)
	{
		LINK_NOTE *pNode = new LINK_NOTE(dwSocketID,szMsg,strlen(szMsg) + 1,dwErrorCode);
		if(pNode)
			::PostMessage(m_hWnd,WM_LINK_MSG,linkConnectClose,(WPARAM)pNode);
	}
	m_LockSocketBuf.Unlock();
}
//------------------------------------------------------------------------
// 注：被通讯线程回调，与wnd不是同一个线程
// 输入：dwSocketID	：在CLinkProxyWnd中定义为socket在m_SocketBuf中的索引
void CLinkProxyWnd::OnDataArrived(DWORD dwSocketID)
{
	m_LockSocketBuf.Lock();
	if(!IsValidSocketIndex(dwSocketID))
	{
		DebugMsgLn(L"Error : CLinkProxyWnd::OnDataArrived() : invalid socket index = %d",dwSocketID);
		m_LockSocketBuf.Unlock();
		return;
	}
	SocketInfo& skt = m_SocketBuf[dwSocketID];
	if(m_bInSameThread)
		skt.pSink->OnDataArrived(skt.dwSocketID);
	else if(m_bSyncByWnd)
	{
		::PostMessage(m_hWnd,WM_LINK_MSG,linkDataArrived,(WPARAM)dwSocketID);
	}
	m_LockSocketBuf.Unlock();
}
//------------------------------------------------------------------------
BOOL CLinkProxyWnd::AddSocket(DWORD dwSocketID,IClientSocketSink *pSink,IClientSocket** ppClientSocket)
{
	Assert(pSink != NULL);
	Assert(ppClientSocket != NULL);
	m_LockSocketBuf.Lock();
	if(m_nSocketCount >= MAX_CLIENT_SOCKET)
	{
		m_LockSocketBuf.Unlock();
		DebugMsgLn(L"Error : CLinkProxyWnd::AddSocket() ：too much sockets");
		return FALSE;
	}
	for(DWORD i = 0; i < MAX_CLIENT_SOCKET; i++)
	{
		if(m_SocketBuf[i].dwSocketID == dwSocketID)
		{
			TraceLn("Error : CLinkProxyWnd::AddSocket() ：find same dwSocketID = %d",dwSocketID);
			return FALSE;
		}
	}
	// 寻找一个空位
	DWORD dwIndex = 0;
	for(; dwIndex < MAX_CLIENT_SOCKET; dwIndex++)
	{
		if(m_SocketBuf[m_nBufLoopIndex].dwSocketID == INVALID_SOCKET_ID)
			break;
		m_nBufLoopIndex = (m_nBufLoopIndex + 1) % MAX_CLIENT_SOCKET;
	}
	if(dwIndex >= MAX_CLIENT_SOCKET)
	{
		m_LockSocketBuf.Unlock();
		DebugMsgLn(L"Error : CLinkProxyWnd::AddSocket() ：no free socket");
		return FALSE;
	}

	IClientSocket* pClientSocket = NULL;
	if(!CreateClientSocket(dwIndex,static_cast<IClientSocketSink*>(this),m_pThreadRoute,m_pTrace,m_bInSameThread,&pClientSocket))
	{
		m_LockSocketBuf.Unlock();
		DebugMsgLn(L"Error : CLinkProxyWnd::AddSocket() ：CreateClientSocket() failed");
		return FALSE;
	}
	
	SocketInfo& skt = m_SocketBuf[m_nBufLoopIndex];
	skt.dwSocketID = dwSocketID;
	skt.pClientSocket = pClientSocket;
	skt.pSink = pSink;
	m_nSocketCount++;
	*ppClientSocket = pClientSocket;

	m_nBufLoopIndex = (m_nBufLoopIndex + 1) % MAX_CLIENT_SOCKET;
	m_LockSocketBuf.Unlock();
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CLinkProxyWnd::RemoveSocket(DWORD dwSocketIndex)
{
	m_LockSocketBuf.Lock();
	if(!IsValidSocketIndex(dwSocketIndex))
	{
		m_LockSocketBuf.Unlock();
		DebugMsgLn(L"Error : CLinkProxyWnd::RemoveSocket() : invalid socket index = %d",dwSocketIndex);
		return FALSE;
	}
	m_SocketBuf[dwSocketIndex].Close();
	m_nSocketCount--;
	m_LockSocketBuf.Unlock();
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CLinkProxyWnd::RemoveSocket(IClientSocket *pClientSocket)
{
	m_LockSocketBuf.Lock();
	for(DWORD i = 0; i < MAX_CLIENT_SOCKET; i++)
		if(m_SocketBuf[i].IsValid() && m_SocketBuf[i].pClientSocket == pClientSocket)
		{
			m_SocketBuf[i].Close();
			m_nSocketCount--;
			m_LockSocketBuf.Unlock();
			return TRUE;
		}
	m_LockSocketBuf.Unlock();
	return FALSE;
}
//------------------------------------------------------------------------
// 采用基于HWND的方式同步主线程，前提是主程序拥有窗口消息循环
LRESULT CLinkProxyWnd::OnLinkMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	if(wParam == linkDataArrived)
	{
		SocketInfo& skt = m_SocketBuf[(DWORD)lParam];
		if(skt.IsValid())
		{
			if(skt.pClientSocket->IsConnected())
			{
				skt.pSink->OnDataArrived(skt.dwSocketID);
			}
			else
			{
			}
		}
		else
		{
			DebugMsgLn(L"Warn : CLinkProxyWnd::OnLinkMsg() : socket[%d] is invalid now",lParam);
		}
		return 0;
	}
	LINK_NOTE * pNote = (LINK_NOTE*)lParam;

	// 因为SocketInfo的增删在本线程中完成，所以不必进行互斥处理
	SocketInfo& skt = m_SocketBuf[pNote->dwSocketIndex];
	if(skt.IsValid())
	{
		switch(wParam)
		{
			case linkDataSending:
				((CClientSocket *)(skt.pClientSocket))->OnFD_WRITE();
				break;
			case linkConnectOK:
				skt.pSink->OnConnectOK(skt.dwSocketID);
				break;
			case linkConnectError:
				skt.pSink->OnConnectError(skt.dwSocketID,pNote->szData,pNote->dwErrorCode);
				break;
			case linkConnectClose:
				if(skt.pClientSocket->IsConnected())
				{
					skt.pSink->OnConnectClose(skt.dwSocketID,pNote->szData,pNote->dwErrorCode);
					skt.pClientSocket->CloseConnect();	// 连接断开时，清理连接资源。因为为保证应用层接收到数据，ClientSocket.cpp没有清理连接资源
				}
				break;
			default:
				break;
		}
	}
	else
	{
		// 原因：当连接已经断开且连接对象已经不在m_SocketBuf中，但系统消息队列中可能还有连接的错误信息
		DebugMsgLn(L"Warn : CLinkProxyWnd::OnLinkMsg() : socket[%d] is invalid now",pNote->dwSocketIndex);
	}
	if(pNote)
		delete pNote;
	return 0;
}
//------------------------------------------------------------------------
void CLinkProxyWnd::Close()
{
	for(DWORD i = 0; i < MAX_CLIENT_SOCKET; i++)
		if(m_SocketBuf[i].IsValid())
			m_SocketBuf[i].Close();
	m_nSocketCount = 0;
	if(m_hWnd)
		DestroyWindow();
}
//------------------------------------------------------------------------