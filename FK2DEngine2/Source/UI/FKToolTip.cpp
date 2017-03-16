/**
*	created:		2013-4-11   22:28
*	filename: 		FKToolTip
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ToolTip
	{
		Base* g_ToolTip = NULL;

		FK_EXPORT bool TooltipActive()
		{
			return g_ToolTip != NULL;
		}

		void Enable( Controls::Base* pControl )
		{
			if ( !pControl->GetToolTip() )
			{ return; }

			g_ToolTip = pControl;
		}

		void Disable( Controls::Base* pControl )
		{
			if ( g_ToolTip == pControl )
			{
				g_ToolTip = NULL;
			}
		}

		void RenderToolTip( Skin::Base* skin )
		{
			if ( !g_ToolTip ) { return; }

			FK2DEngine2::video::Base* render = skin->GetRender();
			FK2DEngine2::Point pOldRenderOffset = render->GetRenderOffset();
			FK2DEngine2::Point MousePos = Input::GetMousePosition();
			FK2DEngine2::Rect Bounds = g_ToolTip->GetToolTip()->GetBounds();
			FK2DEngine2::Rect rOffset = FK2DEngine2::Rect( MousePos.x - Bounds.w * 0.5f, MousePos.y - Bounds.h - 10, Bounds.w, Bounds.h );
			rOffset = Utility::ClampRectToRect( rOffset, g_ToolTip->GetCanvas()->GetBounds() );
			render->AddRenderOffset( rOffset );
			render->EndClip();
			skin->DrawToolTip( g_ToolTip->GetToolTip() );
			g_ToolTip->GetToolTip()->DoRender( skin );
			render->SetRenderOffset( pOldRenderOffset );
		}

		void ControlDeleted( Controls::Base* pControl )
		{
			Disable( pControl );
		}
	}
}
//------------------------------------------------------------------------