/**
*	created:		2013-4-14   21:02
*	filename: 		Server
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "Server.h"
#include "FKLoginServerDefine.h"
//------------------------------------------------------------------------
CServer *CServer::m_pInstance = NULL;
//------------------------------------------------------------------------
CServer::CServer(void)
{
	m_pInstance = this;
	m_bDisableRegister = FALSE;
	m_pszServerTips = NULL;
	m_pszLoginOkTips = NULL;
	m_pszRegisterTips = NULL;
}
//------------------------------------------------------------------------
CServer::~CServer(void)
{
}
//------------------------------------------------------------------------
CClientObject * CServer::NewClientObject()
{
	return newObject();
}
//------------------------------------------------------------------------
VOID CServer::DeleteClientObject( CClientObject * pObject )
{
	deleteObject( (CClientObj *)pObject );
}
//------------------------------------------------------------------------
BOOL CServer::InitServer(CSettingFile&s)
{
	int	t = s.GetInteger( m_pServerName, "disableregister" );

	if( t == 0 )
	{
		CBaseServer::GetIoConsole()->OutPut( 0xff00, "允许注册新帐号!\n" );
		m_bDisableRegister = FALSE;
	}
	else
	{
		CBaseServer::GetIoConsole()->OutPut( 0xff00, "禁止注册新帐号!\n" );
		m_bDisableRegister = TRUE;
	}

	int maxconnection = s.GetInteger( m_pServerName, "maxconnection", MAX_CLIENTOBJECT );
	create( maxconnection );
	CBaseServer::GetIoConsole()->OutPut( 0xff00, "最大连接数 %d!\n", maxconnection );

	m_pszServerTips = (char*)LoadFile( ".\\data\\usertip.txt" );
	m_pszLoginOkTips = (char*)LoadFile( ".\\data\\logintip.txt" );
	m_pszRegisterTips = (char*)LoadFile( ".\\data\\registertip.txt" );
	
	return TRUE;
}
//------------------------------------------------------------------------
VOID CServer::CleanServer()
{
	m_bDisableRegister = FALSE;

}
//------------------------------------------------------------------------
static int test = 0;
VOID CServer::Update()
{
	CClientObj * pObject = m_ObjectPool.First();
	while( pObject )
	{
		pObject->Update();
		pObject = m_ObjectPool.Next();
	}
	
	UpdateSCServer();
	UpdateDBServer();
}
//------------------------------------------------------------------------
VOID CServer::OnInput( const char * pszString )
{
	CBaseServer::OnInput(pszString);

	if (strcmp(pszString,"getgslist") == 0)
	{
		
	}
}
//------------------------------------------------------------------------
VOID CServer::OnSCMsg( PMIRMSG pMsg, int datasize )
{
	CBaseServer::OnSCMsg(pMsg, datasize);
}
//------------------------------------------------------------------------