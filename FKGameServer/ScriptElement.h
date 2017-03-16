/**
*	created:		2013-4-19   9:35
*	filename: 		ScriptElement
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "ScriptFile.h"
//------------------------------------------------------------------------
#define	MAX_CALL_PARAMS	16
//------------------------------------------------------------------------
enum	e_parse_state
{
	EPS_ACT,
	EPS_SAY,
};
//------------------------------------------------------------------------
class CScriptShell;
class CScriptTarget;
class CScriptView;
class CScriptObject;
//------------------------------------------------------------------------
class CScriptElement
{
public:
	CScriptElement()
	{
		m_pNext = NULL;
		m_pPrev = NULL;
		m_nLineNumber = 0;
		m_pViewString = NULL;
	}
	virtual ~CScriptElement()
	{
		Destroy();
	}
	virtual BOOL Parse( CScriptFile & file ){ m_nLineNumber = file.GetCurrentLineNumber(); return TRUE;}
	//	执行接口
	//	需要一个SHELL和一个TARGET，还需要一个PAGEVIEW
	virtual BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView ){ return FALSE;}
	virtual VOID Destroy(){}

	VOID addTail( CScriptElement * pTail )
	{
		CScriptElement * p = this;
		while( p->getNext() )
		{
			p = p->getNext();
		}
		p->setNext( pTail );
		pTail->setPrev( p );
		pTail->setNext( NULL );
	}

	VOID delToTail()
	{
		CScriptElement * p = this;
		CScriptElement * pNext = NULL;
		while( p )
		{
			pNext = p->getNext();
			delete p;
			p = pNext;
		}
	}

	VOID setNext( CScriptElement * pNext ){ m_pNext = pNext;}
	VOID setPrev( CScriptElement * pPrev ){ m_pPrev = pPrev;}
	CScriptElement * getNext(){ return m_pNext;}
	CScriptElement * getPrev(){ return m_pPrev;}

	const char * GetViewString(){ return m_pViewString;}


	static xPacket * NewParamStack()
	{
		xPacket * packet = m_xParamStackPool.newObject();
		if( packet == NULL )
			return NULL;
		if( packet->getbuf() == NULL )
		{
			if( !packet->create( 65536 ) )
			{
				m_xParamStackPool.deleteObject( packet );
				return NULL;
			}
		}
		else
			packet->clear();
		return packet;
	}
	static VOID	DeleteParamStack( xPacket * pPacket )
	{
		pPacket->clear();	
		m_xParamStackPool.deleteObject( pPacket );
	}
protected:

	static xObjectPool<xPacket> m_xParamStackPool;
	CScriptElement * m_pNext;
	CScriptElement * m_pPrev;
	UINT			 m_nLineNumber;
	char * m_pViewString;
};
//------------------------------------------------------------------------
class CParamStackHelper
{
public:
	CParamStackHelper()
	{
		this->m_pPacket = CScriptElement::NewParamStack();
	}
	~CParamStackHelper()
	{
		if( m_pPacket )
			CScriptElement::DeleteParamStack( m_pPacket );
	}
	xPacket * getPacket(){ return m_pPacket;}
	BOOL	push( LPVOID lp, int si ){ if( m_pPacket )return m_pPacket->push( lp, si ); return FALSE;}
	char * getbuf(){ if( m_pPacket )return (char*)m_pPacket->getbuf(); return NULL;}
	char * getfreebuf(){ if( m_pPacket )return (char*)m_pPacket->getfreebuf(); return NULL;}
	int	getsize(){ if( m_pPacket )return m_pPacket->getsize(); return 0;}
	int getfreesize(){ if( m_pPacket )return m_pPacket->getfreesize();return 0;}
	void clear(){ if( m_pPacket )m_pPacket->clear();}
protected:
	xPacket * m_pPacket;
};
//------------------------------------------------------------------------
// 负责解析脚本中的[Goods]段
class CSe_Goods:
	public CScriptElement
{
public:
	CSe_Goods(){ m_pGoodsList = NULL;}
	virtual ~CSe_Goods(){ Destroy();}
	BOOL Parse( CScriptFile & file );
	VOID Destroy();

	Goods * getList(){ return m_pGoodsList;}
protected:
	VOID AddGoods( Goods * pGoods );
	Goods * m_pGoodsList;
};
//------------------------------------------------------------------------
enum	Page_Access_Right
{
	PAR_PUBLIC,
	PAR_PROTECTED,
	PAR_PRIVATE,
};
//------------------------------------------------------------------------
class CSe_Page:
	public CScriptElement
{
public:
	CSe_Page(void);
	virtual ~CSe_Page(void){ Destroy();}
	BOOL Parse( CScriptFile & file );
	BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );
	Page_Access_Right getAccessRight(){ return m_AccessRight;}
	const char * getName(){ return m_szName;}

	CScriptObject * getObject(){ return m_pObject;}
	VOID setObject( CScriptObject * pObject ){ m_pObject = pObject;}

	VOID Destroy();
protected:
	VOID	AddScriptElement( CScriptElement * pElement );
	Page_Access_Right m_AccessRight;
	char	m_szName[64];
	CScriptElement * m_pElements;
	CScriptObject * m_pObject;
};
//------------------------------------------------------------------------
class CSe_NormalAct:
	public CScriptElement
{
public:
	CSe_NormalAct()
	{
		m_nCommand = 0;
		m_nParamCount = 0;
		m_pParams = NULL;
		m_dwResult = 0;
		m_fnProc = NULL;
	}
	virtual ~CSe_NormalAct()
	{Destroy();}
	BOOL Parse( CScriptFile & file );
	BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );

	DWORD	getResult(){ return m_dwResult;}
	VOID Destroy();
protected:
	DWORD	m_dwResult;
	UINT	m_nCommand;
	DWORD	m_nParamCount;
	ScriptParamEx * m_pParams;
	fnCommandProc m_fnProc;
};
//------------------------------------------------------------------------
class CSe_NormalSay:
	public CScriptElement
{
public:
	CSe_NormalSay()
	{
		m_pSayWords = NULL;
	}
	virtual ~CSe_NormalSay()
	{Destroy();}

	BOOL Parse( CScriptFile & file );
	BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );
	VOID Destroy();
protected:
	char * m_pSayWords;
};
//------------------------------------------------------------------------
class CSe_IfStatement:
	public CScriptElement
{
public:
	CSe_IfStatement()
	{
		m_pCondition = NULL;
		m_pTrueElements = NULL;
		m_pFalseElements = NULL;
		m_pElseIfStatement = NULL;
		m_bNot = FALSE;
	}
	virtual ~CSe_IfStatement()
	{Destroy();}
	BOOL Parse( CScriptFile & file );
	BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );
	VOID Destroy();
protected:
	BOOL CheckConditionList( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );
	CSe_NormalAct * m_pCondition;
	CScriptElement * m_pTrueElements;
	CScriptElement * m_pFalseElements;
	CSe_IfStatement * m_pElseIfStatement;
	BOOL	m_bNot;
};
//------------------------------------------------------------------------
class CSe_CaseBlock:
	public CScriptElement
{
public:
	CSe_CaseBlock()
	{
		m_nCode = 0;
		m_pElements = NULL;
	}
	virtual ~CSe_CaseBlock()
	{ Destroy();}
	BOOL Parse( CScriptFile & file );
	BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );
	UINT	getCode(){ return m_nCode;}
	VOID Destroy();
protected:
	UINT	m_nCode;
	CScriptElement * m_pElements;
};
//------------------------------------------------------------------------
class CSe_SwitchStatement:
	public CScriptElement
{
public:
	CSe_SwitchStatement()
	{
		m_nCaseBlocks = 0;
		m_pBranchSource = NULL;
		m_pCaseBlocks = NULL;
		m_pDefaultBlock = NULL;
	}
	virtual ~CSe_SwitchStatement()
	{Destroy();}
	BOOL Parse( CScriptFile & file );
	BOOL Execute( CScriptShell * pShell, CScriptTarget * pTarget, CScriptView * pView );
	VOID Destroy();
protected:
	UINT	m_nCaseBlocks;
	CSe_NormalAct * m_pBranchSource;
	CSe_CaseBlock ** m_pCaseBlocks;
	CSe_CaseBlock * m_pDefaultBlock;
};
//------------------------------------------------------------------------