/**
*	created:		2013-4-13   0:00
*	filename: 		FKLabel_Factory
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlFactory
	{

		using namespace FK2DEngine2;

		namespace Properties
		{
			class Text: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( Text, "The text, or label of the control" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					UnicodeString str = fk_cast<Controls::Label> ( ctrl )->GetText().GetUnicode();
					FK2DEngine2::Utility::Replace<UnicodeString> ( str, L"\n", L"\\n" );
					FK2DEngine2::Utility::Replace<UnicodeString> ( str, L"\t", L"\\t" );
					return str;
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					UnicodeString strOut = str;
					FK2DEngine2::Utility::Replace<UnicodeString> ( strOut, L"\\n", L"\n" );
					FK2DEngine2::Utility::Replace<UnicodeString> ( strOut, L"\\t", L"\t" );
					fk_cast<Controls::Label> ( ctrl )->SetText( strOut );
				}

			};

			class Font: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( Font, "The font name" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return fk_cast<Controls::Label> ( ctrl )->GetFont()->facename;
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					if ( str == L"" ) { return; }

					FK2DEngine2::Font* pFont = fk_cast<Controls::Label> ( ctrl )->GetFont();
					fk_cast<Controls::Label> ( ctrl )->SetFont( str, pFont->size, pFont->bold );
				}

			};

			class FontSize: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( FontSize, "The font size" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return FK2DEngine2::Utility::Format( L"%i", ( int ) fk_cast<Controls::Label> ( ctrl )->GetFont()->size );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					int size;

					if ( swscanf( str.c_str(), L"%i", &size ) != 1 ) { return; }

					FK2DEngine2::Font* pFont = fk_cast<Controls::Label> ( ctrl )->GetFont();

					if ( size == pFont->size ) { return; }

					fk_cast<Controls::Label> ( ctrl )->SetFont( pFont->facename, size, pFont->bold );
				}

			};

			class FontBold: public ControlFactory::PropertyBool
			{
				FK_CONTROL_FACTORY_PROPERTY( FontBold, "The font bold" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					if ( fk_cast<Controls::Label> ( ctrl )->GetFont()->bold ) { return True; }

					return False;
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					bool bTrue = ( str == True );
					FK2DEngine2::Font* pFont = fk_cast<Controls::Label> ( ctrl )->GetFont();

					if ( bTrue == pFont->bold ) { return; }

					fk_cast<Controls::Label> ( ctrl )->SetFont( pFont->facename, pFont->size, bTrue ? true : false );
				}

			};

			class Wrap: public ControlFactory::PropertyBool
			{
				FK_CONTROL_FACTORY_PROPERTY( Wrap, "Wrap the text" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					if ( fk_cast<Controls::Label> ( ctrl )->Wrap() ) { return True; }

					return False;
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					bool bTrue = ( str == True );

					if ( bTrue == fk_cast<Controls::Label> ( ctrl )->Wrap() ) { return; }

					fk_cast<Controls::Label> ( ctrl )->SetWrap( bTrue );
				}

			};

			class VerticalAlign: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( VerticalAlign, "VerticalAlign" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					if ( fk_cast<Controls::Label> ( ctrl )->GetAlignment() & Pos::Top )	{ return L"Top"; }

					if ( fk_cast<Controls::Label> ( ctrl )->GetAlignment() & Pos::CenterV )	{ return L"Center"; }

					if ( fk_cast<Controls::Label> ( ctrl )->GetAlignment() & Pos::Bottom )	{ return L"Bottom"; }

					return L"Top";
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					int iAlign = fk_cast<Controls::Label> ( ctrl )->GetAlignment();
					iAlign &= ~Pos::Top;
					iAlign &= ~Pos::CenterV;
					iAlign &= ~Pos::Bottom;

					if ( str == L"Top" )	{ fk_cast<Controls::Label> ( ctrl )->SetAlignment( iAlign | Pos::Top ); }

					if ( str == L"Center" ) { fk_cast<Controls::Label> ( ctrl )->SetAlignment( iAlign | Pos::CenterV ); }

					if ( str == L"Bottom" ) { fk_cast<Controls::Label> ( ctrl )->SetAlignment( iAlign | Pos::Bottom ); }
				}

				int	OptionNum() { return 3; }

				FK2DEngine2::UnicodeString	OptionGet( int i )
				{
					if ( i == 0 ) { return L"Top"; }

					if ( i == 1 ) { return L"Center"; }

					return L"Bottom";
				}

			};

			class HorizontalAlign: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( HorizontalAlign, "HorizontalAlign" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					if ( fk_cast<Controls::Label> ( ctrl )->GetAlignment() & Pos::Left )	{ return L"Left"; }

					if ( fk_cast<Controls::Label> ( ctrl )->GetAlignment() & Pos::CenterH )	{ return L"Center"; }

					if ( fk_cast<Controls::Label> ( ctrl )->GetAlignment() & Pos::Right )	{ return L"Right"; }

					return L"Left";
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					int iAlign = fk_cast<Controls::Label> ( ctrl )->GetAlignment();
					iAlign &= ~Pos::Left;
					iAlign &= ~Pos::CenterH;
					iAlign &= ~Pos::Right;

					if ( str == L"Left" )	{ fk_cast<Controls::Label> ( ctrl )->SetAlignment( iAlign | Pos::Left ); }

					if ( str == L"Center" ) { fk_cast<Controls::Label> ( ctrl )->SetAlignment( iAlign | Pos::CenterH ); }

					if ( str == L"Right" ) { fk_cast<Controls::Label> ( ctrl )->SetAlignment( iAlign | Pos::Right ); }
				}

				int	OptionNum() { return 3; }

				FK2DEngine2::UnicodeString	OptionGet( int i )
				{
					if ( i == 0 ) { return L"Left"; }

					if ( i == 1 ) { return L"Center"; }

					return L"Right";
				}

			};

		} // namespace Properties

		class Label_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( Label_Factory, ControlFactory::Base )
			{
				AddProperty( new Properties::Text() );
				AddProperty( new Properties::Wrap() );
				AddProperty( new Properties::Font() );
				AddProperty( new Properties::FontSize() );
				AddProperty( new Properties::FontBold() );
				AddProperty( new Properties::VerticalAlign() );
				AddProperty( new Properties::HorizontalAlign() );
			}

			virtual FK2DEngine2::String Name()     { return "Label"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::Label* pControl = new FK2DEngine2::Controls::Label( parent );
				pControl->SetSize( 100, 20 );
				pControl->SetText( "New Label" );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( Label_Factory );

		class LabelClickable_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( LabelClickable_Factory, ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name()     { return "LabelClickable"; }
			virtual FK2DEngine2::String BaseName() { return "Label"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::Label* pControl = new FK2DEngine2::Controls::LabelClickable( parent );
				pControl->SetSize( 100, 20 );
				pControl->SetText( "LabelClickable" );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( LabelClickable_Factory );

	}
}
