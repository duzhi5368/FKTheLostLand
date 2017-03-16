/**
*	created:		2013-4-23   17:27
*	filename: 		FKD3D9Font
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIFont.h"
#include "FKD3D9VideoDriver.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		class CDirect3D9Font : public IFont
		{
		public:
			virtual const std::wstring getTypeInfo() const {
				return L"CDirect3D9Font";
			}
			CDirect3D9Font(const std::wstring & resourceName,CDirect3D9VideoDriver * videoDriver,
				int height,int width,int weight,const std::wstring & fontName);
			virtual ~CDirect3D9Font();
			virtual int getHeight();
			virtual int getWIdth();
			virtual int getWeight();
			virtual unsigned long getHandle();
			virtual bool onLostDevice();
			virtual bool onResetDevice();
		private:
			ID3DXFont * font;
			D3DXFONT_DESC lf;
		};
	}
}
//------------------------------------------------------------------------