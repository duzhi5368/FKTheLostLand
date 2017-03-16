/**
*	created:		2013-4-12   15:52
*	filename: 		FKFile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKProperties.h"
#include "../FKButton.h"
#include "FKFolder.h"
#include "../Dialogs/FKFolderOpen.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class File : public Property::Text
			{
				FK_CONTROL_INLINE( File, Property::Text )
				{
					Controls::Button* pButton = new Controls::Button( this );
					pButton->Dock( Pos::Right );
					pButton->SetText( "..." );
					pButton->SetWidth( 20 );
					pButton->onPress.Add( this, &ThisClass::OnButtonPress );
					pButton->SetMargin( Margin( 1, 1, 1, 2 ) );
					m_strDialogName = "Find File";
					m_strFileExtension = "*.*";
				}

				File* SetExtension( const FK2DEngine2::String & wstring )
				{
					m_strFileExtension = wstring;
					return this;
				}

				void OnButtonPress( Controls::Base* control )
				{
					FK2DEngine2::Dialogs::FileOpen( true, m_strDialogName, m_TextBox->GetText().Get(), m_strFileExtension, this, &Folder::EventFilePicked );
				}

				void EventFilePicked( const FK2DEngine2::UITexObjSimpleInfo & wstring )
				{
					m_TextBox->SetText( wstring );
				}


				String	m_strDialogName;
				String	m_strFileExtension;

			};
		}
	}
}
//------------------------------------------------------------------------