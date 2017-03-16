/**
*	created:		2013-4-19   9:59
*	filename: 		SimpleDBConnection
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\simpledbconnection.h"
//------------------------------------------------------------------------
CSimpleDBConnection::CSimpleDBConnection(void)
{
	this->m_xRecvPacket.create( 65536 );
	this->m_xSendPacket.create( 65536 );
}
//------------------------------------------------------------------------
CSimpleDBConnection::~CSimpleDBConnection(void)
{
	this->m_xRecvPacket.destroy();
	this->m_xSendPacket.destroy();
}
//------------------------------------------------------------------------
VOID CSimpleDBConnection::Update()
{
	BOOL	bSend = FALSE, bRecv = FALSE;
	if( Select( &bRecv, &bSend, NULL, 10 ) )
	{
		if( bRecv && m_xRecvPacket.getfreesize() > 0 )
		{
			int length = Recv( (LPVOID)m_xRecvPacket.getfreebuf(), m_xRecvPacket.getfreesize() );
			if( length > 0 )
				m_xRecvPacket.addsize( length );
		}
		if( m_xRecvPacket.getsize() > 0 )
		{
			char * pszMsg = (char*)m_xRecvPacket.getbuf();
			int msgptr = 0;
			int parsesize = 0;
			int allsize = m_xRecvPacket.getsize();
			if( allsize == 0 )return;
			do
			{
				parsesize = ParseMessage( pszMsg + msgptr, allsize-msgptr );
				msgptr += parsesize;
			}while( parsesize > 0 && allsize > msgptr );
			
			if( msgptr >= allsize )
				m_xRecvPacket.clear();
			else
				m_xRecvPacket.free( msgptr );
		}
		if( m_xSendPacket.getsize() > 0 )
		{
			int length = m_xSendPacket.getsize();
			if( length > 1024 )
				length = 1024;
			length = Send( (LPVOID)m_xSendPacket.getbuf(), length );
			if( length > 0 )
			{
				if( length == m_xSendPacket.getsize() )
					m_xSendPacket.clear();
				else
					m_xSendPacket.free( length );
			}
		}
	}
}
//------------------------------------------------------------------------
static char szTemp[65536];
//------------------------------------------------------------------------
VOID CSimpleDBConnection::SendMsg( DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpData, int datasize )
{
	int length = encodeMsg( szTemp, dwFlag, wCmd, w1, w2, w3, lpData, datasize );
	m_xSendPacket.push( (LPVOID)szTemp, length );
	length = Send( (LPVOID)m_xSendPacket.getbuf(), m_xSendPacket.getsize() );
	if( length < 1 )return;
	if( length == m_xSendPacket.getsize() )
		m_xSendPacket.clear();
	else
		m_xSendPacket.free( length );
}
//------------------------------------------------------------------------
static char g_szTempBuffer2[65536];
//------------------------------------------------------------------------
int	CSimpleDBConnection::ParseMessage( char * pszMsg, int iSize )
{
	char * pStart = NULL;
	int ParsedSize = 0;
	for( int i = 0;i < iSize;i ++ )
	{
		if( pszMsg[i] == '*' )
		{
			ParsedSize = i + 1;
		}
		else if( pszMsg[i] == '#' )
		{
			pStart = pszMsg + i + 1;
		}
		else if( pszMsg[i] == '!' )
		{
			if( pStart != NULL )
			{
				pszMsg[i] = 0;
				if( *pStart =='+' )
				{

				}
				else
				{
					if( *pStart >= '0' && *pStart <= '9' )pStart++;
					int length = _UnGameCode( pStart, (BYTE*)g_szTempBuffer2 );
					OnMsg( (MIRMSG*)g_szTempBuffer2, length - sizeof( MIRMSGHEADER ) );
				}
				pszMsg[i] = '!';
				pStart = NULL;
			}
			ParsedSize = i + 1;
		}
	}
	return ParsedSize;
}
//------------------------------------------------------------------------