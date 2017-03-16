/**
*	created:		2013-5-9   14:18
*	filename: 		CharSelectScene
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "CharSelectScene.h"
//------------------------------------------------------------------------
CCharSelectScene::CCharSelectScene()
	: IScene()
{
	m_pUIMgr		= NULL;
	m_nCurSelect	= 0;

	m_pBackgroud = new CFullScreenActor();
	m_pBackgroud->SetSize( GAME_CANVAS_WIDTH, GAME_CANVAS_HEIGHT );
	m_pBackgroud->SetSprite( CHAR_SEL_BK_FILE );
}
//------------------------------------------------------------------------
CCharSelectScene::~CCharSelectScene()
{

}
//------------------------------------------------------------------------
void CCharSelectScene::OnEnter()
{
	FKTRACE( L"进入 CCharSelectScene" );

	// UI处理
	if( m_pUIMgr == NULL )
	{
		m_pUIMgr = new CCharSelectUI( g_pEngine->getUICanvas(), "CharSelectScene" );
	}
	else
	{
		m_pUIMgr->Show();
	}

	m_pUIMgr->SetOwner( this );

	// 场景精灵处理
	theWorld.Add( m_pBackgroud, DEFAULT_BACKGROUND_LAYER_Z );

	// 连接处理
	CGameSceneMgr::GetInstance().CreateConnection( eNLS_LoginSvr );
}
//------------------------------------------------------------------------
void CCharSelectScene::OnLeave()
{
	FKTRACE( L"离开 CCharSelectScene" );
	if( m_pUIMgr )
	{
		m_pUIMgr->Hide();
	}

	theWorld.Remove( m_pBackgroud );
}
//------------------------------------------------------------------------
void CCharSelectScene::Update( float dt )
{

}
//------------------------------------------------------------------------
void CCharSelectScene::Render()
{

}
//------------------------------------------------------------------------
void CCharSelectScene::SetNextSceneIndex( unsigned int index )
{
	CGameSceneMgr::GetInstance().SetNextSceneIndex( index );
}
//------------------------------------------------------------------------