/**
*	created:		2013-5-3   4:18
*	filename: 		MainSceneUI
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "MainSceneUI.h"
#include "MainScene.h"
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( CMainSceneUI )
{
	Dock( Pos::Fill );
	SetSize( GAME_CANVAS_WIDTH, GAME_CANVAS_HEIGHT );

	m_pBackLoginButton = new Button( this );
	m_pBackLoginButton->SetText( L"·µ»ØµÇÂ½");
	m_pBackLoginButton->SetPos( 860, 720 );
	m_pBackLoginButton->onPress.Add( this, &CMainSceneUI::onBackLoginButton );
}
//------------------------------------------------------------------------
void CMainSceneUI::SetOwner( IScene* scene )
{
	m_pOwner = scene;
}
//------------------------------------------------------------------------
void CMainSceneUI::Render( Skin::Base* skin )
{
	BaseClass::Render( g_pEngine->getUISkin() );
}
//------------------------------------------------------------------------
// ·µ»ØµÇÂ½
void CMainSceneUI::onBackLoginButton( Controls::Base* pControl )
{
	CMainScene* pMain = (CMainScene*)m_pOwner;
	pMain->SetNextSceneIndex( eScene_LoginScene );
}
//------------------------------------------------------------------------