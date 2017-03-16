/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	SocketLoggerImpl
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _SOCKET_LOGGER_IMPL_H_
#define _SOCKET_LOGGER_IMPL_H_
//--------------------------------------------------------------------
#include "LogObject.h"
#include "SocketLogger.h"
//--------------------------------------------------------------------
namespace FKLogger
{
    int InitSocketLogger( SLogWriter** p_ppLogWriter,SSocketLoggerInitParams *p_pParams );
}
//--------------------------------------------------------------------
#endif