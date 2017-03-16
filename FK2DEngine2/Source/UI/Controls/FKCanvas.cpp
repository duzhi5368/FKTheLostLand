/**
*	created:		2013-4-12   15:56
*	filename: 		FKCanvas
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
Canvas::Canvas( FK2DEngine2::Skin::Base* pSkin ) : BaseClass( NULL ), m_bAnyDelete( false )
{
	SetBounds( 0, 0, 10000, 10000 );
	SetScale( 1.0f );
	SetBackgroundColor( Color( 255, 255, 255, 0 ) );
	SetDrawBackground( false );

	if ( pSkin ) { SetSkin( pSkin ); }
}

Canvas::~Canvas()
{
	ReleaseChildren();
}

void Canvas::RenderCanvas()
{
	DoThink();
	FK2DEngine2::video::Base* render = m_Skin->GetRender();
	render->Begin();
	RecurseLayout( m_Skin );
	render->SetClipRegion( GetBounds() );
	render->SetRenderOffset( FK2DEngine2::Point( 0, 0 ) );
	render->SetScale( Scale() );

	if ( m_bDrawBackground )
	{
		render->SetDrawColor( m_BackgroundColor );
		render->DrawFilledRect( GetRenderBounds() );
	}

	DoRender( m_Skin );
	DragAndDrop::RenderOverlay( this, m_Skin );
	ToolTip::RenderToolTip( m_Skin );
	render->End();
}

void Canvas::Render( FK2DEngine2::Skin::Base* /*pRender*/ )
{
	m_bNeedsRedraw = false;
}

void Canvas::OnBoundsChanged( FK2DEngine2::Rect oldBounds )
{
	BaseClass::OnBoundsChanged( oldBounds );
	InvalidateChildren( true );
}


void Canvas::DoThink()
{
	ProcessDelayedDeletes();

	if ( Hidden() ) { return; }

	FK2DEngine2::Anim::Think();
	{
		NextTab = NULL;
		FirstTab = NULL;
	}
	ProcessDelayedDeletes();

	RecurseLayout( m_Skin );

	if ( NextTab == NULL )
	{ NextTab = FirstTab; }

	FK2DEngine2::Input::OnCanvasThink( this );
}

void Canvas::SetScale( float f )
{
	if ( m_fScale == f ) { return; }

	m_fScale = f;

	if ( m_Skin && m_Skin->GetRender() )
	{ m_Skin->GetRender()->SetScale( m_fScale ); }

	OnScaleChanged();
	Redraw();
}

void Canvas::AddDelayedDelete( FK2DEngine2::Controls::Base* pControl )
{
	if ( !m_bAnyDelete || m_DeleteSet.find( pControl ) == m_DeleteSet.end() )
	{
		m_bAnyDelete = true;
		m_DeleteSet.insert( pControl );
		m_DeleteList.push_back( pControl );
	}
}

void Canvas::PreDeleteCanvas( Controls::Base* pControl )
{
	if ( m_bAnyDelete )
	{
		std::set< Controls::Base* >::iterator itFind;

		if ( ( itFind = m_DeleteSet.find( pControl ) ) != m_DeleteSet.end() )
		{
			m_DeleteList.remove( pControl );
			m_DeleteSet.erase( pControl );
			m_bAnyDelete = !m_DeleteSet.empty();
		}
	}
}

void Canvas::ProcessDelayedDeletes()
{
	while ( m_bAnyDelete )
	{
		m_bAnyDelete = false;
		Controls::Base::List deleteList = m_DeleteList;
		m_DeleteList.clear();
		m_DeleteSet.clear();

		for ( FK2DEngine2::Controls::Base::List::iterator it = deleteList.begin(); it != deleteList.end(); ++it )
		{
			FK2DEngine2::Controls::Base* pControl = *it;
			pControl->PreDelete( GetSkin() );
			delete pControl;
			Redraw();
		}
	}
}

void Canvas::ReleaseChildren()
{
	Base::List::iterator iter = Children.begin();

	while ( iter != Children.end() )
	{
		Base* pChild = *iter;
		iter = Children.erase( iter );
		delete pChild;
	}
}

bool Canvas::InputMouseMoved( int x, int y, int deltaX, int deltaY )
{
	if ( Hidden() ) { return false; }

	if ( ToolTip::TooltipActive() )
	{ Redraw(); }

	// Todo: Handle scaling here..
	//float fScale = 1.0f / Scale();
	FK2DEngine2::Input::OnMouseMoved( this, x, y, deltaX, deltaY );

	if ( !FK2DEngine2::HoveredControl ) { return false; }

	if ( FK2DEngine2::HoveredControl == this ) { return false; }

	if ( FK2DEngine2::HoveredControl->GetCanvas() != this ) { return false; }

	FK2DEngine2::HoveredControl->OnMouseMoved( x, y, deltaX, deltaY );
	FK2DEngine2::HoveredControl->UpdateCursor();
	DragAndDrop::OnMouseMoved( FK2DEngine2::HoveredControl, x, y );
	return true;
}

bool Canvas::InputMouseButton( int iButton, bool bDown )
{
	if ( Hidden() ) { return false; }

	return FK2DEngine2::Input::OnMouseClicked( this, iButton, bDown );
}

bool Canvas::InputKey( int iKey, bool bDown )
{
	if ( Hidden() ) { return false; }

	if ( iKey <= FK2DEngine2::Key::Invalid ) { return false; }

	if ( iKey >= FK2DEngine2::Key::Count ) { return false; }

	return FK2DEngine2::Input::OnKeyEvent( this, iKey, bDown );
}

bool Canvas::InputCharacter( FK2DEngine2::UnicodeChar chr )
{
	if ( Hidden() ) { return false; }

	if ( !iswprint( chr ) ) { return false; }

	//Handle Accelerators
	if ( FK2DEngine2::Input::HandleAccelerator( this, chr ) )
	{ return true; }

	//Handle characters
	if ( !FK2DEngine2::KeyboardFocus ) { return false; }

	if ( FK2DEngine2::KeyboardFocus->GetCanvas() != this ) { return false; }

	if ( !FK2DEngine2::KeyboardFocus->Visible() ) { return false; }

	if ( FK2DEngine2::Input::IsControlDown() ) { return false; }

	return KeyboardFocus->OnChar( chr );
}

bool Canvas::InputMouseWheel( int val )
{
	if ( Hidden() ) { return false; }

	if ( !FK2DEngine2::HoveredControl ) { return false; }

	if ( FK2DEngine2::HoveredControl == this ) { return false; }

	if ( FK2DEngine2::HoveredControl->GetCanvas() != this ) { return false; }

	return FK2DEngine2::HoveredControl->OnMouseWheeled( val );
}