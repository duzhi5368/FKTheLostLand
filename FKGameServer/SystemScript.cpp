/**
*	created:		2013-4-19   12:53
*	filename: 		SystemScript
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\systemscript.h"
//------------------------------------------------------------------------
CSystemScript::CSystemScript(void)
{
	m_pScriptObject = NULL;
}
//------------------------------------------------------------------------
CSystemScript::~CSystemScript(void)
{
}
//------------------------------------------------------------------------
BOOL CSystemScript::Init( CScriptObject * pScriptObject )
{
	this->m_pScriptObject = pScriptObject;
	return TRUE;
}
//------------------------------------------------------------------------