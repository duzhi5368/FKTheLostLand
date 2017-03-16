/**
*	created:		2013-4-12   18:06
*	filename: 		FKRadioButton
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
FK_CONTROL_CONSTRUCTOR( RadioButton )
{
	SetSize( 15, 15 );
	SetMouseInputEnabled( true );
	SetTabable( false );
}

void RadioButton::Render( Skin::Base* skin )
{
	skin->DrawRadioButton( this, IsChecked(), IsDepressed() );
}
//------------------------------------------------------------------------