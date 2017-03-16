/**
*	created:		2013-5-28   17:23
*	filename: 		Button
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/button.h"
//------------------------------------------------------------------------
#ifdef _DEBUG
static int NewCount=0;		// 创建Button的个数迭代
#endif
//------------------------------------------------------------------------
CEGButton::CEGButton(void)
{
}
//------------------------------------------------------------------------
CEGButton::~CEGButton(void)
{
}
//------------------------------------------------------------------------
BOOL CEGButton::Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pCaption, UINT id )
{
	m_hWnd = CreateWindow("BUTTON", pCaption, WS_CHILDWINDOW|WS_VISIBLE|dwStyle, 
		x, y, width, height, hParents, NULL, GetModuleHandle( NULL ), 0 );
	if( m_hWnd == NULL )
		return FALSE;

#ifdef _DEBUG
	// Debug模式下输出Button个数
	NewCount++;
	char buff[100];
	sprintf(buff,"New CButton(%p,%p) %d\r\n",m_hWnd,this,NewCount);
	OutputDebugString(buff);
#endif

	if( !HandleWnd())
	{
		DestroyWindow(m_hWnd);
		return FALSE;
	}
	SetId( id );
	return TRUE;
}
//------------------------------------------------------------------------