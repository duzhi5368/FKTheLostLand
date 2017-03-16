/**
*	created:		2013-4-12   17:50
*	filename: 		FKProgressBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT ProgressBar : public Label
		{
			public:

				FK_CONTROL( ProgressBar, Label );

				virtual void Render( Skin::Base* skin );

				virtual void SetVertical()  { m_bHorizontal = false; }
				virtual void SetHorizontal() { m_bHorizontal = true; }

				virtual void SetValue( float val );
				virtual float GetValue() const { return m_fProgress; }

				virtual void SetAutoLabel( bool b ) { m_bAutoLabel = b; }

				virtual float GetCycleSpeed();
				virtual void SetCycleSpeed( float f );

				virtual void CycleThink( float fDelta );

			protected:

				float m_fProgress;
				float m_fCycleSpeed;

				bool m_bHorizontal;
				bool m_bAutoLabel;
		};
	}
}
//------------------------------------------------------------------------