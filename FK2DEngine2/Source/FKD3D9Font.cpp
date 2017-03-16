/**
*	created:		2013-4-23   19:10
*	filename: 		FKD3D9Font
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKLogger.h"
#include "../Include/FKD3D9Font.h"
#include "../Include/FKStringConvert.h"
//------------------------------------------------------------------------
#pragma warning( disable : 4996 )
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		CDirect3D9Font::CDirect3D9Font(const std::wstring & resourceName,CDirect3D9VideoDriver * videoDriver,int height,int width,int weight,const std::wstring & fontName)
			:IFont(resourceName)
		{
			memset(&lf,0,sizeof(lf));
			lf.Height         = height;			// in logical units
			lf.Width          = width;			// in logical units
			lf.Weight         = weight;			// boldness, range 0(light) - 1000(bold)
			lf.Italic         = false;
			lf.CharSet        = DEFAULT_CHARSET;

			wcscpy( lf.FaceName, fontName.c_str() ); // font style
			
			if (FAILED(D3DXCreateFontIndirect(videoDriver->getHandle(),&lf,&font)))
			{
				LogError( L"创建字体失败 : %s", fontName.c_str() );
				font = NULL;
			}
			else 
			{
				LogInfo( L"创建字体成功 : %s", fontName.c_str() );
			}
		}
		CDirect3D9Font::~CDirect3D9Font()
		{
			if (font != NULL)
			{
				LogInfo( L"释放字体 : %s", getObjectName().c_str() );
				font->Release();
				font = NULL;
			}
		}
		int CDirect3D9Font::getHeight()
		{
			return (int)(lf.Height);
		}
		int CDirect3D9Font::getWIdth()
		{
			return (int)(lf.Width);
		}
		int CDirect3D9Font::getWeight()
		{
			return (int)(lf.Weight);
		}
		unsigned long CDirect3D9Font::getHandle()
		{
			return (unsigned long)(font);
		}
		bool CDirect3D9Font::onLostDevice()
		{
			if (FAILED(font->OnLostDevice()))
				return false;
			return true;
		}
		bool CDirect3D9Font::onResetDevice()
		{
			if (FAILED(font->OnResetDevice()))
				return false;
			return true;
		}
	}
}
//------------------------------------------------------------------------