/**
*	created:		2013-4-23   19:38
*	filename: 		FKStringConvert
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include "FKVector2.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		static void CharToWchar(const char *chr, wchar_t *wchar, int size)  
		{
			MultiByteToWideChar( CP_ACP, 0, chr,  strlen(chr)+1, wchar, size/sizeof(wchar[0]) );  
		}

		static void WcharToChar(const wchar_t *wchar, char *chr, int length)
		{
			WideCharToMultiByte( CP_ACP, 0, wchar, -1,  chr, length, NULL, NULL );  
		}

		int StringToInt( const std::wstring& s );
		float StringToFloat( const std::wstring& s );
		bool StringToBool( const std::wstring& s );
		FK2DEngine2::math::Vector2 StringToVector2( const std::wstring& s );
		std::wstring IntToString( int val );
		std::wstring FloatToStr( float val );
		std::wstring BoolToStr( bool val );
		std::wstring Vector2ToString( const FK2DEngine2::math::Vector2& val );
		std::wstring ToUpper( const std::wstring& s );
		std::wstring ToLower( const std::wstring& s );
		std::vector<std::wstring> SplitString( const std::wstring& splitMe, const std::wstring& splitChars,
			bool bRemoveEmptyEntries = true );
		std::vector<std::wstring> SplitString( const std::wstring& splitMe );
		std::wstring TrimString( const std::wstring& trimMe, const std::wstring& trimChars );
		std::wstring TrimString( const std::wstring& trimMe );
		bool IsCharOrNum( const char* iName );
	}
}
//------------------------------------------------------------------------