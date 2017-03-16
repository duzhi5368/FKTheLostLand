/**
*	created:		2013-4-11   22:16
*	filename: 		FKHook
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Hook;
//------------------------------------------------------------------------
std::list<BaseHook*>	g_HookList;
//------------------------------------------------------------------------
void FK2DEngine2::Hook::AddHook( BaseHook* pHook )
{
	g_HookList.push_back( pHook );
}
//------------------------------------------------------------------------
void FK2DEngine2::Hook::RemoveHook( BaseHook* pHook )
{
	g_HookList.remove( pHook );
}
//------------------------------------------------------------------------
HookList & FK2DEngine2::Hook::GetHookList()
{
	return g_HookList;
}
//------------------------------------------------------------------------