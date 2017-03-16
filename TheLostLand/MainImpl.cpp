/**
*	created:		2013-5-3   20:32
*	filename: 		MainImpl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "MainImpl.h"
#include "ServerList.h"
#include "DeveloperList.h"
//------------------------------------------------------------------------
// 加载配置文件
bool InitConfig()
{
	// 加载服务器列表
	if( !CServerList::GetInstance()->LoadFromFile( SERVER_LIST_FILE ) )
	{
		FKTRACE( L"加载服务器列表失败." );
		return false;
	}

	// 加载开发人员列表
	if( !CDeveloperList::GetInstance()->LoadFromFile( DEVELOPER_LIST_FILE ) )
	{
		FKTRACE( L"加载开发人员列表失败." );
		return false;
	}
	return true;
}
//------------------------------------------------------------------------