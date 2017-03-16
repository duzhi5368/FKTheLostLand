/**
*	created:		2013-5-9   13:59
*	filename: 		CharSelectUI
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../MainMacro.h"
//------------------------------------------------------------------------
class CCharSelectUI : public FK2DEngine2::Controls::DockBase
{
public:
	FK_CONTROL( CCharSelectUI, FK2DEngine2::Controls::DockBase );
private:
	Button*				m_pEnterGameBtn;		// 进入游戏按钮
	Button*				m_pCreateCharBtn;		// 创建角色按钮
	Button*				m_pDeleteCharBtn;		// 删除角色按钮
	Button*				m_pPreviousBtn;			// 上一步按钮
private:
	IScene*				m_pOwner;
public:
	void				SetOwner( IScene* pScene );
	void				Render( Skin::Base* skin );
private:
	void				onEnterGameBtn( Controls::Base* pControl );
	void				onCreateCharBtn( Controls::Base* pControl );
	void				onDeleteCharBtn( Controls::Base* pControl );
	void				onPreviousBtn( Controls::Base* pControl );
};
//------------------------------------------------------------------------