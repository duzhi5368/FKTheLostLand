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

#include "../../Include/FKLogger.h"
#include "../../Include/FKStringConvert.h"
#include <stdio.h>

//--------------------------------------------------------------------
#ifdef DISABLE_ALL_LOGS
   
#else
    //--------------------------------------------------------------------
    static FKLogger::SLogWriter* s_pLogWriter = NULL;
    //--------------------------------------------------------------------
    #ifdef DISABLE_THREAD_SAFE
        #define __LOCK_MUTEX
        #define __UNLOCK_MUTEX
    #else
        #include "../../Include/Log/FKMutex.h"
        static FKMutex s_Mutex = 0;
        #define __LOCK_MUTEX        if( s_Mutex ) FKLogger::FKLockMutex( s_Mutex )
        #define __UNLOCK_MUTEX      if( s_Mutex ) FKLogger::FKUnlockMutex( s_Mutex )
    #endif
    //--------------------------------------------------------------------
    #define     CHECK_AND_INIT_LOGGER   if( !s_pLogWriter )                             \
                                        {                                               \
                                            if( InitFKLogger( FKLogger::ELOM_Console, stdout ))   \
                                            return -1;                                  \
                                            if( !s_pLogWriter )                         \
                                            return -1;                                  \
                                        }
    //--------------------------------------------------------------------
    int InitFKLogger( FKLogger::ENUM_LogOutputMode p_eMode, void* p_pInitParams )
    {
        int nRet = 0;
        if( s_pLogWriter )
        {
            DeInitFKLogger();
        }

    #ifndef DISABLE_THREAD_SAFE
        if( !s_Mutex )
        {
            FKLogger::FKCreateMutex( &s_Mutex );
        }
    #endif

        __LOCK_MUTEX;

        switch( p_eMode )
        {
        case FKLogger::ELOM_Socket:
            {
                if( FKLogger::InitSocketLogger( &s_pLogWriter, (FKLogger::SSocketLoggerInitParams *)p_pInitParams ) < 0 )
                {
                    nRet = -1;
                    goto UNLOCK_RETURN;
                }
            }
            break;
        case FKLogger::ELOM_Console:
            {
                if( FKLogger::InitConsoleLogger( &s_pLogWriter, p_pInitParams ) < 0 )
                {
                    nRet = -1;
                    goto UNLOCK_RETURN;
                }
            }
            break;
        case FKLogger::ELOM_File:
            {
                if( FKLogger::InitFileLogger( &s_pLogWriter, (FKLogger::SFileLoggerInitParams *)p_pInitParams ) < 0 )
                {
                    nRet = -1;
                    goto UNLOCK_RETURN;
                }
            }
            break;
        default:
            break;
        }
        nRet = 0;

UNLOCK_RETURN:
        __UNLOCK_MUTEX;
        return nRet;
    }
    //--------------------------------------------------------------------
    void DeInitFKLogger()
    {
        __LOCK_MUTEX;
        s_pLogWriter->m_LogDeInit( s_pLogWriter );
        s_pLogWriter = 0;
        __UNLOCK_MUTEX;
    
        #ifndef DISABLE_THREAD_SAFE
            FKLogger::FKDestroyMutex( &s_Mutex );
            s_Mutex = 0;
        #endif
    }
    //--------------------------------------------------------------------
	static int ReallyLogImplW( FKLogger::ENUM_LogLevel p_eLevel, const char* p_szModuleName, 
		const char* p_szFile, const char* p_szFuncName, const int p_nLineNum,
		const wchar_t* p_szFmt, va_list p_Ap )
	{
		int nRet = 0;

		CHECK_AND_INIT_LOGGER;

		__LOCK_MUTEX;

		nRet = s_pLogWriter->m_LogW( s_pLogWriter, p_eLevel, p_szModuleName,
			p_szFile, p_szFuncName, p_nLineNum, p_szFmt, p_Ap );

		__UNLOCK_MUTEX;

		return nRet;
	}
	//--------------------------------------------------------------------
    static int ReallyLogImpl( FKLogger::ENUM_LogLevel p_eLevel, const char* p_szModuleName, 
        const char* p_szFile, const char* p_szFuncName, const int p_nLineNum,
        const char* p_szFmt, va_list p_Ap )
    {
        int nRet = 0;

        CHECK_AND_INIT_LOGGER;

        __LOCK_MUTEX;

        nRet = s_pLogWriter->m_Log( s_pLogWriter, p_eLevel, p_szModuleName,
            p_szFile, p_szFuncName, p_nLineNum, p_szFmt, p_Ap );

        __UNLOCK_MUTEX;

        return nRet;
    }
    //--------------------------------------------------------------------
	int LogImpl( FKLogger::ENUM_LogLevel p_eLevel, const char* p_szModuleName, 
		const char* p_szFile, const char* p_szFuncName, const int p_nLineNum,
		const wchar_t* p_szFmt, ... )
	{
		int nRet = 0;

		va_list ap;
		va_start( ap, p_szFmt );
		nRet = ReallyLogImplW( p_eLevel, p_szModuleName, p_szFile,
			p_szFuncName, p_nLineNum, p_szFmt, ap );
		va_end( ap );

		return nRet;
	}
	//--------------------------------------------------------------------
    int LogImpl( FKLogger::ENUM_LogLevel p_eLevel, const char* p_szModuleName, 
        const char* p_szFile, const char* p_szFuncName, const int p_nLineNum,
        const char* p_szFmt, ... )
    {
        int nRet = 0;

        va_list ap;
        va_start( ap, p_szFmt );
        nRet = ReallyLogImpl( p_eLevel, p_szModuleName, p_szFile,
            p_szFuncName, p_nLineNum, p_szFmt, ap );
        va_end( ap );

        return nRet;
    }
    //--------------------------------------------------------------------
    int FKLogFunEntry( const char* p_szFunName )
    {
        int nRet = 0;

        CHECK_AND_INIT_LOGGER;

        __LOCK_MUTEX;
        nRet = s_pLogWriter->m_LogFunEntry( s_pLogWriter, p_szFunName );
        __UNLOCK_MUTEX;

        return nRet;
    }
    //--------------------------------------------------------------------
    int FKLogFunExit( const char* p_szFunName, const int p_nLineNumber )
    {
        int nRet = 0;

        CHECK_AND_INIT_LOGGER;

        __LOCK_MUTEX;
        nRet = s_pLogWriter->m_LogFunExit( s_pLogWriter, p_szFunName, p_nLineNumber );
        __UNLOCK_MUTEX;

        return nRet;
    }
    //--------------------------------------------------------------------
#endif