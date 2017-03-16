/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FKMutexWin
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include <windows.h>
#include "../../Include/Log/FKMutex.h"

//--------------------------------------------------------------------
// 创建线程锁
int FKLogger::FKCreateMutex( FKMutex* p_pMutex )
{
    if( p_pMutex == NULL )
    {
        return -1;
    }

    HANDLE hMutex = CreateMutex( NULL, FALSE, NULL );

    if( hMutex == INVALID_HANDLE_VALUE )
    {
        return -2;
    }

    *p_pMutex = hMutex;
    return 0;
}
//--------------------------------------------------------------------
// 锁定
int FKLogger::FKLockMutex( FKMutex p_Mutex )
{
    if( p_Mutex == INVALID_HANDLE_VALUE )
    {
        return -1;
    }

    if( WaitForSingleObject( p_Mutex, INFINITE ) != WAIT_OBJECT_0 )
    {
        return -2;
    }
    return 0;
}
//--------------------------------------------------------------------
// 解锁
int FKLogger::FKUnlockMutex( FKMutex p_Mutex )
{
    if( p_Mutex == INVALID_HANDLE_VALUE )
    {
        return -1;
    }

    if( ReleaseMutex( p_Mutex ) == 0 )
    {
        return -2;
    }

    return 0;
}
//--------------------------------------------------------------------
// 销毁线程锁
int FKLogger::FKDestroyMutex( FKMutex* p_pMutex )
{
    if( (p_pMutex == NULL) || ((*p_pMutex) == INVALID_HANDLE_VALUE) )
    {
        return -1;
    }

    if( CloseHandle( (HANDLE)*p_pMutex ) != 0 )
    {
        return -2;
    }
    
    *p_pMutex = 0;
    return 0;
}
//--------------------------------------------------------------------