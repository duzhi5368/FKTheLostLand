/**
*	created:		2013-4-23   22:52
*	filename: 		FKEmptySceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKEmptySceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			CEmptySceneNode::CEmptySceneNode(const std::wstring nodeName,ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_)
					:ISceneNode(nodeName,parent_,manager_,position_,FK2DEngine2::math::Vector3(0,0,0),FK2DEngine2::math::Vector3(1,1,1))
			{
			}

			void CEmptySceneNode::render()
			{
				// do nothing...
			}
		}
	}
}
//------------------------------------------------------------------------