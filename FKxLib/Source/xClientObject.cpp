/**
*	created:		2013-4-16   4:56
*	filename: 		xClientObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xclientobject.h"
#include "..\Include\xIocpUnit.h"
#include "..\Include\xpacket.h"
#include "..\Include\xIocpServer.h"
//------------------------------------------------------------------------
xClientObject::xClientObject(void) : m_xPacketQueue( 20000 )
{
}
//------------------------------------------------------------------------
xClientObject::~xClientObject(void)
{
}
//------------------------------------------------------------------------
BOOL xClientObject::postSend( xPacket * pPacket )
{
	if( getServer() == NULL )
	{
		setError( -7, "没有设置 Server 对象" );
		return FALSE;
	}

	if( !IsConnected() )
		return FALSE;

	xIocpUnit * pIocpUnit = getServer()->newIocpUnit();
	pIocpUnit->setEventListener( this );
	pIocpUnit->setData( pPacket );
	pIocpUnit->setType( IO_SEND );

	if( !postSend( pIocpUnit, pPacket ) )
	{
		getServer()->releaseIocpUnit(pIocpUnit);
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xClientObject::postSend( LPVOID lpData, int nSize )
{
	if( getServer() == NULL )
	{
		setError( -7, "没有设置 Server 对象" );
		return FALSE;
	}

	int nLeftSize = nSize;
	char * pData = (char*)lpData;
	while( nLeftSize > DEF_PACKET_SIZE )
	{
		xPacket * pPacket = getServer()->newPacket();
		if( pPacket == NULL )
		{
			setError( *getServer() );
			Disconnect();
			return FALSE;
		}
		pPacket->push( pData, DEF_PACKET_SIZE );
	
		if( !postSend( pPacket ) )
		{
			getServer()->releasePacket(pPacket);
			Disconnect();
			return FALSE;
		}
		nLeftSize -= DEF_PACKET_SIZE;
		pData += DEF_PACKET_SIZE;
	}
	if( nLeftSize > 0 )
	{
		xPacket * pPacket = getServer()->newPacket();
		if( pPacket == NULL )
		{
			setError( *getServer() );
			Disconnect();
			return FALSE;
		}
		pPacket->push( pData, nLeftSize );
	
		if( !postSend( pPacket ) )
		{
			getServer()->releasePacket(pPacket);
			Disconnect();
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xClientObject::postRecv()
{
	if( !IsConnected() )
		return FALSE;
	
	xPacket * pPacket = getServer()->newPacket();
	xIocpUnit * pIocpUnit = getServer()->newIocpUnit();
	pIocpUnit->setEventListener( this );
	pIocpUnit->setData( pPacket );
	pIocpUnit->setType( IO_READ );

	if( !postRecv( pIocpUnit, pPacket ) )
	{
		getServer()->releaseIocpUnit(pIocpUnit);
		getServer()->releasePacket(pPacket);
		Disconnect();
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID xClientObject::OnEvent( xEventSender * pSender, int iEvent, int iParam, LPVOID lpParam )
{
	switch( iEvent )
	{
	case	xIocpUnit::IUE_SEND:
		{
			xIocpUnit * pIocpUnit = (xIocpUnit*)lpParam;
			xPacket * pPacket = (xPacket*)pIocpUnit->getData();
			int	sendsize =pPacket->getsize();
			addSendBytes( iParam );
			getServer()->addSendBytes( iParam );
			getServer()->releaseIocpUnit(pIocpUnit);
			getServer()->releasePacket(pPacket);
			if( iParam < sendsize )
			{
				Disconnect();
			}
		}
		break;
	case	xIocpUnit::IUE_READ:
		{
			xIocpUnit * pIocpUnit = (xIocpUnit*)lpParam;
			xPacket * pPacket = (xPacket*)pIocpUnit->getData();
			BOOL	bDisconnect = FALSE;
			pPacket->setsize( iParam );
			if( iParam == 0 )
			{
				//	断开连接
				bDisconnect = TRUE;
			}
			else
			{
				addRecvBytes( iParam );
				getServer()->addRecvBytes( iParam );
				//	失败断开连接
				if( m_xPacketQueue.push(pPacket) )
				{
					pPacket = getServer()->newPacket();
					pIocpUnit->setData(pPacket);
					if( !postRecv( pIocpUnit, pPacket ) )
					{
						bDisconnect = TRUE;
					}
				}
				else
				{
					bDisconnect = TRUE;
				}

			}
			if( bDisconnect )
			{
				getServer()->releaseIocpUnit(pIocpUnit);
				getServer()->releasePacket(pPacket);
				Disconnect();
			}
		}
		break;
	}
}
//------------------------------------------------------------------------
BOOL xClientObject::postSend( xIocpUnit * pIocpUnit, xPacket * pPacket )
{
	return sendEx( (LPVOID)pPacket->getbuf(), pPacket->getsize(), 
		pIocpUnit->getOverlappedEx()->dwNumberOfBytes, 
		pIocpUnit->getOverlappedEx()->dwFlag,
		pIocpUnit->getOverlapped() );
}
//------------------------------------------------------------------------
BOOL xClientObject::postRecv( xIocpUnit * pIocpUnit, xPacket * pPacket )
{
	return recvEx( (LPVOID)pPacket->getbuf(), pPacket->getmaxsize(), 
		pIocpUnit->getOverlappedEx()->dwNumberOfBytes, 
		pIocpUnit->getOverlappedEx()->dwFlag,
		pIocpUnit->getOverlapped() );
}
//------------------------------------------------------------------------
void	xClientObject::Update()
{
	if( !IsConnected() )
		return;
	if( m_xPacketQueue.getcount() > 0 )
	{
		xPacket * pPacket = NULL;
		if( pPacket = m_xPacketQueue.pop() )
		{
			OnDataPacket( pPacket );
			getServer()->releasePacket(pPacket);
		}
	}

	if( m_bQueryDisconnect && this->m_xDisconnectTimer.IsTimeOut() )
		Disconnect();
}
//------------------------------------------------------------------------
BOOL xClientObject::IsConnected()
{
	if( getState() == SS_ACCEPTED || getState() == SS_CONNECTED )
		return TRUE;
	return FALSE;
}
//------------------------------------------------------------------------
VOID xClientObject::Disconnect( DWORD dwTimeOut )
{
	if( dwTimeOut == 0 )
	{
		if( getState() != SS_DISCONNECTED )
		{
			close();
			setState(SS_DISCONNECTED);
			getServer()->onDisconnect( this );
		}
	}
	else if( m_bQueryDisconnect == FALSE )
	{
		m_bQueryDisconnect = TRUE;
		this->m_xDisconnectTimer.Savetime();
		this->m_xDisconnectTimer.SetTimeOut( dwTimeOut );
	}
}
//------------------------------------------------------------------------
VOID xClientObject::Clean()
{
	m_dwRecvBytes = 0;
	m_dwSendBytes = 0;
	m_bQueryDisconnect = FALSE;
	xPacket * pPacket = NULL;
	while( pPacket = m_xPacketQueue.pop() )
	{
		getServer()->releasePacket( pPacket );
	}
	xIndexObject::Clean();
}
//------------------------------------------------------------------------