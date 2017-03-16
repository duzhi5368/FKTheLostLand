/**
*	created:		2013-4-13   0:05
*	filename: 		FKListBox_Factory
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

		class ListBox_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( ListBox_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name()     { return "ListBox"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::ListBox* pControl = new FK2DEngine2::Controls::ListBox( parent );
				pControl->SetSize( 100, 100 );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( ListBox_Factory );

	}
}
//------------------------------------------------------------------------