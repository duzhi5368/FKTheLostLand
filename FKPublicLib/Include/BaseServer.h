/**
*	created:		2013-4-16   5:03
*	filename: 		BaseServer
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "virtualserver.h"
#include "clientobject.h"
#include "ioconsole.h"
#include "scclientobj.h"
#include "dbclientobj.h"
#include "baniplistex.h"
#include "inc.h"
#include "msgprocessor.h"
//------------------------------------------------------------------------
class CTempClient;
//------------------------------------------------------------------------
class CBaseServer :
	public CVirtualServer,public xEventListener,public CInputListener,
	public xThread, public CMsgProcessor
{
public:
	CBaseServer(void);
	virtual ~CBaseServer(void);

public:
	virtual VOID	GetServerState( SERVERSTATE & state );
	BOOL 			Start( CSettingFile & );
	BOOL 			Stop();
	VOID			UpdateTotalInfo();
public:
	VOID 			OnUnCodeMsg(  xClientObject * pObject, const char * pszMsg, int size );
	VOID 			OnCodedMsg(  xClientObject * pObject, PMIRMSG	pMsg, int datasize );

	virtual CClientObject * NewClientObject(){return NULL;}
	virtual VOID			DeleteClientObject( CClientObject * pObject ){}
	virtual CClientObject * GetClientObject( UINT id ){ return NULL;}
	virtual BOOL 			InitServer(CSettingFile &){return TRUE;}
	virtual VOID 			CleanServer(){}
	virtual VOID 			Update();
	virtual VOID 			OnDBMsg( PMIRMSG pMsg, int datasize ){}
	virtual VOID 			OnSCMsg( PMIRMSG pMsg, int datasize );
	virtual VOID 			OnSCServerReady(){}
	virtual VOID 			OnDBServerReady( int index ){}
	virtual void 			ConnectDBInit(){}
	virtual VOID 			OnMASMsg( WORD wCmd, WORD wType, WORD wIndex, const char * pszData, int datasize ){}

	virtual VOID			WillClose(){}
public:
	VOID					OnEvent( xEventSender * pSender, int iEvent, int iParam, LPVOID lpParam );
	UINT GetDisconnectId()
	{
		if( m_DisconnectQueue.GetCount() == 0 )return 0;
		UINT id = 0;
		if( m_DisconnectQueue.Pop(id) )
			return id;
		return 0;
	}
public:
	CIOConsole *	GetIoConsole(){return m_pIoConsole;}
	void 			SetIoConsole( const CIOConsole * pIoConsole ){ m_pIoConsole = (CIOConsole*)pIoConsole;}
	void 			SetServerName( const char * pServerName ){m_pServerName = (char*)pServerName;}
	const char *	GetServerName(){return m_pServerName;}
	void			SetNickName( const char * pNickName ){ strncpy( m_szNickName, pNickName, 64 );m_szNickName[63] = 0;}
	const char *	GetNickName(){return m_szNickName;}
	CDBClientObj * 	GetDBConnection( int index ){ if( index < 0 || index >= m_iDBServerCount ) return NULL;return &m_DBClientObjs[index];}
	CSCClientObj * 	GetSCConnection() { return &m_SCClientObj;}
	int				GetDBConnectionCount(){return m_iDBServerCount;}
	VOID			OnUnknownMsg( PMIRMSG pMsg, int datasize );
	ServerId &		GetServerId(){ return m_Ident;}
	SERVERADDR *	GetDBAddr( UINT index ){ if( index >= m_iDBServerCount )return NULL; return m_DBAddrs + index;}
	virtual VOID	OnInput( const char * pszString );
protected:
	VOID Execute(LPVOID lpParam );
	//	处理连接相关的事件，连上和断开
	VOID ProcConnectionEvent();
	//	更新sc的消息
	VOID UpdateSCServer();
	//	更新db的消息
	VOID UpdateDBServer();
	//	连接sc的服务器
	BOOL ConnectSCServer();
	//	连接db的服务器
	BOOL ConnectDBServer();
protected:
	CDQueue<UINT,1024>			m_DisconnectQueue;
	char						*m_pServerName;
	char						m_szNickName[64];
	CIOConsole					*m_pIoConsole;
	CSCClientObj				m_SCClientObj;
	CDBClientObj				m_DBClientObjs[2];
	servertype					m_Type;
	ServerId					m_Ident;
	SERVERADDR					m_ServerAddr;
	SERVERADDR					m_SCAddr;
	int							m_iDBServerCount;
	SERVERADDR					m_DBAddrs[2];

	SYSTEMTIME					m_stStartTime;
	BOOL						m_bStateInfoUpdated;
	FLOAT						m_fLoopTime;
	DWORD						m_dwLoopTimes;
	DWORD						m_dwLoopStartTime;
	DWORD						m_dwConnectedTimes;
	DWORD						m_dwDisconnectTimes;
	DWORD						m_dwLoopTimesAll;
	CHAR						m_szServerState[1024];
	DWORD						m_dwPreConnections;
	xObjectPool<CTempClient >	m_xTempClients;
	xPtrQueue<CTempClient>		m_xQTempClient;
	char						m_szBanIpFile[256];
	char						m_szTrustIpFile[256];
	CIpListEx 					m_BanList;
	CIpListEx 					m_TrustList;
	xIocpServer					m_xIocpServer;
};
//------------------------------------------------------------------------