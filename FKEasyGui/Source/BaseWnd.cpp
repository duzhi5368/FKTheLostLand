/**
*	created:		2013-5-28   17:19
*	filename: 		BaseWnd
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/basewnd.h"
//------------------------------------------------------------------------
#pragma warning(push)
#pragma warning(disable : 4321)
//------------------------------------------------------------------------
BOOL ConfirmBox( HWND hWnd, CHAR * pszCaption, CHAR * pszText )
{
	return (MessageBox( hWnd, pszText, pszCaption, MB_YESNO )==IDYES);
}
//------------------------------------------------------------------------
CEGBaseWnd::CEGBaseWnd(void)
{
	m_lOldProc = NULL;
	m_hWnd = NULL;
	m_pMsgFilter = NULL;
	m_hResult = 0;
	m_Id = 0;
}
//------------------------------------------------------------------------
CEGBaseWnd::~CEGBaseWnd(void)
{
}
//------------------------------------------------------------------------
HRESULT CEGBaseWnd::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( m_pMsgFilter != NULL )
	{
		if( m_pMsgFilter->FilterMessage(this, uMsg, wParam, lParam ) )
			return TRUE;
	}
	if( OnMessage( hWnd, uMsg, wParam, lParam ) )  
		return m_hResult;
	return CallWindowProc( (WNDPROC)m_lOldProc, hWnd, uMsg, wParam , lParam );
}
//------------------------------------------------------------------------
HRESULT CEGBaseWnd::GlobeMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	CEGBaseWnd * pWnd = NULL;
	LONG	lUserData = GetWindowLong( hWnd, GWL_USERDATA );
	pWnd = (CEGBaseWnd*)lUserData;
	if( pWnd != NULL )
		return pWnd->MsgProc(hWnd, uMsg, wParam, lParam );
	return FALSE;
}
//------------------------------------------------------------------------
BOOL CEGBaseWnd::HandleWnd()
{
	if( m_hWnd == NULL ) return FALSE;
	m_lOldProc = SetWindowLong( m_hWnd, GWL_WNDPROC, (LONG)GlobeMsgProc );
	if( m_lOldProc == NULL ) return FALSE;
	SetWindowLong( m_hWnd, GWL_USERDATA, (LONG)this );
	OnCreate( m_hWnd );
	return TRUE;
}
//------------------------------------------------------------------------
#pragma warning(pop)
//------------------------------------------------------------------------