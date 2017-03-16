/**
*	created:		2013-4-12   18:15
*	filename: 		FKRadioButtonController
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "FKRadioButton.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT RadioButtonController : public Base
		{
			public:

				FK_CONTROL( RadioButtonController, Base );

				virtual void Render( Skin::Base* /*skin*/ ) {};
				virtual void OnRadioClicked( Base* pFromPanel );

				virtual void OnChange();

				virtual LabeledRadioButton* AddOption( const FK2DEngine2::String & strText, const FK2DEngine2::String & strOptionName = "" );
				virtual LabeledRadioButton* AddOption( const FK2DEngine2::UnicodeString & strText, const FK2DEngine2::String & strOptionName = "" );

				virtual LabeledRadioButton*	GetSelected() { return m_Selected; }

				virtual const FK2DEngine2::String & GetSelectedName() { return m_Selected->GetName(); }
				virtual const UITexObjSimpleInfo & GetSelectedLabel() { return m_Selected->GetLabel()->GetText(); }

				Event::Caller		onSelectionChange;

			private:

				LabeledRadioButton* m_Selected;
		};
	}
}
//------------------------------------------------------------------------