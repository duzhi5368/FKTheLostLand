/**
*	created:		2013-5-3   3:18
*	filename: 		MainScene
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../MainMacro.h"
#include "MainSceneUI.h"
//------------------------------------------------------------------------
class CMainScene : public FK2DEngine2::scene::IScene
{
public:
	CMainScene();
	~CMainScene(){};
public:
	void	OnEnter();
	void	OnLeave();
	void	Update( float dt );
	void	Render(){};
	void	ReceiveMessage(FK2DEngine2::event::CMessage *message) {}
public:
	void	SetNextSceneIndex( unsigned int index );
private:
	CMainSceneUI*		m_pUIMgr;				// 主界面UI管理器
	CFullScreenActor*	m_pBackgroud;			// 背景图片
};
//------------------------------------------------------------------------