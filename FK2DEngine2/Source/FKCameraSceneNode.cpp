/**
*	created:		2013-4-23   23:03
*	filename: 		FKCameraSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKCameraSceneNode.h"
#include "../Include/FKI3DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			void CCameraSceneNode::render()
			{
				FK2DEngine2::video::IVideoDriver * videoDriver = manager->getVideoDriver();
				videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_VIEW,viewMatrix);
				videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_PROJECTION,projectionMatrix);	
			}
		}
	}
}
//------------------------------------------------------------------------