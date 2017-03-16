/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FKMutex
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _FK_MUTEX_H_
#define _FK_MUTEX_H_
//--------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
    #include <windows.h>
    typedef HANDLE FKMutex;
#elif defined(__unix) || defined(__linux)
    #include <pthread.h>
    typedef pthread_mutex_t* FKMutex;
#else
#endif
//--------------------------------------------------------------------
namespace FKLogger
{
    // 创建线程锁
    int FKCreateMutex( FKMutex* p_pMutex );
    // 锁定
    int FKLockMutex( FKMutex p_Mutex );
    // 解锁
    int FKUnlockMutex( FKMutex p_Mutex );
    // 销毁线程锁
    int FKDestroyMutex( FKMutex* p_pMutex );
}
//--------------------------------------------------------------------
#endif