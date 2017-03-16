/**
*	created:		2013-4-13   21:45
*	filename: 		FKTextBoxNumeric
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
FK_CONTROL_CONSTRUCTOR( TextBoxNumeric )
{
	SetText( L"0" );
}

bool TextBoxNumeric::IsTextAllowed( const FK2DEngine2::UnicodeString & str, int iPos )
{
	const UnicodeString & strString = GetText().GetUnicode();

	if ( str.length() == 0 )
	{ return true; }

	for ( size_t i = 0; i < str.length(); i++ )
	{
		if ( str[i] == L'-' )
		{
			if ( i != 0 || iPos != 0 )
			{ return false; }

			if ( std::count( strString.begin(), strString.end(), L'-' ) > 0 )
			{ return false; }

			continue;
		}

		if ( str[i] == L'0' ) { continue; }

		if ( str[i] == L'1' ) { continue; }

		if ( str[i] == L'2' ) { continue; }

		if ( str[i] == L'3' ) { continue; }

		if ( str[i] == L'4' ) { continue; }

		if ( str[i] == L'5' ) { continue; }

		if ( str[i] == L'6' ) { continue; }

		if ( str[i] == L'7' ) { continue; }

		if ( str[i] == L'8' ) { continue; }

		if ( str[i] == L'9' ) { continue; }

		if ( str[i] == L'.' )
		{
			if ( std::count( strString.begin(), strString.end(), L'.' ) > 0 )
			{ return false; }

			continue;
		}

		return false;
	}

	return true;
}

float TextBoxNumeric::GetFloatFromText()
{
	double temp = FK2DEngine2::Utility::Strings::To::Float( GetText().GetUnicode() );
	return temp;
}
//------------------------------------------------------------------------