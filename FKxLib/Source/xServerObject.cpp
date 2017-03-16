/**
*	created:		2013-4-16   4:59
*	filename: 		xServerObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xiocpserver.h"
#include "..\Include\xserverobject.h"
//------------------------------------------------------------------------
xServerObject::xServerObject(void)
{
	m_pxIocpServer = NULL;
}
//------------------------------------------------------------------------
xServerObject::~xServerObject(void)
{
	m_pxIocpServer = NULL;
}
//------------------------------------------------------------------------