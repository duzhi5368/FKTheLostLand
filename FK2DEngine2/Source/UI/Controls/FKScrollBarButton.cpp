/**
*	created:		2013-4-12   0:58
*	filename: 		FKScrollBarButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( ScrollBarButton )
{
	SetDirectionUp();
}

void ScrollBarButton::SetDirectionUp()
{
	m_iDirection = Pos::Top;
}

void ScrollBarButton::SetDirectionDown()
{
	m_iDirection = Pos::Bottom;
}

void ScrollBarButton::SetDirectionLeft()
{
	m_iDirection = Pos::Left;
}

void ScrollBarButton::SetDirectionRight()
{
	m_iDirection = Pos::Right;
}

void ScrollBarButton::Render( Skin::Base* skin )
{
	skin->DrawScrollButton( this, m_iDirection, m_bDepressed, IsHovered(), IsDisabled() );
}
//------------------------------------------------------------------------