/**
*	created:		2013-4-16   5:31
*	filename: 		ProgressForm
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/progressform.h"
//------------------------------------------------------------------------
CProgressForm::CProgressForm(void)
{
}
//------------------------------------------------------------------------
CProgressForm::~CProgressForm(void)
{
}
//------------------------------------------------------------------------
BOOL	CProgressForm::Create( HWND hParents, const char * pszTitle, const char * pszLabel, BOOL bSmooth )
{
	if( !CEGForm::Create(GetDesktopWindow(),40,40,300,200, WS_CHILDWINDOW, WS_OVERLAPPED|WS_SYSMENU| WS_MAXIMIZEBOX|WS_THICKFRAME,(char*)pszTitle, SW_HIDE, NULL, NULL, NULL, NULL, 
		(HBRUSH)(COLOR_BTNFACE+1)) )
		return FALSE;
	m_lbText.Create( m_hWnd, 0, 40, 40, 200, 20, (char*)pszLabel );
	m_pbMain.Create( m_hWnd, 40, 80, 200, 20, bSmooth?PBS_SMOOTH:0 );
	return TRUE;	
}
//------------------------------------------------------------------------
BOOL	CProgressForm::Show( const char * pszTitle, int x, int y, int imin, int imax )
{
	SetText( pszTitle );
	SetRange( imin, imax );
	CEGForm::Show();
	return TRUE;
}
//------------------------------------------------------------------------
VOID	CProgressForm::StepIt( const char * pszLabelText )
{
	if( pszLabelText )
	{
		m_lbText.SetText( pszLabelText );
	}
	this->m_pbMain.StepIt();
}
//------------------------------------------------------------------------
VOID	CProgressForm::SetRange( int imin, int imax )
{
	this->m_pbMain.SetRange( imin, imax );
}
//------------------------------------------------------------------------
VOID	CProgressForm::SetPos( int pos )
{
	this->m_pbMain.SetPos( pos );
}
//------------------------------------------------------------------------
VOID	CProgressForm::SetStep( int nStep )
{
	this->m_pbMain.SetStep( nStep );
}
//------------------------------------------------------------------------