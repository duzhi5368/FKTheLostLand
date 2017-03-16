/**
*	created:		2013-4-11   16:57
*	filename: 		FKBaseRender
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKStructures.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	struct Font;
	struct STextureInfo;
	class WindowProvider;

	namespace video
	{
		class Base;

		class ICacheToTexture
		{
			public:

				virtual ~ICacheToTexture() {}
				virtual void Initialize() = 0;
				virtual void ShutDown() = 0;
				virtual void SetupCacheTexture( FK2DEngine2::Controls::Base* control ) = 0;
				virtual void FinishCacheTexture( FK2DEngine2::Controls::Base* control ) = 0;
				virtual void DrawCachedControlTexture( FK2DEngine2::Controls::Base* control ) = 0;
				virtual void CreateControlCacheTexture( FK2DEngine2::Controls::Base* control ) = 0;
				virtual void UpdateControlCacheTexture( FK2DEngine2::Controls::Base* control ) = 0;
				virtual void SetRenderer( FK2DEngine2::video::Base* renderer ) = 0;

		};

		class FK_EXPORT Base
		{
			public:

				Base();
				virtual ~Base();

				virtual void Init() {};

				virtual void Begin() {};
				virtual void End() {};

				virtual void SetDrawColor( Color color ) {};

				virtual void DrawFilledRect( FK2DEngine2::Rect rect ) {};;

				virtual void StartClip() {};
				virtual void EndClip() {};

				virtual void LoadTexture( FK2DEngine2::STextureInfo* pTexture ) {};
				virtual void FreeTexture( FK2DEngine2::STextureInfo* pTexture ) {};
				virtual void DrawTexturedRect( FK2DEngine2::STextureInfo* pTexture, FK2DEngine2::Rect pTargetRect,
					float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f ) {};
				virtual void DrawMissingImage( FK2DEngine2::Rect pTargetRect );
				virtual FK2DEngine2::Color PixelColour( FK2DEngine2::STextureInfo* pTexture, unsigned int x, unsigned int y,
					const FK2DEngine2::Color & col_default = FK2DEngine2::Color( 255, 255, 255, 255 ) ) { return col_default; }

				virtual ICacheToTexture* GetCTT() { return NULL; }

				virtual void LoadFont( FK2DEngine2::Font* pFont ) {};
				virtual void FreeFont( FK2DEngine2::Font* pFont ) {};
				virtual void RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::UnicodeString & text );
				virtual FK2DEngine2::Point MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::UnicodeString & text );

				//
				// 这些函数需要自己实现
				//
				virtual void DrawLinedRect( FK2DEngine2::Rect rect );
				virtual void DrawPixel( int x, int y );
				virtual void DrawShavedCornerRect( FK2DEngine2::Rect rect, bool bSlight = false );
				virtual FK2DEngine2::Point MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::String & text );
				virtual void RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::String & text );

			public:

				//
				// 从渲染坐标调整到观察坐标
				//
				void Translate( int & x, int & y );
				void Translate( FK2DEngine2::Rect & rect );

				//
				// 设置渲染偏移
				//
				void SetRenderOffset( const FK2DEngine2::Point & offset ) { m_RenderOffset = offset; }
				void AddRenderOffset( const FK2DEngine2::Rect & offset ) { m_RenderOffset.x += offset.x; m_RenderOffset.y += offset.y; }
				const FK2DEngine2::Point & GetRenderOffset() const { return m_RenderOffset; }

			private:

				FK2DEngine2::Point m_RenderOffset;

			public:

				void SetClipRegion( FK2DEngine2::Rect rect );
				void AddClipRegion( FK2DEngine2::Rect rect );
				bool ClipRegionVisible();
				const FK2DEngine2::Rect & ClipRegion() const;

			private:

				FK2DEngine2::Rect m_rectClipRegion;
				ICacheToTexture* m_RTT;

			public:

				void SetScale( float fScale ) { m_fScale = fScale; }
				float Scale() const { return m_fScale; }

				float m_fScale;


			public:

				//
				// 自己的初始化和关闭函数
				//

				virtual bool InitializeContext( FK2DEngine2::WindowProvider* pWindow ) { return false; }
				virtual bool ShutdownContext( FK2DEngine2::WindowProvider* pWindow ) { return false; }
				virtual bool ResizedContext( FK2DEngine2::WindowProvider* pWindow, int w, int h ) { return false; }

				virtual bool BeginContext( FK2DEngine2::WindowProvider* pWindow ) { return false; }
				virtual bool EndContext( FK2DEngine2::WindowProvider* pWindow ) { return false; }
				virtual bool PresentContext( FK2DEngine2::WindowProvider* pWindow ) { return false; }



		};
	}
}
//------------------------------------------------------------------------