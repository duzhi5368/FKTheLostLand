/**
*	created:		2013-4-16   4:45
*	filename: 		xListenObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xsupport.h"
#include "xsocket.h"
#include "xserverobject.h"
//------------------------------------------------------------------------
class xIocpUnit;
class xListenObject;
//------------------------------------------------------------------------
class xAcceptSocket :
	public xSocket
{
public:
	xAcceptSocket()
	{
		m_pListenObject = NULL;
		memset( m_szBuffer, 0, sizeof( m_szBuffer ) );
	}
	xListenObject* getListenObject(){ return m_pListenObject;}
	void setListenObject( xListenObject * pObject ){m_pListenObject = pObject;}

	char* getBuffer(){ return m_szBuffer;}
	void reset(){ makeSocket();}
private:
	char	m_szBuffer[sizeof( SOCKADDR_IN ) * 2 + 32];
	xListenObject * m_pListenObject;
};
//------------------------------------------------------------------------
class xListenObject :
	public xSocket,
	public xEventListener,
	public xServerObject
{
public:
	xListenObject(void);
	virtual ~xListenObject(void);
	VOID OnEvent( xEventSender * pSender, int iEvent, int iParam, LPVOID lpParam );
	void postAccept( int nAccept );
	UINT getId(){return m_Id;}
	VOID setId(UINT id ){m_Id = id;}
private:
	UINT m_Id;
private:
	BOOL postAccept( xIocpUnit * pIocpUnit, xAcceptSocket * pAcceptSocket );
	xObjectPool<xAcceptSocket>	m_xAccpetSocketPool;
	xAcceptSocket * newAcceptSocket()
	{ 
		xAcceptSocket * p = m_xAccpetSocketPool.newObject();
		if( p )p->setListenObject( this );
		return p;
	}
	void releaseAcceptSocket(xAcceptSocket * pAcceptSocket){ m_xAccpetSocketPool.deleteObject(pAcceptSocket);}
};
//------------------------------------------------------------------------