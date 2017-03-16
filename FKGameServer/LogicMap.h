/**
*	created:		2013-4-19   14:34
*	filename: 		LogicMap
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "vmap.h"
#include "physicsmap.h"
//------------------------------------------------------------------------
class CArea;
class CHumanPlayer;
class CAliveObject;
//------------------------------------------------------------------------
static DWORD g_dwInterFlag = 0;
//------------------------------------------------------------------------
class CLogicMap
{
public:
	CLogicMap(void){};
	virtual ~CLogicMap(void){};
	BOOL			LoadMap( const char * pszFilename ){ return FALSE; };
	BOOL			IsBlocked( int x, int y ){return FALSE; };
	BOOL			SendMsg( CMapObject * pSender, const char * pszCodedMsg, int size ){return FALSE; };
	BOOL			MoveObject( CMapObject * pObject, int x, int y ){return FALSE; };
	BOOL			AddObject( CMapObject * pObject ){return FALSE; };
	BOOL			RemoveObject( CMapObject * pObject ){return FALSE; };
	CMapObject * 	FindObject( int x, int y, e_object_type type ){return NULL; };
	CMapObject * 	FindObjectMT( int x, int y, DWORD dwTypeFlag ){return NULL; };
	CMapObject * 	FindEventObject( int x, int y, int View ){return NULL; };
	VOID 			CheckEnterCity( CHumanPlayer * pPlayer ){};
	VOID 			DecObjectCount( DWORD dwType ){};
	VOID 			AddObjectCount( DWORD dwType ){};
	VOID			ClearAllMonsters( const char * pszClassName = NULL ){};
	UINT			CountAllMonsters( const char * pszClassName = NULL ){return 0;};
	int				GetObjectCount( e_object_type type )
	{
		int itype = (int)type;
		if( itype < 0 || itype >= OBJ_MAX )return 0;
		return m_iObjectCount[type];
	}
public:
	CAliveObject *	FindTarget( CAliveObject * pAttacker, UINT x, UINT y ){ return NULL; };
	const char * 	GetName(){ assert( m_pPhysicsMap != NULL);return m_pPhysicsMap->GetName();}
	const char * 	GetTitle(){ return m_pName;}
	const char * 	GetSoundType(){ return m_pSoundType;}
	int				GetWidth(){ return m_iWidth;}
	int				GetHeight(){ return m_iHeight;}
	CPhysicsMap *	GetPhysicsMap(){ return m_pPhysicsMap;}
	VOID			SetPhysicsMap( CPhysicsMap * pPhysicsMap ){ m_pPhysicsMap = pPhysicsMap; };
	UINT			GetId(){ return m_Id;}
	VOID			SetId( UINT id ){ m_Id = id;}
	int				GetIndex(){  return m_nIndex;}
	VOID			InitLinks(){};
	VOID			GetObjList( xListHelper<CMapObject> & objlist ){objlist.setList( &m_xObjList );}

private:
	int				m_nIndex;
	char*			m_pSoundType;
	DWORD *			m_pLockLayer;
	int				m_iMaxBlockElements;
	CSettingFile	m_DataFile;
	CPhysicsMap *	m_pPhysicsMap;
	char	*		m_pName;
	int				m_iWidth;
	int 			m_iHeight;
	UINT			m_Id;
	CMapCellInfo ** m_pCellInfo;
	int				m_iStartPointCount;
	int				m_iObjectCount[OBJ_MAX];
	xListHost<CMapObject>	m_xObjList;
	static xObjectPool<CMapCellInfo>	m_xCellInfoPool;
};
//------------------------------------------------------------------------