/**
*	created:		2013-4-18   0:35
*	filename: 		CenterServerCodeMsgParser
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "CenterServerCodeMsgParser.h"
//------------------------------------------------------------------------
CCenterSvrMsgParser::CCenterSvrMsgParser()
{
	__Init();
}
//------------------------------------------------------------------------
CCenterSvrMsgParser::~CCenterSvrMsgParser()
{
	__Release();
}
//------------------------------------------------------------------------
bool CCenterSvrMsgParser::OnRecvCodeMsg( CClientObj * pObject, PMIRMSG pMsg, int datasize )
{
	MSG_FUNC_MAP::const_iterator Ite = m_mapMsgHandlers.find( pMsg->wCmd );
	if( Ite == m_mapMsgHandlers.end() )
	{
		return false;
	}

	CodeMsgCallback Func = Ite->second;
	return Func( pObject, pMsg, datasize );
}
//------------------------------------------------------------------------
bool CCenterSvrMsgParser::__Init()
{
	m_mapMsgHandlers.clear();

	bool bRet = true;

#define REGISTER_MSG_FUNC(a,b) RegisterMsgFunc(a,&b)

	bRet &= REGISTER_MSG_FUNC(SCM_GETGAMESERVERADDR,CCodeMsgFunc::OnMsg_GetGameSvrAddr);	
	bRet &= REGISTER_MSG_FUNC(SCM_REGISTERSERVER,CCodeMsgFunc::OnMsg_RegisterSvr);
	bRet &= REGISTER_MSG_FUNC(SCM_UPDATESERVERINFO,CCodeMsgFunc::OnMsg_UpdateSvrInfo);	
	bRet &= REGISTER_MSG_FUNC(SCM_FINDSERVER,CCodeMsgFunc::OnMsg_FindSvr);
	bRet &= REGISTER_MSG_FUNC(SCM_MSGACROSSSERVER,CCodeMsgFunc::OnMsg_AcrossSvr);	
	bRet &= REGISTER_MSG_FUNC(SCM_MSGGSNAMELIST,CCodeMsgFunc::OnMsg_GSNameList);

#undef REGISTER_MSG_FUNC

	return bRet;
}
//------------------------------------------------------------------------
void CCenterSvrMsgParser::__Release()
{
	MSG_FUNC_MAP::iterator Ite = m_mapMsgHandlers.begin();

	while( Ite != m_mapMsgHandlers.end() )
	{
		m_mapMsgHandlers.erase( Ite++ );
	}
}
//------------------------------------------------------------------------
bool CCenterSvrMsgParser::RegisterMsgFunc( MSG_KEY p_sKey, CodeMsgCallback p_Func )
{
	MSG_FUNC_MAP::const_iterator Ite = m_mapMsgHandlers.find( p_sKey );
	if( Ite != m_mapMsgHandlers.end() )
	{
		// ÒÑ¾­×¢²á
		return false;
	}
	if( p_Func == NULL )
	{
		return false;
	}

	m_mapMsgHandlers.insert( MSG_FUNC_MAP::value_type( p_sKey, p_Func ) );
	return true;
}
//------------------------------------------------------------------------
bool CCenterSvrMsgParser::UnRegisterMsgFunc( MSG_KEY p_sKey )
{
	MSG_FUNC_MAP::iterator Ite = m_mapMsgHandlers.find( p_sKey );
	if( Ite != m_mapMsgHandlers.end() )
	{
		m_mapMsgHandlers.erase( Ite );
	}
	else
	{
		return false;
	}

	return true;
}
//------------------------------------------------------------------------
