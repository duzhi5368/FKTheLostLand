/**
*	created:		2013-4-12   23:51
*	filename: 		FKFilePicker_Factory
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
			using namespace FK2DEngine2;

			class FileType: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( FileType, "In the format \"PNG file | *.png\"" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return Utility::StringToUnicode( fk_cast<Controls::FilePicker> ( ctrl )->GetFileType() );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					fk_cast<Controls::FilePicker> ( ctrl )->SetFileType( Utility::UnicodeToString( str ) );
				}

			};

		}

		class FilePicker_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( FilePicker_Factory, ControlFactory::Base )
			{
				AddProperty( new Properties::FileType() );
			}

			virtual FK2DEngine2::String Name()     { return "FilePicker"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::FilePicker* pControl = new FK2DEngine2::Controls::FilePicker( parent );
				pControl->SetSize( 100, 20 );
				pControl->SetFileType( "EXE file | *.exe" );
				return pControl;
			}
		};

		FK_CONTROL_FACTORY( FilePicker_Factory );

	}
}
//------------------------------------------------------------------------