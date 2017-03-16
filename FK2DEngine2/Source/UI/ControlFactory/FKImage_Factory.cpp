/**
*	created:		2013-4-12   23:58
*	filename: 		FKImage_Factory
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

		namespace Properties
		{

			class ImageName : public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( ImageName, "The path to the image (relative to .exe)" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return fk_cast<Controls::ImagePanel> ( ctrl )->GetImage();
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					fk_cast<Controls::ImagePanel> ( ctrl )->SetImage( str );
				}

			};

			class Stretch: public ControlFactory::PropertyBool
			{
				FK_CONTROL_FACTORY_PROPERTY( Stretch, "The path to the image (relative to .exe)" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					if ( fk_cast<Controls::ImagePanel> ( ctrl )->GetStretch() ) { return True; }

					return False;
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					bool bTrue = ( str == True );
					fk_cast<Controls::ImagePanel> ( ctrl )->SetStretch( bTrue );
				}

			};

		}

		class Image_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( Image_Factory, ControlFactory::Base )
			{
				AddProperty( new Properties::ImageName() );
				AddProperty( new Properties::Stretch() );
			}

			virtual FK2DEngine2::String Name()     { return "ImagePanel"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::ImagePanel* pControl = new FK2DEngine2::Controls::ImagePanel( parent );
				pControl->SetSize( 100, 20 );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( Image_Factory );

	}
}
//------------------------------------------------------------------------