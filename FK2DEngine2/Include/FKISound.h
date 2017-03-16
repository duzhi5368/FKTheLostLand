/**
*	created:		2013-4-23   21:13
*	filename: 		FKISound
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIResource.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace audio
	{
		class ISound : public FK2DEngine2::core::IResource
		{
		public :
			typedef unsigned long HSOUND;
			virtual const std::wstring getTypeInfo() const {
				return L"ISound";
			}
			virtual ~ISound(){}
			ISound(const std::wstring & soundName) :FK2DEngine2::core::IResource(soundName){}

			virtual HSOUND getHandle() = 0;
		};
	}
}
//------------------------------------------------------------------------