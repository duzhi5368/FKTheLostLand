/**
*	created:		2013-4-14   20:50
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
	virtual VOID	OnSCMsg( PMIRMSG pMsg, int datasize );
	void			OnInput( const char * pString );
	CClientObject * GetClientObject( UINT id ){ return getObject( id ); }
	CClientObject * NewClientObject();
	VOID			DeleteClientObject( CClientObject * pObject );
	BOOL 			InitServer(CSettingFile&);
	VOID 			CleanServer();
	VOID 			Update();
public:
	static CServer * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CServer;
		return m_pInstance;
	}
	BOOL RegisterDisabled()
	{
		return m_bDisableRegister;
	}
	const char * GetServerTips(){ return m_pszServerTips==NULL?"":m_pszServerTips;}
	const char * GetLoginOkTips(){ return m_pszLoginOkTips==NULL?"":m_pszLoginOkTips;}
	const char * GetRegisterTips(){ return m_pszRegisterTips==NULL?"":m_pszRegisterTips;}
protected:
	char											*m_pszServerTips;
	char											*m_pszLoginOkTips;
	char											*m_pszRegisterTips;
	BOOL											m_bDisableRegister;
	static CServer									*m_pInstance;
	CIndexListEx<CClientObj/*, MAX_CLIENTOBJECT*/>	m_ClientObjects;
};
//------------------------------------------------------------------------