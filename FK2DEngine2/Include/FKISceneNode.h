/**
*	created:		2013-4-23   22:22
*	filename: 		FKISceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <list>
#include "FKIBase.h"
#include "FKVector3.h"
#include "FKMatrix4.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class I3DSceneManager;

			class ISceneNode : public FK2DEngine2::core::IBase, public FK2DEngine2::core::IObjectInfomation
			{
			public:
				virtual const std::wstring getTypeInfo() const {
					return L"ISceneNode";
				}
				ISceneNode(const std::wstring nodeName,ISceneNode * parent_,I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 rotate_,
					FK2DEngine2::math::Vector3 scale_)
					:FK2DEngine2::core::IObjectInfomation(nodeName),
					parent(parent_),manager(manager_),relativePosition(position_),
					rotate(rotate_),scale(scale_)
				{
					if (parent != NULL)
						parent->addChildNode(this);
					updateAbsoluteTransform();
				}

				virtual ~ISceneNode(){
					removeAllChildNode();
					if (parent != NULL)
						parent->removeChildNode(this);
				}

				virtual void beforeRender(){
					std::list<ISceneNode *>::iterator it; 
					for (it = childrenNodeList.begin(); it != childrenNodeList.end(); it ++)
						(*it)->beforeRender();
				}
				
				virtual void render() = 0;

				virtual void afterRender(){
					updateAbsoluteTransform();
					std::list<ISceneNode *>::iterator it;
					for (it = childrenNodeList.begin(); it != childrenNodeList.end(); it ++)
						(*it)->afterRender();
				}

				virtual void addChildNode(ISceneNode * node){
					if (node != NULL)
					{
						if (node->parent != NULL)
							node->parent->removeChildNode(node);
						childrenNodeList.push_back(node);
					}
				}
				virtual void removeChildNode(ISceneNode * node){
					std::list<ISceneNode *>::iterator it;
					for (it = childrenNodeList.begin(); it != childrenNodeList.end(); it ++)
						if ((*it) == node)
						{
							delete node;
							childrenNodeList.erase(it);
							break;
						}
				}
				virtual void removeAllChildNode(){
					std::list<ISceneNode *>::iterator it;
					for (it = childrenNodeList.begin(); it != childrenNodeList.end(); it ++)
					{
						delete (*it);
					}
					childrenNodeList.clear();
				}
				virtual ISceneNode * getChildNode( unsigned int index){
					if (index < 0 || index >= childrenNodeList.size())
						return NULL;
					std::list<ISceneNode *>::iterator it = childrenNodeList.begin();
					while (index > 0)
					{
						it++;
						index--;
					}
					return (*it);
				}
				std::list<ISceneNode *> & getChildrenNodeList(){
					return childrenNodeList;
				}
				void setRelativePostion(FK2DEngine2::math::Vector3 position){
					relativePosition = position;
				}
				FK2DEngine2::math::Vector3 getRelativePostion(){
					return relativePosition;
				}
				FK2DEngine2::math::Vector3 getAbsolutePosition(){
					return absolutePosition;
				}
				FK2DEngine2::math::Matrix4 getRelativeTransform(){
					FK2DEngine2::math::Matrix4 mat;
					mat.MakeIdentity();
					FK2DEngine2::math::Matrix4 m4;
					m4.MakeScaling(scale.x,scale.y,scale.z);
					mat *= m4;
					m4.MakeRotation(rotate);
					mat *= m4;
					m4.MakeTranslation(relativePosition.x,relativePosition.y,relativePosition.z);
					mat *= m4;
					return mat;
				}
				FK2DEngine2::math::Matrix4 getAbsoluteTransform(){
					return absoluteTransform;
				}
				void setRotate(FK2DEngine2::math::Vector3 rotate_){
					rotate = rotate_;
				}
				FK2DEngine2::math::Vector3 getRotate(){
					return rotate;
				}
				void setScale(FK2DEngine2::math::Vector3 scale_){
					scale = scale_;
				}
				FK2DEngine2::math::Vector3 getScale(){
					return scale;
				}
				void setParent(ISceneNode * parent_){
					parent = parent_;
				}
				ISceneNode * getParent(){
					return parent;
				}
				void setVisible(bool visible){
					isVisible = visible;
				}
				bool getVisible(){
					return isVisible;
				}
			protected:
				void updateAbsoluteTransform(){
					if (parent == NULL)
					{
						absoluteTransform = getRelativeTransform();
						absolutePosition = relativePosition;
					}
					else 
					{
						absoluteTransform = parent->getAbsoluteTransform() * getRelativeTransform();
						absolutePosition = parent->absolutePosition + relativePosition;
					}
				}
			protected:
				std::list<ISceneNode *> childrenNodeList;
				ISceneNode * parent;
				I3DSceneManager * manager;
				bool isVisible;
				FK2DEngine2::math::Matrix4 absoluteTransform;
				FK2DEngine2::math::Vector3 absolutePosition;
				FK2DEngine2::math::Vector3 relativePosition;
				FK2DEngine2::math::Vector3 rotate;
				FK2DEngine2::math::Vector3 scale;
			};
		}
	}
}
//------------------------------------------------------------------------