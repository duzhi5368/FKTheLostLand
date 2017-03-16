/**
*	created:		2013-4-15   23:18
*	filename: 		ClientObj
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\clientobj.h"
#include "server.h"
//------------------------------------------------------------------------
void	_tout( char * pret, char * p, int maxlen )
{
	int len = *p;
	if( len < 0 )
	{
		pret[0] = 0;
		return;
	}
	if( len > maxlen )
		len = maxlen;
	p ++;
	strncpy( pret, p, len );
	pret[len] = 0;
}
//------------------------------------------------------------------------
CClientObj::CClientObj(void)
{
	Clean();
}
//------------------------------------------------------------------------
CClientObj::~CClientObj(void)
{
}
//------------------------------------------------------------------------
void CClientObj::Clean()
{
	CClientObject::Clean();
}
//------------------------------------------------------------------------
VOID CClientObj::Update()
{
	CClientObject::Update();
}
//------------------------------------------------------------------------
VOID CClientObj::OnUnCodeMsg( xClientObject * pObject, char * pszMsg, int size )
{

}
//------------------------------------------------------------------------
VOID CClientObj::OnCodedMsg( xClientObject * pObject, PMIRMSG pMsg, int datasize )
{
	CServer * pServer = CServer::GetInstance();
	CAppDB & appDB = GetAppDB();
	DWORD	dwKey = 0;
	pServer->OnParseMsg( pMsg->wCmd );
}
//------------------------------------------------------------------------