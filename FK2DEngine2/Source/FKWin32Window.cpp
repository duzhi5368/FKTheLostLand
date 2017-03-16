/**
*	created:		2013-4-23   20:49
*	filename: 		FKWin32Window
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKWin32Window.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace system
	{
		static BOOL bHide = FALSE;		// ÊÇ·ñÒþ²Ø±¾´°¿Ú
		TMessageFunc CWin32Window::winFunc = CWin32Window::winMessageFunc;
		
		LRESULT CALLBACK WndProc(HWND hwnd , UINT msg ,WPARAM wparam , LPARAM lparam)
		{
			SWindowMessage message;
			message.windowHandle = (unsigned long)(hwnd); 
			message.messageType = msg;
			message.paramW = wparam;
			message.paramL = lparam;
			return CWin32Window::winFunc(message);
		}

		CWin32Window::CWin32Window(const std::wstring & windowName,HINSTANCE hInstance,int showCmd,int width,int height,DWORD style)
		{
			wcscpy(this->windowname,windowName.c_str());
			init(hInstance,showCmd);
			create(width,height,style);
		}

		void CWin32Window::setWindowName(const std::wstring & windowname)
		{
			wcscpy(this->windowname,windowname.c_str());
			SetWindowText(hwnd,this->windowname);
		}

		unsigned long CWin32Window::getHandle()
		{
			return (unsigned long)hwnd;
		}
		// ×¢²áÀÏ°å¼ü
		bool CWin32Window::RegisteHotKey( UINT p_unVk )
		{
			if( RegisterHotKey( hwnd,0xbbbb,0,p_unVk) == TRUE )
			{
				return true;
			}
			return false;
		}

		bool CWin32Window::isWindowActive()
		{
			return GetActiveWindow() == hwnd;
		}

		bool CWin32Window::peekMessage( FK2DEngine2::Input::Windows * uiInput )
		{
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if( uiInput )
				{
					uiInput->ProcessMessage( msg );
				}
				if (msg.message == WM_QUIT)
					return false;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return true;
		}

		void CWin32Window::init(HINSTANCE hinstance ,int showcmd)
		{
			this->hinstance = hinstance; 
			this ->showcmd = showcmd;

			wcex.cbClsExtra = 0;
			wcex.cbSize = sizeof(wcex);
			wcex.cbWndExtra = 0;
			wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
			wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
			wcex.hIcon = (HICON)LoadImage(NULL,L"Res\\FKGameIcon.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
			wcex.hIconSm = (HICON)LoadImage(NULL,L"Res\\FKGameIcon.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
			wcex.hInstance = hinstance;
			wcex.lpfnWndProc = FK2DEngine2::system::WndProc;
			wcex.lpszClassName = windowname;
			wcex.lpszMenuName = NULL;
			wcex.style = CS_VREDRAW | CS_HREDRAW;

			RegisterClassEx(&wcex);
		}

		void CWin32Window::create(int width,int height,DWORD style)
		{
			RECT rect;
			rect.left = 0; rect.top = 0; rect.right = width ; rect.bottom = height;
			AdjustWindowRectEx(&rect,style,false,0);
			hwnd = CreateWindowEx(0,windowname,windowname,style, CW_USEDEFAULT,CW_USEDEFAULT,rect.right - rect.left,rect.bottom - rect.top ,NULL,NULL,hinstance,0);
			RegisteHotKey();
			ShowWindow(hwnd,showcmd);
			UpdateWindow(hwnd);
		}
		
		
		unsigned long CWin32Window::winMessageFunc(SWindowMessage & message)
		{
			switch(message.messageType)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_HOTKEY:
				{
					ShowWindow( (HWND)(message.windowHandle),(bHide = !bHide) ? SW_HIDE : SW_SHOW);
				}
				break;
			case WM_SIZE:
				{
					// TODO:
				}	
				break;
			}
			return DefWindowProc((HWND)(message.windowHandle),message.messageType,message.paramW,message.paramL);
		}
	}
}
//------------------------------------------------------------------------