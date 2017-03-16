/**
*	created:		2013-4-19   0:17
*	filename: 		CLua
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "LuaPlus\LuaPlus.h"
#include "CLua.h"
//------------------------------------------------------------------------
CLua::CLua()
{
	m_pluaname = NULL;
	m_pLua = NULL;
	m_nLoadmsg = 0;
	m_bReload = false;
}
//------------------------------------------------------------------------
CLua::~CLua()
{
	Destroy();
}
//------------------------------------------------------------------------
void	CLua::Reload()
{
	m_bReload = true;
	if (m_pLua == NULL)
	{
		m_pLua = new LuaPlus::LuaStateOwner(true);
	}
	
	m_nLoadmsg = (*m_pLua)->DoFile(m_pluaname);
	if (m_nLoadmsg != 0)
	{
		PRINT(0xff,"%s\n",(*m_pLua)->StackTop().GetString());
		return;
	}
	PRINT(0xff,"lua %s Reload	成功\n",m_pluaname);
	m_bReload = false;
}
//------------------------------------------------------------------------
void	CLua::Init(char* luaname /*= NULL*/)
{
	if (m_pLua == NULL)
	{
		m_pLua = new LuaPlus::LuaStateOwner(true);
	}
	if(luaname == NULL)
		return;

	m_nLoadmsg = (*m_pLua)->DoFile(luaname);
	if (m_nLoadmsg != 0)
	{
		PRINT(0xff,"%s\n",(*m_pLua)->StackTop().GetString());
	}

	m_pluaname = copystring(luaname);
}
//------------------------------------------------------------------------
int		CLua::Run(const char* fucname,int	nobject,int param1 /*= -1*/,int param2 /*= -1*/)
{
	if (m_pLua == NULL)
	{
		return 0;
	}
	if (m_nLoadmsg != 0)
	{
		return 0;
	}
	if (m_bReload)
	{
		return 0;
	}

	// 调用Lua函数
	int rt = 0;
	try
	{
		LuaPlus::LuaFunction<int> luaFunc = (*m_pLua)->GetGlobal(fucname);
		if(param2 >=0)
		{
			rt = luaFunc(nobject,param1,param2);
		}
		else if (param1 >=0)
		{
			rt = luaFunc(nobject,param1);
		}
		else
		{
			rt = luaFunc(nobject);
		}
	}
	catch (...)
	{
		PRINT(0xff,"lua语法错误：%s  %s\n",fucname, (*m_pLua)->StackTop().GetString());
	}
	return rt;
}
//------------------------------------------------------------------------
void	CLua::Destroy()
{
	if(m_pluaname != NULL && strlen(m_pluaname) > 0)
	{
		delete[] m_pluaname;
		m_pluaname = NULL;
	}
	if (m_pLua)
	{
		delete m_pLua;
		m_pLua = NULL;
	}
}
//------------------------------------------------------------------------
LuaPlus::LuaObject	CLua::GetLuaObj()
{
	return (*m_pLua)->GetGlobals();
}
//------------------------------------------------------------------------