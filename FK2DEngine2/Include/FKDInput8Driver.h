/**
*	created:		2013-4-23   20:17
*	filename: 		FKDInput8Driver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <objbase.h>
#include <dinput.h>

#include "FKIInputDriver.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace input
	{
		class CDirectInput8Driver : public IInputDriver
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CDirectInput8Driver";
			}
			virtual ~CDirectInput8Driver();
			CDirectInput8Driver(HWND hwnd);
			virtual bool initDriver(unsigned long deviceBits);
			virtual bool shutDriver();
		private:
			LPDIRECTINPUT8 lpdi8;
			HWND hwnd;
		};
	}
}
//------------------------------------------------------------------------