/**
*	created:		2013-4-12   17:51
*	filename: 		FKProgressBar
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
class ProgressBarThink : public FK2DEngine2::Anim::Animation
{
	public:

		ProgressBarThink()
		{
			m_fLastFrame = 0.0f;
		}

		virtual void Think()
		{
			float fDiff = Platform::GetTimeInSeconds() - m_fLastFrame;
			fk_cast<ProgressBar> ( m_Control )->CycleThink( FK2DEngine2::Clamp( fDiff, 0.f, 0.3f ) );
			m_fLastFrame = Platform::GetTimeInSeconds();
		}


		float	m_fLastFrame;
};
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( ProgressBar )
{
	SetMouseInputEnabled( true );
	SetBounds( FK2DEngine2::Rect( 0, 0, 128, 32 ) );
	SetTextPadding( Padding( 3, 3, 3, 3 ) );
	SetHorizontal();
	SetAlignment( FK2DEngine2::Pos::Center );
	m_fProgress = 0.0f;
	m_bAutoLabel = true;
	m_fCycleSpeed = 0.0f;
	FK2DEngine2::Anim::Add( this, new ProgressBarThink() );
}

void ProgressBar::SetValue( float val )
{
	if ( val < 0 )
	{ val = 0; }

	if ( val > 1 )
	{ val = 1; }

	m_fProgress = val;

	if ( m_bAutoLabel )
	{
		int displayVal = m_fProgress * 100;
		SetText( Utility::ToString( displayVal ) + "%" );
	}
}

void ProgressBar::CycleThink( float fDelta )
{
	if ( !Visible() ) { return; }

	if ( m_fCycleSpeed == 0.0f ) { return; }

	m_fProgress += m_fCycleSpeed * fDelta;

	if ( m_fProgress < 0.0f ) { m_fProgress += 1.0f; }

	if ( m_fProgress > 1.0f ) { m_fProgress -= 1.0f; }

	Redraw();
}

void ProgressBar::Render( Skin::Base* skin )
{
	skin->DrawProgressBar( this, m_bHorizontal, m_fProgress );
}

float ProgressBar::GetCycleSpeed()
{
	return m_fCycleSpeed;
}

void ProgressBar::SetCycleSpeed( float f )
{
	m_fCycleSpeed = f;
}
//------------------------------------------------------------------------