/**
*	created:		2013-5-3   3:51
*	filename: 		LoginSceneUI
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../MainMacro.h"
//------------------------------------------------------------------------
class CLoginSceneUI : public FK2DEngine2::Controls::DockBase
{
public:
	FK_CONTROL( CLoginSceneUI, FK2DEngine2::Controls::DockBase );
private:
	ImagePanel*			m_pTitleImage;			// 标题图片

	Label*				m_pAccoutLabel;			// 账号
	Label*				m_pPasswordLabel;		// 密码
	CheckBoxWithLabel*	m_pSaveAccoutCheckBox;	// 记录账号
	ComboBox*			m_pGameSelectComboBox;	// 选择游戏
	TextBox*			m_pAccoutTextBox;		// 账号输入框
	TextBox*			m_pPasswordTextBox;		// 密码输入框
	Button*				m_pEnterGameButton;		// 进入游戏

	WindowControl*		m_pLoginWindow;			// 登录面板
	Button*				m_pDevelopButton;		// 开发人员
	Button*				m_pOfficalWebButton;	// 游戏官网
	Button*				m_pRegisteAccoutButton;	// 注册账号
	Button*				m_pExitGameButton;		// 离开游戏

	WindowControl*		m_pConnectUsPanel;		// 联系我们面板
	WindowControl*		m_pDevelopPanel;		// 开发人员面板

	ListBox*			m_pServerListBox;		// 服务器列表

	Label*				m_pInfoLabel1;			// 提示警告1
	Label*				m_pInfoLabel2;			// 提示警告2
private:
	IScene*				m_pOwner;
public:
	void				Init();
	void				SetOwner( IScene* scene );
	void				Render( Skin::Base* skin );
private:
	void				onDevelopButton( Controls::Base* pControl );
	void				onConnectUsButton( Controls::Base* pControl );
	void				onRegisteAccoutButton( Controls::Base* pControl );
	void				onExitGameButton( Controls::Base* pControl );
	void				onOpenWebSite( Controls::Base* pControl );
	void				onAccoutEditChange( Controls::Base* pControl );
	void				onEnterGame( Controls::Base* pControl );
	void				onChangeGame( Controls::Base* pControl );
};
//------------------------------------------------------------------------