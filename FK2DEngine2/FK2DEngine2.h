/**
*	created:		2013-4-21   17:25
*	filename: 		FKWrapperInclude
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#ifndef FK_STATIC
	#ifdef	FK_DLL_EXPORTS
	#define FK_API __declspec(dllexport)
	#else
	#define FK_API __declspec(dllimport)
	#endif
#else  
	#define FK_API 
#endif
//------------------------------------------------------------------------
#include "Include/Network/IFKAppNetworkLink.h"
#include "Include/Network/GameSvrLinkSink.h"
#include "Include/Network/LoginSvrLinkSink.h"
#include "Include/Network/CharSelSvrLinkSink.h"
#include "Include/Network/IDateArchive.h"

#include "Include/FKProcessLimit.h"
#include "Include/FKSystemInfo.h"

#include "Include/FKUIOutSideHead.h"

#include "Include/FKLogger.h"

#include "Include/IFKFileSystem.h"

#include "Include/IFKResManager.h"

#include "Include/FKTrace.h"

#include "Include/FKMathMacro.h"
#include "Include/FKMathUtil.h"
#include "Include/FKInterval.h"
#include "Include/FKLine3D.h"
#include "Include/FKMatrix4.h"
#include "Include/FKVector3.h"
#include "Include/FKPlane.h"
#include "Include/FKQuad.h"
#include "Include/FKTriangle.h"
#include "Include/FKVector2.h"
#include "Include/FKVector4.h"
#include "Include/FKVertex.h"
#include "Include/FKAABBox.h"

#include "Include/FKCoreInterface.h"
#include "Include/FKStringConvert.h"
#include "Include/FKIBase.h"
#include "Include/FKIResource.h"
#include "Include/FKLogger.h"
#include "Include/FKSingleton.h"
#include "Include/FKException.h"
#include "Include/FKResourceMap.h"
#include "Include/FKPing.h"

#include "Include/FKLight.h"
#include "Include/FKSColor.h"
#include "Include/FKSMaterial.h"
#include "Include/FKIFont.h"

#include "Include/FKKeyCode.h"
#include "Include/FKIInputDevice.h"
#include "Include/FKDInput8Driver.h"

#include "Include/FKIWindow.h"
#include "Include/FKITimer.h"

#include "Include/FKISound.h"
#include "Include/FKIChannel.h"
#include "Include/FKIAudioDriver.h"

#include "Include/FKS2DObject.h"
#include "Include/FKI2DSceneManager.h"
#include "Include/FK2DSceneManager.h"
#include "Include/FKIRenderable.h"
#include "Include/FKRenderableIterator.h"
#include "Include/FKISceneMgr.h"
#include "Include/FKActor.h"
#include "Include/FKGridActor.h"
#include "Include/FKFullScreenActor.h"
#include "Include/FKIScene.h"

#include "Include/FKISceneNode.h"
#include "Include/FKIRenderObjectSceneNode.h"
#include "Include/FKILightSceneNode.h"
#include "Include/FKICameraSceneNode.h"
#include "Include/FKI3DSceneManager.h"

#include "Include/FKMessage.h"
#include "Include/FKCallback.h"
#include "Include/FKSwitchboard.h"
#include "Include/FKTagCollection.h"

#include "Include/FKIEngine.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core{}
	namespace math{}
	namespace video{}
	namespace input{}
	namespace audio{}
}
//------------------------------------------------------------------------
FK_API FK2DEngine2::IEngine* GetEngine();
//------------------------------------------------------------------------