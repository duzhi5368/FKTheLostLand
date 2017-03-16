/**
*	created:		2013-4-15   22:57
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "appdb.h"
//------------------------------------------------------------------------
class CClientObj :
	public CClientObject
{
public:
	CClientObj(void);
	virtual ~CClientObj(void);
public:
	VOID	Clean();
	VOID	Update();
	VOID	OnUnCodeMsg( xClientObject * pObject,char * pszMsg, int size );
	VOID	OnCodedMsg( xClientObject * pObject, PMIRMSG	pMsg, int datasize );
	CAppDB & GetAppDB(){return m_appDB;}
private:
	CAppDB	m_appDB;
	char	m_szBuffer[65536];
};
//------------------------------------------------------------------------