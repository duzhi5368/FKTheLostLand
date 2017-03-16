/**
*	created:		2013-5-28   17:23
*	filename: 		Button
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGButton :
	public CEGBaseWnd
{
public:
	CEGButton(void);
	virtual ~CEGButton(void);
public:
	BOOL	Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pCaption, UINT id );
	BOOL	IsCheck(){return (Button_GetCheck( m_hWnd )==BST_CHECKED);}
	VOID	SetCheck( BOOL	bCheck ){
		Button_SetCheck( m_hWnd, bCheck );
	}
};
//------------------------------------------------------------------------