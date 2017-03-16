/**
*	created:		2013-4-19   10:29
*	filename: 		FlagEventEx
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CFlagEventListener;
//------------------------------------------------------------------------
typedef struct stFlagEventEx
{
	stFlagEventEx()
	{
		memset( this, 0, sizeof( *this ) );
	}
	BOOL		bSeted;
	DWORD	dwParam;
	CServerTimer tmrTimeOut;
}FlagEventEx;
//------------------------------------------------------------------------
class CFlagEventEx
{
public:
	CFlagEventEx(UINT id = 0, CFlagEventListener * pListener = NULL, UINT nCount = 0);
	virtual ~CFlagEventEx(void);
	BOOL	Create( UINT nCount );
	VOID	Destroy();
	BOOL	IsSeted( UINT index );
	VOID	SetFlag( UINT index, BOOL bEnable = FALSE, DWORD dwParam = 0, DWORD dwTimeOut = 0xffffffff );
	DWORD	GetParam( UINT index );
	DWORD	GetTimeOut( UINT index );
	VOID	SetTimeOut( UINT index, DWORD dwTimeOut );
	VOID	SetParam( UINT index, DWORD dwParam );
	VOID	DecTimeOut( UINT index, DWORD dwDec = 1);
	VOID	AddTimeOut( UINT index, DWORD dwAdd = 1);

	VOID	Update();
	VOID	Clear();

	CFlagEventListener * GetListener(){ return m_pListener;}
	VOID SetListener( CFlagEventListener * pListener ){ m_pListener = pListener;}

	UINT GetId(){ return m_nId;}
	VOID SetId( UINT id ){ m_nId = id;}

	DWORD	GetFlagValue( UINT nOffset );
protected:
	CFlagEventListener * m_pListener;
	FlagEventEx * m_xFlags;
	UINT	m_nMaxCount;
	UINT	m_nId;
};
//------------------------------------------------------------------------