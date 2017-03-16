/**
*	created:		2013-4-14   20:50
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CClientObj : public CClientObject
{
public:
	CClientObj(void);
	virtual ~CClientObj(void);
	VOID	Clean();
	VOID	Update();
	// 未加密消息
	VOID	OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size );
	// 加密消息
	VOID	OnCodedMsg( xClientObject * pObject, PMIRMSG	pMsg, int datasize );
	// DB发送来的消息
	VOID	OnDBMsg( PMIRMSG pMsg, int datasize );
	// 服务器中心过来的消息
	VOID	OnSCMsg( PMIRMSG pMsg, int datasize );
	// Game服务器过来的消息
	VOID	OnMASMsg( WORD wCmd, WORD wType, WORD wIndex, const char * pszData, int datasize );

	VOID	OnConnection();
protected:
	VOID	SendMsgHook( DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpData = NULL, int datasize = -1 );
private:
	VOID	OnUnknownMsg( PMIRMSG pMsg, int datasize );
private:
	FINDSERVER_RESULT	m_SelectCharServer;
	CHAR	m_szAccount[20];
	UINT	m_nLid;
	UINT	m_nSid;
	UINT	m_nFailCount;
	CServerTimer m_TimeOut;
};
//------------------------------------------------------------------------