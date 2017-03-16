/**
*	created:		2013-4-13   21:47
*	filename: 		FKDockedTabControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( DockedTabControl )
{
	m_WindowControl = NULL;
	Dock( Pos::Fill );
	m_pTitleBar = new TabTitleBar( this );
	m_pTitleBar->Dock( Pos::Top );
	m_pTitleBar->SetHidden( true );
	SetAllowReorder( true );
}

void DockedTabControl::Layout( Skin::Base* skin )
{
	GetTabStrip()->SetHidden( TabCount() <= 1 );
	UpdateTitleBar();
	BaseClass::Layout( skin );
}

void DockedTabControl::UpdateTitleBar()
{
	if ( !GetCurrentButton() ) { return; }

	m_pTitleBar->UpdateFromTab( GetCurrentButton() );
}

void DockedTabControl::DragAndDrop_StartDragging( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y )
{
	BaseClass::DragAndDrop_StartDragging( pPackage, x, y );
	SetHidden( true );

	GetParent()->SetHidden( true );
}

void DockedTabControl::DragAndDrop_EndDragging( bool bSuccess, int /*x*/, int /*y*/ )
{
	SetHidden( false );

	if ( !bSuccess )
	{
		GetParent()->SetHidden( false );
	}
}

void DockedTabControl::MoveTabsTo( DockedTabControl* pTarget )
{
	Base::List Children = GetTabStrip()->Children;

	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		TabButton* pButton = fk_cast<TabButton> ( *iter );

		if ( !pButton ) { continue; }

		pTarget->AddPage( pButton );
	}

	Invalidate();
}
//------------------------------------------------------------------------