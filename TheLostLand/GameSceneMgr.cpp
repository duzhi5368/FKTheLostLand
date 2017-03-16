/**
*	created:		2013-5-1   22:18
*	filename: 		GameSceneMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "GameSceneMgr.h"
#include "Scene/LoginScene.h"
#include "Scene/MainScene.h"
#include "Scene/CharSelectScene.h"
//------------------------------------------------------------------------
CGameSceneMgr* CGameSceneMgr::s_GameManager = NULL;
//------------------------------------------------------------------------
CGameSceneMgr& CGameSceneMgr::GetInstance()
{
	if (s_GameManager == NULL)
	{
		s_GameManager = new CGameSceneMgr();
	}
	return *s_GameManager;
}
//------------------------------------------------------------------------
CGameSceneMgr* CGameSceneMgr::GetInstancePtr()
{
	if (s_GameManager == NULL)
	{
		s_GameManager = new CGameSceneMgr();
	}
	return s_GameManager;
}
//------------------------------------------------------------------------
CGameSceneMgr::CGameSceneMgr()
	: m_nNextSceneIndex( -1 )
	, m_pAppNetworkLink( NULL )
{
	Add( new CLoginScene(), eScene_LoginScene );
	Add( new CMainScene(), eScene_MainScene );
	Add( new CCharSelectScene(), eScene_CharSelectScene );
}
//------------------------------------------------------------------------
void CGameSceneMgr::Update(float dt)
{
	if( m_nNextSceneIndex != -1 )
	{
		SetCurScene( m_nNextSceneIndex );
		m_nNextSceneIndex = -1;
	}
}
//------------------------------------------------------------------------
void CGameSceneMgr::SetNextSceneIndex( unsigned int index )
{
	m_nNextSceneIndex = index;
}
//------------------------------------------------------------------------
bool CGameSceneMgr::CreateConnection( EnumNetworkLinkState e )
{
	if ( m_pAppNetworkLink != NULL)
	{
		IClientLink *pLink = m_pAppNetworkLink->GetClientLink();
		if (pLink && pLink->IsConnected())
		{
			pLink->CloseConnect();
		}
	}

	switch(e) 
	{
	case eNLS_LoginSvr:
		if(m_SocketHelper.Create(5368, static_cast<IClientLinkSink*>(&g_LoginSvrConnector), (ITrace*)g_pTrace) == FALSE)
		{
			FKTRACE( L"网络连接创建失败" );
			return FALSE;
		}
		g_LoginSvrConnector.m_pClientLink = m_SocketHelper.m_pClientLink;
		m_pAppNetworkLink = &g_LoginSvrConnector;
		break;

	case eNLS_CharSelSvr:
		if(m_SocketHelper.Create(5368, static_cast<IClientLinkSink*>(&g_CharSelSvrConnector), (ITrace*)g_pTrace) == FALSE)
		{
			FKTRACE( L"网络连接创建失败" );
			return FALSE;
		}
		g_CharSelSvrConnector.m_pClientLink = m_SocketHelper.m_pClientLink;
		m_pAppNetworkLink = &g_CharSelSvrConnector;
		break;

	case eNLS_GameSvr:
		if(m_SocketHelper.Create(5368, static_cast<IClientLinkSink*>(&g_GameSvrConnector), (ITrace*)g_pTrace) == FALSE )
		{
			FKTRACE( L"网络连接创建失败" );
			return FALSE;
		}
		g_GameSvrConnector.m_pClientLink = m_SocketHelper.m_pClientLink;
		m_pAppNetworkLink = &g_GameSvrConnector;
		break;
	default:
		FKTRACE( L"Unknow SinkState : %d", e);
		return false;
		break;
	}	

	return true;
}
//------------------------------------------------------------------------