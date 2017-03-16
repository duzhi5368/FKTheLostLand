/**
*	created:		2013-4-12   14:00
*	filename: 		FKMenuItem
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "FKButton.h"
#include "FKMenu.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class Menu;

		class FK_EXPORT MenuItem : public Button
		{
			public:

				FK_CONTROL( MenuItem, Button );

				virtual ~MenuItem();

				virtual void Render( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );

				virtual void SizeToContents();

				virtual void OnPress();

				Menu* GetMenu();

				bool IsMenuOpen();
				void OpenMenu();
				void CloseMenu();
				void ToggleMenu();

				void SetOnStrip( bool b ) { m_bOnStrip = b;}
				bool OnStrip() { return m_bOnStrip; }

				virtual void SetCheckable( bool bCheck ) { m_bCheckable = bCheck; }
				virtual void SetChecked( bool bCheck );
				virtual bool GetChecked() { return m_bChecked; }

				template <typename T>
				MenuItem* SetAction( FK2DEngine2::Event::Handler* pHandler, T fn )
				{
					if ( m_Accelerator ) { AddAccelerator( m_Accelerator->GetText(), fn, pHandler ); }

					onMenuItemSelected.Add( pHandler, fn );
					return this;
				}

				void SetAccelerator( const UITexObjSimpleInfo & strAccelerator );

				FK2DEngine2::Event::Caller	onMenuItemSelected;
				FK2DEngine2::Event::Caller	onChecked;
				FK2DEngine2::Event::Caller	onUnChecked;
				FK2DEngine2::Event::Caller	onCheckChange;

			private:

				Menu*	m_Menu;
				bool	m_bOnStrip;
				bool	m_bCheckable;
				bool	m_bChecked;

				Label*	m_Accelerator;


				Controls::Base*		m_SubmenuArrow;
		};
	}

}
//------------------------------------------------------------------------