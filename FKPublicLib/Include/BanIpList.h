/**
*	created:		2013-4-14   20:41
*	filename: 		BanIpList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		禁止IP列表
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <windows.h>
//------------------------------------------------------------------------
// 禁止IP列表
class CBanIpList
{
public:
	CBanIpList(void);
	virtual ~CBanIpList(void);
	VOID	LoadBanIpList( const char * pszBanIpList );
	VOID	AddAddr( const char * pszIpAddr );
	BOOL	InBanList( const char * pszIpAddr );
protected:
	DWORD	AddrToUL( const char * pszIpAddr );
	DWORD	* m_pAddrArray;
	DWORD	m_dwAddrCount;
};
//------------------------------------------------------------------------