/**
*	created:		2013-5-3   3:19
*	filename: 		MainScene
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "MainScene.h"
//------------------------------------------------------------------------
CMainScene::CMainScene()
	: IScene()
{
	m_pUIMgr		= NULL;
	m_pBackgroud	= NULL;

	m_pBackgroud = new CFullScreenActor();
	m_pBackgroud->SetSize( GAME_CANVAS_WIDTH, GAME_CANVAS_HEIGHT );
	m_pBackgroud->SetSprite( MAIN_SCENE_BK_FILE );
}
//------------------------------------------------------------------------
void CMainScene::OnEnter()
{
	FKTRACE( L"½øÈë MainScene" );
	m_pUIMgr = new CMainSceneUI( g_pEngine->getUICanvas(), "MainScene" );
	m_pUIMgr->SetOwner( this );

	theWorld.Add( m_pBackgroud, DEFAULT_BACKGROUND_LAYER_Z );
}
//------------------------------------------------------------------------
void CMainScene::Update( float dt )
{

}
//------------------------------------------------------------------------
void CMainScene::OnLeave()
{
	FKTRACE( L"Àë¿ª MainScene" );
	if( m_pUIMgr )
	{
		m_pUIMgr->Hide();
	}
	theWorld.Remove( m_pBackgroud );
}
//------------------------------------------------------------------------
void CMainScene::SetNextSceneIndex( unsigned int index )
{
	CGameSceneMgr::GetInstance().SetNextSceneIndex( index );
}
//------------------------------------------------------------------------