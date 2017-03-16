/**
*	created:		2013-4-15   23:13
*	filename: 		Server
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "clientobj.h"
//------------------------------------------------------------------------
class CServer :
	public CBaseServer,
	public xIndexObjectPool<CClientObj>
{
public:
	CServer(void);
	virtual ~CServer(void);
public:
	void	OnInput( const char * pString ){	CBaseServer::OnInput( pString );}
	CClientObject * GetClientObject( UINT id ){ return getObject( id );}
	CClientObject * NewClientObject();
	VOID DeleteClientObject( CClientObject * pObject );
	BOOL InitServer(CSettingFile&);
	VOID CleanServer();
	VOID Update();
	VOID OnParseMsg( WORD wMsg );
public:
	static CServer * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CServer;
		return m_pInstance;
	}
protected:
	CServerTimer	m_xxShowTimer;
	DWORD	m_dwMsgTimes[DM_END];
	CAppDB	m_appDB;
	static CServer * m_pInstance;
	CIndexListEx<CClientObj/*, MAX_CLIENTOBJECT*/>	m_ClientObjects;
	char m_szServer[64];
	char m_szDatabase[64];
	char m_szAccount[64];
	char m_szPassword[64];
	char m_szWebDatabase[64];
};
//------------------------------------------------------------------------