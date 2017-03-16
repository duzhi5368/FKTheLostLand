/**
*	created:		2013-4-19   0:55
*	filename: 		gsClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "gsclientobj.h"
#include "server.h"
#include "GmManager.h"
#include "HumanPlayer.h"
#include <time.h>
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
	m_State = GSUM_NOTVERIFIED;
	memset( &m_EnterInfo, 0, sizeof( m_EnterInfo ));
	m_pPlayer = NULL;
	m_hlTimer.Savetime();
	m_iGmLevel = 0;
	m_bScrollTextMode = FALSE;
	m_bNoticeMode = FALSE;
	m_bCompetlyQuit = FALSE;
}
//------------------------------------------------------------------------
VOID CClientObj::Update()
{
	UpdateStarPing();
	CClientObject::Update();
}
//------------------------------------------------------------------------
VOID CClientObj::OnUnCodeMsg( xClientObject * pObject,  char * pszMsg, int size )
{
}
//------------------------------------------------------------------------
VOID CClientObj::OnDBMsg( PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	switch( pMsg->wCmd )
	{
	default:
		pServer->OnUnknownMsg(pMsg, datasize);
		break;
	}
}
//------------------------------------------------------------------------
VOID CClientObj::OnVerifyString( char * pszString )
{
	close();
}
//------------------------------------------------------------------------
static char g_szTempBuffer2[65536];
//------------------------------------------------------------------------
VOID CClientObj::OnCodedMsg( xClientObject * pObject, PMIRMSG pMsg, int datasize ){
	memcpy( g_szTempBuffer2, pMsg, sizeof( MIRMSGHEADER ) + datasize+1 );
	pMsg = (PMIRMSG)g_szTempBuffer2;
	CServer * pServer = CServer::GetInstance();
	if( m_State != GSUM_VERIFIED )
	{
		switch( m_State )
		{
		case	GSUM_NOTVERIFIED:
			{
				OnVerifyString( (char*)pMsg );
			}
			break;
		}
		return;
	}
	ProcClientMsg( pMsg, datasize );
}
//------------------------------------------------------------------------
VOID	CClientObj::OnDisconnect()
{
	xPacket * pPacket = NULL;
	if( pPacket = m_xPacketQueue.pop() )
	{
		OnDataPacket( pPacket );
		getServer()->releasePacket(pPacket);
	}
	if( m_pPlayer != NULL ) 
	{
		EmergencySave();
	}

	if( !m_bCompetlyQuit && this->m_State == GSUM_VERIFIED )
	{
		CSCClientObj * pObj = CServer::GetInstance()->GetSCConnection();
		if( pObj != NULL )
		{
			pObj->SendMsgAcrossServer( 0, MAS_RESTARTGAME, MST_SINGLE, m_EnterInfo.dwSelectCharServerId, (char*)&m_EnterInfo, sizeof( m_EnterInfo ));
		}
	}
}
//------------------------------------------------------------------------
VOID CClientObj::OnCommand(char * pszCommand )
{
	if( m_pPlayer == NULL )return;
	CGmManager::GetInstance()->ExecGameCmd( pszCommand, m_pPlayer );
	return ;
}
//------------------------------------------------------------------------
extern char g_HistoryAddr[];
//------------------------------------------------------------------------
VOID CClientObj::ProcClientMsg( PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance(); 
	switch( pMsg->wCmd ) 
	{
	default:
		pServer->OnUnknownMsg(pMsg, datasize);
		break;
	}
}
//------------------------------------------------------------------------
VOID CClientObj::OnConnection()
{

}
//------------------------------------------------------------------------
// ½ô¼±±£´æ
VOID CClientObj::EmergencySave()
{
	if( m_pPlayer == NULL )return;
	m_pPlayer->UpdateToDB();
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