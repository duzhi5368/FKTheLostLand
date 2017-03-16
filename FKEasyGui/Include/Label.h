/**
*	created:		2013-5-28   17:34
*	filename: 		Label
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "basewnd.h"
//------------------------------------------------------------------------
class CEGLabel:public CEGBaseWnd
{
public:
	CEGLabel(void);
	virtual ~CEGLabel(void);
public:
	BOOL	Create( HWND hParents, DWORD dwStyle, int x, int y, int width, int height, CHAR * pText );
	VOID	printf( const char * , ... );
};
//------------------------------------------------------------------------