/**
*	created:		2013-4-19   14:32
*	filename: 		LogicMapMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "findfile.h"
#include "logicmap.h"
//------------------------------------------------------------------------
#define MAX_LOGIC_MAP	10240
//------------------------------------------------------------------------
class CLogicMapMgr :
	public CFindFile
{
public:
	CLogicMapMgr(void);
	virtual ~CLogicMapMgr(void);

	VOID Load( const char * pszPath );
	CLogicMap * GetLogicMapByTitle( const char * pszTitleName );
	CLogicMap * GetLogicMapById( UINT id ){ if( id == 0 || id > MAX_LOGIC_MAP ) return NULL;return m_pMaps[id-1];}

	static CLogicMapMgr * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CLogicMapMgr;
		return m_pInstance;
	}
	int	getCount(){ return m_LogicMaps.GetCount();}
protected:
	VOID	OnFoundFile( const char * pszFilename, UINT nParam = 0 );

private:
	CLogicMap * m_pMaps[MAX_LOGIC_MAP];
	static CLogicMapMgr * m_pInstance;
	CNameHash	m_MapNameHash;
	CLogicMap * m_pLoadingMap;
	CIndexList<CLogicMap,MAX_LOGIC_MAP>	m_LogicMaps;
};
//------------------------------------------------------------------------