/**
*	created:		2013-4-19   10:32
*	filename: 		vMap
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CMapObject;
class CLogicMap;
class CPhysicsMap;
//------------------------------------------------------------------------
typedef struct t_VisibleObject
{
	t_VisibleObject():Node(this)
	{
		pObject = NULL;
	}
	CMapObject * pObject;
	xListHost<t_VisibleObject>::xListNode Node;
}VISIBLE_OBJECT;
//------------------------------------------------------------------------
typedef xListHost<CMapObject>	CELLOBJECTLIST;
typedef xListHost<CHumanPlayer> CELLHUMANLIST;
//------------------------------------------------------------------------
class CMapCellInfo
{
public:
	WORD	wFlag;
	WORD	wEventFlag;
	xListHost<CMapObject>		m_xObjectList;
	CMapCellInfo()
	{
		wFlag = 0;
		wEventFlag = 0;
	}
};
//------------------------------------------------------------------------