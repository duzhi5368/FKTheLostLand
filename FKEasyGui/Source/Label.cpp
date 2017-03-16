/**
*	created:		2013-5-28   17:35
*	filename: 		Label
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/label.h"
//------------------------------------------------------------------------
CEGLabel::CEGLabel(void)
{
}
//------------------------------------------------------------------------
CEGLabel::~CEGLabel(void)
{
}
//------------------------------------------------------------------------
BOOL CEGLabel::Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pText )
{
	m_hWnd = CreateWindow( "STATIC", pText, WS_CHILDWINDOW|WS_VISIBLE|dwStyle,
		x, y, width, height, hParents,NULL, GetModuleHandle( NULL ), NULL  );
	if( m_hWnd == NULL )
		return FALSE;
	if( !HandleWnd() )
	{
		DestroyWindow(m_hWnd );
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CEGLabel::printf( const char * pBuff, ... )
{
	char szBuff[2048];
	memset( szBuff, 0, 2048 );
	va_list	vl;
	va_start( vl, pBuff );
	vsprintf( szBuff, pBuff, vl );
	va_end( vl);
	szBuff[2047] = '\0';
	SetText( szBuff );
}
//------------------------------------------------------------------------