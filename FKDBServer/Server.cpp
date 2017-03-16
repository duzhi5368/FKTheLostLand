/**
*	created:		2013-4-15   23:24
*	filename: 		Server
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\server.h"
#include "odbcdatabase.h"
#include "time.h"
#include "FKDBServerDefine.h"
//------------------------------------------------------------------------
CServer *CServer::m_pInstance = NULL;
//------------------------------------------------------------------------
CServer::CServer(void)
{
	m_pInstance = this;
	strcpy( m_szServer, "(local)" );
	strcpy( m_szDatabase, "FKGameDB" );
	strcpy( m_szAccount, "root" );
	strcpy( m_szPassword, "123456" );
	strcpy( m_szWebDatabase, "WebDB" );
	memset( m_dwMsgTimes, 0, sizeof( m_dwMsgTimes ) );
}
//------------------------------------------------------------------------
CServer::~CServer(void)
{

}
//------------------------------------------------------------------------
CClientObject * CServer::NewClientObject()
{
	CClientObj * pObj = newObject();
	if( pObj->GetAppDB().OpenDataBase( m_szServer, m_szDatabase, m_szAccount, m_szPassword ) != SE_OK )
	{
		m_pIoConsole->OutPut( RGB(255,0,0), "无法连接数据库，请检查服务器是否开启!\n" );
		deleteObject( pObj );
		return NULL;
	}
	return pObj;
}
//------------------------------------------------------------------------
VOID CServer::DeleteClientObject( CClientObject * pObject )
{
	deleteObject((CClientObj*)pObject );
}
//------------------------------------------------------------------------
// 初始化数据库
BOOL CServer::InitServer(CSettingFile&s)
{
	int maxconnection = s.GetInteger( m_pServerName, "数据库最大连接数", MAX_CLIENTOBJECT );
	create( maxconnection );
	CBaseServer::GetIoConsole()->OutPut( 0xff00, "数据库最大连接数 %d...\n", maxconnection );

	srand( time(NULL));
	char * pszServer = (char*)s.GetString( m_pServerName, "数据库服务器名", "(local)" );
	char * pszDatabase = (char*)s.GetString( m_pServerName, "基本数据库名", "FKGameDB" );
	char * szAccount = (char*)s.GetString( m_pServerName, "数据库账号", "root" );
	char * szPassword = (char*)s.GetString( m_pServerName, "数据库密码", "123456" );
	char * pszWebDatabase = (char*)s.GetString( m_pServerName, "WEB数据库名", "WebDB" );

	strncpy( m_szServer, pszServer, 63 );
	strncpy( m_szDatabase, pszDatabase, 63 );
	strncpy( m_szAccount, szAccount, 63 );
	strncpy( m_szPassword, szPassword, 63 );
	strncpy( m_szWebDatabase, pszWebDatabase, 63 );

	CBaseServer::GetIoConsole()->OutPut( 0xff00, "尝试连接数据库 SV=%s : DB=%s : ID=%s : PW=%s \n",
		pszServer, pszDatabase, szAccount, szPassword );

	// 基本数据库
	if( m_appDB.OpenDataBase( pszServer, pszDatabase, szAccount, szPassword ) != SE_OK )
	{
		m_pIoConsole->OutPut( RGB(255,0,0), "无法连接数据库，请检查服务器是否开启!\n" );
		return FALSE;
	}
	else
	{
		m_pIoConsole->OutPut( RGB(0,255,0), "连接数据库成功!\n" );
	}

	m_appDB.DoInit();
	m_xxShowTimer.Savetime();

	// Web数据库
	if( m_appDB.OpenWebDB( pszServer, pszWebDatabase, szAccount, szPassword ) != SE_OK )
	{
		m_pIoConsole->OutPut( RGB(255,0,0), "无法连接Web数据库 %s，请检查服务器是否开启!\n", pszWebDatabase );
		return FALSE;
	}
	else
	{
		m_pIoConsole->OutPut( RGB(0,255,0), "连接Web数据库成功!\n" );
	}

	return TRUE;
}
//------------------------------------------------------------------------
VOID CServer::CleanServer()
{

}
//------------------------------------------------------------------------
VOID CServer::Update()
{
	CClientObj * pObject = m_ObjectPool.First();
	while( pObject )
	{
		pObject->Update();
		pObject = m_ObjectPool.Next();
	}
	
	UpdateSCServer();
}
//------------------------------------------------------------------------
VOID CServer::OnParseMsg( WORD wMsg )
{
	if( wMsg >= DM_START && wMsg < DM_END )
	{
		this->m_dwMsgTimes[wMsg]++;
	}
}
//------------------------------------------------------------------------