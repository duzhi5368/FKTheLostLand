/**
*	created:		2013-5-10   5:45
*	filename: 		FKCStreamEncrypt
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		根据密钥表示的移位规则把一段数据循环移位最后异或
*/
//------------------------------------------------------------------------
#include "../../Include/Network/FKCStreamEncrypt.h"
//------------------------------------------------------------------------
// 设置密钥
// pKey		:	密钥内容
// nLen		:	密钥长度
BOOL CStreamEncrypter::SetKey( const unsigned char * pKey , int nLen )
{
	if( nLen != sizeof( m_key ) )
		return FALSE;

	memcpy( m_key.mFlag , pKey , nLen );
	return TRUE;
}
//------------------------------------------------------------------------
// 加密一段字符串
// inBuffer :   传入明文 /*IN*/
// outBuffer:   输出密文 /*OUT*/
// inLen	:   明文长度 /*IN*/
// outLen	:	密文长度 /*OUT*/
BOOL CStreamEncrypter::Encrypt( const unsigned char * inBuffer , 
							   unsigned char * outBuffer , 
							   int inLen , 
							   int & outLen )
{
	if( outLen < inLen )
		return FALSE;

	int nFlag = 0 , i = 0;
	register unsigned long lValue= m_key.lValue;
	for( i = 0 ; i <= inLen - 4 ; i += 4 )
	{
		register unsigned char cTemp = m_key.mFlag[ nFlag ];

		__asm 
		{
			mov edx , inBuffer 
				mov eax , [edx]
			mov cl  , cTemp
				ror eax , cl
				xor eax , lValue
				mov edx , outBuffer
				mov [edx] , eax
		}

		nFlag ++;
		nFlag %= 4;

		inBuffer += 4;
		outBuffer += 4;
	}

	if( i < inLen )
	{
		if( ROUND_UP_4BYTES )
		{
			// 不足4字节补齐
			unsigned long lTemp = 0;
			memcpy( &lTemp , &inBuffer[i] , inLen - i );

			i+= 4;
			if( outLen < i )
				return FALSE;

			register unsigned char cTemp = m_key.mFlag[ nFlag ];

			__asm 
			{
				mov edx , inBuffer 
					mov eax , [edx]
				mov cl  , cTemp
					ror eax , cl
					xor eax , lValue
					mov edx , outBuffer
					mov [edx] , eax
			}
		}else
		{
			// 不圆整就1字节移位异或
			for( int j = i ; j < inLen ; j ++ )
			{
				register unsigned char cTemp = m_key.mFlag[ j-i ];
				__asm 
				{
					mov edx , inBuffer
						mov al , [edx]
					mov cl  , cTemp
						ror al , cl
						xor al , cTemp
						mov edx , outBuffer
						mov [edx] , al
				}

				++inBuffer;
				++outBuffer;
			}

			i = inLen;
		}
	}

	outLen = i;
	return TRUE;
}
//------------------------------------------------------------------------
// 解密一段字符串
// inBuffer :   传入密文 /*IN*/
// outBuffer:   输出明文 /*OUT*/
// inLen	:   密文长度 /*IN*/
// outLen	:	明文长度 /*OUT*/
BOOL CStreamEncrypter::Decrypt( const unsigned char * inBuffer , 
							   unsigned char * outBuffer , 
							   int inLen , 
							   int & outLen )
{
	if( outLen < inLen )
		return FALSE;

	int nFlag = 0;
	register unsigned long lValue= m_key.lValue;
	int i = 0;
	for( ; i <= inLen - 4 ; i += 4 )
	{
		register unsigned char cTemp = m_key.mFlag[ nFlag ];

		__asm 
		{
			mov edx , inBuffer
				mov eax , [edx]
			xor eax , lValue
				mov cl  , cTemp
				rol eax , cl
				mov edx , outBuffer
				mov [edx] , eax
		}

		outBuffer += 4;
		inBuffer  += 4;
		nFlag ++;
		nFlag %= 4;
	}

	if( i != inLen )
	{
		if( ROUND_UP_4BYTES )
			return FALSE;
		else
		{
			// 不圆整就1字节移位异或
			for( int j = i ; j < inLen ; j ++ )
			{
				register unsigned char cTemp = m_key.mFlag[ j-i ];
				__asm 
				{
						mov edx , inBuffer
						mov al , [edx]
						mov cl  ,cTemp
						xor al , cl
						rol al , cl
						mov edx , outBuffer
						mov [edx] , al
				}

				++inBuffer;
				++outBuffer;
			}
		}
	}

	outLen = inLen;
	return TRUE;
}
//------------------------------------------------------------------------