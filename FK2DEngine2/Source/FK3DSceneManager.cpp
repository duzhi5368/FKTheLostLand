/**
*	created:		2013-4-23   22:56
*	filename: 		FK3DSceneManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FK3DSceneManager.h"
#include "../Include/FKEmptySceneNode.h"
#include "../Include/FKQuadSceneNode.h"
#include "../Include/FKCubeSceneNode.h"
#include "../Include/FKCameraSceneNode.h"
#include "../Include/FKLightSceneNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			C3DSceneManager::C3DSceneManager(FK2DEngine2::video::IVideoDriver * videoDriver_)
			{
				videoDriver = videoDriver_;
				nodeForest.clear();
				renderSolidNodeList.clear();
				lightNodeList.clear();
				activeCamera = NULL; // 这里要不要默认创建一个默认摄像机呢。。。
			}
			C3DSceneManager::~C3DSceneManager()
			{
				freeAllNodes();
			}

			ISceneNode * C3DSceneManager::addEmptySceneNode(const std::wstring & nodeMame,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position)
			{
				CEmptySceneNode * node = new CEmptySceneNode(nodeMame,parent,this,position);
				if (parent == NULL)
				{
					nodeForest.push_back(node);
				}
				return node;
			}

			ICameraSceneNode * C3DSceneManager::addCameraSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 relativeEyePos,
					FK2DEngine2::math::Vector3 at,
					FK2DEngine2::math::Vector3 up)
			{
				CCameraSceneNode * node = new CCameraSceneNode(nodeName,parent,this,relativeEyePos,at);
				node->setViewUp(up);
				if (parent == NULL)
				{
					nodeForest.push_back(node);
				}
				setActiveCamera(node);
				return node;
			}

			ILightSceneNode * C3DSceneManager::addLightSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::video::SLight light)
			{
				CLightSceneNode * node = new CLightSceneNode(nodeName,parent,this,position,light);
				if (parent == NULL)
				{
					nodeForest.push_back(node);
				}
				return node;
			}

			IRenderObjectSceneNode * C3DSceneManager::addQuadSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::math::Quad quad)
			{
				CQuadSceneNode * node = new CQuadSceneNode(nodeName,parent,this,position,FK2DEngine2::math::Vector3(0,0,0),FK2DEngine2::math::Vector3(1,1,1),quad);
				if (parent == NULL)
				{
					nodeForest.push_back(node);
				}
				return node;
			}

			IRenderObjectSceneNode * C3DSceneManager::addCubeSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::math::Vector3 size)
			{
				CCubeSceneNode * node = new CCubeSceneNode(nodeName,parent,this,size,position,FK2DEngine2::math::Vector3(0,0,0),FK2DEngine2::math::Vector3(1,1,1));
				if (parent == NULL)
				{
					nodeForest.push_back(node);
				}
				return node;
			}

			ISceneNode * C3DSceneManager::getNodeByName(const std::wstring & nodeName)
			{
				return getNodeByName(nodeForest,nodeName);
			}

			ISceneNode * C3DSceneManager::getNodeByName(C3DSceneManager::TNodeList & nodeList,const std::wstring &nodeName)
			{
				C3DSceneManager::TNodeListIterator it;
				for (it = nodeList.begin(); it != nodeList.end() ; it ++)
				{
					if ((*it) ->getObjectName() == nodeName)
						return (*it);
					ISceneNode * node = getNodeByName( (*it) ->getChildrenNodeList(),nodeName);
					if (node != NULL)
						return node;
				}
				return NULL;
			}

			void C3DSceneManager::freeNode(ISceneNode * node)
			{
				if (node != NULL)
				{
					if (node->getParent() == NULL)
					{
						C3DSceneManager::TNodeListIterator it;
						for (it = nodeForest.begin(); it != nodeForest.end(); it++)
							if ((*it) == node)
							{
								nodeForest.erase(it);
								break;
							}
					}
					// 在节点的析构中，会释放全部子节点
					delete node; 
				}
			}

			void C3DSceneManager::freeAllNodes()
			{
				C3DSceneManager::TNodeListIterator it;
				for (it = nodeForest.begin(); it != nodeForest.end() ; it ++)
				{
					delete (*it);
				}
				nodeForest.clear();
			}

			void C3DSceneManager::setActiveCamera(ICameraSceneNode * camera)
			{
				activeCamera = camera;
			}

			ICameraSceneNode * C3DSceneManager::getActiveCamera()
			{
				return activeCamera;
			}

			FK2DEngine2::video::IVideoDriver * C3DSceneManager::getVideoDriver()
			{
				return videoDriver;
			}

			void C3DSceneManager::begin3DScene()
			{
				FK2DEngine2::math::Matrix4 m4;
				m4.MakeIdentity();
				videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_WORLD,m4);
				if (activeCamera == NULL)
				{
					videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_VIEW,m4);
					videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_PROJECTION,m4);
				}
				else 
				{
					activeCamera->render();
				}
				videoDriver->setVideodriverState(FK2DEngine2::video::E_VIDEODRIVER_STATE_LIGHTING,true);
				videoDriver->setVideodriverState(FK2DEngine2::video::E_VIDEODRIVER_STATE_ALPHABLENDING,false);
			}

			void C3DSceneManager::drawAll()
			{
				beforeRender();
				renderAll();
				afterRender();
			}

			void C3DSceneManager::beforeRender()
			{
				C3DSceneManager::TNodeListIterator it;
				for (it = nodeForest.begin(); it != nodeForest.end(); it ++)
					(*it)->beforeRender();
			}

			void C3DSceneManager::renderAll()
			{
				// 光照
				videoDriver->deleteAllLights();

				C3DSceneManager::TNodeListIterator it;
				for (it = lightNodeList.begin(); it != lightNodeList.end(); it ++)
					(*it)->render();

				lightNodeList.clear();

				// 渲染对象
				for (it = renderSolidNodeList.begin(); it != renderSolidNodeList.end(); it ++)
					(*it)->render();

				renderSolidNodeList.clear();

			}
			void C3DSceneManager::afterRender()
			{
				C3DSceneManager::TNodeListIterator it;
				for (it = nodeForest.begin(); it != nodeForest.end(); it ++)
					(*it)->afterRender();
			}

			void C3DSceneManager::end3Dscene ()
			{
			}

			void C3DSceneManager::registerNodeForRendering(ISceneNode * node,E_NODE_TYPE nodeType)
			{
				switch(nodeType)
				{
				case E_NODE_TYPE_LIGHT:
					lightNodeList.push_back(node);
					break;
				case E_NODE_TYPE_RENDER_SOLID:
					renderSolidNodeList.push_back(node);
					break;
				}
			}
		}
	}
}
//------------------------------------------------------------------------