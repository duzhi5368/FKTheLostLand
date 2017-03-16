/**
*	created:		2013-4-23   20:50
*	filename: 		FKWin32Timer
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>

#include "../Include/FKWin32Timer.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace system
	{
		unsigned long CWin32Timer::getTime()
		{
			return timeGetTime();
		}

		void CWin32Timer::delay(unsigned long delayTime)
		{
			Sleep(delayTime);
		}

	}
}
//------------------------------------------------------------------------