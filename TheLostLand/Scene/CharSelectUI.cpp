/**
*	created:		2013-5-9   14:10
*	filename: 		CharSelectUI
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "CharSelectUI.h"
#include "CharSelectScene.h"
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( CCharSelectUI )
{
	Dock( Pos::Fill );
	SetSize( GAME_CANVAS_WIDTH, GAME_CANVAS_HEIGHT );

#pragma region UICreate
	m_pEnterGameBtn		= NULL;
	m_pCreateCharBtn	= NULL;
	m_pDeleteCharBtn	= NULL;
	m_pPreviousBtn		= NULL;

	m_pEnterGameBtn = new Button( this );
	m_pEnterGameBtn->SetText( L"进入游戏" );
	m_pEnterGameBtn->SetPos( (GAME_CANVAS_WIDTH - 100) / 2, GAME_CANVAS_HEIGHT / 2 + 200 );
	m_pEnterGameBtn->onPress.Add( this, &CCharSelectUI::onEnterGameBtn );

	m_pCreateCharBtn = new Button( this );
	m_pCreateCharBtn->SetText( L"创建角色" );
	m_pCreateCharBtn->SetPos( (GAME_CANVAS_WIDTH - 100) / 2, GAME_CANVAS_HEIGHT / 2 + 230 );
	m_pCreateCharBtn->onPress.Add( this, &CCharSelectUI::onCreateCharBtn );

	m_pDeleteCharBtn = new Button( this );
	m_pDeleteCharBtn->SetText( L"删除角色" );
	m_pDeleteCharBtn->SetPos( (GAME_CANVAS_WIDTH - 100) / 2, GAME_CANVAS_HEIGHT / 2 + 260 );
	m_pDeleteCharBtn->onPress.Add( this, &CCharSelectUI::onDeleteCharBtn );

	m_pPreviousBtn = new Button( this );
	m_pPreviousBtn->SetText( L"返回登录界面" );
	m_pPreviousBtn->SetPos(  860, 650 );
	m_pPreviousBtn->onPress.Add( this, &CCharSelectUI::onPreviousBtn );
#pragma endregion
}
//------------------------------------------------------------------------
void CCharSelectUI::SetOwner( IScene* scene )
{
	m_pOwner = scene;
}
//------------------------------------------------------------------------
void CCharSelectUI::Render( Skin::Base* skin )
{
	BaseClass::Render( g_pEngine->getUISkin() );
}
//------------------------------------------------------------------------
void CCharSelectUI::onEnterGameBtn( Controls::Base* pControl )
{

}
//------------------------------------------------------------------------
void CCharSelectUI::onCreateCharBtn( Controls::Base* pControl )
{

}
//------------------------------------------------------------------------
void CCharSelectUI::onDeleteCharBtn( Controls::Base* pControl )
{

}
//------------------------------------------------------------------------
void CCharSelectUI::onPreviousBtn( Controls::Base* pControl )
{
	if( m_pOwner )
	{
		((CCharSelectScene*)m_pOwner)->SetNextSceneIndex( eScene_LoginScene );
	}
}
//------------------------------------------------------------------------