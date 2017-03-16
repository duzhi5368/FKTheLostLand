/**
*	created:		2013-4-28   2:17
*	filename: 		FKProcessLimit
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <Windows.h>
//------------------------------------------------------------------------
template<int nLimitCount>
class FKProcessLimitGuard
{
public:
	FKProcessLimitGuard()
	{
		m_hHandle = CreateSemaphore(NULL,nLimitCount,nLimitCount,L"FreeKnightGame");
		unsigned long sign = WaitForSingleObject(m_hHandle,0);
		m_bOwned = (m_hHandle != INVALID_HANDLE_VALUE && 0 == sign );
	}
	~FKProcessLimitGuard()
	{
		if (m_bOwned)
		{
			ReleaseSemaphore(m_hHandle,1,NULL);
		}

		if (m_hHandle)
		{
			CloseHandle(m_hHandle);
		}
	}

	bool IsOwned()
	{
		return m_bOwned;
	}

	static FKProcessLimitGuard* Instance()
	{ 
		static FKProcessLimitGuard processLimitGuard;
		return &processLimitGuard;
	}

private:
	bool m_bOwned;
	HANDLE m_hHandle;
};
//------------------------------------------------------------------------