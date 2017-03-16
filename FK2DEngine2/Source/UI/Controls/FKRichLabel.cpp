/**
*	created:		2013-4-12   21:43
*	filename: 		FKRichLabel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
const unsigned char Type_Text = 0;
const unsigned char Type_Newline = 1;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( RichLabel )
{
	m_bNeedsRebuild = false;
}

void RichLabel::AddLineBreak()
{
	DividedText t;
	t.type = Type_Newline;
	m_TextBlocks.push_back( t );
}

void RichLabel::AddText( const FK2DEngine2::UITexObjSimpleInfo & text, FK2DEngine2::Color color, FK2DEngine2::Font* font )
{
	if ( text.length() == 0 ) { return; }

	FK2DEngine2::Utility::Strings::UnicodeList lst;
	FK2DEngine2::Utility::Strings::Split( text.GetUnicode(), L"\n", lst, false );

	for ( size_t i = 0; i < lst.size(); i++ )
	{
		if ( i > 0 ) { AddLineBreak(); }

		DividedText t;
		t.type = Type_Text;
		t.text = lst[i];
		t.color = color;
		t.font = font;
		m_TextBlocks.push_back( t );
		m_bNeedsRebuild = true;
		Invalidate();
	}
}

bool RichLabel::SizeToChildren( bool w, bool h )
{
	Rebuild();
	return BaseClass::SizeToChildren( w, h );
}

void RichLabel::SplitLabel( const FK2DEngine2::UnicodeString & text, FK2DEngine2::Font* pFont, const DividedText & txt, int & x, int & y, int & lineheight )
{
	FK2DEngine2::Utility::Strings::UnicodeList lst;
	FK2DEngine2::Utility::Strings::Split( text, L" ", lst, true );

	if ( lst.size() == 0 ) { return; }

	int iSpaceLeft = Width() - x;

	{
		FK2DEngine2::Point StringSize = GetSkin()->GetRender()->MeasureText( pFont, text );

		if ( iSpaceLeft > StringSize.x )
		{
			return CreateLabel( text, txt, x, y, lineheight, true );
		}
	}

	{
		FK2DEngine2::Point WordSize = GetSkin()->GetRender()->MeasureText( pFont, lst[0] );

		if ( WordSize.x >= iSpaceLeft )
		{
			CreateLabel( lst[0], txt, x, y, lineheight, true );

			if ( lst[0].size() >= text.size() ) { return; }

			FK2DEngine2::UnicodeString LeftOver = text.substr( lst[0].size() + 1 );
			return SplitLabel( LeftOver, pFont, txt, x, y, lineheight );
		}
	}
	FK2DEngine2::UnicodeString strNewString = L"";

	for ( size_t i = 0; i < lst.size(); i++ )
	{
		FK2DEngine2::Point WordSize = GetSkin()->GetRender()->MeasureText( pFont, strNewString + lst[i] );

		if ( WordSize.x > iSpaceLeft )
		{
			CreateLabel( strNewString, txt, x, y, lineheight, true );
			x = 0;
			y += lineheight;
			break;;
		}

		strNewString += lst[i];
	}

	FK2DEngine2::UnicodeString LeftOver = text.substr( strNewString.size() + 1 );
	return SplitLabel( LeftOver, pFont, txt, x, y, lineheight );
}

void RichLabel::CreateLabel( const FK2DEngine2::UnicodeString & text, const DividedText & txt, int & x, int & y, int & lineheight, bool NoSplit )
{
	FK2DEngine2::Font* pFont = GetSkin()->GetDefaultFont();

	if ( txt.font ) { pFont = txt.font; }

	FK2DEngine2::Point p = GetSkin()->GetRender()->MeasureText( pFont, text );

	if ( lineheight == -1 )
	{
		lineheight = p.y;
	}

	if ( !NoSplit )
	{
		if ( x + p.x > Width() )
		{
			return SplitLabel( text, pFont, txt, x, y, lineheight );
		}
	}

	if ( x + p.x >= Width() )
	{
		CreateNewline( x, y, lineheight );
	}

	FK2DEngine2::Controls::Label*	pLabel = new FK2DEngine2::Controls::Label( this );
	pLabel->SetText( x == 0 ? FK2DEngine2::Utility::Strings::TrimLeft<FK2DEngine2::UnicodeString> ( text, L" " ) : text );
	pLabel->SetTextColor( txt.color );
	pLabel->SetFont( pFont );
	pLabel->SizeToContents();
	pLabel->SetPos( x, y );

	x += pLabel->Width();

	if ( x >= Width() )
	{
		CreateNewline( x, y, lineheight );
	}
}

void RichLabel::CreateNewline( int & x, int & y, int & lineheight )
{
	x = 0;
	y += lineheight;
}

void RichLabel::Rebuild()
{
	RemoveAllChildren();
	int x = 0;
	int y = 0;
	int lineheight = -1;

	for ( DividedText::List::iterator it = m_TextBlocks.begin(); it != m_TextBlocks.end(); ++it )
	{
		if ( it->type == Type_Newline )
		{
			CreateNewline( x, y, lineheight );
			continue;
		}

		if ( it->type == Type_Text )
		{
			CreateLabel( ( *it ).text, *it, x, y, lineheight, false );
			continue;
		}
	}

	m_bNeedsRebuild = false;
}

void RichLabel::OnBoundsChanged( FK2DEngine2::Rect oldBounds )
{
	BaseClass::OnBoundsChanged( oldBounds );
	Rebuild();
}

void RichLabel::Layout( FK2DEngine2::Skin::Base* skin )
{
	BaseClass::Layout( skin );

	if ( m_bNeedsRebuild )
	{
		Rebuild();
	}
}
//------------------------------------------------------------------------