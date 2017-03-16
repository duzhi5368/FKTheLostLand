/**
*	created:		2013-4-19   10:00
*	filename: 		xsimplesocket
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
enum e_socket_status
{
	SS_EMPTY,
	SS_CONNECTING,
	SS_CONNECTED,
	SS_ACCEPTED,
	SS_LISTEN,
};
//------------------------------------------------------------------------
class xSimpleSocket
{
public:
	xSimpleSocket(void);
	xSimpleSocket( SOCKET sInit, e_socket_status status );
	xSimpleSocket( xSimpleSocket & socket );

	VOID	SetSocket( SOCKET s, e_socket_status status = SS_ACCEPTED );
	virtual ~xSimpleSocket(void);

	BOOL	Socket( int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP );

	BOOL	Connect( const char * pszAddress, UINT nPort );
	BOOL	ConnectNoBlocking( const char * pszAddress, UINT nPort );
	BOOL	Connected();

	BOOL	Listen( const char * pszAddress, UINT nPort );
	BOOL	Accept( xSimpleSocket & socket );

	BOOL	Close();
	VOID	Clear();

	int		Send( LPVOID lpBuffer, int iSize );
	int		Recv( LPVOID lpBuffer, int iSize );

	BOOL 	SetBlocking();
	BOOL 	SetNoBlocking();
	BOOL	Select( PBOOL pRead, PBOOL pWrite, PBOOL pExcept, DWORD dwTimeOut );

	e_socket_status GetStatus(){ return m_Status;}
	
	xSimpleSocket & operator =( xSimpleSocket & socket )
	{
		m_Socket = socket.m_Socket;
		m_Status = socket.m_Status;
		return *this;
	}

	xSimpleSocket & operator =( SOCKET s )
	{
		m_Socket = s;
		m_Status = SS_ACCEPTED;
		return *this;
	}

	static VOID NetStartup();
	static VOID NetCleanup();
	SOCKET	GetHandle(){ return m_Socket;}
protected:
	virtual VOID OnError( const char * pszTips ){}
protected:
	SOCKET	m_Socket;
	e_socket_status m_Status;
};
//------------------------------------------------------------------------