/**
*	created:		2013-5-28   20:29
*	filename: 		RichEdit
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/richedit.h"
#include <richedit.h>
//------------------------------------------------------------------------
CEGRichEdit::CEGRichEdit(void)
{
	LoadLibrary( "riched20.dll" );
}
//------------------------------------------------------------------------
CEGRichEdit::~CEGRichEdit(void)
{
}
//------------------------------------------------------------------------
BOOL CEGRichEdit::Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pText )
{
	m_hWnd = CreateWindowEx( 0,RICHEDIT_CLASS , pText, dwStyle|WS_VSCROLL |ES_AUTOVSCROLL|ES_MULTILINE |/*ES_AUTOHSCROLL |*/WS_CHILD| WS_VISIBLE, 
		x, y, width, height, hParents, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL );
	if( m_hWnd == NULL )
		return FALSE;
	if( !HandleWnd() )
	{
		DestroyWindow(m_hWnd);
		return FALSE;
	}
	SendMessage( m_hWnd, EM_SETEVENTMASK, 0, ENM_LINK );
	SendMessage( m_hWnd, EM_SETWORDWRAPMODE, 0, 0 );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CEGRichEdit::printf( DWORD dwColor, char * pBuff, ... )
{
	char szBuff[4096];
	memset( szBuff, 0, 4096 );
	va_list	vl;
	va_start( vl, pBuff );
	vsprintf( szBuff, pBuff, vl );
	va_end( vl);
	szBuff[4095] = '\0';
	return AddLine( dwColor, szBuff );
}
//------------------------------------------------------------------------
BOOL CEGRichEdit::AddLine( DWORD dwColor, char * pLine )
{
	int length = GetLength();
	Edit_SetSel( m_hWnd, length, length );
	CHARFORMAT	cf,cfold;
	ZeroMemory( &cf, sizeof( cf ) );
	ZeroMemory( &cfold, sizeof( cfold ) );
	cfold.cbSize = sizeof( cfold );
	SendMessage( m_hWnd, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cfold );
	cf.cbSize = sizeof( cf );
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = dwColor;
	if( !SendMessage( m_hWnd, EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cf ) )
		return FALSE;
	Edit_ReplaceSel( m_hWnd, pLine );
	SendMessage( m_hWnd, EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cfold );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CEGRichEdit::AddLink( char * pLink, DWORD dwColor )
{
	int length = GetLength();
	Edit_SetSel( m_hWnd, length, length );
	CHARFORMAT2	cf,cfold;
	ZeroMemory( &cf, sizeof( cf ) );
	ZeroMemory( &cfold, sizeof( cfold ) );
	cfold.cbSize = sizeof( cfold );
	SendMessage( m_hWnd, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cfold );
	cf.cbSize = sizeof( cf );
	cf.dwMask = CFM_LINK|CFM_BACKCOLOR;
	cf.dwEffects = CFE_LINK;
	cf.crBackColor = (COLORREF)dwColor;
	if( !SendMessage( m_hWnd, EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cf ) )
		return FALSE;
	Edit_ReplaceSel( m_hWnd, pLink );
	SendMessage( m_hWnd, EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cfold );
	return TRUE;
}
//------------------------------------------------------------------------
VOID CEGRichEdit::OnNotify( NMHDR * pnmhdr )
{
	switch( pnmhdr->code )
	{
	case EN_LINK:
		{
			OnLink((ENLINK *)pnmhdr);
		}
		break;
	}
}
//------------------------------------------------------------------------
VOID CEGRichEdit::OnLink( ENLINK * pLink )
{
	GetTickCount();
}
//------------------------------------------------------------------------
DWORD CEGRichEdit::SetBkGndColor( DWORD dwColor )
{
	return (DWORD)SendMessage( m_hWnd, EM_SETBKGNDCOLOR, (WPARAM)FALSE, (LPARAM)dwColor );
}
//------------------------------------------------------------------------