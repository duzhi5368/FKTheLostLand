/**
*	created:		2013-4-12   1:19
*	filename: 		FKText
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBaseProperty.h"
#include "../FKTextBox.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class FK_EXPORT Text : public Property::Base
			{
				public:

					FK_CONTROL_INLINE( Text, Property::Base )
					{
						m_TextBox = new TextBox( this );
						m_TextBox->Dock( Pos::Fill );
						m_TextBox->SetShouldDrawBackground( false );
						m_TextBox->onTextChanged.Add( this, &BaseClass::OnPropertyValueChanged );
					}

					virtual UITexObjSimpleInfo GetPropertyValue()
					{
						return m_TextBox->GetText();
					}

					virtual void SetPropertyValue( const UITexObjSimpleInfo & v, bool bFireChangeEvents )
					{
						m_TextBox->SetText( v, bFireChangeEvents );
					}

					virtual bool IsEditing()
					{
						return m_TextBox->HasFocus();
					}

					virtual bool IsHovered()
					{
						return BaseClass::IsHovered() || m_TextBox->IsHovered();
					}

					TextBox* m_TextBox;
			};
		}
	}
}
//------------------------------------------------------------------------