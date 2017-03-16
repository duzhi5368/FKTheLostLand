/**
*	created:		2013-4-15   22:41
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
typedef struct tagLOGINENTER
{
	tagLOGINENTER()
	{
		memset( this, 0, sizeof( *this));
	}
	CHAR	szAccount[12];
	UINT	nLid;
	UINT	nSid;
	DWORD	dwEnterTime;
	UINT	nListId;
}LOGINENTER;
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
	// 未加密消息
	VOID	OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size );
	// 加密消息
	VOID	OnCodedMsg( xClientObject * pObject, PMIRMSG pMsg, int datasize );
	// DBSvr消息
	VOID	OnDBMsg( PMIRMSG pMsg, int datasize );
	// CenterSvr消息
	VOID	OnSCMsg( PMIRMSG pMsg, int datasize );
	// GameSvr消息
	VOID	OnMASMsg( WORD wCmd, WORD wType, WORD wIndex, const char * pszData, int datasize );
	VOID	OnConnection();
protected:
	VOID	OnUnknownMsg( PMIRMSG pMsg, int datasize );
protected:
	UINT				m_nLoginId;
	UINT				m_nSelectId;
	LOGINENTER			m_EnterInfo;
	selcharserverstate	m_State;			// 客户端角色当前状态
	FINDSERVER_RESULT	m_GameServerAddr;
	UINT				m_nFailCount;
	CServerTimer		m_TimeOut;
	BOOL				m_bSelected;
	CHAR				m_szCharName[32];	// 角色名字
	BOOL				m_bWaitForVerify;
	CServerTimer		m_WaitForVerifyTimer;
};
//------------------------------------------------------------------------