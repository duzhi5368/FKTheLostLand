/**
*	created:		2013-4-19   13:08
*	filename: 		ScriptShell
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptshell.h"
#include ".\scripttarget.h"
#include ".\scriptobject.h"
#include ".\scriptview.h"
#include ".\scriptelement.h"
//------------------------------------------------------------------------
CScriptShell::CScriptShell(void)
{
	m_pScriptObject = NULL;
	m_ExecuteResult = ER_OK;
	memset( &m_dwResultValue, 0, sizeof( m_dwResultValue ) );
	m_pCallParams = NULL;
}
//------------------------------------------------------------------------
CScriptShell::~CScriptShell(void)
{
}
//------------------------------------------------------------------------
char * CScriptShell::GetVariableValue( const char * pszVariable )
{
	if( strnicmp( pszVariable, "param", 5 ) == 0 )
	{
		UINT index = (UINT)StringToInteger( pszVariable + 5 );
		if( index >= MAX_CALL_PARAMS )return NULL;
		if( this->m_pCallParams == NULL )return NULL;
		return this->m_pCallParams[index].pszParam;
	}
	else
	{
		char * pvalue = m_xVarList.GetVarValue( pszVariable );
		if( pvalue != NULL )
			return pvalue;
	}
	return xVariableProvider::GetVariableValue( pszVariable );
}
//------------------------------------------------------------------------
//	本函数返回FALSE后，必须清空所有连接～
BOOL CScriptShell::Execute( CScriptTarget * pTarget, const char * pszPage1, BOOL bUserQuery, DWORD dwParam)
{
	CScriptPageView view(this);
	CParamStackHelper paramstack;

	char	szPage[1024];
	char * pszPage = NULL;
	CallParamEx params[MAX_CALL_PARAMS];
	setExecuteResult( ER_OK );
	if( m_pScriptObject == NULL )return FALSE;
	//	如果是第一次进入该SHELL
	BOOL	bFirstPage = FALSE;
	if( pszPage1 == NULL )
	{
		//	清空所有的连接
		pTarget->setCurScriptObject( NULL );
		pTarget->setCurShell( NULL );
		pszPage = "@main";
		bFirstPage = TRUE;
	}
	else
	{
		o_strncpy( szPage, pszPage1, 1020 );
		xStringsExtracter<MAX_CALL_PARAMS+1> queryparam( szPage, "&" );
		for( UINT n = 1;n < queryparam.getCount();n++ )
		{
			params[n-1] = queryparam[n];
			if( *params[n-1].pszParam == '$' )
			{
				char * p = pTarget->GetVariableValue( params[n-1].pszParam + 1 );
				if( p )
				{
					char * lparam = (char*)paramstack.getfreebuf();
					paramstack.push( (LPVOID)p, (int)strlen( p )+1 );
					params[n-1] = lparam;
				}
				else
					params[n-1] = "";
			}
		}
		if( queryparam.getCount() > 1 )
			this->m_pCallParams = params;
		pszPage = (char*)szPage;
	}
	//	如果当前SHELL不是本SHELL
	if( pTarget->getCurShell() != this )
	{
		//	连接到本SHELL，清空页面连接
		pTarget->setCurScriptObject( NULL );
		pTarget->setCurShell( this );
	}

	//	获取请求的页面
	CSe_Page * pPage = NULL;
	
	//	如果当前脚本不是本地SHELL的脚本
	if( pTarget->getCurScriptObject() && pTarget->getCurScriptObject() != this->m_pScriptObject )
	{
		//	从远程脚本取得请求的页面
		pPage = pTarget->getCurScriptObject()->GetPage( pszPage );
	}
	else
		//	从本地脚本取得请求的页面
		pPage = m_pScriptObject->GetPage( pszPage );
	if( pPage == NULL )
		return FALSE;
	//	如果页面没有访问权限，则无法访问页面
	if( bUserQuery && pPage->getAccessRight() != PAR_PUBLIC )
		return FALSE;
	//	设置为当前页面
	pTarget->setCurScriptObject( pPage->getObject() );

	//	执行页面
	if( !pPage->Execute( this, pTarget, &view ) )
	{
		//	执行结果是关闭页面，就关闭页面
		if( getExecuteResult() == ER_CLOSE )
		{
			pTarget->SendClosePage( this );
			return TRUE;
		}
	}
	//	呼叫派生类对特殊PAGEID的处理。
	if( !OnPageShow( pTarget, &view, pszPage ) )
		return FALSE;
	//	否则，发送页面
	view.SendPageToTarget( pTarget, dwParam); 
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CScriptShell::Execute( CScriptTarget * pTarget, CSe_Page * pPage, BOOL bUserQuery, DWORD dwParam)
{	
	CScriptPageView view(this);
	CParamStackHelper paramstack;

	setExecuteResult( ER_OK );

	if( pPage == NULL )
		return FALSE;
	//	如果页面没有访问权限，则无法访问页面
	if( bUserQuery && pPage->getAccessRight() != PAR_PUBLIC )
		return FALSE;
	//	设置为当前页面
	pTarget->setCurScriptObject( pPage->getObject() );

	//	执行页面
	if( !pPage->Execute( this, pTarget, &view ) )
	{
		//	执行结果是关闭页面，就关闭页面
		if( getExecuteResult() == ER_CLOSE )
		{
			pTarget->SendClosePage( this );
			return TRUE;
		}
	}
	view.SendPageToTarget( pTarget, dwParam);
	return TRUE;
}
//------------------------------------------------------------------------