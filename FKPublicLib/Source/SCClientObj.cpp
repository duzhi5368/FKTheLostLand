/**
*	created:		2013-4-16   5:32
*	filename: 		SCClientObj
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/scclientobj.h"
//------------------------------------------------------------------------
CSCClientObj::CSCClientObj(void)
{
	Clean();
}
//------------------------------------------------------------------------
CSCClientObj::~CSCClientObj(void)
{
}
//------------------------------------------------------------------------
void CSCClientObj::Update()
{
	if( this == NULL )return;
	CClientObject::Update();
}
//------------------------------------------------------------------------
VOID CSCClientObj::RegisterServer( SERVERADDR & Addr, ServerId & Id, const char * pszNickName )
{
	if( this == NULL )return;
	REGISTER_SERVER_INFO	info;
	info.addr = Addr;
	info.Id = Id;
	strncpy( info.szName, pszNickName, 64 );

	SendMsg(0,SCM_REGISTERSERVER,0,0,0,&info, sizeof(info));
}
//------------------------------------------------------------------------
VOID CSCClientObj::UpdateInfo( DWORD dwConnections )
{
	if( this == NULL )return;
	SendMsg( dwConnections, SCM_UPDATESERVERINFO, 0, 0, 0, NULL, 0 );
}
//------------------------------------------------------------------------
VOID CSCClientObj::FindServer( UINT id,  servertype type, const char * pszServerName )
{
	if( this == NULL )return;
	SendMsg( id, SCM_FINDSERVER, (WORD)type, 0, 0,(LPVOID) pszServerName, (int)strlen( pszServerName ));
}
//------------------------------------------------------------------------
VOID CSCClientObj::SendMsgAcrossServer( UINT id,  WORD wCmd, MAS_SENDTYPE sendtype, WORD wParam,char * pszData, int datasize )
{
	if( this == NULL )return;
	SendMsg( id, SCM_MSGACROSSSERVER, wCmd, (WORD)sendtype, wParam, (LPVOID)pszData, datasize );
}
//------------------------------------------------------------------------
VOID CSCClientObj::GetGameServerAddr( UINT id, const char * pszServerName, const char * pszMapInfo )
{
	if( this == NULL )return;
	SendMsg( id, SCM_GETGAMESERVERADDR, 0, 0, 0, (LPVOID)pszServerName );
}
//------------------------------------------------------------------------
VOID CSCClientObj::GetGsList( UINT id )
{
	if( this == NULL )return;
	SendMsg( id, SCM_MSGGSNAMELIST, 0, 0, 0);
}
//------------------------------------------------------------------------