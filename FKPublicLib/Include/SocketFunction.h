/**
*	created:		2013-4-16   5:15
*	filename: 		SocketFunction
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "inc.h"
#include <Mswsock.h>
#pragma comment( lib, "mswsock.lib" )
//------------------------------------------------------------------------
typedef struct _connectioninfo_
{
	SOCKET	Socket;
	CHAR	IpAddress[20];
	UINT	Port;
}CONNECTION,*PCONNECTION;
//------------------------------------------------------------------------
typedef struct _serverinitinfo_
{
	CHAR	WanIp[20];		//	广域网绑定IP
	CHAR	LanIp[20];		//	局域网绑定IP
	UINT	WanPort;		//	广域网监听端口
	UINT	LanPort;		//	局域网监听端口
	DWORD	dwParam[16];	//	参数表
}SERVERINITINFO, *PSERVERINITINFO;
//------------------------------------------------------------------------
typedef struct
{
	SOCKADDR_IN	addr;
	CHAR	szIpAddress[16];
}IPADDRESS;
//------------------------------------------------------------------------
typedef enum 
{
	PROXY_SOCKS5,
}PROXY_TYPE;
//------------------------------------------------------------------------
typedef struct _proxy_setting_
{
	PROXY_TYPE	type;
	CHAR	szProxyIp[20];
	UINT	nPort;
	CHAR	szUsername[256];
	CHAR	szPassword[256];
}PROXY_SETTING;
//------------------------------------------------------------------------
struct sock5req1 
{ 
	char Ver; 
	char nMethods; 
	char Methods[255]; 
}; 
//------------------------------------------------------------------------
struct sock5ans1 
{ 
	char Ver; 
	char Method; 
}; 
//------------------------------------------------------------------------
struct sock5req2 
{ 
	char Ver; 
	char Cmd; 
	char Rsv; 
	char Atyp; 
	char other[1]; 
}; 
//------------------------------------------------------------------------
struct sock5ans2 
{ 
	char Ver; 
	char Rep; 
	char Rsv; 
	char Atyp; 
	char other[1]; 
}; 
//------------------------------------------------------------------------
struct authreq 
{ 
	char Ver; 
	char Ulen; 
	char Name[255]; 
	char PLen; 
	char Pass[255]; 
}; 
//------------------------------------------------------------------------
struct authans 
{ 
	char Ver; 
	char Status; 
}; 
//------------------------------------------------------------------------
int		SetNoBlock( SOCKET s );
int		SetBlock( SOCKET s );
void	CloseConnection( SOCKET s );
SOCKET	OpenConnection( const char * ip, const UINT port, PROXY_SETTING * proxysetting = NULL );
SOCKET	Listen( UINT port, int maxqueue );
BOOL	NetCleanup();
BOOL	NetStartup();
BOOL	NetStartup(int ver1, int ver2);
BOOL	Accept(SOCKET sListen, SOCKET & sAccept);
BOOL	Accept(SOCKET sListen, SOCKET& sAccept, char* pszIpAddr, UINT& usPort);
BOOL	OpenConnection(const char * IpAddress , const UINT Port, PCONNECTION pConnection, PROXY_SETTING * proxysetting = NULL );
BOOL	OpenConnection(const char * IpAddress , const UINT Port, PCONNECTION pConnection, int nSeconds);
BOOL	OpenConnection(const char * IpAddress , const UINT Port,const char * szProxyIpAddress , const UINT nProxyPort,const CHAR*szProxyUserName, const CHAR *szProxyPassword, UINT	nProxyType,  PCONNECTION pConnection );
BOOL	Listen(UINT Port, int MaxQueue, PCONNECTION pConnection);
BOOL	Accept(SOCKET sListen, PCONNECTION pConnection);
BOOL	CloseConnection(PCONNECTION pConnection);
BOOL	SetNoBlock(PCONNECTION pConnection);
BOOL	UDPBind(char* szIpAddress, UINT uPort, PCONNECTION pConnection);
BOOL	UDPSend( PCONNECTION pConnection, CHAR * szIpAddress, UINT	nPort, CHAR * pData, int len );
BOOL	UDPSend( PCONNECTION pConnection, IPADDRESS & addr, CHAR * pData, int len );
BOOL	BuildIpAddress( CHAR *pszIp, USHORT nPort, IPADDRESS & address );
BOOL	GetAddrByName( const char * pszHostName, char * pszIpAddress );
//------------------------------------------------------------------------