/**
*	created:		2013-4-23   23:10
*	filename: 		FKIEngine
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
#include "FKResourceMap.h"
#include "FKIVideoDriver.h"
#include "FKIInputDriver.h"
#include "FKIAudioDriver.h"
#include "FKITimer.h"
#include "FKIWindow.h"
#include "FKI2DSceneManager.h"
#include "FKI3DSceneManager.h"
#include "FKUIOutSideHead.h"
#include "FKTrace.h"
#include "IFKFileSystem.h"
#include "IFKResManager.h"
//--------------------------------------------------------------------
namespace FK2DEngine2
{
	typedef enum {
		// window :
		E_ENGINE_STATE_WINDOWWIDTH,		// 1024
		E_ENGINE_STATE_WINDOWHEIGHT,	// 768
		E_ENGINE_STATE_WINDOWSTYLE,		// WS_OVERLAPPEDWINDOW
		E_ENGINE_STATE_WINDOWNAME,		// "FK_Window"
		E_ENGINE_STATE_WINDOWFUNC,		// CWin32Window::winMessageFunc
		
		// video :
		E_ENGINE_STATE_ZDEPTH,			// 255
		E_ENGINE_STATE_FULLSCREEN,		// false
		E_ENGINE_STATE_ZBUFFER,			// true
		E_ENGINE_STATE_ALPHATESTING,	// false
		E_ENGINE_STATE_ALPHABLEND,		// true
		E_ENGINE_STATE_LIGHTING,		// false
		
		// input :
		E_ENGINE_STATE_INITKEYBOARD,	// true
		E_ENGINE_STATE_INITMOUSE,		// true

		// timer :
		E_ENGINE_STATE_FPS				// 60.0
	}E_ENGINE_STATE;

	class IEngine : public FK2DEngine2::core::IBase
	{
	public :
		virtual const std::wstring getTypeInfo() const {
			return L"IEngine";
		}
		IEngine(){
			uiRenderDriver = NULL;
			uiCanvas = NULL;
			uiInput = NULL;
			uiSkin = NULL;
			videoDriver = NULL;
			inputDriver = NULL;
			audioDriver = NULL;
			window = NULL;
			timer = NULL;
			i2DSceneManager = NULL;
			i3DSceneManager = NULL;
			traceWin = NULL;
			resMgr = NULL;
		}
		virtual ~IEngine(){}
		
		virtual bool initEngine() = 0;
		virtual bool runEngine() = 0;
		virtual bool shutEngine() = 0;

		virtual void setEngineStateB(E_ENGINE_STATE state,bool value) = 0;
		virtual void setEngineStateI(E_ENGINE_STATE state,unsigned long value) = 0;
		virtual void setEngineStateF(E_ENGINE_STATE state,float value) = 0;
		virtual void setEngineStateStr(E_ENGINE_STATE state,const std::wstring & str) = 0; 

		virtual bool getEngineStateB(E_ENGINE_STATE state) = 0;
		virtual unsigned long getEngineStateI(E_ENGINE_STATE state) = 0;
		virtual float getEngineStateF(E_ENGINE_STATE state) = 0;
		virtual const std::wstring getEngineStateStr(E_ENGINE_STATE state) = 0;
		
		FK2DEngine2::video::IVideoDriver * getVideoDriver(){
			return videoDriver;
		}
		FK2DEngine2::input::IInputDriver * getInputDriver(){
			return inputDriver;
		}
		FK2DEngine2::audio::IAudioDriver * getAudioDriver(){
			return audioDriver;
		}
		FK2DEngine2::system::IWindow * getWindow(){
			return window;
		}
		FK2DEngine2::system::ITimer * getTimer(){
			return timer;
		}
		FK2DEngine2::core::CResourceMap * getResourceMap(){
			return resourceMap;
		}
		FK2DEngine2::scene::S2D::I2DSceneManager * get2DSceneManager(){
			return i2DSceneManager;
		}
		FK2DEngine2::scene::S3D::I3DSceneManager * get3DSceneManager(){
			return i3DSceneManager;
		}
		FK2DEngine2::video::DirectX9 * getUIRenderDriver(){
			return uiRenderDriver;
		}
		FK2DEngine2::Controls::Canvas * getUICanvas(){
			return uiCanvas;
		}
		FK2DEngine2::Input::Windows * getUIInput(){
			return uiInput;
		}
		FK2DEngine2::Skin::TexturedBase * getUISkin(){
			return uiSkin;
		}
		CFKTrace* getTraceWin(){
			return traceWin;
		}
		IResMgr* getResMgr(){
			return resMgr;
		}
	protected:
		FK2DEngine2::video::IVideoDriver * 			videoDriver;
		FK2DEngine2::input::IInputDriver * 			inputDriver;
		FK2DEngine2::audio::IAudioDriver * 			audioDriver;
		FK2DEngine2::system::IWindow *				window;
		FK2DEngine2::system::ITimer *				timer;
		FK2DEngine2::core::CResourceMap *			resourceMap;
		FK2DEngine2::scene::S2D::I2DSceneManager *	i2DSceneManager;
		FK2DEngine2::scene::S3D::I3DSceneManager *	i3DSceneManager;
		FK2DEngine2::video::DirectX9 *				uiRenderDriver;
		FK2DEngine2::Controls::Canvas *				uiCanvas;
		FK2DEngine2::Input::Windows *				uiInput;
		FK2DEngine2::Skin::TexturedBase *			uiSkin;
		CFKTrace*									traceWin;
		IResMgr*									resMgr;
	};

	extern IEngine* g_pEngineInstance;
}
//------------------------------------------------------------------------