/**
*	created:		2013-4-23   22:54
*	filename: 		FK3DSceneManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <list>

#include "FKIVideoDriver.h"
#include "FKI3DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class C3DSceneManager : public I3DSceneManager
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"C3DSceneManager";
				}
				
				typedef std::list<ISceneNode *> TNodeList;
				typedef std::list<ISceneNode *>::iterator TNodeListIterator;
				
				C3DSceneManager(FK2DEngine2::video::IVideoDriver * videoDriver);
				virtual ~C3DSceneManager();

				virtual ISceneNode * addEmptySceneNode(const std::wstring & nodeMane,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position);

				virtual ICameraSceneNode * addCameraSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 relativeEyePos,
					FK2DEngine2::math::Vector3 at,
					FK2DEngine2::math::Vector3 up);

				virtual ILightSceneNode * addLightSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::video::SLight light);

				virtual IRenderObjectSceneNode * addQuadSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::math::Quad quad);
				
				virtual IRenderObjectSceneNode * addCubeSceneNode(const std::wstring & nodeName,ISceneNode * parent,
					FK2DEngine2::math::Vector3 position,
					FK2DEngine2::math::Vector3 size);

				virtual ISceneNode * getNodeByName(const std::wstring & nodeName);

				virtual void freeNode(ISceneNode * node);

				virtual void freeAllNodes();

				virtual void setActiveCamera(ICameraSceneNode * camera);

				virtual ICameraSceneNode * getActiveCamera();

				virtual FK2DEngine2::video::IVideoDriver * getVideoDriver();

				virtual void begin3DScene();

				virtual void drawAll ();

				virtual void end3Dscene ();

				virtual void registerNodeForRendering(ISceneNode * node,E_NODE_TYPE nodeType);

			protected:
				ISceneNode * getNodeByName(TNodeList & nodeList,const std::wstring &nodeName);
				void beforeRender();
				void renderAll();
				void afterRender();
			protected:
				TNodeList nodeForest;
				TNodeList renderSolidNodeList;
				TNodeList lightNodeList;
				ICameraSceneNode * activeCamera;
				FK2DEngine2::video::IVideoDriver * videoDriver;
			};
		}
	}
}
//------------------------------------------------------------------------