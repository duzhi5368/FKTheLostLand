/**
*	created:		2013-5-10   9:48
*	filename: 		GameSvrLinkSink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKClientSocket.h"
#include "FKThreadRoute.h"
#include "IFKAppNetworkLink.h"
#include "FKFunc.h"
#include <list>
#include <vector>
//------------------------------------------------------------------------
using std::list;
using std::vector;
//------------------------------------------------------------------------
struct IDataReceiver
{
	virtual BOOL OnReceived(const char* pData, int nLen) = 0;	
};
//------------------------------------------------------------------------
struct stReceiverInfoNode
{
	char*	pData;
	int		nLen;
};
//------------------------------------------------------------------------
class CGameSvrLink : public IFKAppNetworkLink, public IEventSink
{
private:
	typedef list< IDataReceiver* >		RECEIVER_LIST;
	typedef vector< RECEIVER_LIST >		MESSAGE_LIST;
private:
	MESSAGE_LIST						m_MsgList;		// 信息列表
	CThreadRouteObject					m_Thread;
	HANDLE								m_hEventWakeDecode;
	list<stReceiverInfoNode>			m_NodeList;
	CCriticalSectionLock				m_Lock;
	BOOL								m_bThreadRun;
public:
	// 锁定/解锁 接收器
	void					LockReceiver(BOOL bLock);
	// 设置线程状态
	void					SetThreadRun(BOOL bRun);
	BOOL					Receiver();
	virtual void			OnEvent(DWORD dwEventID);

	// 连接服务器失败
	// szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
	virtual void			OnConnectError(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode);

	// 连接建立
	virtual void			OnConnectOK(DWORD dwSocketID);

	// 收到一个数据包
	// 注：	如果接收数据包的线程与IThreadRoute不是同一线程，
	//		如由一个窗口(ILinkWnd)负责管理通讯，则ILinkWnd必须负责建立一个接收数据包队列
	virtual BOOL			OnRecv(DWORD dwSocketID, LPCSTR buf, int nLen);

	// 当前连接断开
	// szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
	virtual void			OnConnectClose(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode);

	// 发送数据包
	virtual int				Send(LPCSTR buf, int nLen);

	// 取得IClientLink指针, 使用方法更丰富
	virtual IClientLink *	GetClientLink(void);

	// 需要从网络获取数据的模块, 通过此函数注册后,才可收到消息 
	BOOL					AddReceiver(IDataReceiver *pReceiver, int MsgCode);

	// 移除模块接收者
	BOOL					RemoveReceiver(IDataReceiver *pReceiver, int MsgCode);

	// 返回当前连接到了哪一个状态
	int						GetType(void);
public:
	CGameSvrLink(void);
	virtual ~CGameSvrLink(void);
public:	
	IClientLink *	m_pClientLink;
};
//------------------------------------------------------------------------
extern CGameSvrLink g_GameSvrConnector;
//------------------------------------------------------------------------