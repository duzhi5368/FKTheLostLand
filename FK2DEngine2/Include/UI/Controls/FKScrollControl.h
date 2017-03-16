/**
*	created:		2013-4-12   1:21
*	filename: 		FKScrollControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "FKScrollBar.h"
#include "FKVerticalScrollBar.h"
#include "FKHorizontalScrollBar.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT ScrollControl : public Base
		{
			public:

				FK_CONTROL( ScrollControl, Base );

				virtual void Layout( Skin::Base* skin );
				virtual void Render( Skin::Base* skin );

				virtual void SetScroll( bool h, bool v );
				virtual void SetAutoHideBars( bool should ) { m_bAutoHideBars = should; }
				virtual bool CanScrollH() { return m_bCanScrollH; }
				virtual bool CanScrollV() { return m_bCanScrollV; }
				virtual void OnChildBoundsChanged( FK2DEngine2::Rect oldChildBounds, Base* pChild );
				virtual void UpdateScrollBars();

				virtual void SetVScrollRequired( bool req );
				virtual void SetHScrollRequired( bool req );

				virtual void SetInnerSize( int w, int h );

				virtual void VBarMoved( Controls::Base* control );
				virtual void HBarMoved( Controls::Base* control );

				virtual bool OnMouseWheeled( int iDelta );

				virtual void ScrollToBottom();
				virtual void ScrollToTop();
				virtual void ScrollToLeft();
				virtual void ScrollToRight();

				virtual void Clear();

			protected:

				virtual bool ContentsAreDocked();

				bool m_bCanScrollH;
				bool m_bCanScrollV;

				bool m_bAutoHideBars;

				Controls::BaseScrollBar* m_VerticalScrollBar;
				Controls::BaseScrollBar* m_HorizontalScrollBar;
		};
	}
}
//------------------------------------------------------------------------