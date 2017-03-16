/**
*	created:		2013-4-29   22:18
*	filename: 		FKStringConvert
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKStringConvert.h"

#include <sstream>
#include <algorithm>
#include <cctype>
//------------------------------------------------------------------------
#define ci_strcmp _wcsicmp
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		//------------------------------------------------------------------------
		const wchar_t StringUtil_WhiteSpaceChars[] = L" \t\n\r";
		//------------------------------------------------------------------------
		template <class T>
		bool from_string(T& t, const std::wstring& s, std::ios_base& (*f)(std::ios_base&))
		{
			std::wistringstream iss(s);
			return !(iss >> f >> t).fail();
		}
		//------------------------------------------------------------------------
		template <class T>
		std::wstring to_string(T& t, std::ios_base& (*f)(std::ios_base&))
		{
			std::wstringstream ss;
			ss << f << t;
			return ss.str();
		}
		//------------------------------------------------------------------------
		int StringToInt( const std::wstring& s )
		{
			int retVal = 0;
			from_string<int>( retVal, s, std::dec );
			return retVal;
		}
		//------------------------------------------------------------------------
		float StringToFloat( const std::wstring& s )
		{
			float retVal = 0.0f;
			from_string<float>( retVal, s, std::dec );
			return retVal;
		}
		//------------------------------------------------------------------------
		bool StringToBool( const std::wstring& s )
		{
			if( !ci_strcmp( s.c_str(), L"true") )
				return true;
			else if( !ci_strcmp(s.c_str(), L"false") )
				return false;
			return StringToInt(s) != 0;
		}
		//------------------------------------------------------------------------
		FK2DEngine2::math::Vector2 StringToVector2( const std::wstring& s )
		{
			std::vector< std::wstring > split = SplitString(s);
			FK2DEngine2::math::Vector2 retVal;

			if( split.size() > 0 )
				retVal.X = StringToFloat(split[0]);

			if( split.size() > 1 )
				retVal.Y = StringToFloat(split[1]);

			return retVal;
		}
		//------------------------------------------------------------------------
		std::wstring IntToString( int val )
		{
			return to_string( val, std::dec );
		}
		//------------------------------------------------------------------------
		std::wstring FloatToStr( float val )
		{
			return to_string( val, std::dec );
		}
		//------------------------------------------------------------------------
		std::wstring BoolToStr( bool val )
		{
			return IntToString( val );
		}
		//------------------------------------------------------------------------
		std::wstring Vector2ToString( const FK2DEngine2::math::Vector2& val )
		{
			return FloatToStr( val.X ) + L" " + FloatToStr( val.Y );
		}
		//------------------------------------------------------------------------
		std::wstring ToUpper( const std::wstring& s )
		{
			std::wstring retVal = s;
			std::transform(retVal.begin(), retVal.end(), retVal.begin(),
				(int(*)(int)) std::toupper);

			return retVal;
		}
		//------------------------------------------------------------------------
		std::wstring ToLower( const std::wstring& s )
		{
			std::wstring retVal = s;
			std::transform(retVal.begin(), retVal.end(), retVal.begin(),
				(int(*)(int)) std::tolower);

			return retVal;
		}
		//------------------------------------------------------------------------
		std::vector< std::wstring > SplitString( const std::wstring& splitMe, const std::wstring& splitChars, 
			bool bRemoveEmptyEntries /*=true*/)
		{
			std::vector< std::wstring > retVal;

			std::wstring buildString;
			for ( unsigned int i = 0; i < splitMe.length(); i++ )
			{
				wchar_t ch = splitMe[i];
				if( splitChars.find( ch ) != std::wstring::npos)
				{
					//Add the build wstring to our return val
					if( !bRemoveEmptyEntries || buildString.length() > 0 )
						retVal.push_back( buildString );
					buildString.clear();
				}
				else
				{
					buildString += ch;
				}
			}

			//handle any dangling strings
			if( buildString.length() > 0 )
				retVal.push_back( buildString );

			return retVal;
		}
		//------------------------------------------------------------------------
		std::vector< std::wstring > SplitString( const std::wstring& splitMe )
		{
			return SplitString( splitMe, StringUtil_WhiteSpaceChars );
		}
		//------------------------------------------------------------------------
		std::wstring TrimString( const std::wstring& trimMe, const std::wstring& trimChars )
		{
			std::wstring retVal;

			if( trimChars.length() == 0 )
				return retVal;

			//trim from the front
			int trimStart = -1;
			for( unsigned int i = 0; i < trimMe.length(); i++ )
			{
				wchar_t ch = trimMe[i];
				if( trimChars.find(ch) == std::wstring::npos)
				{
					trimStart = i;
					break;
				}
			}

			if( trimStart >= 0 && trimStart < ((int)trimMe.length()) )
			{
				for( int i = (int)trimMe.length()-1; i >= 0; i-- )
				{
					wchar_t ch = trimMe[i];
					if( trimChars.find(ch) == std::wstring::npos )
					{
						retVal = trimMe.substr( trimStart, i - trimStart + 1);
						break;
					}
				}
			}

			return retVal;
		}
		//------------------------------------------------------------------------
		std::wstring TrimString( const std::wstring& trimMe )
		{
			return TrimString( trimMe, StringUtil_WhiteSpaceChars );
		}
		//------------------------------------------------------------------------
		void GetCarCdr( std::vector< std::wstring >& inputStrings, std::wstring& car,
			std::wstring& cdr, int numInputStrings )
		{
			if( inputStrings.size() == 0 )
				return;

			if( numInputStrings < 0 )
				numInputStrings = (int)inputStrings.size();

			car = inputStrings[0];
			for( int i = 1; i < numInputStrings; i++ )
			{
				cdr += inputStrings[i];
				if( i < numInputStrings - 1 )
					cdr += L" ";

			}
		}
		//------------------------------------------------------------------------
		bool IsCharOrNum( const char* iName )
		{ 
			bool bRet = false;
			while(*iName)
			{
				if((*iName)&0x80)		//是汉字
				{
					//bRet = true;
					//iName++;		//知道是汉字的话跳过一个字节检测
					return false;
				}
				else if((*iName>='a'&&*iName<='z'||*iName>='A'&&*iName<='Z')||((*iName)>='0'&&(*iName)<='9'))
				{
					bRet = true;  
				} 
				else{
					bRet = false;
					break;
				}
				iName++;
			}
			return bRet;
		};
		//------------------------------------------------------------------------
	}
}