/**
*	created:		2013-4-12   23:36
*	filename: 		FKCheckBox_Factory
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
		class CheckBox_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( CheckBox_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name() { return "CheckBox"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::CheckBox* pControl = new FK2DEngine2::Controls::CheckBox( parent );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( CheckBox_Factory );



		namespace Properties
		{
			class CheckboxText: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( CheckboxText, "The text, or label of the control" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return fk_cast<Controls::CheckBoxWithLabel> ( ctrl )->Label()->GetText().GetUnicode();
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					fk_cast<Controls::CheckBoxWithLabel> ( ctrl )->Label()->SetText( str );
				}

			};
		}

		class CheckBoxWithLabel_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( CheckBoxWithLabel_Factory, FK2DEngine2::ControlFactory::Base )
			{
				AddProperty( new Properties::CheckboxText() );
			}

			virtual FK2DEngine2::String Name()     { return "CheckBoxWithLabel"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::CheckBoxWithLabel* pControl = new FK2DEngine2::Controls::CheckBoxWithLabel( parent );
				return pControl;
			}
		};


		FK_CONTROL_FACTORY( CheckBoxWithLabel_Factory );

	}
}
