/**
*	created:		2013-4-11   20:19
*	filename: 		FKDragger
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
		class FK_EXPORT Dragger : public Controls::Base
		{
			public:

				FK_CONTROL( Dragger, Controls::Base );

				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );

				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				virtual void Render( Skin::Base* skin );

				virtual void SetTarget( Controls::Base* pBase ) { m_pTarget = pBase; }
				virtual bool IsDepressed() { return m_bDepressed; }

				virtual void SetDoMove( bool b ) { m_bDoMove = b; }

				virtual void OnMouseDoubleClickLeft( int x, int y );

				FK2DEngine2::Event::Caller	onDragged;
				FK2DEngine2::Event::Caller	onDragStart;

				FK2DEngine2::Event::Caller	onDoubleClickLeft;

			protected:

				bool				m_bDepressed;
				FK2DEngine2::Point	m_HoldPos;
				Controls::Base*		m_pTarget;
				bool				m_bDoMove;
		};
	}
}
//------------------------------------------------------------------------