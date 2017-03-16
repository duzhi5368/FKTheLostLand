/**
*	created:		2013-4-13   0:20
*	filename: 		FKProgressBar_Factory
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
			class CycleSpeed: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( CycleSpeed, "" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return Utility::Format( L"%f", ( float ) fk_cast<Controls::ProgressBar> ( ctrl )->GetCycleSpeed() );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					float num;

					if ( swscanf( str.c_str(), L"%f", &num ) != 1 ) { return; }

					fk_cast<Controls::ProgressBar> ( ctrl )->SetCycleSpeed( num );
				}

			};

		}

		class ProgressBar_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( ProgressBar_Factory, FK2DEngine2::ControlFactory::Base )
			{
				AddProperty( new Properties::CycleSpeed() );
			}

			virtual FK2DEngine2::String Name()     { return "ProgressBar"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::ProgressBar* pControl = new FK2DEngine2::Controls::ProgressBar( parent );
				pControl->SetSize( 200, 20 );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( ProgressBar_Factory );

	}
}
//------------------------------------------------------------------------