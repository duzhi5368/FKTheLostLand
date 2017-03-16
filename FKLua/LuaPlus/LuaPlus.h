/**
*	created:		2013-4-19   0:11
*	filename: 		LuaPlus
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "LuaPlusInternal.h"
#include "src/lua.h"
#include "src/lauxlib.h"
#include "LuaStackObject.h"
#include "LuaObject.h"
#include "LuaState.h"
#include "LuaTableIterator.h"
#include "LuaObject.inl"
#include "LuaStateOutFile.h"
#include "LuaHelper.h"
#include "LuaAutoBlock.h"
#include "LuaStackTableIterator.h"
#include "LuaCall.h"
#include "LuaFunction.h"
#include "LuaPlusCD.h"
//------------------------------------------------------------------------
void LuaState_UserStateOpen_Internal(lua_State* L);
void LuaState_UserStateFree_Internal(lua_State* L);
//------------------------------------------------------------------------