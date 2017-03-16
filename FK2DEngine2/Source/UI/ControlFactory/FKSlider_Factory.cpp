/**
*	created:		2013-4-13   0:46
*	filename: 		FKSlider_Factory
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

			class Min: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( Min, "The minimum value" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return FK2DEngine2::Utility::Format( L"%f", ( int ) fk_cast<Controls::Slider> ( ctrl )->GetMin() );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					float val;

					if ( swscanf( str.c_str(), L"%f", &val ) != 1 ) { return; }

					if ( val == fk_cast<Controls::Slider> ( ctrl )->GetMin() ) { return; }

					fk_cast<Controls::Slider> ( ctrl )->SetRange( val, fk_cast<Controls::Slider> ( ctrl )->GetMax() );
				}

			};

			class Max: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( Max, "The max value" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return FK2DEngine2::Utility::Format( L"%f", ( int ) fk_cast<Controls::Slider> ( ctrl )->GetMax() );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					float val;

					if ( swscanf( str.c_str(), L"%f", &val ) != 1 ) { return; }

					if ( val == fk_cast<Controls::Slider> ( ctrl )->GetMax() ) { return; }

					fk_cast<Controls::Slider> ( ctrl )->SetRange( fk_cast<Controls::Slider> ( ctrl )->GetMin(), val );
				}

			};
		}

		class HorizontalSlider_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( HorizontalSlider_Factory, FK2DEngine2::ControlFactory::Base )
			{
				AddProperty( new Properties::Min() );
				AddProperty( new Properties::Max() );
			}

			virtual FK2DEngine2::String Name() { return "HorizontalSlider"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::HorizontalSlider* pControl = new FK2DEngine2::Controls::HorizontalSlider( parent );
				pControl->SetSize( 100, 20 );
				pControl->SetRange( 0, 1 );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( HorizontalSlider_Factory );

	}
}
