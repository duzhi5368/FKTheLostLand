/**
*	created:		2013-4-17   23:33
*	filename: 		CenterServerCodeMsgParser
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ClientObj.h"
#include "Server.h"
#include <map>
//------------------------------------------------------------------------
typedef WORD MSG_KEY;
using std::map;
//------------------------------------------------------------------------
typedef bool (*CodeMsgCallback)( CClientObj * pObject, PMIRMSG pMsg, int datasize );
//------------------------------------------------------------------------
class CCenterSvrMsgParser : public xSingletonClass< CCenterSvrMsgParser >
{
public:
	CCenterSvrMsgParser();
	~CCenterSvrMsgParser();
public:
	// 接受网络消息
	bool	OnRecvCodeMsg( CClientObj * pObject, PMIRMSG pMsg, int datasize );
private:
	bool	__Init();
	void	__Release();
public:
	bool	RegisterMsgFunc( MSG_KEY, CodeMsgCallback );
	bool	UnRegisterMsgFunc( MSG_KEY );
private:
	typedef std::map< MSG_KEY, CodeMsgCallback >		MSG_FUNC_MAP;
	MSG_FUNC_MAP		m_mapMsgHandlers;
};
//------------------------------------------------------------------------
class CCodeMsgFunc
{
public:
	// 获取GS地址
	static bool OnMsg_GetGameSvrAddr( CClientObj * pObject, PMIRMSG pMsg, int datasize );
	// 注册服务器
	static bool OnMsg_RegisterSvr( CClientObj * pObject, PMIRMSG pMsg, int datasize );
	// 更新服务器连接数
	static bool OnMsg_UpdateSvrInfo( CClientObj * pObject, PMIRMSG pMsg, int datasize );
	// 根据服务器名查找服务器IP
	static bool OnMsg_FindSvr( CClientObj * pObject, PMIRMSG pMsg, int datasize );
	// 获取GS名称列表
	static bool OnMsg_GSNameList( CClientObj * pObject, PMIRMSG pMsg, int datasize );


	// 服务器间的消息传递消息【中心服务器负责查找指定服务器并进行消息转发】
	static bool OnMsg_AcrossSvr( CClientObj * pObject, PMIRMSG pMsg, int datasize );
};
//------------------------------------------------------------------------