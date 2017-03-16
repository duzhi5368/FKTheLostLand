/**
*	created:		2013-5-28   20:27
*	filename: 		PushButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGPushButton :
	public CEGBaseWnd
{
public:
	CEGPushButton(void);
	virtual ~CEGPushButton(void);
public:
	BOOL	Create( HWND hParents, CHAR * pText,DWORD dwStyle,  int x, int y, int width, int height, DWORD dwExtStyle = 0 );
};
//------------------------------------------------------------------------