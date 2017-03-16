/**
*	created:		2013-4-12   15:51
*	filename: 		FKComboBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBaseProperty.h"
#include "../FKComboBox.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class FK_EXPORT ComboBox : public Property::Base
			{
				public:

					FK_CONTROL_INLINE( ComboBox, Property::Base )
					{
						m_ComboBox = new FK2DEngine2::Controls::ComboBox( this );
						m_ComboBox->Dock( Pos::Fill );
						m_ComboBox->onSelection.Add( this, &BaseClass::OnPropertyValueChanged );
						m_ComboBox->SetTabable( true );
						m_ComboBox->SetKeyboardInputEnabled( true );
						m_ComboBox->SetShouldDrawBackground( false );
						SetHeight( 18 );
					}

					virtual UITexObjSimpleInfo GetPropertyValue()
					{
						FK2DEngine2::Controls::Label* pControl = m_ComboBox->GetSelectedItem();

						if ( !pControl ) { return L""; }

						return pControl->GetName();
					}

					virtual void SetPropertyValue( const UITexObjSimpleInfo & v, bool bFireChangeEvents )
					{
						m_ComboBox->SelectItemByName( v.Get(), bFireChangeEvents );
					}

					virtual bool IsEditing()
					{
						return m_ComboBox->HasFocus();
					}

					virtual bool IsHovered()
					{
						return BaseClass::IsHovered() || m_ComboBox->IsHovered();
					}

					FK2DEngine2::Controls::ComboBox* GetComboBox()
					{
						return m_ComboBox;
					}

				protected:

					FK2DEngine2::Controls::ComboBox* m_ComboBox;
			};
		}
	}
}
//------------------------------------------------------------------------