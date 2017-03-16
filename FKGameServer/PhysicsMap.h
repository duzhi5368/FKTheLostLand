/**
*	created:		2013-4-19   14:23
*	filename: 		PhysicsMap
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "vmap.h"
//------------------------------------------------------------------------
class CPhysicsMap
{
public:
	CPhysicsMap(void);
	virtual ~CPhysicsMap(void);
	BOOL			LoadMap( const char * pszFilename );
	BOOL			LoadCache( const char * pszCacheFilename );
	BOOL			SaveCache( const char * pszPath );
	BOOL			IsBlocked( int x, int y );
	int				GetHeight(){ return m_iHeight;}
	int				GetWidth(){ return m_iWidth;}
	const char *	GetName(){ return m_szMapName;}
private:
	BOOL	VerifyPos( int x, int y )
	{
		if( x < 0 || x >= m_iWidth )return FALSE;
		if( y < 0 || y >= m_iHeight )return FALSE;
		return TRUE;
	}
private:
	int 		m_iWidth;
	int 		m_iHeight;
	DWORD *		m_pBlockLayer;
	int			m_iMaxBlockElements;
	char		m_szMapName[32];
};
//------------------------------------------------------------------------