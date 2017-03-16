/**
*	created:		2013-4-16   5:12
*	filename: 		ProgressForm
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "..\..\FKEasygui\easygui.h"
//------------------------------------------------------------------------
class CProgressForm : public CEGForm
{
public:
	CProgressForm(void);
	virtual ~CProgressForm(void);
	BOOL	Create( HWND hParents, const char * pszTitle, const char * pszLabel, BOOL bSmooth );
	BOOL	Show( const char * pszTitle, int x, int y, int imin = 0, int imax = 100 );
	VOID	StepIt( const char * pszLabelText = NULL );
	VOID	SetRange( int imin, int imax );
	VOID	SetPos( int pos );
	VOID	SetStep( int nStep );
	BOOL	OnClose(){ Hide(); return FALSE;}
protected:
	CEGProgressBar	m_pbMain;
	CEGLabel			m_lbText;
};
//------------------------------------------------------------------------