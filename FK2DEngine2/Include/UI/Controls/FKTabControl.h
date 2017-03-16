/**
*	created:		2013-4-12   16:51
*	filename: 		FKTabControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKTabButton.h"
#include "FKTabStrip.h"
#include "FKTabTitleBar.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class ScrollBarButton;
	}

	namespace Controls
	{
		class FK_EXPORT TabControl : public Base
		{
				FK_CONTROL( TabControl, Base );

				virtual TabButton* AddPage( const UITexObjSimpleInfo strText, Controls::Base* pPage = NULL );

				virtual void AddPage( TabButton* pButton );
				virtual void RemovePage( TabButton* pButton );

				virtual void OnTabPressed( Controls::Base* control );
				virtual void OnLoseTab( TabButton* pButton );

				virtual int TabCount( void );
				virtual TabButton* GetTab( int iNum );
				virtual TabButton* GetCurrentButton() { return m_pCurrentButton; }
				virtual TabStrip* GetTabStrip() { return m_TabStrip; }

				virtual void SetTabStripPosition( int iDock );

				virtual bool DoesAllowDrag();

				virtual void SetAllowReorder( bool b ) { GetTabStrip()->SetAllowReorder( b ); }

				FK2DEngine2::Event::Caller	onLoseTab;
				FK2DEngine2::Event::Caller	onAddTab;

			private:

				virtual void PostLayout( Skin::Base* skin );
				void HandleOverflow();

				void ScrollPressLeft( Base* pFrom );
				void ScrollPressRight( Base* pFrom );

				TabStrip*		m_TabStrip;
				TabButton*		m_pCurrentButton;

				ControlsInternal::ScrollBarButton*	m_pScroll[2];
				int				m_iScrollOffset;


		};
	}
}
//------------------------------------------------------------------------