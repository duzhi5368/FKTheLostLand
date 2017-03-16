/**
*	created:		2013-4-12   15:53
*	filename: 		FKFolder
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKProperties.h"
#include "../FKButton.h"
#include "../Dialogs/FKFolderOpen.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class Folder : public Property::Text
			{
				FK_CONTROL_INLINE( Folder, Property::Text )
				{
					Controls::Button* pButton = new Controls::Button( this );
					pButton->Dock( Pos::Right );
					pButton->SetText( "..." );
					pButton->SetWidth( 20 );
					pButton->onPress.Add( this, &ThisClass::OnButtonPress );
					pButton->SetMargin( Margin( 1, 1, 1, 2 ) );
					m_strDialogName = "Find Folder";
				}

				void OnButtonPress( Controls::Base* control )
				{
					FK2DEngine2::Dialogs::FolderOpen( true, m_strDialogName, m_TextBox->GetText().Get(), this, &Folder::EventFilePicked );
				}

				void EventFilePicked( Event::Info info )
				{
					m_TextBox->SetText( info.String );
				}


				String	m_strDialogName;

			};
		}
	}
}
//------------------------------------------------------------------------