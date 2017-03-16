/**
*	created:		2013-4-13   0:15
*	filename: 		FKMenuStrip_Factory
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

		class MenuStrip_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( MenuStrip_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name()     { return "MenuStrip"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::MenuStrip* pControl = new FK2DEngine2::Controls::MenuStrip( parent );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( MenuStrip_Factory );

	}
}
