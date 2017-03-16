/**
*	created:		2013-4-11   20:30
*	filename: 		FKScrollBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKScrollBarBar.h"
#include "FKScrollBarButton.h"
#include "../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
#define SCROLL_BUTTON_UP 0
#define SCROLL_BUTTON_LEFT 0
#define SCROLL_BUTTON_DOWN 1
#define SCROLL_BUTTON_RIGHT 1
#define NUDGE_DIST 10
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT BaseScrollBar : public Base
		{
			public:

				FK_CONTROL( BaseScrollBar, Base );

				virtual void Render( Skin::Base* skin );

				virtual void SetBarSize( int size ) = 0;
				virtual int GetBarSize() = 0;
				virtual int GetBarPos() = 0;

				virtual void OnBarMoved( Controls::Base* control );
				virtual void OnMouseClickLeft( int /*x*/, int /*y*/, bool /*bDown*/ ) {}

				virtual void ScrollToLeft() {}
				virtual void ScrollToRight() {}
				virtual void ScrollToTop() {}
				virtual void ScrollToBottom() {}

				virtual float GetNudgeAmount() { return m_fNudgeAmount / m_fContentSize; }
				virtual void SetNudgeAmount( float nudge ) { m_fNudgeAmount = nudge; }

				virtual void BarMovedNotification();

				virtual float CalculateScrolledAmount() { return 0; }
				virtual int CalculateBarSize() { return 0; }
				virtual bool SetScrolledAmount( float amount, bool forceUpdate );

				virtual void SetContentSize( float size );
				virtual void SetViewableContentSize( float size );

				virtual int GetButtonSize() { return 0; }
				virtual float GetScrolledAmount() { return m_fScrolledAmount; }

				virtual bool IsHorizontal() { return false; }

				FK2DEngine2::Event::Caller	onBarMoved;

			protected:

				ControlsInternal::ScrollBarButton* m_ScrollButton[2];
				ControlsInternal::ScrollBarBar* m_Bar;

				bool m_bDepressed;
				float m_fScrolledAmount;
				float m_fContentSize;
				float m_fViewableContentSize;
				float m_fNudgeAmount;
		};
	}
}
//------------------------------------------------------------------------