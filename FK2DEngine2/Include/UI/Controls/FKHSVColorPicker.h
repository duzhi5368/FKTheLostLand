/**
*	created:		2013-4-12   15:39
*	filename: 		FKHSVColorPicker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKColorControls.h"
#include "FKColorPicker.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT HSVColorPicker : public Controls::Base
		{
			public:
				FK_CONTROL( HSVColorPicker, Controls::Base );

				FK2DEngine2::Color GetColor();
				FK2DEngine2::Color GetDefaultColor() { return m_Before->GetColor(); }
				void SetColor( FK2DEngine2::Color color, bool onlyHue = false, bool reset = false );

				void ColorBoxChanged( FK2DEngine2::Controls::Base* pControl );
				void ColorSliderChanged( FK2DEngine2::Controls::Base* pControl );
				void NumericTyped( FK2DEngine2::Controls::Base* control );

				void UpdateControls( FK2DEngine2::Color newColor );

				Event::Caller	onColorChanged;

			protected:
				ColorLerpBox* m_LerpBox;
				ColorSlider* m_ColorSlider;
				ControlsInternal::ColorDisplay* m_Before;
				ControlsInternal::ColorDisplay* m_After;
		};
	}
}
//------------------------------------------------------------------------