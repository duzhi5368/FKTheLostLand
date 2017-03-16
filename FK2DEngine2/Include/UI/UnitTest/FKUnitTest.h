/**
*	created:		2013-4-11   22:48
*	filename: 		FKUnitTest
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "../FKAlign.h"
#include "../FKUtility.h"
#include "../Controls/FKWindowControl.h"
#include "../Controls/FKTabControl.h"
#include "../Controls/FKListBox.h"
#include "../Controls/FKDockBase.h"
#include "../Controls/FKStatusBar.h"
//------------------------------------------------------------------------
class UnitTest;
//------------------------------------------------------------------------
class GUnit : public FK2DEngine2::Controls::Base
{
	public:

		FK_CONTROL_INLINE( GUnit, FK2DEngine2::Controls::Base )
		{
			m_pUnitTest = NULL;
		}

		void SetUnitTest( UnitTest* u ) { m_pUnitTest = u; }

		void UnitPrint( FK2DEngine2::UnicodeString str );
		void UnitPrint( FK2DEngine2::String str );

		void Layout( FK2DEngine2::Skin::Base* skin )
		{
			if ( GetDock() != FK2DEngine2::Pos::None ) { return; }

			SizeToChildren( true, true );
		}


		UnitTest* m_pUnitTest;
};
//------------------------------------------------------------------------
class UnitTest : public FK2DEngine2::Controls::DockBase
{
	public:

		FK_CONTROL( UnitTest, FK2DEngine2::Controls::DockBase );

		void PrintText( const FK2DEngine2::UnicodeString & str );
		void Render( FK2DEngine2::Skin::Base* skin );

	private:

		void OnCategorySelect( FK2DEngine2::Event::Info info );

		FK2DEngine2::Controls::TabControl*		m_TabControl;
		FK2DEngine2::Controls::ListBox*			m_TextOutput;
		FK2DEngine2::Controls::StatusBar*		m_StatusBar;
		unsigned int							m_iFrames;
		float									m_fLastSecond;

		FK2DEngine2::Controls::Base*			m_pLastControl;

};
//------------------------------------------------------------------------
#define DEFINE_UNIT_TEST( name, displayname ) GUnit* RegisterUnitTest_##name( FK2DEngine2::Controls::Base* tab ){ return new name( tab ); }
//------------------------------------------------------------------------
