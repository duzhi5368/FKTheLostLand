/**
*	created:		2013-5-3   16:14
*	filename: 		FKFullScreenActor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKActor.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
		class CFullScreenActor : public CActor
		{
		public:
			CFullScreenActor();
			~CFullScreenActor();
		public:
			void						SetLock( bool bLocked );
			const bool					IsLocked();
			virtual void				ReceiveMessage(FK2DEngine2::event::CMessage* message);
			virtual const std::wstring	GetActorClassName(){ return L"FullScreenActor"; }
		private:
			bool		m_bLocked;
		private:
			void		Resize();
		};
	}
}
//------------------------------------------------------------------------