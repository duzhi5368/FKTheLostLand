/**
*	created:		2013-4-13   0:48
*	filename: 		FKTextBox_Factory
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

		class TextBox_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( TextBox_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name() { return "TextBox"; }
			virtual FK2DEngine2::String BaseName() { return "Label"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::TextBox* pControl = new FK2DEngine2::Controls::TextBox( parent );
				pControl->SetSize( 100, 20 );
				pControl->SetText( "" );
				return pControl;
			}
		};


		class TextBoxMultiLine_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( TextBoxMultiLine_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name() { return "TextBoxMultiline"; }
			virtual FK2DEngine2::String BaseName() { return "TextBox"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::TextBoxMultiline* pControl = new FK2DEngine2::Controls::TextBoxMultiline( parent );
				pControl->SetSize( 100, 50 );
				pControl->SetText( "" );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( TextBox_Factory );
		FK_CONTROL_FACTORY( TextBoxMultiLine_Factory );

	}
}

