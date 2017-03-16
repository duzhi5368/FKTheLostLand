/**
*	created:		2013-4-16   4:31
*	filename: 		xSocket
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <WinSock2.h>
#include "xsupport.h"
#include "xerror.h"
//------------------------------------------------------------------------
class xSocket : public xError
{
public:
	enum	socket_state
	{
		SS_UNINITED,		// Î´³õÊ¼»¯×´Ì¬
		SS_UNUSED,			// Î´Ê¹ÓÃ×´Ì¬
		SS_ACCEPTED,		// ½ÓÊÜ×´Ì¬
		SS_CONNECTED,		// Á¬½Ó×´Ì¬
		SS_LISTENING,		// ¼àÌý×´Ì¬
		SS_DISCONNECTED,	// Î´Á¬½Ó×´Ì¬
	};
public:
	xSocket();
	xSocket( SOCKET Socket );

	virtual ~xSocket(void);
public:
	BOOL	makeSocket( int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP );
	BOOL	setSocket( SOCKET Socket );
	
	BOOL	setSocket( xSocket & socket ){ if( !setSocket( socket.getSocketFd() ))return FALSE; setState( socket.getState()); setEndPoint( socket.getAddress(), socket.getPort());return TRUE;}
	BOOL	steelSocket( xSocket & socket )
	{ 
		if( !setSocket( socket ) ) return FALSE;
		socket.clear();
		return TRUE;
	}


	BOOL	connect( const char * cp, UINT nPort );

	BOOL	listen( const char * cp, UINT nPort );
	BOOL	listen( UINT nPort );
	BOOL	setNoBlocking();
	BOOL	setBlocking();

	SOCKET	getSocketFd(){ return m_Socket;}

	socket_state getState(){ return m_state;}
	void setState( socket_state state ){ ::InterlockedExchange( (volatile LONG*)&m_state, state );}


	VOID	close();
	VOID	clear(){ setSocket( INVALID_SOCKET );}

	BOOL sendEx( LPVOID lpData, int nDatasize, DWORD &dwBytesSent, DWORD dwFlag, LPOVERLAPPED lpOverlapped );
	BOOL recvEx( LPVOID lpDataBuf, int nBufsize, DWORD &dwBytesReceived, DWORD &dwFlag, LPOVERLAPPED lpOverlapped );
	BOOL acceptEx( xSocket & sAccept, LPVOID lpDataBuf, DWORD dwRecvBufferLength, DWORD &dwBytesReceived, LPOVERLAPPED lpOverlapped );
	

	void setEndPoint( const char * cp, UINT nPort ){ strncpy( m_szAddress, cp, 20 ); m_nPort = nPort;}
	
	const char * getAddress(){return m_szAddress;}
	UINT getPort(){return m_nPort;}
private:
	char	m_szAddress[40];
	UINT	m_nPort;
	SOCKET	m_Socket;
	volatile socket_state m_state;
};
//------------------------------------------------------------------------