/**
*	created:		2013-4-12   17:41
*	filename: 		FKNumericUpDown
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
FK_CONTROL_CONSTRUCTOR( NumericUpDown )
{
	SetSize( 100, 20 );
	Controls::Base* pSplitter = new Controls::Base( this );
	pSplitter->Dock( Pos::Right );
	pSplitter->SetWidth( 13 );
	NumericUpDownButton_Up* pButtonUp = new NumericUpDownButton_Up( pSplitter );
	pButtonUp->onPress.Add( this, &NumericUpDown::OnButtonUp );
	pButtonUp->SetTabable( false );
	pButtonUp->Dock( Pos::Top );
	pButtonUp->SetHeight( 10 );
	NumericUpDownButton_Down* pButtonDown = new NumericUpDownButton_Down( pSplitter );
	pButtonDown->onPress.Add( this, &NumericUpDown::OnButtonDown );
	pButtonDown->SetTabable( false );
	pButtonDown->Dock( Pos::Fill );
	pButtonUp->SetPadding( Padding( 0, 1, 1, 0 ) );
	m_iMax = 100;
	m_iMin = 0;
	m_iNumber = 0;
	SetText( "0" );
}

void NumericUpDown::OnButtonUp( Base* /*control*/ )
{
	SyncNumberFromText();
	SetValue( m_iNumber + 1 );
}

void NumericUpDown::OnButtonDown( Base* /*control*/ )
{
	SyncNumberFromText();
	SetValue( m_iNumber - 1 );
}


void NumericUpDown::SyncTextFromNumber()
{
	SetText( Utility::ToString( m_iNumber ) );
}

void NumericUpDown::SyncNumberFromText()
{
	SetValue( ( int ) GetFloatFromText() );
}

void NumericUpDown::SetMin( int i )
{
	m_iMin = i;
}

void NumericUpDown::SetMax( int i )
{
	m_iMax = i;
}

void NumericUpDown::SetValue( int i )
{
	if ( i > m_iMax ) { i = m_iMax; }

	if ( i < m_iMin ) { i = m_iMin; }

	if ( m_iNumber == i )
	{
		return;
	}

	m_iNumber = i;

	//if ( !HasFocus() )
	{
		SyncTextFromNumber();
	}
	OnChange();
}

void NumericUpDown::OnChange()
{
	onChanged.Call( this );
}

void NumericUpDown::OnTextChanged()
{
	BaseClass::OnTextChanged();
	SyncNumberFromText();
}

void NumericUpDown::OnEnter()
{
	SyncNumberFromText();
	SyncTextFromNumber();
	BaseClass::OnEnter();
}
//------------------------------------------------------------------------