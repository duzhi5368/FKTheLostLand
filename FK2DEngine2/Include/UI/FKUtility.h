/**
*	created:		2013-4-11   17:26
*	filename: 		FKUtility
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <sstream>
#include <vector>
#include "FKStructures.h"
//-----------------------------------------------v-------------------------
namespace FK2DEngine2
{
	class UITexObjSimpleInfo;

	namespace Controls
	{
		class Base;
		class Canvas;
	}

	namespace video
	{
		class Base;
	}

	namespace Debug
	{
		void FK_EXPORT Msg( const wchar_t* str, ... );
		void FK_EXPORT Msg( const char* str, ... );
		void FK_EXPORT AssertCheck( bool b, const char* strMsg );
	}


	namespace Colors
	{
		static const Color Black( 0, 0, 0, 255 );
		static const Color Red( 255, 0, 0, 255 );
		static const Color Yellow( 255, 255, 0, 255 );
		static const Color White( 255, 255, 255, 255 );
		static const Color Blue( 0, 0, 255, 255 );
		static const Color Green( 0, 255, 0, 255 );
		static const Color Grey( 200, 200, 200, 255 );
		static const Color GreyLight( 230, 230, 230, 255 );
		static const Color FKPink( 255, 65, 199, 255 );


	};

	extern FK_EXPORT Controls::Base*	HoveredControl;
	extern FK_EXPORT Controls::Base*	KeyboardFocus;
	extern FK_EXPORT Controls::Base*	MouseFocus;

	namespace Input
	{
		void Blur();
	}

	namespace Utility
	{
		template <typename T>
		const T & Max( const T & x, const T & y )
		{
			if ( y < x ) { return x; }

			return y;
		}

		template <typename T>
		const T & Min( const T & x, const T & y )
		{
			if ( y > x ) { return x; }

			return y;
		}

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif

		String UnicodeToString( const UnicodeString & strIn );
		UnicodeString StringToUnicode( const String & strIn );

		template<typename T> void Replace( T & str, const T & strFind, const T & strReplace )
		{
			size_t pos = 0;

			while ( ( pos = str.find( strFind, pos ) ) != T::npos )
			{
				str.replace( pos, strFind.length(), strReplace );
				pos += strReplace.length();
			}
		}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

		template <class T>
		String ToString( const T & object )
		{
			std::ostringstream os;
			os << object;
			return os.str();
		}

		inline FK2DEngine2::Rect ClampRectToRect( FK2DEngine2::Rect inside, FK2DEngine2::Rect outside, bool clampSize = false )
		{
			if ( inside.x < outside.x )
			{ inside.x = outside.x; }

			if ( inside.y  < outside.y )
			{ inside.y = outside.y; }

			if ( inside.x + inside.w > outside.x + outside.w )
			{
				if ( clampSize )
				{ inside.w = outside.w; }
				else
				{ inside.x = outside.x + outside.w - inside.w; }
			}

			if ( inside.y + inside.h > outside.y + outside.h )
			{
				if ( clampSize )
				{ inside.h = outside.h; }
				else
				{ inside.y = outside.w + outside.h - inside.h; }
			}

			return inside;
		}

		FK_EXPORT UnicodeString Format( const wchar_t* fmt, ... );

		namespace Strings
		{
			typedef std::vector<FK2DEngine2::String> List;
			typedef std::vector<FK2DEngine2::UnicodeString> UnicodeList;

			FK_EXPORT void Split( const FK2DEngine2::String & str, const FK2DEngine2::String & seperator, Strings::List & outbits, bool bLeaveSeperators = false );
			FK_EXPORT void Split( const FK2DEngine2::UnicodeString & str, const FK2DEngine2::UnicodeString & seperator, Strings::UnicodeList & outbits, bool bLeaveSeperators = false );
			FK_EXPORT bool Wildcard( const FK2DEngine2::UITexObjSimpleInfo & strWildcard, const FK2DEngine2::UITexObjSimpleInfo & strHaystack );

			FK_EXPORT void ToUpper( FK2DEngine2::UnicodeString & str );
			FK_EXPORT void Strip( FK2DEngine2::UnicodeString & str, const FK2DEngine2::UnicodeString & chars );

			template <typename T>
			T TrimLeft( const T & str, const T & strChars )
			{
				T outstr = str;
				outstr.erase( 0, outstr.find_first_not_of( strChars ) );
				return outstr;
			}

			namespace To
			{
				FK_EXPORT bool Bool( const FK2DEngine2::String & str );
				FK_EXPORT int Int( const FK2DEngine2::String & str );
				FK_EXPORT float Float( const FK2DEngine2::String & str );
				FK_EXPORT float Float( const FK2DEngine2::UnicodeString & str );
				FK_EXPORT bool Floats( const FK2DEngine2::String & str, float* f, size_t iCount );
			}
		}
	}
}
//------------------------------------------------------------------------