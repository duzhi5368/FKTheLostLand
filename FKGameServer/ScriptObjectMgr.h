/**
*	created:		2013-4-19   9:42
*	filename: 		ScriptObjectMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "findfile.h"
//------------------------------------------------------------------------
class CScriptObject;
//------------------------------------------------------------------------
#define	FINDFILE_SCRIPT	0
#define	FINDFILE_DEFINE	1
//------------------------------------------------------------------------
class CScriptObjectMgr :
	public CFindFile,
	public xVariableProvider
{
public:
	CScriptObjectMgr(void);
	virtual ~CScriptObjectMgr(void);
	VOID	Load( const char * pszPath );
	VOID	OnFoundFile( const char * pszFilename, UINT nParam = 0 );
	char *	GetVariableValue( const char * pszVariable );
public:
	static CScriptObjectMgr * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CScriptObjectMgr;
		return m_pInstance;
	}

	CScriptObject * GetScriptObject( const char * pszName )
	{
		return (CScriptObject*)m_xScriptList.ObjectOf( pszName );
	}
private:
	VOID LoadScript( const char * pszFileName );
	VOID LoadDefine( const char * pszFileName );
	xStringList<512> m_xScriptList;
	xVarList<256>	m_xDefineVarList;
	static CScriptObjectMgr * m_pInstance;
};
//------------------------------------------------------------------------