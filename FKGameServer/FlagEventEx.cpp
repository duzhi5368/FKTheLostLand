/**
*	created:		2013-4-19   10:30
*	filename: 		FlagEventEx
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "flageventex.h"
#include "flageventlistener.h"
//------------------------------------------------------------------------
CFlagEventEx::CFlagEventEx(UINT id, CFlagEventListener * pListener, UINT nCount )
{
	m_pListener = pListener;
	m_xFlags = NULL;
	m_nMaxCount = 0;
	Create( nCount );
	SetId( id );
	Clear();
}
//------------------------------------------------------------------------
CFlagEventEx::~CFlagEventEx(void)
{
	Destroy();
}
//------------------------------------------------------------------------
BOOL	CFlagEventEx::Create( UINT nCount )
{
	if( nCount == 0 )return 0;
	m_xFlags = new FlagEventEx[nCount];
	this->m_nMaxCount = nCount;
	return TRUE;
}
//------------------------------------------------------------------------
VOID CFlagEventEx::Destroy()
{
	if( m_xFlags )
	{
		delete []m_xFlags;
		m_xFlags = NULL;
	}
}
//------------------------------------------------------------------------
BOOL	CFlagEventEx::IsSeted( UINT index )
{
	if( index >= m_nMaxCount )return FALSE;
	return m_xFlags[index].bSeted;
}
//------------------------------------------------------------------------
VOID CFlagEventEx::SetFlag( UINT index, BOOL bEnable, DWORD dwParam, DWORD dwTimeOut )
{
	if( index >= m_nMaxCount )return;
	if( this->m_xFlags[index].bSeted == bEnable )return;
	this->m_xFlags[index].bSeted = bEnable;
	if( bEnable )
	{
		this->m_xFlags[index].dwParam = dwParam;
		this->m_xFlags[index].tmrTimeOut.Savetime( dwTimeOut );
		if( this->m_pListener )this->m_pListener->OnFlagSeted( this, index, dwParam, dwTimeOut );
	}
	else
	{
		if( this->m_pListener )this->m_pListener->OnFlagClred( this, index, m_xFlags[index].dwParam, m_xFlags[index].tmrTimeOut.GetTimeOut() );
	}
}
//------------------------------------------------------------------------
DWORD	CFlagEventEx::GetParam( UINT index )
{
	if( index >= m_nMaxCount )return 0;
	return m_xFlags[index].dwParam;
}
//------------------------------------------------------------------------
DWORD	CFlagEventEx::GetTimeOut( UINT index )
{
	if( index >= m_nMaxCount )return 0;
	return m_xFlags[index].tmrTimeOut.GetTimeOut();
}
//------------------------------------------------------------------------
VOID	CFlagEventEx::SetTimeOut( UINT index, DWORD dwTimeOut )
{
	if( index >= m_nMaxCount )return;
	return m_xFlags[index].tmrTimeOut.SetTimeOut( dwTimeOut );
}
//------------------------------------------------------------------------
VOID	CFlagEventEx::SetParam( UINT index, DWORD dwParam )
{
	if( index >= m_nMaxCount )return;
	m_xFlags[index].dwParam = dwParam;
}
//------------------------------------------------------------------------
VOID	CFlagEventEx::DecTimeOut( UINT index, DWORD dwDec )
{
	if( index >= m_nMaxCount )return;
	DWORD dwTimeOut = m_xFlags[index].tmrTimeOut.GetTimeOut();
	if( dwTimeOut > dwDec )
		dwTimeOut -= dwDec;
	else
		dwTimeOut = 0;
	m_xFlags[index].tmrTimeOut.SetTimeOut( dwTimeOut );
}
//------------------------------------------------------------------------
VOID CFlagEventEx::AddTimeOut( UINT index, DWORD dwAdd )
{
	if( index >= m_nMaxCount )return;
	DWORD dwTimeOut = m_xFlags[index].tmrTimeOut.GetTimeOut()+dwAdd;
	m_xFlags[index].tmrTimeOut.SetTimeOut( dwTimeOut );
}
//------------------------------------------------------------------------
VOID CFlagEventEx::Update()
{
	for( UINT n = 0;n < m_nMaxCount;n ++ )
	{
		if( this->m_xFlags[n].bSeted &&
			this->m_xFlags[n].tmrTimeOut.IsTimeOut() )
		{
			SetFlag( n, FALSE );
		}
	}
}
//------------------------------------------------------------------------
VOID	CFlagEventEx::Clear()
{
	memset( m_xFlags, 0, sizeof( m_xFlags ) );
}
//------------------------------------------------------------------------
DWORD	CFlagEventEx::GetFlagValue( UINT nOffset )
{
	DWORD dwFlagValue = 0;
	for( UINT i = 0;i < 32;i ++ )
	{
		if( IsSeted( nOffset + i ) )
			dwFlagValue |= (1<<i);
	}
	return dwFlagValue;
}
//------------------------------------------------------------------------