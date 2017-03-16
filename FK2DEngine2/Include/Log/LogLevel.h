/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	LogLevel
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _LOG_LEVEL_H_
#define _LOG_LEVEL_H_

//--------------------------------------------------------------------

namespace FKLogger
{
    // 定义Log重要层级
    #define FK_LOG_LEVEL_TRACE  100
    #define FK_LOG_LEVEL_DEBUG  200
    #define FK_LOG_LEVEL_INFO   300
    #define FK_LOG_LEVEL_WARN   400
    #define FK_LOG_LEVEL_ERROR  500
    #define FK_LOG_LEVEL_FATAL  600

    // 定义该宏则使当前文件Log无效
    #define FK_LOG_LEVEL_DISABLED   1000

    typedef enum ENUM_LogLevel
    {
        ELL_Trace,
        ELL_Debug,
        ELL_Info,
        ELL_Warn,
        ELL_Error,
        ELL_Fatal,
    }ELogLevel;

    // 枚举Log的输出方式
    typedef enum ENUM_LogOutputMode
    {
        ELOM_File,
        ELOM_Console,
        ELOM_Socket,
    }ELogOutputMode;
}

//--------------------------------------------------------------------
#endif