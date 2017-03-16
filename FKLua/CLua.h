/**
*	created:		2013-4-19   0:10
*	filename: 		CLua
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CAliveObject;
//------------------------------------------------------------------------
class CLua
{
public:
	CLua();
	virtual ~CLua();
public:
	void	Init(char* luaname = NULL);
	int		Run(const char* fucname,int	nobject,int param1 = -1,int param2 = -1);
	void	Destroy();
public:
	void	Reload();
public:
	LuaPlus::LuaObject	GetLuaObj();
	LuaPlus::LuaStateOwner*	m_pLua;
private:
	char*	m_pluaname;
	int		m_nLoadmsg;
	bool	m_bReload;
};
//------------------------------------------------------------------------
#define REGISTER_FUNC(lua,name,func)		lua.GetLuaObj().RegisterDirect(name,func);
#define REGISTER_MEMFUNC(lua,name,cla,func)	lua.GetLuaObj().RegisterDirect(name,cla,func);
//------------------------------------------------------------------------