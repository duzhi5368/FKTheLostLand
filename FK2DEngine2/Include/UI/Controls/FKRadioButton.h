/**
*	created:		2013-4-12   18:04
*	filename: 		FKRadioButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "FKButton.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKCheckBox.h"
#include "FKLabelClickable.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT RadioButton : public CheckBox
		{
				FK_CONTROL( RadioButton, CheckBox );
				virtual void Render( Skin::Base* skin );

			private:

				virtual bool AllowUncheck() { return false; }
		};

		class FK_EXPORT LabeledRadioButton : public Base
		{
			public:

				FK_CONTROL_INLINE( LabeledRadioButton, Base )
				{
					SetSize( 200, 19 );
					m_RadioButton = new RadioButton( this );
					m_RadioButton->Dock( Pos::Left );
					m_RadioButton->SetMargin( Margin( 0, 2, 2, 2 ) );
					m_RadioButton->SetTabable( false );
					m_RadioButton->SetKeyboardInputEnabled( false );
					m_Label = new LabelClickable( this );
					m_Label->SetAlignment( Pos::CenterV | Pos::Left );
					m_Label->SetText( "Radio Button" );
					m_Label->Dock( Pos::Fill );
					m_Label->onPress.Add( m_RadioButton, &CheckBox::OnPress );
					m_Label->SetTabable( false );
					m_Label->SetKeyboardInputEnabled( false );
				}

				void RenderFocus( FK2DEngine2::Skin::Base* skin )
				{
					if ( FK2DEngine2::KeyboardFocus != this ) { return; }

					if ( !IsTabable() ) { return; }

					skin->DrawKeyboardHighlight( this, GetRenderBounds(), 0 );
				}

				virtual RadioButton*	GetRadioButton() { return m_RadioButton; }
				virtual LabelClickable*	GetLabel() { return m_Label; }
				virtual bool OnKeySpace( bool bDown ) { if ( bDown )  { m_RadioButton->SetChecked( !m_RadioButton->IsChecked() ); } return true;  }

				virtual void Select() { m_RadioButton->SetChecked( true ); }

			private:

				RadioButton*		m_RadioButton;
				LabelClickable*		m_Label;
		};
	}
}
//------------------------------------------------------------------------