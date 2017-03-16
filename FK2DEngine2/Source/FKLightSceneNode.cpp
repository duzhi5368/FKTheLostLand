/**
*	created:		2013-4-23   23:01
*	filename: 		FKLightSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKLightSceneNode.h"
#include "../Include/FKI3DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D 
		{
			void CLightSceneNode::beforeRender()
			{
				if (isVisible)
				{
					manager->registerNodeForRendering(this,E_NODE_TYPE_LIGHT);
				}
				ILightSceneNode::beforeRender();
				light.position = getAbsolutePosition();
			}
			void CLightSceneNode::render()
			{
				manager->getVideoDriver()->addLight(light);
			}
		}
	}
}
//------------------------------------------------------------------------