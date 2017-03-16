/**
*	created:		2013-5-10   8:23
*	filename: 		CharSelSvrLinkSink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/Network/CharSelSvrLinkSink.h"
#include "../../Include/FKLogger.h"
//------------------------------------------------------------------------
CCharSelSvrLink g_CharSelSvrConnector;
//------------------------------------------------------------------------
CCharSelSvrLink::CCharSelSvrLink(void)
{
	m_pClientLink = NULL;
}
//------------------------------------------------------------------------
// 描  述：连接服务器失败
// 参  数：szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
void CCharSelSvrLink::OnConnectError(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode)
{
	wchar_t szTemp[256];
	wsprintf(szTemp, L"连接CharSel服务器失败。[SockID = %d， Msg：%s，ErrorCode：%d]", dwSocketID, szMsg, dwErrorCode);
	LogError( szTemp );
}
//------------------------------------------------------------------------
// 描  述：连接建立
void CCharSelSvrLink::OnConnectOK(DWORD dwSocketID)
{	
	LogInfo( L"连接CharSel服务器成功： %d", dwSocketID );
}
//------------------------------------------------------------------------
// 描  述：当前连接断开
// 参  数：szMsg为错误信息具体内容。dwErrorCode为socket错误代码，参见Win32 API : GetLastError()
void CCharSelSvrLink::OnConnectClose(DWORD dwSocketID, LPCSTR szMsg, DWORD dwErrorCode)
{
	wchar_t szTemp[256];
	wsprintf(szTemp, L"CharSel服务器连接断开。[SockID = %d， Msg：%s，ErrorCode：%d]", dwSocketID, szMsg, dwErrorCode);
	LogInfo( szTemp );
}
//------------------------------------------------------------------------
// 描  述：发送数据包
int	CCharSelSvrLink::Send(LPCSTR buf, int nLen)
{
	if(m_pClientLink == NULL)
	{
		return 0;
	}

	return m_pClientLink->Send(buf, nLen);
}
//------------------------------------------------------------------------
// 描  述：取得IClientLink指针, 使用方法更丰富
IClientLink * CCharSelSvrLink::GetClientLink(void)
{
	return m_pClientLink;
}
//------------------------------------------------------------------------
// 描  述：收到一个数据包
// 参  数：如果接收数据包的线程与IThreadRoute不是同一线程，
// 返回值：如由一个窗口(ILinkWnd)负责管理通讯，则ILinkWnd必须负责建立一个接收数据包队列
BOOL CCharSelSvrLink::OnRecv(DWORD dwSocketID, LPCSTR buf, int nLen)
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
			LogWarn( L"CCharSelSvrLink::OnRecv收到不明消息 %d", wMsgRoot);
		}
		break;
	}

	return TRUE;
}
//------------------------------------------------------------------------
int CCharSelSvrLink::GetType(void)
{
	return eNLS_CharSelSvr;
}
//------------------------------------------------------------------------