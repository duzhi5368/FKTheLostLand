/**
*	created:		2013-4-11   22:18
*	filename: 		FKInputHandler
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
#define DOUBLE_CLICK_SPEED 0.5f
#define MAX_MOUSE_BUTTONS 5
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
struct Action
{
	unsigned char type;

	int x, y;
	FK2DEngine2::UnicodeChar chr;
};
//------------------------------------------------------------------------
static const float KeyRepeatRate = 0.03f;
static const float KeyRepeatDelay = 0.3f;
//------------------------------------------------------------------------
struct t_KeyData
{
	t_KeyData()
	{
		for ( int i = 0; i < FK2DEngine2::Key::Count; i++ )
		{
			KeyState[i] = false;
			NextRepeat[i] = 0;
		}

		Target = NULL;
		LeftMouseDown = false;
		RightMouseDown = false;
	}

	bool KeyState[ FK2DEngine2::Key::Count ];
	float NextRepeat[ FK2DEngine2::Key::Count ];
	Controls::Base* Target;
	bool LeftMouseDown;
	bool RightMouseDown;

} KeyData;
//------------------------------------------------------------------------
FK2DEngine2::Point	MousePosition;
//------------------------------------------------------------------------
static float				g_fLastClickTime[MAX_MOUSE_BUTTONS];
static FK2DEngine2::Point	g_pntLastClickPos;
//------------------------------------------------------------------------
enum
{
	ACT_MOUSEMOVE,
	ACT_MOUSEBUTTON,
	ACT_CHAR,
	ACT_MOUSEWHEEL,
	ACT_KEYPRESS,
	ACT_KEYRELEASE,
	ACT_MESSAGE
};
//------------------------------------------------------------------------
void UpdateHoveredControl( Controls::Base* pInCanvas )
{
	Controls::Base* pHovered = pInCanvas->GetControlAt( MousePosition.x, MousePosition.y );

	if ( pHovered != FK2DEngine2::HoveredControl )
	{
		if ( FK2DEngine2::HoveredControl )
		{
			Controls::Base* OldHover = FK2DEngine2::HoveredControl;
			FK2DEngine2::HoveredControl = NULL;
			OldHover->OnMouseLeave();
		}

		FK2DEngine2::HoveredControl = pHovered;

		if ( FK2DEngine2::HoveredControl )
		{
			FK2DEngine2::HoveredControl->OnMouseEnter();
		}
	}

	if ( FK2DEngine2::MouseFocus && FK2DEngine2::MouseFocus->GetCanvas() == pInCanvas )
	{
		if ( FK2DEngine2::HoveredControl )
		{
			Controls::Base* OldHover = FK2DEngine2::HoveredControl;
			FK2DEngine2::HoveredControl = NULL;
			OldHover->Redraw();
		}

		FK2DEngine2::HoveredControl = FK2DEngine2::MouseFocus;
	}
}
//------------------------------------------------------------------------
bool FindKeyboardFocus( Controls::Base* pControl )
{
	if ( !pControl ) { return false; }

	if ( pControl->GetKeyboardInputEnabled() )
	{
		for ( Controls::Base::List::iterator iter = pControl->Children.begin(); iter != pControl->Children.end(); ++iter )
		{
			Controls::Base* pChild = *iter;

			if ( pChild == FK2DEngine2::KeyboardFocus )
			{ return false; }
		}

		pControl->Focus();
		return true;
	}

	return FindKeyboardFocus( pControl->GetParent() );
}
//------------------------------------------------------------------------
FK2DEngine2::Point FK2DEngine2::Input::GetMousePosition()
{
	return MousePosition;
}
//------------------------------------------------------------------------
void FK2DEngine2::Input::OnCanvasThink( Controls::Base* pControl )
{
	if ( FK2DEngine2::MouseFocus && !FK2DEngine2::MouseFocus->Visible() )
	{ FK2DEngine2::MouseFocus = NULL; }

	if ( FK2DEngine2::KeyboardFocus && ( !FK2DEngine2::KeyboardFocus->Visible() ||  !KeyboardFocus->GetKeyboardInputEnabled() ) )
	{ FK2DEngine2::KeyboardFocus = NULL; }

	if ( !KeyboardFocus ) { return; }

	if ( KeyboardFocus->GetCanvas() != pControl ) { return; }

	float fTime = FK2DEngine2::Platform::GetTimeInSeconds();

	for ( int i = 0; i < FK2DEngine2::Key::Count; i++ )
	{
		if ( KeyData.KeyState[i] && KeyData.Target != KeyboardFocus )
		{
			KeyData.KeyState[i] = false;
			continue;
		}

		if ( KeyData.KeyState[i] && fTime > KeyData.NextRepeat[i] )
		{
			KeyData.NextRepeat[i] = FK2DEngine2::Platform::GetTimeInSeconds() + KeyRepeatRate;

			if ( KeyboardFocus )
			{
				KeyboardFocus->OnKeyPress( i );
			}
		}
	}
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::IsKeyDown( int iKey )
{
	return KeyData.KeyState[ iKey ];
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::IsLeftMouseDown()
{
	return KeyData.LeftMouseDown;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::IsRightMouseDown()
{
	return KeyData.RightMouseDown;
}
//------------------------------------------------------------------------
void FK2DEngine2::Input::OnMouseMoved( Controls::Base* pCanvas, int x, int y, int /*deltaX*/, int /*deltaY*/ )
{
	MousePosition.x = x;
	MousePosition.y = y;
	UpdateHoveredControl( pCanvas );
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::OnMouseClicked( Controls::Base* pCanvas, int iMouseButton, bool bDown )
{
	if ( bDown && ( !FK2DEngine2::HoveredControl || !FK2DEngine2::HoveredControl->IsMenuComponent() ) )
	{
		pCanvas->CloseMenus();
	}

	if ( !FK2DEngine2::HoveredControl ) { return false; }

	if ( FK2DEngine2::HoveredControl->GetCanvas() != pCanvas ) { return false; }

	if ( !FK2DEngine2::HoveredControl->Visible() ) { return false; }

	if ( FK2DEngine2::HoveredControl == pCanvas ) { return false; }

	if ( iMouseButton > MAX_MOUSE_BUTTONS )
	{ return false; }

	if ( iMouseButton == 0 )		{ KeyData.LeftMouseDown = bDown; }
	else if ( iMouseButton == 1 )	{ KeyData.RightMouseDown = bDown; }

	bool bIsDoubleClick = false;

	if ( bDown &&
			g_pntLastClickPos.x == MousePosition.x &&
			g_pntLastClickPos.y == MousePosition.y &&
			( FK2DEngine2::Platform::GetTimeInSeconds() - g_fLastClickTime[ iMouseButton ] ) < DOUBLE_CLICK_SPEED )
	{
		bIsDoubleClick = true;
	}

	if ( bDown && !bIsDoubleClick )
	{
		g_fLastClickTime[ iMouseButton ] = FK2DEngine2::Platform::GetTimeInSeconds();
		g_pntLastClickPos = MousePosition;
	}

	if ( bDown )
	{
		if ( !FindKeyboardFocus( FK2DEngine2::HoveredControl ) )
		{
			if ( FK2DEngine2::KeyboardFocus )
			{ FK2DEngine2::KeyboardFocus->Blur(); }
		}
	}

	FK2DEngine2::HoveredControl->UpdateCursor();

	if ( bDown )
	{ FK2DEngine2::HoveredControl->Touch(); }


	if ( bDown )
	{
		if ( Hook::CallHook( &Hook::BaseHook::OnControlClicked, 
			FK2DEngine2::HoveredControl, MousePosition.x, MousePosition.y ) )
		{ return true; }
	}

	switch ( iMouseButton )
	{
		case 0:
			{
				if ( DragAndDrop::OnMouseButton( FK2DEngine2::HoveredControl, MousePosition.x, MousePosition.y, bDown ) )
				{ return true; }

				if ( bIsDoubleClick )	{ FK2DEngine2::HoveredControl->OnMouseDoubleClickLeft( MousePosition.x, MousePosition.y ); }
				else					{ FK2DEngine2::HoveredControl->OnMouseClickLeft( MousePosition.x, MousePosition.y, bDown ); }

				return true;
			}

		case 1:
			{
				if ( bIsDoubleClick )	{ FK2DEngine2::HoveredControl->OnMouseDoubleClickRight( MousePosition.x, MousePosition.y ); }
				else					{ FK2DEngine2::HoveredControl->OnMouseClickRight( MousePosition.x, MousePosition.y, bDown ); }

				return true;
			}
	}

	return false;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::HandleAccelerator( Controls::Base* pCanvas, FK2DEngine2::UnicodeChar chr )
{
	FK2DEngine2::UnicodeString accelString;

	if ( FK2DEngine2::Input::IsControlDown() )
	{ accelString += L"CTRL+"; }

	if ( FK2DEngine2::Input::IsShiftDown() )
	{ accelString += L"SHIFT+"; }

	chr = towupper( chr );
	accelString += chr;

	if ( FK2DEngine2::KeyboardFocus && FK2DEngine2::KeyboardFocus->HandleAccelerator( accelString ) )
	{ return true; }

	if ( FK2DEngine2::MouseFocus && FK2DEngine2::MouseFocus->HandleAccelerator( accelString ) )
	{ return true; }

	if ( pCanvas->HandleAccelerator( accelString ) )
	{ return true; }

	return false;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::DoSpecialKeys( Controls::Base* pCanvas, FK2DEngine2::UnicodeChar chr )
{
	if ( !FK2DEngine2::KeyboardFocus ) { return false; }

	if ( FK2DEngine2::KeyboardFocus->GetCanvas() != pCanvas ) { return false; }

	if ( !FK2DEngine2::KeyboardFocus->Visible() ) { return false; }

	if ( !FK2DEngine2::Input::IsControlDown() ) { return false; }

	if ( chr == L'C' || chr == L'c' )
	{
		FK2DEngine2::KeyboardFocus->OnCopy( NULL );
		return true;
	}

	if ( chr == L'V' || chr == L'v' )
	{
		FK2DEngine2::KeyboardFocus->OnPaste( NULL );
		return true;
	}

	if ( chr == L'X' || chr == L'x' )
	{
		FK2DEngine2::KeyboardFocus->OnCut( NULL );
		return true;
	}

	if ( chr == L'A' || chr == L'a' )
	{
		FK2DEngine2::KeyboardFocus->OnSelectAll( NULL );
		return true;
	}

	return false;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Input::OnKeyEvent( Controls::Base* pCanvas, int iKey, bool bDown )
{
	FK2DEngine2::Controls::Base* pTarget = FK2DEngine2::KeyboardFocus;

	if ( pTarget && pTarget->GetCanvas() != pCanvas ) { pTarget = NULL; }

	if ( pTarget && !pTarget->Visible() ) { pTarget = NULL; }

	if ( bDown )
	{
		if ( !KeyData.KeyState[ iKey ] )
		{
			KeyData.KeyState[ iKey ] = true;
			KeyData.NextRepeat[ iKey ] = FK2DEngine2::Platform::GetTimeInSeconds() + KeyRepeatDelay;
			KeyData.Target = pTarget;

			if ( pTarget )
			{ return pTarget->OnKeyPress( iKey ); }
		}
	}
	else
	{
		if ( KeyData.KeyState[ iKey ] )
		{
			KeyData.KeyState[ iKey ] = false;

			if ( pTarget )
			{ return pTarget->OnKeyRelease( iKey ); }
		}
	}

	return false;
}
//------------------------------------------------------------------------