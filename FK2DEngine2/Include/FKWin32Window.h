/**
*	created:		2013-4-23   20:46
*	filename: 		FKWin32Window
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <windows.h>
#include "FKIWindow.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace system
	{
		LRESULT CALLBACK WndProc(HWND hwnd , UINT msg ,WPARAM wparam , LPARAM lparam);

		class CWin32Window : public IWindow
		{
			friend LRESULT CALLBACK WndProc(HWND hwnd , UINT msg ,WPARAM wparam , LPARAM lparam);
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CWin32Window";
			}
			CWin32Window(const std::wstring & windowName,HINSTANCE hInstance,int showCmd,int width,int height,DWORD style);
			virtual void setWindowName(const std::wstring & windowname);
			virtual bool isWindowActive();
			virtual bool peekMessage( FK2DEngine2::Input::Windows * uiInput );
			// »ñÈ¡´°¿Ú¾ä±ú
			virtual unsigned long getHandle();
			// ×¢²áÀÏ°å¼ü
			virtual bool RegisteHotKey( UINT p_unVk = VK_F3 );
		protected :
			void init(HINSTANCE hinstance ,int showcmd);
			void create(int width,int height,DWORD style);
			static unsigned long winMessageFunc(SWindowMessage & message);
		private:
			HINSTANCE	hinstance ;
			HWND		hwnd;
			WNDCLASSEX	wcex;
			MSG			msg;
			int			showcmd;
			wchar_t		windowname[255];
			int			width;
			int			height;
			DWORD		style;
		public:
			static TMessageFunc winFunc;
		};
	}
}
//------------------------------------------------------------------------