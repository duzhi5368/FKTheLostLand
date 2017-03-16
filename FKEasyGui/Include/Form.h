/**
*	created:		2013-5-28   17:31
*	filename: 		Form
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGForm:public CEGBaseWnd
{
public:
	CEGForm(void);
	virtual ~CEGForm(void);
public:
	BOOL	Create( HWND hParents, int x, int y, int width, int height, DWORD	dwStyle, DWORD dwRemoveStyle, 
		CHAR * pszTitle,  int nCmdShow = SW_SHOW, LPCTSTR pIcon = NULL, LPCTSTR psmIcon = NULL, 
		LPCTSTR pMenu = NULL, LPCTSTR pCursor = IDC_ARROW, 
		HBRUSH hbrBackground = (HBRUSH)(COLOR_WINDOW+1) );
	virtual int	 EnterMessageLoop();
	virtual VOID	OnShow()				{}
	virtual BOOL	OnClose()				{return FALSE;}
	virtual VOID	OnCommand( UINT	id )	{};
	virtual BOOL	QueryClose()			{return FALSE;}
	virtual VOID	MessageLoop(MSG & msg);
	virtual BOOL	OnMessage( HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam );
};
//------------------------------------------------------------------------