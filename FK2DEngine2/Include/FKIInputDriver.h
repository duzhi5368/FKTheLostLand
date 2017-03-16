/**
*	created:		2013-4-23   19:59
*	filename: 		FKIInputDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
#include "FKIInputDevice.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace input
	{
		typedef enum
		{
			E_INPUT_KEYBOARD	= 0x00000001,
			E_INPUT_MOUSE		= 0x00000002,
		}E_INPUT_DEVICE_BITS;

		const int maxJoystickCount = 1; 

		class IInputDriver : public FK2DEngine2::core::IBase
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"IInputDriver";
			}
			virtual ~IInputDriver(){}
			IInputDriver(){
				keyboard = NULL;
				mouse = NULL;
			}

			bool refreshDriverState(){
				if (keyboard != NULL)
					keyboard->refreshDeviceState();
				if (mouse != NULL)
					mouse->refreshDeviceState();
				return true;
			}

			IInputDeviceKeyboard * getKeyborad(){
				return keyboard;
			}
			IInputDeviceMouse * getMouse(){
				return mouse;
			}

			virtual bool initDriver(unsigned long deviceBits) = 0;
			virtual bool shutDriver() = 0;

		protected:
			IInputDeviceKeyboard * keyboard;
			IInputDeviceMouse * mouse;
		};
	}
}
//------------------------------------------------------------------------