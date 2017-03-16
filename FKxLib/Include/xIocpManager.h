/**
*	created:		2013-4-16   4:43
*	filename: 		xIocpManager
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class xIocpWorkThread;
//------------------------------------------------------------------------
class xIocpManager:public xError
{
public:
	xIocpManager(void);
	virtual ~xIocpManager(void);
	BOOL	Start();
	VOID	Stop();
	BOOL	Bind( SOCKET socket, DWORD dwBindId );
protected:
	HANDLE	m_hIocp;
	xIocpWorkThread *m_pIocpWorkThread;
	int	m_iIocpWorkThreadCount;
};
//------------------------------------------------------------------------