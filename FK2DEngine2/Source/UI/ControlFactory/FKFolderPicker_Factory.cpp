/**
*	created:		2013-4-12   23:53
*	filename: 		FKFolderPicker_Factory
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

		class FolderPicker_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( FolderPicker_Factory, ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name()     { return "FolderPicker"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::FolderPicker* pControl = new FK2DEngine2::Controls::FolderPicker( parent );
				pControl->SetSize( 100, 20 );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( FolderPicker_Factory );

	}
}
//------------------------------------------------------------------------