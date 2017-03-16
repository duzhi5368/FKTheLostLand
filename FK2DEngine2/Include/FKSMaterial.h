/**
*	created:		2013-4-23   15:34
*	filename: 		FKSMaterial
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKSColor.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		class SMaterial
		{
		public:
			SMaterial(){}
			SMaterial(SColor diffuse_,SColor ambient_,SColor specular_,SColor emissive_,float power_)
				:diffuse(diffuse_),ambient(ambient_),specular(specular_),emissive(emissive_),power(power_){}
			static const SMaterial & whiteMaterial(){
				static SMaterial m(SColor::white(),SColor::white(),SColor::white(),SColor::black(),2.0f);
				return m;
			}
			static const SMaterial & redMaterial(){
				static SMaterial m(SColor::red(),SColor::red(), SColor::red(),SColor::black(),2.0f);
				return m;
			}
			static const SMaterial & greenMaterial(){
				static SMaterial m(SColor::green(),SColor::green(),SColor::green(),SColor::black(),2.0f);
				return m;
			}
			static const SMaterial & blueMaterial(){
				static SMaterial m(SColor::blue(),SColor::blue(),SColor::blue(),SColor::black(),2.0f);
				return m;
			}
			static const SMaterial & yellowMaterial(){
				static SMaterial m(SColor::yellow(),SColor::yellow(),SColor::yellow(),SColor::black(),2.0f);
				return m;
			}
			static const SMaterial & noneMaterial(){
				static SMaterial m(SColor::black(),SColor::black(),SColor::black(),SColor::white(),2.0f);
				return m;
			}
		public:
			SColor diffuse;
			SColor ambient;
			SColor specular;
			SColor emissive;
			float power;
		};
	}
}
//------------------------------------------------------------------------