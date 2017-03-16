/**
*	created:		2013-4-16   4:58
*	filename: 		xIocpServer
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xiocpserver.h"
#include "..\Include\xiocpunit.h"
#include "..\Include\xpacket.h"
//------------------------------------------------------------------------
xIocpServer::xIocpServer(void) : m_xAcceptConnectionQueue( 2000 ), m_xDisconnectQueue( 2000 )
{
	WSADATA	wsad;
	memset( &wsad, 0, sizeof( wsad ));
	WSAStartup( 0x202, &wsad );
}
//------------------------------------------------------------------------
xIocpServer::~xIocpServer(void)
{
	WSACleanup();
}
//------------------------------------------------------------------------
BOOL xIocpServer::postListen( const char * cp, UINT nPort, int nPostAccept, UINT id )
{
	//	1- 分配listen对象
	xListenObject * pListenObject = m_xListenObjectPool.newObject();
	if( pListenObject == NULL )
	{
		setError( -4, "无法分配新的监听对象！" );
		return FALSE;
	}

	pListenObject->setServer(this);
	pListenObject->setId(id);
	//	2-	开始监听
	if( !pListenObject->listen( /*cp, */nPort ) )
	{
		setError( *pListenObject );
		return FALSE;
	}
	//	3-	绑定到完成端口
	if( !m_xIocpManager.Bind( pListenObject->getSocketFd(), 0xffffffff ) )
	{
		setError( m_xIocpManager );
		return FALSE;
	}

	//	4-	发送accept请求
	pListenObject->postAccept( nPostAccept );

	return TRUE;
}
//------------------------------------------------------------------------
BOOL	xIocpServer::start()
{
	m_dwSendKBytes = 0;
	m_dwSendBytes = 0;
	m_dwRecvKBytes = 0;
	m_dwRecvBytes = 0;

	//	iocp 管理器开始
	if( !m_xIocpManager.Start() )
	{
		setError( m_xIocpManager );
		return FALSE;
	}

	return TRUE;
}
//------------------------------------------------------------------------
BOOL	xIocpServer::stop()
{
	m_xIocpManager.Stop();
	return TRUE;
}
//------------------------------------------------------------------------
VOID	xIocpServer::update()
{
	xTempClient * pTempSocket = m_xAcceptConnectionQueue.pop();
	if( pTempSocket )
	{
		if( !pTempSocket->isPreDeleted() )
		{
			sendEvent( ISE_ONCONNECTION, pTempSocket->getId(), (LPVOID)pTempSocket );

			pTempSocket->preDelete(2000);
			m_xAcceptConnectionQueue.push(pTempSocket);
		}
		else
		{
			if( !pTempSocket->deleteTimeOut())
			{
				m_xAcceptConnectionQueue.push(pTempSocket);
			}
			else
			{
				//	delete
				pTempSocket->close();
				m_xTempClientPool.deleteObject(pTempSocket);
			}
		}
	}

	xSocket * pSocket = m_xDisconnectQueue.pop();
	if( pSocket )
	{
		sendEvent( ISE_ONDISCONNECTION, 0, pSocket );
	}
}
//------------------------------------------------------------------------
xPacket * xIocpServer::newPacket()
{
	xPacket * pPacket = m_xPacketPool.newObject();
	if( pPacket->notcreated() )
		pPacket->create( DEF_PACKET_SIZE );
	return pPacket;
}
//------------------------------------------------------------------------
void	xIocpServer::releasePacket( xPacket * pPacket )
{
	pPacket->clear();
	m_xPacketPool.deleteObject(pPacket);
}
//------------------------------------------------------------------------
xIocpUnit * xIocpServer::newIocpUnit()
{
	return m_xIocpUnitPool.newObject();
}
//------------------------------------------------------------------------
void	xIocpServer::releaseIocpUnit( xIocpUnit * pIocpUnit )
{
	pIocpUnit->setType( IO_NOTSET );
	pIocpUnit->setData( NULL );
	pIocpUnit->setEventListener( NULL );
	m_xIocpUnitPool.deleteObject( pIocpUnit );
}
//------------------------------------------------------------------------
void	xIocpServer::onConnection( xSocket * pSocket, UINT id )
{
	xTempClient * pTempSocket = m_xTempClientPool.newObject();
	pTempSocket->Clean();
	pTempSocket->steelSocket( *pSocket);
	m_xIocpManager.Bind( pTempSocket->getSocketFd(), 0 );
	pTempSocket->setId( id );
	pTempSocket->setServer( this );
	m_xAcceptConnectionQueue.push( pTempSocket );
}
//------------------------------------------------------------------------
void	xIocpServer::onDisconnect( xSocket * pSocket )
{
	m_xDisconnectQueue.push(pSocket);
}
//------------------------------------------------------------------------
BOOL xIocpServer::postConnection( const char * cp, UINT nPort, xSocket & socket )
{
	if( socket.connect(cp,nPort) )
	{
		if( m_xIocpManager.Bind( socket.getSocketFd(), 0 ) )
			return TRUE;
		socket.close();
	}
	return FALSE;
}
//------------------------------------------------------------------------