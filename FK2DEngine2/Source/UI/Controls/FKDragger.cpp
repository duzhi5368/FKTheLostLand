/**
*	created:		2013-4-12   13:05
*	filename: 		FKDragger
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( Dragger )
{
	m_pTarget = NULL;
	SetMouseInputEnabled( true );
	m_bDepressed = false;
	m_bDoMove = true;
}

void Dragger::OnMouseClickLeft( int x, int y, bool bDown )
{
	if ( bDown )
	{
		m_bDepressed = true;

		if ( m_pTarget )
		{ m_HoldPos = m_pTarget->CanvasPosToLocal( FK2DEngine2::Point( x, y ) ); }

		FK2DEngine2::MouseFocus = this;
		onDragStart.Call( this );
	}
	else
	{
		m_bDepressed = false;
		FK2DEngine2::MouseFocus = NULL;
	}
}

void Dragger::OnMouseMoved( int x, int y, int deltaX, int deltaY )
{
	if ( !m_bDepressed ) { return; }

	if ( m_bDoMove && m_pTarget )
	{
		FK2DEngine2::Point p = FK2DEngine2::Point( x - m_HoldPos.x, y - m_HoldPos.y );

		// Translate to parent
		if ( m_pTarget->GetParent() )
		{ p = m_pTarget->GetParent()->CanvasPosToLocal( p ); }

		m_pTarget->MoveTo( p.x, p.y );
	}

	FK2DEngine2::Event::Information info;
	info.Point = FK2DEngine2::Point( deltaX, deltaY );
	onDragged.Call( this, info );
}

void Dragger::Render( Skin::Base* skin )
{
	//skin->DrawButton(this,false,false, false);
}

void Dragger::OnMouseDoubleClickLeft( int x, int y )
{
	onDoubleClickLeft.Call( this );
}
//------------------------------------------------------------------------