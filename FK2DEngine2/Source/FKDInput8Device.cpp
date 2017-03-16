/**
*	created:		2013-4-23   20:23
*	filename: 		FKDInput8Device
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKLogger.h"
#include "../Include/FKDInput8Device.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace input
	{
		CDirectInput8DeviceKeyboard::~CDirectInput8DeviceKeyboard()
		{		
			freeKeyboard();
		}
		CDirectInput8DeviceKeyboard::CDirectInput8DeviceKeyboard()
		{
			lpdikey = NULL;
			nowKeys = & keys[0];
			lastKeys = & keys[1];
		}
		bool CDirectInput8DeviceKeyboard::initKeyboard(LPDIRECTINPUT8 lpdi8,HWND hwnd)
		{
			if (lpdikey == NULL)
			{
				if (FAILED (lpdi8->CreateDevice(GUID_SysKeyboard,&lpdikey,NULL)))
				{
					lpdikey = NULL;
					LogError( L"创建键盘设备驱动失败！");
					return false;
				}
				if (FAILED (lpdikey->SetCooperativeLevel(hwnd,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
				{
					lpdikey->Release();
					lpdikey = NULL;
					return false;
				}
				if (FAILED (lpdikey->SetDataFormat(&c_dfDIKeyboard)))
				{
					lpdikey->Release();
					lpdikey = NULL;
					return false;
				}
				if (FAILED (lpdikey ->Acquire()))
				{
					lpdikey->Release();
					lpdikey = NULL;
					return false;
				}
				nowKeys = & keys[0];
				lastKeys = & keys[1];
			}
			LogInfo( L"键盘设备初始化成功！");
			return true;
		}

		bool CDirectInput8DeviceKeyboard::freeKeyboard()
		{
			if (lpdikey != NULL)
			{
				lpdikey ->Unacquire();
				lpdikey ->Release();
				lpdikey = NULL;
				LogInfo( L"键盘设备释放成功！");
				return true;
			}
			return false;
		}

		bool CDirectInput8DeviceKeyboard::refreshDeviceState()
		{
			TKeysArray * temp = nowKeys;
			nowKeys = lastKeys;
			lastKeys = temp;
		
			if (lpdikey == NULL)
			{
				return false;
			}
			if (FAILED(lpdikey->GetDeviceState(256,(void *)(*nowKeys))))
			{
				return false;
			}
			return true;
		}

		void * CDirectInput8DeviceKeyboard::getDeviceData()
		{
			return nowKeys;
		}

		bool CDirectInput8DeviceKeyboard::getKeyState(int keyCode,E_BUTTON_STATE type)
		{
			switch (type)
			{
			case E_BUTTON_PRESSED:
				if (keyCode >= 0 && keyCode < 256)
				{
					if ((*nowKeys)[keyCode])
						return true;
				}
			break;
			case E_BUTTON_DOWN:
				if (keyCode >= 0 && keyCode < 256)
				{
					if ( (! (*lastKeys)[keyCode]) && (*nowKeys)[keyCode])
						return true;
				}
			break;
			case E_BUTTON_UP:
				if (keyCode >= 0 && keyCode < 256)
				{
					if ( (*lastKeys)[keyCode] && (! (*nowKeys)[keyCode]) )
						return true;
				}
			break;
			default :
				 return false;
			}
			return false;
		}

		CDirectInput8DeviceMouse::~CDirectInput8DeviceMouse()
		{
			freeMouse();
		}

		CDirectInput8DeviceMouse::CDirectInput8DeviceMouse()
		{
			lpdimouse = 0;
			nowMouse = & mouses[0];
			lastMouse = & mouses[1];
		}

		bool CDirectInput8DeviceMouse::initMouse(LPDIRECTINPUT8 lpdi8,HWND hwnd)
		{
			if (lpdimouse == NULL)
			{
				if (FAILED (lpdi8 ->CreateDevice(GUID_SysMouse,&lpdimouse,NULL)))
				{
					LogError( L"创建鼠标设备驱动失败！");
					lpdimouse = NULL;
					return false;
				}
				if (FAILED (lpdimouse ->SetCooperativeLevel(hwnd,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
				{
					lpdimouse->Release();
					lpdimouse = NULL;
					return false;
				}
				if (FAILED (lpdimouse ->SetDataFormat(&c_dfDIMouse)))
				{
					lpdimouse->Release();
					lpdimouse = NULL;
					return false;
				}
				if (FAILED (lpdimouse ->Acquire()))
					return false;
			}
			LogInfo( L"鼠标设备初始化成功！");
			return true;
		}

		bool CDirectInput8DeviceMouse::freeMouse()
		{
			if (lpdimouse != NULL)
			{
				lpdimouse ->Unacquire();
				lpdimouse ->Release();
				lpdimouse = NULL;
				LogInfo( L"鼠标设备释放成功！");
				return true;
			}
			return false;
		}
		bool CDirectInput8DeviceMouse::refreshDeviceState()
		{
			DIMOUSESTATE * temp = nowMouse;
			nowMouse = lastMouse;
			lastMouse = temp;
			if (lpdimouse == NULL)
			{
				return false;
			}
			if (FAILED (lpdimouse ->GetDeviceState(sizeof (DIMOUSESTATE),(void *)&(*nowMouse))))
			{
				return false;
			}
			return true;
		}
		void * CDirectInput8DeviceMouse::getDeviceData()
		{
			return nowMouse;
		}

		FK2DEngine2::math::Vector3 CDirectInput8DeviceMouse::getMouseRelativePos()
		{
			return FK2DEngine2::math::Vector3((float)(nowMouse->lX),(float)(nowMouse->lY),(float)(nowMouse->lZ));
		}

		bool CDirectInput8DeviceMouse::getMouseButtonState(int keyCode,E_BUTTON_STATE type)
		{
			switch (type)
			{
			case E_BUTTON_PRESSED:
				if (keyCode >= 0 && keyCode < 4)
				{
					if ((nowMouse->rgbButtons)[keyCode])
						return true;
				}
			break;
			case E_BUTTON_DOWN:
				if (keyCode >= 0 && keyCode < 4)
				{
					if ( (! (lastMouse->rgbButtons)[keyCode]) && (nowMouse->rgbButtons)[keyCode])
						return true;
				}
			break;
			case E_BUTTON_UP:
				if (keyCode >= 0 && keyCode < 4)
				{
					if ( (lastMouse->rgbButtons)[keyCode] && (! (nowMouse->rgbButtons)[keyCode]) )
						return true;
				}
			break;
			default :
				 return false;
			}
			return false;
		}
	}
}
//------------------------------------------------------------------------