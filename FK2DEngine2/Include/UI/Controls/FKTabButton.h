/**
*	created:		2013-4-12   16:53
*	filename: 		FKTabButton
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
		class TabControl;

		class FK_EXPORT TabButton : public Button
		{
			public:

				FK_CONTROL( TabButton, Button );
				virtual void Render( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );

				void SetPage( Base* page ) { m_Page = page; }
				Base* GetPage() { return m_Page; }

				void SetTabControl( TabControl* ctrl );
				TabControl* GetTabControl() { return m_Control; }

				bool IsActive() { return m_Page && m_Page->Visible(); }

				virtual bool DragAndDrop_ShouldStartDrag();
				virtual void DragAndDrop_StartDragging( FK2DEngine2::DragAndDrop::Package* /*pPackage*/, int /*x*/, int /*y*/ ) { SetHidden( true ); }
				virtual void DragAndDrop_EndDragging( bool /*bSuccess*/, int /*x*/, int /*y*/ ) { SetHidden( false ); SetDepressed( false ); }

				virtual bool OnKeyLeft( bool bDown );
				virtual bool OnKeyRight( bool bDown );
				virtual bool OnKeyUp( bool bDown );
				virtual bool OnKeyDown( bool bDown );

				virtual void UpdateColours();

				virtual bool ShouldClip() { return false; }

			private:

				Base*		m_Page;
				TabControl*	m_Control;

		};

	}
}
//------------------------------------------------------------------------