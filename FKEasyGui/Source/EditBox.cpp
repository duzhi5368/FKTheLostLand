/**
*	created:		2013-5-28   17:30
*	filename: 		EditBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/editbox.h"
#include <windowsx.h>
//------------------------------------------------------------------------
CEGEditBox::CEGEditBox(void)
{
}
//------------------------------------------------------------------------
CEGEditBox::~CEGEditBox(void)
{
}
//------------------------------------------------------------------------
BOOL CEGEditBox::Create( HWND hParents,  DWORD dwStyle, int x, int y, int width, int height, CHAR * pText )
{
	m_hWnd = CreateWindow( _T("EDIT"), pText, WS_VISIBLE|WS_CHILDWINDOW|dwStyle, x, y, width, height, hParents, NULL, GetModuleHandle(NULL), NULL );
	if( m_hWnd == NULL ) 
		return FALSE;
	if( !HandleWnd() )
	{
		DestroyWindow( m_hWnd );
		return FALSE;
	}
	
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CEGEditBox::OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			OnKeyDown( wParam, lParam );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------------
VOID CEGEditBox::OnKeyDown( WPARAM wParam, LPARAM lParam )
{
	// TODO:
}
//------------------------------------------------------------------------
int CEGEditBox::GetLength()
{
	return Edit_GetTextLength( m_hWnd );
}
//------------------------------------------------------------------------