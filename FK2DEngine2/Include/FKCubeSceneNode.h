/**
*	created:		2013-4-23   23:05
*	filename: 		FKCubeSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIRenderObjectSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class CCubeSceneNode : public IRenderObjectSceneNode
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"CCubeSceneNode";
				}
				CCubeSceneNode(const std::wstring nodeName,
					ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 size,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 rotate_,
					FK2DEngine2::math::Vector3 scale_);
			protected:
				FK2DEngine2::math::Vector3 size;
			};
		}
	}
}
//------------------------------------------------------------------------