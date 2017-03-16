/**
*	created:		2013-4-12   16:16
*	filename: 		FKDockBase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class DockedTabControl;
		class TabControl;

		class FK_EXPORT DockBase : public Base
		{
			public:

				FK_CONTROL( DockBase, Base );

				virtual void Render( Skin::Base* skin );
				virtual void RenderOver( Skin::Base* skin );
				virtual bool IsEmpty();

				virtual TabControl* GetTabControl();

				virtual DockBase* GetRight() { return GetChildDock( Pos::Right ); }
				virtual DockBase* GetLeft() { return GetChildDock( Pos::Left ); }
				virtual DockBase* GetTop() { return GetChildDock( Pos::Top ); }
				virtual DockBase* GetBottom() { return GetChildDock( Pos::Bottom ); }

				virtual bool OnKeySpace( bool /*bDown*/ ) { return false; }

			private:

				virtual bool DragAndDrop_HandleDrop( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual bool DragAndDrop_CanAcceptPackage( FK2DEngine2::DragAndDrop::Package* pPackage );
				virtual void DragAndDrop_HoverEnter( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual void DragAndDrop_HoverLeave( FK2DEngine2::DragAndDrop::Package* pPackage );
				virtual void DragAndDrop_Hover( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );

				virtual void SetupChildDock( int iPos );

				virtual void DoRedundancyCheck();
				virtual void DoConsolidateCheck();
				virtual void OnRedundantChildDock( DockBase* pDockBase );

				virtual int GetDroppedTabDirection( int x, int y );
				virtual void OnTabRemoved( FK2DEngine2::Controls::Base* pControl );

				DockBase* GetChildDock( int iPos );
				DockBase** GetChildDockPtr( int iPos );

				DockBase*		m_Left;
				DockBase*		m_Right;
				DockBase*		m_Top;
				DockBase*		m_Bottom;

				DockedTabControl*		m_DockedTabControl;

				bool		m_bDrawHover;
				bool		m_bDropFar;
				FK2DEngine2::Rect		m_HoverRect;

		};
	}
}
//------------------------------------------------------------------------