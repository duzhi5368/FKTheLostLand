/**
*	created:		2013-4-19   10:25
*	filename: 		CmdProc
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\cmdproc.h"
//------------------------------------------------------------------------
CCommandManager::CCommandManager():m_xCommandList(TRUE)
{
	
}
//------------------------------------------------------------------------
BOOL CCommandManager::AddCommand( const char * pszCommand, fnCommandProc proc )
{
	LPVOID lpProc = this->m_xCommandList.ObjectOf( pszCommand );
	if( lpProc != NULL )return FALSE;
	return (m_xCommandList.Add( pszCommand, (LPVOID)proc ) != -1 );
}
//------------------------------------------------------------------------
fnCommandProc CCommandManager::GetCommandProc( const char * pszCommand )
{
	return (fnCommandProc)m_xCommandList.ObjectOf( pszCommand );
}
//------------------------------------------------------------------------
BOOL CCommandManager::ChangeCommandName( const char * pszCommand, const char * pszNewName )
{
	LPVOID lpProc = this->m_xCommandList.ObjectOf( pszCommand );
	if( lpProc )
	{
		if( m_xCommandList.Add( pszNewName, lpProc ) != -1 )
		{
			m_xCommandList.Delete( pszCommand );
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------------