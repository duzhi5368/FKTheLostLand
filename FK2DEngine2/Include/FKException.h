/**
*	created:		2013-4-23   15:24
*	filename: 		FKException
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
	namespace core
	{
		class CException
		{
		public :
			virtual ~CException(){}
			CException();
			CException(std::wstring message);
			
			virtual const std::wstring & what();
			virtual void addExtendMessage(std::wstring more);
		private:
			std::wstring message;
		};
	}
}
//------------------------------------------------------------------------