/**
*	created:		2013-5-28   17:27
*	filename: 		ComboBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/combobox.h"
//------------------------------------------------------------------------
CEGComboBox::CEGComboBox(void)
{
}
//------------------------------------------------------------------------
CEGComboBox::~CEGComboBox(void)
{
}
//------------------------------------------------------------------------
BOOL CEGComboBox::Create( HWND hParents, int x, int y, int width, int height )
{
	m_hWnd = CreateWindow( "COMBOBOX", NULL, WS_VISIBLE|WS_CHILDWINDOW|WS_BORDER|CBS_HASSTRINGS|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
		x,y,width, height, hParents, NULL, GetModuleHandle(NULL),0);
	if( m_hWnd == NULL )
		return FALSE;
	if( !HandleWnd() )
	{
		DestroyWindow(m_hWnd);
		return FALSE;
	}

	return TRUE;
}
//------------------------------------------------------------------------