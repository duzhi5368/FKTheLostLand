/**
*	created:		2013-4-23   17:27
*	filename: 		FKD3D9VideoDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <list>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dX9Core.h>
#include "FKIVideoDriver.h"
#include "UI/Renderers/FKDirectX9.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		#define FK2DENGINE2_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

		#define TEXT_BUFFER_LENGTH 2048

		class CDirect3D9Font ;
		
		class CDirect3D9VideoDriver : public IVideoDriver
		{
		public:
			virtual const std::wstring getTypeInfo() const {
				return L"CDirect3D9VideoDriver";
			}
			virtual ~CDirect3D9VideoDriver();
			CDirect3D9VideoDriver();

			virtual bool initDriver( int width,int height,int zdepth,HWND hwnd,
									bool fullscreen = false,
									bool zbuffer = false,
									bool alphatesting = false,
									bool alphablend = true,
									bool lighting = false,
									bool immediate = true);

			virtual bool shutDriver();

			virtual int reset(int width,int height,int zdepth,HWND hwnd,
								bool fullscreen = false,
								bool zbuffer = false,
								bool alphatesting = false,
								bool alphablend = true,
								bool lighting = false,
								bool immediate = true);


			virtual int setTransform(E_TRANSFORM_MATRIX tm,FK2DEngine2::math::Matrix4 & m4);

			virtual int setViewport(unsigned int x,unsigned int y,unsigned int width,unsigned int height);

			virtual int setMaterial(const SMaterial & mat);

			virtual int addLight(const SLight & light);

			virtual void deleteAllLights();

			virtual int setLight(const SLight & light,int index);

			virtual int setTexture(ITexture * texture) ;

			virtual void ClearCurTexture();

			virtual bool CurHasTexture();

			virtual void SetUIVideoDriver( DirectX9* p_pUIVideoDriver );

			virtual int setVideodriverState(E_VIDEODRIVER_STATE_TYPE state,bool enable);

			virtual int enableLight(int index,bool enable) ;

			virtual int setRenderTarget(ITexture * renderTarget,unsigned long flag = E_CLEAR_NONE,SColor color = SColor::black());

			virtual ITexture * getRenderTarget();

			virtual int beginScene(SColor color,unsigned long flag) ;

			virtual int endScene() ;

			virtual int drawPixel(FK2DEngine2::math::Vertex & pixel) ;

			virtual int drawLine(FK2DEngine2::math::Line3D & line) ;
			
			virtual int drawTriangle(FK2DEngine2::math::Triangle & triangle) ;

			virtual int drawQuad(FK2DEngine2::math::Quad & quad) ;

			virtual int drawTriangleList(FK2DEngine2::math::Triangle * triangleList,int count);

			virtual int drawTriangleFan(FK2DEngine2::math::Vertex * triangleFanList,int vertexCount);

			virtual int drawTriangleStrip(FK2DEngine2::math::Vertex * triangleStripList,int vertexCount);

			virtual int drawIndexTriangleList(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount);

			virtual int drawIndexTriangleFan(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount);

			virtual int drawIndexTriangleStrip(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount);

			virtual int drawText(IFont * font,float x,float y,SColor color,const char * format,...);

			virtual int drawTextInRect(IFont * font,float centerX,float centerY,float width,float height,SColor color, const char * format,...);

			virtual ITexture * createTexture(const std::wstring & texName,int width,int height) ;

			virtual ITexture * loadTexture(const std::wstring & texName,const std::wstring & fileName) ;

			virtual bool freeTexture(const std::wstring & texName);

			virtual bool freeTexture(ITexture * texture);
			
			virtual IFont * loadFont(const std::wstring & resourceName,int height,int width,int weight,const std::wstring & fontStyleName);

			virtual bool freeFont(const std::wstring & resourceName);

			virtual bool freeFont(IFont * font);
		public:
			LPDIRECT3DDEVICE9 getHandle(){
				return lpd3ddevice;
			}
		protected:
			void setMatrices();
			void onLostDevice();
			void onResetDevice();
		private:
			struct DeviceParam
			{
				int width;
				int height;
				int zdepth;
				HWND hwnd;
				bool fullscreen ;
				bool zbuffer ;
				bool alphatesting ;
				bool alphablend;
				bool lighting ;
				bool immediate ;
			};
		private:
			LPDIRECT3D9					lpd3d;
			LPDIRECT3DDEVICE9			lpd3ddevice;
			D3DPRESENT_PARAMETERS		d3dppfs,d3dppwin;
			D3DDISPLAYMODE				d3ddm;
			DeviceParam					deviceparam;
			bool						devicelost;
			ITexture *					currentTexture;
			FK2DEngine2::math::Matrix4	matrices[E_TRAMSFORM_MATRIX_COUNT];
			std::list<CDirect3D9Font *> fontList;
			ITexture *					currentRenderTarget;
			IDirect3DSurface9 *			screen;
			int							lastLightIndex;
			DirectX9*					UIVideoDriver;
		};
	}
}
//------------------------------------------------------------------------