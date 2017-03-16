/**
*	created:		2013-4-12   18:17
*	filename: 		FKRadioButtonController
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
FK_CONTROL_CONSTRUCTOR( RadioButtonController )
{
	m_Selected = NULL;
	SetTabable( false );
	SetKeyboardInputEnabled( false );
}

void RadioButtonController::OnRadioClicked( FK2DEngine2::Controls::Base* pFromPanel )
{
	RadioButton* pCheckedRadioButton = fk_cast<RadioButton> ( pFromPanel );

	for ( Base::List::iterator iter = Children.begin(); iter != Children.end(); ++iter )
	{
		Base* pChild = *iter;
		LabeledRadioButton* pLRB = fk_cast<LabeledRadioButton> ( pChild );

		if ( pLRB )
		{
			RadioButton* pChildRadioButton = pLRB->GetRadioButton();

			if ( pChildRadioButton == pCheckedRadioButton )
			{
				m_Selected = pLRB;
			}
			else
			{
				pLRB->GetRadioButton()->SetChecked( false );
			}
		}
	}

	OnChange();
}

void RadioButtonController::OnChange()
{
	onSelectionChange.Call( this );
}

LabeledRadioButton* RadioButtonController::AddOption( const FK2DEngine2::String & strText, const FK2DEngine2::String & strOptionName )
{
	return AddOption( FK2DEngine2::Utility::StringToUnicode( strText ), strOptionName );
}

LabeledRadioButton* RadioButtonController::AddOption( const FK2DEngine2::UnicodeString & strText, const FK2DEngine2::String & strOptionName )
{
	LabeledRadioButton* lrb = new LabeledRadioButton( this );
	lrb->SetName( strOptionName );
	lrb->GetLabel()->SetText( strText );
	lrb->GetRadioButton()->onChecked.Add( this, &RadioButtonController::OnRadioClicked );
	lrb->Dock( Pos::Top );
	lrb->SetMargin( Margin( 0, 1, 0, 1 ) );
	lrb->SetKeyboardInputEnabled( false );
	lrb->SetTabable( false );
	Invalidate();
	return lrb;
}
//------------------------------------------------------------------------