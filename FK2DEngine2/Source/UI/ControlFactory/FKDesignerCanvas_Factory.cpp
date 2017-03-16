/**
*	created:		2013-4-12   23:48
*	filename: 		FKDesignerCanvas_Fatcory
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

		class DesignerCanvas_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( DesignerCanvas_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name()     { return "DesignerCanvas"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				return NULL;
			}
		};


		FK_CONTROL_FACTORY( DesignerCanvas_Factory );

	}
}
//------------------------------------------------------------------------