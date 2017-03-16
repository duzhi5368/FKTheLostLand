/**
*	created:		2013-4-16   4:59
*	filename: 		xListenObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xlistenobject.h"
#include "..\Include\xiocpunit.h"
#include "..\Include\xclientobject.h"
#include "..\Include\xInc.h"
#include "..\Include\xiocpserver.h"
//------------------------------------------------------------------------
xListenObject::xListenObject(void)
{
}
//------------------------------------------------------------------------
xListenObject::~xListenObject(void)
{
}
//------------------------------------------------------------------------
VOID xListenObject::OnEvent( xEventSender * pSender, int iEvent, int iParam, LPVOID lpParam )
{
	sockaddr	*	p1 = NULL, *p2 = NULL;
	int	len1, len2;
	if( iEvent == xIocpUnit::IUE_ACCEPT )
	{
		xIocpUnit * pIocpUnit = (xIocpUnit*)lpParam;

		xAcceptSocket * pAcceptSocket = (xAcceptSocket*)pIocpUnit->getData();
		GetAcceptExSockaddrs( (LPVOID)pAcceptSocket->getBuffer(), 0, sizeof( SOCKADDR_IN) + 16, sizeof( SOCKADDR_IN)+16, &p1, &len1, &p2, &len2 );
		if( p2 != NULL )
		{
			char * p = inet_ntoa( ((SOCKADDR_IN*)p2)->sin_addr );
			if( p != NULL )
				pAcceptSocket->setEndPoint(p, ntohs( ((SOCKADDR_IN*)p2)->sin_port ));
		}
		pAcceptSocket->setState( SS_ACCEPTED );
		getServer()->onConnection( pAcceptSocket, getId() );
		pAcceptSocket->reset();
		postAccept( (xIocpUnit*)pSender, pAcceptSocket );
	}
}
//------------------------------------------------------------------------
void	xListenObject::postAccept( int nAccept )
{
	xIocpUnit * pIocpUnit = NULL;
	xAcceptSocket * pAcceptSocket = NULL;
	for( int i = 0;i < nAccept;i ++ )
	{
		if( pIocpUnit == NULL )pIocpUnit = getServer()->newIocpUnit();
		if( pIocpUnit == NULL )continue;
		if( pAcceptSocket == NULL )pAcceptSocket = newAcceptSocket();
		if( pAcceptSocket == NULL )continue;
		pIocpUnit->setEventListener(this);
		pIocpUnit->setType( IO_ACCEPT );
		pIocpUnit->setData( pAcceptSocket );
		if( postAccept(pIocpUnit, pAcceptSocket ))
		{
			pIocpUnit = NULL;
			pAcceptSocket = NULL;
		}
	}
	if( pIocpUnit )getServer()->releaseIocpUnit(pIocpUnit);
	if( pAcceptSocket )releaseAcceptSocket(pAcceptSocket);
}
//------------------------------------------------------------------------
BOOL xListenObject::postAccept( xIocpUnit * pIocpUnit, xAcceptSocket * pAcceptSocket )
{
	return acceptEx( *pAcceptSocket, (LPVOID)pAcceptSocket->getBuffer(), 0, pIocpUnit->getOverlappedEx()->dwNumberOfBytes, pIocpUnit->getOverlapped() );
}
//------------------------------------------------------------------------