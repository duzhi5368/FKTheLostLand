/**
*	created:		2013-5-28   17:26
*	filename: 		ComboBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGComboBox :
	public CEGBaseWnd
{
public:
	CEGComboBox(void);
	virtual ~CEGComboBox(void);
public:
	BOOL	Create( HWND hParents, int x, int y, int width, int height );
	int		AddString( LPCTSTR lpszString ){return ComboBox_AddString(m_hWnd, lpszString);}
	int		GetCurSel(){ return ComboBox_GetCurSel( m_hWnd );}
	int		SetCurSel(int index){ return ComboBox_SetCurSel( m_hWnd, index );}
};
//------------------------------------------------------------------------