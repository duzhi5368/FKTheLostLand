/**
*	created:		2013-4-23   22:39
*	filename: 		FKILightSceneNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKISceneNode.h"
#include "FKLight.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S3D
		{
			class ILightSceneNode : public ISceneNode
			{
			public :
				virtual const std::wstring getTypeInfo() const {
					return L"ILightSceneNode";
				}
				ILightSceneNode(const std::wstring nodeName,ISceneNode * parent,
					I3DSceneManager * manager,FK2DEngine2::math::Vector3 position
					,FK2DEngine2::video::SLight light_)
					:ISceneNode(nodeName,parent,manager,position,FK2DEngine2::math::Vector3(0,0,0),FK2DEngine2::math::Vector3(1,1,1)),
					light(light_)
				{
				}
				void setLight(FK2DEngine2::video::SLight light_){
					light = light_;
				}
				FK2DEngine2::video::SLight getLight(){
					return light;
				}
			protected:
				FK2DEngine2::video::SLight light;
			};
		}
	}
}
//------------------------------------------------------------------------