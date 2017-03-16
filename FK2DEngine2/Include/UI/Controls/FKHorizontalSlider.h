/**
*	created:		2013-4-12   15:02
*	filename: 		FKHorizontalSlider
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKDragger.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKSlider.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT HorizontalSlider : public Slider
		{
				FK_CONTROL( HorizontalSlider, Slider );

				virtual void Layout( Skin::Base* skin );
				virtual void Render( Skin::Base* skin );

				virtual float CalculateValue();
				virtual void UpdateBarFromValue();
				virtual void OnMouseClickLeft( int x, int y, bool bDown );
		};
	}
}
//------------------------------------------------------------------------