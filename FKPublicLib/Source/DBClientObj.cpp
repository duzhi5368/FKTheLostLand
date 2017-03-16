/**
*	created:		2013-4-16   5:27
*	filename: 		DBClientObj
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/dbclientobj.h"
//------------------------------------------------------------------------
CDBClientObj::CDBClientObj(void)
{
	Clean();
}
//------------------------------------------------------------------------
CDBClientObj::~CDBClientObj(void)
{
}
//------------------------------------------------------------------------
void CDBClientObj::Update()
{
	CClientObject::Update();
}
//------------------------------------------------------------------------