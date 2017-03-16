/**
*	created:		2013-4-12   23:47
*	filename: 		FKComboBox_Factory
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

		class ComboBox_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( ComboBox_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name()     { return "ComboBox"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::ComboBox* pControl = new FK2DEngine2::Controls::ComboBox( parent );
				pControl->SetSize( 100, 20 );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( ComboBox_Factory );

	}
}
//------------------------------------------------------------------------