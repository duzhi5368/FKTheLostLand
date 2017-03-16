/**
*	created:		2013-4-16   5:29
*	filename: 		IOConsole
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/ioconsole.h"
#include <stdio.h>
//------------------------------------------------------------------------
CIOConsole::CIOConsole(void)
{
	m_pInputListener = NULL;
}
//------------------------------------------------------------------------
CIOConsole::~CIOConsole(void)
{
}
//------------------------------------------------------------------------
void CIOConsole::OutPut( DWORD dwColor, const char * pszString, ...)
{
	if( this == NULL )return;

	char	szBuff[4096];
	va_list	vl;
	va_start( vl, pszString );
	vsprintf( szBuff, pszString, vl );
	va_end( vl);
	OutPutStatic( dwColor,szBuff );
}
//------------------------------------------------------------------------