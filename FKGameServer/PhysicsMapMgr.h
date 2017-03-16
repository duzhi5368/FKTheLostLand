/**
*	created:		2013-4-19   14:31
*	filename: 		PhysicsMapMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "findfile.h"
//------------------------------------------------------------------------
class CPhysicsMap;
//------------------------------------------------------------------------
class CPhysicsMapMgr :
	public xSingletonClass<CPhysicsMapMgr>
{
public:
	CPhysicsMapMgr(void);
	virtual ~CPhysicsMapMgr(void);

	CPhysicsMap * Load( const char * pszName );
	VOID	Init( const char * pszPath, const char * pszCachePath );
	CPhysicsMap * GetPhysicsMapByName( const char * pszMapName );
private:
	char	m_szPhysicsMapPath[1024];
	char	m_szPhysicsCachePath[1024];
	xStringList<128> m_xMapList;
	BOOL	m_bUseCache;
};
//------------------------------------------------------------------------