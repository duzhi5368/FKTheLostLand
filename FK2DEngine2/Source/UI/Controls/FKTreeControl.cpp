/**
*	created:		2013-4-12   17:58
*	filename: 		FKTreeControl
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
FK_CONTROL_CONSTRUCTOR( TreeControl )
{
	m_TreeControl = this;
	m_ToggleButton->DelayedDelete();
	m_ToggleButton = NULL;
	m_Title->DelayedDelete();
	m_Title = NULL;
	m_InnerPanel->DelayedDelete();
	m_InnerPanel = NULL;
	m_bAllowMultipleSelection = false;
	m_ScrollControl = new ScrollControl( this );
	m_ScrollControl->Dock( Pos::Fill );
	m_ScrollControl->SetScroll( false, true );
	m_ScrollControl->SetAutoHideBars( true );
	m_ScrollControl->SetMargin( Margin( 1, 1, 1, 1 ) );
	m_InnerPanel = m_ScrollControl;
	m_ScrollControl->SetInnerSize( 1000, 1000 );
}

void TreeControl::Render( Skin::Base* skin )
{
	if ( ShouldDrawBackground() )
	{ skin->DrawTreeControl( this ); }
}

void TreeControl::OnChildBoundsChanged( FK2DEngine2::Rect /*oldChildBounds*/, Base* /*pChild*/ )
{
	m_ScrollControl->UpdateScrollBars();
	Invalidate();
}

void TreeControl::Clear()
{
	m_ScrollControl->Clear();
}

void TreeControl::Layout( Skin::Base* skin )
{
	BaseClass::BaseClass::Layout( skin );
}

void TreeControl::PostLayout( Skin::Base* skin )
{
	BaseClass::BaseClass::PostLayout( skin );
}

void TreeControl::OnNodeAdded( TreeNode* pNode )
{
	pNode->onNamePress.Add( this, &TreeControl::OnNodeSelection );
}

void TreeControl::OnNodeSelection( Controls::Base* /*control*/ )
{
	if ( !m_bAllowMultipleSelection || !FK2DEngine2::Input::IsKeyDown( Key::Control ) )
	{ DeselectAll(); }
}
//------------------------------------------------------------------------