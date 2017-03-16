/**
*	created:		2013-4-12   15:45
*	filename: 		FKComboBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKTextBox.h"
#include "FKMenu.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT ComboBox : public Button
		{
			public:

				FK_CONTROL( ComboBox, Button );

				virtual void Render( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );
				virtual void UpdateColours();

				virtual void SelectItem( MenuItem* pItem, bool bFireChangeEvents = true );
				virtual void SelectItemByName( const FK2DEngine2::String & name, bool bFireChangeEvents = true );
				virtual FK2DEngine2::Controls::Label* GetSelectedItem();

				virtual void OnPress();
				virtual void OnItemSelected( Controls::Base* pControl );
				virtual void OpenList();
				virtual void CloseList();

				virtual void ClearItems();

				virtual MenuItem* AddItem( const UnicodeString & strLabel, const String & strName = "" );
				virtual bool OnKeyUp( bool bDown );
				virtual bool OnKeyDown( bool bDown );

				virtual void RenderFocus( FK2DEngine2::Skin::Base* skin );
				virtual void OnLostKeyboardFocus();
				virtual void OnKeyboardFocus();

				virtual bool IsMenuOpen();

				virtual bool IsMenuComponent() { return true; }

				FK2DEngine2::Event::Caller	onSelection;

			protected:

				Menu* m_Menu;
				MenuItem* m_SelectedItem;

				Controls::Base*	m_Button;

		};

	}
}
//------------------------------------------------------------------------