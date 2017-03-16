/**
*	created:		2013-4-12   17:26
*	filename: 		FKFilePicker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "Dialogs/FKFileOpen.h"
#include "FKTextBox.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT FilePicker : public Controls::Base
		{
			public:

				FK_CONTROL_INLINE( FilePicker, Controls::Base )
				{
					m_Button = new Controls::Button( this );
					m_Button->Dock( Pos::Right );
					m_Button->SetMargin( Margin( 2, 0, 0, 0 ) );
					m_Button->SetText( ".." );
					m_Button->SetSize( 20, 20 );
					m_Button->onPress.Add( this, &FilePicker::OnBrowse );
					m_TextBox = new Controls::TextBox( this );
					m_TextBox->Dock( Pos::Fill );
					this->SetSize( 100, 20 );
					SetFileType( "Any Type | *.*" );
				}

				void SetFileType( const FK2DEngine2::String & wstring ) { m_FileType = wstring; }
				FK2DEngine2::String GetFileType() { return m_FileType; }

				void SetFileName( const UITexObjSimpleInfo & strValue )
				{
					m_TextBox->SetText( strValue );
					m_TextBox->MoveCaretToEnd();
					onFileChanged.Call( this );
				}

				const FK2DEngine2::UITexObjSimpleInfo & GetFileName()
				{
					return m_TextBox->GetText();
				}

				void OnBrowse()
				{
					FK2DEngine2::Dialogs::FileOpen( true, "Name", "Start Path", m_FileType, this, &FilePicker::SetFileNameEvent );
				}

				virtual UITexObjSimpleInfo GetValue() { return GetFileName(); }
				virtual void SetValue( const UITexObjSimpleInfo & strValue ) { return SetFileName( strValue ); }

				Event::Caller	onFileChanged;

			private:

				void SetFileNameEvent( Event::Info info )
				{
					SetFileName( info.String );
				}

				Controls::TextBox*	m_TextBox;
				Controls::Button*	m_Button;

				String				m_FileType;

		};
	}

}
//------------------------------------------------------------------------