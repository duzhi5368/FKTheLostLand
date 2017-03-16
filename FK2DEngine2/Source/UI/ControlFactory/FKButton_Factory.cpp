/**
*	created:		2013-4-12   23:30
*	filename: 		FKButton_Factory
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

		class Button_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( Button_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name() { return "Button"; }
			virtual FK2DEngine2::String BaseName() { return "Label"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::Button* pControl = new FK2DEngine2::Controls::Button( parent );
				pControl->SetSize( 100, 20 );
				pControl->SetText( "New Button" );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( Button_Factory );

	}
}
