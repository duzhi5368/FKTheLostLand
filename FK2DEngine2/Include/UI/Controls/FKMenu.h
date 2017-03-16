/**
*	created:		2013-4-12   14:02
*	filename: 		FKMenu
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "FKMenuItem.h"
#include "FKScrollControl.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class MenuItem;

		class FK_EXPORT Menu : public ScrollControl
		{
			public:

				FK_CONTROL( Menu, ScrollControl );

				virtual void Render( Skin::Base* skin );
				virtual void RenderUnder( Skin::Base* skin );

				virtual void Layout( Skin::Base* skin );

				virtual MenuItem* AddItem( const UITexObjSimpleInfo & strName, const UITexObjSimpleInfo & strIconName = L"", const UITexObjSimpleInfo & strAccelerator = L"" );

				virtual void AddDivider();

				void OnHoverItem( FK2DEngine2::Controls::Base* pControl );
				void CloseAll();
				bool IsMenuOpen();
				void ClearItems();

				virtual void Open( unsigned int iPos );
				virtual void Close();

				virtual bool IsMenuComponent() { return true; }
				virtual void CloseMenus();

				bool IconMarginDisabled() { return m_bDisableIconMargin; }
				void SetDisableIconMargin( bool bDisable ) { m_bDisableIconMargin = bDisable; }

				bool DeleteOnClose() { return m_bDeleteOnClose; }
				void SetDeleteOnClose( bool b ) { m_bDeleteOnClose = b; }


			protected:

				virtual bool ShouldHoverOpenMenu() { return true; }
				virtual void OnAddItem( MenuItem* item );

				bool m_bDisableIconMargin;
				bool m_bDeleteOnClose;
		};

		class FK_EXPORT MenuDivider : public Base
		{
			public:

				FK_CONTROL_INLINE( MenuDivider, Base )
				{
					SetHeight( 1 );
				}

				void Render( FK2DEngine2::Skin::Base* skin );
		};
	}

}
//------------------------------------------------------------------------