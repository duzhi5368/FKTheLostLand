/**
*	created:		2013-4-19   14:02
*	filename: 		ScriptVariable
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptvariable.h"
//------------------------------------------------------------------------
CVariableFile::CVariableFile()
{
	m_bModified = FALSE;
	m_pFilename = NULL;
	m_szName[0] = 0;
}
//------------------------------------------------------------------------
CVariableFile::~CVariableFile()
{
	m_xVarList.ClearVars();
}
//------------------------------------------------------------------------
BOOL	CVariableFile::Load( const char * pszFilename )
{
	CStringFile sf( pszFilename );
	char * pLine = NULL;
	for( UINT i = 0;i < (UINT)sf.GetLineCount();i ++ )
	{
		pLine = TrimEx(sf[i]);
		if( *pLine == 0 || *pLine == '#' )continue;
		xStringsExtracter<2> val( pLine, "=", " \t\"" );
		if( val.getCount() == 0 )continue;
		if( val.getCount() > 1 )
			m_xVarList.AddVar( val[0], val[1] );
		else
			m_xVarList.AddVar( val[0], "" );
	}
	if( this->m_pFilename )delete []m_pFilename;
	m_pFilename = copystring( pszFilename );
	_splitpath( m_pFilename, NULL, NULL, m_szName, NULL );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CVariableFile::Reload()
{
	if( m_pFilename == NULL )return FALSE;
	m_xVarList.ClearVars();
	CStringFile sf( m_pFilename );
	char * pLine = NULL;
	for( UINT i = 0;i < (UINT)sf.GetLineCount();i ++ )
	{
		pLine = TrimEx(sf[i]);
		if( *pLine == 0 || *pLine == '#' )continue;
		xStringsExtracter<2> val( pLine, "=", " \t\"" );
		if( val.getCount() == 0 )continue;
		if( val.getCount() > 1 )
			m_xVarList.AddVar( val[0], val[1] );
		else
			m_xVarList.AddVar( val[0], "" );
	}
	return TRUE;
}
//------------------------------------------------------------------------
static char g_szFilename[1024];
//------------------------------------------------------------------------
BOOL	CVariableFile::Save()
{
	if( m_pFilename == NULL )
	{ 
		if( m_szName[0] == 0 )return FALSE;
		sprintf( g_szFilename, "%s.txt", m_szName );
		m_pFilename = copystring( g_szFilename );
	}
	FILE * fp = fopen( m_pFilename, "w" );
	if( fp == NULL )return FALSE;
	xStringList<32> * p = m_xVarList.GetList();
	for( UINT n = 0;n < p->GetCount();n ++ )
	{
		xVarList<32>::Variable * var = (xVarList<32>::Variable *)(*p)[n]->lpObject;
		char * pVal =var->pszValue;
		if( pVal == NULL )
			pVal = "";
		fprintf( fp, "%s = \"%s\"\n", (*p)[n]->pszString, pVal );
	}
	fclose( fp );
	return TRUE;
}
//------------------------------------------------------------------------
const char * CVariableFile::GetVariableValue( const char * pszName )
{
	return this->m_xVarList.GetVarValue( pszName );
}
//------------------------------------------------------------------------
VOID	CVariableFile::SetVariableValue( const char * pszName, const char * pszValue )
{
	this->m_xVarList.AddVar( pszName, (char*)pszValue );
}
//------------------------------------------------------------------------
VOID	CVariableFile::DelVariable( const char * pszName )
{
	this->m_xVarList.DelVar( pszName );
}
//------------------------------------------------------------------------
VOID CVariableFile::Clear()
{
	this->m_xVarList.ClearVars();
}
//------------------------------------------------------------------------
CVariableRegisterAgent::CVariableRegisterAgent( const char * pszName, fnGetVariable fnGet )
{
	if( !CScriptVariableManager::GetInstance()->AddVariable( pszName, fnGet ) )
	{
		PRINT( 0xff, "×¢²á±äÁ¿º¯Êý %s Ê§°Ü£¡\n", pszName );
	}
}
//------------------------------------------------------------------------
CScriptVariableManager::CScriptVariableManager(): m_xVarList( TRUE )
{
	m_nCachePtr = 0;
}
//------------------------------------------------------------------------
BOOL	CScriptVariableManager::AddVariable( const char * pszName, fnGetVariable fnGet )
{
	if( this->m_xVarList.Add( pszName, (LPVOID)fnGet ) == -1 )return FALSE;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CScriptVariableManager::GetVariable( const char * pszName, CHumanPlayer * pPlayer, GetVariableStruct & var )
{
	fnGetVariable fnGet = (fnGetVariable)m_xVarList.ObjectOf( pszName );
	if( fnGet )return fnGet( pszName, var, pPlayer );
	return FALSE;
}
//------------------------------------------------------------------------
VOID CScriptVariableManager::OnFoundFile( const char * pszFilename, UINT nParam )
{
	CVariableFile * pFile = NewVariableFile();
	if( pFile == NULL )return;
	if( !pFile->Load( pszFilename ) )
	{
		DeleteVariableFile( pFile );
		return;
	}
	if( this->m_xVarGroupList.Add( pFile->GetName(), (LPVOID)pFile ) == -1 )
	{
		DeleteVariableFile( pFile );
		return;
	}
}
//------------------------------------------------------------------------
CVariableFile * CScriptVariableManager::NewVariableFile()
{
	return this->m_xVarGroupPool.newObject();
}
//------------------------------------------------------------------------
VOID CScriptVariableManager::DeleteVariableFile( CVariableFile * pFile )
{
	pFile->Clear();
	this->m_xVarGroupPool.deleteObject( pFile );
}
//------------------------------------------------------------------------
BOOL	CScriptVariableManager::SetVariable( const char * pszName, const char * pszVarName, const char * pszValue )
{
	CVariableFile * pFile = (CVariableFile *)m_xVarGroupList.ObjectOf( pszName );
	if( pFile == NULL )
	{
		pFile = NewVariableFile();
		if( pFile == NULL )return FALSE;
		pFile->SetName( pszName );
		if( this->m_xVarGroupList.Add( pFile->GetName(), (LPVOID)pFile ) == -1 )
		{
			DeleteVariableFile( pFile );
			return FALSE;
		}
	}
	pFile->SetVariableValue( pszVarName, pszValue );
	pFile->Save();
	return TRUE;
}
//------------------------------------------------------------------------
const char * CScriptVariableManager::GetVariable( const char * pszName, const char * pszVarName )
{
	CVariableFile * pFile = (CVariableFile *)m_xVarGroupList.ObjectOf( pszName );
	if( pFile == NULL )return NULL;
	return pFile->GetVariableValue( pszVarName );
}
//------------------------------------------------------------------------
VOID	CScriptVariableManager::DelVariable( const char * pszName, const char * pszVarName )
{
	CVariableFile * pFile = (CVariableFile *)m_xVarGroupList.ObjectOf( pszName );
	if( pFile == NULL )return;
	pFile->DelVariable( pszVarName );
}
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( YEAR ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	result.SetValue((UINT)st.wYear);
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( MONTH ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	result.SetValue((UINT)st.wMonth);
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( DAY ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	result.SetValue((UINT)st.wDay);
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( HOUR ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	result.SetValue((UINT)st.wHour);
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( MINUTE ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	result.SetValue((UINT)st.wMinute);
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( SECOND ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	result.SetValue((UINT)st.wSecond);
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( SERVERDATETIME ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	char * p = CScriptVariableManager::GetInstance()->GetStringCache();
	sprintf( p, "%04u-%02u-%02u %02u:%02u:%02u", 
		st.wYear, st.wMonth, st.wDay, 
		st.wHour, st.wMinute, st.wSecond );
	result.SetValue( p );
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( SERVERDATE ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	char * p = CScriptVariableManager::GetInstance()->GetStringCache();
	sprintf( p, "%04u-%02u-%02u", 
		st.wYear, st.wMonth, st.wDay );
	result.SetValue( p );
}END_SCRIPT_VAR
//------------------------------------------------------------------------
DEFINE_SCRIPT_VAR( SERVERTIME ){
	SYSTEMTIME	st;
	GetLocalTime( &st );
	char * p = CScriptVariableManager::GetInstance()->GetStringCache();
	sprintf( p, "%02u:%02u:%02u", 
		st.wHour, st.wMinute, st.wSecond );
	result.SetValue( p );
}END_SCRIPT_VAR
//------------------------------------------------------------------------