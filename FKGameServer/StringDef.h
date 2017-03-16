/**
*	created:		2013-4-19   10:04
*	filename: 		StringDef
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
enum	string_define
{
	SD_EXECCMDERROR_BADCOMMAND,			//您输入了错误的命令
	SD_EXECCMDERROR_GMEXECCMDLEVELLOW,	//您的权限不够，无法执行该GM命令
	SD_EXECCMDERROR_PLAYEREXECCMDLEVELLOW,//您等级不够，无法使用该命令
	SD_CMDRESULTVALUEIS,				//命令返回值
	SD_CMDMAPERROR_SCRIPTNOTFOUND,		//命令映射失败，没有找到页面
	SD_CMDMAPERROR_CMDNOTFOUND,			//命令映射失败，没有找到内部命令
	SD_CMDMAPERROR_CMDALREADYREGISTERED,//命令已经被注册
	SD_MAX,
};
//------------------------------------------------------------------------
static char * g_xStrings[SD_MAX] = {
	"您输入了错误的命令",							//	SD_BAGCOMMAND,
	"您的权限不够，无法执行该GM命令！",				//	SD_GMEXECCMDLEVELLOW
	"您等级不够，无法使用该命令。",					//	SD_PLAYEREXECCMDLEVELLOW,
	"命令返回值: ",									//	SD_CMDRESULTVALUEIS,
	"命令映射失败，没有找到页面",					//	SD_CMDMAPERROR_SCRIPTNOTFOUND
	"命令映射失败，没有找到内部命令",				//	SD_CMDMAPERROR_CMDNOTFOUND
	"命令已经被注册",								//	SD_CMDMAPERROR_CMDALREADYREGISTERED,
};
//------------------------------------------------------------------------
inline const char * getstrings( string_define sd )
{
	if( (UINT)sd >= (UINT)SD_MAX )return "<NULL>";
	return g_xStrings[sd];
}
//------------------------------------------------------------------------