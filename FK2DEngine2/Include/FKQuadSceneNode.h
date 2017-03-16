/**
*	created:		2013-4-23   23:07
*	filename: 		FKQuadSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKQuad.h"
#include "FKIRenderObjectSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class CQuadSceneNode : public IRenderObjectSceneNode
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"CQuadSceneNode";
				}
				CQuadSceneNode(const std::wstring nodeName,
					ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 rotate_,
					FK2DEngine2::math::Vector3 scale_,
					FK2DEngine2::math::Quad quad_);
				virtual ~CQuadSceneNode();
			protected:
				FK2DEngine2::math::Quad quad;
			};
		}
	}
}
//------------------------------------------------------------------------