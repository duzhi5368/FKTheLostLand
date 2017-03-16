/**
*	created:		2013-4-16   4:58
*	filename: 		xIocpUnit
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xiocpunit.h"
//------------------------------------------------------------------------
xIocpUnit::xIocpUnit(void)
{
	m_type = IO_NOTSET;
	m_UnitStruct.pUnit = this;
}
//------------------------------------------------------------------------
xIocpUnit::~xIocpUnit(void)
{
}
//------------------------------------------------------------------------
VOID xIocpUnit::OnComplete( DWORD dwNumberOfBytes, DWORD dwCompletionKey )
{
	sendEvent( IUE_ID + m_type, (int)dwNumberOfBytes, (LPVOID)this );
}
//------------------------------------------------------------------------