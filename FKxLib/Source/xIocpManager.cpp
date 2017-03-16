/**
*	created:		2013-4-16   4:57
*	filename: 		xIocpManager
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xinc.h"
#include "..\Include\xiocpmanager.h"
#include "..\Include\xiocpworkthread.h"
//------------------------------------------------------------------------
xIocpManager::xIocpManager(void)
{
	m_hIocp = NULL;
	m_iIocpWorkThreadCount = 0;
	m_pIocpWorkThread = NULL;
}
//------------------------------------------------------------------------
xIocpManager::~xIocpManager(void)
{
	if( m_hIocp != NULL )
		CloseHandle( m_hIocp );
}
//------------------------------------------------------------------------
BOOL xIocpManager::Start()
{
	m_hIocp = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
	if( m_hIocp == NULL )
	{
		setError( -1, "创建完成端口失败，Errorcode = %d\n", GetLastError() );
		return FALSE;
	}

	SYSTEM_INFO	si;
	GetSystemInfo( &si );
	m_iIocpWorkThreadCount = si.dwNumberOfProcessors * 2;

	m_pIocpWorkThread = new xIocpWorkThread[m_iIocpWorkThreadCount];

	for( int i = 0;i < m_iIocpWorkThreadCount;i ++ )
	{
		m_pIocpWorkThread[i].setIocpHandle(m_hIocp);
		m_pIocpWorkThread[i].Start();
	}

	return TRUE;
}
//------------------------------------------------------------------------
VOID xIocpManager::Stop()
{
	for( int i = 0;i < m_iIocpWorkThreadCount;i ++ )
		m_pIocpWorkThread[i].Terminate();
	delete []m_pIocpWorkThread;
	CloseHandle( m_hIocp );

	m_hIocp = NULL;
}
//------------------------------------------------------------------------
BOOL xIocpManager::Bind( SOCKET socket, DWORD dwBindId )
{
	if( m_hIocp == NULL )
	{
		setError( -2, "绑定socket失败，完成端口没有初始化！" );
		return FALSE;
	}
	HANDLE hPort = CreateIoCompletionPort((HANDLE)socket, m_hIocp, dwBindId, 0 );
	return TRUE;
}
//------------------------------------------------------------------------