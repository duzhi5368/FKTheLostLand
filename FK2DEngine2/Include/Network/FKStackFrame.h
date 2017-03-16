/**
*	created:		2013-5-10   2:24
*	filename: 		FKStackFrame
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		获取当前堆栈信息
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKAPIProxy.h"
#include <vector>
using namespace std;
//------------------------------------------------------------------------
class CStackFrame
{
public:
	CStackFrame( int nMaxsize) : m_nMaxsize(nMaxsize)
	{
	}

	CStackFrame() : m_nMaxsize(128)
	{
	}

	BOOL SaveStack( int nMaxDepth = 6 );

	void Clear();

	BOOL GetStackList( void ** ppList , int & nCount );

	int  GetSize();

	void AddStack( void * pCall );

private:
	vector<void *> m_StackList;
	int  m_nMaxsize;
};
//------------------------------------------------------------------------