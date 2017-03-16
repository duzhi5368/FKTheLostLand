/**
*	created:		2013-5-10   8:21
*	filename: 		CharSelSvrLinkSink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "IFKAppNetworkLink.h"
//------------------------------------------------------------------------
class CCharSelSvrLink : public IFKAppNetworkLink
{
public:
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

	// 返回当前连接到了哪一个状态
	int						GetType(void);
public:
	CCharSelSvrLink(void);
public:	
	IClientLink *	m_pClientLink;
};
//------------------------------------------------------------------------
extern CCharSelSvrLink g_CharSelSvrConnector;
//------------------------------------------------------------------------