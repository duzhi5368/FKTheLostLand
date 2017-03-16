/**
*	created:		2013-4-28   23:25
*	filename: 		FKMessage
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKMessage.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace event
	{
		CMessage::CMessage()
		{
			m_szMessageName = L"GenericMessage";
			m_pSender = NULL;
		}
		//------------------------------------------------------------------------
		CMessage::CMessage( std::wstring messageName, CMessageListener* sender )
		{
			m_szMessageName = messageName;
			m_pSender = sender;
		}
		//------------------------------------------------------------------------
		const std::wstring CMessage::GetMessageName()
		{
			return m_szMessageName;
		}
		//------------------------------------------------------------------------
		const CMessageListener* CMessage::GetMessageSender()
		{
			return m_pSender;
		}
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------