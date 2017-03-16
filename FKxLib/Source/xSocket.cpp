/**
*	created:		2013-4-16   4:33
*	filename: 		xSocket
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xinc.h"
#include "..\Include\xsocket.h"
//------------------------------------------------------------------------
xSocket::xSocket()
{
	setState(SS_UNINITED);
	m_szAddress[0] = 0;
	m_nPort = 0;
	setSocket(INVALID_SOCKET);
}
//------------------------------------------------------------------------
xSocket::xSocket( SOCKET Socket )
{
	setState(SS_UNINITED);
	m_szAddress[0] = 0;
	m_nPort = 0;
	setSocket( Socket );
}
//------------------------------------------------------------------------
xSocket::~xSocket(void)
{
	close();
}
//------------------------------------------------------------------------
BOOL xSocket::makeSocket( int af, int type, int protocol )
{
	m_Socket = socket( af, type, protocol );
	if( m_Socket == INVALID_SOCKET )
	{
		setError( WSAGetLastError(), "socket( %d, %d, %d ) µ÷ÓÃÊ§°Ü£¡", af, type, protocol );
		setState( SS_UNINITED );
		return FALSE;
	}
	setState( SS_UNUSED );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xSocket::setSocket( SOCKET Socket )
{
	m_Socket = Socket;
	if( Socket != INVALID_SOCKET )
		setState( SS_UNUSED );
	else
	{
		m_szAddress[0] = 0;
		m_nPort = 0;
		setState( SS_UNINITED );
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID xSocket::close()
{
	m_nPort = 0;
	closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
	setState(SS_UNINITED);
}
//------------------------------------------------------------------------
BOOL xSocket::sendEx( LPVOID lpData, int nDatasize, DWORD &dwBytesSent, DWORD dwFlag, LPOVERLAPPED lpOverlapped )
{
	WSABUF	wsabuf;
	wsabuf.buf = (char*)lpData;
	wsabuf.len = nDatasize;

	if( WSASend( m_Socket, &wsabuf, 1, &dwBytesSent, dwFlag, lpOverlapped, NULL ) == SOCKET_ERROR )
	{
		int code = WSAGetLastError();
		if( code != WSA_IO_PENDING )
		{
			setError( code, "WSASend() Ê§°Ü£¡" );
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xSocket::recvEx( LPVOID lpDataBuf, int nBufsize, DWORD &dwBytesReceived, DWORD &dwFlag, LPOVERLAPPED lpOverlapped )
{
	WSABUF	wsabuf;
	wsabuf.buf = (char*)lpDataBuf;
	wsabuf.len = nBufsize;

	if( WSARecv( m_Socket, &wsabuf, 1, &dwBytesReceived, &dwFlag, lpOverlapped, NULL ) == SOCKET_ERROR )
	{
		int code = WSAGetLastError();
		if( code != WSA_IO_PENDING )
		{
			setError( code, "WSARecv() Ê§°Ü£¡" );
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xSocket::acceptEx( xSocket & sAccept, LPVOID lpDataBuf, DWORD dwRecvBufferLength, DWORD &dwBytesReceived, LPOVERLAPPED lpOverlapped )
{
	if( sAccept.getState() != SS_UNUSED )
	{
		sAccept.close();
		sAccept.makeSocket();
	}

	if( AcceptEx( m_Socket, sAccept.getSocketFd(), lpDataBuf, dwRecvBufferLength, sizeof( SOCKADDR_IN ) +16, sizeof( SOCKADDR_IN ) +16, &dwBytesReceived, lpOverlapped ) )
	{
		sAccept.setState( SS_ACCEPTED );
		return TRUE;
	}

	if( WSAGetLastError() == ERROR_IO_PENDING )
		return TRUE;

	setError( WSAGetLastError(), "AcceptEx() Ê§°Ü£¡" );

	return FALSE;
}
//------------------------------------------------------------------------
BOOL xSocket::connect( const char * cp, UINT nPort )
{
	struct	sockaddr_in ServAddr;
	LPHOSTENT m_pHost = gethostbyname(cp);
	if( m_pHost == NULL )
	{
		setError( WSAGetLastError(), "connect() ÖÐ gethostbyname( %s ) Ê§°Ü£¡", cp );
		return FALSE;
	}

	if( getState() != SS_UNUSED )
	{
		close();
		makeSocket();
	}

	ServAddr.sin_family	= AF_INET;
	ServAddr.sin_addr.s_addr = *(ULONG *)m_pHost->h_addr_list[0];
	ServAddr.sin_port = htons(nPort);

	int erri = ::connect(m_Socket, (struct sockaddr *)&ServAddr, sizeof(ServAddr));
	if( erri == SOCKET_ERROR )
	{
		setError( WSAGetLastError(), "connect() ÖÐ connect() Ê§°Ü£¡" );
		return FALSE;
	}
	setEndPoint( cp, nPort );
	setState(SS_CONNECTED);
	return	TRUE;
}
//------------------------------------------------------------------------
BOOL	xSocket::listen( UINT nPort )
{
	struct	sockaddr_in	serveraddr;
	if( getState() != SS_UNUSED )
	{
		close();
		makeSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	memset( (void*)&serveraddr, 0, sizeof( struct sockaddr_in ));

	serveraddr.sin_family = PF_INET;
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	serveraddr.sin_port =htons( nPort );


	if( ::bind(m_Socket, (struct sockaddr * )&serveraddr, sizeof( struct sockaddr_in )) == SOCKET_ERROR )
	{
		setError( WSAGetLastError(), "listen() ÖÐ bind() Ê§°Ü£¡" );
		return FALSE;
	}
	if( ::listen( m_Socket, 64 ) == SOCKET_ERROR )
	{	
		setError( WSAGetLastError(), "listen() ÖÐ listen() Ê§°Ü£¡" );
		return FALSE;
	}
	setEndPoint( "0.0.0.0", nPort );
	setState(SS_LISTENING);
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xSocket::listen( const char * cp, UINT nPort )
{
	struct	sockaddr_in	serveraddr;
	LPHOSTENT m_pHost = gethostbyname(cp);
	if( m_pHost == NULL )
	{
		setError( WSAGetLastError(), "listen( %s, %u ) ÖÐ gethostbyname( %s ) Ê§°Ü£¡", cp, nPort, cp );
		return FALSE;
	}

	if( getState() != SS_UNUSED )
	{
		close();
		makeSocket();
	}

	memset( (void*)&serveraddr, 0, sizeof( struct sockaddr_in ));

	serveraddr.sin_family = PF_INET;
	serveraddr.sin_addr.s_addr = *(ULONG *)m_pHost->h_addr_list[0];
	serveraddr.sin_port = htons( nPort );


	if( ::bind(m_Socket, (struct sockaddr * )&serveraddr, sizeof( struct sockaddr_in )) == SOCKET_ERROR )
	{
		setError( WSAGetLastError(), "listen() ÖÐ bind() Ê§°Ü£¡" );
		return FALSE;
	}
	if( ::listen( m_Socket, 64 ) == SOCKET_ERROR )
	{	
		setError( WSAGetLastError(), "listen() ÖÐ listen() Ê§°Ü£¡" );
		return FALSE;
	}
	setEndPoint( cp, nPort );
	setState(SS_LISTENING);
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xSocket::setNoBlocking()
{
	unsigned long mode = 1;
	if( ioctlsocket( m_Socket, FIONBIO, &mode ) == SOCKET_ERROR )
	{
		setError( WSAGetLastError(), "setNoBlocking() ÖÐ ioctlsocket() Ê§°Ü£¡" );
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xSocket::setBlocking()
{
	unsigned long mode = 0;
	if( ioctlsocket( m_Socket, FIONBIO, &mode ) == SOCKET_ERROR )
	{
		setError( WSAGetLastError(), "setBlocking() ÖÐ ioctlsocket() Ê§°Ü£¡" );
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------