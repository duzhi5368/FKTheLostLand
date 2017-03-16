/**
*	created:		2013-5-28   20:20
*	filename: 		ProgressBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGProgressBar :
	public CEGBaseWnd
{
public:
	CEGProgressBar(void);
	virtual ~CEGProgressBar(void);
public:
	BOOL	Create( HWND hParents, int x, int y, int width, int height, DWORD dwStyle = 0 );
	VOID	SetRange( int iMininumValue, int iMaxnumValue )		{ SendMessage( m_hWnd, PBM_SETRANGE32, (WPARAM)iMininumValue, (LPARAM)iMaxnumValue ); }
	VOID	SetStep( int nStep )								{ SendMessage( m_hWnd, PBM_SETSTEP, (WPARAM)nStep, 0 ); }
	VOID	SetPos( int nPos )									{ SendMessage( m_hWnd, PBM_SETPOS, (WPARAM) nPos, 0 ); }
	VOID	StepIt()											{ SendMessage( m_hWnd, PBM_STEPIT, 0, 0 ); }
#if (_WIN32_WINNT >= 0x0501)
	VOID	SetMarquee( BOOL fEnable, DWORD dwDelay = 1000 )	{ SendMessage( m_hWnd, PBM_SETMARQUEE, (WPARAM)fEnable, (LPARAM)dwDelay ); }
#endif
};
//------------------------------------------------------------------------