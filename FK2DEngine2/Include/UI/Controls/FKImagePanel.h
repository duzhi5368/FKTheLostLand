/**
*	created:		2013-4-12   0:32
*	filename: 		FKImagePanel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "FKBase.h"
#include "../FKBaseRender.h"
#include "../FKTexture.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT ImagePanel : public Controls::Base
		{
			public:

				FK_CONTROL_INLINE( ImagePanel, Controls::Base )
				{
					SetUV( 0, 0, 1, 1 );
					SetMouseInputEnabled( false );
					m_DrawColor = Colors::White;
					SetStretch( true );
				}

				virtual ~ImagePanel()
				{
					m_Texture.Release( GetSkin()->GetRender() );
				}

				virtual void SetUV( float u1, float v1, float u2, float v2 )
				{
					m_uv[0] = u1;
					m_uv[1] = v1;
					m_uv[2] = u2;
					m_uv[3] = v2;
				}

				virtual void SetImage( const UITexObjSimpleInfo & imageName )
				{
					m_Texture.Load( imageName, GetSkin()->GetRender() );
				}

				virtual UITexObjSimpleInfo & GetImage()
				{
					return m_Texture.name;
				}

				virtual int TextureWidth()
				{
					return m_Texture.width;
				}

				virtual int TextureHeight()
				{
					return m_Texture.height;
				}

				virtual const UITexObjSimpleInfo & GetImageName()
				{
					return m_Texture.name;
				}

				virtual void Render( Skin::Base* skin )
				{
					skin->GetRender()->SetDrawColor( m_DrawColor );

					if ( m_bStretch )
					{ skin->GetRender()->DrawTexturedRect( &m_Texture, GetRenderBounds(), m_uv[0], m_uv[1], m_uv[2], m_uv[3] ); }
					else
					{ skin->GetRender()->DrawTexturedRect( &m_Texture, FK2DEngine2::Rect( 0, 0, m_Texture.width, m_Texture.height ), m_uv[0], m_uv[1], m_uv[2], m_uv[3] ); }
				}

				virtual void SizeToContents()
				{
					SetSize( m_Texture.width, m_Texture.height );
				}

				virtual void SetDrawColor( FK2DEngine2::Color color )
				{
					m_DrawColor = color;
				}

				virtual bool FailedToLoad()
				{
					return m_Texture.FailedToLoad();
				}

				virtual bool GetStretch() { return m_bStretch; }
				virtual void SetStretch( bool b ) { m_bStretch = b; }

			protected:

				STextureInfo			m_Texture;
				float			m_uv[4];
				FK2DEngine2::Color		m_DrawColor;

				bool			m_bStretch;

		};
	}
}
//------------------------------------------------------------------------