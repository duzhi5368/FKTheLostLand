/**
*	created:		2013-4-12   16:50
*	filename: 		FKDockedTabControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKTabControl.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT DockedTabControl : public TabControl
		{
			public:

				FK_CONTROL( DockedTabControl, TabControl );

				void SetShowTitlebar( bool bShow ) { m_pTitleBar->SetHidden( !bShow ); }

				void Layout( Skin::Base* skin );
				void UpdateTitleBar();

				virtual void DragAndDrop_StartDragging( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y );
				virtual void DragAndDrop_EndDragging( bool bSuccess, int x, int y );

				void MoveTabsTo( DockedTabControl* pTarget );

			private:

				TabTitleBar*	m_pTitleBar;
				Base*			m_WindowControl;

		};
	}
}
//------------------------------------------------------------------------