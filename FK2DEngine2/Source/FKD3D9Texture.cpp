/**
*	created:		2013-4-23   19:13
*	filename: 		FKD3D9Texture
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

#include "../Include/FKLogger.h"
#include "../Include/FKD3D9Texture.h"
#include "../Include/FKStringConvert.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video 
	{
		CDirect3D9Texture::CDirect3D9Texture(const std::wstring & texName)
			:ITexture(texName)
		{
			lpTexture = 0;
			isRenderTarget = false;
		}

		CDirect3D9Texture::~CDirect3D9Texture()
		{
			releaseTexture();
		}

		ITexture::HTEXTURE CDirect3D9Texture::getHandle()
		{
			return (HTEXTURE)lpTexture;
		}

		E_VIDEODRIVERTYPE CDirect3D9Texture::getDriverType()
		{
			return E_VIDEODRIVERTYPE_D3D;
		}

		void CDirect3D9Texture::releaseTexture()
		{
			if (lpTexture != 0)
			{
				HRESULT hr = lpTexture->Release();
				if (FAILED(hr))
				{
					LogError( L"纹理释放失败 : %s", getObjectName().c_str() );
				}
				else 
				{
					LogInfo( L"纹理释放 : %s", getObjectName().c_str() );
				}
				lpTexture = 0;
			}
		}
		bool CDirect3D9Texture::createTexture(int width,int height,LPDIRECT3DDEVICE9 lpDevice)
		{
			releaseTexture();
			if (FAILED (D3DXCreateTexture(lpDevice,width,height,D3DX_DEFAULT,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&lpTexture)))
			{
				LogError( L"创建纹理失败 : 宽 = %d  高 = %d", width, height );
				return false;
			}
			isRenderTarget = true;
			return true;
		}
		bool CDirect3D9Texture::loadTexture(const std::wstring &fileName,LPDIRECT3DDEVICE9 lpDevice)
		{
			releaseTexture();

			HRESULT hr = S_FALSE;
			hr = D3DXCreateTextureFromFile(lpDevice,fileName.c_str(),&lpTexture);
			if ( hr != S_OK )
			{
				LogError( L"加载纹理失败 : %s %s", fileName.c_str(), DXGetErrorString(hr) );
				return false;
			}
			return true;
		}

		unsigned int CDirect3D9Texture::getTextureWidth() const
		{
			if (lpTexture == 0)
				return 0;
			D3DSURFACE_DESC surfaceDescribe;
			if (FAILED(lpTexture->GetLevelDesc(0,&surfaceDescribe)))
				return 0;
			return surfaceDescribe.Width;
		};

		unsigned int CDirect3D9Texture::getTextureHeight() const 
		{
			if (lpTexture == 0)
				return 0;
			D3DSURFACE_DESC surfaceDescribe;
			if (FAILED(lpTexture->GetLevelDesc(0,&surfaceDescribe)))
				return 0;
			return surfaceDescribe.Height;
		}
		
		IDirect3DSurface9 * CDirect3D9Texture::getRenderTarget() const
		{
			if (isRenderTarget == false)
				return NULL;
			IDirect3DSurface9 * renderTarget = 0;
			if (lpTexture != 0)
			{
				if (FAILED(lpTexture->GetSurfaceLevel(0,&renderTarget)))
					return 0;
			}
			if (renderTarget != 0)
				renderTarget->Release();
			return renderTarget;
		}
	}
}
//------------------------------------------------------------------------