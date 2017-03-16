/**
*	created:		2013-4-23   23:02
*	filename: 		FKCameraSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKICameraSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class CCameraSceneNode : public ICameraSceneNode
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"CCameraSceneNode";
				}
				CCameraSceneNode(const std::wstring nodeName,ISceneNode * parent,
					I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 at)
					:ICameraSceneNode(nodeName,parent,manager_,position_,at)
				{}

				virtual void render();
			};
		}
	}
}
//------------------------------------------------------------------------