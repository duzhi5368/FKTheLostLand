/**
*	created:		2013-4-13   0:49
*	filename: 		FKVerticalSplitter_Factory
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
		class VerticalSplitter_Factory : public FK2DEngine2::ControlFactory::Base
		{
		public:

			FK_CONTROL_FACTORY_CONSTRUCTOR( VerticalSplitter_Factory, FK2DEngine2::ControlFactory::Base )
			{
			}

			virtual FK2DEngine2::String Name() { return "VerticalSplitter"; }
			virtual FK2DEngine2::String BaseName() { return "Base"; }

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent )
			{
				FK2DEngine2::Controls::SplitterVertical* pControl = new FK2DEngine2::Controls::SplitterVertical( parent );
				pControl->SetSize( 200, 200 );
				return pControl;
			}

			void AddChild( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* child, FK2DEngine2::Point & pos )
			{
				FK2DEngine2::Controls::SplitterVertical* pSplitter = fk_cast<FK2DEngine2::Controls::SplitterVertical> ( ctrl );
				child->SetParent( pSplitter );

				if ( pos.y < pSplitter->SplitterPos() )
				{ pSplitter->SetPanels( child, NULL ); }
				else
				{ pSplitter->SetPanels( NULL, child ); }
			}

			void AddChild( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* child, int iPage )
			{
				child->SetParent( ctrl );
			}
		};


		FK_CONTROL_FACTORY( VerticalSplitter_Factory );
	}
}

