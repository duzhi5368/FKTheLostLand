/**
*	created:		2013-5-3   16:41
*	filename: 		FKFullScreenActor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKFullScreenActor.h"
#include "../Include/FKSwitchboard.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
	//------------------------------------------------------------------------
		CFullScreenActor::CFullScreenActor()
			: m_bLocked( false )
		{
			theSwitchboard.SubscribeTo( this, L"WindowSizeChange" );
			Resize();
		}
		CFullScreenActor::~CFullScreenActor()
		{

		}
		void CFullScreenActor::SetLock( bool bLocked )
		{
			m_bLocked = bLocked;
			if( !m_bLocked )
			{
				Resize();
			}
		}
		const bool CFullScreenActor::IsLocked()
		{
			return m_bLocked;
		}
		void CFullScreenActor::ReceiveMessage(FK2DEngine2::event::CMessage* message)
		{
			if (!m_bLocked && message->GetMessageName() == L"WindowSizeChange")
			{
				Resize();
			}
		}
		void CFullScreenActor::Resize()
		{
			// TODO:
			// SetSize(dimensions.X, dimensions.Y);
		}
	//------------------------------------------------------------------------
	}
}