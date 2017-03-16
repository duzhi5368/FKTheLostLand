/**
*	created:		2013-4-23   20:00
*	filename: 		FKIInputDevice
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
#include "FKVector3.h"
#include "FKVector4.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace input
	{
		typedef enum
		{
			E_BUTTON_DOWN,
			E_BUTTON_UP,
			E_BUTTON_PRESSED
		}E_BUTTON_STATE;

		class IInputDevice : public FK2DEngine2::core::IBase
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"IInputDevice";
			}
			virtual ~IInputDevice(){}
		
			virtual bool refreshDeviceState() = 0; 
			virtual void * getDeviceData() = 0;
		};

		class IInputDeviceKeyboard : public IInputDevice
		{
		public:
			virtual const std::wstring getTypeInfo() const {
				return L"IInputDeviceKeyboard";
			}
			//! 获取键盘状态
			//!\params keyCode : 按键代号，参见FKKeyCode.h
			//!\params type: 按键状态
			//!\params type: E_BUTTON_DOWN			该键是否刚刚按下
			//!\params type: E_BUTTON_UP			该键是否刚刚释放
			//!\params type: E_BUTTON_PRESSED		该键是否处于按下状态
			virtual bool getKeyState(int keyCode,E_BUTTON_STATE type) = 0;
		};

		typedef enum 
		{
			E_MOUSE_BUTTON_LEFT = 0,
			E_MOUSE_BUTTON_RIGHT = 1,
			E_MOUSE_BUTTON_MIDDLE = 2
		}E_MOUSE_BUTTONS;

		class IInputDeviceMouse : public IInputDevice
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"IInputDeviceMouse";
			}
			//! 获取鼠标状态
			//\return : 鼠标相对位置
			virtual FK2DEngine2::math::Vector3 getMouseRelativePos() = 0;
			//! 获取鼠标按钮状态
			//!\params keyCode : 鼠标按键代号 E_MOUSE_BUTTONS
			//!\params type: 按键状态
			//!\params type: E_BUTTON_DOWN			该键是否刚刚按下
			//!\params type: E_BUTTON_UP			该键是否刚刚释放
			//!\params type: E_BUTTON_PRESSED		该键是否处于按下状态
			virtual bool getMouseButtonState(int keyCode,E_BUTTON_STATE type) = 0;
		};
	}
}
//------------------------------------------------------------------------