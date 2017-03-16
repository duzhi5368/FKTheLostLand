/**
*	created:		2013-4-12   14:56
*	filename: 		FKColorPicker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "../FKSkin.h"
#include "../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT ColorDisplay : public Controls::Base
		{
			public:
				FK_CONTROL_INLINE( ColorDisplay, Controls::Base )
				{
					SetSize( 32, 32 );
					m_Color = Color( 255, 0, 0, 255 );
					m_DrawCheckers = true;
				}

				virtual void Render( FK2DEngine2::Skin::Base* skin )
				{
					skin->DrawColorDisplay( this, m_Color );
				}

				virtual void SetColor( FK2DEngine2::Color color ) { m_Color = color; }
				virtual FK2DEngine2::Color GetColor() { return m_Color; }

				virtual void SetRed( int red )  	{ m_Color.r = red;	}
				virtual void SetGreen( int green )	{ m_Color.g = green;}
				virtual void SetBlue( int blue )	{ m_Color.b = blue;	}
				virtual void SetAlpha( int alpha )	{ m_Color.a = alpha;}

				virtual void SetDrawCheckers( bool should ) { m_DrawCheckers = should; }

			protected:
				FK2DEngine2::Color m_Color;
				bool m_DrawCheckers;
		};
	}
	namespace Controls
	{

		class FK_EXPORT ColorPicker : public Base
		{
			public:

				FK_CONTROL( ColorPicker, Base );

				virtual void Layout( Skin::Base* skin );
				virtual void CreateControls();
				virtual void SlidersMoved( FK2DEngine2::Controls::Base* control );
				virtual void NumericTyped( FK2DEngine2::Controls::Base* control );
				virtual void UpdateControls();
				virtual void UpdateColorControls( FK2DEngine2::String name, FK2DEngine2::Color col, int sliderVal );
				virtual void CreateColorControl( FK2DEngine2::String name, int y );

				virtual void SetColor( FK2DEngine2::Color color );
				virtual FK2DEngine2::Color GetColor() { return m_Color; }

				int GetColorByName( FK2DEngine2::String colorName );
				void SetColorByName( FK2DEngine2::String colorName, int colorValue );
				FK2DEngine2::String GetColorFromName( FK2DEngine2::String name );
				virtual void SetAlphaVisible( bool visible );

				virtual void SetRed( int red )  	{ m_Color.r = red;	}
				virtual void SetGreen( int green )	{ m_Color.g = green;}
				virtual void SetBlue( int blue )	{ m_Color.b = blue;	}
				virtual void SetAlpha( int alpha )	{ m_Color.a = alpha;}

				Event::Caller	onColorChanged;

			protected:
				FK2DEngine2::Color m_Color;

		};
	}
}
//------------------------------------------------------------------------