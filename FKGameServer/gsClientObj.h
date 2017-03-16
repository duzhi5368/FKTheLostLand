/**
*	created:		2013-4-18   23:54
*	filename: 		gsClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
enum	e_sendmsg_rage
{
	SMR_AREA,
	SMR_AROUND,
	SMR_MAP,
	SMR_SERVER,
	SMR_WORLD,
	SMR_GROUP,
	SMR_GUILD,
};
//------------------------------------------------------------------------
class CHumanPlayer;
//------------------------------------------------------------------------
class CClientObj :
	public CClientObject
{
public:
	CClientObj(void);
	virtual ~CClientObj(void);
public:
	VOID	Clean();
	VOID	Update();
public:
	VOID	OnUnCodeMsg( xClientObject * pObject,char * pszMsg, int size );
	VOID	OnCodedMsg( xClientObject * pObject, PMIRMSG	pMsg, int datasize );
	VOID	OnDBMsg( PMIRMSG pMsg, int datasize );
public:
	// 用户未登录时收到消息
	VOID	OnVerifyString( char * pszString );
	VOID	OnDisconnect();
	VOID	OnConnection();
public:
	int		GetGmLevel(){ return m_iGmLevel;}
	const char * GetAccount(){ return m_EnterInfo.szAccount;}
	// 紧急保存
	VOID	EmergencySave();
	VOID	OnUnknownMsg( PMIRMSG pMsg, int datasize );
private:
	VOID	ProcClientMsg( PMIRMSG pMsg, int datasize );
	VOID	OnCommand( char * pszCommand );
	VOID	CreateTestItem(  char * pszName, BYTE btStdMode, BYTE btShape, WORD wImage, BYTE btFlag );
private:
	ENTERGAMESERVER		m_EnterInfo;
	gameserverusermode	m_State;
	CHumanPlayer *		m_pPlayer;
	CServerTimer		m_hlTimer;
	int					m_iGmLevel;
	BOOL				m_bScrollTextMode;
	BOOL				m_bNoticeMode;
	BOOL				m_bCompetlyQuit;
};
//------------------------------------------------------------------------