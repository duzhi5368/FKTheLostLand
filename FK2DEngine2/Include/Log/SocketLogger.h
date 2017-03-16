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

#ifndef _SOCKET_LOGGER_H_
#define _SOCKET_LOGGER_H_
//--------------------------------------------------------------------
namespace FKLogger
{
    typedef struct SSocketLoggerInitParams
    {
        char*       m_pServer;
        int         m_nPort;

        SSocketLoggerInitParams()
        {
            m_pServer = NULL;
            m_nPort = 0;
        }
    }socket_logger_init_params;
}
//--------------------------------------------------------------------
#endif