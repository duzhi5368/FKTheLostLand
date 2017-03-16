/**
*	created:		2013-4-11   17:28
*	filename: 		FKTextObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKUtility.h"
#include <string>
//------------------------------------------------------------------------
#pragma warning( disable:4172 )
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	class UITexObjSimpleInfo
	{
		public:

			UITexObjSimpleInfo() {}

			UITexObjSimpleInfo( const FK2DEngine2::String & text )
			{
				m_String = text;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			UITexObjSimpleInfo( const char* text )
			{
				m_String = text;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			UITexObjSimpleInfo( const wchar_t* text )
			{
				m_Unicode = text;
				m_String = FK2DEngine2::Utility::UnicodeToString( m_Unicode );
			}

			UITexObjSimpleInfo( const FK2DEngine2::UnicodeString & unicode )
			{
				*this = unicode;
			}

			operator const FK2DEngine2::String & () { return m_String; }
			operator const FK2DEngine2::UnicodeString & () { return m_Unicode; }

			void operator = ( const char* str )
			{
				m_String = str;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			void operator = ( const FK2DEngine2::String & str )
			{
				m_String = str;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			void operator = ( const FK2DEngine2::UnicodeString & unicodeStr )
			{
				m_Unicode = unicodeStr;
				m_String = FK2DEngine2::Utility::UnicodeToString( m_Unicode );
			}

			bool operator == ( const UITexObjSimpleInfo & to ) const
			{
				return m_Unicode == to.m_Unicode;
			}

			const FK2DEngine2::String & Get() const
			{
				return m_String;
			}

			const char* c_str() const
			{
				return m_String.c_str();
			}

			const FK2DEngine2::UnicodeString & GetUnicode() const
			{
				return m_Unicode;
			}

			const FK2DEngine2::UnicodeString& GetPassword() const
			{
				static std::wstring EmptyPassword( L"" );
				static std::wstring Password1( 1, '*' );
				static std::wstring Password2( 2, '*' );
				static std::wstring Password3( 3, '*' );
				static std::wstring Password4( 4, '*' );
				static std::wstring Password5( 5, '*' );
				static std::wstring Password6( 6, '*' );
				static std::wstring Password7( 7, '*' );
				static std::wstring Password8( 8, '*' );
				static std::wstring Password9( 9, '*' );
				static std::wstring Password10( 10, '*' );
				static std::wstring Password11( 11, '*' );
				static std::wstring Password12( 12, '*' );
				static std::wstring Password13( 13, '*' );
				static std::wstring Password14( 14, '*' );
				static std::wstring Password15( 15, '*' );
				static std::wstring Password16( 16, '*' );
				switch( length() )
				{
				case 0:return EmptyPassword;
				case 1:return Password1;
				case 2:return Password2;
				case 3:return Password3;
				case 4:return Password4;
				case 5:return Password5;
				case 6:return Password6;
				case 7:return Password7;
				case 8:return Password8;
				case 9:return Password9;
				case 10:return Password10;
				case 11:return Password11;
				case 12:return Password12;
				case 13:return Password13;
				case 14:return Password14;
				case 15:return Password15;
				case 16:return Password16;
				default: return EmptyPassword;
				}
				return EmptyPassword;
			}

			int length() const { return m_Unicode.length(); }

			FK2DEngine2::UnicodeString		m_Unicode;
			FK2DEngine2::String				m_String;
	};
}
//------------------------------------------------------------------------