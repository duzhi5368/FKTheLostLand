/**
*	created:		2013-5-28   20:31
*	filename: 		Updown
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGUpdown:public CEGBaseWnd
{
public:
	CEGUpdown(void);
	virtual ~CEGUpdown(void);
public:
	BOOL	Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height );
};
//------------------------------------------------------------------------