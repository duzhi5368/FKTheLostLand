/**
*	created:		2013-4-16   5:13
*	filename: 		SCClientObj
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "clientobject.h"
//------------------------------------------------------------------------
// 与CenterServer通信	
class CSCClientObj : public CClientObject
{
public:
	CSCClientObj(void);
	virtual ~CSCClientObj(void);
public:
	void	Update();
	//	注册服务器
	VOID RegisterServer( SERVERADDR & Addr, ServerId & Id, const char * pszNickName );
	VOID UpdateInfo( DWORD dwConnections );
	VOID FindServer( UINT id, servertype type, const char * pszServerName );
	VOID GetGsList( UINT id );
	VOID SendMsgAcrossServer( UINT id, WORD wCmd, MAS_SENDTYPE sendtype, WORD wParam,char * pszData, int datasize );
	VOID GetGameServerAddr( UINT id, const char * pszServerName, const char * pszMapInfo );
	xPacket * GetPacket(){ return m_xPacketQueue.pop();}
};
//------------------------------------------------------------------------