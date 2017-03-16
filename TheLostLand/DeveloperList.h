/**
*	created:		2013-5-3   17:58
*	filename: 		DeveloperList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "MainMacro.h"
//------------------------------------------------------------------------
enum ENUM_JobType
{
	eJobTypeCeHua		= 0,	// 策划
	eJobTypeChengXu		= 1,	// 程序
	eJobTypeMeiShu		= 2,	// 美术
	eJobTypeYinYue		= 3,	// 音乐
	eJobTypeCeShi		= 4,	// 测试
	eJobTypeYunYing		= 5,	// 运营

	eJobTypeMax,
};
//------------------------------------------------------------------------
struct SDeveloperInfo
{
	int						m_nIndex;		// 开发者编号
	std::wstring			m_szJobName;	// 开发者职位
	std::wstring			m_szName;		// 开发者名字
	std::wstring			m_szImageUrl;	// 开发者头像地址
	std::wstring			m_szInfo;		// 开发者信息简介
};
//------------------------------------------------------------------------
class CDeveloperList : public TSingletonClass< CDeveloperList >
{
public:
	typedef std::vector< SDeveloperInfo >			DEVELOPER_INFO_VEC;
	typedef std::map< int, DEVELOPER_INFO_VEC >		DEVELOPER_INFO_MAP;
public:
	CDeveloperList(){};
	~CDeveloperList(){};
public:
	DEVELOPER_INFO_MAP				m_DeveloperInfoMap;
public:
	// 获取指定职业组的开发者个数
	int								GetDeveloperNum( int nJobGroupID );
	// 加载服务器列表
	bool							LoadFromFile( const char* filename );
};
//------------------------------------------------------------------------