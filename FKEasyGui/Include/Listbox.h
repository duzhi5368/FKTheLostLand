/**
*	created:		2013-5-28   17:37
*	filename: 		Listbox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGListBox :
	public CEGBaseWnd
{
public:
	CEGListBox(void);
	virtual ~CEGListBox(void);
public:
	virtual BOOL Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, int maxline);
	virtual int	AddLine( CHAR * pszText );
	VOID	printf_( char * line, ... );
	VOID	Clear()			{ListBox_ResetContent( m_hWnd );}
protected:
	int		m_iMaxLines;
};
//------------------------------------------------------------------------