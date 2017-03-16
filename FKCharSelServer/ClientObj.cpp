/**
*	created:		2013-4-15   22:50
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\clientobj.h"
#include "server.h"
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
	m_State = SCS_NOTVERIFIED;
	m_TimeOut.Savetime();
	m_nFailCount = 0;
	m_bSelected = FALSE;
	this->m_szCharName[0] = 0;
}
//------------------------------------------------------------------------
VOID CClientObj::OnConnection()
{
	m_TimeOut.Savetime();
}
//------------------------------------------------------------------------
VOID CClientObj::Update()
{
	if( m_State == SCS_WAITINGFORVERIFIED )
	{
		if( CServer::GetInstance()->GetLoginEnterInfo(m_nLoginId,m_nSelectId,m_EnterInfo))
		{
			m_TimeOut.Savetime();
			m_State = SCS_VERIFIED;
			PRINT( 255, "帐号 %s 通过验证...\n", m_EnterInfo.szAccount );
		}
		else
		{
			if( m_TimeOut.IsTimeOut( 10 * 1000 ) )
			{
				Disconnect();
				return;
			}
		}
	}
	else
	{
		if( m_TimeOut.IsTimeOut( 30*60*1000) )
		{
			Disconnect();
			return;
		}
		if( m_nFailCount >= 30 )
		{
			Disconnect();
			return;
		}
	}
	CClientObject::Update();
}
//------------------------------------------------------------------------
VOID CClientObj::OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size )
{

}
//------------------------------------------------------------------------
// GameServer的消息
VOID CClientObj::OnMASMsg( WORD wCmd, WORD wType, WORD wIndex, const char * pszData, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	switch( wCmd )
	{
	case	MAS_ENTERGAMESERVER:
		{
			ENTERGAMESERVER * pEnterInfo = (ENTERGAMESERVER*)pszData;
			if( pEnterInfo->nSelCharId == m_EnterInfo.nSid && pEnterInfo->nLoginId == m_EnterInfo.nLid )
			{
				if( m_State == SCS_VERIFIED && pEnterInfo->result == SE_OK )
				{ 
					// 通知Client进入GameServer,发送GameSvr地址
				}
				else
				{
					Disconnect();
					return;
				}
			}
		}
		break;
	}
}
//------------------------------------------------------------------------
//ServerCenter的消息
VOID CClientObj::OnSCMsg( PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	switch( pMsg->wCmd )
	{
	case SCM_GETGAMESERVERADDR://得到GameServer地址
		{
			if( pMsg->wParam[0] == SE_OK && m_State == SCS_VERIFIED )
			{
				m_GameServerAddr = *((FINDSERVER_RESULT*)pMsg->data);
				
				CSCClientObj * pObj = pServer->GetSCConnection();
				if( pObj != NULL )
				{
					ENTERGAMESERVER	enterinfo;
					enterinfo.nLoginId = m_EnterInfo.nLid;
					enterinfo.nSelCharId = m_EnterInfo.nSid;
					enterinfo.nClientId = getId();
					strncpy( enterinfo.szAccount, m_EnterInfo.szAccount, 10 );
					enterinfo.szAccount[10] = 0;
					o_strncpy( enterinfo.szName, m_szCharName, 20 );
					pObj->SendMsgAcrossServer( 0, MAS_ENTERGAMESERVER, MST_SINGLE, m_GameServerAddr.Id.bIndex,(char*)&enterinfo, sizeof( enterinfo ) );
					break;
				}
			}
		}
		break;
	}
}
//------------------------------------------------------------------------
//DBServer的消息
VOID CClientObj::OnDBMsg( PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	OnUnknownMsg( pMsg, datasize );
}
//------------------------------------------------------------------------
//Client的加密消息
VOID CClientObj::OnCodedMsg( xClientObject * pObject, PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	OnUnknownMsg( pMsg, datasize );
}
//------------------------------------------------------------------------
static char g_szTempOutputBuffer[65536];
//------------------------------------------------------------------------
VOID CClientObj::OnUnknownMsg( PMIRMSG pMsg, int datasize )
{
	CLogFile * pLogFile = CLogFile::GetInstance();
	char	 * szText = g_szTempOutputBuffer;
	int	tptr=0;
	pLogFile->LogText( "[%08x] [%s] MSGID %d\n", timeGetTime(), getAddress(), pMsg->wCmd );
	pLogFile->LogText(  /*fplog,*/"0x%08x %04x %04x %04x %04x[", pMsg->dwFlag, pMsg->wCmd, pMsg->wParam[0],pMsg->wParam[1],pMsg->wParam[2] );
	int i;
	for( i = 0;i < datasize;i ++ )
	{
		if( ((BYTE)*(pMsg->data + i ) ) < 20 )
			szText[i] = '.';
		else
			szText[i] = *(pMsg->data + i );
	}
	szText[i] = 0;
	pLogFile->LogText(  /*fplog,*/"%s", szText); 
	pLogFile->LogText(  /*fplog,*/"]\n" );
	pLogFile->LogText( /* fplog,*/"[" );
	for( int i = 0;i < datasize;i ++ )
	{
		pLogFile->LogText(  /*fplog,*/"%02x ", (BYTE)((*(pMsg->data + i))&0xff)); 
	}
	pLogFile->LogText(  /*fplog,*/"]\n" );
}
//------------------------------------------------------------------------