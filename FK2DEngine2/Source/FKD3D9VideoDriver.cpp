/**
*	created:		2013-4-23   17:32
*	filename: 		FKD3D9VideoDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include <d3d9.h>
#include <DxErr.h>
#include "../Include/FKD3D9VideoDriver.h"
#include "../Include/FKD3D9Font.h"
#include "../Include/FKD3D9Texture.h"
#include "../Include/FKStringConvert.h"
//------------------------------------------------------------------------
#pragma warning( disable:4244 )
#pragma warning( disable:4996 )
//------------------------------------------------------------------------
using namespace FK2DEngine2::core;
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		CDirect3D9VideoDriver::~CDirect3D9VideoDriver()
		{}

		CDirect3D9VideoDriver::CDirect3D9VideoDriver()
		{
			lpd3d = NULL;
			lpd3ddevice = NULL;
			currentTexture = NULL;
			for (int i = 0; i < E_TRAMSFORM_MATRIX_COUNT; i ++)
				matrices[i].MakeIdentity();
			fontList.clear();
			currentRenderTarget = NULL;
			screen = NULL;
			lastLightIndex = -1;
			UIVideoDriver = NULL;
		}

		bool CDirect3D9VideoDriver::initDriver( int width,int height,int zdepth,HWND hwnd,
									bool fullscreen ,
									bool zbuffer ,
									bool alphatesting ,
									bool alphablend ,
									bool lighting ,
									bool immediate )
		{
			devicelost = false;
        
			deviceparam.width = width;
			deviceparam.height = height;
			deviceparam.zdepth = zdepth;
			deviceparam.hwnd = hwnd;
			deviceparam.fullscreen = fullscreen;
			deviceparam.zbuffer = zbuffer;
			deviceparam.alphatesting = alphatesting;
			deviceparam.alphablend = alphablend;
			deviceparam.lighting = lighting;
			deviceparam.immediate = immediate;

			D3DPRESENT_PARAMETERS * d3dp = NULL;
			lpd3d = Direct3DCreate9(D3D_SDK_VERSION);
			if (lpd3d == NULL) 
			{
				LogFatal( L"无法创建D3D对象");
				throw FK2DEngine2::core::CException(L"无法加载Direct3D9 \n");
			}
			
			if (FAILED (lpd3d ->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
			{
				LogFatal( L"无法获取视频Adapter信息");
				throw FK2DEngine2::core::CException(L"无法获取视频Adapter信息 \n");
			}
			
			memset(&d3dppwin,0,sizeof(d3dppwin));
			d3dppwin.Windowed = TRUE;
			d3dppwin.BackBufferWidth = width;
			d3dppwin.BackBufferHeight = height;
			d3dppwin.BackBufferFormat = d3ddm.Format; 
			d3dppwin.BackBufferCount = 1;
			d3dppwin.hDeviceWindow = hwnd;
			d3dppwin.SwapEffect       = D3DSWAPEFFECT_FLIP;
			if (immediate)
				d3dppwin.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			else 
				d3dppwin.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			if (zbuffer)
			{
				d3dppwin.EnableAutoDepthStencil = TRUE;
				d3dppwin.AutoDepthStencilFormat = D3DFMT_D16;
			}
			
			memset(&d3dppfs,0,sizeof(d3dppfs));
			d3dppfs.Windowed = FALSE;
			d3dppfs.BackBufferWidth = width;
			d3dppfs.BackBufferHeight = height;
			d3dppfs.BackBufferFormat = d3ddm.Format; 
			d3dppfs.BackBufferCount = 1;
			d3dppfs.hDeviceWindow = hwnd;
			d3dppfs.SwapEffect       = D3DSWAPEFFECT_FLIP;
			d3dppfs.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			if (immediate)
				d3dppfs.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			else 
				d3dppfs.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			if (zbuffer)
			{
				d3dppfs.EnableAutoDepthStencil = TRUE;
				d3dppfs.AutoDepthStencilFormat = D3DFMT_D16;
			}

			if (fullscreen) 
			{
				d3dp = & d3dppfs;
			}
			else 
			{
				d3dp = & d3dppwin;
			}

			if (FAILED (lpd3d ->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,d3dp,&lpd3ddevice)))
			{
				lpd3d->Release();
				LogFatal( L"无法创建D3D设备对象");
				throw FK2DEngine2::core::CException(L"无法创建D3D设备对象\n");
			}
			
			lpd3ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			if (zbuffer)
			{
				lpd3ddevice ->SetRenderState(D3DRS_ZENABLE, TRUE);
				lpd3ddevice ->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
			}

			if (alphatesting)
			{
				lpd3ddevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000000);
				lpd3ddevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
				lpd3ddevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			}

			if (alphablend)
			{
				lpd3ddevice ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
				lpd3ddevice ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
				lpd3ddevice ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
				lpd3ddevice ->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			}

			if (lighting)
			{
				lpd3ddevice->SetRenderState(D3DRS_LIGHTING, TRUE ) ;
			}
			else 
			{
				lpd3ddevice->SetRenderState(D3DRS_LIGHTING, FALSE ) ;
			}

			lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
			lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
			lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP,D3DTOP_MODULATE);
			
			if (FAILED(lpd3ddevice->GetRenderTarget(0,&screen)))
				return 0;
			screen->Release();

			setMatrices();

			LogInfo( L"D3D设备初始化成功！");
			return true;
			
		}

		bool CDirect3D9VideoDriver::shutDriver()
		{
			if (currentRenderTarget != NULL)
			{
				currentRenderTarget->decRef();
				currentRenderTarget = NULL;
			}
			if (currentTexture != NULL)
			{
				currentTexture->decRef();
				currentTexture = NULL;
			}
			if (lpd3ddevice)
			{
				lpd3ddevice ->Release();
				lpd3ddevice = NULL;
			}
			if (lpd3d)
			{
				lpd3d ->Release();
				lpd3d = NULL;
			}
			LogInfo( L"D3D设备关闭完成！");
			return true;
		}

		int CDirect3D9VideoDriver::reset(int width,int height,int zdepth,HWND hwnd,
								bool fullscreen ,
								bool zbuffer ,
								bool alphatesting ,
								bool alphablend,
								bool lighting,
								bool immediate)
		{
			devicelost = false;
        
			deviceparam.width = width;
			deviceparam.height = height;
			deviceparam.zdepth = zdepth;
			deviceparam.hwnd = hwnd;
			deviceparam.fullscreen = fullscreen;
			deviceparam.zbuffer = zbuffer;
			deviceparam.alphatesting = alphatesting;
			deviceparam.alphablend = alphablend;
			deviceparam.lighting = lighting;
			deviceparam.immediate = immediate;
			
			D3DPRESENT_PARAMETERS * d3dp = NULL;

			if (FAILED (lpd3d ->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
			{
				LogError( L"无法获取视频Adapter信息！");
				return 0;
			}
			memset(&d3dppwin,0,sizeof(d3dppwin));
			d3dppwin.Windowed = TRUE;
			d3dppwin.BackBufferWidth = width;
			d3dppwin.BackBufferHeight = height;
			d3dppwin.BackBufferFormat = d3ddm.Format; 
			d3dppwin.BackBufferCount = 1;
			d3dppwin.hDeviceWindow = hwnd;
			d3dppwin.SwapEffect       = D3DSWAPEFFECT_FLIP;
			if (immediate)
				d3dppwin.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			else 
				d3dppwin.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			if (zbuffer)
			{
				d3dppwin.EnableAutoDepthStencil = TRUE;
				d3dppwin.AutoDepthStencilFormat = D3DFMT_D16;
			}
			
			memset(&d3dppfs,0,sizeof(d3dppfs));
			d3dppfs.Windowed = FALSE;
			d3dppfs.BackBufferWidth = width;
			d3dppfs.BackBufferHeight = height;
			d3dppfs.BackBufferFormat = d3ddm.Format; 
			d3dppfs.BackBufferCount = 1;
			d3dppfs.hDeviceWindow = hwnd;
			d3dppfs.SwapEffect       = D3DSWAPEFFECT_FLIP;
			d3dppfs.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			if (immediate)
				d3dppfs.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			else 
				d3dppfs.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			if (zbuffer)
			{
				d3dppfs.EnableAutoDepthStencil = TRUE;
				d3dppfs.AutoDepthStencilFormat = D3DFMT_D16;
			}

			if (fullscreen) 
			{
				d3dp = & d3dppfs;
			}
			else 
			{
				d3dp = & d3dppwin;
			}

			if (FAILED(lpd3ddevice->Reset(d3dp)))
			{
				LogError( L"无法重置D3D设备！");
				return 0;
			}
			lpd3ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			if (zbuffer)
			{
				lpd3ddevice ->SetRenderState(D3DRS_ZENABLE, TRUE);
				lpd3ddevice ->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
			}

			if (alphatesting)
			{
				lpd3ddevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000000);
				lpd3ddevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
				lpd3ddevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			}
			
			if (alphablend)
			{
				if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE)))
					return 0;
				if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA)))
					return 0;
				if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA)))
					return 0;
				if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD)))
					return 0;
			}

			if (lighting)
			{
				lpd3ddevice->SetRenderState(D3DRS_LIGHTING, TRUE ) ;
			}
			else 
			{
				lpd3ddevice->SetRenderState(D3DRS_LIGHTING, FALSE ) ;
			}

			lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
			lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
			lpd3ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP,D3DTOP_MODULATE);
			
			if (FAILED(lpd3ddevice->GetRenderTarget(0,&screen)))
				return 0;
			screen->Release();
			
			setMatrices();

			return 1;
		}

		void CDirect3D9VideoDriver::setMatrices()
		{
			lpd3ddevice ->SetTransform(D3DTS_WORLD,(D3DMATRIX *)&matrices[E_TRANSFORM_MATRIX_WORLD]);
			lpd3ddevice ->SetTransform(D3DTS_VIEW,(D3DMATRIX *)&matrices[E_TRANSFORM_MATRIX_VIEW]);
			lpd3ddevice ->SetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&matrices[E_TRANSFORM_MATRIX_PROJECTION]);
		}
		
		int CDirect3D9VideoDriver::setTransform(E_TRANSFORM_MATRIX tm,FK2DEngine2::math::Matrix4 & m4)
		{
			switch (tm)
			{
			case E_TRANSFORM_MATRIX_WORLD :
				lpd3ddevice ->SetTransform(D3DTS_WORLD,(D3DMATRIX *)&m4);
				matrices[E_TRANSFORM_MATRIX_WORLD] = m4;
				break;
			case E_TRANSFORM_MATRIX_VIEW:
				lpd3ddevice ->SetTransform(D3DTS_VIEW,(D3DMATRIX *)&m4);
				matrices[E_TRANSFORM_MATRIX_VIEW] = m4;
				break;
			case E_TRANSFORM_MATRIX_PROJECTION:
				lpd3ddevice ->SetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&m4);
				matrices[E_TRANSFORM_MATRIX_PROJECTION] = m4;
				break;
			}
			return 1;
		}

		int CDirect3D9VideoDriver::setViewport(unsigned int x,unsigned int y,unsigned int width,unsigned int height)
		{
			D3DVIEWPORT9 d3dvp9;
			d3dvp9.X = x;
			d3dvp9.Y = y;
			d3dvp9.Width = width;
			d3dvp9.Height = height;
			d3dvp9.MaxZ = 1.0f;
			d3dvp9.MinZ = 0.0f;
			if (FAILED (lpd3ddevice ->SetViewport(&d3dvp9)))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::setMaterial(const SMaterial & mat)
		{
			if (FAILED( lpd3ddevice ->SetMaterial((D3DMATERIAL9 *)(& mat))))
				return 0;
			return 1;
		}
 
		int CDirect3D9VideoDriver::setLight(const SLight & light,int index)
		{
			D3DLIGHT9 d3dLight;
			if (light.type == E_LIGHT_TYPE_POINT)
			{
				d3dLight.Type = D3DLIGHT_POINT;
				d3dLight.Position = *(D3DVECTOR*)(&light.position);
			}
			if (light.type == E_LIGHT_TYPE_DIRECTIONAL)
			{
				d3dLight.Type = D3DLIGHT_DIRECTIONAL;
				d3dLight.Direction = *(D3DVECTOR*)(&light.position);
			}

			d3dLight.Diffuse = *(D3DCOLORVALUE*)((void*)(&light.diffuse));
			d3dLight.Specular = *(D3DCOLORVALUE*)((void*)(&light.specular));
			d3dLight.Ambient = *(D3DCOLORVALUE*)((void*)(&light.ambient));
			d3dLight.Range = 10000.0f;

			d3dLight.Attenuation0 = 0.0f;
			d3dLight.Attenuation1 = 1.0f / light.radius;
			d3dLight.Attenuation2 = 0.0f;

			if (FAILED(lpd3ddevice ->SetLight(index,&d3dLight)))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::addLight(const SLight & light)
		{
			lastLightIndex ++;
			if (setLight(light,lastLightIndex) == 0)
				return -1;
			if (enableLight(lastLightIndex,true) == 0)
				return -1;
			return lastLightIndex;
		}

		void CDirect3D9VideoDriver::deleteAllLights()
		{
			int i;
			for (i = 0 ; i <= lastLightIndex ; i ++)
			{
				enableLight(i,false);
			}
			lastLightIndex = -1;
		}

		int CDirect3D9VideoDriver::setTexture(ITexture * texture)
		{
			if (currentTexture != texture)
			{
				if (currentTexture != NULL)
				{
					currentTexture->decRef();
				}
				if (texture != NULL)
				{
					texture->addRef();
				}
				currentTexture = texture;
				if (currentTexture != NULL)
				{
					{
						lpd3ddevice ->SetTexture(0,(LPDIRECT3DTEXTURE9)(currentTexture->getHandle()));
						if( UIVideoDriver )
						{
							UIVideoDriver->ClearCurTexture();
						}
					}
				}
				else
				{
					lpd3ddevice ->SetTexture(0,(LPDIRECT3DTEXTURE9)0);
				}
			}
			return 1;
		}

		void CDirect3D9VideoDriver::ClearCurTexture()
		{
			currentTexture = NULL;
		}

		bool CDirect3D9VideoDriver::CurHasTexture()
		{
			if( currentTexture == NULL )
			{
				return false;
			}
			return true;
		}

		void CDirect3D9VideoDriver::SetUIVideoDriver( DirectX9* p_pUIVideoDriver )
		{
			UIVideoDriver = p_pUIVideoDriver;
		}

		int CDirect3D9VideoDriver::setVideodriverState(E_VIDEODRIVER_STATE_TYPE state,bool enable)
		{
			switch (state)
			{
			case E_VIDEODRIVER_STATE_ALPHATESTING:
				if (enable)
				{
					lpd3ddevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000000);
					lpd3ddevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
					lpd3ddevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
				}
				else 
				{
					lpd3ddevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); 
				}
				break;
			case E_VIDEODRIVER_STATE_ALPHABLENDING :
				if (enable)
				{
					if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE)))
						return 0;
					if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA)))
						return 0;
					if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA)))
						return 0;
					if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD)))
						return 0;
				}
				else 
				{
					if (FAILED(lpd3ddevice ->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE)))
						return 0;
				}
				break;
			case E_VIDEODRIVER_STATE_LIGHTING :
				if (enable)
				{
					lpd3ddevice->SetRenderState(D3DRS_LIGHTING, TRUE ) ;
					lpd3ddevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
				} 
				else 
				{
					lpd3ddevice->SetRenderState(D3DRS_LIGHTING, FALSE ) ;
					lpd3ddevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
				}
				break;
			case E_VIDEODRIVER_STATE_SPECULARENABLE:
				if (enable)
				{
					lpd3ddevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
					lpd3ddevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
				}
				else
				{
					lpd3ddevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
				}
				break;
			case E_VIDEODRIVER_STATE_ZBUFFER :
				if (enable)
				{
					lpd3ddevice ->SetRenderState(D3DRS_ZENABLE, TRUE);
					lpd3ddevice ->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
				}
				else
				{
					lpd3ddevice ->SetRenderState(D3DRS_ZENABLE, FALSE);
				}
				break;
			}
			return 1;
		}

		int CDirect3D9VideoDriver::enableLight(int index,bool enable) 
		{
			if (FAILED(lpd3ddevice->LightEnable(index,enable)))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::setRenderTarget(ITexture * renderTarget,unsigned long flag ,SColor color)
		{
			if (currentRenderTarget != renderTarget)
			{
				IDirect3DSurface9 * target;
				if (renderTarget == 0)
				{
					target = screen;
				}
				else 
				{
					if (renderTarget->getDriverType() != E_VIDEODRIVERTYPE_D3D)
					{
						LogError( L"尝试设置一个非D3D纹理对象 : %s", currentTexture->getObjectName() );
						return 0;
					}
					target = ((CDirect3D9Texture *)(renderTarget))->getRenderTarget();
					if (target == NULL)
					{
						LogError( L"无法获取纹理所绑定的渲染对象 : %s", currentTexture->getObjectName() );
						return 0;
					}
				}
				if (FAILED(lpd3ddevice->SetRenderTarget(0,target)))
				{
					LogError( L"无法设置渲染对象");
					return 0;
				}
				if (currentRenderTarget != NULL)
				{
					currentRenderTarget->decRef();
				}
				if (renderTarget != NULL)
				{
					renderTarget->addRef();
				}
				currentRenderTarget = renderTarget;

				DWORD clearFlag = 0;
				if (flag & E_CLEAR_COLOR)
				{
					clearFlag |= D3DCLEAR_TARGET;
				}
				if ((flag & E_CLEAR_ZBUFFER) && (deviceparam.zbuffer == true))
				{
					clearFlag |= D3DCLEAR_ZBUFFER;
				}

				if (flag & E_CLEAR_STRENCIL && (false))
				{
					clearFlag |= D3DCLEAR_STENCIL;
				}
				DWORD cr = (DWORD)(color.r * 255);
				DWORD cg = (DWORD)(color.g * 255);
				DWORD cb = (DWORD)(color.b * 255);
				if (flag != E_CLEAR_NONE)
				{
					lpd3ddevice ->Clear(0,NULL,clearFlag,D3DCOLOR_XRGB(cr,cg,cb),1.0f,0);
				}
			}
			return 1;
		}

		ITexture * CDirect3D9VideoDriver::getRenderTarget()
		{
			return currentRenderTarget;
		}

		int CDirect3D9VideoDriver::beginScene(SColor color,unsigned long flag)
		{
			HRESULT hr;
			if (devicelost)
			{
				if(FAILED(hr = lpd3ddevice->TestCooperativeLevel()))
				{
					if (hr == D3DERR_DEVICELOST)
						return 0;

					if (hr == D3DERR_DEVICENOTRESET)
					{
						reset(deviceparam.width,deviceparam.height,deviceparam.zdepth,
							  deviceparam.hwnd,deviceparam.fullscreen,deviceparam.zbuffer,
							  deviceparam.alphatesting,deviceparam.alphablend,deviceparam.lighting,
							  deviceparam.immediate);
						onResetDevice();
					}
					return 0;
				}
			}
			DWORD clearFlag = 0;
			if (flag & E_CLEAR_COLOR)
			{
				clearFlag |= D3DCLEAR_TARGET;
			}
			if ((flag & E_CLEAR_ZBUFFER) && (deviceparam.zbuffer == true))
			{
				clearFlag |= D3DCLEAR_ZBUFFER;
			}
			if (flag & E_CLEAR_STRENCIL && (false))
			{
				clearFlag |= D3DCLEAR_STENCIL;
			}
			DWORD cr = (DWORD)(color.r * 255);
			DWORD cg = (DWORD)(color.g * 255);
			DWORD cb = (DWORD)(color.b * 255);
			if (flag != E_CLEAR_NONE)
			{
				lpd3ddevice ->Clear(0,NULL,clearFlag,D3DCOLOR_XRGB(cr,cg,cb),1.0f,0);
			}
			if (FAILED (lpd3ddevice ->BeginScene()) )
				return 0;
			lpd3ddevice ->SetFVF(FK2DENGINE2_FVF);
			return 1;
		}

		int CDirect3D9VideoDriver::endScene()
		{
			HRESULT hr;
			if (devicelost)
				return 0;
			lpd3ddevice ->EndScene();
		
			hr = lpd3ddevice ->Present(NULL,NULL,NULL,NULL);
			if (hr == D3DERR_DEVICELOST)
			{
				devicelost = true;
				onLostDevice();
			}
			else
			if (FAILED(hr) && hr != D3DERR_INVALIDCALL)
			{
				return 0;
			}
			return 1;
		}

		int CDirect3D9VideoDriver::drawPixel(FK2DEngine2::math::Vertex & pixel)
		{
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_POINTLIST ,1,(void *)&pixel,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawLine(FK2DEngine2::math::Line3D & line)
		{
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_LINELIST ,1, (void *) &line,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawTriangle(FK2DEngine2::math::Triangle & triangle)
		{
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_TRIANGLELIST,1,(void *)&triangle,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawQuad(FK2DEngine2::math::Quad & quad)
		{
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(void *)&quad,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawTriangleList(FK2DEngine2::math::Triangle * triangleList,int count)
		{
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_TRIANGLELIST,count,(void *)triangleList,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawTriangleFan(FK2DEngine2::math::Vertex * triangleFanList,int vertexCount)
		{
			if (vertexCount < 3)
				return 0;
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,vertexCount - 2,(void *)triangleFanList,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawTriangleStrip(FK2DEngine2::math::Vertex * triangleStripList,int vertexCount)
		{
			if (vertexCount < 3)
				return 0;
			if (FAILED(lpd3ddevice ->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,vertexCount - 2,(void *)triangleStripList,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawIndexTriangleList(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount)
		{
			if (vertexCount < 3 || triangleCount < 1)
				return 0;
			HRESULT hr = lpd3ddevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,vertexCount,
				triangleCount,indexBuffer,D3DFMT_INDEX16,trianglelist,sizeof(FK2DEngine2::math::Vertex));
			if ( FAILED( hr ) )
			{
				LogError( L"渲染四边形出错：%s", DXGetErrorString(hr) );
				return 0;
			}
			return 1;
		}

		int CDirect3D9VideoDriver::drawIndexTriangleFan(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount)
		{
			if (vertexCount < 3 || triangleCount < 1)
				return 0;
			if (FAILED(lpd3ddevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLEFAN,0,vertexCount,
				triangleCount,indexBuffer,D3DFMT_INDEX16,trianglelist,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawIndexTriangleStrip(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount)
		{
			if (vertexCount < 3 || triangleCount < 1)
				return 0;
			if (FAILED(lpd3ddevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP,0,vertexCount,
				triangleCount,indexBuffer,D3DFMT_INDEX16,trianglelist,sizeof(FK2DEngine2::math::Vertex))))
				return 0;
			return 1;
		}

		int CDirect3D9VideoDriver::drawText(IFont * font,float x,float y,SColor color,const char * format,...)
		{
			wchar_t buffer[TEXT_BUFFER_LENGTH];
			char	sBuffer[TEXT_BUFFER_LENGTH*2];
			char * parg;
			parg = (char *)&format + sizeof(format);
			vsprintf(sBuffer,format,parg);

			FK2DEngine2::core::CharToWchar( sBuffer, buffer, TEXT_BUFFER_LENGTH * 2 );

			RECT rect;
			rect.left = x; rect.top = y;
			rect.right = x + 10000; rect.bottom = y + 10000;

			((ID3DXFont *)(font->getHandle())) ->DrawText( 0,buffer,-1,&rect,DT_TOP | DT_LEFT,color.getDwordValue());

			return 1;
		}

		int CDirect3D9VideoDriver::drawTextInRect(IFont * font,float centerX,float centerY,float width,float height,SColor color, const char * format,...)
		{
			wchar_t buffer[TEXT_BUFFER_LENGTH];
			char	sBuffer[TEXT_BUFFER_LENGTH*2];
			char * parg;
			parg = (char *)&format + sizeof(format);
			vsprintf(sBuffer,format,parg);

			FK2DEngine2::core::CharToWchar( sBuffer, buffer, TEXT_BUFFER_LENGTH * 2 );

			RECT rect;
			rect.left = centerX - width / 2; rect.top = centerY - height / 2;
			rect.right = centerX + width / 2; rect.bottom = centerY + height / 2;

			((ID3DXFont *)(font->getHandle())) ->DrawText(0,buffer,-1,&rect,DT_WORDBREAK,color.getDwordValue());
			
			return 1;
		}

		void CDirect3D9VideoDriver::onLostDevice()
		{
			std::list<CDirect3D9Font *>::iterator it;
			for (it = fontList.begin() ; it != fontList.end(); it ++)
				(*it)->onLostDevice();
		}
		void CDirect3D9VideoDriver::onResetDevice()
		{
			std::list<CDirect3D9Font *>::iterator it;
			for (it = fontList.begin() ; it != fontList.end(); it ++)
				(*it)->onResetDevice();
		}

		ITexture * CDirect3D9VideoDriver::createTexture(const std::wstring & texName,int width,int height)
		{
			CDirect3D9Texture * texture = new CDirect3D9Texture(texName);
			if (texture->createTexture(width,height,lpd3ddevice) == false)
			{
				LogError( L"创建纹理失败 : %s", texName.c_str() );
				return NULL;
			}
			if (resourceMap->addResource(texture) == false)
			{
				texture->decRef();
				LogError( L"无法将纹理插入资源表( 资源表可能已经存在该对象 ) : %s", texName.c_str() );
				return NULL;
			}
			LogInfo( L"纹理创建成功 : %s", texName.c_str() );
			return texture;
		}

		ITexture * CDirect3D9VideoDriver::loadTexture(const std::wstring & texName,const std::wstring & fileName) 
		{
			CDirect3D9Texture * texture = new CDirect3D9Texture(texName);
			if (texture->loadTexture(fileName,lpd3ddevice) == false)
			{
				LogError( L"加载纹理失败 : %s", texName.c_str() );
				return NULL;
			}
			if (resourceMap->addResource(texture) == false)
			{
				texture->decRef();
				LogError( L"无法将纹理插入资源表( 资源表可能已经存在该对象 ) : %s", texName.c_str() );
				return NULL;
			}
			//LogInfo( L"纹理加载成功 : %s", texName.c_str() );
			return texture;
		}

		bool CDirect3D9VideoDriver::freeTexture(const std::wstring & texName)
		{
			IResource * texture = resourceMap->getResourceByName(texName);
			if (texture == NULL)
			{
				LogError( L"释放纹理失败 : %s", texName.c_str() );
				return false;
			}
			if (texture->getTypeInfo() != L"CDirect3D9Texture")
			{
				LogError( L"尝试释放一个非D3D纹理 : %s", texName.c_str() );
				return false;
			}
			resourceMap->freeResource(texture);
			return true;
		}

		bool CDirect3D9VideoDriver::freeTexture(ITexture * texture)
		{
			if (texture == NULL)
			{
				LogError( L"不能释放空指针纹理" );
				return false;
			}
			if (texture->getTypeInfo() != L"CDirect3D9Texture")
			{
				LogError( L"尝试释放一个非D3D纹理 : %s", texture->getObjectName() );
				return false;
			}
			resourceMap->freeResource(texture);
			return true;
		}

		IFont * CDirect3D9VideoDriver::loadFont(const std::wstring & resourceName,int height,int width,int weight,const std::wstring & fontStyleName)
		{
			CDirect3D9Font * font = new CDirect3D9Font(resourceName,this,height,width,weight,fontStyleName);
			if (resourceMap->addResource(font) == false)
			{
				font->decRef();
				LogError( L"无法将字体插入资源表( 资源表可能已经存在该对象 ) : %s", resourceName.c_str() );
				return NULL;
			}
			fontList.push_back(font);
			LogInfo( L"字体资源加载成功 : %s", resourceName.c_str() );
			return font;
		}

		bool CDirect3D9VideoDriver::freeFont(const std::wstring & resourceName)
		{
			IResource * font = resourceMap->getResourceByName(resourceName);
			if (font == NULL)
			{
				LogError( L"释放字体失败 : %s", resourceName.c_str() );
				return false;
			}
			if (font->getTypeInfo() != L"CDirect3D9Font")
			{
				LogError( L"尝试释放一个非D3D字体 : %s", resourceName.c_str() );
				return false;
			}
			resourceMap->freeResource(font);

			std::list<CDirect3D9Font * >::iterator it;
			for (it = fontList.begin(); it != fontList.end(); it ++)
				if ((*it) == font)
				{
					fontList.erase(it);
					break;
				}
			return true;
		}

		bool CDirect3D9VideoDriver::freeFont(IFont * font)
		{
			if (font == NULL)
			{
				LogError( L"不能释放空指针字体" );
				return false;
			}
			if (font->getTypeInfo() != L"CDirect3D9Font")
			{
				LogError( L"尝试释放一个非D3D字体 : %s", font->getObjectName() );
				return false;
			}
			resourceMap->freeResource(font);

			std::list<CDirect3D9Font * >::iterator it;
			for (it = fontList.begin(); it != fontList.end(); it ++)
				if ((*it) == font)
				{
					fontList.erase(it);
					break;
				}
			return true;
		}
	}
}
//------------------------------------------------------------------------