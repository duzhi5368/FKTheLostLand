/**
*	created:		2013-4-12   18:08
*	filename: 		FKCheckBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "FKLabelClickable.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{

		class FK_EXPORT CheckBox : public Button
		{
			public:

				FK_CONTROL( CheckBox, Button );

				virtual void Render( Skin::Base* skin );
				virtual void OnPress();

				virtual void SetChecked( bool Checked );
				virtual void Toggle() { SetChecked( !IsChecked() ); }
				virtual bool IsChecked() { return m_bChecked; }

				FK2DEngine2::Event::Caller	onChecked;
				FK2DEngine2::Event::Caller	onUnChecked;
				FK2DEngine2::Event::Caller	onCheckChanged;

			private:

				virtual bool AllowUncheck() { return true; }

				void OnCheckStatusChanged();

				bool m_bChecked;
		};

		class FK_EXPORT CheckBoxWithLabel : public Base
		{
			public:

				FK_CONTROL_INLINE( CheckBoxWithLabel, Base )
				{
					SetSize( 200, 19 );
					m_Checkbox = new CheckBox( this );
					m_Checkbox->Dock( Pos::Left );
					m_Checkbox->SetMargin( Margin( 0, 2, 2, 2 ) );
					m_Checkbox->SetTabable( false );
					m_Label = new LabelClickable( this );
					m_Label->Dock( Pos::Fill );
					m_Label->onPress.Add( m_Checkbox, &CheckBox::OnPress );
					m_Label->SetTabable( false );
					SetTabable( false );
				}

				virtual CheckBox* Checkbox() { return m_Checkbox; }
				virtual LabelClickable* Label() { return m_Label; }
				virtual bool OnKeySpace( bool bDown ) { if ( !bDown ) { m_Checkbox->SetChecked( !m_Checkbox->IsChecked() ); } return true; }

			private:

				CheckBox*		m_Checkbox;
				LabelClickable*	m_Label;
		};
	}
}
//------------------------------------------------------------------------