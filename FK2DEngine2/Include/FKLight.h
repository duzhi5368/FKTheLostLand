/**
*	created:		2013-4-23   15:35
*	filename: 		FKLight
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKVector3.h"
#include "FKSColor.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		//------------------------------------------------------------------------
		typedef enum {
			E_LIGHT_TYPE_POINT,
			E_LIGHT_TYPE_DIRECTIONAL
		}E_LIGHT_TYPE;
		//------------------------------------------------------------------------
		class SLight
		{
		public:
			SLight():radius(100.0f),type(E_LIGHT_TYPE_POINT){}
			SLight(E_LIGHT_TYPE type_, SColor ambient_,SColor diffuse_,SColor specular_,FK2DEngine2::math::Vector3 position_,float radius_)
				:type(type_),ambient(ambient_),diffuse(diffuse_),specular(specular_),position(position_),radius(radius_){}
		public:
			SColor ambient;
			SColor diffuse;
			SColor specular;
			FK2DEngine2::math::Vector3 position;
			float radius;
			E_LIGHT_TYPE type;
		};
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------