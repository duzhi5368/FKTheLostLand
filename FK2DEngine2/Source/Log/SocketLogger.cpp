/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	SocketLogger
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../Include/Log/FKSocket.h"
#include "../../Include/Log/FKTime.h"
#include "../../Include/Log/SocketLogger.h"
#include "../../Include/Log/SocketLoggerImpl.h"
#include "../../Include/Log/LogObject.h"
#include "../../Include/Log/LogConfig.h"
#include <stdio.h>

//--------------------------------------------------------------------
#pragma warning( disable:4996 )
//--------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
    #define __func__ __FUNCTION__
    #define snprintf _snprintf_s
#endif
//--------------------------------------------------------------------
static int SendToSock( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
                      const char* p_szModuleName, const char* p_szFile, const char* p_szFuncName,
                      const int p_nLineNum, const char* p_pFmt, va_list p_Ap );
static int SendToSockW( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
					  const char* p_szModuleName, const char* p_szFile, const char* p_szFuncName,
					  const int p_nLineNum, const wchar_t* p_pFmt, va_list p_Ap );
static int SockFunLogEntry( FKLogger::SLogWriter* p_pThis, const char* p_szFuncName );
static int SockFunLogExit( FKLogger::SLogWriter* p_pThis, const char* p_szFuncName, const int p_nLineNum );
static int SockLogDeInit( FKLogger::SLogWriter* p_pThis );
static const char* GetLogPrefix( const FKLogger::ENUM_LogLevel p_eLogLevel );
//--------------------------------------------------------------------
typedef struct SSockLogWriter
{
    FKLogger::SLogWriter        m_Base;
    FKSocket                    m_Sock;
}sock_log_writer;
//--------------------------------------------------------------------
static SSockLogWriter tagSockLogWriter = 
{
    {
        SendToSock,
		SendToSockW,
        SockFunLogEntry,
        SockFunLogExit,
        SockLogDeInit,
    },
    0
};
//--------------------------------------------------------------------
int FKLogger::InitSocketLogger( FKLogger::SLogWriter** p_ppLogWriter,FKLogger::SSocketLoggerInitParams *p_pParams )
{
    if(( p_ppLogWriter == NULL ) || ( p_pParams == NULL ) || ( p_pParams->m_pServer == NULL ))
    {
        return -1;
    }

    *p_ppLogWriter = NULL;

    if( tagSockLogWriter.m_Sock != NULL )
    {
        SockLogDeInit( (FKLogger::SLogWriter*)&tagSockLogWriter );
    }

    if( FKLogger::FKCreateConnectedSocket( p_pParams->m_pServer, p_pParams->m_nPort, &tagSockLogWriter.m_Sock ) != 0 )
    {
        return -2;
    }

    char szCurDateTime[32] = { 0 };
    char szTempBuffer[128] = { 0 };
    if( FKLogger::GetCurrentDateTime( szCurDateTime, sizeof(szCurDateTime) ) == 0 )
    {
        int nBytes = snprintf( szTempBuffer, sizeof( szTempBuffer ), "\n [FKLogger start work: %s] \n", szCurDateTime );
        if( (nBytes <= 0) || (nBytes > sizeof(szTempBuffer)) )
        {
            nBytes = sizeof(szTempBuffer);
        }
        FKLogger::FKSendLog( tagSockLogWriter.m_Sock, szTempBuffer, nBytes );
    }

    *p_ppLogWriter = ( FKLogger::SLogWriter* )&tagSockLogWriter;
    return 0;
}
//--------------------------------------------------------------------
static int SendToSockW( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
					  const char* p_szModuleName, const char* p_szFile, const char* p_szFuncName,
					  const int p_nLineNum, const wchar_t* p_pFmt, va_list p_Ap )
{
	SSockLogWriter* pSockLogWriter = (SSockLogWriter*)p_pThis;
	if(( pSockLogWriter == NULL ) || ( pSockLogWriter->m_Sock < 0 ))
	{
		return -1;
	}

	wchar_t szBuf[MAX_SOCKET_BUF_SIZE / 2] = { 0 };
	int nBytes = 0;
	nBytes = _snwprintf_s( szBuf, MAX_SOCKET_BUF_SIZE - 1, L"\n%s:%s:%s:%s:%s:%d", GetLogPrefix(p_eLogLevel),
		p_szModuleName, p_szFile, p_szFuncName, p_nLineNum );
	if( nBytes < (MAX_SOCKET_BUF_SIZE / 2 -1) )
	{
		nBytes += vswprintf_s( szBuf + nBytes * 2, MAX_SOCKET_BUF_SIZE / 2 - 1 - nBytes, p_pFmt, p_Ap );
	}
	szBuf[ MAX_SOCKET_BUF_SIZE / 2 - 1 ] = 0;

	if(( nBytes < 0 ) || ( nBytes > MAX_SOCKET_BUF_SIZE / 2 - 1 ))
	{
		nBytes = MAX_SOCKET_BUF_SIZE / 2 - 1;
	}

	return FKLogger::FKSendLog( pSockLogWriter->m_Sock, szBuf, nBytes );
}
//--------------------------------------------------------------------
static int SendToSock( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
                      const char* p_szModuleName, const char* p_szFile, const char* p_szFuncName,
                      const int p_nLineNum, const char* p_pFmt, va_list p_Ap )
{
    SSockLogWriter* pSockLogWriter = (SSockLogWriter*)p_pThis;
    if(( pSockLogWriter == NULL ) || ( pSockLogWriter->m_Sock < 0 ))
    {
        return -1;
    }

    char szBuf[MAX_SOCKET_BUF_SIZE] = { 0 };
    int nBytes = 0;
    nBytes = snprintf( szBuf, MAX_SOCKET_BUF_SIZE - 1, "\n%s:%s:%s:%s:%s:%d", GetLogPrefix(p_eLogLevel),
        p_szModuleName, p_szFile, p_szFuncName, p_nLineNum );
    if( nBytes < (MAX_SOCKET_BUF_SIZE -1) )
    {
        nBytes += vsnprintf( szBuf + nBytes, MAX_SOCKET_BUF_SIZE - 1 - nBytes, p_pFmt, p_Ap );
    }
    szBuf[ MAX_SOCKET_BUF_SIZE - 1 ] = 0;

    if(( nBytes < 0 ) || ( nBytes > MAX_SOCKET_BUF_SIZE - 1 ))
    {
        nBytes = MAX_SOCKET_BUF_SIZE - 1;
    }

    return FKLogger::FKSendLog( pSockLogWriter->m_Sock, szBuf, nBytes );
}
//--------------------------------------------------------------------
static int SockFunLogEntry( FKLogger::SLogWriter* p_pThis, const char* p_szFuncName )
{
    SSockLogWriter* pSockLogWriter = (SSockLogWriter*)p_pThis;
    if(( pSockLogWriter == NULL ) || ( pSockLogWriter->m_Sock < 0 ))
    {
        return -1;
    }

    char szBuf[MAX_SOCKET_BUF_SIZE] = { 0 };
    int nBytes = 0;

#if defined(WIN32) || defined(_WIN32)
    nBytes = _snprintf( szBuf, MAX_SOCKET_BUF_SIZE - 1, "\n [ %s", p_szFuncName );
#else
    nBytes = snprintf( szBuf, MAX_SOCKET_BUF_SIZE - 1, "\n [ %s", p_szFuncName );
#endif

    szBuf[MAX_SOCKET_BUF_SIZE - 1] = 0;
    if(( nBytes < 0 ) || ( nBytes > MAX_SOCKET_BUF_SIZE - 1 ))
    {
        nBytes = MAX_SOCKET_BUF_SIZE - 1;
    }

    return FKLogger::FKSendLog( pSockLogWriter->m_Sock, szBuf, nBytes );
}
//--------------------------------------------------------------------
static int SockFunLogExit( FKLogger::SLogWriter* p_pThis, const char* p_szFuncName, const int p_nLineNum )
{
    SSockLogWriter* pSockLogWriter = (SSockLogWriter*)p_pThis;
    if(( pSockLogWriter == NULL ) || ( pSockLogWriter->m_Sock < 0 ))
    {
        return -1;
    }

    char szBuf[MAX_SOCKET_BUF_SIZE] = { 0 };
    int nBytes = 0;

#if defined(WIN32) || defined(_WIN32)
    nBytes = _snprintf( szBuf, MAX_SOCKET_BUF_SIZE - 1, "\n %s : %d ]", p_szFuncName, p_nLineNum );
#else
    nBytes = snprintf( szBuf, MAX_SOCKET_BUF_SIZE - 1, "\n %s: %d ]", p_szFuncName, p_nLineNum );
#endif

    szBuf[MAX_SOCKET_BUF_SIZE - 1] = 0;
    if(( nBytes < 0 ) || ( nBytes > MAX_SOCKET_BUF_SIZE - 1 ))
    {
        nBytes = MAX_SOCKET_BUF_SIZE - 1;
    }

    return FKLogger::FKSendLog( pSockLogWriter->m_Sock, szBuf, nBytes );
}
//--------------------------------------------------------------------
static int SockLogDeInit( FKLogger::SLogWriter* p_pThis )
{
    SSockLogWriter* pSockLogWriter = (SSockLogWriter*)p_pThis;
    if( pSockLogWriter != NULL )
    {
        FKLogger::FKDestroySocket( &pSockLogWriter->m_Sock );
    }
    return 0;
}
//--------------------------------------------------------------------
static const char* GetLogPrefix( const FKLogger::ENUM_LogLevel p_eLogLevel )
{
    switch( p_eLogLevel )
    {
    case FKLogger::ELL_Trace: return "[追踪]";
    case FKLogger::ELL_Debug: return "[调试]";
    case FKLogger::ELL_Info: return "[信息]";
    case FKLogger::ELL_Warn: return "[警告]";
    case FKLogger::ELL_Error: return "[错误]";
    case FKLogger::ELL_Fatal: return "[严重]";
    default:
        break;
    }
    return "[未知]";
}
//--------------------------------------------------------------------