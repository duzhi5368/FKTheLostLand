/**
*	created:		2013-5-10   6:23
*	filename: 		FKLinkProxyWnd
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKClientSocket.h"
#include "FKFunc.h"
#include <atlbase.h>
#include <atlwin.h>
//------------------------------------------------------------------------
#define WM_LINK_MSG	(WM_USER + 123)
//------------------------------------------------------------------------
class CLinkProxyWnd : public CWindowImpl<CLinkProxyWnd>,public IClientSocketSink,public ILinkProxy
{
public:
	void Close();
	CLinkProxyWnd();
	DECLARE_WND_CLASS(NULL)
	BEGIN_MSG_MAP(CLinkProxyWnd)
		MESSAGE_HANDLER(WM_LINK_MSG, OnLinkMsg)
	END_MSG_MAP()

	BOOL Create(IThreadRoute *pThreadRoute,ITrace* pTrace,BOOL bSyncByWnd,BOOL bInSameThread);

	virtual BOOL AddSocket(DWORD dwSocketID,IClientSocketSink *pSink,IClientSocket** ppClientSocket);
	virtual BOOL RemoveSocket(IClientSocket* pClientSocket);
	virtual void Release()
	{
		Close();
		if(m_hWnd)
			DestroyWindow();
		delete this;
	}

private:
	BOOL RemoveSocket(DWORD dwSocketIndex);
	BOOL IsValidSocketIndex(DWORD dwSocketIndex)
	{
		if(dwSocketIndex >= MAX_CLIENT_SOCKET)
			return FALSE;
		return m_SocketBuf[dwSocketIndex].dwSocketID != INVALID_SOCKET_ID;
	}


	BOOL	CreateWnd();
	LRESULT OnLinkMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	// 连接服务器失败
	virtual void OnConnectError(DWORD dwSocketID,LPCSTR szMsg,DWORD dwErrorCode);
	// 连接建立
	virtual void OnConnectOK(DWORD dwSocketID);
	// 收到数据包
	// 注：	如果接收数据包的线程与IThreadRoute不是同一线程，
	//		如由一个窗口(ILinkWnd)负责管理通讯，则ILinkWnd必须负责建立一个接收数据包队列
	virtual void OnDataArrived(DWORD dwSocketID);

	// 当前连接断开
	virtual void OnConnectClose(DWORD dwSocketID,LPCSTR szMsg,DWORD dwErrorCode);
public:
	enum LinkMsgType
	{
		linkConnectError,linkConnectOK,linkDataArrived,linkConnectClose,linkDataSending
	};
	struct LINK_NOTE
	{
		LINK_NOTE(DWORD	dwSocketIndex,LPCSTR szData,DWORD dwDataLen,DWORD dwErrorCode)
		{
			if(szData)
			{
				this->szData = MyAllocMemory(dwDataLen);
				if(this->szData)
					memcpy(this->szData,szData,dwDataLen);
			}
			else
				this->szData = NULL;
			this->dwSocketIndex = dwSocketIndex;
			this->dwDataLen = dwDataLen;
			this->dwErrorCode = dwErrorCode;
		}
		~LINK_NOTE()
		{
			if(szData)
				delete szData;
		}
		DWORD		dwSocketIndex;
		char*		szData;			// 对于连接错误，这里是字符串，对于通讯包，这里是数据包
		DWORD		dwDataLen;		// 数据包长度
		DWORD		dwErrorCode;	//
	};
private:
	struct SocketInfo
	{
		SocketInfo()
		{
			pClientSocket = NULL;
			Close();
		}
		DWORD				dwSocketID;
		IClientSocketSink*	pSink;
		IClientSocket*		pClientSocket;
		void Close()
		{
			dwSocketID = INVALID_SOCKET_ID;
			pSink = NULL;
			if(pClientSocket)
			{
				if(pClientSocket->IsConnected())
					pClientSocket->CloseConnect();	// 由应用负责删除
				pClientSocket = NULL;
			}
		}
		BOOL IsValid()
		{
			return dwSocketID != INVALID_SOCKET_ID;
		}
	};

	SocketInfo		m_SocketBuf[MAX_CLIENT_SOCKET];
	CCriticalSectionLock	m_LockSocketBuf;	// 删除m_SocketBuf中的一项跟通讯线程IClientSocketSink事件需要互斥访问
	int				m_nSocketCount;
	int				m_nBufLoopIndex;			// 当增加新的socket时，循环索引m_SocketBuf空闲项
												// 这样做的好处是：新的socket不会立即使用一个老的socket槽
	IThreadRoute*	m_pThreadRoute;
	ITrace*			m_pTrace;

	BOOL			m_bInSameThread;
	BOOL			m_bSyncByWnd;
public:
};
//------------------------------------------------------------------------