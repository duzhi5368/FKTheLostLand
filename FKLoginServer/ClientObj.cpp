/**
*	created:		2013-4-14   20:54
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "Clientobj.h"
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
	m_szAccount[0] = 0;
	m_nLid = 0;
	m_nFailCount = 0;
}
//------------------------------------------------------------------------
VOID CClientObj::OnConnection()
{
	char * p = (char*)CServer::GetInstance()->GetServerTips();
	PRINT( 0xff, "%s", p );
	m_TimeOut.Savetime();
}
//------------------------------------------------------------------------
VOID CClientObj::Update()
{
	if( m_TimeOut.IsTimeOut( 5*60*1000) )
	{
		Disconnect();
		return;
	}
	if( m_nFailCount >= 16 )
	{
		Disconnect();
		return;
	}
	CClientObject::Update();
}
//------------------------------------------------------------------------
VOID CClientObj::OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size )
{

}
//------------------------------------------------------------------------
void _tout( CIOConsole * pConsole, char * p )
{
	int len = *p;
	p ++;
	char	szText[128];
	strncpy( szText, p, len );
	szText[len] = 0;
	pConsole->OutPut( RGB(255,0,0), "%s\n", szText );
}
//------------------------------------------------------------------------
// 数据库过来的消息
VOID CClientObj::OnDBMsg( PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	OnUnknownMsg( pMsg, datasize );
}
//------------------------------------------------------------------------
VOID CClientObj::OnSCMsg( PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	OnUnknownMsg( pMsg, datasize );
}
//------------------------------------------------------------------------
VOID CClientObj::OnCodedMsg( xClientObject * pObject, PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	OnUnknownMsg( pMsg, datasize );
}
//------------------------------------------------------------------------
VOID CClientObj::OnMASMsg( WORD wCmd, WORD wType, WORD wIndex, const char * pszData, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
}
//------------------------------------------------------------------------
static char g_szTempOutputBuffer[65536];
//------------------------------------------------------------------------
VOID CClientObj::OnUnknownMsg( PMIRMSG pMsg, int datasize )
{
	CLogFile * pLogFile = CLogFile::GetInstance();
	char	 * szText = g_szTempOutputBuffer;
	int	tptr = 0;
	pLogFile->LogText( "[%08x] [%s] MSGID %d\n", timeGetTime(), getAddress(), pMsg->wCmd );
	pLogFile->LogText(  /*fplog,*/"0x%08x %04x %04x %04x %04x[", pMsg->dwFlag, pMsg->wCmd, pMsg->wParam[0],pMsg->wParam[1],pMsg->wParam[2] );
	 int i;
	for(i = 0;i < datasize;i ++ )
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
static char g_szTempBuffer6[65536];
//------------------------------------------------------------------------
VOID CClientObj::SendMsgHook( DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpData, int datasize )
{
	SendMsg( dwFlag, wCmd, w1, w2, w3, lpData, datasize );
	return;
	MIRMSG	*	pmsg = (MIRMSG	*)g_szTempBuffer6;
	pmsg->dwFlag = dwFlag;
	pmsg->wCmd = wCmd;
	pmsg->wParam[0] = w1;
	pmsg->wParam[1] = w2;
	pmsg->wParam[2] = w3;
	if( lpData )
	{
		if( datasize <= 0 )
			datasize = (int)strlen( (char*)lpData );
		memcpy( pmsg->data, lpData, datasize );
		lpData = (LPVOID)pmsg->data;
	}
	for( unsigned int i = 0;i < sizeof( MIRMSGHEADER ) + datasize;i ++ )
	{
		g_szTempBuffer6[i] ^= 1;
	}
	SendMsg( pmsg->dwFlag, pmsg->wCmd, pmsg->wParam[0], pmsg->wParam[1], pmsg->wParam[2], lpData, datasize );
}
//------------------------------------------------------------------------