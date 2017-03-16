/**
*	created:		2013-4-23   22:28
*	filename: 		FKI3DSceneManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIBase.h"
#include "FKQuad.h"
#include "FKIVideoDriver.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			typedef enum {
				E_NODE_TYPE_EMPTY,
				//E_NODE_TYPE_CAMERA,
				E_NODE_TYPE_LIGHT,
				E_NODE_TYPE_RENDER_SOLID,
				//E_NODE_TYPE_RENDER_TRANSPARENT
			}E_NODE_TYPE;

			class ISceneNode ;
			class IRenderObjectSceneNode;
			class ICameraSceneNode;
			class ILightSceneNode;

			//! 3D场景对象管理器
			class I3DSceneManager : public FK2DEngine2::core::IBase
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"I3DSceneManager";
				}
				
				//! 向管理器增加一个空场景节点【通常用来做一些节点的父节点】
				virtual ISceneNode * addEmptySceneNode(const std::wstring & nodeMane,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position) = 0;

				//! 向管理器增加一个摄像机节点并且设置他为活动摄像机【部分摄像机参数可以在Add之后再设置】
				virtual ICameraSceneNode * addCameraSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 relativeEyePos,
					FK2DEngine2::math::Vector3 at,
					FK2DEngine2::math::Vector3 up) = 0;

				//! 向管理器增加一个光照节点
				virtual ILightSceneNode * addLightSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::video::SLight light) = 0;

				//! 向管理器增加一个正方形节点
				virtual IRenderObjectSceneNode * addQuadSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::math::Quad quad) = 0;

				//! 向管理器增加一个立方体节点【大小 = (width,height,depth)】
				virtual IRenderObjectSceneNode * addCubeSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::math::Vector3 size) = 0;

				//! 通过名称获取一个节点指针
				virtual ISceneNode * getNodeByName(const std::wstring & nodeName) = 0;

				//! 释放一个节点指针
				virtual void freeNode(ISceneNode * node) = 0;

				//! 释放全部节点指针
				virtual void freeAllNodes() = 0;

				//! 设置活动摄像机
				virtual void setActiveCamera(ICameraSceneNode * camera) = 0;

				//! 获取活动摄像机
				virtual ICameraSceneNode * getActiveCamera() = 0;

				//! 获取图形渲染器
				virtual FK2DEngine2::video::IVideoDriver * getVideoDriver() = 0;

				//! 开始3D场景渲染
				virtual void begin3DScene() = 0;

				//! 渲染场景
				virtual void drawAll () = 0;

				//! 停止3D场景渲染
				virtual void end3Dscene () = 0;

				//! 注册一个节点，让其进入渲染
				virtual void registerNodeForRendering(ISceneNode * node,E_NODE_TYPE nodeType) = 0;
				
			};
		}
	}
}
//------------------------------------------------------------------------