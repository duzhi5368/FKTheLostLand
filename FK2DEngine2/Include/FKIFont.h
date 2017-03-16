/**
*	created:		2013-4-23   15:44
*	filename: 		FKIFont
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
	namespace video
	{
		class IFont : public FK2DEngine2::core::IResource
		{
		public:
			virtual const std::wstring getTypeInfo() const {
				return L"IFont";
			}
			IFont(const std::wstring & resourceName) : FK2DEngine2::core::IResource(resourceName){}
			virtual int getHeight() = 0;
			virtual int getWIdth() = 0;
			virtual int getWeight() = 0;
			virtual unsigned long getHandle() = 0;
		};
	}
}
//------------------------------------------------------------------------