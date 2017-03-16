/**
*	created:		2013-4-12   17:32
*	filename: 		FKMenuStrip
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
FK_CONTROL_CONSTRUCTOR( MenuStrip )
{
	SetBounds( 0, 0, 200, 22 );
	Dock( Pos::Top );
	m_InnerPanel->SetPadding( Padding( 5, 0, 0, 0 ) );
}

void MenuStrip::Render( Skin::Base* skin )
{
	skin->DrawMenuStrip( this );
}

void MenuStrip::Layout( Skin::Base* /*skin*/ )
{

}

void MenuStrip::OnAddItem( MenuItem* item )
{
	item->Dock( Pos::Left );
	item->SetTextPadding( Padding( 5, 0, 5, 0 ) );
	item->SetPadding( Padding( 10, 0, 10, 0 ) );
	item->SizeToContents();
	item->SetOnStrip( true );
	item->onHoverEnter.Add( this, &Menu::OnHoverItem );
}

bool MenuStrip::ShouldHoverOpenMenu()
{
	return IsMenuOpen();
}
//------------------------------------------------------------------------