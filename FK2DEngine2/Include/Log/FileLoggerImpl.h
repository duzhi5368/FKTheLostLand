/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FileLoggerImpl
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _FILE_LOGGER_IMPL_H_
#define _FILE_LOGGER_IMPL_H_
//--------------------------------------------------------------------
#include "LogConfig.h"
#include "LogObject.h"
#include "FileLogger.h"
//--------------------------------------------------------------------
namespace FKLogger
{
    int InitFileLogger( FKLogger::SLogWriter** p_ppLogWriter, FKLogger::SFileLoggerInitParams* p_pParams );
    int InitConsoleLogger( FKLogger::SLogWriter** p_ppLogWriter, void* p_pInitParams );
}
//--------------------------------------------------------------------
#endif