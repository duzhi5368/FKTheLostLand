/**
*	created:		2013-5-10   7:39
*	filename: 		IFKAppNetworkLink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <winsock2.h>
#include "FKClientLink.h"
//------------------------------------------------------------------------
enum EnumNetworkLinkState
{
	eNLS_Unknow			= 0,
	eNLS_LoginSvr		= 1,	// 登陆服务器
	eNLS_CharSelSvr		= 2,	// 角色选择服务器
	eNLS_GameSvr		= 3,	// 游戏主服务器
	eNLS_Max,
};
//------------------------------------------------------------------------
struct IFKAppNetworkLink : public IClientLinkSink
{
	// 发送数据包
	virtual int				Send(LPCSTR buf, int nLen) = NULL;

	// 取得IClientLink指针, 使用方法更丰富
	virtual IClientLink *	GetClientLink(void) = NULL;

	// 返回当前连接到了哪一个状态
	virtual int				GetType(void) = NULL;
};
//------------------------------------------------------------------------