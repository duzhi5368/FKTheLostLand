/**
*	created:		2013-5-3   17:55
*	filename: 		ServerList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "ServerList.h"
//------------------------------------------------------------------------
CServerList::~CServerList()
{
}
//------------------------------------------------------------------------
// 获取指定游戏的服务器个数
int CServerList::GetServerNum( std::wstring& szGameName )
{
	SERVER_INFO_MAP::const_iterator Ite = m_ServerInfoMap.find( szGameName );
	if( Ite == m_ServerInfoMap.end() )
	{
		return 0;
	}
	return (int)( Ite->second.size() );
}
//------------------------------------------------------------------------
// 获取主游戏类型的个数
int CServerList::GetGameNum()
{
	return m_ServerInfoMap.size();
}
//------------------------------------------------------------------------
// 加载服务器列表
bool CServerList::LoadFromFile( const char* filename )
{
	IResScript* pObj = g_pResMgr->LoadResScript( filename );
	if( pObj == NULL )
	{
		FKTRACE( L"读取文件 %s 失败！", filename );
		return false;
	}
	int nNum = pObj->GetObjectCount();
	IResObject* pRoot = pObj->GetResObjectRoot();
	if( pRoot == NULL )
	{
		pObj->Release();
		return false;
	}

	int nSubNum = pRoot->GetSubObjectCount();
	bool bResult = true;
	for( int i = 0; i < nSubNum; ++i )
	{
		bResult &= Parser( pRoot->GetSubObjectByIndex(i), 0, "" );
	}
	if (!bResult) 
	{
		//解析出错
		FKTRACE( L"解析文件 %s 出错！", filename );
		pObj->Release();
		return false;
	}
	// pObj->Dump();
	//pObj->Release();
	return true;
}
//------------------------------------------------------------------------
bool CServerList::Parser( IResObject *pResObject, int nParentID, std::string szGameName )
{
	if( pResObject == NULL )
	{
		return false;
	}
	const char* pAdd = pResObject->GetPropertyString( "Login服务器IP地址" );
	// 说明是服务器主类
	if( strcmp( pAdd,"无" ) == 0 )
	{
		bool bResult = true;
		int nSubCount = pResObject->GetSubObjectCount();
		for( int i = 0; i < nSubCount; ++i )
		{
			bResult &= Parser( pResObject->GetSubObjectByIndex(i), pResObject->GetID(), pResObject->GetObjectName() );
		}

		if (!bResult) 
		{
			//解析出错
			FKTRACE( L"解析文件出错！" );
			return false;
		}
	}
	else
	{// 说明是子服务器类
		SServerInfo tagInfo;
		tagInfo.m_nServerIndex = pResObject->GetID();
		tagInfo.m_szServerIP = pAdd;
		char szServerName[64];
		memset( szServerName, 0, 64 );
		memcpy( szServerName, pResObject->GetObjectName(), 64 - 1 );
		tagInfo.m_szServerName = FK2DEngine2::Utility::StringToUnicode( szServerName );
		
		std::wstring szTmpGameName;
		szTmpGameName = FK2DEngine2::Utility::StringToUnicode( szGameName );
		SERVER_INFO_MAP::iterator Ite = m_ServerInfoMap.find( szTmpGameName.c_str() );
		if( Ite != m_ServerInfoMap.end() )
		{
			// 本类型原本就有服务器了
			Ite->second.push_back( tagInfo );
		}
		else
		{
			// 本类型原本没有服务器
			SERVER_INFO_VEC vec;
			vec.push_back( tagInfo );
			m_ServerInfoMap.insert( std::make_pair( szTmpGameName, vec ) );
		}
	}
	return true;
}
//------------------------------------------------------------------------