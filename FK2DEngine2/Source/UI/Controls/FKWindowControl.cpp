/**
*	created:		2013-4-12   23:07
*	filename: 		FKWindowControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/UI/Controls/FKWindowControl.h"
#include "../../../Include/UI/Controls/FKImagePanel.h"
#include "../../../Include/UI/Controls/FKLabel.h"
#include "../../../Include/UI/Controls/FKModal.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( WindowControl )
{
	m_Modal = NULL;
	m_bDeleteOnClose = false;
	m_TitleBar = new Dragger( this );
	m_TitleBar->SetHeight( 24 );
	m_TitleBar->SetPadding( Padding( 0, 0, 0, 0 ) );
	m_TitleBar->SetMargin( Margin( 0, 0, 0, 4 ) );
	m_TitleBar->SetTarget( this );
	m_TitleBar->Dock( Pos::Top );
	m_Title = new Label( m_TitleBar );
	m_Title->SetAlignment( Pos::Left | Pos::CenterV );
	m_Title->SetText( "Window" );
	m_Title->Dock( Pos::Fill );
	m_Title->SetPadding( Padding( 8, 0, 0, 0 ) );
	m_Title->SetTextColor( GetSkin()->Colors.Window.TitleInactive );
	m_CloseButton = new FK2DEngine2::Controls::WindowCloseButton( m_TitleBar );
	m_CloseButton->SetText( "" );
	m_CloseButton->Dock( Pos::Right );
	m_CloseButton->onPress.Add( this, &WindowControl::CloseButtonPressed );
	m_CloseButton->SetTabable( false );
	m_CloseButton->SetName( "closeButton" );
	m_CloseButton->SetWindow( this );
	m_InnerPanel = new Base( this );
	m_InnerPanel->Dock( Pos::Fill );
	m_bCanMove = true;
	GetResizer( 8 )->Hide();
	BringToFront();
	SetTabable( false );
	Focus();
	SetMinimumSize( FK2DEngine2::Point( 100, 40 ) );
	SetClampMovement( true );
	SetKeyboardInputEnabled( false );
}


WindowControl::~WindowControl()
{
	DestroyModal();
}

void WindowControl::MakeModal( bool bDrawBackground )
{
	if ( m_Modal ) { return; }

	m_Modal = new ControlsInternal::Modal( GetCanvas() );
	SetParent( m_Modal );
	m_Modal->SetShouldDrawBackground( bDrawBackground );
}

void WindowControl::DestroyModal()
{
	if ( !m_Modal ) { return; }

	SetParent( GetCanvas() );
	m_Modal->DelayedDelete();
	m_Modal = NULL;
}

bool WindowControl::IsOnTop()
{
	for ( Base::List::reverse_iterator iter = GetParent()->Children.rbegin(); iter != GetParent()->Children.rend(); ++iter )
	{
		WindowControl* pWindow = fk_cast<WindowControl> ( *iter );

		if ( !pWindow )
		{ continue; }

		if ( pWindow == this )
		{ return true; }

		return false;
	}

	return false;
}

void WindowControl::Moveable( bool moveable )
{
	m_bCanMove = moveable;
	if( moveable )
	{
		m_TitleBar->SetTarget( this );	
	}
	else
	{
		m_TitleBar->SetTarget( NULL );
	}
}

void WindowControl::Render( Skin::Base* skin )
{
	bool bHasFocus = IsOnTop();

	if ( bHasFocus )
	{ m_Title->SetTextColor( GetSkin()->Colors.Window.TitleActive ); }
	else
	{ m_Title->SetTextColor( GetSkin()->Colors.Window.TitleInactive ); }

	skin->DrawWindow( this, m_TitleBar->Bottom(), bHasFocus );
}

void WindowControl::RenderUnder( Skin::Base* skin )
{
	BaseClass::RenderUnder( skin );
	skin->DrawShadow( this );
}

void WindowControl::SetTitle( FK2DEngine2::UnicodeString title )
{
	m_Title->SetText( title );
}

void WindowControl::SetClosable( bool closeable )
{
	m_CloseButton->SetHidden( !closeable );
}

void WindowControl::SetHidden( bool hidden )
{
	if ( !hidden )
	{ BringToFront(); }

	BaseClass::SetHidden( hidden );
}

void WindowControl::Touch()
{
	BaseClass::Touch();
	BringToFront();
}

void WindowControl::CloseButtonPressed()
{
	DestroyModal();
	onWindowClosed.Call( this );
	SetHidden( true );

	if ( m_bDeleteOnClose )
	{ DelayedDelete(); }
}


void WindowControl::RenderFocus( FK2DEngine2::Skin::Base* /*skin*/ )
{
}
//------------------------------------------------------------------------