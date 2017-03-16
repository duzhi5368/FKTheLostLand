/**
*	created:		2013-4-11   19:42
*	filename: 		FKInputHandler
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <queue>
#include "FKExports.h"
#include "FKStructures.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class Base;
	}

	namespace Key
	{
		const unsigned char Invalid = 0;
		const unsigned char Return = 1;
		const unsigned char Backspace = 2;
		const unsigned char Delete = 3;
		const unsigned char Left = 4;
		const unsigned char Right = 5;
		const unsigned char Shift = 6;
		const unsigned char Tab = 7;
		const unsigned char Space = 8;
		const unsigned char Home = 9;
		const unsigned char End = 10;
		const unsigned char Control = 11;
		const unsigned char Up = 12;
		const unsigned char Down = 13;
		const unsigned char Escape = 14;
		const unsigned char Alt = 15;

		const unsigned char Count = 16;
	}

	namespace Input
	{
		namespace Message
		{
			enum
			{
				Copy,
				Paste,
				Cut,
				Undo,
				Redo,
				SelectAll
			};
		};

		bool FK_EXPORT IsKeyDown( int iKey );
		bool FK_EXPORT IsLeftMouseDown();
		bool FK_EXPORT IsRightMouseDown();
		FK2DEngine2::Point FK_EXPORT GetMousePosition();

		inline bool IsShiftDown() { return IsKeyDown( FK2DEngine2::Key::Shift ); }
		inline bool IsControlDown() { return IsKeyDown( FK2DEngine2::Key::Control ); }

		bool FK_EXPORT DoSpecialKeys( Controls::Base* pCanvas, FK2DEngine2::UnicodeChar chr );
		bool FK_EXPORT HandleAccelerator( Controls::Base* pCanvas, FK2DEngine2::UnicodeChar chr );

		void FK_EXPORT OnMouseMoved( Controls::Base* pCanvas, int x, int y, int deltaX, int deltaY );
		bool FK_EXPORT OnMouseClicked( Controls::Base* pCanvas, int iButton, bool bDown );
		bool FK_EXPORT OnKeyEvent( Controls::Base* pCanvas, int iKey, bool bDown );
		void FK_EXPORT OnCanvasThink( Controls::Base* pControl );

	};
}
//------------------------------------------------------------------------