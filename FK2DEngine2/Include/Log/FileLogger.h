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

#ifndef _FILE_LOGGER_H_
#define _FILE_LOGGER_H_

//--------------------------------------------------------------------
namespace FKLogger
{
    // 文件打开类型
    typedef enum ENUM_FileOpenMode
    {
        EFOM_ClearMode = 0,
        EFOM_AppendMode
    }EFileOpenMode;

    // 文件Log初始化参数
    typedef struct SFileLoggerInitParams
    {
        // 文件Log的文件名
        char*               m_pFileName;
        ENUM_FileOpenMode   m_eMode;

        SFileLoggerInitParams()
        {
            m_pFileName = 0;
            m_eMode = EFOM_ClearMode;
        }
    }file_logger_init_params;
}
//--------------------------------------------------------------------
#endif