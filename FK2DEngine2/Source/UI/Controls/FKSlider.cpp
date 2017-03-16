/**
*	created:		2013-4-12   15:05
*	filename: 		FKSlider
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include <math.h>
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( SliderBar )
{
	SetTarget( this );
	RestrictToParent( true );
}

void SliderBar::Render( Skin::Base* skin )
{
	skin->DrawSlideButton( this, IsDepressed(), IsHorizontal() );
}


FK_CONTROL_CONSTRUCTOR( Slider )
{
	SetBounds( FK2DEngine2::Rect( 0, 0, 32, 128 ) );
	m_SliderBar = new SliderBar( this );
	m_SliderBar->onDragged.Add( this, &Slider::OnMoved );
	m_fMin = 0.0f;
	m_fMax = 1.0f;
	m_bClampToNotches = false;
	m_iNumNotches = 5;
	m_fValue = 0.0f;
	SetTabable( true );
}

void Slider::OnMoved( Controls::Base* /*control*/ )
{
	SetValueInternal( CalculateValue() );
}

void Slider::Layout( Skin::Base* skin )
{
	BaseClass::Layout( skin );
}

float Slider::CalculateValue()
{
	return 0;
}

void Slider::SetFloatValue( float val, bool /*forceUpdate*/ )
{
	if ( val < m_fMin ) { val = m_fMin; }

	if ( val > m_fMax ) { val = m_fMax; }

	val = ( val - m_fMin ) / ( m_fMax - m_fMin );
	SetValueInternal( val );
	Redraw();
}

void Slider::SetValueInternal( float val )
{
	if ( m_bClampToNotches )
	{
		val = floorf( ( val * ( float ) m_iNumNotches ) + 0.5f );
		val /= ( float ) m_iNumNotches;
	}

	if ( m_fValue != val )
	{
		m_fValue = val;
		onValueChanged.Call( this );
	}

	UpdateBarFromValue();
}

float Slider::GetFloatValue()
{
	return m_fMin + ( m_fValue * ( m_fMax - m_fMin ) );
}

void Slider::SetRange( float fMin, float fMax )
{
	m_fMin = fMin;
	m_fMax = fMax;
}

void Slider::RenderFocus( FK2DEngine2::Skin::Base* skin )
{
	if ( FK2DEngine2::KeyboardFocus != this ) { return; }

	if ( !IsTabable() ) { return; }

	skin->DrawKeyboardHighlight( this, GetRenderBounds(), 0 );
}
//------------------------------------------------------------------------