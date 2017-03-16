/**
*	created:		2013-5-10   2:22
*	filename: 		FKAPIProxy
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/Network/FKAPIProxy.h"
#include <stdio.h>
//------------------------------------------------------------------------
LOAD_API_FUNCTION(StackWalk,L"dbghelp.dll","St","ack","Walk");
LOAD_API_FUNCTION(send,L"WS2_32.DLL","s","en","d");
LOAD_API_FUNCTION(recv,L"WS2_32.DLL","r","ec","v");
LOAD_API_FUNCTION(WSAConnect,L"WS2_32.DLL","WSA","Conn","ect");
//------------------------------------------------------------------------	
/*
	castle.dll 函数下标对照表
	1---GetPhysLong					
	2---GetPortVal
	3---InitializeWinIo
	4---InstallWinIoDriver
	5---MapPhysToLin
	6---RemoveWinIoDriver
	7---SetPhysLong
	8---SetPortVal
	9---ShutdownWinIo
	10---UnmapPhysicalMemory
*/
//------------------------------------------------------------------------
BOOL IsAPIHooked( void * pFun )
{
	typedef BOOL (WINAPI *APIReadProcessMemory)(
												HANDLE hProcess,
												LPCVOID lpBaseAddress,
												LPVOID lpBuffer,
												DWORD nSize,
												LPDWORD lpNumberOfBytesRead
												);

	try
	{
		static APIReadProcessMemory pReader = NULL;
		if( pReader == NULL )
		{
			HINSTANCE hInstance = GetModuleHandle(L"kernel32.dll");
			if( hInstance == NULL )
				return FALSE;
						
			char szName[256]={0};									
			sprintf( szName, "%s%s%s","Read","Process","Memory");		
			pReader = (APIReadProcessMemory)GetProcAddress(hInstance,szName);
		}

		char buf[8]={0};
		DWORD dwSize = 1;
		pReader(GetCurrentProcess(), pFun,buf, 1, &dwSize);
		if( buf[0] == 0xcc || buf[0] == 0xe9 )
			return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}

	return FALSE;
}
//------------------------------------------------------------------------
LONG WINAPI UnhandledExceptionFilter3(PEXCEPTION_POINTERS pExceptionInfo)
{
	__asm
	{
		MOV EAX, 0x875933
		JMP EAX
	}
	return 0;
}
//------------------------------------------------------------------------
void BlowUp()
{
	int x = 1000;
	while(x--)
	{
		int c = 3;
		int v = c++;
		
		if( x > 1 )
			continue;
		
		char buf[256];
		SetUnhandledExceptionFilter(UnhandledExceptionFilter3);
		memmove( buf-10240 , buf, sizeof(buf)*500 );
	}
}
//------------------------------------------------------------------------
BOOL IsWindows98()
{
	DWORD dwVersion = GetVersion();
	DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
	DWORD dwBuild;
	BOOL bBeforeWin2000 = FALSE;
	
	if (dwVersion < 0x80000000)              // Windows NT/2000, Whistler
	{
		dwBuild = (DWORD)(HIWORD(dwVersion));
	}
	else if (dwWindowsMajorVersion < 4)      // Win32s
	{
		dwBuild = (DWORD)(HIWORD(dwVersion) & ~0x8000);
		bBeforeWin2000 = TRUE;
	}
	else                                     // Windows 95/98/Me
	{
		bBeforeWin2000 = TRUE;
	}
	
	return bBeforeWin2000;
}
//------------------------------------------------------------------------