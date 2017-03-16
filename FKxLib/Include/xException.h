/**
*	created:		2013-4-16   0:58
*	filename: 		xException
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#ifndef EXCEPTION_ON
	#define TRY_BEGIN
	#define TRY_END
	#define TRY_END_NOTHIS
	#define	TRY_INIT
	#define	TRY_END_RETURN(ret)
#else
#pragma warning( disable : 4313 4297 4244 4355 4311 4312 4172 )
#define	TRY_INIT	{ \
	FILE * fp = ::fopen( EXCEPTION_LOG_FILE, "a+" );\
	if( fp )\
								{\
								SYSTEMTIME	stNow;\
								GetLocalTime( &stNow );\
								fprintf( fp, "\n[%04u-%02u-%02u %02u:%02u:%02u.%03u] [NEW INSTANCE]\n",\
								stNow.wYear, stNow.wMonth, stNow.wDay, stNow.wHour, stNow.wMinute, stNow.wSecond, stNow.wMilliseconds);\
								fclose( fp );\
								}\
							}
#define TRY_BEGIN try {
#define TRY_END	} \
	catch(...) \
				{ \
				FILE * fp = ::fopen( EXCEPTION_LOG_FILE,"a+"); \
				if(fp) \
					{ \
					unsigned long nLen = __LINE__;\
					char temp[1024];\
					SYSTEMTIME	stNow;\
					GetLocalTime( &stNow );\
					::sprintf(temp,"[%04u-%02u-%02u %02u:%02u:%02u.%03u] %s %05d 0x%08x ", \
					stNow.wYear, stNow.wMonth, stNow.wDay, stNow.wHour, stNow.wMinute, stNow.wSecond, stNow.wMilliseconds\
					,__FILE__, nLen, (LPVOID)this );\
					::fwrite(temp,strlen(temp),1,fp);\
					::fwrite(__FUNCTION__,sizeof(__FUNCTION__) - 1,1,fp); \
					::fwrite("\r\n",2,1,fp); \
					::fclose(fp); \
					} \
					throw; \
				}
#define TRY_END_NOTHIS	} \
	catch(...) \
				{ \
				FILE * fp = ::fopen( EXCEPTION_LOG_FILE,"a+"); \
				if(fp) \
					{ \
					unsigned long nLen = __LINE__;\
					char temp[1024];\
					SYSTEMTIME	stNow;\
					GetLocalTime( &stNow );\
					::sprintf(temp,"[%04u-%02u-%02u %02u:%02u:%02u.%03u] %s %05d ", \
					stNow.wYear, stNow.wMonth, stNow.wDay, stNow.wHour, stNow.wMinute, stNow.wSecond, stNow.wMilliseconds\
					,__FILE__, nLen );\
					::fwrite(temp,strlen(temp),1,fp);\
					::fwrite(__FUNCTION__,sizeof(__FUNCTION__) - 1,1,fp); \
					::fwrite("\r\n",2,1,fp); \
					::fclose(fp); \
					} \
					throw; \
				}
#define TRY_END_RETURN(ret)	} \
	catch(...) \
				{ \
				FILE * fp = ::fopen( EXCEPTION_LOG_FILE,"a+"); \
				if(fp) \
					{ \
					unsigned long nLen = __LINE__;\
					char temp[1024];\
					SYSTEMTIME	stNow;\
					GetLocalTime( &stNow );\
					::sprintf(temp,"[%04u-%02u-%02u %02u:%02u:%02u.%03u] %s %05d 0x%08x ", \
					stNow.wYear, stNow.wMonth, stNow.wDay, stNow.wHour, stNow.wMinute, stNow.wSecond, stNow.wMilliseconds\
					,__FILE__, nLen, (LPVOID)this );\
					::fwrite(temp,strlen(temp),1,fp);\
					::fwrite(__FUNCTION__,sizeof(__FUNCTION__) - 1,1,fp); \
					::fwrite("\r\n",2,1,fp); \
					::fclose(fp); \
					} \
					return (ret); \
				}
#endif
//------------------------------------------------------------------------