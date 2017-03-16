/**
*	created:		2013-4-28   2:43
*	filename: 		FKSystemInfo
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKSystemInfo.h"
#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h>
//------------------------------------------------------------------------
#pragma comment(lib, "winmm.lib ") 
//------------------------------------------------------------------------
char* siOsNames[] = 
{
	"Windows NT 4",
	"Windows 2000",
	"Windows XP",
	"Windows .NET",
	"Windows 95",
	"Windows 98",
	"Windows ME",
	"Linux",
	"FreeBSD",
	"Unknown"
};
//------------------------------------------------------------------------
static char errorMsg[255] = "No errors";
//------------------------------------------------------------------------
const char* siGetLastError(void)
{
	return errorMsg;
}
//------------------------------------------------------------------------
void _siSetLastError(const char* errorMessage)
{
	strcpy(errorMsg, errorMessage);
	return;
}
//------------------------------------------------------------------------
/* Returns the total amount of physical memory in the system */
int siGetPhysicalMem(int units)
{
	MEMORYSTATUS memInfo;
	GlobalMemoryStatus(&memInfo);

	return (int)(memInfo.dwTotalPhys / units);
}
//------------------------------------------------------------------------
/* Returns the amount of available memory in the system */
int siGetAvailableMem(int units)
{
	MEMORYSTATUS memInfo;
	GlobalMemoryStatus(&memInfo);

	return (int)(memInfo.dwAvailPhys / units);
}
//------------------------------------------------------------------------
/* Returns the wstring corresponding to the Operating System's name */
char* siGetOsName(void)
{
	OSVERSIONINFO osInfo;

	/* Get the info */
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osInfo);

	/* Figure out what it is ... */
	if(osInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		/* NT 5 ... */
		if(osInfo.dwMajorVersion == 5)
		{
			/* 5.2 - Windows .NET Server */
			if(osInfo.dwMinorVersion == 2)
				return siOsNames[SI_OS_DOTNET];

			/* 5.1 - Windows XP */
			else if(osInfo.dwMinorVersion == 1)
				return siOsNames[SI_OS_XP];

			/* 5.0 - Windows 2000 */
			else if(osInfo.dwMinorVersion == 0)
				return siOsNames[SI_OS_2K];
		}
		else
		{
			/* NT 4 (or 3 ... ) */
			return siOsNames[SI_OS_NT];
		}
	}

	else if(osInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		if(osInfo.dwMinorVersion == 0)
			return siOsNames[SI_OS_95];

		else if(osInfo.dwMinorVersion == 10)
			return siOsNames[SI_OS_98];

		else if(osInfo.dwMinorVersion == 90)
			return siOsNames[SI_OS_ME];
	}

	return siOsNames[SI_OS_UNKNOWN];
}
//------------------------------------------------------------------------
/* Returns the version number of the Operating System */
siVersion siGetOsVersion(void)
{
	siVersion versionInfo;
	OSVERSIONINFO osInfo;

	/* Get the info */
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osInfo);


	/* Fill in the struct */
	versionInfo.major = osInfo.dwMajorVersion;
	versionInfo.minor = osInfo.dwMinorVersion;

	return versionInfo;
}
//------------------------------------------------------------------------
/* Returns an SI_ identifier corresponding to the operating system type */
unsigned int siGetOsType(void)
{
	OSVERSIONINFO osInfo;

	/* Get the info */
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osInfo);

	/* Figure out what it is ... */
	if(osInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		/* NT 5 ... */
		if(osInfo.dwMajorVersion == 5)
		{
			/* 5.2 - Windows .NET Server */
			if(osInfo.dwMinorVersion == 2)
				return SI_OS_DOTNET;

			/* 5.1 - Windows XP */
			else if(osInfo.dwMinorVersion == 1)
				return SI_OS_XP;

			else if(osInfo.dwMinorVersion == 0)
				return SI_OS_2K;
		}
		else
		{
			/* NT 4 (or 3 ... ) */
			return SI_OS_NT;
		}
	}

	else if(osInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		if(osInfo.dwMinorVersion == 0)
			return SI_OS_95;

		else if(osInfo.dwMinorVersion == 10)
			return SI_OS_98;

		else if(osInfo.dwMinorVersion == 90)
			return SI_OS_ME;
	}

	return SI_OS_UNKNOWN;
}
//------------------------------------------------------------------------
/* Returns a wstring corresponding to processor type */
/* We can't use IsProcessorFeaturePresent() because that only works on NT ... */
siCpu siGetCpuType(void)
{
	siCpu cpuInfo;
	int cpuVal;
	int a1, a2, a3;


#ifndef  __GNUC__


	/* Use CPUID to gather information ... */

	__asm
	{
		mov eax, 0;
		cpuid;
		mov cpuVal, eax;
		mov a1, ebx;
		mov a2, edx;
		mov a3, ecx;
	}


#else


	/* AT&T Syntax for doing exactly the same thing ... */

	__asm__("
		movl $0, %%eax
		cpuid
		"
		:"=a" (cpuVal), "=b" (a1), "=d" (a2), "=c" (a3)
		);


#endif


	/* Copy into a character array */
	memcpy(&(cpuInfo.idString[0]), &a1, 4);
	memcpy(&(cpuInfo.idString[4]), &a2, 4);
	memcpy(&(cpuInfo.idString[8]), &a3, 4);
	cpuInfo.idString[12] = '\0';

	/* Check for MMX */	
	if(cpuVal && (1 << 23))
		cpuInfo.hasMMX = 1;
	else
		cpuInfo.hasMMX = 0;

	/* Check for SSE */
	if(cpuVal && (1 << 25))
		cpuInfo.hasSSE = 1;
	else
		cpuInfo.hasSSE = 0;

	/* Check for SSE2 */
	if(cpuVal && (1 << 26))
		cpuInfo.hasSSE2 = 1;
	else
		cpuInfo.hasSSE2 = 0;

	/* This last check is for 3dNow! */

#ifndef  __GNUC__


	/* Use CPUID to gather information ... */

	__asm
	{
		mov eax, 0x80000001;
		cpuid;
		mov cpuVal, edx;
	}


#else


	/* AT&T Syntax for doing exactly the same thing ... */

	__asm__("
		movl $0x80000001, %%eax
		cpuid
		"
		:"=d" (cpuVal)
		);


#endif

	/* Only run this check if we have an AMD CPU */
	/* FIXME: probably not the best way to do this ... */
	if(!strcmp(cpuInfo.idString, "AuthenticAMD"))
	{
		/* Check for 3dNow! */
		if(cpuVal && (1 << 31))
			cpuInfo.has3dNow = 1;
		else
			cpuInfo.has3dNow = 0;
	}	
	else
		cpuInfo.has3dNow = 0;

	return cpuInfo;
}
//------------------------------------------------------------------------
/* RDTSC macro used for portability */
#ifndef  __GNUC__

#define TIMESTAMP(x)	\
	__asm				\
{					\
	cpuid			\
	_emit 0x0F		\
	_emit 0x31		\
	mov [x], eax	\
}

#else

#define TIMESTAMP(x) \
	__asm__ __volatile__ ("cpuid\n\trdtsc\n\t":"=a" (x));

#endif
//------------------------------------------------------------------------
#pragma warning (disable: 4035)
__int64 GetCycleCount(){__asm _emit 0x0F __asm _emit 0x31}
#pragma warning (default: 4035)
//------------------------------------------------------------------------
/*
* Returns processor speed in MHZ
* NOTE --- runs for 1 SECOND to get a reasonably accurate reading
*/
unsigned int siGetCpuSpeed(void)
{
	int	timeStart = 0;
	__int64 startTicks,endTicks,totalTicks;

	__int64 cpuSpeed = 0;

	startTicks = GetCycleCount();

	timeStart = timeGetTime();

	/* One second delay ... */
	while((timeGetTime() - timeStart) <= 1000)
	{
		/* Do nothing ... */
	}

	endTicks = GetCycleCount();

	/* Calculate clock speed */
	totalTicks = endTicks - startTicks;
	cpuSpeed = totalTicks / 1000000;

	return (int)cpuSpeed;
}
//------------------------------------------------------------------------