/**
*	created:		2013-5-3   17:42
*	filename: 		ServerList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "MainMacro.h"
//------------------------------------------------------------------------
enum ENUM_ServerState
{
	eServerState_Unknown		= 0,	// 未知
	eServerState_UnConnected	= 1,	// 无法连接
	eServerState_Normal			= 2,	// 正常
	// TODO: ping 下？ 或者是直接检查人数（不推荐）？
};
//------------------------------------------------------------------------
struct SServerInfo
{
	int					m_nServerIndex;
	std::wstring		m_szServerName;
	ENUM_ServerState	m_nServerState;
	std::string			m_szServerIP;

	SServerInfo() : m_nServerIndex(0) , m_nServerState(eServerState_Unknown)
	{
		m_szServerName = L"未知服务器";
		m_szServerIP = "0.0.0.0";
	}
};
//------------------------------------------------------------------------
class CServerList : public TSingletonClass< CServerList >
{
public:
	typedef std::vector< SServerInfo >					SERVER_INFO_VEC;
	typedef std::map< std::wstring, SERVER_INFO_VEC >	SERVER_INFO_MAP;
public:
	CServerList(){};
	~CServerList();
public:
	SERVER_INFO_MAP					m_ServerInfoMap;
public:
	// 获取指定游戏的服务器个数
	int								GetServerNum( std::wstring& szGameName );
	// 获取主游戏类型的个数
	int								GetGameNum();
	// 加载服务器列表
	bool							LoadFromFile( const char* filename );
private:
	bool							Parser( IResObject *pResObject, int nParentID, std::string szGameName );
};
//------------------------------------------------------------------------