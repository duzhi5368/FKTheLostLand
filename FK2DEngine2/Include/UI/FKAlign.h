/**
*	created:		2013-4-11   20:38
*	filename: 		FKAlign
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "Controls/FKBase.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Align
	{
		inline void PlaceBelow( Controls::Base* ctrl, Controls::Base* below, int iBorder = 0 )
		{
			ctrl->SetPos( ctrl->X(), below->Bottom() + iBorder );
		}
	}
}
//------------------------------------------------------------------------