/**
*	created:		2013-4-12   1:26
*	filename: 		FKHorizontalScrollBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKDragger.h"
#include "FKScrollBar.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT HorizontalScrollBar : public BaseScrollBar
		{
			public:

				FK_CONTROL( HorizontalScrollBar, BaseScrollBar );

				virtual void Layout( Skin::Base* skin );

				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				virtual void OnBarMoved( Controls::Base* control );

				virtual int GetBarSize() { return m_Bar->Width(); }
				virtual int GetBarPos() { return m_Bar->X() - Height(); }
				virtual void SetBarSize( int size ) { m_Bar->SetWidth( size ); }
				virtual int GetButtonSize() { return Height(); }

				virtual void ScrollToLeft();
				virtual void ScrollToRight();
				virtual void NudgeLeft( Base* control );
				virtual void NudgeRight( Base* control );
				virtual float GetNudgeAmount();

				virtual float CalculateScrolledAmount();
				virtual bool SetScrolledAmount( float amount, bool forceUpdate );

				virtual bool IsHorizontal() { return true; }
		};
	}
}
//------------------------------------------------------------------------