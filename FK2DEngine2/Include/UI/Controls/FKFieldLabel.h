/**
*	created:		2013-4-12   17:25
*	filename: 		FKFieldLabel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKLabel.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT FieldLabel : public Controls::Label
		{
			public:

				static inline FieldLabel* Setup( Controls::Base* pControl, const FK2DEngine2::UITexObjSimpleInfo & text )
				{
					FieldLabel* plbl = new FieldLabel( pControl->GetParent() );
					plbl->SetText( text );
					plbl->SetSize( pControl->Width(), pControl->Height() );
					plbl->Dock( pControl->GetDock() );
					plbl->SetField( pControl );
					return plbl;
				}

			public:

				FK_CONTROL_INLINE( FieldLabel, Controls::Label )
				{
					m_pField = NULL;
					SetMargin( Margin( 0, 1, 0, 1 ) );
					SetAlignment( Pos::CenterV | Pos::Left );
				}

				void SetField( Controls::Base* pField )
				{
					pField->SetParent( this );
					pField->Dock( Pos::Right );
					m_pField = pField;
				}

				void Layout( FK2DEngine2::Skin::Base* pskin )
				{
					m_pField->SetWidth( Width() - 70 );
					BaseClass::Layout( pskin );
				}

			protected:

				Controls::Base* m_pField;

		};
	}
}
//------------------------------------------------------------------------