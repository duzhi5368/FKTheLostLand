/**
*	created:		2013-4-11   21:33
*	filename: 		FKWindows
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKInputHandler.h"
#include "../../FKLogger.h"
#include "../Controls/FKCanvas.h"
//------------------------------------------------------------------------
#include <windows.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Input
	{
		class Windows
		{
			public:

				Windows()
				{
					m_Canvas = NULL;
					m_MouseX = 0;
					m_MouseY = 0;
				}

				void Initialize( FK2DEngine2::Controls::Canvas* c )
				{
					m_Canvas = c;
				}

				void GetMousePos( int& x, int& y)
				{
					x = m_MouseX;
					y = m_MouseY;
				}

				bool ProcessMessage( MSG msg )
				{
					if ( !m_Canvas ) { return false; }

					switch ( msg.message )
					{
						case WM_SYSCOMMAND:
							{
								if ( msg.message == WM_SYSCOMMAND && msg.wParam != SC_CLOSE )
								{ return false; }

								return m_Canvas->InputQuit();
							}

						case WM_MOUSEMOVE:
							{
								int x = ( signed short ) LOWORD( msg.lParam );
								int y = ( signed short ) HIWORD( msg.lParam );
								int dx = x - m_MouseX;
								int dy = y - m_MouseY;
								m_MouseX = x;
								m_MouseY = y;
								// LogInfo(L"%d %d %d %d", x, y, dx, dy);
								return m_Canvas->InputMouseMoved( x, y, dx, dy );
							}

						case WM_CHAR:
							{
								FK2DEngine2::UnicodeChar chr = ( FK2DEngine2::UnicodeChar ) msg.wParam;
								return m_Canvas->InputCharacter( chr );
							}

#ifdef WM_MOUSEWHEEL

						case WM_MOUSEWHEEL:
							{
								return m_Canvas->InputMouseWheel( ( short ) HIWORD( msg.wParam ) );
							}

#endif

						case WM_LBUTTONDOWN:
							{
								SetCapture( msg.hwnd );
								return m_Canvas->InputMouseButton( 0, true );
							}

						case WM_LBUTTONUP:
							{
								ReleaseCapture();
								return m_Canvas->InputMouseButton( 0, false );
							}

						case WM_RBUTTONDOWN:
							{
								SetCapture( msg.hwnd );
								return m_Canvas->InputMouseButton( 1, true );
							}

						case WM_RBUTTONUP:
							{
								ReleaseCapture();
								return m_Canvas->InputMouseButton( 1, false );
							}

						case WM_MBUTTONDOWN:
							{
								SetCapture( msg.hwnd );
								return m_Canvas->InputMouseButton( 2, true );
							}

						case WM_MBUTTONUP:
							{
								ReleaseCapture();
								return m_Canvas->InputMouseButton( 2, false );
							}

						case WM_LBUTTONDBLCLK:
						case WM_RBUTTONDBLCLK:
						case WM_MBUTTONDBLCLK:
							{
								return true;
							}

						case WM_KEYDOWN:
						case WM_KEYUP:
							{
								bool bDown = msg.message == WM_KEYDOWN;
								int iKey = -1;

								// 当 Ctrl 和 WM_CHAR 一同按下时的消息
								if ( bDown && GetKeyState( VK_CONTROL ) & 0x80 && msg.wParam >= 'A' && msg.wParam <= 'Z' )
								{
									FK2DEngine2::UnicodeChar chr = ( FK2DEngine2::UnicodeChar ) msg.wParam;
									return m_Canvas->InputCharacter( chr );
								}

								if ( msg.wParam == VK_SHIFT ) { iKey = FK2DEngine2::Key::Shift; }
								else if ( msg.wParam == VK_RETURN ) { iKey = FK2DEngine2::Key::Return; }
								else if ( msg.wParam == VK_BACK ) { iKey = FK2DEngine2::Key::Backspace; }
								else if ( msg.wParam == VK_DELETE ) { iKey = FK2DEngine2::Key::Delete; }
								else if ( msg.wParam == VK_LEFT ) { iKey = FK2DEngine2::Key::Left; }
								else if ( msg.wParam == VK_RIGHT ) { iKey = FK2DEngine2::Key::Right; }
								else if ( msg.wParam == VK_TAB ) { iKey = FK2DEngine2::Key::Tab; }
								else if ( msg.wParam == VK_SPACE ) { iKey = FK2DEngine2::Key::Space; }
								else if ( msg.wParam == VK_HOME ) { iKey = FK2DEngine2::Key::Home; }
								else if ( msg.wParam == VK_END ) { iKey = FK2DEngine2::Key::End; }
								else if ( msg.wParam == VK_CONTROL ) { iKey = FK2DEngine2::Key::Control; }
								else if ( msg.wParam == VK_SPACE ) { iKey = FK2DEngine2::Key::Space; }
								else if ( msg.wParam == VK_UP ) { iKey = FK2DEngine2::Key::Up; }
								else if ( msg.wParam == VK_DOWN ) { iKey = FK2DEngine2::Key::Down; }

								if ( iKey != -1 )
								{
									return m_Canvas->InputKey( iKey, bDown );
								}

								break;
							}

						default:
							{
								break;
							}
					}

					return false;
				}

			protected:

				FK2DEngine2::Controls::Canvas*	m_Canvas;
				int m_MouseX;
				int m_MouseY;

		};
	}
}
//------------------------------------------------------------------------