/**
*	created:		2013-4-16   4:29
*	filename: 		xIocpServer
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xsupport.h"
#include "xlistenobject.h"
#include "xiocpmanager.h"
#include "xsocket.h"
#include "xindexobject.h"
#include "xclientobject.h"
//------------------------------------------------------------------------
class xIocpUnit;
//------------------------------------------------------------------------
class xTempClient :
	public xClientObject
{
public:
	xTempClient()
	{
		m_bPreDeleted = FALSE;
	}

	VOID	Clean()
	{
		xClientObject::Clean();
		m_bPreDeleted = FALSE;
	}

	VOID	preDelete( DWORD dwTime = 0 )
	{
		if( dwTime == 0 )
			dwTime = 10000;
		m_deleteTimer.SetTimeOut(dwTime);
		m_deleteTimer.Savetime();
		m_bPreDeleted = TRUE;
	}

	BOOL	deleteTimeOut( DWORD dwTime = 0 )
	{
		if( dwTime > 0 )
			return m_deleteTimer.IsTimeOut(dwTime);
		return m_deleteTimer.IsTimeOut();
	}

	BOOL	isPreDeleted(){return m_bPreDeleted;}

private:
	BOOL	m_bPreDeleted;
	CServerTimer m_deleteTimer;
};
//------------------------------------------------------------------------
struct accept_connection
{
	UINT	nListenId;
	SOCKET sAccept;
};
//------------------------------------------------------------------------
class xIocpServer : 
	public xError,
	public xEventSender
{
public:
	enum	eventid
	{
		ISE_ID	=	2000,
		ISE_ONCONNECTION,
		ISE_ONDISCONNECTION,
	};

	xIocpServer(void);
	virtual ~xIocpServer(void);

	BOOL	postListen( const char * cp, UINT nPort, int nPostAccept = 64, UINT id = 0 );
	BOOL	postConnection( const char * cp, UINT nPort, xSocket & socket );

	BOOL	start();
	BOOL	stop();
	VOID	update();

	xPacket * newPacket();
	void	releasePacket( xPacket * pPacket );

	xIocpUnit * newIocpUnit();
	void	releaseIocpUnit( xIocpUnit * pIocpUnit );

	void	onConnection( xSocket * pSocket, UINT id );
	void	onDisconnect( xSocket * pSocket );

	void	addRecvBytes( DWORD dwBytes )
	{
		InterlockedExchangeAdd(
			( LPLONG ) &m_dwRecvBytes,
			dwBytes
			);
		if( m_dwRecvBytes >= 1024 )
		{
			InterlockedExchangeAdd(
				( LPLONG ) &m_dwRecvBytes,
				-1024
				);
			InterlockedIncrement( ( LPLONG ) &m_dwRecvKBytes );
		}
	}
	DWORD	getRecvKBytes(){ return m_dwRecvKBytes;}

	void	addSendBytes( DWORD dwBytes )
	{
		InterlockedExchangeAdd(
			( LPLONG )  &m_dwSendBytes,
			dwBytes
			);
		if( m_dwRecvBytes >= 1024 )
		{
			InterlockedExchangeAdd(
				( LPLONG ) &m_dwSendBytes,
				-1024
				);
			InterlockedIncrement( ( LPLONG ) &m_dwSendKBytes );
		}
	}
	DWORD	getSendKBytes(){ return m_dwRecvKBytes;}
	void	getPacketCount( int & free, int & used, int & all )
	{
		free = m_xPacketPool.getFreeCount();
		used = m_xPacketPool.getUsedCount();
		all = m_xPacketPool.getCount();
	}

	void	getUnitCount( int & free, int & used, int & all )
	{
		free = m_xIocpUnitPool.getFreeCount();
		used = m_xIocpUnitPool.getUsedCount();
		all = m_xIocpUnitPool.getCount();
	}
private:

	volatile DWORD	m_dwRecvKBytes;
	volatile DWORD	m_dwRecvBytes;
	volatile DWORD	m_dwSendKBytes;
	volatile DWORD	m_dwSendBytes;

	xPtrQueue<xSocket>					m_xDisconnectQueue;
	xPtrQueue<xTempClient>				m_xAcceptConnectionQueue;
	CDQueue<accept_connection, 2000>	m_xAcceptQueue;
	xObjectPool<xListenObject>			m_xListenObjectPool;
	xObjectPool<xPacket>				m_xPacketPool;
	xObjectPool<xIocpUnit>				m_xIocpUnitPool;
	xObjectPool<xTempClient>			m_xTempClientPool;
	xIocpManager						m_xIocpManager;
};
//------------------------------------------------------------------------