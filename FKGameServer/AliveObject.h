/**
*	created:		2013-4-19   10:55
*	filename: 		AliveObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "mapobject.h"
#include "scripttarget.h"
//------------------------------------------------------------------------
class CScriptTargetForPlayer;
class CAliveObject;
//------------------------------------------------------------------------
class CRefObject
{
public:
	CRefObject()
	{
		m_pObject = NULL;
		m_dwInstanceKey;
	}
	CAliveObject *	GetObject(){ return m_pObject;}
	VOID			SetObject( CAliveObject * pObject );
	BOOL			IsValid(){ return FALSE; };
protected:
	CAliveObject *	m_pObject;
	DWORD			m_dwInstanceKey;
};
//------------------------------------------------------------------------
class CAttackObject
{
public:
	CAttackObject()
	{
		nAttackCount = 0;
		nDamage = 0;
	}
	VOID Clear()
	{
		refObject.SetObject( NULL );
		nAttackCount = 0;
		nDamage = 0;
	}
	CAliveObject * GetObject()
	{
		return refObject.GetObject();
	}
	UINT GetAttackCount()
	{
		return nAttackCount;
	}
	UINT GetDamage()
	{
		return nDamage;
	}
	VOID UpdateValid()
	{
		if( !refObject.IsValid())
			Clear();
	}
	VOID AddAttackInfo( CAliveObject * pObj, UINT inDamage )
	{
		if( pObj != refObject.GetObject())
		{
			refObject.SetObject( pObj );
			nAttackCount = 0;
			nDamage = 0;
		}
		nAttackCount ++;
		nDamage += inDamage;
		timer.Savetime();
	}

	BOOL	IsTimeOut( DWORD dwTime )
	{
		return timer.IsTimeOut( dwTime );
	}
private:
	CRefObject refObject;
	UINT nAttackCount;
	UINT nDamage;
	CServerTimer timer;
};
//------------------------------------------------------------------------
#define MAX_ACTION_TIME	500000
//------------------------------------------------------------------------
typedef xListHost<VISIBLE_OBJECT>	VISIBLE_OBJECT_LIST;
//------------------------------------------------------------------------
class CAliveObject :
	public CMapObject
{
public:
	CAliveObject(void){};
	virtual ~CAliveObject(void){};
	virtual VOID 	Clean(){};
	virtual VOID 	Update(){}; 
public:
	UINT 			GetId(){ return m_Id;}
	VOID 			SetId( UINT Id ){  m_Id = Id;}
public:
	void 			SaySystemEx(int type, const char * pszMsg, ... ){};
private:
	UINT			m_Id;
};
//------------------------------------------------------------------------