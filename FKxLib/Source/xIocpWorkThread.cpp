#include "..\Include\xiocpworkthread.h"
#include "..\Include\xIocpUnit.h"
xIocpWorkThread::xIocpWorkThread(void)
{
	m_hIocp = NULL;
}

xIocpWorkThread::xIocpWorkThread( HANDLE hIocp )
{
	m_hIocp = hIocp;
}

xIocpWorkThread::~xIocpWorkThread(void)
{
}

void xIocpWorkThread::Execute(LPVOID lpParam)
{
	DWORD	dwNumberOfBytes = 0;
	ULONG_PTR	ulCompletionKey = 0;
	IOCP_UNIT	* pIocpunit;
	while( !xThread::IsTerminated() )
	{
		//BOOL GetQueuedCompletionStatus(
		//	HANDLE CompletionPort,
		//	LPDWORD lpNumberOfBytes,
		//	PULONG_PTR lpCompletionKey,
		//	LPOVERLAPPED* lpOverlapped,
		//	DWORD dwMilliseconds
		//	);

		if( GetQueuedCompletionStatus(						m_hIocp, 
															&dwNumberOfBytes, 
															&ulCompletionKey,
															(LPOVERLAPPED*)&pIocpunit,
															0 ) )
		{
			//if( pIocpunit == NULL )
			//{
			//	Sleep( 1 );
			//	continue;
			//}
			pIocpunit->pUnit->OnComplete( dwNumberOfBytes, (DWORD)ulCompletionKey );
		}
		else
		{
			if( pIocpunit != NULL )
			{
				pIocpunit->pUnit->OnComplete( 0, 0 );
			}
			Sleep( 1 );
		}
	}
}