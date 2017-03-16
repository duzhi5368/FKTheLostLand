/**
*	created:		2013-5-28   20:28
*	filename: 		RichEdit
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "editbox.h"
#include <richedit.h>
//------------------------------------------------------------------------
class CEGRichEdit :
	public CEGEditBox
{
public:
	CEGRichEdit(void);
	virtual ~CEGRichEdit(void);
public:
	virtual BOOL	Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pText );
	virtual BOOL	printf( DWORD dwColor, char * pBuff, ... );
	virtual BOOL	AddLine( DWORD dwColor, char * pLine );
	virtual BOOL	AddLink( char * pLink, DWORD dwColor = 0xff  );
	virtual VOID	OnNotify( NMHDR * pnmhdr );
	virtual VOID	OnLink( ENLINK * pLink );
	virtual DWORD	SetBkGndColor( DWORD dwColor );
	virtual BOOL	GetCharRange( CHARRANGE &chrge, char * pRetString )
	{
		TEXTRANGE tr;
		tr.chrg = chrge;
		tr.lpstrText = pRetString;
		int length = (int)SendMessage( m_hWnd, EM_GETTEXTRANGE, 0, (LPARAM)&tr );
		if( length == 0 )return FALSE;
		pRetString[length] = 0;
		return TRUE;
	}
}; 
//------------------------------------------------------------------------