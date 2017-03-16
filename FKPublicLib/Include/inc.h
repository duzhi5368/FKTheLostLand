/**
*	created:		2013-4-16   5:08
*	filename: 		inc
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#define	WIN32_LEAN_AND_MEAN
//------------------------------------------------------------------------
#include <winsock2.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib")
//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------
#include "..\..\FKxLib\xlib.h"
#include "Gamedefine.h"
//------------------------------------------------------------------------
typedef union tagServerId
{
	struct
	{
		BYTE	bType;	//	服务器类型	参见 servertype
		BYTE	bGroup;	//	服务器组
		BYTE	bId;	//	服务器唯一标识
		BYTE	bIndex;	//	服务器在服务器中心的注册顺序(由服务器中心负责填写)
	};
	DWORD 	dwId;
}ServerId;
//------------------------------------------------------------------------
enum	servertype
{
	ST_UNKNOWN = 0,
	ST_SERVERCENTER,	// 中心服务器
	ST_DATABASESERVER,	// 数据库服务器
	ST_LOGINSERVER,		// 登陆服务器
	ST_SELCHARSERVER,	// 选人服务器
	ST_GAMESERVER,		// 游戏服务器
};
//------------------------------------------------------------------------
inline	servertype GetServerTypeByName( const char * pszName )
{
	if( pszName == NULL )return ST_UNKNOWN;
	if( stricmp( pszName, "服务器中心" ) == 0 )return ST_SERVERCENTER;
	if( stricmp( pszName, "数据库服务器" ) == 0 )return ST_DATABASESERVER;
	if( stricmp( pszName, "登陆服务器" ) == 0 )return ST_LOGINSERVER;
	if( stricmp( pszName, "选人服务器" ) == 0 )return ST_SELCHARSERVER;
	if( stricmp( pszName, "游戏世界服务器" ) == 0 )return ST_GAMESERVER;
	return ST_UNKNOWN;
}
//------------------------------------------------------------------------
inline const char * GetServerTypeNameByType( servertype type )
{
	switch( type )
	{
	case	ST_SERVERCENTER:
		return "服务器中心";
	case	ST_DATABASESERVER:
		return "数据库服务器";
	case	ST_LOGINSERVER:
		return "登陆服务器";
	case	ST_SELCHARSERVER:
		return "选人服务器";
	case	ST_GAMESERVER:
		return "游戏世界服务器";
	}
	return "未知的服务器类型";
}
//------------------------------------------------------------------------
// 服务器地址
typedef struct tagSERVERADDR
{
	tagSERVERADDR()
	{
		memset( this, 0, sizeof( *this));
	}
	char	addr[16];
	DWORD	nPort;
	void	SetAddr( const char * pAddr )
	{
		strncpy( addr, pAddr, 16 );
		addr[15] = 0;
	}

}SERVERADDR;
//------------------------------------------------------------------------
// 向某服务器进行服务器注册时的注册信息
typedef struct tagREGISTER_SERVER_INFO
{
	char	szName[64];
	ServerId	Id;
	SERVERADDR	addr;
}REGISTER_SERVER_INFO;
//------------------------------------------------------------------------
// 向服务器注册另外一个服务器的结果
typedef struct tagREGISTER_SERVER_RESULT
{
	ServerId	Id;
	int			nDbCount;
	SERVERADDR	DbAddr[2];
}REGISTER_SERVER_RESULT;
//------------------------------------------------------------------------
// 查找某一个注册服务器的信息
typedef struct tagFINDSERVER_RESULT
{
	tagFINDSERVER_RESULT()
	{
		ZeroMemory( this, sizeof(*this));
	}
	SERVERADDR	addr;
	ServerId	Id;
}FINDSERVER_RESULT;
//------------------------------------------------------------------------
// 服务器错误码
typedef enum e_servererror
{
	SE_FAIL,
	SE_OK,
	SE_SERVERFULL,					// 服务器已满
	SE_INVALIDPARAM,				// 注册服务器失败，服务器类型错误
	SE_NOTINITLIZED,				// 卸载注册服务器失败，该服务器没有注册过
	SE_SERVERNOTFOUND,				// 查找服务器失败
	SE_ALLOCMEMORYFAIL,				// 服务器分配内存失败
	SE_ODBC_SQLALLOCHANDLEFAIL,
	SE_ODBC_SQLSETENVATTRFAIL,
	SE_ODBC_SQLCONNECTFAIL,
	SE_ODBC_SQLDISCONNECTFAIL,
	SE_ODBC_SQLEXECDIRECTFAIL,
	SE_ODBC_SQLNUMRESULTCOLSFAIL,	// NumResultCols
	SE_ODBC_SQLDESCRIBECOLFAIL,		// DescribeCol
	SE_ODBC_SQLBINDCOLFAIL,
	SE_ODBC_SQLFETCHFAIL,
	SE_ODBC_SQLPREPAREFAIL,
	SE_ODBC_SQLEXECUTEFAIL,
	SE_DB_NOMOREDATA,
	SE_DB_NOTINITED,
	SE_LOGIN_ACCOUNTEXIST,
	SE_LOGIN_ACCOUNTINGAME,
	SE_LOGIN_TIMEDELAY,
	SE_LOGIN_ACCOUNTNOTEXIST,
	SE_LOGIN_ACCOUNTKEY_NOTEXIST,
	SE_LOGIN_ACCOUNT_CREATE_ERR,
	SE_LOGIN_PASSWORDERROR,
	SE_LOGIN_ACCOUNTONLINE,
	SE_SELCHAR_CHAREXIST,
	SE_SELCHAR_NOTEXIST,
	SE_REG_INVALIDACCOUNT,
	SE_REG_INVALIDPASSWORD,
	SE_REG_INVALIDNAME,
	SE_REG_INVALIDBIRTHDAY,
	SE_REG_INVALIDPHONENUMBER,
	SE_REG_INVALIDMOBILEPHONE,
	SE_REG_INVALIDQUESTION,
	SE_REG_INVALIDANSWER,
	SE_REG_INVALIDIDCARD,
	SE_REG_INVALIDEMAIL,
	SE_CREATECHARACTER_INVALID_CHARNAME,
}SERVER_ERROR;
//------------------------------------------------------------------------
// Login服务器中客户端玩家状态
enum	loginseverstate
{
	LST_NOTVERIFIED,			// 未登陆
};
//------------------------------------------------------------------------
// SelcectChar服务器中的客户端玩家状态
enum	selcharserverstate
{
	SCS_NOTVERIFIED,			// 未登陆
	SCS_WAITINGFORVERIFIED,		// 等待登陆（下一帧自动登陆）
	SCS_VERIFIED,				// 已登陆
};
//------------------------------------------------------------------------
// Game服务器中的客户端玩家状态
enum	gameserverusermode
{
	GSUM_NOTVERIFIED,			// 未登陆
	GSUM_WAITINGDBINFO,			// 等待DB数据状态
	GSUM_WAITINGCONFIRM,		// 
	GSUM_VERIFIED,				// 已登陆
};
//------------------------------------------------------------------------
#define ID_SERVERCENTERCONNECTION	100032
#define ID_DBSERVERCONNECTIONSTART	100033
//------------------------------------------------------------------------
enum	MAS_SENDTYPE
{
	MST_SINGLE,	//	发给一个单个服务器，参数为服务器ｉｎｄｅｘ
	MST_GROUP,	//	发给一个服务器组，参数为服务器组号
	MST_TYPE,	//	发给一类服务器，参数为服务器类型号
};
//------------------------------------------------------------------------
typedef struct tagENTERGAMESERVER
{
	tagENTERGAMESERVER()
	{
		memset( this, 0, sizeof( *this));
	}
	char	szAccount[12];
	UINT	nLoginId;
	UINT	nSelCharId;
	union
	{
		UINT			nClientId;
		SERVER_ERROR	result;
	};
	DWORD	dwEnterTime;
	char	szName[32];
	DWORD	dwSelectCharServerId;
}ENTERGAMESERVER;
//------------------------------------------------------------------------
#define SERVER_COPYRIGHT		"FreeKnight"
//------------------------------------------------------------------------