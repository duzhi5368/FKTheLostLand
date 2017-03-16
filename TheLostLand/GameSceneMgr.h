/**
*	created:		2013-5-1   21:42
*	filename: 		GameSceneMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "MainMacro.h"
//------------------------------------------------------------------------
enum EnumSceneType
{
	eScene_LoginScene		= 1,
	eScene_CharSelectScene	= 2,


	eScene_MainScene,

	eScene_Max,
};
//------------------------------------------------------------------------
class CGameSceneMgr : public FK2DEngine2::scene::S2D::FKISceneManager
{
public:
	static CGameSceneMgr& GetInstance();
	static CGameSceneMgr* GetInstancePtr();
protected:
	CGameSceneMgr();
	static CGameSceneMgr *s_GameManager;
public:
	void Render(){}
	void Update(float dt);
	void ReceiveMessage(FK2DEngine2::event::CMessage* message) {}
	bool CreateConnection( EnumNetworkLinkState e );
public:
	void SetNextSceneIndex( unsigned int index );
private:
	int	m_nNextSceneIndex;						// 下一个场景索引
	IFKAppNetworkLink*	m_pAppNetworkLink;		// 网络通讯接口
	CClientLinkHelper	m_SocketHelper;			// 创建Socket的协助接口
};
//------------------------------------------------------------------------