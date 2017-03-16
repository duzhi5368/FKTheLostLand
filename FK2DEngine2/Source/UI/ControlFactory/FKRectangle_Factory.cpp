/**
*	created:		2013-4-13   0:45
*	filename: 		FKRectangle_Factory
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

			class Color : public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( Color, "Rectangle's Background Color" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					Controls::Rectangle* pRect = fk_cast<Controls::Rectangle> ( ctrl );
					return Utility::Format( L"%i %i %i %i", pRect->GetColor().r, pRect->GetColor().g, pRect->GetColor().b, pRect->GetColor().a );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					Controls::Rectangle* pRect = fk_cast<Controls::Rectangle> ( ctrl );
					int r, g, b, a;

					if ( swscanf( str.c_str(), L"%i %i %i %i", &r, &g, &b, &a ) != 4 ) { return; }

					pRect->SetColor( FK2DEngine2::Color( r, g, b, a ) );
				}

				int	NumCount() { return 4; };

				FK2DEngine2::String NumName( int i )
				{
					if ( i == 0 ) { return "r"; }

					if ( i == 1 ) { return "g"; }

					if ( i == 2 ) { return "b"; }

					return "a";
				}

				float NumGet( Controls::Base* ctrl, int i )
				{
					Controls::Rectangle* pRect = fk_cast<Controls::Rectangle> ( ctrl );

					if ( i == 0 ) { return pRect->GetColor().r; }

					if ( i == 1 ) { return pRect->GetColor().g; }

					if ( i == 2 ) { return pRect->GetColor().b; }

					return pRect->GetColor().a;
				}

				void NumSet( Controls::Base* ctrl, int i, float f )
				{
					Controls::Rectangle* pRect = fk_cast<Controls::Rectangle> ( ctrl );
					FK2DEngine2::Color c = pRect->GetColor();

					if ( i == 0 ) { c.r = f; }

					if ( i == 1 ) { c.g = f; }

					if ( i == 2 ) { c.b = f; }

					if ( i == 3 ) { c.a = f; }

					pRect->SetColor( c );
				}

			};

		}


		class Rectangle_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( Rectangle_Factory, ControlFactory::Base )
			{
				AddProperty( new Properties::Color() );
			}

			virtual FK2DEngine2::String Name() { return "Rectangle"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::Rectangle* pControl = new FK2DEngine2::Controls::Rectangle( parent );
				pControl->SetSize( 100, 100 );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( Rectangle_Factory );

	}
}
