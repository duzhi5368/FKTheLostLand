/**
*	created:		2013-4-19   10:09
*	filename: 		GameWorld
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CGameWorld
{
public:
	CGameWorld(){}
	~CGameWorld(){}
public:
	// 初始化
	bool	Init(){ return true; };
	// 每逻辑帧刷新
	void	Update(){};
	// 输入信息
	void	OnInput( const char* pString ){};
public:
	static CGameWorld * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CGameWorld;
		return m_pInstance;
	}
private:
	static CGameWorld * m_pInstance;
};
//------------------------------------------------------------------------