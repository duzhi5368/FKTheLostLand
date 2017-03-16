/**
*	created:		2013-4-16   5:38
*	filename: 		SocketFunction
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/socketfunction.h"
//------------------------------------------------------------------------
int SetNoBlock( SOCKET s )
{
	unsigned long mode = 1;
	if( ioctlsocket( s, FIONBIO, &mode ) == -1 )
		return 0;
	return 1;
}
//------------------------------------------------------------------------
int SetBlock( SOCKET s )
{
	unsigned long mode = 0;
	if( ioctlsocket( s, FIONBIO, &mode ) == -1 )
		return 0;
	return 1;
}
//------------------------------------------------------------------------
BOOL	NetStartup()
{
	return NetStartup( 2,2 );
}
//------------------------------------------------------------------------
BOOL	NetCleanup()
{
	return WSACleanup();
}
//------------------------------------------------------------------------
SOCKET	OpenConnection( const char * ip, const UINT port, PROXY_SETTING * proxysetting )
{
	LPHOSTENT m_pHost;
	SOCKET	s;
	if( proxysetting != NULL )
	{
		int ierr = 0;
		s = OpenConnection( proxysetting->szProxyIp, proxysetting->nPort );
		if( s == 0	)
			return 0;
		char buff[600];
		struct sock5req1 *m_proxyreq1; 
		m_proxyreq1 = (struct sock5req1 *)buff; 
		m_proxyreq1->Ver = 5; 
		m_proxyreq1->nMethods = 2; 
		m_proxyreq1->Methods[0] = 0; 
		m_proxyreq1->Methods[1] = 2; 
		ierr = send(s, buff,4, 0); 
		if( ierr < 0 || ierr != 4 )
		{
			closesocket( s );
			return 0;
		}
		struct sock5ans1 *m_proxyans1; 
		m_proxyans1 = (struct sock5ans1 *)buff; 
		memset(buff,0,600); 
		ierr = recv(s,buff,600, 0); 
		if( ierr <= 0 )
		{
			closesocket( s );
			return 0;
		}
		if(m_proxyans1->Ver != 5 || (m_proxyans1->Method!=0 && m_proxyans1->Method!=2)) 
		{ 
			printf("通过代理连接主站不成功!\n"); 
			closesocket( s );
			return 0; 
		} 
		if(m_proxyans1->Method == 2) 
		{

			int nUserLen = (int)strlen(proxysetting->szUsername); 
			int nPassLen = (int)strlen(proxysetting->szPassword); 
			struct authreq *m_authreq; 
			m_authreq = (struct authreq *)buff; 
			m_authreq->Ver = 1; 
			m_authreq->Ulen = nUserLen; 
			strcpy(m_authreq->Name,proxysetting->szUsername); 
			m_authreq->PLen = nPassLen; 
			strcpy(m_authreq->Pass,proxysetting->szPassword); 
			ierr = send(s,buff,513, 0); 
			if( ierr < 0 || ierr != 513 )
			{
				closesocket( s );
				return 0;
			}
			struct authans *m_authans; 
			m_authans = (struct authans *)buff; 
			memset(buff,0,600); 
			ierr = recv(s,buff,600,0); 
			if( ierr <= 0 )
			{
				closesocket( s );
				return 0;
			}
			if(m_authans->Ver != 1 || m_authans->Status != 0) 
			{ 
				printf("代理服务器用户验证不成功!\n"); 
				closesocket( s );
				return 0; 
			} 
		} 
		struct sock5req2 *m_proxyreq2; 
		m_proxyreq2 = (struct sock5req2 *)buff; 
		m_proxyreq2->Ver = 5; 
		m_proxyreq2->Cmd = 1; 
		m_proxyreq2->Rsv = 0; 
		m_proxyreq2->Atyp = 1; 
		unsigned long tmpLong = inet_addr(ip); 
		unsigned short nport = ntohs(port);//GetPort()); 
		memcpy(m_proxyreq2->other,&tmpLong,4); 
		memcpy(m_proxyreq2->other+4,&nport,2); 
		ierr = send(s, buff,sizeof(struct sock5req2)+5, 0); 
		if( ierr < 0 || ierr != (sizeof( struct sock5req2)+5) )
		{
			closesocket( s );
			return 0;
		}
		struct sock5ans2 *m_proxyans2; 
		memset(buff,0,600); 
		m_proxyans2 = (struct sock5ans2 *)buff; 
		ierr = recv(s,buff,600, 0); 
		if( ierr  <= 0 )
		{
			closesocket( s );
			return 0;
		}
		if(m_proxyans2->Ver != 5 || m_proxyans2->Rep != 0) 
		{ 
			printf("通过代理连接主站不成功!\n"); 
			closesocket( s );
			return 0; 
		} 

	}
	else
	{
		struct	sockaddr_in ServAddr;
		m_pHost = gethostbyname(ip);
		if( m_pHost == NULL )
			return 0;
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if( s == INVALID_SOCKET )
			return 0;
		ServAddr.sin_family	= AF_INET;
		ServAddr.sin_addr.s_addr = *(ULONG *)m_pHost->h_addr_list[0];
		ServAddr.sin_port = htons(port);
		int erri = connect(s, (struct sockaddr *)&ServAddr, sizeof(ServAddr));
		if( erri == -1)
		{
			closesocket( s );
			return 0;
		}
	}
	return s;
}
//------------------------------------------------------------------------
void	CloseConnection( SOCKET s )
{
	LINGER lingerStruct;

	lingerStruct.l_onoff	= 1;
	lingerStruct.l_linger	= 0;

	setsockopt(s, SOL_SOCKET, SO_LINGER, (char *)&lingerStruct, sizeof(lingerStruct));
	closesocket( s );
}
//------------------------------------------------------------------------
SOCKET Listen(UINT port, int maxqueue)
{
	struct	sockaddr_in	serveraddr;
	SOCKET	s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( s == INVALID_SOCKET )
		return 0;

	memset( (void*)&serveraddr, 0, sizeof( struct sockaddr_in ));

	serveraddr.sin_family = PF_INET;
    serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	serveraddr.sin_port = htons( port );
	
	
	if( bind(s, (struct sockaddr * )&serveraddr, sizeof( struct sockaddr_in )) < 0 )
	{
		closesocket( s );
		return 0;
	}
	if( listen( s, maxqueue ) == SOCKET_ERROR )
	{	
		closesocket( s );
		return 0;
	}
	
	return s;
}
//------------------------------------------------------------------------
BOOL Accept(SOCKET sListen, SOCKET & sAccept)
{
	sockaddr_in	addr;
	int addrlen;
	addrlen = sizeof( addr );

	sAccept = accept( sListen, (sockaddr*)&addr, &addrlen );
	if( sAccept != INVALID_SOCKET )
	{
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------------
// 网络初始化
BOOL NetStartup(int ver1, int ver2)
{
	WSADATA m_wsaData;
	return (WSAStartup(MAKEWORD(ver1,ver2), &m_wsaData) != SOCKET_ERROR);
}
//------------------------------------------------------------------------
BOOL Accept(SOCKET sListen, SOCKET& sAccept, char* pszIpAddr, UINT& usPort)
{
	sockaddr_in	addr;
	int addrlen;
	addrlen = sizeof( addr );

	sAccept = accept( sListen, (sockaddr*)&addr, &addrlen );


	if( sAccept != INVALID_SOCKET )
	{
		usPort = htons( addr.sin_port );
		if( pszIpAddr != NULL )
			sprintf( pszIpAddr, "%u.%u.%u.%u", addr.sin_addr.S_un.S_addr & 0xff, (addr.sin_addr.S_un.S_addr & 0xff00)>>8, (addr.sin_addr.S_un.S_addr & 0xff0000)>>16, (addr.sin_addr.S_un.S_addr & 0xff000000)>>24 );
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------------
BOOL OpenConnection(const char * IpAddress ,const UINT Port, PCONNECTION pConnection, PROXY_SETTING * proxysetting )
{
	pConnection->Socket = OpenConnection( IpAddress, Port, proxysetting );
	if( pConnection->Socket == 0 )
		return FALSE;
	pConnection->Port = Port;
	strcpy( pConnection->IpAddress, IpAddress );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL Listen(UINT Port, int MaxQueue, PCONNECTION pConnection)
{
	if( (pConnection->Socket = Listen( Port, MaxQueue ))== 0 )
	{
		return FALSE;
	}
	pConnection->Port = Port;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL Accept(SOCKET sListen, PCONNECTION pConnection)
{
	return Accept( sListen, pConnection->Socket, pConnection->IpAddress, pConnection->Port );
}
//------------------------------------------------------------------------
BOOL CloseConnection(PCONNECTION pConnection)
{
	LINGER lingerStruct;

	lingerStruct.l_onoff	= 1;
	lingerStruct.l_linger	= 0;

	setsockopt(pConnection->Socket, SOL_SOCKET, SO_LINGER, (char *)&lingerStruct, sizeof(lingerStruct));

	return (closesocket( pConnection->Socket ) != SOCKET_ERROR );
}
//------------------------------------------------------------------------
BOOL SetNoBlock(PCONNECTION pConnection)
{
	return SetNoBlock(pConnection->Socket);
}
//------------------------------------------------------------------------
BOOL GetAddrByName( const char * pszHostName, char * pszIpAddress )
{
	LPHOSTENT m_pHost = gethostbyname(pszHostName);
	if( m_pHost == NULL )return FALSE;
	ULONG lAddr = *(ULONG *)m_pHost->h_addr_list[0];
	sprintf( pszIpAddress, "%u.%u.%u.%u", lAddr & 0xff, (lAddr & 0xff00)>>8, (lAddr & 0xff0000)>>16, (lAddr & 0xff000000)>>24 );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL OpenConnection(const char * IpAddress , const UINT Port, PCONNECTION pConnection, int nSeconds)
{
	LPHOSTENT m_pHost;
	SOCKET	s;
	struct	sockaddr_in ServAddr;
	m_pHost = gethostbyname(IpAddress);
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( s == INVALID_SOCKET	)
		return 0;
	SetNoBlock(s);
	ServAddr.sin_family	= AF_INET;
	ServAddr.sin_addr.s_addr = *(ULONG *)m_pHost->h_addr_list[0];
	ServAddr.sin_port = htons(Port);

	int erri = connect(s, (struct sockaddr *)&ServAddr, sizeof(ServAddr));
	if( erri == -1 )
	{
		if(  WSAGetLastError() == 10035 )
		{
			fd_set	fds;
			fds.fd_count = 0;
			FD_SET(s,&fds);
			timeval	tv;
			tv.tv_sec = nSeconds;
			tv.tv_usec = 0;
			select( 0, 0, &fds, 0,&tv );
			if(! FD_ISSET(s, &fds ))
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	pConnection->Socket = s;
	pConnection->Port = Port;
	strncpy( pConnection->IpAddress, IpAddress, 16 );
	pConnection->IpAddress[16] = '\0';
	return TRUE;
 }
//------------------------------------------------------------------------
BOOL UDPBind(char* szIpAddress, UINT uPort, PCONNECTION pConnection)
{
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	IPADDRESS	addr;

	if( s == INVALID_SOCKET )
		return FALSE;

	if( !BuildIpAddress(szIpAddress, uPort, addr))
	{
		return FALSE;
	}

	if( bind(s, (SOCKADDR*)&addr.addr, sizeof( addr.addr))== SOCKET_ERROR)
	{
		closesocket(s);
		return FALSE;
	}

	strncpy( pConnection->IpAddress, szIpAddress, 15 );
	pConnection->Port = uPort;
	pConnection->Socket = s;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL OpenConnection(const char * IpAddress , const UINT Port,const char * szProxyIpAddress , const UINT nProxyPort,const CHAR*szProxyUserName, const CHAR *szProxyPassword, UINT	nProxyType,  PCONNECTION pConnection )
{
	if( !OpenConnection( szProxyIpAddress, nProxyPort, pConnection ))
	{
		return FALSE;
	}
	char buff[600];
	struct sock5req1 *m_proxyreq1; 
	m_proxyreq1 = (struct sock5req1 *)buff; 
	m_proxyreq1->Ver = 5; 
	m_proxyreq1->nMethods = 2; 
	m_proxyreq1->Methods[0] = 0; 
	m_proxyreq1->Methods[1] = 2; 
	send(pConnection->Socket, buff,4, 0); 
	struct sock5ans1 *m_proxyans1; 
	m_proxyans1 = (struct sock5ans1 *)buff; 
	memset(buff,0,600); 
	recv(pConnection->Socket,buff,600, 0); 
	if(m_proxyans1->Ver != 5 || (m_proxyans1->Method!=0 && m_proxyans1->Method!=2)) 
	{ 
		printf("通过代理连接主站不成功!\n"); 
		CloseConnection(pConnection);
		return FALSE; 
	} 
	struct sock5req2 *m_proxyreq2; 
	m_proxyreq2 = (struct sock5req2 *)buff; 
	m_proxyreq2->Ver = 5; 
	m_proxyreq2->Cmd = 1; 
	m_proxyreq2->Rsv = 0; 
	m_proxyreq2->Atyp = 1; 
	unsigned long tmpLong = inet_addr(IpAddress); 
	unsigned short port = ntohs(Port);//GetPort()); 
	memcpy(m_proxyreq2->other,&tmpLong,4); 
	memcpy(m_proxyreq2->other+4,&port,2); 
	send(pConnection->Socket, buff,sizeof(struct sock5req2)+5, 0); 
	struct sock5ans2 *m_proxyans2; 
	memset(buff,0,600); 
	m_proxyans2 = (struct sock5ans2 *)buff; 
	recv(pConnection->Socket,buff,600, 0); 
	if(m_proxyans2->Ver != 5 || m_proxyans2->Rep != 0) 
	{ 
		printf("通过代理连接主站不成功!\n"); 
		CloseConnection(pConnection); 
		return FALSE; 
	} 
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	UDPSend( PCONNECTION pConnection, CHAR * szIpAddress, UINT	nPort, CHAR * pData, int len )
{
	IPADDRESS	addr;
	if( !BuildIpAddress( szIpAddress, nPort, addr) )
	{
		return FALSE;
	}
	return UDPSend(pConnection, addr, pData, len );
}
//------------------------------------------------------------------------
BOOL	UDPSend( PCONNECTION pConnection, IPADDRESS & addr, CHAR * pData, int len )
{
	if( sendto( pConnection->Socket, pData, len, 0, (SOCKADDR*)&addr.addr, sizeof( addr.addr) ) == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	BuildIpAddress( CHAR *pszIp, USHORT nPort, IPADDRESS & address )
{
	if( strlen( pszIp ) > 15 )
		return FALSE;
	strncpy( address.szIpAddress, pszIp, 15 );
	address.addr.sin_addr.s_addr = inet_addr( pszIp );
	address.addr.sin_family = AF_INET;
	address.addr.sin_port = htons( nPort );
	return TRUE;
}
//------------------------------------------------------------------------