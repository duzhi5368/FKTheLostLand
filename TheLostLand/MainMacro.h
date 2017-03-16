/**
*	created:		2013-5-1   20:59
*	filename: 		MainMacro
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------

#pragma once
//------------------------------------------------------------------------
#include "../FK2DEngine2/FK2DEngine2.h"
#include "../CS_Common/CS_CommonDefine.h"
#include "ResTable.h"
//------------------------------------------------------------------------
// 是否开启单机测试模式
// #define SINGLE_TEST
//------------------------------------------------------------------------
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#pragma warning( disable:4244 )
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::core;
using namespace FK2DEngine2::video;
using namespace FK2DEngine2::input;
using namespace FK2DEngine2::system;
using namespace FK2DEngine2::audio;
using namespace FK2DEngine2::math;
using namespace FK2DEngine2::scene;
using namespace FK2DEngine2::scene::S2D;
using namespace FK2DEngine2::scene::S3D;
using namespace FK2DEngine2::Controls;
using namespace FK2DEngine2::actor;
//------------------------------------------------------------------------
extern IEngine *						g_pEngine;
extern IVideoDriver *					g_pVideoDriver;
extern I2DSceneManager *				g_p2DSceneMgr;
extern IInputDriver *					g_pInputDriver;
extern CFKTrace *						g_pTrace;
extern bool								g_bReadyExit;
extern IResMgr*							g_pResMgr;
//------------------------------------------------------------------------
#include "GameSceneMgr.h"
//------------------------------------------------------------------------
#define FKTRACE							g_pTrace->ThreadSafeDebugPrintLn
#define FKTRACET						g_pTrace->ThreadSafeDebugPrintLnWithTime
//------------------------------------------------------------------------
#define DEFAULT_BACKGROUND_LAYER_Z		250
#define GAME_CANVAS_WIDTH				1024
#define GAME_CANVAS_HEIGHT				768
//------------------------------------------------------------------------