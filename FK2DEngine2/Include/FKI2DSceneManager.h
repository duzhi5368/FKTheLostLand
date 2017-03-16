/**
*	created:		2013-4-23   22:06
*	filename: 		FKI2DSceneManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
#include "FKS2DObject.h"
#include "FKIVideoDriver.h"
#include "FKMessage.h"
#include "FKISceneMgr.h"
#include "UI/Controls/FKCanvas.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S2D
		{
			class I2DSceneManager : public FK2DEngine2::core::IBase, public FK2DEngine2::event::CMessageListener
			{
			public :
				virtual const std::wstring getTypeInfo() const {
					return L"I2DSceneManager";
				}

				virtual bool init2DSceneManager(FK2DEngine2::video::IVideoDriver * videoDriver_,int bufferLength,
					float width,float height,float zdepth) = 0;
				virtual bool shut2DSceneManager() = 0;
				virtual bool begin2DScene() = 0;
				virtual void drawAll( FK2DEngine2::Controls::Canvas * uiCanvas ) = 0;
				virtual void renderUI( FK2DEngine2::Controls::Canvas * uiCanvas ) = 0;
				virtual bool end2DScene() = 0;
				virtual void RenderPixel(S2DPixel pixel,float x,float y,float z) = 0;
				virtual void RenderLine(S2DLine line,float x,float y,float z) = 0;
				virtual void RenderTriangle(S2DTriangle triangle,float x,float y,float z) = 0;
				virtual void RenderQuad(S2DQuad quad,float x,float y,float z) = 0;
				virtual void RenderQuadEx(S2DQuad quad,float x,float y,float z,float angle,float scalex,float scaley) = 0;
				virtual void SetSceneMgr(FKISceneManager* scene) = 0;
				virtual FKISceneManager* GetSceneMgr() = 0;
			};
		}
	}
}
//------------------------------------------------------------------------