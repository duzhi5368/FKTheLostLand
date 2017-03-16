/**
*	created:		2013-4-19   10:48
*	filename: 		MapObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "mapobject.h"
#include "logicmap.h"
//------------------------------------------------------------------------
CMapObject::CMapObject(void):m_pMap(NULL),m_Mapid(0)
{ 
	int i = 0;
	m_DLinkNodes = new xListHost<CMapObject>::xListNode/*<CMapObject>*/(this);
}
//------------------------------------------------------------------------
CMapObject::~CMapObject(void)
{

}
//------------------------------------------------------------------------
VOID CMapObject::Clean()
{ 
	m_wX = 0,m_wY = 0;
	m_DLinkNodes->Leave();
	m_pMap = NULL;
	m_dwRefenceCount= 0;
	m_dwUpdateKey = 0;
	m_dwLoopCount = 0;
}
//------------------------------------------------------------------------
VOID	CMapObject::setXY(WORD x, WORD y )
{ 
	if( x != m_wX || y != m_wY )
		OnSetPos( m_wX, m_wY, x, y );
	m_wX = x, m_wY = y;
}
//------------------------------------------------------------------------
int CMapObject::EncodeMsg( char * buffer, DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpdata, int datasize )
{ 
	MIRMSGHEADER	header( dwFlag, wCmd, w1, w2, w3 );
	int	codedsize = 1;
	buffer[0] = '#';
	codedsize += _CodeGameCode( (BYTE*)&header, sizeof( header ), (BYTE*)buffer+codedsize );
	if( lpdata != NULL )
	{
		if( datasize < 0 )
			datasize = (int)strlen( (char*)lpdata );
		codedsize += _CodeGameCode( (BYTE*)lpdata, datasize, (BYTE*)buffer+codedsize );
	}
	buffer[codedsize++] = '!';
	buffer[codedsize] = 0;
	return codedsize;
}
//------------------------------------------------------------------------