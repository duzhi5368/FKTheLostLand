/**
*	created:		2013-4-12   14:45
*	filename: 		FKMenu
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
FK_CONTROL_CONSTRUCTOR( Menu )
{
	SetBounds( 0, 0, 10, 10 );
	SetPadding( Padding( 2, 2, 2, 2 ) );
	SetDisableIconMargin( false );
	SetAutoHideBars( true );
	SetScroll( false, true );
	SetDeleteOnClose( false );
}


void Menu::Render( Skin::Base* skin )
{
	skin->DrawMenu( this, IconMarginDisabled() );
}

void Menu::RenderUnder( Skin::Base* skin )
{
	BaseClass::RenderUnder( skin );
	skin->DrawShadow( this );
}

void Menu::Layout( Skin::Base* skin )
{
	int childrenHeight = 0;

	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = ( *it );

		if ( !pChild )
		{ continue; }

		childrenHeight += pChild->Height();
	}

	if ( Y() + childrenHeight > GetCanvas()->Height() )
	{ childrenHeight = GetCanvas()->Height() - Y(); }

	SetSize( Width(), childrenHeight );
	BaseClass::Layout( skin );
}

MenuItem* Menu::AddItem( const UITexObjSimpleInfo & strName, const UITexObjSimpleInfo & strIconName, const UITexObjSimpleInfo & strAccelerator )
{
	MenuItem* pItem = new MenuItem( this );
	pItem->SetPadding( Padding( 2, 4, 4, 4 ) );
	pItem->SetText( strName );
	pItem->SetImage( strIconName );
	pItem->SetAccelerator( strAccelerator );
	OnAddItem( pItem );
	return pItem;
}

void Menu::OnAddItem( MenuItem* item )
{
	item->SetTextPadding( Padding( IconMarginDisabled() ? 0 : 24, 0, 16, 0 ) );
	item->Dock( Pos::Top );
	item->SizeToContents();
	item->SetAlignment( Pos::CenterV | Pos::Left );
	item->onHoverEnter.Add( this, &Menu::OnHoverItem );

	int w = item->Width() + 10 + 32;
	if ( w < Width() ) { w = Width(); }

	SetSize( w, Height() );
}

void Menu::ClearItems()
{
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = *it;

		if ( !pChild ) { continue; }

		pChild->DelayedDelete();
	}
}

void Menu::CloseAll()
{
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = *it;
		MenuItem* pItem = fk_cast<MenuItem> ( pChild );

		if ( !pItem ) { continue; }

		pItem->CloseMenu();
	}
}

bool Menu::IsMenuOpen()
{
	for ( Base::List::iterator it = m_InnerPanel->Children.begin(); it != m_InnerPanel->Children.end(); ++it )
	{
		Base* pChild = *it;
		MenuItem* pItem = fk_cast<MenuItem> ( pChild );

		if ( !pItem ) { continue; }

		if ( pItem->IsMenuOpen() )
		{ return true; }
	}

	return false;
}

void Menu::OnHoverItem( FK2DEngine2::Controls::Base* pControl )
{
	if ( !ShouldHoverOpenMenu() ) { return; }

	MenuItem* pItem = fk_cast<MenuItem> ( pControl );

	if ( !pItem ) { return; }

	if ( pItem->IsMenuOpen() ) { return; }

	CloseAll();
	pItem->OpenMenu();
}

void Menu::Open( unsigned int iPos )
{
	SetHidden( false );
	BringToFront();
	FK2DEngine2::Point MousePos = Input::GetMousePosition();
	SetPos( MousePos.x, MousePos.y );
}

void Menu::Close()
{
	SetHidden( true );

	if ( DeleteOnClose() )
	{
		DelayedDelete();
	}
}

void Menu::CloseMenus()
{
	BaseClass::CloseMenus();
	CloseAll();
	Close();
}

void Menu::AddDivider()
{
	MenuDivider* divider = new MenuDivider( this );
	divider->Dock( Pos::Top );
	divider->SetMargin( Margin( IconMarginDisabled() ? 0 : 24, 0, 4, 0 ) );
}

void MenuDivider::Render( FK2DEngine2::Skin::Base* skin )
{
	skin->DrawMenuDivider( this );
}
//------------------------------------------------------------------------