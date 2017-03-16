/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FKLogger
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _FK_LOGGER_H_
#define _FK_LOGGER_H_

//--------------------------------------------------------------------
// 用户控制宏
//--------------------------------------------------------------------
// 只要开启本宏，所有Log全部无效
// #define DISABLE_ALL_LOGS
// 只要开启本宏，不再有线程安全
// #define DISABLE_THREAD_SAFE
//--------------------------------------------------------------------
#include "Log/LogVersion.h"
#include "Log/LogLevel.h"
#include "Log/LogConfig.h"
#include "Log/LogObject.h"
#include "Log/FKTime.h"
#include "Log/FKMutex.h"
#include "Log/FileLogger.h"
#include "Log/FileLoggerImpl.h"
#include "Log/SocketLogger.h"
#include "Log/SocketLoggerImpl.h"
//--------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif
    //--------------------------------------------------------------------
#ifdef DISABLE_ALL_LOGS
    #ifdef __GNUC__
        #warning FKLogger disabled.
    #endif
    #ifdef _MSC_VER
        TRACE("FKLogger disabled.")
    #endif

    #define InitFKLogger
    #define DeInitFKLogger()
    #define LogFuncEntry()
    #define LogFuncExit()
    #define LogTrace
    #define LogDebug
    #define LogInfo 
    #define LogWarn	
    #define LogError
    #define LogFatal

#else
    #if defined(WIN32) || defined(_WIN32)
        #define __func__ __FUNCTION__
    #endif

#ifdef _UNICODE
	int     LogImpl( FKLogger::ENUM_LogLevel p_eLevel, const char* p_szModuleName, 
		const char* p_szFile, const char* p_szFuncName, const int p_nLineNum,
		const wchar_t* p_szFmt, ... );
#else
    int     LogImpl( FKLogger::ENUM_LogLevel p_eLevel, const char* p_szModuleName, 
                    const char* p_szFile, const char* p_szFuncName, const int p_nLineNum,
                    const char* p_szFmt, ... );
#endif
    int     InitFKLogger( FKLogger::ENUM_LogOutputMode p_eMode, void* p_pInitParams );
    void    DeInitFKLogger();

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_TRACE
        #define LogTrace(fmt, ...) LogImpl(FKLogger::ELL_Trace,LOG_DEFAULT_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
    #else
        #define LogTrace
    #endif

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_DEBUG
        #define LogDebug(fmt, ...) LogImpl(FKLogger::ELL_Debug,LOG_DEFAULT_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
    #else
        #define LogDebug
    #endif

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_INFO
        #define LogInfo(fmt, ...) LogImpl(FKLogger::ELL_Info,LOG_DEFAULT_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
    #else
        #define LogInfo
    #endif

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_WARN
        #define LogWarn(fmt, ...) LogImpl(FKLogger::ELL_Warn,LOG_DEFAULT_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
    #else
        #define LogWarn
    #endif

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_ERROR
        #define LogError(fmt, ...) LogImpl(FKLogger::ELL_Error,LOG_DEFAULT_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
    #else
        #define LogError
    #endif

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_FATAL
        #define LogFatal(fmt, ...) LogImpl(FKLogger::ELL_Fatal,LOG_DEFAULT_MODULE_NAME,__FILE__,__func__, __LINE__ , fmt , ## __VA_ARGS__)
    #else
        #define LogFatal
    #endif

    #if FK_LOG_LEVEL <= FK_LOG_LEVEL_TRACE
        int FKLogFunEntry( const char* p_szFunName );
        int FKLogFunExit( const char* p_szFunName, const int p_nLineNumber );
        #define LogFuncEntry()      FKLogFunEntry( __func__ )
        #define LogFuncExit()       FKLogFunExit( __func__, __LINE__ )
    #else
        #define LogFuncEntry()  
        #define LogFuncExit()    
    #endif
#endif
//--------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//--------------------------------------------------------------------
#endif