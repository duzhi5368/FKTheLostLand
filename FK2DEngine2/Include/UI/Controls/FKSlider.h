/**
*	created:		2013-4-12   15:03
*	filename: 		FKSlider
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKDragger.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT SliderBar : public ControlsInternal::Dragger
		{
				FK_CONTROL( SliderBar, ControlsInternal::Dragger );

				virtual void Render( Skin::Base* skin );
				virtual void SetHorizontal( bool b ) { m_bHorizontal = b; }
				virtual bool IsHorizontal() { return m_bHorizontal; }

			protected:

				bool m_bHorizontal;
		};
	}

	namespace Controls
	{

		class FK_EXPORT Slider : public Base
		{
				FK_CONTROL( Slider, Base );

				virtual void Render( Skin::Base* skin ) = 0;
				virtual void Layout( Skin::Base* skin );

				virtual void SetClampToNotches( bool bClamp ) { m_bClampToNotches = bClamp; }

				virtual void SetNotchCount( int num ) { m_iNumNotches = num; }
				virtual int GetNotchCount() { return m_iNumNotches; }

				virtual void SetRange( float fMin, float fMax );
				virtual float GetFloatValue();
				virtual void SetFloatValue( float val, bool forceUpdate = true );

				virtual float CalculateValue();
				virtual void OnMoved( Controls::Base* control );

				virtual void OnMouseClickLeft( int /*x*/, int /*y*/, bool /*bDown*/ ) {};

				virtual bool OnKeyRight( bool bDown )	{	if ( bDown ) { SetFloatValue( GetFloatValue() + 1, true ); } return true; }
				virtual bool OnKeyLeft( bool bDown )	{	if ( bDown ) { SetFloatValue( GetFloatValue() - 1, true ); } return true; }
				virtual bool OnKeyUp( bool bDown )		{	if ( bDown ) { SetFloatValue( GetFloatValue() + 1, true ); } return true; }
				virtual bool OnKeyDown( bool bDown )	{	if ( bDown ) { SetFloatValue( GetFloatValue() - 1, true ); } return true; }

				virtual void RenderFocus( FK2DEngine2::Skin::Base* skin );

				FK2DEngine2::Event::Caller	onValueChanged;

				virtual float GetMin() { return m_fMin; }
				virtual float GetMax() { return m_fMax; }

			protected:

				virtual void SetValueInternal( float fVal );
				virtual void UpdateBarFromValue() = 0;

				ControlsInternal::SliderBar* m_SliderBar;
				bool m_bClampToNotches;
				int m_iNumNotches;
				float m_fValue;

				float m_fMin;
				float m_fMax;

		};
	}


}
//------------------------------------------------------------------------