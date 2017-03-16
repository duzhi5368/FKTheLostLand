/**
*	created:		2013-5-3   3:08
*	filename: 		CS_CommonDefine
*	author:			FreeKnight
*	Copyright (C): 	 
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
// 用户账户名最大长度【实际最大长度为15】
#define MAX_ACCOUT_LEN				16
// 用户密码最大长度【实际最大长度为15】
#define MAX_PASSWORD_LEN			16
//------------------------------------------------------------------------
// 一个账号内最大角色数量
#define MAX_MAIN_ROLE_NUM			4
//------------------------------------------------------------------------
// 主角名称最大长度[ char ]不带\0
#define MAX_MAIN_ROLE_NAME_LEN		15		
//------------------------------------------------------------------------
// 国家阵营枚举
enum EnumCountryCampType
{
	eCountryCampType_Unknow			= 0,
	eCountryCampType_DiSiKaiTe		= 1,	// 蒂斯凯特
	eCountryCampType_FeiEr			= 2,	// 费尔		
	eCountryCampType_FeiErLong		= 3,	// 菲尔隆
	eCountryCampType_KeManSaSi		= 4,	// 科曼萨斯
	eCountryCampType_NuoTaiEr		= 5,	// 诺泰尔
	eCountryCampType_Max,
};
//------------------------------------------------------------------------
// 标准阵营枚举
enum EnumCampType
{
	eCampType_Unknow				= 0,	// 未知阵营
	eCampType_LawfulGood			= 1,	// 守序善良
	eCampType_ChaoticGood			= 2,	// 混乱善良
	eCampType_Neutral				= 3,	// 绝对中立
	eCampType_ChaoticEvil			= 4,	// 混乱邪恶
	eCampType_LawfulEvil			= 5,	// 守序邪恶
	eCampType_Max,						
};
//------------------------------------------------------------------------
// 性别枚举
enum EnumSexType
{
	eSexType_Unknow		= 0,
	eSexType_Male		= 1,		// 男性
	eSexType_Female		= 2,		// 女性
	eSexType_Max,
};
//------------------------------------------------------------------------
// 种族枚举
enum EnumRaceType
{
	eRaceType_Unknow	= 0,
	eRaceType_Human		= 1,		// 人类
	eRaceType_Elf		= 2,		// 精灵
	eRaceType_Dwarf		= 3,		// 矮人
	eRaceType_HalfOrc	= 4,		// 半兽人
	eRaceType_Element	= 5,		// 元素精灵
	eRaceType_Max,					

	// 怪物并非这些阵营而已，上述仅仅是玩家种族
};
//------------------------------------------------------------------------
// 角色登录时信息
struct stMainRoleLoginInfo
{
	char				m_szMainRoleName[MAX_MAIN_ROLE_NAME_LEN+1];	// 角色名称
	EnumCountryCampType	m_eCountryCamp;								// 所属国家阵营
	EnumSexType			m_eSex;										// 性别
	EnumRaceType		m_eRace;									// 种族
	EnumCampType		m_eCamp;									// 标准阵营
	int					m_nLv;										// 等级
	int					m_nHeroCardNum;								// 英雄卡牌数

	stMainRoleLoginInfo()
	{
		memset( this, 0, sizeof(this) );
	}
};
//------------------------------------------------------------------------