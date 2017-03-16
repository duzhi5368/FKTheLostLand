/**
*	created:		2013-4-12   15:35
*	filename: 		FKGroupBox
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
FK_CONTROL_CONSTRUCTOR( GroupBox )
{
	SetMouseInputEnabled( true );
	SetTextPadding( Padding( 10, 0, 0, 0 ) );
	SetAlignment( Pos::Top | Pos::Left );
	Invalidate();
	m_InnerPanel = new Base( this );
	m_InnerPanel->Dock( Pos::Fill );
	m_InnerMargin = 6;
}

void GroupBox::Layout( Skin::Base* skin )
{
	m_InnerPanel->SetMargin( Margin( m_InnerMargin, TextHeight() - 3 + m_InnerMargin, m_InnerMargin, m_InnerMargin ) );
	BaseClass::Layout( skin );
}


void GroupBox::Render( Skin::Base* skin )
{
	skin->DrawGroupBox( this, TextX(), TextHeight(), TextWidth() );
}
//------------------------------------------------------------------------