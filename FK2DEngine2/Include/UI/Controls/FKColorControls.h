/**
*	created:		2013-4-12   14:51
*	filename: 		FKColorControls
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
	namespace Controls
	{

		class FK_EXPORT ColorLerpBox : public Controls::Base
		{
			public:
				FK_CONTROL( ColorLerpBox, Controls::Base );
				virtual void Render( FK2DEngine2::Skin::Base* skin );
				FK2DEngine2::Color GetColorAtPos( int x, int y );
				void SetColor( FK2DEngine2::Color color, bool onlyHue = true );
				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				FK2DEngine2::Color GetSelectedColor();

				Event::Caller	onSelectionChanged;
			protected:
				FK2DEngine2::Point cursorPos;
				bool m_bDepressed;
				int m_Hue;

		};

		class FK_EXPORT ColorSlider : public Controls::Base
		{
			public:
				FK_CONTROL( ColorSlider, Controls::Base );
				virtual void Render( FK2DEngine2::Skin::Base* skin );
				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				FK2DEngine2::Color GetSelectedColor();
				FK2DEngine2::Color GetColorAtHeight( int y );
				void SetColor( FK2DEngine2::Color color );

				Event::Caller	onSelectionChanged;

			protected:
				int m_iSelectedDist;
				bool m_bDepressed;

		};
	}

}
//------------------------------------------------------------------------