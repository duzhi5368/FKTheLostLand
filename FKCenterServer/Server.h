/**
*	created:		2013-4-15   22:06
*	filename: 		Server
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "clientobj.h"
#include "FKCenterServerDefine.h"
//------------------------------------------------------------------------
typedef struct tagSERVERARRAY
{
	UINT	Ids[64];
	int		count;
	int		pickptr;
	tagSERVERARRAY()
	{
		count = 0;
		pickptr = 0;
	}
	void	DelId( UINT id )
	{
		int i = 0;
		for( i = 0;i < count;i ++ )
		{
			if( Ids[i] == id )
			{
				for( int j = i;j < count-1;j ++ )
				{
					Ids[j] = Ids[j+1];
				}
				count --;
				break;
			}
		}
	}
	BOOL	AddId( UINT id )
	{
		if( count >= 64 )return FALSE;
		Ids[count++] = id;
		return TRUE;
	}
}SERVERARRAY;
//------------------------------------------------------------------------
class CServer :
	public CBaseServer,
	public xIndexObjectPool<CClientObj>,
	public xSingletonClass<CServer>
{
public:
	CServer(void);
	virtual ~CServer(void);
public:
	// 根据ID获取指定连接
	CClientObject * GetClientObject( UINT id ){ return getObject( id );}
	// 创建一个新连接
	CClientObject * NewClientObject();
	// 删除指定连接
	VOID DeleteClientObject( CClientObject * pObject );
	// 初始化服务器
	BOOL InitServer(CSettingFile&);
	// 清除服务器
	VOID CleanServer();
	// 每帧更新
	VOID Update();
	// 输入框输入字符处理
	VOID OnInput( const char * pszString );
	// 输出命令表
	VOID OutputCmdList();
public:
	SERVER_ERROR RegisterServer( CClientObj * pObj, REGISTER_SERVER_INFO * pInfo, REGISTER_SERVER_RESULT * pResult );
	SERVER_ERROR UnRegisterServer( CClientObj * pObj );
	SERVER_ERROR FindServer( servertype type, const char * pszName, FINDSERVER_RESULT * pResult );
	SERVER_ERROR GetGameServerName( string& namelist );
public:
	VOID SendDBServer( SERVERADDR * pAddr, int count );
	int	PrepareServer( int type, int count, SERVERADDR * pAddrArray );
protected:
	SERVERARRAY	m_ServerArrays[ST_GAMESERVER];
	CIndexListEx<CClientObj/*, MAX_CLIENTOBJECT*/>	m_ClientObjects;
};
//------------------------------------------------------------------------