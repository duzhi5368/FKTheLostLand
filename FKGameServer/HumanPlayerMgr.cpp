/**
*	created:		2013-4-19   10:13
*	filename: 		HumanPlayerMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\humanplayermgr.h"
#include ".\gameworld.h"
//------------------------------------------------------------------------
CHumanPlayerMgr * CHumanPlayerMgr::m_pInstance = NULL;
//------------------------------------------------------------------------
CHumanPlayerMgr::CHumanPlayerMgr(void)
{
	if( m_pInstance == NULL )
		m_pInstance = this;
	m_HumanPlayers.Create( 4000 );
}
//------------------------------------------------------------------------
CHumanPlayerMgr::~CHumanPlayerMgr(void)
{

}
//------------------------------------------------------------------------
CHumanPlayer * CHumanPlayerMgr::FindbyName( const char * pszName )
{
	return (CHumanPlayer*)m_PlayerNameHash.HGet(pszName);
}
//------------------------------------------------------------------------
CHumanPlayer * CHumanPlayerMgr::FindbyId( UINT id )
{
	if( ((id & 0xff000000)>>24) == OBJ_PLAYER )
		id &= 0xffffff;
	return m_HumanPlayers.Get(id);
}
//------------------------------------------------------------------------
BOOL CHumanPlayerMgr::AddPlayerNameList( CHumanPlayer * pPlayer, const char * pszName )
{
	return m_PlayerNameHash.HAdd( pszName, (LPVOID)pPlayer );
}
//------------------------------------------------------------------------
CHumanPlayer * CHumanPlayerMgr::NewPlayer(/* CREATEHUMANDESC & desc */)
{
	CHumanPlayer * pPlayer = NULL;
	UINT id = 0;
	id = m_HumanPlayers.New(&pPlayer);
 
	if( id == 0 || pPlayer == NULL )  
		return NULL;
	id |= (OBJ_PLAYER << 24);
	pPlayer->SetId( id );

	return pPlayer;
}
//------------------------------------------------------------------------
BOOL CHumanPlayerMgr::DeletePlayer( CHumanPlayer * pPlayer )
{
	UINT	id = (pPlayer->GetId() & 0xffffff);
	m_PlayerNameHash.HDel( pPlayer->GetName());
	pPlayer->Clean();
	return m_HumanPlayers.Del(id);
}
//------------------------------------------------------------------------
CHumanPlayer* CHumanPlayerMgr::GetfirstPlayer()
{
	return m_HumanPlayers.First();
}
//------------------------------------------------------------------------
CHumanPlayer*	CHumanPlayerMgr::GetPlayerById(DWORD id)
{
	CIndexListEx<CHumanPlayer> * pList = GetPlayerList();
	CHumanPlayer * pPlayer = pList->First();
	while (pPlayer)
	{
		if (pPlayer->GetId() == id)
		{
			return pPlayer;
		}
		pPlayer = pList->Next();
	}
	return NULL;
}
//------------------------------------------------------------------------
CHumanPlayer* CHumanPlayerMgr::GetPlayerByDbId(DWORD id)
{
	CIndexListEx<CHumanPlayer> * pList = GetPlayerList();
	CHumanPlayer * pPlayer = pList->First();
	while (pPlayer)
	{
		if (pPlayer->GetDBId() == id)
		{
			return pPlayer;
		}
		pPlayer = pList->Next();
	}
	return NULL;
}
//------------------------------------------------------------------------