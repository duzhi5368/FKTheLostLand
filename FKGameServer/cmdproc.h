/**
*	created:		2013-4-19   10:24
*	filename: 		CmdProc
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CCommandManager :
	public xSingletonClass<CCommandManager>
{
public:
	CCommandManager();
	BOOL			AddCommand( const char * pszCommand, fnCommandProc proc );
	fnCommandProc	GetCommandProc( const char * pszCommand );
	BOOL			ChangeCommandName( const char * pszCommand, const char * pszNewName );
protected:
	xStringList<1024> m_xCommandList;
};
//------------------------------------------------------------------------