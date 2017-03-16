/**
*	created:		2013-4-11   20:25
*	filename: 		FKScrollBarBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKDragger.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT ScrollBarBar : public ControlsInternal::Dragger
		{
			public:

				FK_CONTROL( ScrollBarBar, ControlsInternal::Dragger );

				virtual void Render( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );

				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
				virtual void OnMouseClickLeft( int x, int y, bool bDown );

				virtual void MoveTo( int x, int y );

				virtual void SetHorizontal()	{ m_bHorizontal = true; }
				virtual void SetVertical()		{ m_bHorizontal = false; }
				virtual bool IsVertical()		{ return !m_bHorizontal; }
				virtual bool IsHorizontal()		{ return m_bHorizontal; }
				virtual bool IsDepressed()		{ return m_bDepressed; }

			protected:

				bool m_bHorizontal;

		};
	}
}
//------------------------------------------------------------------------