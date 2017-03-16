/**
*	created:		2013-4-23   20:47
*	filename: 		FKWin32Timer
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKITimer.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace system
	{
		class CWin32Timer : public ITimer
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CWin32TImer";
			}
		protected:
			virtual unsigned long getTime();
			virtual void delay(unsigned long delayTime);
		};
	}
}
//------------------------------------------------------------------------