/**
*	created:		2013-5-10   8:03
*	filename: 		LoginSvrLinkSink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/Network/LoginSvrLinkSink.h"
#include "../../Include/FKLogger.h"
//------------------------------------------------------------------------
CLoginSvrLink g_LoginSvrConnector;
//------------------------------------------------------------------------
CLoginSvrLink::CLoginSvrLink(void)
{
	m_pClientLink = NULL;
}
//------------------------------------------------------------------------
// 描  述：连接服务器失败
// 参  数：szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
void CLoginSvrLink::OnConnectError(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode)
{
	wchar_t szTemp[256];
	wsprintf(szTemp, L"连接Login服务器失败。[SockID = %d， Msg：%s，ErrorCode：%d]", dwSocketID, szMsg, dwErrorCode);
	LogError( szTemp );
}
//------------------------------------------------------------------------
// 描  述：连接建立
void CLoginSvrLink::OnConnectOK(DWORD dwSocketID)
{	
	LogInfo( L"连接Login服务器成功： %d", dwSocketID );
}
//------------------------------------------------------------------------
// 描  述：当前连接断开
// 参  数：szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
void CLoginSvrLink::OnConnectClose(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode)
{
	wchar_t szTemp[256];
	wsprintf(szTemp, L"Login服务器连接断开。[SockID = %d， Msg：%s，ErrorCode：%d]", dwSocketID, szMsg, dwErrorCode);
	LogInfo( szTemp );
}
//------------------------------------------------------------------------
// 描  述：发送数据包
int	CLoginSvrLink::Send(LPCSTR buf, int nLen)
{
	if(m_pClientLink == NULL)
	{
		return 0;
	}

	return m_pClientLink->Send(buf, nLen);
}
//------------------------------------------------------------------------
// 描  述：取得IClientLink指针, 使用方法更丰富
IClientLink * CLoginSvrLink::GetClientLink(void)
{
	return m_pClientLink;
}
//------------------------------------------------------------------------
// 描  述：收到一个数据包
// 参  数：如果接收数据包的线程与IThreadRoute不是同一线程，
// 返回值：如由一个窗口(ILinkWnd)负责管理通讯，则ILinkWnd必须负责建立一个接收数据包队列
BOOL CLoginSvrLink::OnRecv(DWORD dwSocketID, LPCSTR buf, int nLen)
{
	if(nLen < sizeof(WORD))
	{
		return FALSE;
	}

	WORD wMsgRoot = *((WORD *)(buf));
	switch(wMsgRoot)
	{
	default:
		{
			LogWarn( L"CLoginSvrLink::OnRecv收到不明消息 %d", wMsgRoot);
		}
		break;
	}
	
	return TRUE;
}
//------------------------------------------------------------------------
int CLoginSvrLink::GetType(void)
{
	return eNLS_LoginSvr;
}
//------------------------------------------------------------------------