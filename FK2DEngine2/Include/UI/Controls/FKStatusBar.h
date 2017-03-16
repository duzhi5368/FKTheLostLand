/**
*	created:		2013-4-12   21:59
*	filename: 		FKStatusBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "FKLabel.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class StatusBar : public Controls::Label
		{
		public:

			FK_CONTROL_INLINE( StatusBar, Controls::Label )
			{
				SetHeight( 22 );
				Dock( Pos::Bottom );
				SetPadding( Padding( 2, 2, 2, 2 ) );
				SetText( "" );
				SetAlignment( Pos::Left | Pos::CenterV );
			}

			virtual void AddControl( Controls::Base* pCtrl, bool bRight )
			{
				pCtrl->SetParent( this );
				pCtrl->Dock( bRight ? Pos::Right : Pos::Left );
			}

			virtual void Render( Skin::Base* skin )
			{
				skin->DrawStatusBar( this );
			}
		};
	}
}
//------------------------------------------------------------------------