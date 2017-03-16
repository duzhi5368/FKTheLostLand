/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	LogObject
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _LOG_OBJECT_H_
#define _LOG_OBJECT_H_
//--------------------------------------------------------------------
#include <stdarg.h>
#include "LogLevel.h"
//--------------------------------------------------------------------
namespace FKLogger
{
    struct SLogWriter;

    typedef int (*FKLog)( struct SLogWriter* p_pThis, const ENUM_LogLevel p_eLogLevel,
        const char* p_pModuleName, const char* p_pFile, const char* p_pFuncName,
        const int p_nLineNum, const char* p_pFmt, va_list p_Ap );
	typedef int (*FKLogW)( struct SLogWriter* p_pThis, const ENUM_LogLevel p_eLogLevel,
		const char* p_pModuleName, const char* p_pFile, const char* p_pFuncName,
		const int p_nLineNum, const wchar_t* p_pFmt, va_list p_Ap );
    typedef int (*FKLogFunEntry)( struct SLogWriter* p_pThis, const char* p_pFuncName );
    typedef int (*FKLogFunExit)( struct SLogWriter* p_pThis, const char* p_pFuncName, int p_nLineNum );
    typedef int (*FKLogDeInit)( struct SLogWriter* p_pThis );

    typedef struct SLogWriter
    {
        FKLog               m_Log;
		FKLogW				m_LogW;
        FKLogFunEntry       m_LogFunEntry;
        FKLogFunExit        m_LogFunExit;
        FKLogDeInit         m_LogDeInit;
    }log_writer;
}
//--------------------------------------------------------------------
#endif