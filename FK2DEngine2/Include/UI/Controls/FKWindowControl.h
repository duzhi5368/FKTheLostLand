/**
*	created:		2013-4-12   23:00
*	filename: 		FKWindowControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "FKBase.h"
#include "FKLabel.h"
#include "FKButton.h"
#include "FKDragger.h"
#include "FKLabel.h"
#include "FKResizableControl.h"
#include "FKModal.h"
#include "FKWindowButtons.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class CloseButton;

		class FK_EXPORT WindowControl : public ResizableControl
		{
			public:

				FK_CONTROL( WindowControl, ResizableControl );

				virtual ~WindowControl();
				virtual void Render( Skin::Base* skin );
				virtual void RenderUnder( Skin::Base* skin );

				virtual void SetTitle( FK2DEngine2::UnicodeString title );
				virtual void SetTitle( FK2DEngine2::String title ) { SetTitle( FK2DEngine2::Utility::StringToUnicode( title ) ); }
				virtual void SetClosable( bool closeable );

				virtual void Touch();
				bool IsOnTop();
				virtual void Moveable( bool moveable );

				virtual void SetHidden( bool hidden );

				void CloseButtonPressed();
				void RenderFocus( FK2DEngine2::Skin::Base* skin );
				void SetDeleteOnClose( bool b ) { m_bDeleteOnClose = b; }

				void MakeModal( bool bDrawBackground = true );
				void DestroyModal();

				FK2DEngine2::Event::Caller	onWindowClosed;

			protected:

				FK2DEngine2::ControlsInternal::Dragger*		m_TitleBar;
				FK2DEngine2::Controls::Label*				m_Title;
				FK2DEngine2::Controls::WindowCloseButton*	m_CloseButton;

				bool m_bDeleteOnClose;
				bool m_bCanMove;

				ControlsInternal::Modal* m_Modal;
		};
	}
}
//------------------------------------------------------------------------