/**
*	created:		2013-4-23   23:08
*	filename: 		FKQuadSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKQuadSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			CQuadSceneNode::CQuadSceneNode(const std::wstring nodeName,
					ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 rotate_,
					FK2DEngine2::math::Vector3 scale_,
					FK2DEngine2::math::Quad quad_)
					:IRenderObjectSceneNode(nodeName,parent_,manager_,position_,rotate_,scale_)
					,quad(quad_)
			{
				this->vertices = (FK2DEngine2::math::Vertex *)&quad;
				this->verticesLength = 4;
				this->indices = new unsigned short[6];
				this->indicesLength = 6;
				indices[0] = 0; indices[1] = 1;
				indices[2] = 2; indices[3] = 1;
				indices[4] = 3; indices[5] = 2; 
			}
			CQuadSceneNode::~CQuadSceneNode()
			{
				vertices = NULL;
			}
		}
	}
}
//------------------------------------------------------------------------