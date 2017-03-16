/**
*	created:		2013-5-28   20:30
*	filename: 		TrayIcon
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/trayicon.h"
//------------------------------------------------------------------------
CEGTrayIcon::CEGTrayIcon(void)
{
	ZeroMemory( &m_IconData, sizeof( m_IconData ));
	m_IconData.cbSize  = sizeof( m_IconData );
	m_bRegistered = FALSE;
}
//------------------------------------------------------------------------
CEGTrayIcon::~CEGTrayIcon(void)
{
	UnRegister();
}
//------------------------------------------------------------------------
BOOL CEGTrayIcon::Register(HWND	hWnd, UINT nMsg, UINT nIcon, HICON hIcon, CHAR * szTip )
{
	if( m_bRegistered )
		return FALSE;
	ZeroMemory( &m_IconData, sizeof( m_IconData ));
	m_IconData.cbSize  = sizeof( m_IconData );
	m_IconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	m_IconData.hWnd = hWnd;
	m_IconData.uID = nIcon;
	m_IconData.hIcon = hIcon;
	m_IconData.uCallbackMessage = nMsg;
	strncpy( m_IconData.szTip, szTip, 128 );
	if( Shell_NotifyIcon( NIM_ADD, &m_IconData ) )
	{
		m_bRegistered = TRUE;
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------------
VOID CEGTrayIcon::UnRegister(void)
{
	if( !m_bRegistered )return;
	if( Shell_NotifyIcon( NIM_DELETE, &m_IconData ) )
		m_bRegistered = FALSE;
	return VOID();
}
//------------------------------------------------------------------------
VOID CEGTrayIcon::ShowCoolTip(CHAR * pszTitle , CHAR * pszText , UINT nTime)
{
	if( !m_bRegistered )
		return;
	m_IconData.uFlags |= NIF_INFO;
	strncpy( m_IconData.szInfo, pszText, 256 );
	strncpy( m_IconData.szInfoTitle, pszTitle, 64 );
	m_IconData.dwInfoFlags = NIIF_INFO;
	m_IconData.uTimeout = nTime;
	Shell_NotifyIcon( NIM_MODIFY, &m_IconData );
	return VOID();
}
//------------------------------------------------------------------------