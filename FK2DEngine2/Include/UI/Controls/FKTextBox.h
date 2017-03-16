/**
*	created:		2013-4-11   20:32
*	filename: 		FKTextBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "FKLabel.h"
#include "FKScrollControl.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT TextBox : public Label
		{
				FK_CONTROL( TextBox, Label );

				virtual void Render( Skin::Base* skin );
				virtual void RenderFocus( FK2DEngine2::Skin::Base* /*skin*/ ) {};
				virtual void Layout( Skin::Base* skin );
				virtual void PostLayout( Skin::Base* skin );

				virtual void UpdateCaretColor();

				virtual bool OnChar( FK2DEngine2::UnicodeChar c );

				virtual void InsertText( const FK2DEngine2::UnicodeString & str );
				virtual void DeleteText( int iStartPos, int iLength );

				virtual void RefreshCursorBounds();

				virtual bool OnKeyReturn( bool bDown );
				virtual bool OnKeyBackspace( bool bDown );
				virtual bool OnKeyDelete( bool bDown );
				virtual bool OnKeyRight( bool bDown );
				virtual bool OnKeyLeft( bool bDown );
				virtual bool OnKeyHome( bool bDown );
				virtual bool OnKeyEnd( bool bDown );

				virtual bool AccelOnlyFocus() { return true; }

				virtual void OnPaste( FK2DEngine2::Controls::Base* pCtrl );
				virtual void OnCopy( FK2DEngine2::Controls::Base* pCtrl );
				virtual void OnCut( FK2DEngine2::Controls::Base* pCtrl );
				virtual void OnSelectAll( FK2DEngine2::Controls::Base* pCtrl );

				virtual void OnMouseDoubleClickLeft( int x, int y );

				virtual void EraseSelection();
				virtual bool HasSelection();
				virtual UnicodeString GetSelection();

				virtual void SetCursorPos( int i );
				virtual void SetCursorEnd( int i );

				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );

				virtual void SetSelectAllOnFocus( bool b ) { m_bSelectAll = b; if ( b ) { OnSelectAll( this ); } }

				virtual void MakeCaratVisible();

				virtual void OnEnter();

				virtual bool NeedsInputChars() { return true; }

				virtual void MoveCaretToEnd();
				virtual void MoveCaretToStart();

				Event::Caller	onTextChanged;
				Event::Caller	onReturnPressed;

			protected:

				virtual void OnTextChanged();
				virtual bool IsTextAllowed( const FK2DEngine2::UnicodeString & /*str*/, int /*iPos*/ ) { return true; }

				bool m_bSelectAll;

				int m_iCursorPos;
				int m_iCursorEnd;
				int m_iCursorLine;

				FK2DEngine2::Rect m_rectSelectionBounds;
				FK2DEngine2::Rect m_rectCaretBounds;

				float m_fNextCaretColorChange;
				FK2DEngine2::Color	m_CaretColor;
		};
		//------------------------------------------------------------------------
		class FK_EXPORT TextBoxNumeric : public TextBox
		{
			public:

				FK_CONTROL( TextBoxNumeric, TextBox );

				virtual float GetFloatFromText();

			private:

				virtual bool IsTextAllowed( const FK2DEngine2::UnicodeString & str, int iPos );

		};
		//------------------------------------------------------------------------
		class FK_EXPORT TextBoxMultiline : public TextBox
		{
			public:

				FK_CONTROL( TextBoxMultiline, TextBox );

				virtual bool OnKeyReturn( bool bDown );
				virtual void MakeCaratVisible();

				virtual bool OnKeyHome( bool bDown );
				virtual bool OnKeyEnd( bool bDown );
				virtual bool OnKeyUp( bool bDown );
				virtual bool OnKeyDown( bool bDown );

				virtual int GetCurrentLine();
		};
	}
}
//------------------------------------------------------------------------