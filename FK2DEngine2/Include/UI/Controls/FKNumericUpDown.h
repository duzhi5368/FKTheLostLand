/**
*	created:		2013-4-12   17:38
*	filename: 		FKNumericUpDown
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKTextBox.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT NumericUpDownButton_Up : public Button
		{
				FK_CONTROL_INLINE( NumericUpDownButton_Up, Button )
				{
					SetSize( 7, 7 );
				}

				virtual void Render( Skin::Base* skin )
				{
					skin->DrawNumericUpDownButton( this, IsDepressed(), true );
				}
		};

		class FK_EXPORT NumericUpDownButton_Down : public Button
		{
				FK_CONTROL_INLINE( NumericUpDownButton_Down, Button )
				{
					SetSize( 7, 7 );
				}

				virtual void Render( Skin::Base* skin )
				{
					skin->DrawNumericUpDownButton( this, IsDepressed(), false );
				}
		};

		class FK_EXPORT NumericUpDown : public TextBoxNumeric
		{
			public:

				FK_CONTROL( NumericUpDown, TextBoxNumeric );

				virtual void SetMin( int i );
				virtual void SetMax( int i );
				virtual void SetValue( int i );

				Event::Caller	onChanged;

			private:

				virtual void OnEnter();
				virtual void OnChange();
				virtual void OnTextChanged();

				virtual void OnButtonUp( Base* control );
				virtual void OnButtonDown( Base* control );

				virtual bool OnKeyUp( bool bDown )	{	if ( bDown ) { OnButtonUp( NULL ); } return true;   }
				virtual bool OnKeyDown( bool bDown ) {	if ( bDown ) { OnButtonDown( NULL ); } return true; }

				virtual void SyncTextFromNumber();
				virtual void SyncNumberFromText();

				int m_iNumber;
				int m_iMax;
				int m_iMin;

		};
	}
}
//------------------------------------------------------------------------