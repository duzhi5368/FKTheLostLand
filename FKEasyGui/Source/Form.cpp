/**
*	created:		2013-5-28   17:32
*	filename: 		Form
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/form.h"
#include <stdio.h>
//------------------------------------------------------------------------
#define FORM_WNDCLASS	_T( "FkForm" )
//------------------------------------------------------------------------
CEGForm::CEGForm(void)
{
}
//------------------------------------------------------------------------
CEGForm::~CEGForm(void)
{
}
//------------------------------------------------------------------------
BOOL	CEGForm::Create( HWND hParents, int x, int y, int width, int height,  DWORD	dwStyle, DWORD dwRemoveStyle, 
			   CHAR * pszTitle, int nCmdShow , LPCTSTR pIcon, 
			   LPCTSTR psmIcon, LPCTSTR pMenu, 
			   LPCTSTR pCursor, 
			   HBRUSH hbrBackground )
{
	CHAR	szWindowClass[256];
	sprintf( szWindowClass, "%s_%s", FORM_WNDCLASS, pszTitle );
	HINSTANCE	hInstance = GetModuleHandle( NULL );
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)DefWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)pIcon);
	wcex.hCursor		= LoadCursor(NULL, pCursor);
	wcex.hbrBackground	= (HBRUSH)hbrBackground;
	wcex.lpszMenuName	= (LPCTSTR)pMenu;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)psmIcon);

	RegisterClassEx(&wcex);
	DWORD	_dwStyle = dwStyle | WS_OVERLAPPEDWINDOW;
	_dwStyle ^= dwRemoveStyle;
	m_hWnd = CreateWindow(szWindowClass, pszTitle, _dwStyle,
		x, y, width, height, hParents, NULL, hInstance, NULL);

	if (!m_hWnd)
	{
		return FALSE;
	}
	if( !HandleWnd() )
	{
		DestroyWindow(m_hWnd);
		return FALSE;
	}
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}
//------------------------------------------------------------------------
int CEGForm::EnterMessageLoop()
{
	MSG	msg;  
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		MessageLoop(msg);
	}

	return (int) msg.wParam;
}
//------------------------------------------------------------------------
VOID	CEGForm::MessageLoop(MSG & msg)
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}
//------------------------------------------------------------------------
BOOL	CEGForm::OnMessage( HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{

	case	WM_NOTIFY:
		{
			CEGBaseWnd	*	pWnd = GetWndObject( ((NMHDR*)lParam)->hwndFrom );
			if( pWnd != NULL )
			{
				pWnd->OnNotify( (NMHDR*)lParam );
			}
		}
		break;
	case	WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT		pDrawItemStruct = (LPDRAWITEMSTRUCT)lParam;
			UINT	id = (UINT)wParam;
			CEGBaseWnd * pWnd = GetWndObject( pDrawItemStruct->hwndItem );
			if( pWnd != NULL )
			{
				return pWnd->OnDrawItem( pDrawItemStruct );
			}
		}
		break;
	case	WM_SHOWWINDOW:
		{
			OnShow();
		}
		break;
	case	WM_CLOSE:
		{
			if( !OnClose() )
			{
				m_hResult = 0;
				return TRUE;
			}
			PostQuitMessage(0);
			return FALSE;
		}
		break;
	case	WM_COMMAND:
		{
			OnCommand( LOWORD(wParam) );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------------