/**
*	created:		2013-4-16   4:47
*	filename: 		xMtVerify
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#pragma comment( lib, "USER32" )
//------------------------------------------------------------------------
#include <crtdbg.h>
//------------------------------------------------------------------------
#define	MTASSERT(a)	_ASSERTE(a)
#define	MTVERIFY(a) if( !(a) )PrintError( #a, __FILE__, __LINE__, GetLastError() );
//------------------------------------------------------------------------
__inline void PrintError( wchar_t* linedesc, wchar_t* filename, int lineno, DWORD errnum )
{
	wchar_t*	lpBuffer;
	char	errbuf[256];
#ifdef _WINDOWS
	char	modulename[MAX_PATH];
#else
	DWORD	numread;
#endif
	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM, NULL, errnum, LANG_NEUTRAL, (LPTSTR)&lpBuffer,0, NULL );
	wsprintf( errbuf, "\n在文件 %s 的 %d 行进行的下列调用失败: \n\n"
		"     %s\n\n原因: %s\n", filename, lineno, linedesc, lpBuffer );
#ifndef _WINDOWS
	WriteFile( GetStdHandle( STD_ERROR_HANDLE ), errbuf, (int)strlen( errbuf ), &numread, FALSE );
	Sleep( 3000 );
#else
	GetModuleFileName( NULL, modulename, MAX_PATH );
	MessageBox( NULL, errbuf, modulename, 
		MB_ICONWARNING|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND);
#endif
	exit( EXIT_FAILURE );
}
//------------------------------------------------------------------------