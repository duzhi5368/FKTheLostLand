/**
*	created:		2013-4-12   20:56
*	filename: 		FKRectangle
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

		class FK_EXPORT Rectangle : public Controls::Base
		{
			public:

				FK_CONTROL( Rectangle, Controls::Base );

				virtual void Render( Skin::Base* skin );

				const FK2DEngine2::Color & GetColor() { return m_Color; }
				void SetColor( const FK2DEngine2::Color & col ) { m_Color = col; }

			protected:

				FK2DEngine2::Color		m_Color;

		};
	}
}
//------------------------------------------------------------------------