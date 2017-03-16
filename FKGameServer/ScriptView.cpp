/**
*	created:		2013-4-19   13:12
*	filename: 		ScriptView
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptview.h"
#include ".\scriptshell.h"
#include ".\humanplayer.h"
//------------------------------------------------------------------------
CScriptView::CScriptView(CScriptShell * pShell) 
{
	m_xScriptPacket.create( m_szBuffer, 65536 );
	m_szBuffer[0] = 0;
	ChangeShell( pShell );
	m_dwParam = 0;
	m_nPageSize = 0;
}
//------------------------------------------------------------------------
CScriptView::~CScriptView(void)
{
	m_xScriptPacket.destroy();
}
//------------------------------------------------------------------------
static char g_szTempBuffer[65536];
//------------------------------------------------------------------------
BOOL CScriptView::AppendWordsEx( const char * pszWords, ... )
{
	va_list	vl;
	va_start( vl, pszWords );
	vsprintf( g_szTempBuffer, pszWords, vl );
	va_end( vl);
	return AppendWords(g_szTempBuffer);
}
//------------------------------------------------------------------------
CScriptPageView::CScriptPageView( CScriptShell * pShell ): CScriptView( pShell )
{
	if( m_pShell )
	{
		m_xScriptPacket.push( (LPVOID)pShell->GetTitleName(), (int)strlen( pShell->GetTitleName() ) );
		m_xScriptPacket.push( (LPVOID)"/", 1 );
	}
}
//------------------------------------------------------------------------
BOOL CScriptPageView::AppendWords( const char * pszWords )
{
	UINT nLength = strlen( pszWords );
	m_nPageSize += nLength;
	return m_xScriptPacket.push( (LPVOID)pszWords, (int)nLength );
}
//------------------------------------------------------------------------
VOID CScriptPageView::SendPageToTarget( CScriptTarget * pTarget, DWORD dwParam  )
{
	this->m_dwParam = dwParam;
	if( m_nPageSize > 0 )
	{
		if( pTarget )pTarget->SendPage( this->m_pShell, this);
	}
}
//------------------------------------------------------------------------
VOID CScriptPageView::SendClosePageToTarget( CScriptTarget * pTarget)
{
	if( pTarget )pTarget->SendClosePage( m_pShell );
}
//------------------------------------------------------------------------
VOID CScriptPageView::ChangeShell( CScriptShell * pShell )
{
	m_xScriptPacket.clear();
	m_xScriptPacket.push( (LPVOID)pShell->GetTitleName(), (int)strlen( pShell->GetTitleName() ) );
	m_xScriptPacket.push( (LPVOID)"/", 1 );
	CScriptView::ChangeShell( pShell );
}
//------------------------------------------------------------------------