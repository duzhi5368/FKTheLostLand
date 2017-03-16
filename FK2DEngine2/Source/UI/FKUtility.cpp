/**
*	created:		2013-4-11   20:49
*	filename: 		FKUtility
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#ifdef _MSC_VER
	#pragma warning(disable:4267)	// ×ª»»size_tÎªint
#endif
//------------------------------------------------------------------------
#ifdef __MINGW32__
	#undef vswprintf
	#define vswprintf _vsnwprintf
#endif
//------------------------------------------------------------------------
#ifdef _MSC_VER
	#define FK_FNULL "NUL"
#else
	#define FK_FNULL "/dev/null"
#endif
//------------------------------------------------------------------------
#ifndef va_copy 
# ifdef __va_copy 
# define va_copy(DEST,SRC) __va_copy((DEST),(SRC)) 
# else 
# define va_copy(DEST, SRC) memcpy((&DEST), (&SRC), sizeof(va_list)) 
# endif 
#endif  
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	UnicodeString FK2DEngine2::Utility::Format( const wchar_t* fmt, ... )
	{
		va_list s;
		int len = 0;

		va_start( s, fmt );

		{	
			FILE* fnull = fopen( FK_FNULL, "wb" );
			va_list c;
			va_copy( c, s );
			len = vfwprintf( fnull, fmt, c );
			va_end( c );
			fclose( fnull );
		} 

		UnicodeString strOut;

		if (len > 0)
		{
			strOut.resize( len + 1 );
			va_list c;
			va_copy( c, s );
			len = vswprintf( &strOut[0], strOut.size(), fmt, c );
			va_end( c );
			strOut.resize( len );
		}

		va_end( s );

		return strOut;
	}
	//------------------------------------------------------------------------
	void FK2DEngine2::Utility::Strings::Split( const FK2DEngine2::String & str, const FK2DEngine2::String & seperator,
		Strings::List & outbits, bool bLeave )
	{
		int iOffset = 0;
		int iLength = str.length();
		int iSepLen = seperator.length();
		size_t i = str.find( seperator, 0 );

		while ( i != std::string::npos )
		{
			outbits.push_back( str.substr( iOffset, i - iOffset ) );
			iOffset = i + iSepLen;
			i = str.find( seperator, iOffset );

			if ( bLeave ) { iOffset -= iSepLen; }
		}

		outbits.push_back( str.substr( iOffset, iLength - iOffset ) );
	}
	//------------------------------------------------------------------------
	void FK2DEngine2::Utility::Strings::Split( const FK2DEngine2::UnicodeString & str, const FK2DEngine2::UnicodeString & seperator,
		Strings::UnicodeList & outbits, bool bLeave )
	{
		int iOffset = 0;
		int iLength = str.length();
		int iSepLen = seperator.length();
		size_t i = str.find( seperator, 0 );

		while ( i != std::wstring::npos )
		{
			outbits.push_back( str.substr( iOffset, i - iOffset ) );
			iOffset = i + iSepLen;
			i = str.find( seperator, iOffset );

			if ( bLeave ) { iOffset -= iSepLen; }
		}

		outbits.push_back( str.substr( iOffset, iLength - iOffset ) );
	}
	//------------------------------------------------------------------------
	int FK2DEngine2::Utility::Strings::To::Int( const FK2DEngine2::String & str )
	{
		if ( str == "" ) { return 0; }

		return atoi( str.c_str() );
	}
	//------------------------------------------------------------------------
	float FK2DEngine2::Utility::Strings::To::Float( const FK2DEngine2::String & str )
	{
		if ( str == "" ) { return 0.0f; }

		return ( float ) atof( str.c_str() );
	}
	//------------------------------------------------------------------------
	float FK2DEngine2::Utility::Strings::To::Float( const FK2DEngine2::UnicodeString & str )
	{
		return wcstod( str.c_str(), NULL );
	}
	//------------------------------------------------------------------------
	bool FK2DEngine2::Utility::Strings::To::Bool( const FK2DEngine2::String & str )
	{
		if ( str.size() == 0 ) { return false; }

		if ( str[0] == 'T' || str[0] == 't' || str[0] == 'y' || str[0] == 'Y' ) { return true; }

		if ( str[0] == 'F' || str[0] == 'f' || str[0] == 'n' || str[0] == 'N' ) { return false; }

		if ( str[0] == '0' ) { return false; }

		return true;
	}
	//------------------------------------------------------------------------
	bool FK2DEngine2::Utility::Strings::To::Floats( const FK2DEngine2::String & str, float* f, size_t iCount )
	{
		Strings::List lst;
		Strings::Split( str, " ", lst );

		if ( lst.size() != iCount ) { return false; }

		for ( size_t i = 0; i < iCount; i++ )
		{
			f[i] = Strings::To::Float( lst[i] );
		}

		return true;
	}
	//------------------------------------------------------------------------
	bool FK2DEngine2::Utility::Strings::Wildcard( const UITexObjSimpleInfo & strWildcard, const UITexObjSimpleInfo & strHaystack )
	{
		const UnicodeString & W = strWildcard.GetUnicode();
		const UnicodeString & H = strHaystack.GetUnicode();

		if ( strWildcard == "*" ) { return true; }

		int iPos = W.find( L"*", 0 );

		if ( iPos == UnicodeString::npos ) { return strWildcard == strHaystack; }

		if ( iPos > 0 && W.substr( 0, iPos ) != H.substr( 0, iPos ) )
		{ return false; }

		if ( iPos != W.length() - 1 )
		{
			UnicodeString strEnd = W.substr( iPos + 1, W.length() );

			if ( strEnd != H.substr( H.length() - strEnd.length(), H.length() ) )
			{ return false; }
		}

		return true;
	}
	//------------------------------------------------------------------------
	void FK2DEngine2::Utility::Strings::ToUpper( FK2DEngine2::UnicodeString & str )
	{
		transform( str.begin(), str.end(), str.begin(), towupper );
	}
	//------------------------------------------------------------------------
	void FK2DEngine2::Utility::Strings::Strip( FK2DEngine2::UnicodeString & str, const FK2DEngine2::UnicodeString & chars )
	{
		FK2DEngine2::UnicodeString Source = str;
		str = L"";

		for ( unsigned int i = 0; i < Source.length(); i++ )
		{
			if ( chars.find( Source[i] ) != FK2DEngine2::UnicodeString::npos )
			{ continue; }

			str += Source[i];
		}
	}
	//------------------------------------------------------------------------
	mbstate_t out_cvt_state;
	mbstate_t in_cvt_state;
	//------------------------------------------------------------------------
	typedef std::codecvt<wchar_t, char, mbstate_t> CodecvtFacet;
	//------------------------------------------------------------------------
	namespace Utility
	{
		FK2DEngine2::String UnicodeToString( const FK2DEngine2::UnicodeString & strIn )
		{
			/*
			if ( !strIn.length() ) { return ""; }

			std::locale sys_loc("");

			const wchar_t* src_wstr = strIn.c_str();
			const size_t MAX_UNICODE_BYTES = 4;
			const size_t BUFFER_SIZE = strIn.size() * MAX_UNICODE_BYTES + 1;

			char* extern_buffer = new char[BUFFER_SIZE];
			memset(extern_buffer, 0, BUFFER_SIZE);

			const wchar_t* intern_from = src_wstr;
			const wchar_t* intern_from_end = intern_from + strIn.size();
			const wchar_t* intern_from_next = 0;
			char* extern_to = extern_buffer;
			char* extern_to_end = extern_to + BUFFER_SIZE;
			char* extern_to_next = 0;

			typedef std::codecvt<wchar_t, char, mbstate_t> CodecvtFacet;

			CodecvtFacet::result cvt_rst =
				std::use_facet<CodecvtFacet>(sys_loc).out(
				out_cvt_state,
				intern_from, intern_from_end, intern_from_next,
				extern_to, extern_to_end, extern_to_next);
			if (cvt_rst != CodecvtFacet::ok) {
				switch(cvt_rst) 
				{
				case CodecvtFacet::partial:
					std::cerr << "partial";
					break;
				case CodecvtFacet::error:
					std::cerr << "error";
					break;
				case CodecvtFacet::noconv:
					std::cerr << "noconv";
					break;
				default:
					std::cerr << "unknown";
				}
				std::cerr  << ", please check out_cvt_state." << std::endl;
			}
			std::string result = extern_buffer;

			delete []extern_buffer;

			return result;
			*/
			if( strIn.size() <= 0 )
			{
				return std::string("");
			}
			int nLen = WideCharToMultiByte(CP_ACP, 0, strIn.c_str(), -1, NULL, 0, NULL, NULL);
			if (nLen<= 0) return std::string("");
			char* pszDst = new char[nLen];
			if (NULL == pszDst) return std::string("");
			WideCharToMultiByte(CP_ACP, 0, strIn.c_str(), -1, pszDst, nLen, NULL, NULL);
			pszDst[nLen -1] = 0;
			std::string strTemp(pszDst);
			delete [] pszDst;
			return strTemp;
		}
		//------------------------------------------------------------------------
		FK2DEngine2::UnicodeString StringToUnicode( const FK2DEngine2::String & strIn )
		{
			/*
			if ( !strIn.length() ) { return L""; }

			std::locale sys_loc("");

			const char* src_str = strIn.c_str();
			const size_t BUFFER_SIZE = strIn.size() + 1;

			wchar_t* intern_buffer = new wchar_t[BUFFER_SIZE];
			wmemset(intern_buffer, 0, BUFFER_SIZE);

			const char* extern_from = src_str;
			const char* extern_from_end = extern_from + strIn.size();
			const char* extern_from_next = 0;
			wchar_t* intern_to = intern_buffer;
			wchar_t* intern_to_end = intern_to + BUFFER_SIZE;
			wchar_t* intern_to_next = 0;

			typedef std::codecvt<wchar_t, char, mbstate_t> CodecvtFacet;

			CodecvtFacet::result cvt_rst =
				std::use_facet<CodecvtFacet>(sys_loc).in(
				in_cvt_state,
				extern_from, extern_from_end, extern_from_next,
				intern_to, intern_to_end, intern_to_next);
			if (cvt_rst != CodecvtFacet::ok) {
				switch(cvt_rst) 
				{
				case CodecvtFacet::partial:
					std::cerr << "partial";
					break;
				case CodecvtFacet::error:
					std::cerr << "error";
					break;
				case CodecvtFacet::noconv:
					std::cerr << "noconv";
					break;
				default:
					std::cerr << "unknown";
				}
				std::cerr << ", please check in_cvt_state." << std::endl;
			}
			std::wstring result = intern_buffer;

			delete []intern_buffer;

			return result;
			*/
			if( strIn.size() <= 0 )
			{
				return std::wstring(L"");
			}
			int nLen = strIn.size();
			int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strIn.c_str(), nLen, 0, 0);
			if(nSize <= 0) return std::wstring(L"");
			WCHAR *pwszDst = new WCHAR[nSize+1];
			if( NULL == pwszDst) return std::wstring(L"");
			MultiByteToWideChar(CP_ACP, 0,(LPCSTR)strIn.c_str(), nLen, pwszDst, nSize);
			pwszDst[nSize] = 0;
			if( pwszDst[0] == 0xFEFF) // skip Oxfeff
				for(int i = 0; i < nSize; i ++) 
					pwszDst[i] = pwszDst[i+1]; 
			std::wstring wcharString(pwszDst);
			delete pwszDst;
			return wcharString;
		}
	}
	//------------------------------------------------------------------------
}
//------------------------------------------------------------------------
FK_EXPORT FK2DEngine2::Controls::Base* FK2DEngine2::HoveredControl = NULL;
FK_EXPORT FK2DEngine2::Controls::Base* FK2DEngine2::KeyboardFocus = NULL;
FK_EXPORT FK2DEngine2::Controls::Base* FK2DEngine2::MouseFocus = NULL;
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	//------------------------------------------------------------------------
	namespace Debug
	{
		void Msg( const char* str, ... )
		{
			char strOut[1024];
			va_list s;
			va_start( s, str );
			vsnprintf( strOut, sizeof( strOut ), str, s );
			va_end( s );
			FKUtil_OutputDebugCharString( strOut );
		}
#ifdef UNICODE
		void Msg( const wchar_t* str, ... )
		{
			wchar_t strOut[1024];
			va_list s;
			va_start( s, str );
			vswprintf( strOut, sizeof( strOut ), str, s );
			va_end( s );
			FKUtil_OutputDebugWideString( strOut );
		}
#endif
		void AssertCheck( bool b, const char* strMsg )
		{
			if ( b ) { return; }

			Msg( "Assert: %s\n", strMsg );
#ifdef _WIN32
			MessageBoxA( NULL, strMsg, "Assert", MB_ICONEXCLAMATION | MB_OK );
			_asm { int 3 }
#endif
		}
	}
	//------------------------------------------------------------------------
	namespace Input
	{
		void Blur()
		{
			if ( KeyboardFocus )
			{ KeyboardFocus->Blur(); }
		}
	}
	//------------------------------------------------------------------------
}
//------------------------------------------------------------------------