/**
*	created:		2013-4-16   5:14
*	filename: 		ServerForm
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "..\..\FKeasygui\easygui.h"
#include "ioconsole.h"
#include "baseServer.h"
//------------------------------------------------------------------------
#define IDM_STARTSERVER	10000
#define IDM_STOPSERVER	10001
#define IDRE_CHAT		20000
#define ID_TOOLBAR		20001
#define ID_STATUEBAR	20002
#define IDED_INPUT		20003
#define IDBTN_INPUT		20004
#define ID_STATUETIMER	20005
//#define ID_CMD_LIST		20006
//#define ID_CMD_COMBO	20007
//------------------------------------------------------------------------
#define CONFIG_FILENAME	".\\config.ini"
//------------------------------------------------------------------------
class CProgressForm;
//------------------------------------------------------------------------
class CServerForm :
	public CEGForm,public CIOConsole, public CEGWndMsgFilter
{
public:
	CServerForm(void);
	virtual ~CServerForm(void);
public:
	BOOL	Create( const char * pszTitle, const char * pszCmdLine = NULL );
	BOOL	OnClose();
	VOID	OnCreate( HWND hWnd );
	//	统一窗口控件的字体~
	VOID	MakeAllFont();
	void	InitToolbar(UINT nBitmapId);
	void	InitStatueBar();
	void	OnCommand( UINT id );
	virtual BOOL StartServer();
	virtual BOOL StopServer();
	virtual VOID OnTimer();
	BOOL	OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	void	OutPutStatic(DWORD dwColor, const char * pszString );
	CBaseServer * GetServer(){return m_pServer;}
	void	SetServer( CBaseServer * pServer ){ m_pServer = pServer;}
	BOOL	FilterMessage(CEGBaseWnd * pWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int		EnterMessageLoop();
	CProgressForm * GetProgressForm(){ return m_pProgressForm;}
protected:
	HWND	m_hStatueBar;
	HWND	m_hToolsBar;
	CEGRichEdit	m_reChat;
	CEGEditBox	m_edInput;
	CEGPushButton m_btnInput;
	CEGButton	m_grp01;
	CBaseServer * m_pServer;
	CEGLabel	m_lbType;
	CEGLabel	m_lbText01;	//	连接数
	CEGLabel	m_lbText02;	//	连接次数
	CEGLabel	m_lbText03;	//	断开次数
	CEGLabel	m_lbText04;	//	发送字节数
	CEGLabel	m_lbText05;	//	接收字节数
	CEGLabel	m_lbText06;	//	循环时间
	CEGLabel	m_lbConnections;
	CEGLabel	m_lbConnectedTimes;
	CEGLabel	m_lbDisconnectedTimes;
	CEGLabel	m_lbRecvBytes;
	CEGLabel	m_lbSendBytes;
	CEGLabel	m_lbLooptime;
	//CEGListBox	m_CmdList;
	//CEGComboBox m_CmdComboBox;
	UINT		m_iThroughCount;
	char *		m_pCmdLine;
	BOOL		m_bShowConfirm;
	CProgressForm * m_pProgressForm;
protected:
	char *	m_pszServerName;
};
//------------------------------------------------------------------------
