/**
*	created:		2013-4-11   21:15
*	filename: 		FKSkin
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
#include <math.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Skin
	{
		void Base::DrawArrowDown( FK2DEngine2::Rect rect )
		{
			float x = ( rect.w / 5.0f );
			float y = ( rect.h / 5.0f );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 0.0f, rect.y + y * 1.0f, x, y * 1.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 1.0f, x, y * 2.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 2.0f, rect.y + y * 1.0f, x, y * 3.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 3.0f, rect.y + y * 1.0f, x, y * 2.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 4.0f, rect.y + y * 1.0f, x, y * 1.0f ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawArrowUp( FK2DEngine2::Rect rect )
		{
			float x = ( rect.w / 5.0f );
			float y = ( rect.h / 5.0f );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 0.0f, rect.y + y * 3.0f, x, y * 1.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 2.0f, x, y * 2.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 2.0f, rect.y + y * 1.0f, x, y * 3.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 3.0f, rect.y + y * 2.0f, x, y * 2.0f ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 4.0f, rect.y + y * 3.0f, x, y * 1.0f ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawArrowLeft( FK2DEngine2::Rect rect )
		{
			float x = ( rect.w / 5.0f );
			float y = ( rect.h / 5.0f );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 3.0f, rect.y + y * 0.0f, x * 1.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 2.0f, rect.y + y * 1.0f, x * 2.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 2.0f, x * 3.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 2.0f, rect.y + y * 3.0f, x * 2.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 3.0f, rect.y + y * 4.0f, x * 1.0f, y ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawArrowRight( FK2DEngine2::Rect rect )
		{
			float x = ( rect.w / 5.0f );
			float y = ( rect.h / 5.0f );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 0.0f, x * 1.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 1.0f, x * 2.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 2.0f, x * 3.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 3.0f, x * 2.0f, y ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 4.0f, x * 1.0f, y ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawCheck( FK2DEngine2::Rect rect )
		{
			float x = ( rect.w / 5.0f );
			float y = ( rect.h / 5.0f );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 0.0f, rect.y + y * 3.0f, x * 2, y * 2 ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 1.0f, rect.y + y * 4.0f, x * 2, y * 2 ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 2.0f, rect.y + y * 3.0f, x * 2, y * 2 ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 3.0f, rect.y + y * 1.0f, x * 2, y * 2 ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + x * 4.0f, rect.y + y * 0.0f, x * 2, y * 2 ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawTreeNode( Controls::Base* ctrl, bool bOpen, bool bSelected, int iLabelHeight, int iLabelWidth, int iHalfWay, int iLastBranch, bool bIsRoot )
		{
			GetRender()->SetDrawColor( Colors.Tree.Lines );

			if ( !bIsRoot )
			{ GetRender()->DrawFilledRect( FK2DEngine2::Rect( 8, iHalfWay, 16 - 9, 1 ) ); }

			if ( !bOpen ) { return; }

			GetRender()->DrawFilledRect( FK2DEngine2::Rect( 14 + 7, iLabelHeight + 1, 1, iLastBranch + iHalfWay - iLabelHeight ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawPropertyTreeNode( Controls::Base* control, int BorderLeft, int BorderTop )
		{
			FK2DEngine2::Rect rect = control->GetRenderBounds();
			m_Render->SetDrawColor( Colors.Properties.Border );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x, rect.y, BorderLeft, rect.h ) );
			m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + BorderLeft, rect.y, rect.w - BorderLeft, BorderTop ) );
		}
		//------------------------------------------------------------------------
		void Base::DrawPropertyRow( Controls::Base* control, int iWidth, bool bBeingEdited, bool bHovered )
		{
			FK2DEngine2::Rect rect = control->GetRenderBounds();

			if ( bBeingEdited )					{ m_Render->SetDrawColor( Colors.Properties.Column_Selected ); }
			else if ( bHovered )				{ m_Render->SetDrawColor( Colors.Properties.Column_Hover ); }
			else								{ m_Render->SetDrawColor( Colors.Properties.Column_Normal ); }

			m_Render->DrawFilledRect( FK2DEngine2::Rect( 0, rect.y, iWidth, rect.h ) );

			if ( bBeingEdited )					{ m_Render->SetDrawColor( Colors.Properties.Line_Selected ); }
			else if ( bHovered )				{ m_Render->SetDrawColor( Colors.Properties.Line_Hover ); }
			else								{ m_Render->SetDrawColor( Colors.Properties.Line_Normal ); }

			m_Render->DrawFilledRect( FK2DEngine2::Rect( iWidth, rect.y, 1, rect.h ) );
			rect.y += rect.h - 1;
			rect.h = 1;
			m_Render->DrawFilledRect( rect );
		}
		//------------------------------------------------------------------------
	}
}
