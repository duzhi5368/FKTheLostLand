/**
*	created:		2013-4-12   21:08
*	filename: 		FKResizableControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "FKButton.h"
#include "FKDragger.h"
#include "FKResizer.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{

		class FK_EXPORT ResizableControl : public Base
		{
			public:

				FK_CONTROL( ResizableControl, Base );

				virtual void SetClampMovement( bool shouldClamp ) { m_bClampMovement = shouldClamp; }
				virtual bool GetClampMovement() { return m_bClampMovement; }

				virtual void SetMinimumSize( const FK2DEngine2::Point & minSize ) { m_MinimumSize = minSize; }
				virtual FK2DEngine2::Point GetMinimumSize() { return m_MinimumSize; }

				virtual void DisableResizing();

				virtual bool SetBounds( int x, int y, int w, int h );

				virtual void OnResized() {};

				Event::Caller	onResize;

				virtual ControlsInternal::Resizer* GetResizer( int iResizer ) { return m_Resizer[iResizer]; }

			protected:

				void OnResizedInternal( Controls::Base* pControl );

				FK2DEngine2::Point m_MinimumSize;
				bool m_bClampMovement;
				bool m_bResizable;

				ControlsInternal::Resizer* m_Resizer[10];

		};
	}
}
//------------------------------------------------------------------------