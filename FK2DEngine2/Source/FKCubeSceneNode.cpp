/**
*	created:		2013-4-23   23:06
*	filename: 		FKCubeSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKCubeSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			CCubeSceneNode::CCubeSceneNode(const std::wstring nodeName,
					ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 size_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 rotate_,
					FK2DEngine2::math::Vector3 scale_)
					:IRenderObjectSceneNode(nodeName,parent_,manager_,position_,rotate_,scale_)
					,size(size_)
			{
				this->vertices = new FK2DEngine2::math::Vertex [12];
				this->verticesLength = 12;
				vertices[0].SetValue(-size.x/2,-size.y/2,-size.z/2, -1,-1,-1, 0xffffffff, 0, 1);
				vertices[1].SetValue(size.x/2,-size.y/2,-size.z/2,  1,-1,-1, 0xffffffff, 1, 1); 
				vertices[2].SetValue(size.x/2,size.y/2,-size.z/2,  1, 1,-1, 0xffffffff, 1, 0); 
				vertices[3].SetValue(-size.x/2,size.y/2,-size.z/2, -1, 1,-1, 0xffffffff, 0, 0); 
				vertices[4].SetValue(size.x/2,-size.y/2,size.z/2,  1,-1, 1, 0xffffffff, 0, 1); 
				vertices[5].SetValue(size.x/2,size.y/2,size.z/2,  1, 1, 1, 0xffffffff, 0, 0); 
				vertices[6].SetValue(-size.x/2,size.y/2,size.z/2, -1, 1, 1, 0xffffffff, 1, 0); 
				vertices[7].SetValue(-size.x/2,-size.y/2,size.z/2, -1,-1, 1, 0xffffffff, 1, 1); 
				vertices[8].SetValue(-size.x/2,size.y/2,size.z/2, -1, 1, 1, 0xffffffff, 0, 1); 
				vertices[9].SetValue(-size.x/2,size.y/2,-size.z/2, -1, 1,-1, 0xffffffff, 1, 1); 
				vertices[10].SetValue(size.x/2,-size.y/2,size.z/2,  1,-1, 1, 0xffffffff, 1, 0); 
				vertices[11].SetValue(size.x/2,-size.y/2,-size.z/2,  1,-1,-1, 0xffffffff, 0, 0); 
				this->indices = new unsigned short[36];
				this->indicesLength = 36;
				unsigned short a[36] = {0,2,1, 0,3,2, 1,5,4, 1,2,5, 4,6,7, 4,5,6, 7,3,0, 7,6,3, 9,5,2, 9,8,5, 0,11,10, 0,10,7};
				for (int i = 0; i < 36; i ++)
					indices[i] = a[i];
			}

		}
	}
}
//------------------------------------------------------------------------