/**
*	created:		2013-4-18   1:27
*	filename: 		CodeMsgFunc
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "CenterServerCodeMsgParser.h"
//------------------------------------------------------------------------
#define CODE_MSG_COMMON  if( pObject == NULL ) return false;\
		CServer * pServer = CServer::GetInstance();
//------------------------------------------------------------------------
bool CCodeMsgFunc::OnMsg_GetGameSvrAddr( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	CODE_MSG_COMMON;
	pMsg->wParam[0] = pServer->FindServer( ST_GAMESERVER, pMsg->data, (FINDSERVER_RESULT*)pMsg->data );
	if( pMsg->wParam[0] == SE_OK )
		datasize = sizeof( FINDSERVER_RESULT );
	pObject->SendMsg(pMsg, datasize);
	return true;
}
//------------------------------------------------------------------------
bool CCodeMsgFunc::OnMsg_RegisterSvr( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	CODE_MSG_COMMON;
	pMsg->wParam[0] = pServer->RegisterServer( pObject, (REGISTER_SERVER_INFO*)pMsg->data, (REGISTER_SERVER_RESULT*)pMsg->data );
	pObject->SendMsg(pMsg,sizeof(REGISTER_SERVER_RESULT));
	if( pMsg->wParam[0] != SE_OK )
	{
		pObject->Disconnect( 1000 );
	}
	return true;
}
//------------------------------------------------------------------------
bool CCodeMsgFunc::OnMsg_UpdateSvrInfo( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	CODE_MSG_COMMON;
	pObject->m_RegInfo.dwConnections = pMsg->dwFlag;
	return true;
}
//------------------------------------------------------------------------
bool CCodeMsgFunc::OnMsg_FindSvr( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	CODE_MSG_COMMON;
	pMsg->wParam[0] = pServer->FindServer( (servertype)pMsg->wParam[0], pMsg->data, (FINDSERVER_RESULT*)pMsg->data );
	if( pMsg->wParam[0] == SE_OK )
		datasize = sizeof( FINDSERVER_RESULT );
	pObject->SendMsg(pMsg, datasize);
	return true;
}
//------------------------------------------------------------------------
bool CCodeMsgFunc::OnMsg_AcrossSvr( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	CODE_MSG_COMMON;
	UINT id = pMsg->wParam[2];
	CClientObj * pObj = (CClientObj *)pServer->getObject(id);
	if( pObj )
	{
		pMsg->wParam[1] = pObject->m_RegInfo.Ident.bType;
		pMsg->wParam[2] = pObject->getId();
		pObj->SendMsg( pMsg, datasize );
	}
	return true;
}
//------------------------------------------------------------------------
bool CCodeMsgFunc::OnMsg_GSNameList( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	CODE_MSG_COMMON;
	string list;
	pMsg->wParam[1] = pServer->GetGameServerName(list);
	if( pMsg->wParam[1] == SE_OK )
	{
		pObject->SendMsg(pMsg->dwFlag,SCM_MSGGSNAMELIST,pMsg->wParam[1],0,0,(LPVOID)list.c_str(),list.length());
	}
	return true;
}
//------------------------------------------------------------------------