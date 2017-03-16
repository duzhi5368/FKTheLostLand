/**
*	created:		2013-4-12   0:25
*	filename: 		FKCheckBox
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
FK_CONTROL_CONSTRUCTOR( CheckBox )
{
	SetSize( 15, 15 );
	m_bChecked = true;
	Toggle();
}
//------------------------------------------------------------------------
void CheckBox::Render( Skin::Base* skin )
{
	skin->DrawCheckBox( this, m_bChecked, IsDepressed() );
}
//------------------------------------------------------------------------
void CheckBox::OnPress()
{
	if ( IsDisabled() )
	{ return; }

	if ( IsChecked() && !AllowUncheck() )
	{ return; }

	Toggle();
}
//------------------------------------------------------------------------
void CheckBox::OnCheckStatusChanged()
{
	if ( IsChecked() )
	{
		onChecked.Call( this );
	}
	else
	{
		onUnChecked.Call( this );
	}

	onCheckChanged.Call( this );
}
//------------------------------------------------------------------------
void CheckBox::SetChecked( bool bChecked )
{
	if ( m_bChecked == bChecked ) { return; }

	m_bChecked = bChecked;
	OnCheckStatusChanged();
}
//------------------------------------------------------------------------