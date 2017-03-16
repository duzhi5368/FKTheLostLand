/**
*	created:		2013-4-18   23:33
*	filename: 		Server
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "gsclientobj.h"
//------------------------------------------------------------------------
class CGameWorld;
//------------------------------------------------------------------------
#define MAX_CLIENTOBJECT	64
//------------------------------------------------------------------------
class CServer :
	public CBaseServer,
	public xIndexObjectPool<CClientObj>
{
public:
	CServer(void);
	virtual ~CServer(void);
public:
	void			OnInput( const char * pString );
	CClientObject * GetClientObject( UINT id ){ return getObject( id );}	
	CClientObject * NewClientObject();
	VOID			DeleteClientObject( CClientObject * pObject );
public:
	BOOL 			InitServer(CSettingFile&);
	VOID 			CleanServer();
	VOID 			Update();
public:
	VOID 			OnDBMsg( PMIRMSG pMsg, int datasize );
	VOID 			OnSCMsg( PMIRMSG pMsg, int datasize );
	VOID 			OnMASMsg( WORD wCmd, WORD wType, WORD wIndex,char * pszData, int datasize );
public:
	virtual void	ConnectDBInit();
	SERVER_ERROR	AddEnterAccount( UINT nLoginId, UINT nSelCharId, const char * pszAccount, const char * pszName, WORD wIndex );
	BOOL			GetEnterInfo( UINT nLoginId, UINT nSelCharId, const char * pszAccount, ENTERGAMESERVER & enterinfo );
public:
	static CServer * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CServer;
		return m_pInstance;
	}
public:
	// 服务器即将关闭
	VOID WillClose();
	// 保存全部玩家数据
	VOID SaveAllPlayerData();
	// 踢出全部玩家
	VOID KickAll();
	// 服务器被终止，保存玩家全部数据
	VOID OnTerminated(BOOL bExcepted = FALSE );
protected:
	BOOL												m_bWillClose;
	CIntHash<1024>										m_Inthash;
	CIndexListEx<ENTERGAMESERVER/*, MAX_CLIENTOBJECT*/>	m_EnterObjects;
	CIndexListEx<CClientObj/*, MAX_CLIENTOBJECT*/>		m_ClientObjects;
	CGameWorld *										m_pGameWorld;
private:
	static CServer *									m_pInstance;
};
//------------------------------------------------------------------------