/**
*	created:		2013-4-11   23:34
*	filename: 		FKDirectX9
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
#include <D3D9.h>
#include <D3DX9Core.h>
//------------------------------------------------------------------------
#pragma comment( lib, "D3D9.lib" )
#pragma comment( lib, "D3Dx9.lib" )
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace video
	{
		class IVideoDriver;
	}
}
namespace FK2DEngine2
{
	namespace video
	{
		class FK_EXPORT DirectX9 : public FK2DEngine2::video::Base
		{
			public:

				DirectX9( IDirect3DDevice9* pDevice );
				DirectX9( FK2DEngine2::video::IVideoDriver* pDriver = NULL );
				~DirectX9();

				virtual void Begin();
				virtual void End();
				virtual void Release();
				virtual void ClearCurTexture();
				virtual bool CurHasTexture();

				virtual void SetDrawColor( FK2DEngine2::Color color );

				virtual void DrawFilledRect( FK2DEngine2::Rect rect );

				virtual void LoadFont( FK2DEngine2::Font* pFont );
				virtual void FreeFont( FK2DEngine2::Font* pFont );
				virtual void RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::UnicodeString & text );
				virtual FK2DEngine2::Point MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::UnicodeString & text );

				// ¿ªÊ¼¼ô²Ã
				void StartClip();
				// ¹Ø±Õ¼ô²Ã
				void EndClip();

				void DrawTexturedRect( FK2DEngine2::STextureInfo* pTexture, FK2DEngine2::Rect pTargetRect, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f );
				void LoadTexture( FK2DEngine2::STextureInfo* pTexture );
				void FreeTexture( FK2DEngine2::STextureInfo* pTexture );
				FK2DEngine2::Color PixelColour( FK2DEngine2::STextureInfo* pTexture, unsigned int x, unsigned int y, const FK2DEngine2::Color & col_default );

			protected:

				void*				m_pCurrentTexture;
				IDirect3DDevice9*	m_pDevice;
				IDirect3D9*			m_pD3D;
				DWORD				m_Color;
				FK2DEngine2::video::IVideoDriver* m_pDriver;
				FK2DEngine2::Font::List	m_FontList;

				void Flush();
				void AddVert( int x, int y );
				void AddVert( int x, int y, float u, float v );

			protected:

				struct VertexFormat
				{
					FLOAT x, y, z, rhw;
					DWORD color;
					float u, v;
				};

				static const int		MaxVerts = 1024;
				VertexFormat			m_pVerts[MaxVerts];
				int						m_iVertNum;
		};

	}
}
//------------------------------------------------------------------------