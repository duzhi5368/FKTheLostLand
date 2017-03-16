/**
*	created:		2013-4-23   23:00
*	filename: 		FKLightSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKILightSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class CLightSceneNode : public ILightSceneNode
			{
			public :
				virtual const std::wstring getTypeInfo() const {
					return L"CLightSceneNode";
				}
				CLightSceneNode(const std::wstring nodeName,ISceneNode * parent,
					I3DSceneManager * manager,FK2DEngine2::math::Vector3 position
					,FK2DEngine2::video::SLight light_)
					:ILightSceneNode(nodeName,parent,manager,position,light_){}
				virtual void beforeRender();
				virtual void render();
			};
		}
	}
}
//------------------------------------------------------------------------