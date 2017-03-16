/**
*	created:		2013-4-12   17:34
*	filename: 		FKModal
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class Modal : public Controls::Base
		{
			FK_CONTROL_INLINE( Modal, Controls::Base )
			{
				SetKeyboardInputEnabled( true );
				SetMouseInputEnabled( true );
				SetShouldDrawBackground( true );
				SetBounds( 0, 0, GetParent()->Width(), GetParent()->Height() );
			}

			virtual void Layout( Skin::Base* /*skin*/ )
			{
				SetBounds( 0, 0, GetCanvas()->Width(), GetCanvas()->Height() );
			}

			virtual void Render( Skin::Base* skin )
			{
				skin->DrawModalControl( this );
			}
		};
	}
}
//------------------------------------------------------------------------