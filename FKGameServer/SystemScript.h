/**
*	created:		2013-4-19   12:53
*	filename: 		SystemScript
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "scriptshell.h"
//------------------------------------------------------------------------
class CSystemScript :
	public CScriptShell,
	public xSingletonClass<CSystemScript>
{
public:
	CSystemScript(void);
	virtual ~CSystemScript(void);
	BOOL Init( CScriptObject * pScriptObject );
};
//------------------------------------------------------------------------