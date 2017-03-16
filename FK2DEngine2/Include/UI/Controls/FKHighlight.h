/**
*	created:		2013-4-12   17:06
*	filename: 		FKHighlight
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT Highlight : public Controls::Base
		{
			public:

				FK_CONTROL_INLINE( Highlight, Controls::Base )
				{
				}

				void Render( Skin::Base* skin )
				{
					skin->DrawHighlight( this );
				}
		};
	}

}
//------------------------------------------------------------------------