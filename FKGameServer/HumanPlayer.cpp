/**
*	created:		2013-4-19   15:01
*	filename: 		HumanPlayer
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "ScriptVariable.h"
#include "HumanPlayer.h"
//------------------------------------------------------------------------
// 获取脚本记录值
const char* CHumanPlayer::GetScriptVarValue( const char * pszName )
{
	GetVariableStruct var;
	if( CScriptVariableManager::GetInstance()->GetVariable( pszName, this, var ) )
	{
		if( var.nType == 0 )
		{
			sprintf( m_szTempScriptVarValue, "%u", var.nValue );
			return m_szTempScriptVarValue;
		}
		else
			return var.pszValue;
	}
	else
		return "";
}
//------------------------------------------------------------------------