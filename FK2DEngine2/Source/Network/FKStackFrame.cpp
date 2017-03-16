/**
*	created:		2013-5-10   2:25
*	filename: 		FKStackFrame
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/Network/FKStackFrame.h"
#include <algorithm>
//------------------------------------------------------------------------
#pragma comment(linker, "/defaultlib:dbghelp.lib")
//------------------------------------------------------------------------
BOOL CStackFrame::SaveStack( int nMaxDepth )
{
	if( m_StackList.size() >= m_nMaxsize )
		return TRUE;

	CONTEXT context;
	PCONTEXT pContext = &context;
	memset(pContext,0,sizeof(CONTEXT));
	pContext->ContextFlags = CONTEXT_FULL;
	if( !GetThreadContext(GetCurrentThread(),pContext) )
		return FALSE;

	DWORD dwMachineType = 0;

	STACKFRAME sf;
	memset( &sf, 0, sizeof(sf) );

#ifdef _M_IX86
	//初次调用需要初始化STACKFRAME结构 - 仅需要在I386机器上
	sf.AddrPC.Offset       = pContext->Eip;
	sf.AddrPC.Mode         = AddrModeFlat;
	sf.AddrStack.Offset    = pContext->Esp;
	sf.AddrStack.Mode      = AddrModeFlat;
	sf.AddrFrame.Offset    = pContext->Ebp;
	sf.AddrFrame.Mode      = AddrModeFlat;

	dwMachineType = IMAGE_FILE_MACHINE_I386;
#endif

	while ( nMaxDepth-- )
	{
		// 获得夏一个栈帧
		if ( ! StackWalk(  dwMachineType,
			GetCurrentProcess(),
			GetCurrentThread(),
			&sf,
			pContext,
			0,
			SymFunctionTableAccess,
			SymGetModuleBase,
			0 ) )
			break;

		if ( 0 == sf.AddrFrame.Offset ) // 检查Frame是否正确
			break;                      // 坏的，则break

		void  * pCall = (void *)(sf.AddrPC.Offset);
		vector<void *>::iterator it = std::find( m_StackList.begin(),m_StackList.end(),pCall );
		if( it == m_StackList.end() )
		{
			m_StackList.push_back(pCall);
		}
	}

	return TRUE;
}
//------------------------------------------------------------------------
void CStackFrame::Clear()
{
	m_StackList.clear();
}
//------------------------------------------------------------------------
BOOL CStackFrame::GetStackList( void ** ppList , int & nCount )
{
	if( ppList == NULL || nCount < m_StackList.size() )
		return FALSE;

	memcpy( ppList , &m_StackList[0],m_StackList.size()*sizeof(void *));
	nCount = m_StackList.size();
	return TRUE;
}
//------------------------------------------------------------------------
int  CStackFrame::GetSize()
{
	return m_StackList.size();
}
//------------------------------------------------------------------------
void CStackFrame::AddStack( void * pCall )
{
	if( m_StackList.size() >= m_nMaxsize )
		return;

	vector<void *>::iterator it = find( m_StackList.begin(),m_StackList.end(),pCall );
	if( it == m_StackList.end() )
	{
		m_StackList.push_back(pCall);
	}
}
//------------------------------------------------------------------------