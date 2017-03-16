/**
*	created:		2013-4-16   5:32
*	filename: 		ServerForm
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/serverform.h"
#include "../Include/socketfunction.h"
#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")
#include "../Include/progressform.h"
//------------------------------------------------------------------------
CServerForm::CServerForm(void)
{
	m_pServer = NULL;
	m_pCmdLine = NULL;
	NetStartup(2,2);
	m_iThroughCount = 0;
	this->m_pProgressForm = NULL;
}
//------------------------------------------------------------------------
CServerForm::~CServerForm(void)
{
	NetCleanup();
}
//------------------------------------------------------------------------
BOOL CServerForm::Create( const char * pszTitle, const char * pszCmdLine )
{
TRY_BEGIN
	m_pszServerName = (char*)pszTitle;
	m_pCmdLine = (char*) pszCmdLine;
	BOOL b = CEGForm::Create(GetDesktopWindow(),40,40,800,600,WS_OVERLAPPED, WS_MAXIMIZEBOX|WS_THICKFRAME,(char*)pszTitle, SW_SHOW, NULL, NULL, NULL, NULL, 
							 (HBRUSH)(COLOR_BTNFACE+1));
	if( b )
	{
		m_pProgressForm = new CProgressForm;
		m_pProgressForm->Create( m_hWnd, "测试", "ok", TRUE );
	}
	return b;
TRY_END
}
//------------------------------------------------------------------------
VOID CServerForm::OnCreate( HWND hWnd )
{
	RECT winrc;
	GetWindowRect(hWnd,&winrc);
	int winwidth = winrc.right - winrc.left;

	int	top = 50;
	DWORD	style1 = SS_CENTER, style2 = SS_CENTER;
	int	x = winwidth - 130;
	int width = 92;

	//	控制台RichEdit控件
	m_reChat.Create(hWnd,/*ES_READONLY|*/ES_NOHIDESEL |ES_WANTRETURN|WS_BORDER,30,30,609,490,0);
	m_reChat.SetId(IDRE_CHAT);
	m_reChat.SetBkGndColor(RGB(22,22,22));

	//	控制台输入控件
	m_edInput.Create( hWnd, WS_BORDER|ES_WANTRETURN, 30, 524, 539, 20, "");
	m_edInput.SetId( IDED_INPUT );

	//	输入按钮
	m_btnInput.Create( hWnd, "发送", 0, 580,524,70,20);
	m_btnInput.SetId(IDBTN_INPUT);

	//	组
	m_grp01.Create( hWnd, BS_GROUPBOX, winwidth - 132 , 30, 100 , 515, "状态", 0 );

	//	labels
	m_lbType.Create( hWnd, style2,	 x, top, width, 15, m_pszServerName );
	m_lbText01.Create( hWnd, style1, x , (top+=20), width, 15, "连接数" );
	m_lbConnections.Create( hWnd, style2, x, (top+=20), width, 15, "0" );
	m_lbText02.Create( hWnd, style1, x, (top+=20), width, 15, "连接次数" );		//	连接次数
	m_lbConnectedTimes.Create( hWnd, style2, x, (top+=20), width, 15, "0" );
	m_lbText03.Create( hWnd, style1, x, (top+=20), width, 15, "断开次数" );		//	断开次数
	m_lbDisconnectedTimes.Create( hWnd, style2, x, (top+=20), width, 15, "0" );
	m_lbText04.Create( hWnd, style1, x, (top+=20), width, 15, "发送" );			//	发送字节数
	m_lbSendBytes.Create( hWnd, style2, x, (top+=20), width, 15, "0" );
	m_lbText05.Create( hWnd, style1, x, (top+=20), width, 15, "接收" );			//	接收字节数
	m_lbRecvBytes.Create( hWnd, style2, x, (top+=20), width, 15, "0" );
	m_lbText06.Create( hWnd, style1, x, (top+=20), width, 15, "循环时间" );		//	循环时间
	m_lbLooptime.Create( hWnd, style2, x, (top+=20), width, 15, "0.0 ms" );

	//// 命令行选择控件
	//m_CmdComboBox.Create( hWnd, x, (top+=20), width, 150 );
	//m_CmdComboBox.SetId(ID_CMD_COMBO);

	//// 命令行控件
	//m_CmdList.Create( hWnd, 0, x, (top+=20), width, 20, 50 );
	//m_CmdList.SetId(ID_CMD_LIST);


	m_edInput.SetMsgFilter( this );

	HDC	dc = GetDC();
	ReleaseDC( dc );
	MakeAllFont();
	GetTickCount();
}
//------------------------------------------------------------------------
VOID CServerForm::MakeAllFont()
{
	LOGFONT LogFont;
	ZeroMemory( &LogFont, sizeof(LogFont) );
	LogFont.lfHeight			= -13;
	LogFont.lfWidth				= 0;
	LogFont.lfEscapement		= 0;
	LogFont.lfOrientation		= 0;
	LogFont.lfWeight			= FW_NORMAL;
	LogFont.lfItalic			= FALSE;
	LogFont.lfUnderline			= FALSE;
	LogFont.lfStrikeOut			= FALSE;
	LogFont.lfCharSet			= GB2312_CHARSET;
	LogFont.lfOutPrecision		= 3;
	LogFont.lfClipPrecision		= 2;
	LogFont.lfQuality			= 1;
	LogFont.lfPitchAndFamily	= 2;
	strcpy(LogFont.lfFaceName, "宋体" );

	HFONT	hFont = CreateFontIndirect( &LogFont );
	SetFont(hFont);
}
//------------------------------------------------------------------------
void CServerForm::InitToolbar(UINT nBitmapId)
{
	TBBUTTON	buttons[2];
	ZeroMemory( buttons, sizeof( buttons ));
	buttons[0].iBitmap = 0;
	buttons[0].idCommand = IDM_STARTSERVER;
	buttons[0].iString = 0;
	buttons[0].fsStyle = TBSTYLE_BUTTON;
	buttons[0].fsState = TBSTATE_ENABLED;
	buttons[1].iBitmap = 1;
	buttons[1].idCommand = IDM_STOPSERVER;
	buttons[1].iString = 0;
	buttons[1].fsStyle = TBSTYLE_BUTTON;
	buttons[1].fsState = 0;

	HINSTANCE	hInst = GetModuleHandle(NULL);

	m_hToolsBar = CreateToolbarEx( m_hWnd,WS_CHILD|CCS_TOP|WS_VISIBLE|TBSTYLE_TOOLTIPS,ID_TOOLBAR,
		2,hInst,(nBitmapId), buttons, 2,16, 16, 16, 16, sizeof( TBBUTTON ));
}
//------------------------------------------------------------------------
void CServerForm::InitStatueBar()
{
	m_hStatueBar = CreateStatusWindow(WS_CHILD|WS_VISIBLE,NULL,m_hWnd, ID_STATUEBAR );
}
//------------------------------------------------------------------------
VOID CServerForm::OnCommand( UINT id )
{
	switch( id )
	{
		// 启动服务器
	case	IDM_STARTSERVER:
		{
			SendMessage( m_hToolsBar, TB_ENABLEBUTTON, (WPARAM)IDM_STARTSERVER, (LPARAM)MAKELONG(FALSE,0) );
			if( !StartServer() )
			{
				SendMessage( m_hToolsBar, TB_ENABLEBUTTON, (WPARAM)IDM_STARTSERVER, (LPARAM)MAKELONG(TRUE,0) );
			}
			else
			{
				SetTimer( m_hWnd, ID_STATUETIMER, 1000, NULL );
				SendMessage( m_hToolsBar, TB_ENABLEBUTTON, (WPARAM)IDM_STOPSERVER, (LPARAM)MAKELONG(TRUE,0) );
			}
		}
		break;
		// 停止服务器
	case	IDM_STOPSERVER:
		{
			SendMessage( m_hToolsBar, TB_ENABLEBUTTON, (WPARAM)IDM_STOPSERVER, (LPARAM)MAKELONG(FALSE,0) );
			if( !StopServer() )
			{
				SendMessage( m_hToolsBar, TB_ENABLEBUTTON, (WPARAM)IDM_STOPSERVER, (LPARAM)MAKELONG(TRUE,0) );
			}
			else
			{
				KillTimer(m_hWnd, ID_STATUETIMER );
				SendMessage( m_hToolsBar, TB_ENABLEBUTTON, (WPARAM)IDM_STARTSERVER, (LPARAM)MAKELONG(TRUE,0) );
			}
		}
		break;
	case IDBTN_INPUT:
		{
			char	szText[1024];
			int count = m_edInput.GetText( szText, sizeof( szText ) );
			if( count > 0 )
			{
				m_pInputListener->OnInput( szText );
			}
			m_edInput.SetText("" );
		}
		break;
	//case ID_CMD_LIST:
	//	{
	//		// todo:
	//	}
	//	break;
	//case ID_CMD_COMBO:
	//	{
	//		// todo:
	//	}
	//	break;
	}
}
//------------------------------------------------------------------------
BOOL CServerForm::StartServer()
{
	if(m_pServer != NULL)
	{
		CSettingFile sf;
		if( !sf.Open( CONFIG_FILENAME ) )
		{
			m_reChat.printf( RGB( 255, 0, 0 ), "启动服务器失败：%s\n", ERRMSG_NOCONFIGFILE );
			return FALSE;
		}
		m_bShowConfirm = sf.GetInteger( NULL, "是否关闭前提示", 0 );
		return m_pServer->Start(sf);
	}
	m_reChat.printf( RGB( 255, 0, 0 ), "启动服务器失败：%s\n", ERRMSG_NOSERVER );
	return FALSE;
}
//------------------------------------------------------------------------
BOOL CServerForm::StopServer()
{
	if(m_pServer != NULL)
		return m_pServer->Stop();
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CServerForm::OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case	WM_TIMER:
		{
			OnTimer();
		}
		break;
	}
	return CEGForm::OnMessage( hWnd, uMsg, wParam, lParam );
}
//------------------------------------------------------------------------
VOID CServerForm::OnTimer()
{
	m_iThroughCount ++;

	SERVERSTATE	serverstate;
	char * pServerName = NULL;
	if( m_pServer != NULL )
	{
		m_pServer->GetServerState(serverstate);
	}
	CHAR	text[200];

	sprintf( text, "[%s]%s-%s", 	SERVER_COPYRIGHT, m_pszServerName, serverstate.pServerDescript );
	SetText( text );

	m_lbConnections.printf( "%d", serverstate.numConnection );
	m_lbConnectedTimes.printf( "%d", serverstate.numConnected );
	m_lbDisconnectedTimes.printf( "%d", serverstate.numDisconnected );

	m_lbLooptime.printf( "%f ms", serverstate.fLoopTime );
	CServerTimer::SetTimeJump( ((int)( serverstate.fLoopTime+0.5f)) + 5 );
	m_lbRecvBytes.printf( "%u", serverstate.dwRecvBytes );
	m_lbSendBytes.printf( "%u", serverstate.dwSendBytes );
}
//------------------------------------------------------------------------
VOID CServerForm::OutPutStatic( DWORD dwColor, const char * pszString )
{
	if(NULL == pszString)
		return;

	SYSTEMTIME st;
	GetLocalTime(&st);
	char buf[4096];
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	strcat(buf, pszString);

	m_reChat.printf( dwColor, "%s", buf);
}
//------------------------------------------------------------------------
BOOL CServerForm::FilterMessage(CEGBaseWnd * pWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( pWnd->GetId() == IDED_INPUT )
	{
		if( uMsg == WM_KEYDOWN && wParam == VK_RETURN )
		{
			char	szText[1024];
			int count = m_edInput.GetText( szText, sizeof( szText ) );
			if( count > 0 )
			{
				m_pInputListener->OnInput( szText );
			}
			m_edInput.SetText("" );
		}
	}
	return FALSE;
}
//------------------------------------------------------------------------
int CServerForm::EnterMessageLoop()
{
	if( stricmp( m_pCmdLine, "start" ) == 0 )
		OnCommand( IDM_STARTSERVER );
	return CEGForm::EnterMessageLoop();
}
//------------------------------------------------------------------------
BOOL CServerForm::OnClose()
{
	if( m_bShowConfirm )
	{
		if( !ConfirmBox( m_hWnd, "请您确认", "您真的要关闭服务器么？") )
			return FALSE;
	}
	if( m_pServer )
	{
		m_pServer->Terminate();
	}
	return TRUE;
}
//------------------------------------------------------------------------