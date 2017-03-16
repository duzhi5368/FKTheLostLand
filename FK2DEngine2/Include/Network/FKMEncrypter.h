/**
*	created:		2013-5-10   5:48
*	filename: 		FKMEncrypter
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKStreamEncrypt.h"
#include "FKCStreamEncrypt.h"
#include "Des.h"
//------------------------------------------------------------------------
// 循环校验开关
// #define  ENABLE_CRC_CHECK	TRUE
//------------------------------------------------------------------------
class MEncrypter : public IStreamEncrypt
{
public:
	// 设置密钥
	// pKey		:	密钥内容
	// nLen		:	密钥长度
	BOOL SetKey( const unsigned char * pKey , int nLen );

	// 加密一段字符串
	// inBuffer :   传入明文 /*IN*/
	// outBuffer:   输出密文 /*OUT*/
	// inLen	:   明文长度 /*IN*/
	// outLen	:	密文长度 /*IN/OUT*/
	BOOL Encrypt( const unsigned char * inBuffer , 
		unsigned char * outBuffer , 
		int inLen , 
		int & outLen );

	// 解密一段字符串
	// inBuffer :   传入密文 /*IN*/
	// outBuffer:   输出明文 /*OUT*/
	// inLen	:   密文长度 /*IN*/
	// outLen	:	明文长度 /*IN/OUT*/
	BOOL Decrypt( const unsigned char * inBuffer , 
		unsigned char * outBuffer , 
		int inLen , 
		int & outLen );

	void Clear(){ m_byLastSendFlag = 0; }
	void Release(){	delete this; }

	static void EnableCRC( BOOL bFlag )
	{
		ENABLE_CRC_CHECK = bFlag;
	}

	MEncrypter();
	virtual ~MEncrypter();

private:
	// 计算某段数据的CRC码
	BYTE CalculateCRC( const unsigned char * buf , int nLen );

public:
	struct STREAM_KEY
	{
		CStreamEncrypter::KEY	key;		// 密钥
		BYTE					byCrc;		// 循环校验码
		BYTE					byFlag;		// 递增标识
		WORD					wLen;		// 流数据长度
	};

	typedef  unsigned __int64	DES_KEY;

private:
	static CStreamEncrypter  m_StreamEncrypter;
	static unsigned long	 m_DesKey[256];
	static BOOL				 ENABLE_CRC_CHECK;

	STREAM_KEY		 m_LastStreamKey;
	BYTE			 m_byLastSendFlag;
};
//------------------------------------------------------------------------