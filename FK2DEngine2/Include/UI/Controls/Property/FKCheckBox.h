/**
*	created:		2013-4-13   20:58
*	filename: 		FKCheckBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBaseProperty.h"
#include "../FKCheckBox.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class FK_EXPORT Checkbox : public Property::Base
			{
				public:

					FK_CONTROL_INLINE( Checkbox, Property::Base )
					{
						m_Checkbox = new FK2DEngine2::Controls::CheckBox( this );
						m_Checkbox->SetShouldDrawBackground( false );
						m_Checkbox->onCheckChanged.Add( this, &BaseClass::OnPropertyValueChanged );
						m_Checkbox->SetTabable( true );
						m_Checkbox->SetKeyboardInputEnabled( true );
						m_Checkbox->SetPos( 2, 1 );
						SetHeight( 18 );
					}

					virtual UITexObjSimpleInfo GetPropertyValue()
					{
						return m_Checkbox->IsChecked() ? L"1" : L"0";
					}

					virtual void SetPropertyValue( const UITexObjSimpleInfo & v, bool bFireChangeEvents )
					{
						if ( v == L"1" || v == L"true" || v == L"TRUE" || v == L"yes" || v == L"YES" )
						{ return m_Checkbox->SetChecked( true ); }

						return m_Checkbox->SetChecked( false );
					}

					virtual bool IsEditing()
					{
						return m_Checkbox->HasFocus();
					}

					virtual bool IsHovered()
					{
						return BaseClass::IsHovered() || m_Checkbox->IsHovered();
					}

					FK2DEngine2::Controls::CheckBox* m_Checkbox;
			};
		}
	}
}
//------------------------------------------------------------------------