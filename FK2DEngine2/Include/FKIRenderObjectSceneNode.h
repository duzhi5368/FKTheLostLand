/**
*	created:		2013-4-23   22:26
*	filename: 		FKIRenderObjectSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKISceneNode.h"
#include "FKVertex.h"
#include "FKSMaterial.h"
#include "FKITexture.h"
#include "FKIVideoDriver.h"
#include "FKI3DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			//! 所有渲染对象的场景节点基类
			class IRenderObjectSceneNode : public ISceneNode
			{
			public :
				virtual const std::wstring getTypeInfo() const {
					return L"IRenderObjectSceneNode";
				}
				IRenderObjectSceneNode(const std::wstring nodeName,
					ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 rotate_,
					FK2DEngine2::math::Vector3 scale_)
				:ISceneNode(nodeName,parent_,manager_,position_,rotate_,scale_)
				{
						material = FK2DEngine2::video::SMaterial::noneMaterial();
						texture = NULL;
						videoDriver = manager->getVideoDriver();
						vertices = NULL;
						verticesLength = 0;
						indices = NULL;
						indicesLength = 0;
				}
				virtual ~IRenderObjectSceneNode()
				{
					if (vertices != NULL)
					{
						delete [] vertices;
						vertices = NULL;
					}
					if (indices != NULL)
					{
						delete [] indices;
						indices = NULL;
					}
				}
				virtual void beforeRender()
				{
					if (isVisible)
					{
						manager->registerNodeForRendering(this,E_NODE_TYPE_RENDER_SOLID);
						ISceneNode::beforeRender();
					}
				}
				virtual void render(){
					if (videoDriver != NULL)
					{
						// 设置世界矩阵
						videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_WORLD,absoluteTransform);
						// 设置材质
						videoDriver->setMaterial(material);
						// 设置纹理
						videoDriver->setTexture(texture);

						// 渲染对象
						if (vertices != NULL && indices != NULL && verticesLength !=0  && indicesLength >=3)
						{
							videoDriver->drawIndexTriangleList(vertices,verticesLength,indices,indicesLength / 3);
						}
					}
				}

				void setMaterial( const FK2DEngine2::video::SMaterial & material_){
					material = material_;
				}
				FK2DEngine2::video::SMaterial getMaterial(){
					return material;
				}
				void setTexture(FK2DEngine2::video::ITexture * texture_/*,int index*/){
					texture = texture_;
				}
				FK2DEngine2::video::ITexture * getTexture(int index){
					return texture;
				}
				FK2DEngine2::math::Vertex * getVertices(){
					return vertices;
				}
				int getVerticesLength(){
					return verticesLength;
				}
				unsigned short * getIndices(){
					return indices;
				}
				int getIndicesLength(){
					return indicesLength;
				}
			protected:
				FK2DEngine2::video::SMaterial material;
				FK2DEngine2::video::ITexture * texture;
				FK2DEngine2::video::IVideoDriver * videoDriver;
				FK2DEngine2::math::Vertex * vertices;
				int verticesLength;
				unsigned short * indices;
				int indicesLength;
			};
		}
	}
}
//------------------------------------------------------------------------