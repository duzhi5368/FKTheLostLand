/**
*	created:		2013-5-28   17:28
*	filename: 		EditBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGEditBox:public CEGBaseWnd
{
public:
	CEGEditBox(void);
	virtual ~CEGEditBox(void);
public:
	int				GetLength();
	VOID			SetPasswordChar( CHAR passwordchar )			{Edit_SetPasswordChar(m_hWnd, passwordchar);}
	CHAR			GetPasswordChar()								{return Edit_GetPasswordChar(m_hWnd);}
	BOOL			IsPassword()									{return ((GetStyle() & ES_PASSWORD) == ES_PASSWORD );}
	VOID			SetPassword(BOOL bPassword )					{if( bPassword )AddStyle(ES_PASSWORD); else RemoveStyle(ES_PASSWORD);}
	BOOL			SetReadOnly( BOOL bReadOnly )					{return Edit_SetReadOnly(m_hWnd, bReadOnly );}
	int				GetLineCount()									{return Edit_GetLineCount( m_hWnd );}
	int 			GetLine(int line, CHAR * pszString, int cchMax ){return Edit_GetLine( m_hWnd, line, pszString, cchMax );}

	virtual BOOL	Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pText );
	VOID			Destroy();
	virtual VOID	OnKeyDown( WPARAM wParam, LPARAM lParam );
	virtual BOOL	OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};
//------------------------------------------------------------------------