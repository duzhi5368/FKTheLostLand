/**
*	created:		2013-4-19   0:56
*	filename: 		GmManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\gmmanager.h"
#include ".\humanplayer.h"
#include ".\ScriptObjectMgr.h"
#include ".\cmdproc.h"
#include ".\SystemScript.h"
#include ".\ScriptView.h"
#include ".\ScriptObject.h"
//------------------------------------------------------------------------
CGmManager * CGmManager::m_pInstance = NULL;
//------------------------------------------------------------------------
CGmManager::CGmManager(void) : m_xCmdList( TRUE )
{
	if( m_pInstance == NULL )
		m_pInstance = this;
}
//------------------------------------------------------------------------
CGmManager::~CGmManager(void)
{
}
//------------------------------------------------------------------------
BOOL CGmManager::Load( const char * pszFile )
{
	CStringFile	sf( pszFile );
	char * Params[2];
	int	nParam = 0;
	gm_node * pnode = NULL;
	for( int i = 0;i < sf.GetLineCount();i ++ )
	{
		if( *sf[i] == '#' )
			continue;
		nParam = SearchParam( sf[i], Params, 2, '/' );
		if( nParam == 2 )
		{
			pnode = m_xGmNodePool.newObject();
			if( pnode == NULL )continue;
			if( m_GmHash.HAdd(Params[0],pnode))
			{
				o_strncpy(pnode->szAccount, Params[0], 16 );
				pnode->level = StringToInteger( Params[1] );
			}
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CGmManager::Save( const char * pszFile )
{
	return;
}
//------------------------------------------------------------------------
int	CGmManager::GetGmLevel( const char * pszAccount )
{
	gm_node * p = (gm_node *)m_GmHash.HGet(pszAccount);
	if( p )
		return p->level;
	return 0;
}
//------------------------------------------------------------------------
static char m_szTempBuffer[65536];
//------------------------------------------------------------------------
BOOL CGmManager::ExecGameCmd( const char * pszCommand, CHumanPlayer * pPlayer )
{
	xCharSet csWht( " \t\"" );
	xCharSet csSpl( " \t," );
	o_strncpy( m_szTempBuffer, pszCommand, 65535 );
	char	*	Params[20];
	replaceOutPair( m_szTempBuffer, '(', ')', ' ' );

	int nParam = ExtractStrings( (char*)m_szTempBuffer, csWht, csSpl, Params, 20, FALSE );
	CallParamEx params[20];
	if( nParam > 0 )
	{
		GameCommand * pCmd = (GameCommand *)m_xCmdList.ObjectOf( Params[0] );
		GameCommand rcmd;
		if( pCmd == NULL )
		{
			if( pCmd == NULL )
			{
				pPlayer->SaySystemEx(1,  "<%s %s >", getstrings( SD_EXECCMDERROR_BADCOMMAND ), Params[0] );
				return FALSE;
			}
			
		}

		for( int i = 0;i < nParam-1;i ++ ) 
		{
			if( *Params[i+1] == '$' ) 
				params[i].pszParam = pPlayer->GetScriptTarget()->GetVariableValue( Params[i+1] + 1 );
			else
				params[i].pszParam = Params[i+1];
			if( params[i].pszParam==NULL )params[i].pszParam = "";
			params[i].nParam = StringToInteger( params[i].pszParam );
		}
		if( pCmd->fIsCallPage && pCmd->pPage )
		{
			CSystemScript::GetInstance()->setCallParams( params );
			CSystemScript::GetInstance()->Execute( pPlayer->GetScriptTarget(), pCmd->pPage->szString, FALSE );
		}
		else
		{
			CScriptShell shell;
			CScriptPageView view(&shell);
			BOOL	b1 = TRUE;
			DWORD result = pCmd->proc( &shell, pPlayer->GetScriptTarget(), &view, params, nParam -1, b1 );
			char * p = (char*)view.getPacket().getbuf();
			p[view.getPacket().getsize()] = 0; 
			if( pCmd->fIsGmCmd )
			{
				pPlayer->SaySystemEx(1,  "%s%u", getstrings( SD_CMDRESULTVALUEIS ), result );
			}
		}
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------------
BOOL CGmManager::LoadCommandDef( const char * pszFile )
{
	ClearCmdList();
	CStringFile sf( pszFile );
	for( UINT i = 0;i < (UINT)sf.GetLineCount();i ++ )
	{
		if( *sf[i] == '#' )continue;
		xStringsExtracter<10> cmd( sf[i], ")=", "( \t" );
		if( cmd.getCount() != 3 )continue;
		MapCommand( StringToInteger( cmd[0] ), cmd[1], cmd[2] );
	}		
	return TRUE;
}
//------------------------------------------------------------------------
VOID CGmManager::ClearCmdList()
{
	GameCommand * p = NULL;
	for( UINT i = 0;i < m_xCmdList.GetCount();i ++ )
	{
		p = (GameCommand*)m_xCmdList[i]->lpObject;
		if( p->pPage )
		{
			CPoolManager::GetInstance()->GetStringCachePool()->deleteObject( p->pPage );
		}
		delete p;
		m_xCmdList[i]->lpObject = NULL;
	}
	m_xCmdList.Clear();
}
//------------------------------------------------------------------------
BOOL	CGmManager::MapCommand( int iLevel,  char * pszCommand, char * pszBuildInCommand )
{
	GameCommand gcmd;
	if( iLevel <= 0 )
	{
		gcmd.fIsGmCmd = FALSE;
		iLevel = abs( iLevel );
	}
	else
		gcmd.fIsGmCmd = TRUE;
	gcmd.nLimitLevel = iLevel;


	if( *pszBuildInCommand == '@' )
	{
		gcmd.fIsCallPage = TRUE;
		if( CSystemScript::GetInstance()->getScriptObject() == 0 || CSystemScript::GetInstance()->getScriptObject()->GetPage( pszBuildInCommand ) == NULL )
		{
			PRINT( 0xff, "%s %s %s\n", pszCommand, getstrings( SD_CMDMAPERROR_SCRIPTNOTFOUND ), pszBuildInCommand );
			return FALSE;
		}
		gcmd.pPage = CPoolManager::GetInstance()->GetStringCachePool()->newObject();
		o_strncpy( gcmd.pPage->szString, pszBuildInCommand, 250 );
	}
	else
	{
		gcmd.proc = CCommandManager::GetInstance()->GetCommandProc( pszBuildInCommand );
		if( gcmd.proc == NULL )
		{
			PRINT( 0xff, "%s %s %s\n", pszCommand, getstrings( SD_CMDMAPERROR_CMDNOTFOUND ), pszBuildInCommand );
			return FALSE;
		}

	}

	GameCommand * pCmd = new GameCommand;
	*pCmd = gcmd;
	if( m_xCmdList.Add( pszCommand, (LPVOID)pCmd ) == -1 )
	{
		PRINT( 0xff, "%s %s\n", pszCommand, getstrings( SD_CMDMAPERROR_CMDALREADYREGISTERED ) );
		delete pCmd;
		return FALSE;
	}
	else
	{
		DPRINT( 0xff, "”≥…‰ %s √¸¡ÓµΩ %s\n", pszCommand, pszBuildInCommand );
	}

	return TRUE;
}
//------------------------------------------------------------------------