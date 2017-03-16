/**
*	created:		2013-4-11   17:06
*	filename: 		FKMacros
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>
#include <algorithm>
//------------------------------------------------------------------------
#ifdef _WIN32
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#include <windows.h>

	#define FKUtil_OutputDebugCharString( lpOutputString ) OutputDebugStringA( lpOutputString )
	#define FKUtil_OutputDebugWideString( lpOutputString ) OutputDebugStringW( lpOutputString )

#elif defined(__APPLE__)

	#include <CoreFoundation/CoreFoundation.h>
	#define FKUtil_OutputDebugCharString( lpOutputString )
	#define FKUtil_OutputDebugWideString( lpOutputString )

#elif defined(__linux__)

	#define FKUtil_OutputDebugCharString( lpOutputString )
	#define FKUtil_OutputDebugWideString( lpOutputString )

#else

#error "Not support platform."

#endif
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	template <typename T>
	inline T Min( T a, T b )
	{
		return a < b ? a : b;
	}

	template <typename T>
	inline T Max( T a, T b )
	{
		return a > b ? a : b;
	}

	template <typename T>
	inline T Clamp( T current, T vmin, T vmax )
	{
		if ( current >= vmax ) { return vmax; }

		if ( current <= vmin ) { return vmin; }

		return current;
	}

	template <typename T, typename T2>
	inline T Approach( T fCurrent, T fTarget, T2 fDelta )
	{
		if ( fCurrent < fTarget )
		{
			fCurrent += fDelta;

			if ( fCurrent > fTarget ) { return fTarget; }
		}
		else if ( fCurrent > fTarget )
		{
			fCurrent -= fDelta;

			if ( fCurrent < fTarget ) { return fTarget; }
		}

		return fCurrent;
	}
}
//------------------------------------------------------------------------