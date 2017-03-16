/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FKTime
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../Include/Log/FKTime.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------
int FKLogger::GetCurrentDateTime( char* p_pStr, int p_nStrLen )
{
    time_t t;
    struct tm* tmp;

    t = time( NULL );
    tmp = localtime( &t );

    if( tmp == NULL )
    {
        return -1;
    }

    if( strftime( p_pStr, p_nStrLen, " %c ", tmp ) == 0 )
    {
        return -2;
    }

    return 0;
}
//--------------------------------------------------------------------