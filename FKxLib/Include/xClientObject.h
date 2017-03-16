/**
*	created:		2013-4-16   0:38
*	filename: 		xClientObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xsocket.h"
#include "xserverobject.h"
#include "xsupport.h"
#include "xindexobject.h"
//------------------------------------------------------------------------
// IOCP包默认大小
#define DEF_PACKET_SIZE	 4096
//------------------------------------------------------------------------
class xIocpUnit;
class xPacket;
//------------------------------------------------------------------------
class xClientObject : 
	public xSocket,
	public xServerObject,
	public xEventListener,
	public xIndexObject
{
public:
	xClientObject(void);
	virtual ~xClientObject(void);
	BOOL postSend( xPacket * pPacket );
	BOOL postSend( LPVOID lpData, int nSize );
	BOOL postRecv();
	VOID OnEvent( xEventSender * pSender, int iEvent, int iParam, LPVOID lpParam );

	virtual void Update();
	virtual void OnDataPacket( xPacket * pPacket ){}
	virtual void OnDisconnect(){}
	virtual void Clean();

	BOOL	IsConnected();
	VOID	Disconnect( DWORD dwTimeOut = 0 );

	VOID	addSendBytes( DWORD dwBytes )
	{
		InterlockedExchangeAdd(
			( LPLONG ) &m_dwSendBytes,
			dwBytes
			);
	}
	DWORD	getSendBytes(){ return m_dwSendBytes;}

	VOID	addRecvBytes( DWORD dwBytes )
	{
		InterlockedExchangeAdd(
			( LPLONG ) &m_dwRecvBytes,
			dwBytes
			);
	}
	DWORD	getRecvBytes(){ return m_dwRecvBytes;}
private:
	volatile DWORD	m_dwSendBytes;
	volatile DWORD	m_dwRecvBytes;

	BOOL postSend( xIocpUnit * pIocpUnit, xPacket * pPacket );
	BOOL postRecv( xIocpUnit * pIocpUnit, xPacket * pPacket );
protected:
	xPtrQueue<xPacket>	m_xPacketQueue;
	CServerTimer m_xDisconnectTimer;
	BOOL	m_bQueryDisconnect;
};
//------------------------------------------------------------------------