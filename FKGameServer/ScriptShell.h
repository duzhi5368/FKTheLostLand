/**
*	created:		2013-4-19   13:01
*	filename: 		scriptshell
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CScriptTarget;
class CScriptObject;
//------------------------------------------------------------------------
// Ö´ÐÐ½á¹û
enum	Execute_Result
{
	ER_OK,
	ER_CLOSE,
	ER_RETURN,
	ER_BREAK,
};
//------------------------------------------------------------------------
class CSe_Page;
//------------------------------------------------------------------------
class CScriptShell :
	public xVariableProvider
{
public:
	CScriptShell(void);
	virtual ~CScriptShell(void);
public:
	BOOL 					Execute( CScriptTarget * pTarget, const char * pszPage = NULL, BOOL bUserQuery = TRUE, DWORD dwParam = 0);
	BOOL 					Execute( CScriptTarget * pTarget, CSe_Page * pPage, BOOL bUserQuery = TRUE, DWORD dwParam = 0);
	char *					GetVariableValue( const char * pszVariable );
public:
	virtual const char *	GetTitleName(){ return "";}
	virtual UINT 			GetTitleId(){ return 0xffffffff;}
	virtual UINT 			GetNpcId(){ return 0xffffffff;}
	virtual UINT 			GetForceId(){ return 0xffff;}
	virtual BOOL 			OnPageShow( CScriptTarget * pTarget, CScriptView * pView, const char * pszPage ){ return TRUE;}

	Execute_Result			getExecuteResult(){ return m_ExecuteResult;}
	CallParamEx &			getExecuteResultValue(){ return m_dwResultValue;}
	CScriptObject * 		getScriptObject(){ return m_pScriptObject;}
	virtual BOOL			setScriptObject(CScriptObject* scriptobj){ m_pScriptObject = scriptobj;return TRUE;}
	VOID					setCallParams( CallParamEx * pParams ){ m_pCallParams = pParams;}
	CallParamEx *			getCallParams(){ return m_pCallParams;}
public:
	VOID setExecuteResult( Execute_Result result, const char * pszValue = NULL )
	{
		m_ExecuteResult = result;
		m_xVarList.AddVar( "returnvalue", (char*)pszValue );
		m_dwResultValue.nParam = pszValue == NULL?0:StringToInteger( pszValue );
	}
protected:
	xVarList<32>				m_xVarList;	//	_return, _p1, _p2, _p3, _p4
	CScriptObject * 			m_pScriptObject;
	Execute_Result				m_ExecuteResult;
	CallParamEx					m_dwResultValue;
	CallParamEx	*				m_pCallParams;
};
//------------------------------------------------------------------------