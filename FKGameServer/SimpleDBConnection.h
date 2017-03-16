/**
*	created:		2013-4-19   9:58
*	filename: 		simpledbconnection
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xsimplesocket.h"
//------------------------------------------------------------------------
class CSimpleDBConnection :
	public xSimpleSocket
{
public:
	CSimpleDBConnection(void);
	virtual ~CSimpleDBConnection(void);
	VOID	Update();
	VOID	SendMsg( DWORD dwFlag, WORD wCmd, WORD w1, WORD w2, WORD w3, LPVOID lpData = NULL, int datasize = -1 );
	virtual VOID	OnMsg( MIRMSG * pMsg, int datasize ){}
protected:
	int	ParseMessage( char * pszMsg, int iSize );

	xPacket	m_xSendPacket;
	xPacket m_xRecvPacket;
};
//------------------------------------------------------------------------