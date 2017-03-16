/**
*	created:		2013-4-12   1:00
*	filename: 		FKScrollBarBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( ScrollBarBar )
{
	RestrictToParent( true );
	SetTarget( this );
}

void ScrollBarBar::Render( Skin::Base* skin )
{
	skin->DrawScrollBarBar( this, m_bDepressed, IsHovered(), m_bHorizontal );
	BaseClass::Render( skin );
}

void ScrollBarBar::OnMouseMoved( int x, int y, int deltaX, int deltaY )
{
	BaseClass::OnMouseMoved( x, y, deltaX, deltaY );

	if ( !m_bDepressed )
	{ return; }

	InvalidateParent();
}

void ScrollBarBar::OnMouseClickLeft( int x, int y, bool bDown )
{
	BaseClass::OnMouseClickLeft( x, y, bDown );
	InvalidateParent();
}

void ScrollBarBar::Layout( Skin::Base* /*skin*/ )
{
	if ( !GetParent() )
	{ return; }

	MoveTo( X(), Y() );
}

void ScrollBarBar::MoveTo( int x, int y )
{
	BaseClass::MoveTo( x, y );
}
//------------------------------------------------------------------------