/**
*	created:		2013-4-19   9:37
*	filename: 		ScriptElement
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptelement.h"
#include ".\scriptview.h"
#include ".\scripttarget.h"
#include ".\scriptshell.h"
#include ".\scriptobjectmgr.h"
#include ".\scriptobject.h"
#include ".\humanplayer.h"
#include ".\cmdproc.h"
//------------------------------------------------------------------------
xObjectPool<xPacket> CScriptElement::m_xParamStackPool;
//------------------------------------------------------------------------
BOOL	g_bDebugScript = FALSE;
//------------------------------------------------------------------------
BOOL CSe_Goods::Parse( CScriptFile & file )
{
	char * pLine = NULL;
	while( pLine = file.NextLine() )
	{
		if( *pLine == '[' )
		{
			file.PrevLine();
			return TRUE;
		}
		xStringsExtracter<3> goods( pLine, " \t", " \t" );
		if( goods[0] == NULL || goods[0][0] == 0 )continue;
		Goods * pGoods = new Goods;
		/*
		o_strncpy( pGoods->szName, goods[0], 30 );
		if( goods[1] )
			pGoods->wCount = (WORD)StringToInteger( goods[1] );
		else
			pGoods->wCount = 0;
		if( goods[2] )
			pGoods->wRefreshTime = (WORD)StringToInteger( goods[2] );
		else
			pGoods->wRefreshTime = 5;
		*/
		AddGoods( pGoods );
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CSe_Goods::AddGoods( Goods * pGoods )
{
	if( this->m_pGoodsList )
	{
		Goods * p = m_pGoodsList;
		while( p->pNext )
			p = p->pNext;
		p->pNext = pGoods;
	}
	else
		m_pGoodsList = pGoods;
	pGoods->pNext = NULL;
}
//------------------------------------------------------------------------
VOID CSe_Goods::Destroy()
{
	Goods * p = m_pGoodsList;
	Goods * pNext = NULL;
	while( p )
	{
		pNext = p->pNext;
		delete p;
		p = pNext;
	}
}
//------------------------------------------------------------------------
CSe_Page::CSe_Page(void)
{
	this->m_pElements = NULL;
	this->m_AccessRight = PAR_PUBLIC;
	this->m_szName[0] = 0;
	m_pObject = NULL;
}
//------------------------------------------------------------------------
BOOL	CSe_Page::Parse( CScriptFile & file )
{
	CScriptElement::Parse( file );
	char * pLine = file.CurrentLine();
	if( pLine == NULL )return FALSE;
	char * tp = strchr( pLine, ':' );
	if( tp )
	{
		*tp++= 0;
		pLine = TrimEx( pLine );
		tp = TrimEx( tp );
		if( stricmp( tp, "public" ) == 0 )
			this->m_AccessRight = PAR_PUBLIC;
		else if( stricmp( tp, "private" ) == 0 )
			this->m_AccessRight = PAR_PRIVATE;
		else if( stricmp( tp, "protected" ) == 0 )
			this->m_AccessRight = PAR_PROTECTED;
		else
			this->m_AccessRight = PAR_PUBLIC;
	}
	if( *pLine == '[' )pLine++;
	tp = strchr( pLine, ']' );
	if( tp )
	{
		*tp = 0;
		pLine = TrimEx( pLine );
	}
	if( *pLine == '@' )
		o_strncpy( m_szName, pLine, 60 );
	else
	{
		m_szName[0] = '@';
		o_strncpy( m_szName+1, pLine, 60 );
	}
	e_parse_state parsestate = EPS_SAY;
	while( pLine = file.NextLine() )
	{
		if( *pLine == 0 )continue;
		if( *pLine == '#' )
		{
			CScriptElement * pElement = NULL;
			if( stricmp( pLine, "#if" ) == 0 ||stricmp( pLine, "#ifnot" ) == 0  )
			{
				pElement = new CSe_IfStatement;
				if( !pElement->Parse( file ) )
				{
					PRINT( 0xff, "if 块解析失败在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
					delete pElement;
				}
				else
				{
					this->AddScriptElement( pElement );
				}
			}
			else if( stricmp( pLine, "#switch" ) == 0 )
			{
				pElement = new CSe_SwitchStatement;
				if( !pElement->Parse( file ) )
				{
					PRINT( 0xff, "switch 块解析失败在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
					delete pElement;
				}
				else
				{
					this->AddScriptElement( pElement );
				}			
			}
			else if( stricmp( pLine, "#act" ) == 0 )
			{
				parsestate = EPS_ACT;
			}
			else if( stricmp( pLine, "#say" ) == 0 )
			{
				parsestate = EPS_SAY;
			}
			else
			{
				PRINT( 0xff, "非法指令 %s 在 %s 的 %u 行！\n", file.CurrentLine(), file.GetFileName(), file.GetCurrentLineNumber() );
				return FALSE;
			}
		}
		else if( *pLine == '[' )
		{
			file.PrevLine();
			break;
		}
		else
		{
			CScriptElement * pElement = NULL;
			if( parsestate == EPS_ACT )
			{
				pElement = new CSe_NormalAct;
			}
			else
			{
				pElement = new CSe_NormalSay;
			}
			if( !pElement->Parse( file ) )
			{

				PRINT( 0xff, "语句 %s 解析失败在 %s 的 %u 行！\n", file.CurrentLine(), file.GetFileName(), file.GetCurrentLineNumber() );
				delete pElement;
			}
			else
				this->AddScriptElement( pElement );
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID	CSe_Page::AddScriptElement( CScriptElement * pElement )
{
	if( m_pElements )
		m_pElements->addTail( pElement );
	else
		m_pElements = pElement;
}
//------------------------------------------------------------------------
BOOL CSe_Page::Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{
	if( g_bDebugScript )
	{ 
		PRINT( 0xff, "(" );
		PRINT( 0xff00, "%u", this->m_nLineNumber );
		PRINT( 0xff, ")[" );
		PRINT( 0xff00, "%s", ((CScriptTargetForPlayer*)pTarget)->GetOwner()->GetName() );
		PRINT( 0xff, "]" );
		PRINT( 0xff, ":ExecPage:" );
		PRINT( 0xff00, "%s.%s \n", this->m_pObject->getName(), this->m_szName );
	}
	CScriptElement * p = m_pElements;  
	while( p ) 
	{
		if( !p->Execute( pShell, pTarget, pView ) )
			return FALSE;
		p = p->getNext();
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CSe_Page::Destroy()
{
	if( m_pElements )
	{
		this->m_pElements->delToTail();
		m_pElements = NULL;
	}
}
//------------------------------------------------------------------------
BOOL CSe_NormalAct::Parse( CScriptFile & file )
{
	CScriptElement::Parse( file );
	xCharSet csWht( " \t\"" );
	xCharSet csSpl( " \t," );
	char * pLine = file.CurrentLine();
	if( pLine == NULL || *pLine == 0 )return FALSE;
	char * Params[20];
	replaceOutPair( pLine, '(', ')', ' ' );
	int nParam = ExtractStrings( pLine, csWht, csSpl, Params, 20, FALSE );
	if( nParam <= 0 )return FALSE;
	m_fnProc = CCommandManager::GetInstance()->GetCommandProc( Params[0] );
	if( m_fnProc == NULL )return FALSE;

	m_nParamCount = nParam - 1;
	if( m_nParamCount > 0 )
	{
		if( m_nParamCount > MAX_CALL_PARAMS+1 )m_nParamCount = MAX_CALL_PARAMS+1;
		m_pParams = new ScriptParamEx[m_nParamCount];
		for( UINT i = 0;i < m_nParamCount;i ++ )
		{
			char * p = Params[i+1];
			if( *p == '$' )
			{
				//	看看是不是define里面的
				p = CScriptObjectMgr::GetInstance()->GetVariableValue( p+1 );
				if( p )
				{
					m_pParams[i].wType = SP_STRING;
					m_pParams[i].nParam = (UINT)StringToInteger( p );
				}
				else
				{
					m_pParams[i].wType = SP_VARIABLE;
					p = Params[i+1]+1;
				}
				m_pParams[i].pszParam = copystring( p );
			}
			else
			{
				m_pParams[i].wType = SP_STRING;
				m_pParams[i].pszParam = copystring( p );
				m_pParams[i].nParam = (UINT)StringToInteger( p );
			}
		}
	}
	m_pViewString = copystring( Params[0] );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CSe_NormalAct::Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{
	CParamStackHelper paramstack;
	if( m_fnProc == NULL )return FALSE;
	//	构建最终参数表
	CallParamEx Params[MAX_CALL_PARAMS+1];
	for( UINT i = 0;i < m_nParamCount;i ++ )
	{
		if( m_pParams[i].wType == SP_VARIABLE )
		{
			char * p = pTarget->GetVariableValue( m_pParams[i].pszParam );
			if( p )
			{
				Params[i].pszParam = (char*)paramstack.getfreebuf();
				paramstack.push( (LPVOID)p, (int)strlen( p ) + 1 );
				Params[i].nParam = (UINT)StringToInteger( Params[i].pszParam );
			}
			else
			{
				Params[i].pszParam = "";
				Params[i].nParam = 0;
			}
		}
		else
		{
			Params[i].pszParam = m_pParams[i].pszParam;
			Params[i].nParam = m_pParams[i].nParam;
		}
	}
	//	调用
	BOOL	bContinue = TRUE;
	if( g_bDebugScript )
	{
		PRINT( 0xff, "(" );
		PRINT( 0xff00, "%u", this->m_nLineNumber );
		PRINT( 0xff, ")[" );
		PRINT( 0xff00, "%s", ((CScriptTargetForPlayer*)pTarget)->GetOwner()->GetName() );
		PRINT( 0xff, "]" );
		PRINT( 0xff, ":ExecCmd:" );
		PRINT( 0xff00, "%s ", m_pViewString );
		for( UINT i = 0;i < m_nParamCount;i ++ )
		{ 
			PRINT( 0xff00, "%s ", Params[i].pszParam );
		}
		PRINT( 0xff, "\n" ); 
	}
	m_dwResult = m_fnProc( /*(CScriptShell *)*/pShell, /*(CScriptTarget *)*/pTarget, /*(CScriptView *)*/pView, Params, m_nParamCount, bContinue );
	return bContinue;
}
//------------------------------------------------------------------------
VOID CSe_NormalAct::Destroy()
{
	if( m_pParams )
	{
		delete []m_pParams;
		m_pParams = NULL;
	}
	if( m_pViewString )
	{
		delete []	m_pViewString;
		m_pViewString = NULL;
	}
	m_fnProc = NULL;
}
//------------------------------------------------------------------------
static char	g_szTempBuffer[65536];
//------------------------------------------------------------------------
BOOL CSe_NormalSay::Parse( CScriptFile & file )
{
	CScriptElement::Parse( file );
	char * pLine = file.CurrentLine();
	if( pLine == NULL || *pLine == 0 )return FALSE;
	int size = ProcFmtText( pLine, g_szTempBuffer, 65536, (xVariableProvider*)CScriptObjectMgr::GetInstance() );
	if( size > 0 )
		this->m_pSayWords = copystring( g_szTempBuffer );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CSe_NormalSay::Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{

	if( m_pSayWords )
	{
		int size = ProcFmtText( m_pSayWords, g_szTempBuffer, 65536, (xVariableProvider*)pTarget );
		if( g_bDebugScript )
		{
			PRINT( 0xff, "(" );
			PRINT( 0xff00, "%u", this->m_nLineNumber );
			PRINT( 0xff, ")[" );
			PRINT( 0xff00, "%s", ((CScriptTargetForPlayer*)pTarget)->GetOwner()->GetName()  );
			PRINT( 0xff, "]" );
			PRINT( 0xff, ":AddWords:" );
			PRINT( 0xff00, "%s \n", g_szTempBuffer );
		}		
		pView->AppendWords( g_szTempBuffer );
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CSe_NormalSay::Destroy()
{
	if( m_pSayWords )
	{
		delete []m_pSayWords;
		m_pSayWords = NULL;
	}
}
//------------------------------------------------------------------------
enum	if_parse_state
{
	IPS_IF,
	IPS_TRUE,
	IPS_FALSE,
};
//------------------------------------------------------------------------
BOOL CSe_IfStatement::Parse( CScriptFile & file )
{
	char * pLine = NULL;
	e_parse_state parsestate = EPS_ACT;
	if_parse_state statementstate = IPS_IF;
	pLine = file.CurrentLine();
	if( stricmp( pLine, "#ifnot" ) == 0 )
		this->m_bNot = TRUE;
	else 
		this->m_bNot = FALSE;
	while( pLine = file.NextLine() )
	{
		if( *pLine == 0 )continue;
		if( *pLine == '#' )
		{
			if( stricmp( pLine, "#act" ) == 0 )
			{
				//	如果正在解析FALSE部分
				if( statementstate == IPS_FALSE )
				{
					file.PrevLine();
					break;
				}
				parsestate = EPS_ACT;
				if( statementstate != IPS_TRUE )statementstate = IPS_TRUE;
			}
			else if( stricmp( pLine, "#say" ) == 0 )
			{
				if( statementstate == IPS_FALSE )
				{
					file.PrevLine();
					break;
				}
				parsestate = EPS_SAY;
				if( statementstate != IPS_TRUE )statementstate = IPS_TRUE;
			}
			else if( stricmp( pLine, "#elseact" ) == 0 )
			{
				parsestate = EPS_ACT;
				if( statementstate != IPS_FALSE )statementstate = IPS_FALSE;
			}
			else if( stricmp( pLine, "#elsesay" ) == 0 )
			{
				parsestate = EPS_SAY;
				if( statementstate != IPS_FALSE )statementstate = IPS_FALSE;
			}
			else if( stricmp( pLine, "#end" ) == 0 )
			{
				return TRUE;
			}
			else if( stricmp( pLine, "#elseif" ) == 0 )
			{
				this->m_pElseIfStatement = new CSe_IfStatement;
				return this->m_pElseIfStatement->Parse( file );
			}
			else
			{
				file.PrevLine();
				break;
			}
		}
		else if( *pLine == '[' )
		{
			file.PrevLine();
			break;
		}
		else
		{
			CScriptElement * pElement = NULL;

			if( statementstate == IPS_IF )
				parsestate = EPS_ACT;

			if( parsestate == EPS_ACT )
				pElement = new CSe_NormalAct;
			else
				pElement = new CSe_NormalSay;

			if( !pElement->Parse( file ) )
			{
				PRINT( 0xff, "语句 %s 解析失败在 %s 的 %u 行！\n", file.CurrentLine(), file.GetFileName(), file.GetCurrentLineNumber() );
				delete pElement;
			}
			else
			{
				CScriptElement **ppList = NULL;
				if( statementstate == IPS_IF )
					ppList = (CScriptElement **)&m_pCondition;
				else if( statementstate == IPS_TRUE )
					ppList = (CScriptElement **)&m_pTrueElements;
				else 
					ppList = (CScriptElement **)&m_pFalseElements;

				if( ppList )
				{
					if( *ppList )
						(*ppList)->addTail( pElement );
					else
						*ppList = pElement;
				}
			}

		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CSe_IfStatement::CheckConditionList( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{
	CSe_NormalAct * p = m_pCondition;
	while( p )
	{
		p->Execute( pShell, pTarget, pView );
		if( p->getResult() == 0 )return FALSE;
		p = (CSe_NormalAct *)p->getNext();
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CSe_IfStatement::Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{
	CScriptElement * pElement = NULL;
	CScriptElement * p = NULL;

	BOOL bCheckResult = CheckConditionList( pShell, pTarget, pView );

	if( this->m_bNot )
		bCheckResult = !bCheckResult;
	if( bCheckResult )
		p = m_pTrueElements;
	else
		p = m_pFalseElements;

	while( p )
	{
		if( !p->Execute( pShell, pTarget, pView ) )
			return FALSE;
		p = p->getNext();
	}

	if( !bCheckResult && this->m_pElseIfStatement )
	{
		return this->m_pElseIfStatement->Execute( pShell, pTarget, pView );
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID	CSe_IfStatement::Destroy()
{
	if( m_pCondition )
	{
		m_pCondition->delToTail();
		m_pCondition = NULL;
	}
	if( m_pTrueElements )
	{
		m_pTrueElements->delToTail();
		m_pTrueElements = NULL;
	}
	if( m_pFalseElements )
	{
		m_pFalseElements->delToTail();
		m_pFalseElements = NULL;
	}
}
//------------------------------------------------------------------------
BOOL CSe_CaseBlock::Parse( CScriptFile & file )
{
	char * pLine = file.CurrentLine();
	if( pLine == NULL )return FALSE;

	if( strnicmp( pLine, "#case:", 6 ) == 0 )
		m_nCode = StringToInteger( pLine + 6 );
	else
		m_nCode = 0;

	e_parse_state state = EPS_ACT;

	while( pLine = file.NextLine() )
	{
		if( *pLine == 0 )continue;
		if( *pLine == '#' )
		{
			if( stricmp( pLine, "#act" ) == 0 )
				state = EPS_ACT;
			else if( stricmp( pLine, "#say" ) == 0 )
				state = EPS_SAY;
			else
			{
				file.PrevLine();
				break;
			}
		}
		else if( *pLine == '[' )
		{
			file.PrevLine();
			break;
		}
		else
		{
			CScriptElement * pElement = NULL;
			if( state == EPS_ACT )
				//	parse act command
				pElement = new CSe_NormalAct;
			else
				//	parse say command
				pElement = new CSe_NormalSay;
			if( !pElement->Parse( file ) )
			{
				PRINT( 0xff, "语句 %s 解析失败在 %s 的 %u 行！\n", file.CurrentLine(), file.GetFileName(), file.GetCurrentLineNumber() );
				delete pElement;
			}
			else
			{
				if( m_pElements )
					m_pElements->addTail( pElement );
				else
					m_pElements = pElement;
			}
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CSe_CaseBlock::Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{
	CScriptElement * p = this->m_pElements;
	while( p )
	{
		if( !p->Execute( pShell, pTarget, pView ) )
			return FALSE;
		p = p->getNext();
	}
	return TRUE;
}
//------------------------------------------------------------------------
VOID CSe_CaseBlock::Destroy()
{
	this->m_nCode = 0;
	if( m_pElements )
	{
		this->m_pElements->delToTail();
		this->m_pElements = NULL;
	}
}
//------------------------------------------------------------------------
enum	switch_parse_state
{
	SPS_SWITCH,
	SPS_CASESAY,
	SPS_CASEACT,
	SPS_DEFAULTSAY,
	SPS_DEFAULTACT,
};
//------------------------------------------------------------------------
BOOL CSe_SwitchStatement::Parse( CScriptFile & file )
{
	UINT nStartIndex = file.GetCurrentLineNumber();
	char * pLine = NULL;
	UINT nCaseBlocks = 0;
	UINT nDefaultBlocks = 0;
	//	计算CASE的数量
	while( pLine = file.NextLine() )
	{
		if( pLine[0] == 0 )continue;
		if( pLine[0] == '[' )break;
		if( pLine[0] != '#' )continue;

		if( strnicmp( pLine, "#case:", 6 ) == 0 )
			nCaseBlocks ++;
		else if( stricmp( pLine, "#default" ) == 0 )
			continue;
		else if( stricmp( pLine, "#switch" ) == 0 )
			continue;
		else if( stricmp( pLine, "#say" ) == 0 )
			continue;
		else if( stricmp( pLine, "#act" ) == 0 )
			continue;
		else
			break;
	}

	switch_parse_state parsestate = SPS_SWITCH;
	file.SetLineIndex( nStartIndex );
	m_nCaseBlocks = 0;
	if( nCaseBlocks > 0 )
	{
		this->m_pCaseBlocks = new CSe_CaseBlock*[nCaseBlocks];
		memset( m_pCaseBlocks, 0, sizeof( CSe_CaseBlock*) * nCaseBlocks );
	}
	while( pLine = file.NextLine() )
	{
		//	ok, we jump over empty lines
		if( pLine[0] == 0 )continue;
		if( pLine[0] == '#' )
		{
			parsestate = SPS_CASESAY;
			if( strnicmp( pLine, "#case:", 6 ) == 0 )
			{
				//	new case 
				m_pCaseBlocks[m_nCaseBlocks] = new CSe_CaseBlock;
				if( !m_pCaseBlocks[m_nCaseBlocks]->Parse( file ) )
				{
					PRINT( 0xff, "CASE块解析失败在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
					delete m_pCaseBlocks[m_nCaseBlocks];
					m_pCaseBlocks[m_nCaseBlocks] = NULL;
				}
				else
					m_nCaseBlocks ++;
			}
			else if( stricmp( pLine, "#default" ) == 0 )
			{
				if( m_pDefaultBlock )
				{
					//	todo: error 'default' too more
					PRINT( 0xff, "多余的DEFAULT在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
				}
				else
				{
					m_pDefaultBlock = new CSe_CaseBlock;
					if( !m_pDefaultBlock->Parse( file ) )
					{
						PRINT( 0xff, "DEFAULT解析失败在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
						delete m_pDefaultBlock;
						m_pDefaultBlock = NULL;
					}
				}
			}
			else if( stricmp( pLine, "#end" ) == 0 )
			{
				return TRUE;
			}
			else if( stricmp( pLine, "#switch" ) == 0 )
			{
				//	多余的switch
				file.PrevLine();
				break;
			}
			else
			{
				file.PrevLine();
				break;
			}
		}
		else if( *pLine == '[' )
		{
			file.PrevLine();
			break;
		}
		else
		{
			if( parsestate == SPS_SWITCH )
			{
				if( this->m_pBranchSource != NULL )
				{
					PRINT( 0xff00, "警告: switch过多的条件项目在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
					continue;
				}
				else
				{
					m_pBranchSource = new CSe_NormalAct;
					if( !m_pBranchSource->Parse( file ) )
					{
						PRINT( 0xff00, "错误: Switch 条件解析失败在 %s 的 %u 行！\n", file.GetFileName(), file.GetCurrentLineNumber() );
						delete m_pBranchSource;
						m_pBranchSource = NULL;
					}
				}
			}
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CSe_SwitchStatement::Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView )
{
	if( m_pBranchSource )
	{
		if( !m_pBranchSource->Execute( pShell, pTarget, pView ) )
			return FALSE;
		DWORD nCode = m_pBranchSource->getResult();

		for( UINT i = 0;i < this->m_nCaseBlocks;i ++ )
		{
			if( this->m_pCaseBlocks[i] &&
				this->m_pCaseBlocks[i]->getCode() == nCode )
				return this->m_pCaseBlocks[i]->Execute( pShell, pTarget, pView );
		}
		
	}
	if( this->m_pDefaultBlock )
		return m_pDefaultBlock->Execute( pShell, pTarget, pView );
	return TRUE;
}
//------------------------------------------------------------------------
VOID CSe_SwitchStatement::Destroy()
{
	if( m_pCaseBlocks != NULL )
	{
		for( UINT n = 0;n < this->m_nCaseBlocks;n ++ )
		{
			if( m_pCaseBlocks[n] )
				delete m_pCaseBlocks[n];
		}
		delete []m_pCaseBlocks;
		m_pCaseBlocks = NULL;
	}
	m_nCaseBlocks = 0;
	if( m_pBranchSource )
	{
		delete m_pBranchSource;
		m_pBranchSource = NULL;
	}
	if( m_pDefaultBlock )
	{
		delete m_pDefaultBlock;
		m_pDefaultBlock = NULL;
	}
}
//------------------------------------------------------------------------