/**
*	created:		2013-4-16   4:45
*	filename: 		xIocpWorkThread
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xThread.h"
//------------------------------------------------------------------------
class xIocpWorkThread :
	public xThread
{
public:
	xIocpWorkThread(void);
	xIocpWorkThread( HANDLE hIocp );
	virtual ~xIocpWorkThread(void);

	void	setIocpHandle( HANDLE hIocp )
	{
		m_hIocp = hIocp;
	}

protected:
	void Execute(LPVOID lpParam);
private:
	HANDLE	m_hIocp;
};
//------------------------------------------------------------------------