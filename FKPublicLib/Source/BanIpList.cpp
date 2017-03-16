/**
*	created:		2013-4-16   5:20
*	filename: 		BanIpList
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include "../Include/baniplist.h"
#include "../Include/inc.h"
//------------------------------------------------------------------------
CBanIpList::CBanIpList(void)
{
	m_pAddrArray = NULL;
	m_dwAddrCount = 0;
}
//------------------------------------------------------------------------
CBanIpList::~CBanIpList(void)
{
}
//------------------------------------------------------------------------
VOID CBanIpList::LoadBanIpList( const char * pszBanIpList )
{
	CStringFile sf( pszBanIpList );
	m_pAddrArray = new DWORD[sf.GetLineCount()];
	for( int i = 0;i < sf.GetLineCount(); i ++ )
	{
		AddAddr( sf[i] );
	}
}
//------------------------------------------------------------------------
VOID CBanIpList::AddAddr( const char * pszIpAddr )
{
	if( pszIpAddr == NULL || pszIpAddr[0] == 0 )return;
	DWORD	dwAddr = AddrToUL( pszIpAddr );
	for( DWORD i = 0;i < m_dwAddrCount; i ++ )
	{
		if( dwAddr < m_pAddrArray[i] )
		{
			for( DWORD j = m_dwAddrCount;j > i;j -- )
			{
				m_pAddrArray[j] = m_pAddrArray[j-1];
			}
			m_pAddrArray[i] = dwAddr;
			m_dwAddrCount ++;
			return;
		}
	}
	m_pAddrArray[m_dwAddrCount++] = dwAddr;
}
//------------------------------------------------------------------------
BOOL CBanIpList::InBanList( const char * pszIpAddr )
{
	DWORD	dwAddr = AddrToUL( pszIpAddr );
	DWORD	s = 0, m = 0, e = m_dwAddrCount;

	// ¶þ·Ö²éÕÒ
	while( s < e )
	{
		m = (s+e)/2;
		if( dwAddr == m_pAddrArray[m] )
			return TRUE;
		if( dwAddr < m_pAddrArray[m] )
		{
			if( e == m )
				return FALSE;
			e = m;
		}
		else
		{
			if( s == m )
				return FALSE;
			s = m;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------------
DWORD  CBanIpList::AddrToUL( const char * pszIpAddr )
{
	return (DWORD)inet_addr( pszIpAddr );
}
//------------------------------------------------------------------------