/**
*	created:		2013-5-10   6:01
*	filename: 		FKClientLink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/Network/FKMEncrypter.h"
#include "../../Include/Network/FKClientLink.h"
//------------------------------------------------------------------------
#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif
//------------------------------------------------------------------------
extern "C" IClientLink* CreateClientLink(DWORD dwSocketID,IClientLinkSink* pSink,ITrace* pTrace,IClientSocket* pClientSocket,void* pOption)
{
	CClientLink * p = new CClientLink();
	if(p == NULL)
		return NULL;
	if(!p->Create(dwSocketID,pSink,pClientSocket,pTrace) )
	{
		delete p;
		return NULL;
	}
	return static_cast<IClientLink*>(p);
}
//------------------------------------------------------------------------
IClientLink* CClientLinkHelper::MyCreateClientLink(DWORD dwVersion,DWORD dwSocketID,IClientLinkSink* pSink,ITrace* pTrace,IClientSocket* pClientSocket,void* pOption)
{
	if(dwVersion > VERSION_CLIENTLINK)
	{
		wchar_t buf[1024];
		wsprintf(buf,L"Error : dllCreateClientLink() : version mismatch,%d wanted,but %d is requested\r\n",VERSION_CLIENTLINK,dwVersion);
		OutputDebugString(buf);
		return FALSE;
	}
	return CreateClientLink(dwSocketID,pSink,pTrace,pClientSocket,pOption);
}
//------------------------------------------------------------------------
// 设置接收数据的解密策略
void CClientLink::SelEncrypt_Rcv( IStreamEncrypt * pStrategy )
{
	if( m_pEncryptRcv )
	{
		m_pEncryptRcv->Release();
		m_pEncryptRcv = NULL;
	}

	m_pEncryptRcv = pStrategy;
}
//------------------------------------------------------------------------
// 设置发送数据的加密策略
void CClientLink::SelEncrypt_Snd( IStreamEncrypt * pStrategy )
{
	if( m_pEncryptSnd )
	{
		m_pEncryptSnd->Release();
		m_pEncryptSnd = NULL;
	}

	m_pEncryptSnd = pStrategy;
}
//------------------------------------------------------------------------
// 设置加密策略
BOOL CClientLink::SetEncryptStrategy()
{
	static BOOL s_seted_key = FALSE;

	// 指定加密算法
	IStreamEncrypt * pStrategy = new MEncrypter;
	if( pStrategy == NULL )
		return FALSE;

	// 设置密锁
	if( !s_seted_key )
	{
		s_seted_key = TRUE;
		MEncrypter::DES_KEY	des_key = 0x0621906902715035; // 可修改
		pStrategy->SetKey( (const unsigned char *)&des_key ,  sizeof(des_key) );
	}

	SelEncrypt_Snd( pStrategy );

	// 指定解密算法
	IStreamEncrypt * pStrategy2 = new CStreamEncrypter( FALSE );
	if( pStrategy == NULL )
		return FALSE;

	// 设置密锁
	CStreamEncrypter::KEY	key;
	key.mFlag[0] = 38;  // 可修改
	key.mFlag[1] = 95;  // 可修改
	key.mFlag[2] = 13;  // 可修改
	key.mFlag[3] = 49;  // 可修改
	pStrategy2->SetKey( (const unsigned char *)&key , sizeof( CStreamEncrypter::KEY ) );

	SelEncrypt_Rcv( pStrategy2 );
	return TRUE;
}
//------------------------------------------------------------------------