/**
*	created:		2013-4-12   1:22
*	filename: 		FKVerticalScrollBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKScrollBar.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT VerticalScrollBar : public BaseScrollBar
		{
			FK_CONTROL( VerticalScrollBar, BaseScrollBar );

			virtual void Layout( Skin::Base* skin );

			virtual void OnMouseClickLeft( int x, int y, bool bDown );
			virtual void OnBarMoved( Controls::Base* control );

			virtual int GetBarSize() { return  m_Bar->Height(); }
			virtual int GetBarPos() { return m_Bar->Y() - Width(); }
			virtual void SetBarSize( int size ) { m_Bar->SetHeight( size ); }
			virtual int GetButtonSize() { return Width(); }

			virtual void ScrollToTop();
			virtual void ScrollToBottom();
			virtual void NudgeUp( Base* control );
			virtual void NudgeDown( Base* control );
			virtual float GetNudgeAmount();

			virtual float CalculateScrolledAmount();
			virtual bool SetScrolledAmount( float amount, bool forceUpdate );

		};
	}
}
//------------------------------------------------------------------------