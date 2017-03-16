/**
*	created:		2013-5-28   20:21
*	filename: 		ProgressBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/progressbar.h"
#include <windowsx.h>
//------------------------------------------------------------------------
CEGProgressBar::CEGProgressBar(void)
{
	INITCOMMONCONTROLSEX initctrls;
	initctrls.dwSize = sizeof( initctrls );
	initctrls.dwICC = ICC_PROGRESS_CLASS;
	InitCommonControlsEx( &initctrls );
}
//------------------------------------------------------------------------
CEGProgressBar::~CEGProgressBar(void)
{
}
//------------------------------------------------------------------------
BOOL CEGProgressBar::Create( HWND hParents, int x, int y, int width, int height, DWORD dwStyle )
{
	m_hWnd = CreateWindow( PROGRESS_CLASS, NULL, WS_VISIBLE|WS_CHILDWINDOW|dwStyle,
		x,y,width, height, hParents, NULL, GetModuleHandle(NULL),0);
	if( m_hWnd == NULL )
		return FALSE;
	if( !HandleWnd() )
	{
		DestroyWindow(m_hWnd);
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------