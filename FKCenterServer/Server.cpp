/**
*	created:		2013-4-15   22:32
*	filename: 		Server
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\server.h"
//------------------------------------------------------------------------
CServer::CServer(void)
{
}
//------------------------------------------------------------------------
CServer::~CServer(void)
{
}
//------------------------------------------------------------------------
BOOL CServer::InitServer(CSettingFile&s)
{
	int maxconnection = s.GetInteger( m_pServerName, "最大连接数", MAX_CLIENTOBJECT );
	create( maxconnection );
	CBaseServer::GetIoConsole()->OutPut( 0xff00, "最大连接数 %d!\n", maxconnection );
	return TRUE;
}
//------------------------------------------------------------------------
VOID CServer::Update()
{
	CClientObj * pObj = m_ObjectPool.First();
	while( pObj )
	{
		pObj->Update();
		pObj = m_ObjectPool.Next();
	}
	//	中心服务器无需更新
	//	DB服务器无需更新
}
//------------------------------------------------------------------------
CClientObject * CServer::NewClientObject()
{
	return newObject();
}
//------------------------------------------------------------------------
VOID CServer::DeleteClientObject( CClientObject * pObject )
{
	UnRegisterServer( (CClientObj*)pObject );
	deleteObject((CClientObj*)pObject);
}
//------------------------------------------------------------------------
VOID CServer::CleanServer()
{
}
//------------------------------------------------------------------------
BOOL	CheckType( int type )
{
	if( type <= ST_UNKNOWN || type > ST_GAMESERVER )
		return FALSE;
	return TRUE;
}
//------------------------------------------------------------------------
SERVER_ERROR CServer::RegisterServer( CClientObj * pObj, REGISTER_SERVER_INFO * pInfo, REGISTER_SERVER_RESULT * pResult )
{
	int type = pInfo->Id.bType;
	if( !CheckType( type ) )
		return SE_INVALIDPARAM;
	m_pIoConsole->OutPut( RGB(0,255,0), "%s %s|%s:%u 注册到服务器中心.\n", GetServerTypeNameByType( (servertype)pInfo->Id.bType), pInfo->szName,
							pInfo->addr.addr, pInfo->addr.nPort  );

	UINT	id = pObj->getId();

	if( !m_ServerArrays[type-1].AddId(id))
		return SE_SERVERFULL;
	REGISTEREDSERVER	*	pRegInfo = pObj->GetRegInfo();

	pRegInfo->Ident = pInfo->Id;
	pRegInfo->Addr = pInfo->addr;
	memcpy( pRegInfo->szName, pInfo->szName, 64 );
	pRegInfo->dwConnections = 0;
	pRegInfo->Ident.bIndex = (BYTE)id;
	
	memset( pResult, 0, sizeof( *pResult ));

	pResult->Id = pRegInfo->Ident;

	if( type != ST_DATABASESERVER )
	{
		if( type == ST_GAMESERVER )
		{
			pResult->nDbCount = PrepareServer( ST_DATABASESERVER, 2, pResult->DbAddr );
		}
		else
			pResult->nDbCount = PrepareServer( ST_DATABASESERVER, 1, pResult->DbAddr );
		pRegInfo->iSendDBCount = pResult->nDbCount;
	}
	else
	{
		//	发送给DBSvr
		SERVERADDR	addr[2];
		int icount = PrepareServer( ST_DATABASESERVER, 2, addr );
		if( icount == 2 )
		{
			SendDBServer(addr,icount);
		}
	}


	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CServer::UnRegisterServer( CClientObj * pObj )
{
	REGISTEREDSERVER * pInfo = pObj->GetRegInfo();
	if( pInfo->Ident.dwId == 0 )
		return SE_NOTINITLIZED;
	int type = pInfo->Ident.bType;
	if( type <= ST_UNKNOWN || type > ST_GAMESERVER )
		return SE_INVALIDPARAM;
	m_pIoConsole->OutPut( RGB(0,255,0), "%s:%s|%s:%u 从服务器中心注销.\n",GetServerTypeNameByType( (servertype)pInfo->Ident.bType), 
		pInfo->szName,
		pInfo->Addr.addr, pInfo->Addr.nPort );

	m_ServerArrays[type-1].DelId( pObj->getId());
	return SE_OK;
}
//------------------------------------------------------------------------
//找服务器， 通过config.ini的type, name
SERVER_ERROR CServer::FindServer( servertype type, const char * pszName, FINDSERVER_RESULT * pResult )
{
	if( type <= ST_UNKNOWN||type>ST_GAMESERVER )return SE_INVALIDPARAM;
	int i = 0;
	SERVERARRAY	*	pArray = &m_ServerArrays[type-1];
	REGISTEREDSERVER	*	pInfo = NULL;
	for( i = 0;i < pArray->count;i++)
	{
		CClientObj * pObj = (CClientObj *)getObject(pArray->Ids[i]);
		if( pObj != NULL )
		{
			pInfo = pObj->GetRegInfo();
			if( pInfo && strcmp( pszName, pInfo->szName ) == 0 )
			{
				pResult->addr = pInfo->Addr;
				pResult->Id = pInfo->Ident;
				return SE_OK;
			}
		}
	}
	return SE_SERVERNOTFOUND;
}
//------------------------------------------------------------------------
SERVER_ERROR		CServer::GetGameServerName(string& namelist)
{
	int i = 0;
	SERVERARRAY	*	pArray = &m_ServerArrays[ST_GAMESERVER-1];
	REGISTEREDSERVER	*	pInfo = NULL;
	for( i = 0;i < pArray->count;i++)
	{
		CClientObj * pObj = (CClientObj *)getObject(pArray->Ids[i]);
		if( pObj != NULL )
		{
			pInfo = pObj->GetRegInfo();
			if( pInfo )
			{
				namelist.append(pInfo->szName);
				namelist.append("/");
			}
		}
	}
	return SE_OK;
}
//------------------------------------------------------------------------
VOID		CServer::OnInput( const char * pszString )
{
	CBaseServer::OnInput(pszString);

	if (strcmp(pszString,"GetGSList") == 0)
	{
		string namelist;
		GetGameServerName(namelist);
		m_pIoConsole->OutPut( RGB(0,255,0), "游戏服务器列表：%s\n",namelist.c_str());
		return;
	}

	m_pIoConsole->OutPut( 0xff00, "无法识别的命令: %s\n", pszString );

	OutputCmdList();
}
//------------------------------------------------------------------------
int CServer::PrepareServer( int type, int count, SERVERADDR * pAddrArray )
{
	SERVERARRAY	*	pArray = &m_ServerArrays[type-1];
	if( pArray->count == 0 )
		return 0;
	int i;
	for( i = 0;i < count;i ++ )
	{
		if( pArray->pickptr < 0 || pArray->pickptr >= pArray->count )pArray->pickptr = 0;
		UINT id = pArray->Ids[pArray->pickptr];
		CClientObj * pObj = (CClientObj*)GetClientObject(id);
		if( pObj )
		{
			pAddrArray[i] = pObj->GetRegInfo()->Addr;
		}
		pArray->pickptr++;
	}
	return i;
}
//------------------------------------------------------------------------
VOID CServer::SendDBServer( SERVERADDR * pAddr, int count )
{
	REGISTER_SERVER_RESULT result;
	if( count<= 0 )return;
	result.DbAddr[0] = *pAddr;
	result.DbAddr[1] = *(pAddr+1);
	CClientObj * pObj = m_ObjectPool.First();
	while( pObj )
	{
		if( pObj->GetRegInfo()->Ident.bType != ST_UNKNOWN && pObj->GetRegInfo()->Ident.bType != ST_DATABASESERVER &&
			pObj->GetRegInfo()->iSendDBCount == 0 )
		{
			result.Id = pObj->GetRegInfo()->Ident;

			if( pObj->GetRegInfo()->Ident.bType == ST_GAMESERVER )
				result.nDbCount = count;
			else
				result.nDbCount = 1;
			pObj->GetRegInfo()->iSendDBCount = result.nDbCount;
			pObj->SendMsg( 0, SCM_REGISTERSERVER, SE_OK, 0, 0, &result, sizeof( result ) );
		}
		pObj = m_ObjectPool.Next();
	}
}
//------------------------------------------------------------------------
// 输出命令表
VOID CServer::OutputCmdList()
{
	m_pIoConsole->OutPut( 0xff00,	"=============================\n" );
	m_pIoConsole->OutPut( 0xff00,	"\t当前服务器支持的命令表如下\n" );
	m_pIoConsole->OutPut( 0xff00,	"=============================\n" );
	m_pIoConsole->OutPut( 0xff,		"命令：GetGSList\n" );
	m_pIoConsole->OutPut( 0xffff,	"\t参数：无\n" );
	m_pIoConsole->OutPut( 0xffff,	"\t说明：游戏服务器列表\n" );
}
//------------------------------------------------------------------------