/**
*	created:		2013-4-14   20:43
*	filename: 		BanIpListEx
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		禁止IP列表
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
//	1- IP范围支持
//	2- 掩码支持
//	3- 单个IP支持
//	4- 支持重新读取
//	5- 多线程支持
typedef struct tagRangeAddress
{
	DWORD	dwStart;
	DWORD	dwEnd;
	BOOL	AddrIn( DWORD dwAddr1 )
	{
		return ((dwAddr1 >= dwStart ) && (dwAddr1 <= dwEnd));
	}
}RangeAddress;
//------------------------------------------------------------------------
typedef struct tagMaskAddress
{
	DWORD	dwAddr;
	DWORD	dwMask;
	BOOL	AddrIn( DWORD dwAddr1 )
	{
		return ((dwAddr1)&dwMask) == dwAddr;
	}
}MaskAddress;
//------------------------------------------------------------------------
class CIpListEx
{
public:
	CIpListEx(void);
	virtual ~CIpListEx(void);
	BOOL	Load( const char * pszFilename );
	BOOL AddressIn( const char * pszIpAddress );

	BOOL	IsEmpty()
	{
		return ((m_pNormalAddress == NULL ) &&
					( m_pRangeAddress == NULL ) &&
					( m_pMaskAddress == NULL ) );
	}
protected:

	BOOL	AddRangeAddr( DWORD dwStart, DWORD dwEnd );
	BOOL	AddMaskAddr( DWORD dwAddr, DWORD dwMask );
	BOOL	AddNormalAddr( DWORD dwAddr );
	BOOL	AddressInNormalAddr( DWORD dwAddr );
	BOOL	AddressInMaskAddr( DWORD dwAddr );
	BOOL	AddressInRangeAddr( DWORD dwAddr );

	THREAD_PROTECT_DEFINE;
	DWORD	*	m_pNormalAddress;
	DWORD	m_dwNormalAddressCount;
	RangeAddress * m_pRangeAddress;
	DWORD	m_dwRangeAddressCount;
	MaskAddress * m_pMaskAddress;
	DWORD	m_dwMaskAddressCount;
};
//------------------------------------------------------------------------