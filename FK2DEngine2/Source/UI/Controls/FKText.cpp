/**
*	created:		2013-4-12   1:05
*	filename: 		FKText
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( Text )
{
	m_Font = NULL;
	m_ColorOverride = Color( 255, 255, 255, 0 );
	m_Color = GetSkin()->Colors.Label.Default;
	SetMouseInputEnabled( false );
	m_bPassword = false;
	SetWrap( false );
}

Text::~Text()
{
	// 字体无需释放
}

void Text::Layout( Skin::Base* skin )
{
	if ( m_bTextChanged )
	{
		RefreshSize();
		m_bTextChanged = false;
	}
}

FK2DEngine2::Font* Text::GetFont()
{
	return m_Font;
}

void Text::SetFont( FK2DEngine2::Font* pFont )
{
	if ( m_Font == pFont ) { return; }

	m_Font = pFont;
	m_bTextChanged = true;
	{
		TextLines::iterator it = m_Lines.begin();
		TextLines::iterator itEnd = m_Lines.end();

		while ( it != itEnd )
		{
			( *it )->SetFont( m_Font );
			++it;
		}
	}
	Invalidate();
}

void Text::SetString( const UITexObjSimpleInfo & str )
{
	if ( m_String == str ) { return; }

	m_String = str.GetUnicode();
	m_bTextChanged = true;
	Invalidate();
}

void Text::Render( Skin::Base* skin )
{
	if ( m_bWrap ) { return; }

	if ( Length() == 0 || !GetFont() ) { return; }

	if ( m_ColorOverride.a == 0 )
	{ skin->GetRender()->SetDrawColor( m_Color ); }
	else
	{ skin->GetRender()->SetDrawColor( m_ColorOverride ); }

	if( m_bPassword )
	{
		skin->GetRender()->RenderText( GetFont(), FK2DEngine2::Point( GetPadding().left, GetPadding().top ), m_String.GetPassword() );
	}
	else
	{
		skin->GetRender()->RenderText( GetFont(), FK2DEngine2::Point( GetPadding().left, GetPadding().top ), m_String.GetUnicode() );
	}
}

FK2DEngine2::Rect Text::GetCharacterPosition( int iChar )
{
	if ( !m_Lines.empty() )
	{
		TextLines::iterator it = m_Lines.begin();
		TextLines::iterator itEnd = m_Lines.end();
		int iChars = 0;

		while ( it != itEnd )
		{
			Text* pLine = *it;
			++it;
			iChars += pLine->Length();

			if ( iChars <= iChar ) { continue; }

			iChars -= pLine->Length();
			FK2DEngine2::Rect rect = pLine->GetCharacterPosition( iChar - iChars );
			rect.x += pLine->X();
			rect.y += pLine->Y();
			return rect;
		}
	}

	if ( Length() == 0 || iChar == 0 )
	{
		FK2DEngine2::Point p = GetSkin()->GetRender()->MeasureText( GetFont(), L" " );
		return FK2DEngine2::Rect( 1, 0, 0, p.y );
	}

	UnicodeString sub = m_String.GetUnicode().substr( 0, iChar );
	FK2DEngine2::Point p = GetSkin()->GetRender()->MeasureText( GetFont(), sub );
	return Rect( p.x, 0, 0, p.y );
}

int Text::GetClosestCharacter( FK2DEngine2::Point p )
{
	if ( !m_Lines.empty() )
	{
		TextLines::iterator it = m_Lines.begin();
		TextLines::iterator itEnd = m_Lines.end();
		int iChars = 0;

		while ( it != itEnd )
		{
			Text* pLine = *it;
			++it;
			iChars += pLine->Length();

			if ( p.y < pLine->Y() ) { continue; }

			if ( p.y > pLine->Bottom() ) { continue; }

			iChars -= pLine->Length();
			int iLinePos = pLine->GetClosestCharacter( FK2DEngine2::Point( p.x - pLine->X(), p.y - pLine->Y() ) );
			iLinePos--;
			return iChars + iLinePos;
		}
	}

	int iDistance = 4096;
	int iChar = 0;

	for ( size_t i = 0; i < m_String.GetUnicode().length() + 1; i++ )
	{
		FK2DEngine2::Rect cp = GetCharacterPosition( i );
		int iDist = abs( cp.x - p.x ) + abs( cp.y - p.y );

		if ( iDist > iDistance ) { continue; }

		iDistance = iDist;
		iChar = i;
	}

	return iChar;
}

void Text::OnScaleChanged()
{
	Invalidate();
}

void Text::RefreshSize()
{
	if ( m_bWrap )
	{
		return RefreshSizeWrap();
	}

	if ( !GetFont() )
	{
		Debug::AssertCheck( 0, "Text::RefreshSize() - No Font!!\n" );
		return;
	}

	FK2DEngine2::Point p( 1, GetFont()->size );

	if ( Length() > 0 )
	{
		p = GetSkin()->GetRender()->MeasureText( GetFont(), m_String.GetUnicode() );
	}

	p.x += GetPadding().left + GetPadding().right;
	p.y += GetPadding().top + GetPadding().bottom;

	if ( p.x == Width() && p.y == Height() )
	{ return; }

	if ( p.y < GetFont()->size ) { p.y = GetFont()->size; }

	SetSize( p.x, p.y );
	InvalidateParent();
	Invalidate();
}

void SplitWords( const FK2DEngine2::UnicodeString & s, wchar_t delim, std::vector<FK2DEngine2::UnicodeString> & elems )
{
	FK2DEngine2::UnicodeString str;

	for ( unsigned int i = 0; i < s.length(); i++ )
	{
		if ( s[i] == L'\n' )
		{
			if ( !str.empty() ) { elems.push_back( str ); }

			elems.push_back( L"\n" );
			str.clear();
			continue;
		}

		if ( s[i] == L' ' )
		{
			str += s[i];
			elems.push_back( str );
			str.clear();
			continue;
		}

		str += s[i];
	}

	if ( !str.empty() ) { elems.push_back( str ); }
}

void Text::RefreshSizeWrap()
{
	RemoveAllChildren();

	for ( TextLines::iterator it = m_Lines.begin(); it != m_Lines.end(); ++it )
	{
		delete *it;
	}

	m_Lines.clear();
	std::vector<FK2DEngine2::UnicodeString> words;
	SplitWords( GetText().GetUnicode(), L' ', words );
	words.push_back( L"" );

	if ( !GetFont() )
	{
		Debug::AssertCheck( 0, "Text::RefreshSize() - No Font!!\n" );
		return;
	}

	Point pFontSize = GetSkin()->GetRender()->MeasureText( GetFont(), L" " );
	int w = GetParent()->Width();
	int x = 0, y = 0;
	FK2DEngine2::UnicodeString strLine;

	for ( std::vector<FK2DEngine2::UnicodeString>::iterator it = words.begin(); it != words.end(); ++it )
	{
		bool bFinishLine = false;
		bool bWrapped = false;

		if ( ( *it ).c_str() [0] == L'\n' ) { bFinishLine = true; }

		{
			strLine += ( *it );
			FK2DEngine2::Point p = GetSkin()->GetRender()->MeasureText( GetFont(), strLine );

			if ( p.x > Width() ) { bFinishLine = true; bWrapped = true; }
		}

		if ( --words.end() == it )
		{
			bFinishLine = true;
		}

		if ( bFinishLine )
		{
			Text* t = new Text( this );
			t->SetFont( GetFont() );
			t->SetString( strLine.substr( 0, strLine.length() - ( *it ).length() ) );
			t->RefreshSize();
			t->SetPos( x, y );
			m_Lines.push_back( t );
			strLine = *it;
			y += pFontSize.y;
			x = 0;
		}
	}

	{
		Point childsize = ChildrenSize();
		SetSize( w, childsize.y );
	}
	InvalidateParent();
	Invalidate();
}

int Text::NumLines()
{
	return m_Lines.size();
}

Text* Text::GetLine( int i )
{
	TextLines::iterator it = m_Lines.begin();
	TextLines::iterator itEnd = m_Lines.end();

	while ( it != itEnd )
	{
		if ( i == 0 ) { return *it; }

		++it;
		i--;
	}

	return NULL;
}

int Text::GetLineFromChar( int i )
{
	TextLines::iterator it = m_Lines.begin();
	TextLines::iterator itEnd = m_Lines.end();
	int iChars = 0;
	int iLine = 0;

	while ( it != itEnd )
	{
		Text* pLine = *it;
		++it;
		iChars += pLine->Length();

		if ( iChars > i ) { return iLine; }

		iLine++;
	}

	return iLine;
}

int Text::GetStartCharFromLine( int i )
{
	TextLines::iterator it = m_Lines.begin();
	TextLines::iterator itEnd = m_Lines.end();
	int iChars = 0;

	while ( it != itEnd )
	{
		Text* pLine = *it;
		++it;

		if ( i == 0 ) { return FK2DEngine2::Clamp( iChars, 0, Length() ); }

		iChars += pLine->Length();
		i--;
	}

	return FK2DEngine2::Clamp( iChars, 0, Length() );
}

int Text::GetEndCharFromLine( int i )
{
	int iStart = GetStartCharFromLine( i );
	Text* iLine = GetLine( i );

	if ( iLine )
	{
		iStart += iLine->Length();
	}

	return FK2DEngine2::Clamp( iStart, 0, Length() );
}

int Text::GetCharPosOnLine( int i )
{
	int iLine = GetLineFromChar( i );
	Text* line = GetLine( iLine );

	if ( !line ) { return 0; }

	int iStart = GetStartCharFromLine( iLine );
	return i - iStart;
}
//------------------------------------------------------------------------