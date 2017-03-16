/**
*	created:		2013-5-3   4:17
*	filename: 		MainSceneUI
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../MainMacro.h"
//------------------------------------------------------------------------
class CMainSceneUI : public FK2DEngine2::Controls::DockBase
{
public:
	FK_CONTROL( CMainSceneUI, FK2DEngine2::Controls::DockBase );
private:
	Button*				m_pBackLoginButton;		// ·µ»ØµÇÂ½½çÃæ
private:
	IScene*				m_pOwner;
public:
	void				SetOwner( IScene* scene );
	void				Render( Skin::Base* skin );
private:
	void				onBackLoginButton( Controls::Base* pControl );
};
//------------------------------------------------------------------------