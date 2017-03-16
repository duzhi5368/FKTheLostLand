/**
*	created:		2013-4-12   14:58
*	filename: 		FKColorPicker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
using namespace FK2DEngine2::ControlsInternal;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( ColorPicker )
{
	SetMouseInputEnabled( true );
	SetSize( 256, 150 );
	CreateControls();
	SetColor( FK2DEngine2::Color( 50, 60, 70, 255 ) );
}

void ColorPicker::CreateColorControl( FK2DEngine2::String name, int y )
{
	int colorSize = 12;
	GroupBox* colorGroup = new GroupBox( this );
	colorGroup->SetPos( 10, y );
	colorGroup->SetText( name );
	colorGroup->SetSize( 160, 35 );
	colorGroup->SetName( name + "groupbox" );
	ColorDisplay* disp = new ColorDisplay( colorGroup );
	disp->SetName( name );
	disp->SetBounds( 0 , 10, colorSize, colorSize );
	TextBoxNumeric* numeric = new TextBoxNumeric( colorGroup );
	numeric->SetName( name + "Box" );
	numeric->SetPos( 105, 7 );
	numeric->SetSize( 26, 16 );
	numeric->SetSelectAllOnFocus( true );
	numeric->onTextChanged.Add( this, &ColorPicker::NumericTyped );
	HorizontalSlider* slider = new HorizontalSlider( colorGroup );
	slider->SetPos( colorSize + 5 , 8 );
	slider->SetRange( 0, 255 );
	slider->SetSize( 80, FK2DEngine2::Utility::Max( colorSize, 15 ) );
	slider->SetName( name + "Slider" );
	slider->onValueChanged.Add( this, &ColorPicker::SlidersMoved );
}

void ColorPicker::NumericTyped( FK2DEngine2::Controls::Base* control )
{
	TextBoxNumeric* box = fk_cast<TextBoxNumeric> ( control );

	if ( !box )
	{ return; }

	if ( box->GetText() == L"" )
	{ return; }

	int textValue = atoi( box->GetText().c_str() );

	if ( textValue < 0 ) { textValue = 0; }

	if ( textValue > 255 ) { textValue = 255; }

	if ( box->GetName().find( "Red" ) != FK2DEngine2::String::npos )
	{ SetRed( textValue ); }

	if ( box->GetName().find( "Green" ) != FK2DEngine2::String::npos )
	{ SetGreen( textValue ); }

	if ( box->GetName().find( "Blue" ) != FK2DEngine2::String::npos )
	{ SetBlue( textValue ); }

	if ( box->GetName().find( "Alpha" ) != FK2DEngine2::String::npos )
	{ SetAlpha( textValue ); }

	UpdateControls();
}

void ColorPicker::SetColor( FK2DEngine2::Color color )
{
	m_Color = color;
	UpdateControls();
}

void ColorPicker::CreateControls()
{
	int startY = 5;
	int height = 35;
	CreateColorControl( "Red",	 startY );
	CreateColorControl( "Green", startY + height );
	CreateColorControl( "Blue",  startY + height * 2 );
	CreateColorControl( "Alpha", startY + height * 3 );
	GroupBox* finalGroup = new GroupBox( this );
	finalGroup->SetPos( 180, 40 );
	finalGroup->SetSize( 60, 60 );
	finalGroup->SetText( "Result" );
	finalGroup->SetName( "ResultGroupBox" );
	ColorDisplay* disp = new ColorDisplay( finalGroup );
	disp->SetName( "Result" );
	disp->SetBounds( 0 , 10, 32, 32 );
	disp->SetDrawCheckers( true );
}

void ColorPicker::UpdateColorControls( FK2DEngine2::String name, FK2DEngine2::Color col, int sliderVal )
{
	ColorDisplay* disp = fk_cast<ColorDisplay> ( FindChildByName( name, true ) );
	disp->SetColor( col );
	HorizontalSlider* slider = fk_cast<HorizontalSlider> ( FindChildByName( name + "Slider", true ) );
	slider->SetFloatValue( sliderVal );
	TextBoxNumeric* box = fk_cast<TextBoxNumeric> ( FindChildByName( name + "Box", true ) );
	box->SetText( FK2DEngine2::Utility::ToString( sliderVal ) );
}

void ColorPicker::UpdateControls()
{
	UpdateColorControls( "Red",		Color( GetColor().r, 0, 0, 255 ), GetColor().r );
	UpdateColorControls( "Green",	Color( 0, GetColor().g, 0, 255 ), GetColor().g );
	UpdateColorControls( "Blue",	Color( 0, 0, GetColor().b, 255 ), GetColor().b );
	UpdateColorControls( "Alpha",	Color( 255, 255, 255, GetColor().a ), GetColor().a );
	ColorDisplay* disp = fk_cast<ColorDisplay> ( FindChildByName( "Result", true ) );
	disp->SetColor( Color( GetColor().r, GetColor().g, GetColor().b, GetColor().a ) );
	onColorChanged.Call( this );
}
void ColorPicker::SlidersMoved( FK2DEngine2::Controls::Base* control )
{
	HorizontalSlider* slider = fk_cast<HorizontalSlider> ( control );

	if ( slider )
	{ SetColorByName( GetColorFromName( slider->GetName() ), slider->GetFloatValue() ); }

	UpdateControls();
}

void ColorPicker::Layout( Skin::Base* skin )
{
	BaseClass::Layout( skin );
	SizeToChildren( false, true );
	SetSize( Width(), Height() + 5 );
	GroupBox* groupBox = fk_cast<GroupBox> ( FindChildByName( "ResultGroupBox", true ) );

	if ( groupBox )
	{ groupBox->SetPos( groupBox->X(), Height() * 0.5f - groupBox->Height() * 0.5f ); }

	UpdateControls();
}


int ColorPicker::GetColorByName( FK2DEngine2::String colorName )
{
	if ( colorName == "Red" )
	{ return GetColor().r; }
	else if ( colorName == "Green" )
	{ return GetColor().g; }
	else if ( colorName == "Blue" )
	{ return GetColor().b; }
	else if ( colorName == "Alpha" )
	{ return GetColor().a; }
	else
	{ return 0; }
}

FK2DEngine2::String ColorPicker::GetColorFromName( FK2DEngine2::String name )
{
	if ( name.find( "Red" ) != FK2DEngine2::String::npos )
	{ return "Red"; }

	if ( name.find( "Green" ) != FK2DEngine2::String::npos )
	{ return "Green"; }

	if ( name.find( "Blue" ) != FK2DEngine2::String::npos )
	{ return "Blue"; }

	if ( name.find( "Alpha" ) != FK2DEngine2::String::npos )
	{ return "Alpha"; }
	else
	{ return ""; }
}

void ColorPicker::SetColorByName( FK2DEngine2::String colorName, int colorValue )
{
	if ( colorName == "Red" )
	{ SetRed( colorValue ); }
	else if ( colorName == "Green" )
	{ SetGreen( colorValue ); }
	else if ( colorName == "Blue" )
	{ SetBlue( colorValue ); }
	else if ( colorName == "Alpha" )
	{ SetAlpha( colorValue ); }
}

void ColorPicker::SetAlphaVisible( bool visible )
{
	GroupBox* groupBox = fk_cast<GroupBox> ( FindChildByName( "Alphagroupbox", true ) );
	groupBox->SetHidden( !visible );
	Invalidate();
}
//------------------------------------------------------------------------