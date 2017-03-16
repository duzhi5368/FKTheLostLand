/**
*	created:		2013-4-23   15:06
*	filename: 		FKWrapperInclude
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "FK2DEngine2.h"
#include "Include/FKEngine.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
FK_API FK2DEngine2::IEngine * GetEngine()
{
	if( g_pEngineInstance == NULL )
	{
		g_pEngineInstance = new CEngine();
	}
	return g_pEngineInstance;
}
//------------------------------------------------------------------------
#ifndef FK_STATIC

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif
//------------------------------------------------------------------------