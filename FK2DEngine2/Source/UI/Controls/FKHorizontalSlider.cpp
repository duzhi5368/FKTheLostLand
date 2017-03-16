/**
*	created:		2013-4-12   15:32
*	filename: 		FKHorizontalSlider
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
FK_CONTROL_CONSTRUCTOR( HorizontalSlider )
{
	m_SliderBar->SetHorizontal( true );
}

float HorizontalSlider::CalculateValue()
{
	return ( float ) m_SliderBar->X() / ( float )( Width() - m_SliderBar->Width() );
}

void HorizontalSlider::UpdateBarFromValue()
{
	m_SliderBar->MoveTo( ( Width() - m_SliderBar->Width() ) * ( m_fValue ), m_SliderBar->Y() );
}

void HorizontalSlider::OnMouseClickLeft( int x, int y, bool bDown )
{
	m_SliderBar->MoveTo( CanvasPosToLocal( FK2DEngine2::Point( x, y ) ).x - m_SliderBar->Width() * 0.5,  m_SliderBar->Y() );
	m_SliderBar->OnMouseClickLeft( x, y, bDown );
	OnMoved( m_SliderBar );
}

void HorizontalSlider::Layout( Skin::Base* /*skin*/ )
{
	m_SliderBar->SetSize( 15, Height() );
}

void HorizontalSlider::Render( Skin::Base* skin )
{
	skin->DrawSlider( this, true, m_bClampToNotches ? m_iNumNotches : 0, m_SliderBar->Width() );
}
//------------------------------------------------------------------------