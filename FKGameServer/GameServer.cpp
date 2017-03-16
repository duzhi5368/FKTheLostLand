/**
*	created:		2013-4-18   23:23
*	filename: 		GameServer
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "GameServer.h"
#include "server.h"
#include "fmttextfile.h"
#include "scriptobject.h"
#include "savetodbthread.h"
//------------------------------------------------------------------------
#define FK_GAMESVR_LOG		".\\log\\FKGameSvrLog"
//------------------------------------------------------------------------
CServerForm g_Form;
CServer	*	g_pServer = NULL;
//------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
#ifndef _DEBUG
	SetUnhandledExceptionFilter( StackTraceExceptionFilter );
#endif
	int ret = 0;

	TRY_INIT
	CLogFile::GetInstance()->Init( FK_GAMESVR_LOG );
	g_Form.Create( SERVER_NAME, lpCmdLine );
	g_Form.InitToolbar(IDB_TOOLBAR);
	g_Form.InitStatueBar();
	g_pServer = CServer::GetInstance();
	g_pServer->SetServerName(SERVER_NAME);
	g_pServer->SetIoConsole(&g_Form);
	g_Form.SetInputListener(g_pServer);
	g_Form.SetServer(g_pServer);
	ret = g_Form.EnterMessageLoop();

	return ret;
}
//------------------------------------------------------------------------