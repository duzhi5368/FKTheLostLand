/**
*	created:		2013-4-19   0:56
*	filename: 		GmManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct gm_node
{
	char szAccount[32];
	int	level;
};
//------------------------------------------------------------------------
typedef struct tagGameCommand
{
	tagGameCommand()
	{
		memset( this, 0, sizeof( *this ) );
	}
	StringCacheNode * pPage;
	fnCommandProc proc;
	BOOL	fIsCallPage;
	BOOL	fIsGmCmd;
	UINT	nLimitLevel;
}GameCommand;
//------------------------------------------------------------------------
class CPoolManager:
	public xSingletonClass<CPoolManager>
{
public:
	CPoolManager(void){};
	virtual ~CPoolManager(void){};
	xObjectPool<StringCacheNode> * GetStringCachePool(){ return &m_xStringCachePool;}
protected:
	xObjectPool<StringCacheNode> m_xStringCachePool;
};
//------------------------------------------------------------------------
class CGmManager
{
public:
	CGmManager(void);
	virtual ~CGmManager(void);
	BOOL Load( const char * pszFile );
	VOID Save( const char * pszFile );
	int	GetGmLevel( const char * pszAccount );
	static CGmManager * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new CGmManager;
		return m_pInstance;
	}
	BOOL LoadCommandDef( const char * pszFile );
	BOOL ExecGameCmd( const char * pszCommand, CHumanPlayer * pPlayer );
	BOOL MapCommand( int iLevel, char * pszCommand, char * pszBuildInCommand );
private:
	VOID ClearCmdList();
	xStringList<512>	m_xCmdList;
	static CGmManager * m_pInstance;
	xObjectPool<gm_node>	m_xGmNodePool;
	CNameHash m_GmHash;	//GMÁÐ±í
};
//------------------------------------------------------------------------