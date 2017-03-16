/********************************************************************
*
*	Copyright(c) FreeKnightDuzhi 2011
*   License： LGPL
*   E-Mail：duzhi5368@163.com
* 	
*	-----------------------------------------------------------------
*
*	文件名：	LogConfig
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*	创建时间：	2011/08/02
*
*	修改人:		
*	修改内容:
*********************************************************************/

#ifndef _LOG_CONFIG_H_
#define _LOG_CONFIG_H_
//--------------------------------------------------------------------
// 默认Log层级
#ifndef LOG_DEFAULT_LEVEL
#define LOG_DEFAULT_LEVEL FK_LOG_LEVEL_TRACE
#endif

#ifndef FK_LOG_LEVEL
#define FK_LOG_LEVEL LOG_DEFAULT_LEVEL
#endif
//--------------------------------------------------------------------
// 默认Log模块名称
#ifndef LOG_DEFAULT_MODULE_NAME
#define LOG_DEFAULT_MODULE_NAME "Unknown Module"
#endif
//--------------------------------------------------------------------
// 默认文件名称
#ifndef DEFAULT_FILE_LOG_NAME
#define DEFAULT_FILE_LOG_NAME "FKLog.txt"
#endif
//--------------------------------------------------------------------
// SocketLog单次消息最大长度
#ifndef MAX_SOCKET_BUF_SIZE
#define MAX_SOCKET_BUF_SIZE 1024
#endif
//--------------------------------------------------------------------
#endif