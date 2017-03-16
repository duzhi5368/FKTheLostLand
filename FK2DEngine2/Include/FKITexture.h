/**
*	created:		2013-4-23   15:45
*	filename: 		FKITexture
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIResource.h"
#include "FKEVideoDriverType.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		class ITexture : public FK2DEngine2::core::IResource
		{
		public :
			typedef unsigned int HTEXTURE;
			virtual ~ITexture(){}
			ITexture(const std::wstring & textureName):FK2DEngine2::core::IResource(textureName){}
			virtual const std::wstring getTypeInfo() const {
				return L"ITexture";
			}
			//! 获取纹理句柄
			virtual HTEXTURE getHandle() = 0;
			//! 获取渲染器类型
			virtual E_VIDEODRIVERTYPE getDriverType() = 0;
			//! \return 获取纹理宽度
			virtual unsigned int getTextureWidth() const = 0;
			//! \return 获取纹理高度
			virtual unsigned int getTextureHeight() const = 0;
		};
	}
}
//------------------------------------------------------------------------