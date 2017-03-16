/**
*	created:		2013-4-12   17:21
*	filename: 		FKResizer
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
FK_CONTROL_CONSTRUCTOR( Resizer )
{
	m_iResizeDir = Pos::Left;
	SetMouseInputEnabled( true );
	SetSize( 6, 6 );
}

void Resizer::OnMouseMoved( int x, int y, int /*deltaX*/, int /*deltaY*/ )
{
	if ( !m_pTarget ) { return; }

	if ( !m_bDepressed ) { return; }

	FK2DEngine2::Rect pBounds = m_pTarget->GetBounds();
	FK2DEngine2::Point pntMin = m_pTarget->GetMinimumSize();
	FK2DEngine2::Point pCursorPos = m_pTarget->CanvasPosToLocal( FK2DEngine2::Point( x, y ) );
	FK2DEngine2::Point pDelta = m_pTarget->LocalPosToCanvas( m_HoldPos );
	pDelta.x -= x;
	pDelta.y -= y;

	if ( m_iResizeDir & Pos::Left )
	{
		pBounds.x -= pDelta.x;
		pBounds.w += pDelta.x;

		if ( pBounds.w < pntMin.x )
		{
			int diff = pntMin.x - pBounds.w;
			pBounds.w += diff;
			pBounds.x -= diff;
		}
	}

	if ( m_iResizeDir & Pos::Top )
	{
		pBounds.y -= pDelta.y;
		pBounds.h += pDelta.y;

		if ( pBounds.h < pntMin.y )
		{
			int diff = pntMin.y - pBounds.h;
			pBounds.h += diff;
			pBounds.y -= diff;
		}
	}

	if ( m_iResizeDir & Pos::Right )
	{
		int woff = pBounds.w - m_HoldPos.x;
		int diff = pBounds.w;
		pBounds.w = pCursorPos.x + woff;

		if ( pBounds.w < pntMin.x ) { pBounds.w = pntMin.x; }

		diff -= pBounds.w;
		m_HoldPos.x -= diff;
	}

	if ( m_iResizeDir & Pos::Bottom )
	{
		int hoff = pBounds.h - m_HoldPos.y;
		int diff = pBounds.h;
		pBounds.h = pCursorPos.y + hoff;

		if ( pBounds.h < pntMin.y ) { pBounds.h = pntMin.y; }

		diff -= pBounds.h;
		m_HoldPos.y -= diff;
	}

	m_pTarget->SetBounds( pBounds );
	onResize.Call( this );
}

void Resizer::SetResizeDir( int dir )
{
	m_iResizeDir = dir;

	if ( ( dir & Pos::Left && dir & Pos::Top ) || ( dir & Pos::Right && dir & Pos::Bottom ) )
	{ return SetCursor( FK2DEngine2::CursorType::SizeNWSE ); }

	if ( ( dir & Pos::Right && dir & Pos::Top ) || ( dir & Pos::Left && dir & Pos::Bottom ) )
	{ return SetCursor( FK2DEngine2::CursorType::SizeNESW ); }

	if ( dir & Pos::Right || dir & Pos::Left )
	{ return SetCursor( FK2DEngine2::CursorType::SizeWE ); }

	if ( dir & Pos::Top || dir & Pos::Bottom )
	{ return SetCursor( FK2DEngine2::CursorType::SizeNS ); }
}
//------------------------------------------------------------------------