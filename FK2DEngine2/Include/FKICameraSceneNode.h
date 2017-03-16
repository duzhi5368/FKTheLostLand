/**
*	created:		2013-4-23   22:41
*	filename: 		FKICameraSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKISceneNode.h"
#include "FKVector3.h"
#include "FKMatrix4.h"
#include "FKIVideoDriver.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			// 摄像机场景节点
			class ICameraSceneNode : public ISceneNode
			{
			public :
				virtual const std::wstring getTypeInfo() const {
					return L"ICameraSceneNode";
				}
				ICameraSceneNode(const std::wstring nodeName,ISceneNode * parent,
					I3DSceneManager * manager_,
					FK2DEngine2::math::Vector3 position_,
					FK2DEngine2::math::Vector3 at)
					:ISceneNode(nodeName,parent,manager_,position_,FK2DEngine2::math::Vector3(0,0,0),FK2DEngine2::math::Vector3(1,1,1))
				{
					viewAt = at;
					viewUp = FK2DEngine2::math::Vector3(0,1,0);
					fovy = M_PI / 2.5f; 
					aspect = 4.0f / 3.0f;
					zn = 1.0f;
					zf = 3000.0f;
					calulateViewMatrix();
					calulateProjctionMatrix();
				}
				void setRelativeViewEye(FK2DEngine2::math::Vector3 eye){
					setRelativePostion(eye);
					updateAbsoluteTransform();
					calulateViewMatrix();
				}
				FK2DEngine2::math::Vector3 getRelativeViewEye(){
					return getRelativePostion();
				}
				void setViewAt(FK2DEngine2::math::Vector3 at){
					viewAt = at;
					calulateViewMatrix();
				}
				FK2DEngine2::math::Vector3 getViewAt(){
					return viewAt;
				}
				void setViewUp(FK2DEngine2::math::Vector3 up){
					viewUp = up;
					calulateViewMatrix();
				}
				FK2DEngine2::math::Vector3 getViewUp(){
					return viewUp;
				}
				void setProjection(float fovy,float aspect,float zn,float zf){
					this ->fovy = fovy; this ->aspect = aspect; this->zn = zn; this ->zf = zf;
					calulateProjctionMatrix();
				}
				float getFovy(){
					return fovy;
				}
				float getAspect(){
					return aspect;
				}
				float getNearPlane(){
					return zn;
				}
				float getFarPlane(){
					return zf;
				}
			protected:
				void calulateViewMatrix(){
					viewMatrix.MakeLookAtLeftHand(getAbsolutePosition(),viewAt,viewUp);
				}
				void calulateProjctionMatrix(){
					projectionMatrix.MakePerspectiveFovLeftHand(fovy,aspect,zn,zf);
				}
			protected:
				FK2DEngine2::math::Vector3	viewAt;
				FK2DEngine2::math::Vector3	viewUp;
				float fovy,aspect,zn,zf;
				FK2DEngine2::math::Matrix4 viewMatrix;
				FK2DEngine2::math::Matrix4 projectionMatrix;
			};
		}
	}
}
//------------------------------------------------------------------------