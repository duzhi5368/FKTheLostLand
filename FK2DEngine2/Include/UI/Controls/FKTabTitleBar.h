/**
*	created:		2013-4-12   17:05
*	filename: 		FKTabTitleBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "FKTabButton.h"
#include "../FKDragAndDrop.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT TabTitleBar : public Label
		{
			public:

				FK_CONTROL_INLINE( TabTitleBar, Label )
				{
					SetMouseInputEnabled( true );
					SetTextPadding( FK2DEngine2::Padding( 5, 2, 5, 2 ) );
					SetPadding( FK2DEngine2::Padding( 1, 2, 1, 2 ) );
					DragAndDrop_SetPackage( true, "TabWindowMove" );
				}

				void Render( Skin::Base* skin )
				{
					skin->DrawTabTitleBar( this );
				}

				void DragAndDrop_StartDragging( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y )
				{
					DragAndDrop::SourceControl = GetParent();
					DragAndDrop::SourceControl->DragAndDrop_StartDragging( pPackage, x, y );
				}

				void UpdateFromTab( TabButton* pButton )
				{
					SetText( pButton->GetText() );
					SizeToContents();
				}

			private:

		};
	}
}
//------------------------------------------------------------------------