/**
*	created:		2013-5-3   3:54
*	filename: 		LoginSceneUI
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "LoginSceneUI.h"
#include "LoginScene.h"
#include "../ServerList.h"
#include "../DeveloperList.h"
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( CLoginSceneUI )
{
	Dock( Pos::Fill );
	SetSize( GAME_CANVAS_WIDTH, GAME_CANVAS_HEIGHT );

#pragma region UICreate
	m_pAccoutLabel				= NULL;
	m_pPasswordLabel			= NULL;
	m_pSaveAccoutCheckBox		= NULL;
	m_pGameSelectComboBox		= NULL;
	m_pAccoutTextBox			= NULL;
	m_pPasswordTextBox			= NULL;
	m_pEnterGameButton			= NULL;

	m_pLoginWindow				= NULL;
	m_pDevelopButton			= NULL;
	m_pOfficalWebButton			= NULL;
	m_pRegisteAccoutButton		= NULL;
	m_pExitGameButton			= NULL;

	m_pConnectUsPanel			= NULL;
	m_pDevelopPanel				= NULL;
	m_pServerListBox			= NULL;

	m_pInfoLabel1				= NULL;
	m_pInfoLabel2				= NULL;

	m_pOwner					= NULL;

	m_pTitleImage = new ImagePanel( this );
	m_pTitleImage->SetImage( LOGIN_SCENE_GAME_TITLE_FILE );
	m_pTitleImage->SetBounds( (GAME_CANVAS_WIDTH - 600) / 2, 50, 600, 200 );

	m_pLoginWindow = new WindowControl( this );
	m_pLoginWindow->SetSize( 410, 250 );
	m_pLoginWindow->SetPos( (GAME_CANVAS_WIDTH - 410) / 2,( GAME_CANVAS_HEIGHT - 250 ) / 2 + 70);
	m_pLoginWindow->SetTitle( L"登陆面板" );
	m_pLoginWindow->SetClosable( false );
	m_pLoginWindow->Moveable( false );
	m_pLoginWindow->DisableResizing();

	m_pServerListBox = new ListBox( m_pLoginWindow );
	m_pServerListBox->SetBounds( 210, 10, 180, 200 );
	m_pServerListBox->SetAllowMultiSelect( false );

	m_pAccoutLabel= new Label( m_pLoginWindow );
	m_pAccoutLabel->SetText( L"账号：" );
	m_pAccoutLabel->SetPos( 30, 20+2 );
	m_pAccoutLabel->SizeToContents();

	m_pAccoutTextBox = new TextBox( m_pLoginWindow );
	m_pAccoutTextBox->SetText( L"" );
	m_pAccoutTextBox->SetSize( 80, 20 );
	m_pAccoutTextBox->SetPos( 80, 20 );
	m_pAccoutTextBox->onTextChanged.Add( this,&CLoginSceneUI::onAccoutEditChange );

	m_pPasswordLabel= new Label( m_pLoginWindow );
	m_pPasswordLabel->SetText( L"密码：" );
	m_pPasswordLabel->SetPos( 30, 50+2 );
	m_pPasswordLabel->SizeToContents();

	m_pPasswordTextBox = new TextBox( m_pLoginWindow );
	m_pPasswordTextBox->SetText( L"" );
	m_pPasswordTextBox->SetSize( 80, 20 );
	m_pPasswordTextBox->SetPos( 80, 50 );
	m_pPasswordTextBox->SetPassword( true );

	m_pSaveAccoutCheckBox = new CheckBoxWithLabel( m_pLoginWindow );
	m_pSaveAccoutCheckBox->Label()->SetText( L"记录账号");
	m_pSaveAccoutCheckBox->SetSize( 75, 20 );
	m_pSaveAccoutCheckBox->SetPos( 70, 80 );

	m_pGameSelectComboBox = new ComboBox( m_pLoginWindow );
	m_pGameSelectComboBox->SetWidth( 150 );
	m_pGameSelectComboBox->SetPos( 30, 110 );
	// 增加游戏列表
	int nGameNum = CServerList::GetInstance()->GetGameNum();
	if( nGameNum != 0 )
	{
		CServerList::SERVER_INFO_MAP::iterator Ite = CServerList::GetInstance()->m_ServerInfoMap.end();
		CServerList::SERVER_INFO_MAP::const_iterator IteBegin = CServerList::GetInstance()->m_ServerInfoMap.begin();
		for( ; Ite != IteBegin;  )
		{
			--Ite;
			m_pGameSelectComboBox->AddItem( Ite->first );
		}
	}
	// 回调
	m_pGameSelectComboBox->onSelection.Add( this,&CLoginSceneUI::onChangeGame );

	m_pEnterGameButton = new Button( m_pLoginWindow );
	m_pEnterGameButton->SetText( L"进入游戏");
	m_pEnterGameButton->SetPos( 60, 165 );
	m_pEnterGameButton->onPress.Add( this, &CLoginSceneUI::onEnterGame );

	m_pInfoLabel1 = new Label( this );
	m_pInfoLabel1->SetTextColor( Color(255,255,255,255) );
	m_pInfoLabel1->SetText( L"抵制不良游戏，拒绝盗版游戏。注意自我保护，预防受骗上当。" );
	m_pInfoLabel1->SetPos( 350, 720 );
	m_pInfoLabel1->SizeToContents();
	m_pInfoLabel2 = new Label( this );
	m_pInfoLabel2->SetTextColor( Color(255,255,255,255) );
	m_pInfoLabel2->SetText( L"适度游戏益脑，沉迷游戏伤身。合理安排时间，享受健康生活。" );
	m_pInfoLabel2->SizeToContents();
	m_pInfoLabel2->SetPos( 350, 740 );

	m_pDevelopButton = new Button( this );
	m_pDevelopButton->SetText( L"开发人员");
	m_pDevelopButton->SetPos( 860, 560 );
	m_pDevelopButton->onPress.Add( this, &CLoginSceneUI::onDevelopButton );

	m_pOfficalWebButton = new Button( this );
	m_pOfficalWebButton->SetText( L"联系我们");
	m_pOfficalWebButton->SetPos( 860, 590 );
	m_pOfficalWebButton->onPress.Add( this, &CLoginSceneUI::onConnectUsButton );

	m_pRegisteAccoutButton = new Button( this );
	m_pRegisteAccoutButton->SetText( L"注册账号");
	m_pRegisteAccoutButton->SetPos( 860, 620 );
	m_pRegisteAccoutButton->onPress.Add( this, &CLoginSceneUI::onRegisteAccoutButton );

	m_pExitGameButton = new Button( this );
	m_pExitGameButton->SetText( L"离开游戏");
	m_pExitGameButton->SetPos( 860, 650 );
	m_pExitGameButton->onPress.Add( this, &CLoginSceneUI::onExitGameButton );

	// 增加服务器列表
	if( m_pGameSelectComboBox->GetSelectedItem() != NULL )
	{
		std::wstring szGameName = m_pGameSelectComboBox->GetSelectedItem()->GetText().GetUnicode();
		int nServerNum = CServerList::GetInstance()->GetServerNum( szGameName );
		if( nServerNum != 0 )
		{
			CServerList::SERVER_INFO_MAP::const_iterator Ite = CServerList::GetInstance()->m_ServerInfoMap.find( szGameName );
			if( Ite != CServerList::GetInstance()->m_ServerInfoMap.end() )
			{
				for( unsigned int i = 0; i < Ite->second.size(); ++i  )
				{
					// 开始Ping
					int nTime = FK2DEngine2::Ping::Ping( ((Ite->second)[i]).m_szServerIP.c_str() );
					std::wstring szInfo = ((Ite->second)[i]).m_szServerName + L"   状态：" 
						+ FK2DEngine2::Ping::GetPingState( nTime );
					m_pServerListBox->AddItem( szInfo );
				}
			}
		}
	}

#pragma endregion
}
//------------------------------------------------------------------------
void CLoginSceneUI::Init()
{
	if( m_pAccoutLabel )
	{
		m_pAccoutLabel->SetText( L"" );
	}
	if( m_pPasswordLabel )
	{
		m_pPasswordLabel->SetText( L"" );
	}
	if( m_pDevelopPanel && m_pDevelopPanel->Visible() )
	{
		m_pDevelopPanel->Hide();
	}
	if( m_pConnectUsPanel && m_pConnectUsPanel->Visible() )
	{
		m_pConnectUsPanel->Hide();
	}
	if( m_pEnterGameButton )
	{
		m_pEnterGameButton->SetDisabled( false );
	}
	if( m_pLoginWindow && !m_pLoginWindow->Visible() )
	{
		m_pLoginWindow->Show();
	}
}
//------------------------------------------------------------------------
void CLoginSceneUI::SetOwner( IScene* scene )
{
	m_pOwner = scene;
}
//------------------------------------------------------------------------
void CLoginSceneUI::Render( Skin::Base* skin )
{
	BaseClass::Render( g_pEngine->getUISkin() );
}
//------------------------------------------------------------------------
// 按下开发人员按钮
void CLoginSceneUI::onDevelopButton( Controls::Base* pControl )
{
	/*
	if( m_pDevelopPanel && m_pDevelopPanel->Visible() )
	{
		m_pDevelopPanel->Hide();
		return;
	}

	if( m_pDevelopPanel &&  !m_pDevelopPanel->Visible() )
	{
		// 隐藏登陆面板
		if( m_pLoginWindow && m_pLoginWindow->Visible() )
		{
			m_pLoginWindow->Hide();
		}
		m_pDevelopPanel->Show();
		return;
	}

	if( m_pDevelopPanel == NULL )
	{
		// 隐藏登陆面板
		if( m_pLoginWindow && m_pLoginWindow->Visible() )
		{
			m_pLoginWindow->Hide();
		}
	}

	m_pDevelopPanel = new Controls::WindowControl( g_pEngine->getUICanvas() );
	m_pDevelopPanel->SetTitle( L"开发人员列表" );
	m_pDevelopPanel->SetSize( 290, 530 );
	m_pDevelopPanel->SetPos( (GAME_CANVAS_WIDTH - 290) / 2, (GAME_CANVAS_HEIGHT - 530) / 2 + 105 );
	m_pDevelopPanel->Moveable( false );
	m_pDevelopPanel->DisableResizing();

	CollapsibleList* pList = new CollapsibleList( m_pDevelopPanel );
	pList->SetSize( 265, 400 );
	pList->SetPos( 10, 10 );
	{
		CollapsibleCategory* pProgram = pList->Add( L"策划" );
		int nNum = CDeveloperList::GetInstance()->GetDeveloperNum( eJobTypeCeHua );
		if( nNum != 0 )
		{
			CDeveloperList::DEVELOPER_INFO_MAP::iterator Ite = CDeveloperList::GetInstance()->m_DeveloperInfoMap.find( eJobTypeCeHua );
			if( Ite !=  CDeveloperList::GetInstance()->m_DeveloperInfoMap.end() )
			{
				CDeveloperList::DEVELOPER_INFO_VEC vec = Ite->second;
				for( unsigned int i = 0; i < vec.size(); ++i )
				{
					pProgram->Add( vec[i].m_szJobName + L"  -  " + vec[i].m_szName );
				}
			}
		}
	}
	{
		CollapsibleCategory* pProgram = pList->Add( L"程序" );
		int nNum = CDeveloperList::GetInstance()->GetDeveloperNum( eJobTypeChengXu );
		if( nNum != 0 )
		{
			CDeveloperList::DEVELOPER_INFO_MAP::iterator Ite = CDeveloperList::GetInstance()->m_DeveloperInfoMap.find( eJobTypeChengXu );
			if( Ite !=  CDeveloperList::GetInstance()->m_DeveloperInfoMap.end() )
			{
				CDeveloperList::DEVELOPER_INFO_VEC vec = Ite->second;
				for( unsigned int i = 0; i < vec.size(); ++i )
				{
					pProgram->Add( vec[i].m_szJobName + L"  -  " + vec[i].m_szName );
				}
			}
		}
	}
	{
		CollapsibleCategory* pProgram = pList->Add( L"美术" );
		int nNum = CDeveloperList::GetInstance()->GetDeveloperNum( eJobTypeMeiShu );
		if( nNum != 0 )
		{
			CDeveloperList::DEVELOPER_INFO_MAP::iterator Ite = CDeveloperList::GetInstance()->m_DeveloperInfoMap.find( eJobTypeMeiShu );
			if( Ite !=  CDeveloperList::GetInstance()->m_DeveloperInfoMap.end() )
			{
				CDeveloperList::DEVELOPER_INFO_VEC vec = Ite->second;
				for( unsigned int i = 0; i < vec.size(); ++i )
				{
					pProgram->Add( vec[i].m_szJobName + L"  -  " + vec[i].m_szName );
				}
			}
		}
	}
	{
		CollapsibleCategory* pProgram = pList->Add( L"音乐" );
		int nNum = CDeveloperList::GetInstance()->GetDeveloperNum( eJobTypeYinYue );
		if( nNum != 0 )
		{
			CDeveloperList::DEVELOPER_INFO_MAP::iterator Ite = CDeveloperList::GetInstance()->m_DeveloperInfoMap.find( eJobTypeYinYue );
			if( Ite !=  CDeveloperList::GetInstance()->m_DeveloperInfoMap.end() )
			{
				CDeveloperList::DEVELOPER_INFO_VEC vec = Ite->second;
				for( unsigned int i = 0; i < vec.size(); ++i )
				{
					pProgram->Add( vec[i].m_szJobName + L"  -  " + vec[i].m_szName );
				}
			}
		}
	}
	{
		CollapsibleCategory* pProgram = pList->Add( L"测试" );
		int nNum = CDeveloperList::GetInstance()->GetDeveloperNum( eJobTypeCeShi );
		if( nNum != 0 )
		{
			CDeveloperList::DEVELOPER_INFO_MAP::iterator Ite = CDeveloperList::GetInstance()->m_DeveloperInfoMap.find( eJobTypeCeShi );
			if( Ite !=  CDeveloperList::GetInstance()->m_DeveloperInfoMap.end() )
			{
				CDeveloperList::DEVELOPER_INFO_VEC vec = Ite->second;
				for( unsigned int i = 0; i < vec.size(); ++i )
				{
					pProgram->Add( vec[i].m_szJobName + L"  -  " + vec[i].m_szName );
				}
			}
		}
	}
	{
		CollapsibleCategory* pProgram = pList->Add( L"运营宣传" );
		int nNum = CDeveloperList::GetInstance()->GetDeveloperNum( eJobTypeYunYing );
		if( nNum != 0 )
		{
			CDeveloperList::DEVELOPER_INFO_MAP::iterator Ite = CDeveloperList::GetInstance()->m_DeveloperInfoMap.find( eJobTypeYunYing );
			if( Ite !=  CDeveloperList::GetInstance()->m_DeveloperInfoMap.end() )
			{
				CDeveloperList::DEVELOPER_INFO_VEC vec = Ite->second;
				for( unsigned int i = 0; i < vec.size(); ++i )
				{
					pProgram->Add( vec[i].m_szJobName + L"  -  " + vec[i].m_szName );
				}
			}
		}
	}

	ImagePanel* pHead = new ImagePanel( m_pDevelopPanel, "DevelopHeadImage" );
	pHead->SetSize( 64, 64 );
	pHead->SetPos( 10, ( 400  + 20 ) );
	pHead->SetImage( DEFAULT_DEVELOPER_HEAD_FILE );

	ListBox* pInfo = new ListBox( m_pDevelopPanel, "DevelopInfoList" );
	pInfo->SetPos( 10 * 2 + 64, ( 400  + 20 ) );
	pInfo->SetSize( 190, 64 );
	pInfo->Clear();
	pInfo->AddItem( L"尚无信息" );
	*/
}
//------------------------------------------------------------------------
void CLoginSceneUI::onConnectUsButton( Controls::Base* pControl )
{
	if( m_pConnectUsPanel && m_pConnectUsPanel->Visible() )
	{
		m_pConnectUsPanel->Hide();
		return;
	}

	if( m_pConnectUsPanel &&  !m_pConnectUsPanel->Visible() )
	{
		m_pConnectUsPanel->Show();
		return;
	}

	m_pConnectUsPanel = new Controls::WindowControl( g_pEngine->getUICanvas() );
	m_pConnectUsPanel->SetTitle( L"联系我们" );
	m_pConnectUsPanel->SetSize( 130, 200 );
	m_pConnectUsPanel->Moveable( false );
	m_pConnectUsPanel->SetPos( (GAME_CANVAS_WIDTH - 10 - 130), (GAME_CANVAS_HEIGHT - 300) / 2 );
	m_pConnectUsPanel->DisableResizing();

	Button* pWebSiteBtn = new Button( m_pConnectUsPanel );
	pWebSiteBtn->SetPos( 15, 10 );
	pWebSiteBtn->SetText( L"官方网站" );
	pWebSiteBtn->onPress.Add( m_pConnectUsPanel, &CLoginSceneUI::onOpenWebSite );

	Button* pBBSBtn = new Button( m_pConnectUsPanel );
	pBBSBtn->SetPos( 15, 40 );
	pBBSBtn->SetText( L"游戏论坛" );

	Button* pBussinessBtn = new Button( m_pConnectUsPanel );
	pBussinessBtn->SetPos( 15, 70 );
	pBussinessBtn->SetText( L"商务合作" );

	Label* pEmailHeadLabel = new Label( m_pConnectUsPanel );
	pEmailHeadLabel->SetPos( 20, 112 );
	pEmailHeadLabel->SetTextColor( Color(0, 0, 255, 255) );
	pEmailHeadLabel->SetText( L"主负责人邮箱：" );
	pEmailHeadLabel->SizeToContents();
	TextBox* pEmailEdit = new TextBox( m_pConnectUsPanel );
	pEmailEdit->SetPos( 10, 130 );
	pEmailEdit->SetSize( 110, 18 );
	pEmailEdit->SetTextColor( Color(0, 0, 255, 255) );
	pEmailEdit->SetText( L"duzhi5368@163.com" );
	pEmailEdit->SetDisabled( true );
}
//------------------------------------------------------------------------
void CLoginSceneUI::onRegisteAccoutButton( Controls::Base* pControl )
{

}
//------------------------------------------------------------------------
void CLoginSceneUI::onExitGameButton( Controls::Base* pControl )
{
	g_bReadyExit = true;
}
//------------------------------------------------------------------------
void CLoginSceneUI::onOpenWebSite( Controls::Base* pControl )
{
	ShellExecute(NULL,L"open",L"http://www.freeknightgame.com/",NULL,NULL,SW_SHOWNORMAL);
}
//------------------------------------------------------------------------
void CLoginSceneUI::onAccoutEditChange( Controls::Base* pControl )
{
	FK2DEngine2::Controls::TextBox* textbox = ( FK2DEngine2::Controls::TextBox* )( pControl );
	if( textbox == NULL )
	{
		return;
	}
	if( textbox->GetText().m_String.empty() )
	{
		return;
	}
	// 检查是否是字母和数字
	if( !IsCharOrNum( textbox->GetText().m_String.c_str() ) )
	{
		textbox->SetText( std::wstring( textbox->GetText().m_Unicode.begin(), 
			textbox->GetText().m_Unicode.end() - 1 ) );
	}
}
//------------------------------------------------------------------------
void CLoginSceneUI::onEnterGame( Controls::Base* pControl )
{
	CLoginScene* pLogin = (CLoginScene*)m_pOwner;
	// 本地记录账号密码
	strcpy_s( pLogin->m_szAccout, m_pAccoutTextBox->GetText().Get().c_str() );
	strcpy_s( pLogin->m_szPassword, m_pPasswordTextBox->GetText().Get().c_str() );

	FK2DEngine2::Controls::Button* pEnterBtn = ( FK2DEngine2::Controls::Button* )pControl;
	pEnterBtn->SetDisabled( true );

	theSwitchboard.Broadcast( new FK2DEngine2::event::CMessage(L"EnterCharSel") );
}
//------------------------------------------------------------------------
void CLoginSceneUI::onChangeGame( Controls::Base* pControl )
{
	// 获取子类的选择菜单值
	FK2DEngine2::Controls::MenuItem* selectItem = ( FK2DEngine2::Controls::MenuItem* )( pControl );
	if( selectItem == NULL )
	{
		return;
	}
	if( selectItem->GetText().m_String.empty() )
	{
		return;
	}

	// 更换列表
	if( m_pGameSelectComboBox->GetSelectedItem() != NULL )
	{
		std::wstring szGameName = m_pGameSelectComboBox->GetSelectedItem()->GetText().GetUnicode();
		int nServerNum = CServerList::GetInstance()->GetServerNum( szGameName );
		if( nServerNum != 0 )
		{
			m_pServerListBox->Clear();
			CServerList::SERVER_INFO_MAP::const_iterator Ite = CServerList::GetInstance()->m_ServerInfoMap.find( szGameName );
			if( Ite != CServerList::GetInstance()->m_ServerInfoMap.end() )
			{
				for( unsigned int i = 0; i < Ite->second.size(); ++i  )
				{
					// 开始Ping
					int nTime = FK2DEngine2::Ping::Ping( ((Ite->second)[i]).m_szServerIP.c_str() );
					std::wstring szInfo = ((Ite->second)[i]).m_szServerName + L"   状态：" 
						+ FK2DEngine2::Ping::GetPingState( nTime );
					m_pServerListBox->AddItem( szInfo );
				}
			}
		}
	}
}
//------------------------------------------------------------------------