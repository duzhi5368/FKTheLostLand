/**
*	created:		2013-4-16   5:11
*	filename: 		MsgProcessor
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "inc.h"
//------------------------------------------------------------------------
class xClientObject;
//------------------------------------------------------------------------
class CMsgProcessor
{
public:
	virtual void OnUnCodeMsg( xClientObject * pObject, const char * pszMsg, int size ){}
	virtual void OnCodedMsg(  xClientObject * pObject, PMIRMSG	pMsg, int datasize ){}
};
//------------------------------------------------------------------------