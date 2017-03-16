/**
*	created:		2013-4-19   10:44
*	filename: 		MapObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "vmap.h"
#include "flageventlistener.h"
//------------------------------------------------------------------------
class CLogicMap;
class CVArea;
//------------------------------------------------------------------------
class CMapObject:
	public CFlagEventListener
{
public:
	CMapObject(void);
	virtual ~CMapObject(void);
	xListHost<CMapObject>::xListNode/*<CMapObject>*/	*	GetLinkNode(){ return m_DLinkNodes; }
	WORD					getX(){ return m_wX;}
	WORD					getY(){ return m_wY;}
	VOID					setX(WORD x){  setXY( x, m_wY );}
	VOID					setY(WORD y){  setXY( m_wX, y );}
	VOID					setXY(WORD x, WORD y );
	virtual BOOL 			CanRecvMsg(){ return FALSE;}
	virtual VOID 			OnAroundMsg( CMapObject * pSender, const char * pszCodedMsg, int size ){}
	virtual UINT 			GetId(){  return 0;}
	virtual VOID 			OnEnterMap( CLogicMap * pMap ){ m_pMap = pMap;}
	virtual VOID 			OnLeaveMap( CLogicMap * pMap ){ m_pMap = NULL;}
	virtual VOID 			Update(){m_dwLoopCount++;}
	virtual VOID 			Clean();
	virtual BOOL 			GetViewmsg( char * pszMsg, int & length, CMapObject * pViewer = NULL ){  return FALSE;}
	virtual BOOL 			GetOutViewmsg( char * pszMsg, int & length, CMapObject * pViewer = NULL  ){  return FALSE;}
	virtual e_object_type	GetType(){  return OBJ_UNKNOWN;}
	CLogicMap *				GetMap(){ return m_pMap;}
	virtual VOID			OnSetPos( WORD oldx, WORD oldy, WORD newx, WORD newy ){}
	DWORD					AddRef(){return(++m_dwRefenceCount);}
	DWORD					DecRef(){  return(--m_dwRefenceCount);}
	DWORD					GetRef(){ return m_dwRefenceCount; }
	VOID					SetDelTimer(){  m_DeleteTimer.Savetime();}
	BOOL					IsDelTimerTimeOut( DWORD dwTimeOut ){  return m_DeleteTimer.IsTimeOut(dwTimeOut);}
	UINT					GetMapId(){ return m_Mapid;}
	VOID					SetMapId( UINT mapid ){  m_Mapid = mapid;}
	VOID					SetUpdateKey( DWORD dwKey ){  m_dwUpdateKey = dwKey;}
	DWORD					GetUpdateKey(){  return m_dwUpdateKey;}
	virtual const char *	GetName(){ return "MAPOBJECT";}
	virtual VOID			OnMoveTo( UINT ox, UINT oy, UINT nx, UINT ny ){}
protected:
	int						EncodeMsg( char * buffer, DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpdata = 0, int datasize = -1 );
	CLogicMap * m_pMap;
	CServerTimer	m_DeleteTimer;
	DWORD	m_dwUpdateKey;
	DWORD	m_dwLoopCount;
	DWORD	m_dwRefenceCount;
	WORD	m_wX, m_wY;
	UINT	m_Mapid;
	xListHost<CMapObject>::xListNode/*<CMapObject>*/	*	m_DLinkNodes;
};
