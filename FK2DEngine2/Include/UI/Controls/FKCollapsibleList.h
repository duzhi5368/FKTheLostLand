/**
*	created:		2013-4-12   16:00
*	filename: 		FKCollapsibleList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKScrollControl.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKCollapsibleCategory.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT CollapsibleList : public FK2DEngine2::Controls::ScrollControl
		{
			public:

				FK2DEngine2::Event::Caller	onSelection;

			public:

				FK_CONTROL_INLINE( CollapsibleList, FK2DEngine2::Controls::ScrollControl )
				{
					SetScroll( false, true );
					SetAutoHideBars( true );
				}

				virtual void Add( FK2DEngine2::Controls::CollapsibleCategory* pCategory )
				{
					pCategory->SetParent( this );
					pCategory->Dock( Pos::Top );
					pCategory->SetMargin( Margin( 1, 0, 1, 1 ) );
					pCategory->SetList( this );
					pCategory->onSelection.Add( this, &ThisClass::OnSelectionEvent );
				}

				virtual FK2DEngine2::Controls::CollapsibleCategory* Add( const UITexObjSimpleInfo & name )
				{
					FK2DEngine2::Controls::CollapsibleCategory* pCategory = new CollapsibleCategory( this );
					pCategory->SetText( name );
					Add( pCategory );
					return pCategory;
				}

				virtual void Render( Skin::Base* skin )
				{
					skin->DrawCategoryHolder( this );
				}

				virtual void UnselectAll()
				{
					Base::List & children = GetChildren();

					for ( Base::List::iterator iter = children.begin(); iter != children.end(); ++iter )
					{
						FK2DEngine2::Controls::CollapsibleCategory* pChild = fk_cast<FK2DEngine2::Controls::CollapsibleCategory> ( *iter );

						if ( !pChild ) { continue; }

						pChild->UnselectAll();
					}
				}

				virtual FK2DEngine2::Controls::Button* GetSelected()
				{
					Base::List & children = GetChildren();

					for ( Base::List::iterator iter = children.begin(); iter != children.end(); ++iter )
					{
						FK2DEngine2::Controls::CollapsibleCategory* pChild = fk_cast<FK2DEngine2::Controls::CollapsibleCategory> ( *iter );

						if ( !pChild ) { continue; }

						FK2DEngine2::Controls::Button* pSelected = pChild->GetSelected();

						if ( pSelected ) { return pSelected; }
					}

					return NULL;
				}

			protected:

				virtual void OnSelection( FK2DEngine2::Controls::CollapsibleCategory* pControl, FK2DEngine2::Controls::Button* pSelected )
				{
					onSelection.Call( this );
				}

				void OnSelectionEvent( Controls::Base* pControl )
				{
					FK2DEngine2::Controls::CollapsibleCategory* pChild = fk_cast<FK2DEngine2::Controls::CollapsibleCategory> ( pControl );

					if ( !pChild ) { return; }

					OnSelection( pChild, pChild->GetSelected() );
				}
		};

	}
}
//------------------------------------------------------------------------