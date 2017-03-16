/**
*	created:		2013-4-11   20:27
*	filename: 		FKScrollBarButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKButton.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT ScrollBarButton : public Controls::Button
		{
			public:

				FK_CONTROL( ScrollBarButton, Controls::Button );

				void Render( Skin::Base* skin );

				void SetDirectionUp();
				void SetDirectionDown();
				void SetDirectionLeft();
				void SetDirectionRight();

			protected:

				int m_iDirection;
		};
	}
}
//------------------------------------------------------------------------