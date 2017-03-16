/**
*	created:		2013-4-15   23:35
*	filename: 		AppDB
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\appdb.h"
#include "odbcdatabase.h"
#include "server.h"
#include "time.h"
//------------------------------------------------------------------------
CAppDB::CAppDB(void)
{
	m_pDatabase = NULL;
	m_pDBConnection = NULL;

	m_pWebDB = NULL;
	m_pWebDBConnection = NULL;
}
//------------------------------------------------------------------------
CAppDB::~CAppDB(void)
{
	if( m_pDBConnection != NULL )
		m_pDatabase->DelConnection(m_pDBConnection);
	if( m_pDatabase != NULL )
	{
		m_pDatabase->UnInit();
		delete m_pDatabase;
	}

	if( NULL != m_pWebDBConnection && NULL != m_pWebDB)
	{
		m_pWebDB->DelConnection(m_pWebDBConnection);

		m_pWebDB->UnInit();
		delete m_pWebDB;
	}
}
//------------------------------------------------------------------------
SERVER_ERROR CAppDB::OpenDataBase( const char * pszServer, const char * pszDBName, const char * pszId, const char * pszPassword )
{
	SERVER_ERROR	ret = SE_OK;
	m_pDatabase = new CODBCDatabase;
	if( m_pDatabase == NULL )return SE_ALLOCMEMORYFAIL;
	ret = m_pDatabase->Init();
	if( ret != SE_OK )
		return ret;
	m_pDBConnection = m_pDatabase->GetConnection();
	if( m_pDBConnection == NULL )
		return SE_ALLOCMEMORYFAIL;
	ret = m_pDBConnection->Connect( pszServer, pszDBName, pszId, pszPassword );
	if( ret != SE_OK )
		return ret;
	return SE_OK;
}
//------------------------------------------------------------------------
//web
SERVER_ERROR CAppDB::OpenWebDB( const char * pszServer, const char * pszDBName, const char * pszId, const char * pszPassword )
{
	SERVER_ERROR	ret = SE_OK;
	m_pWebDB = new CODBCDatabase;
	if( m_pWebDB == NULL )return SE_ALLOCMEMORYFAIL;
	ret = m_pWebDB->Init();
	if( ret != SE_OK )
		return ret;
	m_pWebDBConnection = m_pWebDB->GetConnection();
	if( m_pWebDBConnection == NULL )
		return SE_ALLOCMEMORYFAIL;
	ret = m_pWebDBConnection->Connect( pszServer, pszDBName, pszId, pszPassword );
	if( ret != SE_OK )
		return ret;
	return SE_OK;	
}
//------------------------------------------------------------------------
// ≥ı ºªØ
VOID CAppDB::DoInit()
{

}
//------------------------------------------------------------------------
VOID CAppDB::Test()
{
	GetTickCount();
}
//------------------------------------------------------------------------