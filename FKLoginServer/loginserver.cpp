/**
*	created:		2013-4-14   20:59
*	filename: 		loginserver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "loginserver.h"
#include "server.h"
#include "FKLoginServerDefine.h"
//------------------------------------------------------------------------
CServerForm g_Form;
CServer	*g_pServer;
//------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CLogFile::GetInstance()->Init( LOGIN_SERVER_LOG_FILE );
	g_Form.Create( SERVER_NAME, lpCmdLine );
	g_Form.InitToolbar(IDB_TOOLBAR);
	g_Form.InitStatueBar();
	g_pServer = CServer::GetInstance();
	g_pServer->SetServerName(SERVER_NAME);
	g_pServer->SetIoConsole(&g_Form);
	g_Form.SetInputListener(g_pServer);
	g_Form.SetServer(g_pServer);
	return (int) g_Form.EnterMessageLoop();
}
//------------------------------------------------------------------------