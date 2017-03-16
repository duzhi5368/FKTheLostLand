/**
*	created:		2013-4-23   20:18
*	filename: 		FKDInput8Device
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

#include "FKIInputDevice.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace input
	{
		class CDirectInput8DeviceKeyboard : public IInputDeviceKeyboard
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CDirectInput8DeviceKeyboard";
			}
			virtual ~CDirectInput8DeviceKeyboard();
			CDirectInput8DeviceKeyboard();
			bool initKeyboard(LPDIRECTINPUT8 lpdi8,HWND hwnd);
			bool freeKeyboard();
			virtual bool refreshDeviceState(); 
			virtual void * getDeviceData();
			virtual bool getKeyState(int keyCode,E_BUTTON_STATE type);
		private:
			LPDIRECTINPUTDEVICE8 lpdikey;
			typedef UCHAR TKeysArray[256]; 
			TKeysArray keys[2];
			TKeysArray * lastKeys;
			TKeysArray * nowKeys;
		};

		class CDirectInput8DeviceMouse : public IInputDeviceMouse
		{
		public:
			virtual const std::wstring getTypeInfo() const {
				return L"CDirectInput8DeviceMouse";
			}
			virtual ~CDirectInput8DeviceMouse();
			CDirectInput8DeviceMouse();
			bool initMouse(LPDIRECTINPUT8 lpdi8,HWND hwnd);
			bool freeMouse();
			virtual bool refreshDeviceState(); 
			virtual void * getDeviceData();
			virtual FK2DEngine2::math::Vector3 getMouseRelativePos();
			virtual bool getMouseButtonState(int keyCode,E_BUTTON_STATE type);
		private:
			LPDIRECTINPUTDEVICE8 lpdimouse;
			DIMOUSESTATE mouses[2];
			DIMOUSESTATE * lastMouse;
			DIMOUSESTATE * nowMouse;
		};
	}
}
//------------------------------------------------------------------------