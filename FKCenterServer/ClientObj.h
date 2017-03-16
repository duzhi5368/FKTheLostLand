/**
*	created:		2013-4-15   22:01
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
typedef struct tagREGISTEREDSERVER
{
	char		szName[64];			// 连接的服务器名称
	ServerId	Ident;				// 服务器标示信息ID	
	SERVERADDR	Addr;				// 服务器IP信息
	int			iSendDBCount;		
	DWORD		dwConnections;
}REGISTEREDSERVER;
//------------------------------------------------------------------------
class CClientObj : public CClientObject
{
public:
	CClientObj(void);
	virtual ~CClientObj(void);
public:
	// 清理内部数据
	VOID	Clean();
	// 每帧更新
	VOID	Update();
	// 解析未加密消息
	VOID	OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size );
	// 解析加密消息
	VOID	OnCodedMsg( xClientObject * pObject, PMIRMSG	pMsg, int datasize );
	REGISTEREDSERVER * GetRegInfo(){ return &m_RegInfo;}
public:
	REGISTEREDSERVER m_RegInfo;
};
//------------------------------------------------------------------------