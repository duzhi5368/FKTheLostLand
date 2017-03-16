/**
*	created:		2013-4-18   23:46
*	filename: 		SaveToDBThread
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "SimpleDBConnection.h"
//------------------------------------------------------------------------
// 当前线程状态
enum	thread_state
{
	TS_CONNECTINGDBSERVER,		// 准备链接DBSvr
	TS_WAITING,					// 等待状态
	TS_RUNNING,					// 进行中
};
//------------------------------------------------------------------------
class CHumanPlayer;
class CSaveToDBThread :
	public CSimpleDBConnection,
	public xThread,
	public xSingletonClass<CSaveToDBThread>
{
public:
	CSaveToDBThread(void);
	virtual ~CSaveToDBThread(void);
public:
	VOID OnMsg( MIRMSG * pMsg, int datasize );
protected:
	// 保存指定玩家的全部信息
	VOID DoWithPlayer( CHumanPlayer * pPlayer );
	// 紧急服务器备份
	VOID Execute( LPVOID lpParam );
protected:
	CSimpleDBConnection * m_pxDBConnection;
	thread_state m_State;
};
//------------------------------------------------------------------------