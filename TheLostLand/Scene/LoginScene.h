/**
*	created:		2013-5-1   21:29
*	filename: 		LoginScene
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../MainMacro.h"
#include "LoginSceneUI.h"
//------------------------------------------------------------------------
class CLoginScene : public FK2DEngine2::scene::IScene
{
public:
	CLoginScene();
	~CLoginScene();
public:
	void				OnEnter();
	void				OnLeave();
	void				Update( float dt );
	void				Render();
	void				ReceiveMessage(FK2DEngine2::event::CMessage *message);
public:
	void				SetNextSceneIndex( unsigned int index );
public:
	char				m_szAccout[MAX_ACCOUT_LEN];
	char				m_szPassword[MAX_PASSWORD_LEN];
private:
	CFullScreenActor*	m_pBackgroud;			// ±³¾°Í¼Æ¬
	CLoginSceneUI*		m_pUIMgr;				// µÇÂ½UI¹ÜÀíÆ÷
};
//------------------------------------------------------------------------