/**
*	created:		2013-4-12   17:28
*	filename: 		FKFolderPicker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "Dialogs/FKFolderOpen.h"
#include "FKTextBox.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT FolderPicker : public Controls::Base
		{
			public:

				FK_CONTROL_INLINE( FolderPicker, Controls::Base )
				{
					m_Button = new Controls::Button( this );
					m_Button->Dock( Pos::Right );
					m_Button->SetMargin( Margin( 2, 0, 0, 0 ) );
					m_Button->SetText( ".." );
					m_Button->SetSize( 20, 20 );
					m_Button->onPress.Add( this, &FolderPicker::OnBrowse );
					m_TextBox = new Controls::TextBox( this );
					m_TextBox->Dock( Pos::Fill );
					this->SetSize( 100, 20 );
					m_BrowseName = "Find Folder";
				}

				void SetFolder( const UITexObjSimpleInfo & strValue )
				{
					m_TextBox->SetText( strValue );
					m_TextBox->MoveCaretToEnd();
					onFolderChanged.Call( this );
				}

				const FK2DEngine2::UITexObjSimpleInfo & GetFolder()
				{
					return m_TextBox->GetText();
				}

				void OnBrowse()
				{
					FK2DEngine2::Dialogs::FolderOpen( true, "Name", GetFolder().Get(), this, &FolderPicker::SetFolderCallback );
				}

				virtual UITexObjSimpleInfo GetValue() { return GetFolder(); }
				virtual void SetValue( const UITexObjSimpleInfo & strValue ) { return SetFolder( strValue ); }

				Event::Caller	onFolderChanged;

			private:

				void SetFolderCallback( FK2DEngine2::Event::Info info )
				{
					SetFolder( info.String );
				}

				Controls::TextBox*	m_TextBox;
				Controls::Button*	m_Button;
				FK2DEngine2::String		m_BrowseName;

		};
	}

}
//------------------------------------------------------------------------