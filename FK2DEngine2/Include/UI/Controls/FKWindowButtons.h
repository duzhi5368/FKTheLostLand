/**
*	created:		2013-4-12   22:27
*	filename: 		FKWindowButtons
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "FKButton.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT WindowCloseButton : public Button
		{
				FK_CONTROL_INLINE( WindowCloseButton, Button )
				{
					m_pWindow = NULL;
					SetSize( 31, 31 );
					SetText( "" );
				}

				virtual void Render( Skin::Base* skin )
				{
					if ( !m_pWindow ) { return; }

					skin->DrawWindowCloseButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), IsDisabled() );
				}

				void SetWindow( FK2DEngine2::Controls::Base* p )
				{
					m_pWindow = p;
				}

			protected:

				Controls::Base* m_pWindow;
		};

		class FK_EXPORT WindowMaximizeButton : public WindowCloseButton
		{
				FK_CONTROL_INLINE( WindowMaximizeButton, WindowCloseButton ) { m_bMaximized = false; };

				virtual void Render( Skin::Base* skin )
				{
					if ( !m_pWindow ) { return; }

					skin->DrawWindowMaximizeButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), IsDisabled(), m_bMaximized );
				}

				virtual void SetMaximized( bool b )
				{
					m_bMaximized = b;
				}

			protected:

				bool m_bMaximized;
		};

		class FK_EXPORT WindowMinimizeButton : public WindowCloseButton
		{
				FK_CONTROL_INLINE( WindowMinimizeButton, WindowCloseButton ) {};

				virtual void Render( Skin::Base* skin )
				{
					if ( !m_pWindow ) { return; }

					skin->DrawWindowMinimizeButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), IsDisabled() );
				}

		};
	}
}
//------------------------------------------------------------------------