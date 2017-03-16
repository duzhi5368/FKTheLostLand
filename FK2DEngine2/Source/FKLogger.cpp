/**
*	created:		2013-4-23   15:22
*	filename: 		FKLogger
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include <fstream>
#include "../Include/FKLogger.h"
//------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		CLogger CLogger::defaultStaticLogger(L"FKLog.txt");

		CLogger::~CLogger()
		{
			if (isOwnStream)
			{
				delete outStream;
			}
		}
		CLogger::CLogger(wostream * outStream_ /* = &(std::cout) */)
			:outStream(outStream_),level(E_LOG_LEVEL_WARNING)
		{
			isOwnStream = false;
		}

		CLogger::CLogger(const wstring & fileName)
		{
			outStream = new wofstream(fileName.c_str());
			level = E_LOG_LEVEL_WARNING;
			isOwnStream = true;
		}
		void CLogger::setOutStream(wostream * outStream_)
		{
			if (isOwnStream)
			{
				delete outStream;
				isOwnStream = false;
			}
			outStream = outStream_;
		}

		E_LOG_LEVEL_MODE CLogger::getLoggerLevel() const 
		{
			return level; 
		}
		void CLogger::setLoggerLevel(E_LOG_LEVEL_MODE level_)
		{
			level = level_;
		}
		void CLogger::printLoggerLevel()
		{
			switch(level)
			{
			case E_LOG_LEVEL_INFOMATION:
				(*outStream) << "ÐÅÏ¢ : ";
				break;
			case E_LOG_LEVEL_WARNING :
				(*outStream) << "¾¯¸æ : ";
				break;
			case E_LOG_LEVEL_ERROR :
				(*outStream) << "´íÎó : ";
				break;
			case E_LOG_LEVEL_NONE:
				break;
			}
		}
	}
}
//------------------------------------------------------------------------