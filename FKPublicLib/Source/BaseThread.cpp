/**
*	created:		2013-4-16   5:25
*	filename: 		BaseThread
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/basethread.h"
#include <time.h>
#include <stdlib.h>
#include "../Include/inc.h"
//------------------------------------------------------------------------
int CBaseThread::m_nTreadCreated = 0;
int CBaseThread::m_nTreadRun = 0;
//------------------------------------------------------------------------
CBaseThread::CBaseThread(void)
{
	m_lpParam = NULL;
	m_hThread = NULL;
	m_hExitEvent = NULL;
	m_dwThreadId = 0;
	m_dwRunTimes = 0;
	m_dwRunTimesKilo = 0;
	GetLocalTime(&m_stStartTime);
}
//------------------------------------------------------------------------
CBaseThread::~CBaseThread(void)
{
	if( ThreadActive() )
	{
		SafeTerminate( 100 );
	}
}
//------------------------------------------------------------------------
// 线程处理函数
DWORD CBaseThread::ThreadProc(LPVOID lpParam)
{
	CBaseThread * pThread = (CBaseThread*)lpParam;
	DWORD	dwRet;
	pThread->OnStart();
	dwRet = pThread->Proc( pThread->m_lpParam );
	pThread->OnExit();
	return dwRet;
}
//------------------------------------------------------------------------
// 真正的线程处理函数
DWORD CBaseThread::Proc(LPVOID lpParam)
{
	return 0;
}
//------------------------------------------------------------------------
// 创建线程
HANDLE CBaseThread::Create(DWORD dwStackSize, LPVOID lpParam, DWORD* pId, DWORD	dwThreadPriorityLevel )
{
	m_lpParam = lpParam;
	m_hThread = CreateThread( NULL, dwStackSize, ( LPTHREAD_START_ROUTINE )ThreadProc, this, CREATE_SUSPENDED , &m_dwThreadId );
	if( m_hThread == NULL )
	{
		return NULL;
	}
	if( pId != NULL )
	{
		(*pId ) = m_dwThreadId;
	}
	if( dwThreadPriorityLevel != TL_NORMAL )
	{
		int	iClass = (dwThreadPriorityLevel & 0xffff0000)>>16;
		int	iLevel = dwThreadPriorityLevel & 0xffff;
		if( iClass != 0 )
		{
			SetPriorityClass(m_hThread, (DWORD)iClass);		//	
		}
		SetThreadPriority( m_hThread, iLevel );
	}
	ResumeThread(m_hThread);
	m_nTreadCreated ++;
	return m_hThread;
}
//------------------------------------------------------------------------
// 安全退出线程
BOOL CBaseThread::SafeTerminate( DWORD dwWaitTime )
{
	if( m_hExitEvent == NULL || m_hThread == NULL )
		return FALSE;
	SetEvent( m_hExitEvent );
	if( WaitForSingleObject( m_hThread, dwWaitTime )==WAIT_TIMEOUT)
	{
		WaitForSingleObject(m_hThread, INFINITE);
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CBaseThread::OnStart(void)
{
	srand((unsigned int)time(0));
	m_hExitEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	ResetEvent( m_hExitEvent );
	m_nTreadRun ++;
	m_dwRunTimes = 0;
	m_dwRunTimesKilo = 0;
	GetLocalTime( &m_stStartTime );
	return ;
}
//------------------------------------------------------------------------
VOID CBaseThread::OnExit(void)
{
	m_lpParam = NULL;
	m_hThread = NULL;
	m_hExitEvent = NULL;
	m_dwThreadId = 0;
	m_nTreadRun --;
	m_nTreadCreated --;
	return ;
}
//------------------------------------------------------------------------
BOOL CBaseThread::WaitForTerminate(void)
{
	WaitForSingleObject( m_hThread, INFINITE );
	return 0;
}
//------------------------------------------------------------------------
// 测试线程是否活跃
BOOL CBaseThread::ThreadActive(void)
{
	if( m_hThread == NULL )
	{
		return FALSE;
	}
	m_dwRunTimes ++;
	if( m_dwRunTimes >= 1000 )
	{
		m_dwRunTimes = 0;
		m_dwRunTimesKilo ++;
	}
	return (WaitForSingleObject( m_hExitEvent, 0 ) == WAIT_TIMEOUT);
}
//------------------------------------------------------------------------
// 暴力结束线程
BOOL CBaseThread::Terminate(void)
{
	if( !ThreadActive())
		return FALSE;
	TerminateThread( m_hThread, 0 );
	OnExit();
	m_nTreadRun--;
	m_nTreadCreated --;
	return TRUE;
}
//------------------------------------------------------------------------
VOID CBaseThread::GetTimeInfo( DWORD & dwRunTimes, DWORD & dwRunTimesKilo, DWORD & dwRunSeconds )
{
	dwRunTimes = m_dwRunTimes;
	dwRunTimesKilo = m_dwRunTimesKilo;
	SYSTEMTIME	stNow;
	GetLocalTime( &stNow );
	dwRunSeconds = GetT1toT2Second(m_stStartTime, stNow);
}
//------------------------------------------------------------------------