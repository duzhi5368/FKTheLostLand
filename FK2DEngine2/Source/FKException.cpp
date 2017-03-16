/**
*	created:		2013-4-23   15:25
*	filename: 		FKException
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKException.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		CException::CException()
		{
			message = L"";
		}

		CException::CException(std::wstring message_)
			:message(message_)
		{
		}

		const std::wstring & CException::what()
		{
			return message;
		}

		void CException::addExtendMessage(std::wstring more)
		{
			message += more;
		}
	}
}
//------------------------------------------------------------------------