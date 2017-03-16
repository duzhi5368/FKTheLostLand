/**
*	created:		2013-4-16   5:18
*	filename: 		TempClient
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "clientobject.h"
//------------------------------------------------------------------------
class CTempClient : public CClientObject
{
public:
	CTempClient(void);
	virtual ~CTempClient(void);
	BOOL	IsTimeOut( DWORD dwTimeOut ){ return m_LiveTimer.IsTimeOut( dwTimeOut );}
	VOID	SaveTime(){ m_LiveTimer.Savetime();}
private:
	CServerTimer	m_LiveTimer;
};
//------------------------------------------------------------------------