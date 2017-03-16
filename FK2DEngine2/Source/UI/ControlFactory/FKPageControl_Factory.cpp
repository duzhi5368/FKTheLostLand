/**
*	created:		2013-4-13   0:17
*	filename: 		FKPageControl_Factory
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
			class NumPages: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( NumPages, "The number of pages we have" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					return Utility::Format( L"%i", ( int ) fk_cast<Controls::PageControl> ( ctrl )->GetPageCount() );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					int num;

					if ( swscanf( str.c_str(), L"%i", &num ) != 1 ) { return; }

					fk_cast<Controls::PageControl> ( ctrl )->SetPageCount( num );
				}

			};

			class FinishName: public ControlFactory::Property
			{
				FK_CONTROL_FACTORY_PROPERTY( FinishName, "The name of the finish button" );

				UnicodeString GetValue( Controls::Base* ctrl )
				{
					FK2DEngine2::Controls::PageControl* pControl = fk_cast<FK2DEngine2::Controls::PageControl> ( ctrl );
					return Utility::StringToUnicode( pControl->FinishButton()->GetName() );
				}

				void SetValue( Controls::Base* ctrl, const UnicodeString & str )
				{
					FK2DEngine2::Controls::PageControl* pControl = fk_cast<FK2DEngine2::Controls::PageControl> ( ctrl );
					pControl->FinishButton()->SetName( Utility::UnicodeToString( str ) );
				}
			};

		}

		class PageControl_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( PageControl_Factory, FK2DEngine2::ControlFactory::Base )
			{
				AddProperty( new Properties::NumPages() );
				AddProperty( new Properties::FinishName() );
			}

			virtual FK2DEngine2::String Name()     { return "PageControl"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::PageControl* pControl = new FK2DEngine2::Controls::PageControl( parent );
				pControl->SetSize( 300, 300 );
				pControl->SetPageCount( 1 );
				return pControl;
			}

			virtual bool ChildTouched( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* pChildControl )
			{
				FK2DEngine2::Controls::PageControl* pControl = fk_cast<FK2DEngine2::Controls::PageControl> ( ctrl );

				if ( pChildControl == pControl->NextButton() ) { pControl->NextButton()->DoAction(); return true; }

				if ( pChildControl == pControl->BackButton() ) { pControl->BackButton()->DoAction(); return true; }

				return false;
			}

			void AddChild( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* child, const FK2DEngine2::Point & pos )
			{
				FK2DEngine2::Controls::PageControl* pControl = fk_cast<FK2DEngine2::Controls::PageControl> ( ctrl );
				AddChild( ctrl, child, pControl->GetPageNumber() );
			}

			void AddChild( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* child, int iPage )
			{
				FK2DEngine2::Controls::PageControl* pControl = fk_cast<FK2DEngine2::Controls::PageControl> ( ctrl );

				if ( !pControl->GetPage( iPage ) ) { iPage = 0; }

				SetParentPage( child, iPage );
				child->SetParent( pControl->GetPage( iPage ) );
			}
		};


		FK_CONTROL_FACTORY( PageControl_Factory );

	}
}
//------------------------------------------------------------------------