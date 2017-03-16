/**
*	created:		2013-5-10   2:18
*	filename: 		FKStreamEncrypt
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		流式数据的加密
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <winsock2.h>
//------------------------------------------------------------------------
struct IStreamEncrypt
{
	// 设置密钥
	// pKey		:	密钥内容
	// nLen		:	密钥长度
	virtual BOOL SetKey( const unsigned char * pKey , int nLen ) = 0;

	// 加密一段字符串
	// inBuffer :   传入明文 /*IN*/
	// outBuffer:   输出密文 /*OUT*/
	// inLen	:   明文长度 /*IN*/
	// outLen	:	密文长度 /*IN/OUT*/
	virtual BOOL Encrypt( const unsigned char * inBuffer , 
		unsigned char * outBuffer , 
		int inLen , 
		int & outLen ) = 0;

	// 解密一段字符串
	// inBuffer :   传入密文 /*IN*/
	// outBuffer:   输出明文 /*OUT*/
	// inLen	:   密文长度 /*IN*/
	// outLen	:	明文长度 /*IN/OUT*/
	virtual BOOL Decrypt( const unsigned char * inBuffer , 
		unsigned char * outBuffer , 
		int inLen , 
		int & outLen ) = 0;

	// 清除
	virtual void Clear() = 0;

	// 销毁
	virtual void Release() = NULL;
};
//------------------------------------------------------------------------