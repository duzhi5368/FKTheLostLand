/**
*	created:		2013-4-12   0:16
*	filename: 		FKLabelClickable
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT LabelClickable : public Button
		{
			public:

				FK_CONTROL( LabelClickable, Button );

				virtual void Render( Skin::Base* skin );

		};
	}
}
//------------------------------------------------------------------------