/**
*	created:		2013-4-19   10:12
*	filename: 		HumanPlayerMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "humanplayer.h"
//------------------------------------------------------------------------
#define MAX_HUMANPLAYER	128
//------------------------------------------------------------------------
class CHumanPlayerMgr
{
public:
	CHumanPlayerMgr(void);
	virtual ~CHumanPlayerMgr(void);
public:
	CHumanPlayer * FindbyName( const char * pszName );
	CHumanPlayer * FindbyId( UINT id );
	CHumanPlayer * NewPlayer(/* CREATEHUMANDESC & desc */);
	BOOL DeletePlayer( CHumanPlayer * pPlayer );
	BOOL AddPlayerNameList( CHumanPlayer * pPlayer, const char * pszName );
public:
	static CHumanPlayerMgr * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CHumanPlayerMgr;
		return m_pInstance;
	}
	int getCount()
	{
		return m_HumanPlayers.GetCount();
	}
public:
	CHumanPlayer* GetfirstPlayer();
	CIndexListEx<CHumanPlayer> * GetPlayerList(){ return &m_HumanPlayers; }

	CHumanPlayer*	GetPlayerById(DWORD id);
	CHumanPlayer*	GetPlayerByDbId(DWORD id);
private:
	static CHumanPlayerMgr * m_pInstance;
	CIndexListEx<CHumanPlayer/*, MAX_HUMANPLAYER*/>	m_HumanPlayers;
	CNameHash m_PlayerNameHash;
};
//------------------------------------------------------------------------