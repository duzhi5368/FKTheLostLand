/**
*	created:		2013-4-28   20:34
*	filename: 		FKMessage
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <string>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace event
	{
		class CMessageListener;

		class CMessage
		{
		public:
			CMessage();
			CMessage( std::wstring messageName, CMessageListener* sender = NULL );
		public:
			virtual const std::wstring	GetMessageName();
			const CMessageListener*		GetMessageSender();
		protected:
			std::wstring		m_szMessageName;
			CMessageListener*	m_pSender;
		};

		class CMessageListener
		{
		public:
			virtual void	ReceiveMessage(CMessage* m) = 0;
		};
	}
}