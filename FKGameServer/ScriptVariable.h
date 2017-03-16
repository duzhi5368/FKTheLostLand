/**
*	created:		2013-4-19   14:00
*	filename: 		ScriptVariable
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "findfile.h"
//------------------------------------------------------------------------
class CVariableFile
{
public:
	CVariableFile();
	~CVariableFile();
	BOOL			Load( const char * pszFilename );
	BOOL			Reload();
	BOOL			Save();
	VOID			Clear();
	const char *	GetVariableValue( const char * pszName );
	VOID			SetVariableValue( const char * pszName, const char * pszValue );
	VOID			DelVariable( const char * pszName );

	void			SetName( const char * pszName ){ o_strncpy( m_szName, pszName, 60 );}
	const char *	GetName(){ return m_szName;}
	const char *	GetFileName(){ return m_pFilename;}
protected:
	BOOL	m_bModified;
	char	*	m_pFilename;
	char	m_szName[64];
	xVarList<32> m_xVarList;
};
//------------------------------------------------------------------------
class CScriptVariableManager :
	public xSingletonClass<CScriptVariableManager>,
	public CFindFile
{
public:
	CScriptVariableManager();
	BOOL			AddVariable( const char * pszName, fnGetVariable fnGet );
	BOOL			GetVariable( const char * pszName, CHumanPlayer * pPlayer, GetVariableStruct & var );
	char *			GetStringCache(){ if(m_nCachePtr >= 256)m_nCachePtr = 0; return m_xStringCache[m_nCachePtr++].szString;}
	CVariableFile * NewVariableFile();
	VOID			DeleteVariableFile( CVariableFile * pFile );
	BOOL			SetVariable( const char * pszName, const char * pszVarName, const char * pszValue );
	const char *	GetVariable( const char * pszName, const char * pszVarName );
	VOID			DelVariable( const char * pszName, const char * pszVarName );
protected:
	VOID			OnFoundFile( const char * pszFilename, UINT nParam = 0 );
protected:
	xStringList<256> m_xVarList;
	StringCacheNode m_xStringCache[256];
	UINT	m_nCachePtr;
	xStringList<32> m_xVarGroupList;
	xObjectPool<CVariableFile> m_xVarGroupPool;
};
//------------------------------------------------------------------------
class CVariableRegisterAgent
{
public:
	CVariableRegisterAgent( const char * pszName, fnGetVariable fnGet );
};
//------------------------------------------------------------------------
#define	DEFINE_SCRIPT_VAR( name )	BOOL	VAR_##name( const char * , GetVariableStruct &, CHumanPlayer * );\
													CVariableRegisterAgent VarRegAgent_##name( #name, VAR_##name );\
													BOOL VAR_##name( const char * pszName, GetVariableStruct & result, CHumanPlayer * pPlayer ){

#define	END_SCRIPT_VAR				return TRUE;}
//------------------------------------------------------------------------