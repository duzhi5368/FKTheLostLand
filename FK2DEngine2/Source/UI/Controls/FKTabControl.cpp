/**
*	created:		2013-4-13   21:38
*	filename: 		FKTabControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
class TabControlInner : public Base
{
	public:

		FK_CONTROL_INLINE( TabControlInner, Base )
		{
		}

		void Render( Skin::Base* skin )
		{
			skin->DrawTabControl( this );
		}
};

FK_CONTROL_CONSTRUCTOR( TabControl )
{
	m_iScrollOffset = 0;
	m_pCurrentButton = NULL;
	m_TabStrip = new TabStrip( this );
	m_TabStrip->SetTabPosition( Pos::Top );
	m_pScroll[0] = new ControlsInternal::ScrollBarButton( this );
	m_pScroll[0]->SetDirectionLeft();
	m_pScroll[0]->onPress.Add( this, &TabControl::ScrollPressLeft );
	m_pScroll[0]->SetSize( 14, 14 );
	m_pScroll[1] = new ControlsInternal::ScrollBarButton( this );
	m_pScroll[1]->SetDirectionRight();
	m_pScroll[1]->onPress.Add( this, &TabControl::ScrollPressRight );
	m_pScroll[1]->SetSize( 14, 14 );
	m_InnerPanel = new TabControlInner( this );
	m_InnerPanel->Dock( Pos::Fill );
	m_InnerPanel->SendToBack();
	SetTabable( false );
}

TabButton* TabControl::AddPage( UITexObjSimpleInfo strText, Controls::Base* pPage )
{
	if ( !pPage )
	{
		pPage = new Base( this );
	}
	else
	{
		pPage->SetParent( this );
	}

	TabButton* pButton = new TabButton( m_TabStrip );
	pButton->SetText( strText );
	pButton->SetPage( pPage );
	pButton->SetTabable( false );
	AddPage( pButton );
	return pButton;
}

void TabControl::RemovePage( TabButton* pButton )
{
	pButton->SetParent( GetCanvas() );
	OnLoseTab( pButton );
}

void TabControl::AddPage( TabButton* pButton )
{
	Base* pPage = pButton->GetPage();
	pPage->SetParent( this );
	pPage->SetHidden( true );
	pPage->SetMargin( Margin( 6, 6, 6, 6 ) );
	pPage->Dock( Pos::Fill );
	pButton->SetParent( m_TabStrip );
	pButton->Dock( Pos::Left );
	pButton->SizeToContents();

	if ( pButton->GetTabControl() ) { pButton->onPress.RemoveHandler( pButton->GetTabControl() ); }

	pButton->SetTabControl( this );
	pButton->onPress.Add( this, &TabControl::OnTabPressed );

	if ( !m_pCurrentButton )
	{
		pButton->OnPress();
	}

	onAddTab.Call( this );
	Invalidate();
}

void TabControl::OnTabPressed( Controls::Base* control )
{
	TabButton* pButton = fk_cast<TabButton> ( control );

	if ( !pButton ) { return; }

	Base* pPage = pButton->GetPage();

	if ( !pPage ) { return; }

	if ( m_pCurrentButton == pButton )
	{ return; }

	if ( m_pCurrentButton )
	{
		Base* pPage = m_pCurrentButton->GetPage();

		if ( pPage )
		{
			pPage->SetHidden( true );
		}

		m_pCurrentButton->Redraw();
		m_pCurrentButton = NULL;
	}

	m_pCurrentButton = pButton;
	pPage->SetHidden( false );
	m_TabStrip->Invalidate();
	Invalidate();
}

void TabControl::PostLayout( Skin::Base* skin )
{
	BaseClass::PostLayout( skin );
	HandleOverflow();
}

void TabControl::OnLoseTab( TabButton* pButton )
{
	if ( m_pCurrentButton == pButton )
	{ m_pCurrentButton = NULL; }

	//TODO:
	onLoseTab.Call( this );
	Invalidate();
}

int TabControl::TabCount( void )
{
	return m_TabStrip->NumChildren();
}

TabButton* TabControl::GetTab( int iNum )
{
	return fk_cast<TabButton> ( m_TabStrip->GetChild( iNum ) );
}

void TabControl::SetTabStripPosition( int iDock )
{
	m_TabStrip->SetTabPosition( iDock );
}

bool TabControl::DoesAllowDrag()
{
	return m_TabStrip->AllowsTabReorder();
}

void TabControl::HandleOverflow()
{
	FK2DEngine2::Point TabsSize = m_TabStrip->ChildrenSize();

	bool bNeeded = TabsSize.x > Width() && m_TabStrip->GetDock() == Pos::Top;
	m_pScroll[0]->SetHidden( !bNeeded );
	m_pScroll[1]->SetHidden( !bNeeded );

	if ( !bNeeded ) { return; }

	m_iScrollOffset = FK2DEngine2::Clamp( m_iScrollOffset, 0, TabsSize.x - Width() + 32 );

	// TODO
	m_TabStrip->SetMargin( Margin( m_iScrollOffset * -1, 0, 0, 0 ) );

	m_pScroll[0]->SetPos( Width() - 30 , 5 );
	m_pScroll[1]->SetPos( m_pScroll[0]->Right(), 5 );
}

void TabControl::ScrollPressLeft( Base* pFrom )
{
	m_iScrollOffset -= 120;
}

void TabControl::ScrollPressRight( Base* pFrom )
{
	m_iScrollOffset += 120;
}
//------------------------------------------------------------------------