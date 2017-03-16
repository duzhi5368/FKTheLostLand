/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	FKSocket
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _FK_SOCKET_H_
#define _FK_SOCKET_H_
//--------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
    #include <winsock2.h>
    typedef SOCKET FKSocket;
#elif defined(__unix) || defined(__linux)
    typedef int FKSocket;
#else
#endif
//--------------------------------------------------------------------
namespace FKLogger
{
    // 创建一个Socket并连接
    int FKCreateConnectedSocket( const char* p_pServerName, int p_nPort, FKSocket* p_pSockHandle );
    // 发送Log数据到Log服务器
    int FKSendLog( FKSocket p_SocketHandle, const char* p_pData, const int p_nDataSize );
	int	FKSendLog( FKSocket p_SocketHandle, const wchar_t* p_pData, const int p_nDataSize );
    // 关闭销毁一个Socket连接
    int FKDestroySocket( FKSocket* p_pSocket );
}
//--------------------------------------------------------------------
#endif