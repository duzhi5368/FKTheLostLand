/**
*	created:		2013-4-19   12:47
*	filename: 		ScriptTarget
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CScriptView;
class CSe_Page;
class CScriptShell;
class CScriptObject;
//------------------------------------------------------------------------
class CScriptTarget:
	public xVariableProvider
{
public:
	CScriptTarget(void);
	virtual ~CScriptTarget(void);

	virtual VOID	SendPage( CScriptShell * pShell, CScriptView * pView){}
	virtual VOID	SendClosePage( CScriptShell * pShell ){ setCurScriptObject( NULL ); setCurShell( NULL );}
	virtual char *	GetVariableValue( const char * pszVariable );
	CScriptObject * getCurScriptObject(){ return m_pCurScriptObject;}
	VOID			setCurScriptObject( CScriptObject * pObject ){ m_pCurScriptObject = pObject;}
	CScriptShell *	getCurShell(){ return m_pCurShell;}
	VOID			setCurShell( CScriptShell * pShell ){ m_pCurShell = pShell;}
	VOID 			SetInputPage( const char * pszPage, CScriptShell * pInputShell, UINT nLength );
	VOID 			OnInputConfirm( char * pszInputText );
	VOID 			SetPutItemPage( const char * pszPage, CScriptShell * pPutItemShell );
	VOID 			OnPutItem( UINT nShellId, UINT nMakeIndex );
	virtual VOID 	SetVariableValue( const char * pszVariable, const char * pszValue );
	virtual VOID 	ClrVariable( const char * pszVariable );
	virtual BOOL 	AddVariable( const char * pszVariable, const char * pszValue );
protected:
	char			m_szToPage[64];
	CScriptShell *	m_pInputShell;
	UINT			m_nInputLength;
	CScriptObject * m_pCurScriptObject;
	CScriptShell *	m_pCurShell;
	xVarList<32>	m_xVarList;
};
//------------------------------------------------------------------------
class CHumanPlayer;
//------------------------------------------------------------------------
class CScriptTargetForPlayer:
	public CScriptTarget
{
public:
	CScriptTargetForPlayer(){ m_pOwner = NULL; };
	CScriptTargetForPlayer( CHumanPlayer * pPlayer );
	VOID 			SendPage( CScriptShell * pShell, CScriptView * pView);
	VOID 			SendClosePage( CScriptShell * pShell );
	char *			GetVariableValue(  char * pszVariable );
	VOID 			SetVariableValue(  char * pszVariable,  char * pszValue );
	VOID 			ClrVariable( char * pszVariable );
	BOOL 			AddVariable(  char * pszVariable, char * pszValue );
	VOID 			Clean();
	CHumanPlayer *	GetOwner(){ return m_pOwner;}
	VOID			SaveVars( const char * pszFilename );
	VOID			LoadVars( const char * pszFilename );
protected:
	CHumanPlayer *	m_pOwner;
};
//------------------------------------------------------------------------