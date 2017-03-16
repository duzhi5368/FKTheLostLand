/**
*	created:		2013-4-12   15:58
*	filename: 		FKCollapsibleCategory
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class CollapsibleList;

		class FK_EXPORT CollapsibleCategory : public FK2DEngine2::Controls::Base
		{
			public:

				FK_CONTROL( CollapsibleCategory, FK2DEngine2::Controls::Base );

				virtual void Render( Skin::Base* skin );

				virtual void SetText( const UITexObjSimpleInfo & text );

				virtual Button* Add( const UITexObjSimpleInfo & name );

				virtual void PostLayout( Skin::Base* /*skin*/ );

				virtual void SetList( Controls::CollapsibleList* p ) { m_pList = p; }

				virtual void UnselectAll();
				virtual Button* GetSelected();

			public:

				FK2DEngine2::Event::Caller	onSelection;

			protected:

				virtual void OnSelection( Controls::Base* control );

				Controls::Button*			m_pButton;
				Controls::CollapsibleList*	m_pList;
		};

	}
}
//------------------------------------------------------------------------