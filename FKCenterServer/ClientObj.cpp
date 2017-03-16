/**
*	created:		2013-4-15   22:31
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\clientobj.h"
#include ".\server.h"
#include ".\CenterServerCodeMsgParser.h"
//------------------------------------------------------------------------
CClientObj::CClientObj(void)
{
	Clean();
}
//------------------------------------------------------------------------
CClientObj::~CClientObj(void)
{
}
//------------------------------------------------------------------------
void CClientObj::Clean()
{
	CClientObject::Clean();
	memset( &m_RegInfo, 0, sizeof( m_RegInfo ) );
}
//------------------------------------------------------------------------
VOID CClientObj::Update()
{
	CClientObject::Update();
}
//------------------------------------------------------------------------
VOID CClientObj::OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size )
{

}
//------------------------------------------------------------------------
VOID CClientObj::OnCodedMsg( xClientObject * pObject, PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	if( !CCenterSvrMsgParser::GetInstance()->OnRecvCodeMsg( this, pMsg, datasize ) )
	{
		pConsole->OutPut( 0xff00, "解析消息失败...ID = %d\n", pMsg->wCmd );
	}
	else
	{
		pConsole->OutPut( 0xff00, "解析消息成功...ID = %d\n", pMsg->wCmd );
	}
}
//------------------------------------------------------------------------