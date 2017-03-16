/**
*	created:		2013-4-12   21:03
*	filename: 		FKRectangle
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
FK_CONTROL_CONSTRUCTOR( Rectangle )
{
	m_Color = FK2DEngine2::Color( 255, 255, 255, 255 );
}

void Rectangle::Render( Skin::Base* skin )
{
	skin->GetRender()->SetDrawColor( m_Color );
	skin->GetRender()->DrawFilledRect( GetRenderBounds() );
}
//------------------------------------------------------------------------