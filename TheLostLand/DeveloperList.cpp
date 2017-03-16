/**
*	created:		2013-5-3   19:52
*	filename: 		DeveloperList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "DeveloperList.h"
//------------------------------------------------------------------------
// 获取指定职业组的开发者个数
int CDeveloperList::GetDeveloperNum( int nJobGroupID )
{
	if( nJobGroupID >= eJobTypeMax || nJobGroupID < 0 )
	{
		return 0;
	}
	DEVELOPER_INFO_MAP::iterator Ite = m_DeveloperInfoMap.find( nJobGroupID );
	if( Ite != m_DeveloperInfoMap.end() )
	{
		return ( Ite->second.size() );
	}
	return 0;
}
//------------------------------------------------------------------------
// 加载服务器列表
bool CDeveloperList::LoadFromFile( const char* filename )
{
	IResScript* pObj = g_pResMgr->LoadResScript( filename );
	if( pObj == NULL )
	{
		FKTRACE( L"读取文件 %s 失败！", filename );
		return false;
	}
	// 开发人员种类个数
	int nNum = pObj->GetObjectCount();
	IResObject* pRoot = pObj->GetResObjectRoot();
	if( pRoot == NULL )
	{
		pObj->Release();
		return false;
	}

	// 获取主种类
	int nSubNum = pRoot->GetSubObjectCount();
	bool bResult = true;
	IResObject* pCur = NULL;
	int nMainType = eJobTypeMax;
	char szTemp[512];
	for( int i = 0; i < nSubNum; ++i )
	{
		pCur = pRoot->GetSubObjectByIndex(i);
		if( pCur == NULL )
		{
			bResult = false;
			break;
		}
		const char* pMainTile = pCur->GetObjectName();
		if( strcmp( pMainTile, "策划") == 0 )
		{
			nMainType = eJobTypeCeHua;
		}
		else if( strcmp( pMainTile, "程序") == 0 )
		{
			nMainType = eJobTypeChengXu;
		}
		else if( strcmp( pMainTile, "美术") == 0 )
		{
			nMainType = eJobTypeMeiShu;
		}
		else if( strcmp( pMainTile, "音乐") == 0 )
		{
			nMainType = eJobTypeYinYue;
		}
		else if( strcmp( pMainTile, "测试") == 0 )
		{
			nMainType = eJobTypeCeShi;
		}
		else if( strcmp( pMainTile, "运营") == 0 )
		{
			nMainType = eJobTypeYunYing;
		}

		SDeveloperInfo info;
		info.m_nIndex = pCur->GetID();
		memset( szTemp, 0, 512 );
		strcpy_s( szTemp, pCur->GetPropertyString("子职位") );
		info.m_szJobName = FK2DEngine2::Utility::StringToUnicode( szTemp );
		strcpy_s( szTemp, pCur->GetPropertyString("名字") );
		info.m_szName = FK2DEngine2::Utility::StringToUnicode( szTemp );
		strcpy_s( szTemp, pCur->GetPropertyString("头像") );
		info.m_szImageUrl = FK2DEngine2::Utility::StringToUnicode( szTemp );
		strcpy_s( szTemp, pCur->GetPropertyString("介绍") );
		info.m_szInfo = FK2DEngine2::Utility::StringToUnicode( szTemp );

		DEVELOPER_INFO_MAP::iterator Ite = m_DeveloperInfoMap.find( nMainType );
		if( Ite != m_DeveloperInfoMap.end() )
		{
			// 本类型原本就有了
			Ite->second.push_back( info );
		}
		else
		{
			// 本类型原本没有
			DEVELOPER_INFO_VEC vec;
			vec.push_back( info );
			m_DeveloperInfoMap.insert( std::make_pair( nMainType, vec ) );
		}
	}
	if (!bResult) 
	{
		//解析出错
		FKTRACE( L"解析文件 %s 出错！", filename );
		pObj->Release();
		return false;
	}

	// pObj->Release();
	return true;
}
//------------------------------------------------------------------------