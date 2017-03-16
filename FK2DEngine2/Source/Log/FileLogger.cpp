/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FileLogger
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../Include/Log/LogConfig.h"
#include "../../Include/Log/FileLoggerImpl.h"
#include "../../Include/Log/FKTime.h"
#include "../../Include/FKStringConvert.h"
#include <stdio.h>
#include <memory.h>
#include <locale.h>
//--------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
    #define  vsnprintf(buf,buf_size,fmt,ap) _vsnprintf(buf,buf_size,fmt,ap);
    #define	inline __inline
#endif
//--------------------------------------------------------------------
static int WriteToFile( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
                       const char* p_pModuleName, const char* p_pFile, const char* p_pFuncName,
                       const int p_nLineNum, const char* p_pFmt, va_list p_Ap );
static int WriteToFileW( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
					   const char* p_pModuleName, const char* p_pFile, const char* p_pFuncName,
					   const int p_nLineNum, const wchar_t* p_pFmt, va_list p_Ap );
static int FileFunLogEntry( FKLogger::SLogWriter* p_pThis, const char* p_pFuncName );
static int FileFunLogExit( FKLogger::SLogWriter* p_pThis, const char* p_pFuncName, const int p_nLineNumber );
static int FileLogDeInit( FKLogger::SLogWriter* p_pThis );
static const char* GetLogPrefix( const FKLogger::ENUM_LogLevel p_eLevel );
//--------------------------------------------------------------------
typedef struct SFileLogWriter
{
    FKLogger::SLogWriter        m_Base;
    FILE*                       m_pFp;
}file_log_writer;
//--------------------------------------------------------------------
static SFileLogWriter tagFileLogWriter = 
{
    {
        WriteToFile,
		WriteToFileW,
        FileFunLogEntry,
        FileFunLogExit,
        FileLogDeInit,
    },
    NULL
};
//--------------------------------------------------------------------
int FKLogger::InitFileLogger( FKLogger::SLogWriter** p_ppLogWriter, FKLogger::SFileLoggerInitParams* p_pParams )
{
    char* pFileOpenMode = "w";
    if(( p_ppLogWriter == NULL ) || ( p_pParams == NULL ))
    {
        return -1;
    }

    *p_ppLogWriter = NULL;
    if( p_pParams->m_pFileName == NULL )
    {
        return -2;
    }
    
    if( tagFileLogWriter.m_pFp != NULL )
    {
        FileLogDeInit( (FKLogger::SLogWriter*)&tagFileLogWriter );
    }

    switch( p_pParams->m_eMode )
    {
    case FKLogger::EFOM_AppendMode:
        pFileOpenMode = "a";
        break;
    case FKLogger::EFOM_ClearMode:
        pFileOpenMode = "w";
        break;
    default:
        break;
    }

    fopen_s( &tagFileLogWriter.m_pFp, p_pParams->m_pFileName, pFileOpenMode );
    if( tagFileLogWriter.m_pFp == NULL )
    {
        return -3;
    }

    char szCurDateTime[32] = { 0 };
    if( FKLogger::GetCurrentDateTime( szCurDateTime, sizeof(szCurDateTime) ) == 0 )
    {
        fprintf_s( tagFileLogWriter.m_pFp, "\n[----------------------------------------]\n[FKLogger start work: %s] \n[----------------------------------------]\n\n", szCurDateTime );
    }

    *p_ppLogWriter = ( FKLogger::SLogWriter* )&tagFileLogWriter;
    return 0;
}
//--------------------------------------------------------------------
int FKLogger::InitConsoleLogger( FKLogger::SLogWriter** p_ppLogWriter, void* p_pInitParams )
{
    char szCurDateTime[32] = { 0 };
    if( p_ppLogWriter == NULL )
    {
        return -1;
    }

    *p_ppLogWriter = NULL;

    if( tagFileLogWriter.m_pFp != NULL )
    {
        FileLogDeInit( (FKLogger::SLogWriter*)&tagFileLogWriter );
    }

    if( ( p_pInitParams != stdout ) && ( p_pInitParams != stderr ) )
    {
        p_pInitParams = stdout;
    }

    tagFileLogWriter.m_pFp = (FILE*)p_pInitParams;

    if( FKLogger::GetCurrentDateTime( szCurDateTime, sizeof(szCurDateTime) ) == 0 )
    {
        fprintf_s( tagFileLogWriter.m_pFp, "\n[----------------------------------------]\n[FKLogger start work: %s] \n[----------------------------------------]\n\n", szCurDateTime );
    }

    *p_ppLogWriter = ( FKLogger::SLogWriter* )&tagFileLogWriter;
    return 0;
}
//--------------------------------------------------------------------
static wchar_t szFileUnicodeFormatBuf[2048];
//--------------------------------------------------------------------
static int WriteToFile( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
                       const char* p_pModuleName, const char* p_pFile, const char* p_pFuncName,
                       const int p_nLineNum, const char* p_pFmt, va_list p_Ap )
{
    SFileLogWriter* pFileLogWriter = (SFileLogWriter*)p_pThis;
    if(( p_pThis == NULL ) || ( pFileLogWriter->m_pFp == NULL ))
    {
        return -1;
    }

    fprintf_s( pFileLogWriter->m_pFp, GetLogPrefix( p_eLogLevel ) );
    fprintf_s( pFileLogWriter->m_pFp, " - %s - %s - 函数%s %5d行 ", p_pModuleName, p_pFile, p_pFuncName, p_nLineNum );
	vfprintf_s( pFileLogWriter->m_pFp, p_pFmt, p_Ap );
    fprintf_s( pFileLogWriter->m_pFp, "\n" );
    fflush( pFileLogWriter->m_pFp );

    return 0;
}
//--------------------------------------------------------------------
static int WriteToFileW( FKLogger::SLogWriter* p_pThis, const FKLogger::ENUM_LogLevel p_eLogLevel,
					   const char* p_pModuleName, const char* p_pFile, const char* p_pFuncName,
					   const int p_nLineNum, const wchar_t* p_pFmt, va_list p_Ap )
{
	SFileLogWriter* pFileLogWriter = (SFileLogWriter*)p_pThis;
	if(( p_pThis == NULL ) || ( pFileLogWriter->m_pFp == NULL ))
	{
		return -1;
	}
	setlocale(LC_ALL, "chinese-simplified"); 

	fprintf_s( pFileLogWriter->m_pFp, GetLogPrefix( p_eLogLevel ) );
	fprintf_s( pFileLogWriter->m_pFp, " - %s - %s - 函数%s %5d行 ", p_pModuleName, p_pFile, p_pFuncName, p_nLineNum );
	vfwprintf( pFileLogWriter->m_pFp, p_pFmt, p_Ap );
	fprintf_s( pFileLogWriter->m_pFp, "\n" );
	fflush( pFileLogWriter->m_pFp );

	//fprintf_s( pFileLogWriter->m_pFp, GetLogPrefix( p_eLogLevel ) );
	//fprintf_s( pFileLogWriter->m_pFp, " - %s - %s - 函数%s %5d行 ", p_pModuleName, p_pFile, p_pFuncName, p_nLineNum );
	//wchar_t m_szCache[2048];
	//vswprintf( m_szCache, p_pFmt, p_Ap );
	//fputws( m_szCache, pFileLogWriter->m_pFp );
	//fprintf_s( pFileLogWriter->m_pFp, "\n" );
	//fflush( pFileLogWriter->m_pFp );

	return 0;
}
//--------------------------------------------------------------------
static int FileFunLogEntry( FKLogger::SLogWriter* p_pThis, const char* p_pFuncName )
{
    SFileLogWriter* pFileLogWriter = (SFileLogWriter*)p_pThis;
    if(( p_pThis == NULL ) || ( pFileLogWriter->m_pFp == NULL ))
    {
        return -1;
    }

    int nBytesWritten = 0;
    nBytesWritten = fprintf_s( pFileLogWriter->m_pFp, "[--- %s \n", p_pFuncName );
    fflush( pFileLogWriter->m_pFp );

    return nBytesWritten;
}
//--------------------------------------------------------------------
static int FileFunLogExit( FKLogger::SLogWriter* p_pThis, const char* p_pFuncName, const int p_nLineNumber )
{
    SFileLogWriter* pFileLogWriter = (SFileLogWriter*)p_pThis;
    if(( p_pThis == NULL ) || ( pFileLogWriter->m_pFp == NULL ))
    {
        return -1;
    }

    int nBytesWritten = 0;
    nBytesWritten = fprintf_s( pFileLogWriter->m_pFp, "%s : %d ---]\n", p_pFuncName, p_nLineNumber );
    fflush( pFileLogWriter->m_pFp );

    return nBytesWritten;
}
//--------------------------------------------------------------------
static int FileLogDeInit( FKLogger::SLogWriter* p_pThis )
{
    SFileLogWriter* pFileLogWriter = (SFileLogWriter*)p_pThis;
    if(( pFileLogWriter != NULL ) && ( pFileLogWriter->m_pFp != NULL ))
    {
        if(( pFileLogWriter->m_pFp != stdout ) && ( pFileLogWriter->m_pFp != stderr ))
        {
            fclose( pFileLogWriter->m_pFp );
        }
    }

    pFileLogWriter->m_pFp = NULL;

    return 0;
}
//--------------------------------------------------------------------
static const char* GetLogPrefix( const FKLogger::ENUM_LogLevel p_eLevel )
{
    switch( p_eLevel )
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