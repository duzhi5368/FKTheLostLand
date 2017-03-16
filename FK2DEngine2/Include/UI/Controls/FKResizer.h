/**
*	created:		2013-4-12   17:17
*	filename: 		FKResizer
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
#include "FKDragger.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT Resizer : public Dragger
		{
			public:

				FK_CONTROL( Resizer, Dragger );

				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual void SetResizeDir( int dir );

				Event::Caller	onResize;

			protected:

				int		m_iResizeDir;

		};
	}
}
//------------------------------------------------------------------------