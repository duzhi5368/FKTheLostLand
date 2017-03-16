/**
*	created:		2013-5-28   20:32
*	filename: 		Updown
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/updown.h"
//------------------------------------------------------------------------
CEGUpdown::CEGUpdown(void)
{
}
//------------------------------------------------------------------------
CEGUpdown::~CEGUpdown(void)
{
}
//------------------------------------------------------------------------
BOOL CEGUpdown::Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height )
{
	m_hWnd = CreateWindow( "UPDOWN", NULL, WS_VISIBLE|WS_CHILDWINDOW|dwStyle,
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