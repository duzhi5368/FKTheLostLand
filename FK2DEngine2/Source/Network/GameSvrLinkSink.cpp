/**
*	created:		2013-5-10   10:36
*	filename: 		GameSvrLinkSink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include <winsock2.h>
#include "../../Include/Network/GameSvrLinkSink.h"
#include "../../Include/FKLogger.h"
#include <algorithm>
//------------------------------------------------------------------------
CGameSvrLink g_GameSvrConnector;
//------------------------------------------------------------------------
LPCSTR  szRunErrDesc = "与服务器(GameSvr)连接断开, 请重新登录游戏! 如情况再度出现,请邮件联系 duzhi5368@163.com";
//------------------------------------------------------------------------
CGameSvrLink::CGameSvrLink(void)
{
	m_bThreadRun = FALSE;
	m_pClientLink = NULL;
	m_hEventWakeDecode = NULL;
	
	m_Thread.Close();
	if(!m_Thread.Create(NULL))
	{
		return;
	}

	DWORD dwEventID;
	if(!m_Thread->AddEvent(static_cast<IEventSink*>(this),dwEventID))
		return;

	m_hEventWakeDecode = m_Thread->GetEventHandle(dwEventID);

	if(!m_Thread->Start())
	{
		m_Thread.Close();
		return;
	}

	return;
}
//------------------------------------------------------------------------
CGameSvrLink::~CGameSvrLink(void)
{
	m_Thread.Close();
}
//------------------------------------------------------------------------
// 描  述：连接服务器失败
// 参  数：szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
void CGameSvrLink::OnConnectError(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode)
{
	wchar_t szTemp[256];
	wsprintf(szTemp, L"连接Game服务器失败。[SockID = %d， Msg：%s，ErrorCode：%d]", dwSocketID, szMsg, dwErrorCode);
	LogError( szTemp );
}
//------------------------------------------------------------------------
// 描  述：连接建立
void CGameSvrLink::OnConnectOK(DWORD dwSocketID)
{
	LogInfo( L"连接Game服务器成功： %d", dwSocketID );
}
//------------------------------------------------------------------------
// 描  述：当前连接断开
// 参  数：szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
void CGameSvrLink::OnConnectClose(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode)
{
	wchar_t szTemp[256];
	wsprintf(szTemp, L"Game服务器连接断开。[SockID = %d， Msg：%s，ErrorCode：%d]", dwSocketID, szMsg, dwErrorCode);
	LogInfo( szTemp );
}
//------------------------------------------------------------------------
// 描  述：发送数据包
int	CGameSvrLink::Send(LPCSTR buf, int nLen)
{
	if(m_pClientLink == NULL)
	{
		return 0;
	}

	return m_pClientLink->Send(buf, nLen);
}
//------------------------------------------------------------------------
// 描  述：取得IClientLink指针, 使用方法更丰富
IClientLink * CGameSvrLink::GetClientLink(void)
{
	return m_pClientLink;
}
//------------------------------------------------------------------------
//需要从网络获取数据的模块 , 通过此函数注册后,才可收到消息 
BOOL CGameSvrLink::AddReceiver(IDataReceiver *pReceiver, int nMsgCode)
{
	MESSAGE_LIST  *pList  = &m_MsgList;
	int           MsgCode = nMsgCode;

	//在表中添加新注册者
	RECEIVER_LIST::iterator itor = find((*pList)[MsgCode].begin(), 
		(*pList)[MsgCode].end(), pReceiver);
	
	if (itor != (*pList)[MsgCode].end())
	{//接收者已经注册了
		return FALSE;
	}

	(*pList)[MsgCode].push_back(pReceiver);
	return TRUE;
}
//------------------------------------------------------------------------
//移除模块接收者
BOOL CGameSvrLink::RemoveReceiver(IDataReceiver *pReceiver, int nMsgCode) 
{
	MESSAGE_LIST  *pList  = &m_MsgList;
	int           MsgCode = nMsgCode;

	(*pList)[MsgCode].remove(pReceiver);
	return TRUE;
}
//------------------------------------------------------------------------
// 描  述：收到一个数据包
// 参  数：如果接收数据包的线程与IThreadRoute不是同一线程，
// 返回值：如由一个窗口(ILinkWnd)负责管理通讯，则ILinkWnd必须负责建立一个接收数据包队列
BOOL CGameSvrLink::OnRecv(DWORD dwSocketID, LPCSTR buf, int nLen)
{
	if(nLen < sizeof(WORD))
	{
		return FALSE;
	}
	
	stReceiverInfoNode node;
	node.pData = new char[nLen];
	memcpy(node.pData, buf, nLen);
	node.nLen = nLen;

	m_NodeList.push_back(node);
	
	if (!m_bThreadRun)
	{
		while(m_NodeList.size() != 0)
			Receiver();
		return TRUE;
	}

	SetEvent(m_hEventWakeDecode);

	return TRUE;
}
//------------------------------------------------------------------------
BOOL CGameSvrLink::Receiver()
{
	int nCount = m_NodeList.size();
	if(nCount == 0)
	{
		return FALSE;
	}

	stReceiverInfoNode node = m_NodeList.front();
	m_NodeList.pop_front();
	LPCSTR buf = node.pData;
	
	WORD wMsgRoot = *((WORD *)(buf));
	int hsize = sizeof(WORD);         //消息码的长度

	switch(wMsgRoot)
	{
	default:
		{
			for (RECEIVER_LIST::iterator itor = m_MsgList[wMsgRoot].begin();
			itor != m_MsgList[wMsgRoot].end(); ++itor)
			{
				(*itor)->OnReceived(buf + hsize, node.nLen - hsize);
			} 
		}
		break;
	}

	delete[] node.pData;
	
	return TRUE;
}
//------------------------------------------------------------------------
void CGameSvrLink::OnEvent(DWORD dwEventID)
{
	m_Lock.Lock();

	if(Receiver())
		SetEvent(m_hEventWakeDecode);

	m_Lock.Unlock();

	return;
}
//------------------------------------------------------------------------
void CGameSvrLink::LockReceiver(BOOL bLock)
{
	if(bLock)
	{
		m_Lock.Lock();		
		if (!m_bThreadRun)
		{
			while(m_NodeList.size() != 0)
				Receiver();
		}
	}
	else
		m_Lock.Unlock();
	
}
//------------------------------------------------------------------------
void CGameSvrLink::SetThreadRun(BOOL bRun)
{
	m_bThreadRun = bRun;
}
//------------------------------------------------------------------------
int CGameSvrLink::GetType(void)
{
	return eNLS_GameSvr;
}
//------------------------------------------------------------------------