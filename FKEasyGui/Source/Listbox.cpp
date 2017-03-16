/**
*	created:		2013-5-28   17:37
*	filename: 		Listbox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/listbox.h"
//------------------------------------------------------------------------
CEGListBox::CEGListBox(void)
{
	m_iMaxLines = 0;
}
//------------------------------------------------------------------------
CEGListBox::~CEGListBox(void)
{
}
//------------------------------------------------------------------------
BOOL CEGListBox::Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, int maxline )
{
	m_hWnd = CreateWindow( _T("LISTBOX"), NULL, WS_VISIBLE | WS_CHILDWINDOW | dwStyle,
		x, y, width, height, hParents, NULL, GetModuleHandle( NULL), NULL );
	if( m_hWnd == NULL ) 
		return FALSE;
	if( !HandleWnd() )
	{
		DestroyWindow(m_hWnd);
		return FALSE;
	}
	m_iMaxLines = maxline;
	return TRUE;
}
//------------------------------------------------------------------------
int	CEGListBox::AddLine( CHAR * pszText )
{
	int cnt = 0;
	cnt = ListBox_GetCount( m_hWnd );
	if( cnt >= m_iMaxLines )
	{
		ListBox_DeleteString( m_hWnd, 0 );
		cnt --;
	}
	
	int pos=GetScrollPos(m_hWnd,SB_VERT);
	int maxpos,minpos;
	GetScrollRange(m_hWnd,SB_VERT,&minpos,&maxpos);
	
	int index = ListBox_AddString( m_hWnd, pszText );
	if ( maxpos-pos <= 35 )
		ListBox_SetCurSel( m_hWnd, cnt );
	return index;
}
//------------------------------------------------------------------------
VOID CEGListBox::printf_( char * line, ... )
{
	char	szBuff1[2048];
	char	szBuff2[2048];
	memset( szBuff1, 0, 2048 );
	memset( szBuff2, 0, 2048 );
	SYSTEMTIME	st;
	va_list	vl;
	va_start( vl, line );
	vsprintf( szBuff1, line, vl );
	va_end( vl);
	GetLocalTime(&st);
	szBuff1[2047] = '\0';
	sprintf( szBuff2, "%s",szBuff1 );
	szBuff2[2047] = '\0';
	AddLine( szBuff2 );
}
//------------------------------------------------------------------------