/**
*	created:		2013-4-13   21:29
*	filename: 		FKTextBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
#include <math.h>
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
class ChangeCaretColor : public FK2DEngine2::Anim::Animation
{
	public:

		virtual void Think()
		{
			fk_cast<TextBox> ( m_Control )->UpdateCaretColor();
		}
};


FK_CONTROL_CONSTRUCTOR( TextBox )
{
	SetSize( 200, 20 );
	SetMouseInputEnabled( true );
	SetKeyboardInputEnabled( true );
	SetAlignment( Pos::Left | Pos::CenterV );
	SetPadding( Padding( 4, 2, 4, 2 ) );
	m_iCursorPos = 0;
	m_iCursorEnd = 0;
	m_iCursorLine = 0;
	m_bSelectAll = false;
	SetTextColor( FK2DEngine2::Color( 50, 50, 50, 255 ) );   // TODO: From Skin
	SetTabable( true );
	AddAccelerator( L"Ctrl + C", &TextBox::OnCopy );
	AddAccelerator( L"Ctrl + X", &TextBox::OnCut );
	AddAccelerator( L"Ctrl + V", &TextBox::OnPaste );
	AddAccelerator( L"Ctrl + A", &TextBox::OnSelectAll );
	FK2DEngine2::Anim::Add( this, new ChangeCaretColor() );
}

bool TextBox::OnChar( FK2DEngine2::UnicodeChar c )
{
	if ( c == '\t' ) { return false; }

	FK2DEngine2::UnicodeString str;
	str += c;
	InsertText( str );
	return true;
}

void TextBox::InsertText( const FK2DEngine2::UnicodeString & strInsert )
{
	if ( HasSelection() )
	{
		EraseSelection();
	}

	if ( m_iCursorPos > TextLength() ) { m_iCursorPos = TextLength(); }

	if ( !IsTextAllowed( strInsert, m_iCursorPos ) )
	{ return; }

	UnicodeString str = GetText().GetUnicode();
	str.insert( m_iCursorPos, strInsert );
	SetText( str );
	m_iCursorPos += ( int ) strInsert.size();
	m_iCursorEnd = m_iCursorPos;
	m_iCursorLine = 0;
	RefreshCursorBounds();
}

void TextBox::UpdateCaretColor()
{
	if ( m_fNextCaretColorChange > FK2DEngine2::Platform::GetTimeInSeconds() ) { return; }

	if ( !HasFocus() ) { m_fNextCaretColorChange = FK2DEngine2::Platform::GetTimeInSeconds() + 0.5f; return; }

	FK2DEngine2::Color targetcolor = FK2DEngine2::Color( 230, 230, 230, 255 );

	if ( m_CaretColor == targetcolor )
	{ targetcolor = FK2DEngine2::Color( 20, 20, 20, 255 ); }

	m_fNextCaretColorChange = FK2DEngine2::Platform::GetTimeInSeconds() + 0.5;
	m_CaretColor = targetcolor;
	Redraw();
}

void TextBox::Render( Skin::Base* skin )
{
	if ( ShouldDrawBackground() )
	{ skin->DrawTextBox( this ); }

	if ( !HasFocus() ) { return; }

	if ( m_iCursorPos != m_iCursorEnd )
	{
		skin->GetRender()->SetDrawColor( FK2DEngine2::Color( 50, 170, 255, 200 ) );
		skin->GetRender()->DrawFilledRect( m_rectSelectionBounds );
	}

	skin->GetRender()->SetDrawColor( m_CaretColor );
	skin->GetRender()->DrawFilledRect( m_rectCaretBounds );
}

void TextBox::RefreshCursorBounds()
{
	m_fNextCaretColorChange = FK2DEngine2::Platform::GetTimeInSeconds() + 1.5f;
	m_CaretColor = FK2DEngine2::Color( 30, 30, 30, 255 );
	MakeCaratVisible();
	FK2DEngine2::Rect pA = GetCharacterPosition( m_iCursorPos );
	FK2DEngine2::Rect pB = GetCharacterPosition( m_iCursorEnd );
	m_rectSelectionBounds.x = Utility::Min( pA.x, pB.x );
	m_rectSelectionBounds.y = m_Text->Y() - 1;
	m_rectSelectionBounds.w = Utility::Max( pA.x, pB.x ) - m_rectSelectionBounds.x;
	m_rectSelectionBounds.h = m_Text->Height() + 2;
	m_rectCaretBounds.x = pA.x;
	m_rectCaretBounds.y = pA.y;
	m_rectCaretBounds.w = 1;
	m_rectCaretBounds.h = pA.h;
	Redraw();
}


void TextBox::OnPaste( FK2DEngine2::Controls::Base* /*pCtrl*/ )
{
	InsertText( Platform::GetClipboardText() );
}

void TextBox::OnCopy( FK2DEngine2::Controls::Base* /*pCtrl*/ )
{
	if ( !HasSelection() ) { return; }

	Platform::SetClipboardText( GetSelection() );
}

void TextBox::OnCut( FK2DEngine2::Controls::Base* /*pCtrl*/ )
{
	if ( !HasSelection() ) { return; }

	Platform::SetClipboardText( GetSelection() );
	EraseSelection();
}

void TextBox::OnSelectAll( FK2DEngine2::Controls::Base* /*pCtrl*/ )
{
	m_iCursorEnd = 0;
	m_iCursorPos = TextLength();
	m_iCursorLine = 0;
	RefreshCursorBounds();
}

void TextBox::OnMouseDoubleClickLeft( int /*x*/, int /*y*/ )
{
	OnSelectAll( this );
}

UnicodeString TextBox::GetSelection()
{
	if ( !HasSelection() ) { return L""; }

	int iStart = Utility::Min( m_iCursorPos, m_iCursorEnd );
	int iEnd = Utility::Max( m_iCursorPos, m_iCursorEnd );
	const UnicodeString & str = GetText().GetUnicode();
	return str.substr( iStart, iEnd - iStart );
}

bool TextBox::OnKeyReturn( bool bDown )
{
	if ( bDown ) { return true; }

	OnKeyTab( true );

	if ( HasFocus() )
	{
		Blur();
	}

	OnEnter();
	return true;
}

bool TextBox::OnKeyBackspace( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( HasSelection() )
	{
		EraseSelection();
		return true;
	}

	if ( m_iCursorPos == 0 ) { return true; }

	DeleteText( m_iCursorPos - 1, 1 );
	return true;
}

bool TextBox::OnKeyDelete( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( HasSelection() )
	{
		EraseSelection();
		return true;
	}

	if ( m_iCursorPos >= TextLength() ) { return true; }

	DeleteText( m_iCursorPos, 1 );
	return true;
}

bool TextBox::OnKeyLeft( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( m_iCursorPos > 0 )
	{ m_iCursorPos--; }

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

bool TextBox::OnKeyRight( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( m_iCursorPos < TextLength() )
	{ m_iCursorPos++; }

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

bool TextBox::OnKeyHome( bool bDown )
{
	if ( !bDown ) { return true; }

	m_iCursorPos = 0;

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

bool TextBox::OnKeyEnd( bool /*bDown*/ )
{
	m_iCursorPos = TextLength();

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

void TextBox::SetCursorPos( int i )
{
	if ( m_iCursorPos == i ) { return; }

	m_iCursorPos = i;
	m_iCursorLine = 0;
	RefreshCursorBounds();
}

void TextBox::SetCursorEnd( int i )
{
	if ( m_iCursorEnd == i ) { return; }

	m_iCursorEnd = i;
	RefreshCursorBounds();
}


void TextBox::DeleteText( int iStartPos, int iLength )
{
	UnicodeString str = GetText().GetUnicode();
	str.erase( iStartPos, iLength );
	SetText( str );

	if ( m_iCursorPos > iStartPos )
	{
		SetCursorPos( m_iCursorPos - iLength );
	}

	SetCursorEnd( m_iCursorPos );
}

bool TextBox::HasSelection()
{
	return m_iCursorPos != m_iCursorEnd;
}

void TextBox::EraseSelection()
{
	int iStart = Utility::Min( m_iCursorPos, m_iCursorEnd );
	int iEnd = Utility::Max( m_iCursorPos, m_iCursorEnd );
	DeleteText( iStart, iEnd - iStart );

	m_iCursorPos = iStart;
	m_iCursorEnd = iStart;
}

void TextBox::OnMouseClickLeft( int x, int y, bool bDown )
{
	if ( m_bSelectAll )
	{
		OnSelectAll( this );
		m_bSelectAll = false;
		return;
	}

	int iChar = m_Text->GetClosestCharacter( m_Text->CanvasPosToLocal( FK2DEngine2::Point( x, y ) ) );

	if ( bDown )
	{
		SetCursorPos( iChar );

		if ( !FK2DEngine2::Input::IsShiftDown() )
		{ SetCursorEnd( iChar ); }

		FK2DEngine2::MouseFocus = this;
	}
	else
	{
		if ( FK2DEngine2::MouseFocus == this )
		{
			SetCursorPos( iChar );
			FK2DEngine2::MouseFocus = NULL;
		}
	}
}

void TextBox::OnMouseMoved( int x, int y, int /*deltaX*/, int /*deltaY*/ )
{
	if ( FK2DEngine2::MouseFocus != this ) { return; }

	int iChar = m_Text->GetClosestCharacter( m_Text->CanvasPosToLocal( FK2DEngine2::Point( x, y ) ) );
	SetCursorPos( iChar );
}

void TextBox::MakeCaratVisible()
{
	if ( m_Text->Width() < Width() )
	{
		m_Text->Position( m_iAlign );
	}
	else
	{
		int iCaratPos = m_Text->GetCharacterPosition( m_iCursorPos ).x;
		int iRealCaratPos = iCaratPos + m_Text->X();
		int iSlidingZone = m_Text->GetFont()->size + 1; //Width()*0.1f

		if ( iRealCaratPos >= iSlidingZone && iRealCaratPos <= Width() - iSlidingZone )
		{ return; }

		int x = 0;

		if ( iRealCaratPos > Width() - iSlidingZone )
		{
			x = Width() - iCaratPos - iSlidingZone;
		}

		if ( iRealCaratPos < iSlidingZone )
		{
			x = -iCaratPos + iSlidingZone;
		}

		if ( x + m_Text->Width() < Width() - GetPadding().right )
		{ x = -m_Text->Width() + ( Width() - GetPadding().right ); }

		if ( x > GetPadding().left )
		{ x = GetPadding().left; }

		int y = 0;

		if ( m_iAlign & Pos::Top ) { y = GetPadding().top; }

		if ( m_iAlign & Pos::Bottom ) { y = Height() - m_Text->Height() - GetPadding().bottom ; }

		if ( m_iAlign & Pos::CenterV ) { y = ( Height() - m_Text->Height() ) * 0.5; }

		m_Text->SetPos( x, y );
	}
}

void TextBox::Layout( Skin::Base* skin )
{
	BaseClass::Layout( skin );
	RefreshCursorBounds();
}

void TextBox::PostLayout( Skin::Base* skin )
{
}

void TextBox::OnTextChanged()
{
	if ( m_iCursorPos > TextLength() ) { m_iCursorPos = TextLength(); }

	if ( m_iCursorEnd > TextLength() ) { m_iCursorEnd = TextLength(); }

	onTextChanged.Call( this );
}

void TextBox::OnEnter()
{
	onReturnPressed.Call( this );
}

void TextBox::MoveCaretToEnd()
{
	m_iCursorPos = TextLength();
	m_iCursorEnd = TextLength();
	RefreshCursorBounds();
}

void TextBox::MoveCaretToStart()
{
	m_iCursorPos = 0;
	m_iCursorEnd = 0;
	RefreshCursorBounds();
}


FK_CONTROL_CONSTRUCTOR( TextBoxMultiline )
{
	SetWrap( true );
	SetAlignment( Pos::Left | Pos::Top );
}

bool TextBoxMultiline::OnKeyReturn( bool bDown )
{
	if ( bDown )
	{
		InsertText( L"\n" );
	}

	return true;
}

void TextBoxMultiline::MakeCaratVisible()
{
	// TODO
}

int TextBoxMultiline::GetCurrentLine()
{
	return m_Text->GetLineFromChar( m_iCursorPos );
}

bool TextBoxMultiline::OnKeyHome( bool bDown )
{
	if ( !bDown ) { return true; }

	int iCurrentLine = GetCurrentLine();
	int iChar = m_Text->GetStartCharFromLine( iCurrentLine );
	m_iCursorLine = 0;
	m_iCursorPos = iChar;

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

bool TextBoxMultiline::OnKeyEnd( bool bDown )
{
	if ( !bDown ) { return true; }

	int iCurrentLine = GetCurrentLine();
	int iChar = m_Text->GetEndCharFromLine( iCurrentLine );
	m_iCursorLine = 0;
	m_iCursorPos = iChar - 1; // NAUGHTY

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

bool TextBoxMultiline::OnKeyUp( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( m_iCursorLine == 0 ) { m_iCursorLine = m_Text->GetCharPosOnLine( m_iCursorPos ); }

	int iLine = m_Text->GetLineFromChar( m_iCursorPos );

	if ( iLine == 0 ) { return true; }

	m_iCursorPos = m_Text->GetStartCharFromLine( iLine - 1 );
	m_iCursorPos += Clamp( m_iCursorLine, 0, m_Text->GetLine( iLine - 1 )->Length() );
	m_iCursorPos = Clamp( m_iCursorPos, 0, m_Text->Length() );

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}

bool TextBoxMultiline::OnKeyDown( bool bDown )
{
	if ( !bDown ) { return true; }

	if ( m_iCursorLine == 0 ) { m_iCursorLine = m_Text->GetCharPosOnLine( m_iCursorPos ); }

	int iLine = m_Text->GetLineFromChar( m_iCursorPos );

	if ( iLine >= m_Text->NumLines() - 1 ) { return true; }

	m_iCursorPos = m_Text->GetStartCharFromLine( iLine + 1 );
	m_iCursorPos += Clamp( m_iCursorLine, 0, m_Text->GetLine( iLine + 1 )->Length() );
	m_iCursorPos = Clamp( m_iCursorPos, 0, m_Text->Length() );

	if ( !FK2DEngine2::Input::IsShiftDown() )
	{
		m_iCursorEnd = m_iCursorPos;
	}

	RefreshCursorBounds();
	return true;
}
//------------------------------------------------------------------------