/**
*	created:		2013-5-10   5:44
*	filename: 		FKCStreamEncrypt
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		根据密钥表示的移位规则把一段数据循环移位最后异或
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKStreamEncrypt.h"
//------------------------------------------------------------------------
class CStreamEncrypter :public IStreamEncrypt
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

	void Clear() {}
	void Release(){	delete this; }

	CStreamEncrypter() : ROUND_UP_4BYTES( TRUE )
	{
		m_key.lValue = 0;
	}

	// bRndup : 是否圆整成4字节的倍数
	CStreamEncrypter( BOOL bRndup ) : ROUND_UP_4BYTES( bRndup )
	{
		m_key.lValue = 0;
	}

	virtual ~CStreamEncrypter()
	{
	}

public:
	union KEY
	{
		unsigned char	mFlag[4];
		unsigned long   lValue;
	};

	KEY		m_key;
	// 是否圆整成4字节
	BOOL	ROUND_UP_4BYTES;
};
//------------------------------------------------------------------------