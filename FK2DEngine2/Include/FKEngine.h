/**
*	created:		2013-4-23   23:14
*	filename: 		FKEngine
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIEngine.h"
#include "FKD3D9VideoDriver.h"
#include "FKFmodAudioDriver.h"
#include "FKDInput8Driver.h"
#include "FKWin32Window.h"
#include "FKWin32Timer.h"
#include "FK2DSceneManager.h"
#include "FK3DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	class CEngine : public IEngine
	{
	public:
		virtual const std::wstring getTypeInfo() const {
			return L"CEngine";
		}

		CEngine();
		virtual ~CEngine();

		virtual bool initEngine();
		virtual bool runEngine();
		virtual bool shutEngine();

		virtual void setEngineStateB(E_ENGINE_STATE state,bool value);
		virtual void setEngineStateI(E_ENGINE_STATE state,unsigned long value);
		virtual void setEngineStateF(E_ENGINE_STATE state,float value);
		virtual void setEngineStateStr(E_ENGINE_STATE state,const std::wstring & str); 

		virtual bool getEngineStateB(E_ENGINE_STATE state);
		virtual unsigned long getEngineStateI(E_ENGINE_STATE state);
		virtual float getEngineStateF(E_ENGINE_STATE state);
		virtual const std::wstring getEngineStateStr(E_ENGINE_STATE state);

	private:
		// window :
		unsigned long windowWidth;	// default = 1024;
		unsigned long windowHeight; // default = 768;
		unsigned long windowStyle ; // default = WS_OVERLAPPEDWINDOW
		std::wstring windowName;	// default = "FK_Window"

		// video :
		unsigned long zdepth;		// default = 255;
		bool fullscreen;			// default = false,
		bool zbuffer;				// default  = true,
		bool alphatesting;			// default  = false,
		bool alphablend;			// default = true,
		bool lighting;				// default = false
		
		// input :
		bool initKeyboard;			// default = true;
		bool initMouse;				// default = true;

		// timer :
		float fps;					// default = 60.0f
	};
}
//------------------------------------------------------------------------