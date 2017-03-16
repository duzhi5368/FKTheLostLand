/**
*	created:		2013-4-16   5:05
*	filename: 		ClientObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "virtualobject.h"
#include "inc.h"
#include "msgprocessor.h"
//------------------------------------------------------------------------
#define PINGTIME	60000
#define USE_SEND_CACHE
//------------------------------------------------------------------------
class CClientObject :
	public CVirtualObject,public xClientObject, public CMsgProcessor
{
public:
	CClientObject(void);
	virtual ~CClientObject(void);
public:
	virtual VOID Clean(void);
	VOID	OnClientPingRet();
	BOOL	SendMsg( DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpData = NULL, int datasize = -1 );
	BOOL	SendMsg( PMIRMSG pMsg, int datasize );
	BOOL	PostMsg( const char * pszCodedMsg, int size );
	VOID	OnSCMsg_T( PMIRMSG pMsg, int datasize );
	int		ParseMessage( char * pszMsg, int iSize );

	virtual VOID OnDBMsg( PMIRMSG pMsg, int datasize ){}
	virtual VOID OnSCMsg( PMIRMSG pMsg, int datasize ){}

	virtual VOID OnConnection(){}
	virtual VOID OnMASMsg( WORD wCmd, WORD wType, WORD wIndex, const char * pszData, int datasize ){}
	virtual VOID Update();
	void	OnDataPacket(xPacket * pPacket );
	VOID	UpdateStarPing()
	{
		TRY_BEGIN
		if( m_Pingtimer.IsTimeOut( PINGTIME ))
		{
			m_Pingtimer.Savetime();
			if( m_bPingNoRet )
			{
				Disconnect();
				return;
			}
			PostMsg( "*", 1 );
		}
		TRY_END
	}

	DWORD	GetKey()
	{
		if( this == NULL )return 0;
		return m_dwClientKey;
	}

	CMsgProcessor * GetMsgProcessor(){ return this->m_pMsgProcessor;}
	VOID SetMsgProcessor( CMsgProcessor * pMsgProcessor ){ m_pMsgProcessor = pMsgProcessor;}

protected:
	DWORD	m_dwClientKey;
	DWORD	m_dwPing;
private:
	CMsgProcessor * m_pMsgProcessor;
	CServerTimer	m_Pingtimer;
	BOOL	m_bPingNoRet;
	xPacket	m_xParsePacket;
#ifdef USE_SEND_CACHE
	xPacket m_xSendPacket;
#endif
};
//------------------------------------------------------------------------