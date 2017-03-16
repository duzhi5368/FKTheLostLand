/**
*	created:		2013-4-23   17:33
*	filename: 		FKD3D9Texture
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "FKITexture.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		class CDirect3D9VideoDriver;
		class CDirect3D9Texture : public ITexture 
		{
			friend CDirect3D9VideoDriver;
		public :
			virtual ~CDirect3D9Texture() ;
			virtual const std::wstring getTypeInfo() const {
				return L"CDirect3D9Texture";
			}
			virtual HTEXTURE getHandle();
			virtual E_VIDEODRIVERTYPE getDriverType();
			virtual unsigned int getTextureWidth() const;
			virtual unsigned int getTextureHeight() const ;
			IDirect3DSurface9 * getRenderTarget() const;
		protected:
			CDirect3D9Texture(const std::wstring & texName);
			bool createTexture(int width,int height,LPDIRECT3DDEVICE9 lpDevice);
			bool loadTexture(const std::wstring & fileName,LPDIRECT3DDEVICE9 lpDevice);
			void releaseTexture();
		private :
			LPDIRECT3DTEXTURE9 lpTexture;
			bool isRenderTarget;
		};
	}
}
//------------------------------------------------------------------------