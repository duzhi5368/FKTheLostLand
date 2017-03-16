/**
*	created:		2013-4-23   22:51
*	filename: 		FKEmptySceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKISceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class CEmptySceneNode : public ISceneNode
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"CEmptySceneNode";
				}
				CEmptySceneNode(const std::wstring nodeName,ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_);

				virtual void render();
			};
		}
	}
}
//------------------------------------------------------------------------