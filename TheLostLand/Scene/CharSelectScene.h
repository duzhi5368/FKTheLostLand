/**
*	created:		2013-5-9   13:56
*	filename: 		CharSelectScene
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../MainMacro.h"
#include "CharSelectUI.h"
//------------------------------------------------------------------------
class CCharSelectScene : public FK2DEngine2::scene::IScene
{
public:
	CCharSelectScene();
	~CCharSelectScene();
public:
	void				OnEnter();
	void				OnLeave();
	void				Update( float dt );
	void				Render();
	void				ReceiveMessage(FK2DEngine2::event::CMessage *message) {}
	void				SetNextSceneIndex( unsigned int index );
private:
	CCharSelectUI*		m_pUIMgr;							// 选择角色UI管理器
	int					m_nCurSelect;						// 当前选择的角色编号
	stMainRoleLoginInfo m_tagRoleList[MAX_MAIN_ROLE_NUM];	// 角色信息
	CFullScreenActor*	m_pBackgroud;						// 背景图片
};
//------------------------------------------------------------------------