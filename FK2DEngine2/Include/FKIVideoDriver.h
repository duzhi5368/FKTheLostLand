/**
*	created:		2013-4-23   15:48
*	filename: 		FKIVideoDriver
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <cstdarg>
#include <windows.h>

#include "FKLine3D.h"
#include "FKTriangle.h"
#include "FKQuad.h"

#include "FKException.h"
#include "FKResourceMap.h"
#include "FKLogger.h"
#include "FKIBase.h"

#include "FKEVideoDriverType.h"
#include "FKITexture.h"
#include "FKSColor.h"
#include "FKLight.h"
#include "FKSMaterial.h"
#include "FKIFont.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		//------------------------------------------------------------------------
		// 枚举矩阵类型
		typedef enum{
			E_TRANSFORM_MATRIX_WORLD,
			E_TRANSFORM_MATRIX_VIEW,
			E_TRANSFORM_MATRIX_PROJECTION,
			E_TRAMSFORM_MATRIX_COUNT
		}E_TRANSFORM_MATRIX;
		//------------------------------------------------------------------------
		// 缓冲区清理方式枚举
		typedef enum{
			E_CLEAR_NONE = 0x00000000,
			E_CLEAR_ALL = 0xffffffff,
			E_CLEAR_COLOR = 0x00000001,
			E_CLEAR_ZBUFFER = 0x00000002,
			E_CLEAR_STRENCIL = 0x00000004,
		}E_CLEAR_BUFFER_BIT;
		//------------------------------------------------------------------------
		// 渲染器状态枚举
		typedef enum {
			E_VIDEODRIVER_STATE_ALPHATESTING,
			E_VIDEODRIVER_STATE_ALPHABLENDING,
			E_VIDEODRIVER_STATE_LIGHTING,
			E_VIDEODRIVER_STATE_ZBUFFER,
			E_VIDEODRIVER_STATE_SPECULARENABLE
		}E_VIDEODRIVER_STATE_TYPE;
		//------------------------------------------------------------------------
		class IVideoDriver : public FK2DEngine2::core::IBase
		{
		public :
			virtual ~IVideoDriver(){};
			IVideoDriver(){};

			//! 初始化渲染器
			//! \return 是否成功
			virtual bool initDriver( int width,int height,int zdepth,HWND hwnd,
									bool fullscreen = false,
									bool zbuffer = false,
									bool alphatesting = false,
									bool alphablend = true,
									bool lighting = false,
									bool immediate = true) = 0;
			//! 关闭渲染器 
			//! \return 是否成功
			virtual bool shutDriver() = 0;

			//! 重置渲染器
			//! \return 渲染器状态
			virtual int reset(int width,int height,int zdepth,HWND hwnd,
								bool fullscreen = false,
								bool zbuffer = false,
								bool alphatesting = false,
								bool alphablend = true,
								bool lighting = false,
								bool immediate = true) = 0;

			//! 设置渲染器的转换矩阵
			virtual int setTransform(E_TRANSFORM_MATRIX tm,FK2DEngine2::math::Matrix4 & m4) = 0;

			//! 设置渲染器的视口
			virtual int setViewport(unsigned int x,unsigned int y,unsigned int width,unsigned int height) = 0;
			
			//! 设置当前渲染材质
			virtual int setMaterial(const SMaterial & mat) = 0;

			//! 设置光照组内的光照信息
			virtual int setLight(const SLight & light,int index) = 0;

			//! 向渲染器的光照组中增加光照
			//!\return 返回该光照在光照组中的索引值
			virtual int addLight(const SLight & light) = 0;

			//! 清理渲染器的当前纹理
			virtual void ClearCurTexture() = 0;

			//! 获取当前渲染器是否有纹理
			virtual bool CurHasTexture() = 0;

			//! 删除全部光照
			virtual void deleteAllLights() = 0;

			//! 设置当前渲染纹理 【内部会对该纹理 addRef】
			virtual int setTexture(ITexture * texture) = 0;

			//! 设置渲染器状态
			virtual int setVideodriverState(E_VIDEODRIVER_STATE_TYPE state,bool enable) = 0;

			//! 设置渲染对象进行清理
			//!\params renderTarget: 渲染对象纹理 【如果该值为NULL，则表示渲染对象纹理为全屏幕】
			virtual int setRenderTarget(ITexture * renderTarget,unsigned long flag = E_CLEAR_NONE,SColor color = SColor::black()) = 0;

			//! 获取当前渲染对象 【如果渲染对象是全屏幕，则返回 NULL】
			virtual ITexture * getRenderTarget() = 0;
			
			//! 开启指定编号的光照
			virtual int enableLight(int index,bool enable) = 0;
			
			//! 清除全部缓冲，开始进行渲染
			virtual int beginScene(SColor color,unsigned long flag) = 0;

			//! 渲染完毕，进行后台缓冲链交换
			virtual int endScene() = 0;

			//! 绘制一个像素
			virtual int drawPixel(FK2DEngine2::math::Vertex & pixel) = 0;

			//! 绘制一条线
			virtual int drawLine(FK2DEngine2::math::Line3D & line) = 0;
			
			//! 绘制一个三角形
			virtual int drawTriangle(FK2DEngine2::math::Triangle & triangle) = 0;

			//! 绘制一个四方形
			virtual int drawQuad(FK2DEngine2::math::Quad & quad) = 0;

			//! 绘制一个三角形链
			virtual int drawTriangleList(FK2DEngine2::math::Triangle * triangleList,int count) = 0;

			//! 绘制一个三角形扇
			virtual int drawTriangleFan(FK2DEngine2::math::Vertex * triangleFanList,int vertexCount) = 0;

			//! 绘制一个三角形表
			virtual int drawTriangleStrip(FK2DEngine2::math::Vertex * triangleStripList,int vertexCount) = 0;

			//! 绘制一个带索引的三角形链
			virtual int drawIndexTriangleList(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount) = 0;

			//! 绘制一个带索引的三角形扇
			virtual int drawIndexTriangleFan(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount) = 0;

			//! 绘制一个带索引的三角形表
			virtual int drawIndexTriangleStrip(FK2DEngine2::math::Vertex * trianglelist,int vertexCount,const unsigned short * indexBuffer,int triangleCount) = 0;

			//! 绘制文字
			virtual int drawText(IFont * font,float x,float y,SColor color,const char * format,...) = 0;

			//! 在一个矩形区间内绘制文字
			virtual int drawTextInRect(IFont * font,float centerX,float centerY,float width,float height,SColor color, const char * format,...) = 0;
			
			//! 创建一个纹理 【通过纹理工厂创建，创建后会被加入到资源表内】
			virtual ITexture * createTexture(const std::wstring & texName,int width,int height) = 0;

			//! 加载一个纹理资源【通过纹理工厂创建，创建后会被加入到资源表内】
			virtual ITexture * loadTexture(const std::wstring & texName,const std::wstring & fileName) = 0;

			//! 释放一个纹理 【从资源表中删除】
			virtual bool freeTexture(const std::wstring & texName) = 0;

			//! 释放一个纹理 【从资源表中删除】
			virtual bool freeTexture(ITexture * texture) = 0;

			//! 创建一个文字 【创建后会被加入到资源表内】
			virtual IFont * loadFont(const std::wstring & resourceName,int height,int width,int weight,const std::wstring & fontStyleName) = 0;

			//! 释放一个文字 【从资源表中删除】
			virtual bool freeFont(const std::wstring & resourceName) = 0;

			//! 释放一个文字 【从资源表中删除】
			virtual bool freeFont(IFont * font) = 0;

		public:
			FK2DEngine2::core::CResourceMap * getResourceMap(){
				return resourceMap;
			}
			FK2DEngine2::core::CResourceMap * setResourceMap(FK2DEngine2::core::CResourceMap * resourceMap_){
				FK2DEngine2::core::CResourceMap * ret = resourceMap;
				resourceMap = resourceMap_;
				return ret;
			}
		protected: 
			FK2DEngine2::core::CResourceMap * resourceMap;
		};
	}
}
//------------------------------------------------------------------------