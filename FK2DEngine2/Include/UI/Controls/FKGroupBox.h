/**
*	created:		2013-4-12   15:34
*	filename: 		FKGroupBox
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

		class FK_EXPORT GroupBox : public Label
		{
			public:

				FK_CONTROL( GroupBox, Label );

				virtual void Render( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );

				virtual void SetInnerMargin( int i ) { m_InnerMargin = i; }

			protected:

				int	m_InnerMargin;

		};
	}
}
//------------------------------------------------------------------------