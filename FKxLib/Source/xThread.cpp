/**
*	created:		2013-4-16   5:00
*	filename: 		xThread
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xthread.h"
//------------------------------------------------------------------------
xThread::xThread(void) : m_dwThreadID(0), m_hThread(INVALID_HANDLE_VALUE), 
m_bTerminated(FALSE), m_bIsSuspended(FALSE), m_lpParam( NULL )
{
}
//------------------------------------------------------------------------
xThread::~xThread(void)
{
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		if (m_bIsSuspended)
			Resume();
		Terminate();
		WaitFor();
	}
}
//------------------------------------------------------------------------
void xThread::WaitFor(void)
{
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(m_hThread, INFINITE);
	}
}
//------------------------------------------------------------------------
BOOL xThread::Start(LPVOID lpParam, BOOL bSuspended)
{
	unsigned int dwThreadID;
	int nFlag = 0;
	m_lpParam = lpParam;
	if (bSuspended)
	{
		nFlag = CREATE_SUSPENDED;
		m_bIsSuspended = TRUE;
	}
	else
		m_bIsSuspended = FALSE;

	HANDLE hThread = (HANDLE)CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadProc,
		(void*)this,
		nFlag,
		(LPDWORD)&dwThreadID);
	if (hThread == INVALID_HANDLE_VALUE)
		return FALSE;
	m_dwThreadID = dwThreadID;
	m_hThread = hThread;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL xThread::Resume(void)
{
	if (ResumeThread(m_hThread) != (DWORD)-1)
	{
		m_bIsSuspended = FALSE;
		return TRUE;
	}
	else
		return FALSE;
}
//------------------------------------------------------------------------
BOOL xThread::Suspend(void)
{
	if (SuspendThread(m_hThread) != (DWORD)-1)
	{
		m_bIsSuspended = TRUE;
		return TRUE;
	}
	else
		return FALSE;
}
//------------------------------------------------------------------------
BOOL xThread::IsTerminated(void)
{
	return m_bTerminated;
}
//------------------------------------------------------------------------
BOOL xThread::IsStarted(void)
{
	return m_hThread != INVALID_HANDLE_VALUE;
}
//------------------------------------------------------------------------
void xThread::Terminate(void)
{
	::InterlockedExchange((LONG *)&m_bTerminated,TRUE);
}
//------------------------------------------------------------------------
unsigned WINAPI xThread::ThreadProc(LPVOID pParam)
{
	xThread* pThread = (xThread*)pParam;
	::InterlockedExchange((LONG *)&(pThread->m_bTerminated),FALSE);
	srand( (UINT)pThread->getHandle() + timeGetTime() );
	BOOL	bException = FALSE;
	try
	{
		pThread->Execute(pThread->m_lpParam);
	}
	catch(...)
	{
		throw;
	}

	pThread->OnTerminated(bException);
	CloseHandle(pThread->m_hThread);
	pThread->m_hThread = INVALID_HANDLE_VALUE;
	pThread->m_dwThreadID = 0;
	pThread->m_bTerminated = TRUE;
	return 0;
}
//------------------------------------------------------------------------