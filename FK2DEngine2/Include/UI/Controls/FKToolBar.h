/**
*	created:		2013-4-12   22:04
*	filename: 		FKToolBar
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
	namespace Controls
	{
		class ToolBarButton : public FK2DEngine2::Controls::Button
		{
				FK_CONTROL_INLINE( ToolBarButton, FK2DEngine2::Controls::Button )
				{
					SetSize( 20, 20 );
					Dock( Pos::Left );
				}

				virtual bool ShouldDrawBackground()
				{
					return IsHovered();
				}

		};

		class ToolBarStrip : public Base
		{
				FK_CONTROL_INLINE( ToolBarStrip, Base )
				{
					SetSize( 25, 25 );
					SetPadding( Padding( 2, 2, 2, 2 ) );
				}

				virtual void Render( Skin::Base* skin )
				{
					skin->DrawMenuStrip( this );
				}

				virtual ToolBarButton* Add( const UITexObjSimpleInfo & Text, const UITexObjSimpleInfo & Icon )
				{
					ToolBarButton* pButton = new ToolBarButton( this );
					pButton->SetToolTip( Text );
					pButton->SetImage( Icon );
					return pButton;
				}
		};
	}
}
//------------------------------------------------------------------------