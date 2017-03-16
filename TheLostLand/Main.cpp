/**
*	created:		2013-5-1   20:58
*	filename: 		Main
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "MainMacro.h"
#include "MainImpl.h"
#include "../depend/vld2.3/include/vld.h"
//------------------------------------------------------------------------
//#ifdef _DEBUG  
//#include <crtdbg.h>  
//#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)  
//#else  
//#define DEBUG_NEW new  
//#endif 
////------------------------------------------------------------------------
//#ifdef _DEBUG   
//#define new DEBUG_NEW  
//#endif  
//------------------------------------------------------------------------
IEngine *						g_pEngine = NULL;
IVideoDriver *					g_pVideoDriver = NULL;
I2DSceneManager *				g_p2DSceneMgr = NULL;
IInputDriver *					g_pInputDriver = NULL;
CFKTrace *						g_pTrace = NULL;
IResMgr*						g_pResMgr = NULL;

bool							g_bReadyExit = false;
//------------------------------------------------------------------------
// 自己的初始化
bool MyInit();
// 主循环
bool MyUpdate();
// 自己的释放
bool MyShut();
//------------------------------------------------------------------------
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	// 开启DEBUG内存泄露检查
	_CrtDumpMemoryLeaks();
	// 不能启动超过二个相同的进程
	if(!FKProcessLimitGuard<1>::Instance()->IsOwned())
	{
		MessageBox(0, L"对不起，本游戏不支持双开以及多开。", L"FreeKnightGame提示", 0);
		return 0;
	}

	g_pEngine = GetEngine();
	if( !g_pEngine )
	{
		return -1;
	}
	g_pEngine->setEngineStateStr( E_ENGINE_STATE_WINDOWNAME, L"遗失之岛 Version 1.0 by FK2DEngine2");
	if( !g_pEngine->initEngine())
	{
		return -2;
	}
	if( !MyInit() )
	{
		return -3;
	}

	// 主循环
	while (g_pEngine->runEngine())
	{
		// 自己的每帧循环
		if (!MyUpdate())
		{
			break;
		}
	}

	if( !MyShut() )
	{
		return -4;
	}
	if( !g_pEngine->shutEngine())
	{
		return -5;
	}
	return 0;
}
//------------------------------------------------------------------------
// 自己的初始化
bool MyInit()
{
	// 初始化部分设备资源
	g_pVideoDriver = g_pEngine->getVideoDriver();
	g_pInputDriver = g_pEngine->getInputDriver();
	g_p2DSceneMgr = g_pEngine->get2DSceneManager();
	g_pTrace = g_pEngine->getTraceWin();
	g_pResMgr = g_pEngine->getResMgr();

	// 读取配置
	if( !InitConfig() )
	{
		FKTRACE( L"加载配置文件失败..." );
		return false;
	}

	// 场景
	g_p2DSceneMgr->SetSceneMgr( CGameSceneMgr::GetInstancePtr() );
	g_p2DSceneMgr->GetSceneMgr()->SetCurScene( eScene_LoginScene );

	return true;
}
//------------------------------------------------------------------------
// 主循环
bool MyUpdate()
{
	g_pVideoDriver->beginScene(SColor::orange(),E_CLEAR_COLOR|E_CLEAR_ZBUFFER);
	{
		// 每帧刷新Input设备状态【使用DInput只能获取两帧间偏移】
		g_pInputDriver->refreshDriverState();

		// 渲染2D对象
		g_p2DSceneMgr->begin2DScene();
		g_p2DSceneMgr->drawAll( g_pEngine->getUICanvas() );
		g_p2DSceneMgr->end2DScene();

		// 渲染UI
		g_p2DSceneMgr->renderUI( g_pEngine->getUICanvas() );
	}
	// 关闭渲染
	g_pVideoDriver->endScene();

	if( g_bReadyExit )
	{
		return false;
	}

	return true;
}
//------------------------------------------------------------------------
// 自己的释放
bool MyShut()
{
	return true;
}
//------------------------------------------------------------------------