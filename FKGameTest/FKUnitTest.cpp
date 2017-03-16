/**
*	created:		2013-4-24   7:36
*	filename: 		FKUnitTest
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "FKUnitTestControls.h"
#include "../FK2DEngine2/Include/UI/UnitTest/FKUnitTest.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
#define ADD_UNIT_TEST( name )\
	GUnit* RegisterUnitTest_##name( FK2DEngine2::Controls::Base* tab );\
{\
	Controls::Button* pButton = cat->Add( #name );\
	pButton->SetName( #name );\
	GUnit* test = RegisterUnitTest_##name( pCenter );\
	test->Hide();\
	test->SetUnitTest( this );\
	pButton->onPress.Add( this, &ThisClass::OnCategorySelect, FK2DEngine2::Event::Packet( test ) );\
}\

//------------------------------------------------------------------------
FK2DEngine2::Controls::TabButton* pButton = NULL;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( UnitTest )
{
	// 初始化控件记录空
	m_pLastControl = NULL;
	Dock( Pos::Fill );
	SetSize( 1024, 768 );

	// 创建折叠表控件
	Controls::CollapsibleList* pList = new Controls::CollapsibleList( this );
	GetLeft()->GetTabControl()->AddPage( "折叠表", pList );
	GetLeft()->SetWidth( 150 );

	// 创建信息输出框
	m_TextOutput = new Controls::ListBox( GetBottom() );
	pButton = GetBottom()->GetTabControl()->AddPage( "信息框", m_TextOutput );
	pButton->Dock( Pos::Center );
	GetBottom()->SetHeight( 200 );

	// 创建底层状态栏
	m_StatusBar = new Controls::StatusBar( this );
	m_StatusBar->Dock( Pos::Bottom );

	Controls::Layout::Center* pCenter = new Controls::Layout::Center( this );
	pCenter->Dock( Pos::Fill );

	{
		Controls::CollapsibleCategory* cat = pList->Add( "基础控件" );
		ADD_UNIT_TEST( UnitButton );
		ADD_UNIT_TEST( UnitLabel );
		ADD_UNIT_TEST( UnitLabelMultiline );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "无交互性控件" );
		ADD_UNIT_TEST( UnitProgressBar );
		ADD_UNIT_TEST( UnitGroupBox );
		ADD_UNIT_TEST( UnitImagePanel );
		ADD_UNIT_TEST( UnitStatusBar );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "常规控件" );
		ADD_UNIT_TEST( UnitComboBox );
		ADD_UNIT_TEST( UnitTextBox );
		ADD_UNIT_TEST( UnitListBox );
		ADD_UNIT_TEST( UnitCrossSplitter );
		ADD_UNIT_TEST( UnitRadioButton );
		ADD_UNIT_TEST( UnitCheckbox );
		ADD_UNIT_TEST( UnitNumeric );
		ADD_UNIT_TEST( UnitSlider );
		ADD_UNIT_TEST( UnitMenuStrip );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "容器控件" );
		ADD_UNIT_TEST( UnitWindow );
		ADD_UNIT_TEST( UnitTreeControl );
		ADD_UNIT_TEST( UnitProperties );
		ADD_UNIT_TEST( UnitTabControl );
		ADD_UNIT_TEST( UnitScrollControl );
		ADD_UNIT_TEST( UnitPageControl );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "非标准控件" );
		ADD_UNIT_TEST( UnitCollapsibleList );
		ADD_UNIT_TEST( UnitColorPicker );
	}

	// 将状态栏移至UI底层
	m_StatusBar->SendToBack();

	// 信息栏输出文字
	PrintText( L"UI单元测试开始.\n" );

	// 刷新计算帧率
	m_fLastSecond = FK2DEngine2::Platform::GetTimeInSeconds();
	m_iFrames = 0;

	pList->GetNamedChildren( "MenuStrip" ).DoAction();
}
//------------------------------------------------------------------------
void UnitTest::OnCategorySelect( FK2DEngine2::Event::Info info )
{
	if ( m_pLastControl )
	{
		m_pLastControl->Hide();
	}

	info.Packet->Control->Show();
	m_pLastControl = info.Packet->Control;
}
//------------------------------------------------------------------------
void UnitTest::PrintText( const FK2DEngine2::UnicodeString & str )
{
	m_TextOutput->AddItem( str );
	m_TextOutput->ScrollToBottom();
}
//------------------------------------------------------------------------
void UnitTest::Render( FK2DEngine2::Skin::Base* skin )
{
	m_iFrames++;

	if ( m_fLastSecond < FK2DEngine2::Platform::GetTimeInSeconds() )
	{
		m_StatusBar->SetText( FK2DEngine2::Utility::Format( L"FK2DUIEngine2 单元测试：当前帧率 - %i fps", m_iFrames * 2 ) );
		m_fLastSecond = FK2DEngine2::Platform::GetTimeInSeconds() + 0.5f;
		m_iFrames = 0;
	}

	BaseClass::Render( skin );
}
//------------------------------------------------------------------------
void GUnit::UnitPrint( FK2DEngine2::UnicodeString str )
{
	m_pUnitTest->PrintText( str );
}
//------------------------------------------------------------------------
void GUnit::UnitPrint( FK2DEngine2::String str )
{
	UnitPrint( Utility::StringToUnicode( str ) );
}
//------------------------------------------------------------------------