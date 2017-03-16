/**
*	created:		2013-4-19   9:43
*	filename: 		ScriptObjectMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptobjectmgr.h"
#include "scriptobject.h"
//------------------------------------------------------------------------
CScriptObjectMgr * CScriptObjectMgr::m_pInstance = NULL;
//------------------------------------------------------------------------
CScriptObjectMgr::CScriptObjectMgr(void) : m_xScriptList( TRUE )
{
	if( m_pInstance == NULL )
		m_pInstance = this;
}
//------------------------------------------------------------------------
CScriptObjectMgr::~CScriptObjectMgr(void)
{
}
//------------------------------------------------------------------------
VOID	CScriptObjectMgr::Load( const char * pszPath )
{
	StartFind( pszPath, "*.txt", TRUE, FINDFILE_SCRIPT );
	StartFind( pszPath, "*.def", TRUE, FINDFILE_DEFINE );
}
//------------------------------------------------------------------------
VOID	CScriptObjectMgr::OnFoundFile( const char * pszFilename, UINT nParam )
{
	if( nParam == FINDFILE_DEFINE )
	{
		LoadDefine( pszFilename );
	}
	else if( nParam == FINDFILE_SCRIPT )
	{
		LoadScript( pszFilename );
	}
}
//------------------------------------------------------------------------
char * CScriptObjectMgr::GetVariableValue( const char * pszVariable )
{
	//	查找本地变量集合
	char * p = m_xDefineVarList.GetVarValue( pszVariable );
	//	如果找到，返回结果。
	if( p )return p;
	//	找不到的话，直接返回基类的结果
	return xVariableProvider::GetVariableValue( pszVariable );
}
//------------------------------------------------------------------------
VOID CScriptObjectMgr::LoadScript( const char * pszFileName )
{
	CScriptObject * pObject = new CScriptObject;
	if( pObject->Load( pszFileName ) )
	{
		m_xScriptList.Add( pObject->getName(), (LPVOID)pObject );
	}
	else
		delete pObject;
}
//------------------------------------------------------------------------
VOID CScriptObjectMgr::LoadDefine( const char * pszFileName )
{
	CStringFile sf( pszFileName );
	for( int i = 0;i < sf.GetLineCount();i ++ )
	{
		xStringsExtracter<3> define( sf[i], " \t", " \t\"" );
		if( define.getCount() == 2 || define.getCount() == 3 )
		{
			if( stricmp( define[0], "#define" ) == 0 )
			{
				char * pValue = NULL;
				if( (pValue = this->m_xDefineVarList.GetVarValue( define[1] )) != NULL )
				{
					PRINT( 0xff, "发现重定义在 %s 文件的 %u 行: %s 已经定义过值 [%s]\n", pszFileName, i + 1, define[1], pValue );
				}
				else
				{
					m_xDefineVarList.AddVar( define[1], define[2] );
				}
			}
		}
	}
}
//------------------------------------------------------------------------