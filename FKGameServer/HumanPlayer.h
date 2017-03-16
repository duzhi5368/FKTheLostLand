/**
*	created:		2013-4-19   9:24
*	filename: 		HumanPlayer
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "AliveObject.h"
#include "ScriptTarget.h"
//------------------------------------------------------------------------
class CHumanPlayer :
	public CAliveObject
{
public:
	CHumanPlayer(){}
	virtual ~CHumanPlayer(){}
public:
	// 保存角色信息到本包内
	bool	UpdateToDB(){ return true; };
	// 保存角色的全部信息到本包内
	VOID	GetDBInfoPacket( xPacket & packet ){};
	// 记录部分参数
	VOID	SaveVars(){};
	// 读取部分参数
	VOID	LoadVars(){};
	// 获取角色DB_Id
	DWORD	GetDBId(){  return m_dwDBId;}

	virtual CScriptTargetForPlayer* GetScriptTarget(){ return &m_ScriptTarget;}
public:
	// 获取角色名称
	const char *	GetName(){  return ""; }
	// 获取脚本记录值
	const char*		GetScriptVarValue( const char * pszName );
private:
	CScriptTargetForPlayer	m_ScriptTarget;
	UINT					m_dwDBId;
	char					m_szTempScriptVarValue[256];
};
//------------------------------------------------------------------------