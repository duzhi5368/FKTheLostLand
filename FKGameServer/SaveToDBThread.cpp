/**
*	created:		2013-4-18   23:48
*	filename: 		SaveToDBThread
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\savetodbthread.h"
#include ".\simpledbconnection.h"
#include ".\server.h"
#include ".\humanplayermgr.h"
#include ".\humanplayer.h"
//------------------------------------------------------------------------
extern CServerForm g_Form;
//------------------------------------------------------------------------
CSaveToDBThread::CSaveToDBThread(void)
{
	m_pxDBConnection = new CSimpleDBConnection;
}
//------------------------------------------------------------------------
CSaveToDBThread::~CSaveToDBThread(void)
{
}
//------------------------------------------------------------------------
static char	m_szBackupBuffer[1024*1024];
//------------------------------------------------------------------------
VOID CSaveToDBThread::Execute( LPVOID lpParam )
{
	AllocConsole();
	FILE * fpout = freopen("CONOUT$", "r+", stdout);
	printf( "FK紧急保存开始...\n" );

	CIndexListEx<CHumanPlayer> * pList = CHumanPlayerMgr::GetInstance()->GetPlayerList();
	if( pList == NULL || pList->GetCount() == 0 )
	{
		FreeConsole();
		return;
	}

	// 获取DB服务器地址
	SERVERADDR	* pAddr = CServer::GetInstance()->GetDBAddr( 0 );
	if( pAddr == NULL )
	{
		printf( "无法取得ＤＢ服务器的地址，无法完成紧急数据备份。\n" );
		return;
	}
	m_State = TS_CONNECTINGDBSERVER;

	CHumanPlayer * pPlayer = pList->First();
	while( !this->IsTerminated() )
	{
		Sleep( 1 );
		if( GetStatus() != SS_EMPTY )
		{
			CSimpleDBConnection::Update();
		}
		switch( m_State )
		{
		case	TS_CONNECTINGDBSERVER:
			{
				if( !Connect( pAddr->addr, pAddr->nPort ) )
				{
					printf( "无法连接DBSERVER %s:%u 请检查是否已经打开，10秒钟后重试。\n" );
					Sleep( 10000 );
				}
				else
				{
					printf( "连接到DBServer!!开始进行紧急数据备份\n" );
					this->SetNoBlocking();
					m_State = TS_WAITING;
					SendMsg( 0, DM_CHECKFREE, 0, 0, 0 );
				}
			}
			break;
		case	TS_WAITING:
			{
				
			}
			break;
		case	TS_RUNNING:
			{
				if( pPlayer )
				{
					DoWithPlayer( pPlayer );
					pPlayer = pList->Next();
					SendMsg( 0, DM_CHECKFREE, 0, 0, 0 );
					m_State = TS_WAITING;
				}
				else
				{
					printf( "没有角色，10秒钟后退出\n" );
					Sleep( 10000 );
					FreeConsole();
					return;
				}
			}
			break;
		}
	}
	
	printf( "FK紧急保存完成...\n" );
	FreeConsole();
}
//------------------------------------------------------------------------
VOID CSaveToDBThread::OnMsg( MIRMSG * pMsg, int datasize )
{
	switch( pMsg->wCmd )
	{
	case DM_CHECKFREE:
		{
			m_State = TS_RUNNING;
		}
		break;
	}
}

#define	PACKET_PART_SIZE	1024
//------------------------------------------------------------------------
VOID CSaveToDBThread::DoWithPlayer( CHumanPlayer * pPlayer )
{
	xPacket msgpacket( m_szBackupBuffer, 1024*1024 );
	pPlayer->GetDBInfoPacket( msgpacket );
	SetBlocking();
	char * msg = (char*)msgpacket.getbuf();
	int size = msgpacket.getsize();
	while( size > 0 )
	{
		Send( (LPVOID)msg, size > PACKET_PART_SIZE?PACKET_PART_SIZE:size );
		msg += PACKET_PART_SIZE;
		size -= PACKET_PART_SIZE;
	}
	pPlayer->SaveVars();
	printf( "角色 %s 信息已经保存到数据库！\n", pPlayer->GetName() );
	SetNoBlocking();
}
//------------------------------------------------------------------------