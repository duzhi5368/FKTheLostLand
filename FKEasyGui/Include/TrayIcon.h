/**
*	created:		2013-5-28   20:30
*	filename: 		TrayIcon
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <shellapi.h>
//------------------------------------------------------------------------
class CEGTrayIcon
{
public:
	CEGTrayIcon(void);
	virtual ~CEGTrayIcon(void);
private:
	NOTIFYICONDATA	m_IconData;
	BOOL	m_bRegistered;
public:
	virtual BOOL IsRegistered(){ return m_bRegistered;}
	virtual BOOL Register(HWND	hWnd, UINT nMsg, UINT nIcon, HICON hIcon, CHAR * szTip);
	virtual VOID UnRegister(void);
	virtual VOID ShowCoolTip(CHAR * pszTitle , CHAR * pszText , UINT nTime);
};
//------------------------------------------------------------------------