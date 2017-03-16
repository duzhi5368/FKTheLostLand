/**
*	created:		2013-4-12   16:58
*	filename: 		FKTabStrip
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKTabButton.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT TabStrip : public Base
		{
			public:

				FK_CONTROL( TabStrip, Base );

				virtual void Layout( Skin::Base* skin );

				virtual bool DragAndDrop_HandleDrop( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual bool DragAndDrop_CanAcceptPackage( FK2DEngine2::DragAndDrop::Package* pPackage );

				virtual void DragAndDrop_HoverEnter( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual void DragAndDrop_HoverLeave( FK2DEngine2::DragAndDrop::Package* pPackage );
				virtual void DragAndDrop_Hover( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );

				virtual void SetTabPosition( int iPos );

				virtual void SetAllowReorder( bool b ) { m_bAllowReorder = b; }
				virtual bool AllowsTabReorder() { return m_bAllowReorder; }

				virtual bool ShouldClip() { return false; }

			private:

				Base*	m_TabDragControl;
				bool	m_bAllowReorder;

		};
	}
}
//------------------------------------------------------------------------