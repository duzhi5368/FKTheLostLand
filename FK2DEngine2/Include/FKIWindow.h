/**
*	created:		2013-4-23   20:45
*	filename: 		FKIWindow
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
#include "UI/Input/FKWindows.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace system
	{
		struct SWindowMessage
		{
			unsigned long windowHandle;
			unsigned long messageType;
			unsigned long paramW;
			unsigned long paramL;
		};
		typedef unsigned long (*TMessageFunc)(SWindowMessage & message);
		
		class IWindow : FK2DEngine2::core::IBase
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"IWindow";
			}
			virtual ~IWindow (){};
			virtual void setWindowName(const std::wstring & windowname) = 0;
			virtual bool isWindowActive() = 0;
			virtual bool peekMessage( FK2DEngine2::Input::Windows * uiInput ) = 0;
			virtual unsigned long getHandle() = 0;
		};
	}
}
//------------------------------------------------------------------------