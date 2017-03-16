/**
*	created:		2013-4-14   20:44
*	filename: 		BanIpListEx
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "stdafx.h"
#include "../Include/inc.h"
#include "../Include/baniplistex.h"
//------------------------------------------------------------------------
CIpListEx::CIpListEx(void)
{
	this->m_pMaskAddress = NULL;
	this->m_pNormalAddress = NULL;
	this->m_pRangeAddress = NULL;
}
//------------------------------------------------------------------------
CIpListEx::~CIpListEx(void)
{
	if( this->m_pMaskAddress )delete []this->m_pMaskAddress;
	if( this->m_pRangeAddress )delete []this->m_pRangeAddress;
	if( this->m_pNormalAddress )delete []this->m_pNormalAddress;

	this->m_dwMaskAddressCount = 0;
	this->m_dwNormalAddressCount = 0;
	this->m_dwRangeAddressCount = 0;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::Load( const char * pszFilename )
{
	THREAD_PROTECT;	//	读取和检测要进行线程保护
	CStringFile sf( pszFilename );

	char * pszAddress = NULL;
	

	if( this->m_pMaskAddress )
	{
		delete []this->m_pMaskAddress;
		this->m_pMaskAddress = NULL;
	}
	if( this->m_pRangeAddress )
	{
		delete []this->m_pRangeAddress;
		this->m_pRangeAddress = NULL;
	}
	if( this->m_pNormalAddress )
	{
		delete []this->m_pNormalAddress;
		this->m_pNormalAddress = NULL;
	}

	this->m_dwMaskAddressCount = 0;
	this->m_dwNormalAddressCount = 0;
	this->m_dwRangeAddressCount = 0;

	for( UINT i = 0;i < (UINT)sf.GetLineCount();i ++ )
	{
		pszAddress = TrimEx( sf[i] );
		if( *pszAddress == 0 ||
			*pszAddress == '#' )continue;
		if( strchr( pszAddress, '-' ) != NULL )
			this->m_dwRangeAddressCount ++;
		else if( strchr( pszAddress, ':' ) != NULL )
			this->m_dwMaskAddressCount ++;
		else
			this->m_dwNormalAddressCount ++;
	}

	if( this->m_dwMaskAddressCount > 0 )
		this->m_pMaskAddress = new MaskAddress[this->m_dwMaskAddressCount];
	if( this->m_dwRangeAddressCount > 0 )
		this->m_pRangeAddress = new RangeAddress[this->m_dwRangeAddressCount];
	if( this->m_dwNormalAddressCount > 0 )
		this->m_pNormalAddress = new DWORD[this->m_dwNormalAddressCount];

	char * p = NULL;

	for( UINT i = 0;i < (UINT)sf.GetLineCount();i ++ )
	{
		pszAddress = TrimEx( sf[i] );
		if( *pszAddress == 0 ||
			*pszAddress == '#' )continue;
		if( (p = strchr( pszAddress, '-' )) != NULL )
		{
			*p++ = 0;
			AddRangeAddr(  (DWORD)ntohl(inet_addr( TrimEx(pszAddress) )),  (DWORD)ntohl(inet_addr( TrimEx(p) )) );
		}
		else if( (p = strchr( pszAddress, ':' )) != NULL )
		{
			*p++ = 0;
			AddMaskAddr(  (DWORD)ntohl(inet_addr( TrimEx(pszAddress) )),  (DWORD)ntohl(inet_addr( TrimEx(p) )) );
		}
		else
			AddNormalAddr( (DWORD)ntohl(inet_addr( TrimEx(pszAddress) )) );
	}
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::AddressIn( const char * pszIpAddress )
{
	THREAD_PROTECT;	//	读取和检测要进行线程保护
	DWORD	dwAddr = (DWORD)ntohl(inet_addr( pszIpAddress ));
	if( AddressInRangeAddr( dwAddr ) )return TRUE;
	if( AddressInNormalAddr( dwAddr ) )return TRUE;
	if( AddressInMaskAddr( dwAddr ) )return TRUE;
	return FALSE;
}
//------------------------------------------------------------------------
//	自动合并重复的范围
BOOL	CIpListEx::AddRangeAddr( DWORD dwStart, DWORD dwEnd )
{
	DWORD	d1 = dwStart, d2 = dwEnd;
	dwStart = min( d1, d2 );
	dwEnd = max( d1, d2 );
	if( dwStart == dwEnd )return AddNormalAddr( dwStart );
	for( DWORD	i = 0;i < this->m_dwRangeAddressCount;i ++ )
	{
		if( dwEnd < this->m_pRangeAddress[i].dwStart )
		{
			memmove( &m_pRangeAddress[i+1], &m_pRangeAddress[i], sizeof( RangeAddress ) * (this->m_dwRangeAddressCount - i) );
			m_pRangeAddress[i].dwStart = dwStart;
			m_pRangeAddress[i].dwEnd = dwEnd;
			this->m_dwRangeAddressCount ++;
			return TRUE;
		}
		else if( dwStart > m_pRangeAddress[i].dwEnd )
		{
			continue;
		}

		if( dwEnd > m_pRangeAddress[i].dwEnd )
			m_pRangeAddress[i].dwEnd = dwEnd;

		if( dwStart < m_pRangeAddress[i].dwStart )
			m_pRangeAddress[i].dwStart = dwStart;
		
		return TRUE;
	}
	this->m_pRangeAddress[this->m_dwRangeAddressCount].dwStart = dwStart;
	this->m_pRangeAddress[this->m_dwRangeAddressCount++].dwEnd = dwEnd;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::AddMaskAddr( DWORD dwAddr, DWORD dwMask )
{
	dwAddr &= dwMask;
	for( DWORD	i = 0;i < this->m_dwMaskAddressCount;i ++ )
	{
		if( this->m_pMaskAddress[i].dwAddr == dwAddr )
		{
			if( (dwMask & this->m_pMaskAddress[i].dwMask) == dwMask )
				return TRUE;
			if( (dwMask & this->m_pMaskAddress[i].dwMask) == this->m_pMaskAddress[i].dwMask )
			{
				m_pMaskAddress[i].dwMask = dwMask;
				return TRUE;
			}
		}
	}
	this->m_pMaskAddress[this->m_dwMaskAddressCount].dwAddr = dwAddr;
	this->m_pMaskAddress[this->m_dwMaskAddressCount++].dwMask = dwMask;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::AddNormalAddr( DWORD dwAddr )
{
	for( DWORD	i = 0;i < this->m_dwNormalAddressCount;i ++ )
	{
		if( dwAddr < this->m_pNormalAddress[i] )
		{
			memmove( &m_pNormalAddress[i+1], &m_pNormalAddress[i], sizeof( DWORD ) * (this->m_dwNormalAddressCount - i) );
			m_pNormalAddress[i] = dwAddr;
			this->m_dwNormalAddressCount ++;
			return TRUE;
		}
		else if( dwAddr == this->m_pNormalAddress[i] )
			return TRUE;
	}
	this->m_pNormalAddress[this->m_dwNormalAddressCount++] = dwAddr;
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::AddressInNormalAddr( DWORD dwAddr )
{
	DWORD	s = 0, m = 0, e = this->m_dwNormalAddressCount;
	while( s < e )
	{
		m = (s+e)/2;
		if( dwAddr == this->m_pNormalAddress[m] )
			return TRUE;
		else if( dwAddr > this->m_pNormalAddress[m] )
		{
			if( s == m )
				return FALSE;
			s = m;
		}
		else
		{
			if( e == m )
				return FALSE;
			e = m;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::AddressInMaskAddr( DWORD dwAddr )
{
	for( DWORD i = 0;i < this->m_dwMaskAddressCount;i ++ )
	{
		if( this->m_pMaskAddress[i].AddrIn( dwAddr ) )return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------------
BOOL	CIpListEx::AddressInRangeAddr( DWORD dwAddr )
{
	DWORD	s = 0, m = 0, e = this->m_dwRangeAddressCount;
	while( s < e )
	{
		m = (s+e)/2;
		if( this->m_pRangeAddress[m].AddrIn( dwAddr ) )
			return TRUE;
		else if( dwAddr > this->m_pRangeAddress[m].dwEnd )
		{
			if( s == m )
				return FALSE;
			s = m;
		}
		else
		{
			if( e == m )
				return FALSE;
			e = m;
		}
	}
	return FALSE;	
}
//------------------------------------------------------------------------