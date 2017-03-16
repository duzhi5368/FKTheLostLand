/**
*	created:		2013-4-12   17:30
*	filename: 		FKMenuStrip
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "FKMenu.h"
#include "FKMenuItem.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT MenuStrip : public Menu
		{
				FK_CONTROL( MenuStrip, Menu );

				virtual void Render( Skin::Base* skin );
				virtual void RenderUnder( Skin::Base* /*skin*/ ) {}
				virtual void Layout( Skin::Base* skin );

			protected:

				virtual void OnAddItem( MenuItem* item );
				virtual bool ShouldHoverOpenMenu();
				virtual void Close() {}


		};
	}

}
//------------------------------------------------------------------------