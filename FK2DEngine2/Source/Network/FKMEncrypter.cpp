/**
*	created:		2013-5-10   5:55
*	filename: 		FKMEncrypter
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		流数据加密类
*	Dese:			实现每次发包都用一个新的密钥
*					数据流的格式是:
*					0  …… 31 bits  密钥
*					32 …… 47 bits  随机标识或做CRC校验
*					48 …… 63 bits  数据长度 这段数据用前面的密钥加密
*/
//------------------------------------------------------------------------
#include "../../Include/Network/FKMEncrypter.h"
//------------------------------------------------------------------------
CStreamEncrypter MEncrypter::m_StreamEncrypter;
unsigned long	 MEncrypter::m_DesKey[256];
BOOL MEncrypter::ENABLE_CRC_CHECK = TRUE;
//------------------------------------------------------------------------
MEncrypter::MEncrypter() : m_byLastSendFlag( 0 )
{
	memset( &m_LastStreamKey , 0 , sizeof( m_LastStreamKey ) );
}
//------------------------------------------------------------------------
MEncrypter::~MEncrypter()
{
}
//------------------------------------------------------------------------
// 设置密钥
// pKey		:	密钥内容
// nLen		:	密钥长度
BOOL MEncrypter::SetKey( const unsigned char * pKey , int nLen )
{
	des_ky( (void *)pKey , (void *)&m_DesKey[0] );
	return TRUE;
}
//------------------------------------------------------------------------
// 加密一段字符串
// inBuffer :   传入明文 /*IN*/
// outBuffer:   输出密文 /*OUT*/
// inLen	:   明文长度 /*IN*/
// outLen	:	密文长度 /*IN/OUT*/
BOOL MEncrypter::Encrypt( const unsigned char * inBuffer , 
						 unsigned char * outBuffer , 
						 int inLen , 
						 int & outLen )
{
	// 随机生成密码
	STREAM_KEY	tempKey;
	srand( GetTickCount() );
	tempKey.key.mFlag[0] = rand()%256;
	tempKey.key.mFlag[1] = rand()%256;
	tempKey.key.mFlag[2] = rand()%256;
	tempKey.key.mFlag[3] = rand()%256;

	tempKey.wLen = inLen;

	if( m_byLastSendFlag == 255 )
		m_byLastSendFlag = 0;
	else
		m_byLastSendFlag ++;

	tempKey.byFlag = m_byLastSendFlag;

	// 循环校验
	if( ENABLE_CRC_CHECK )
	{
		tempKey.byCrc = CalculateCRC( inBuffer , inLen );
	}

	STREAM_KEY	Key;
	des_ec( (const void *)&tempKey, (void *)&Key,  (void *)&m_DesKey[0] );

	if( outLen < sizeof( STREAM_KEY ) )
		return FALSE;

	memcpy( outBuffer , &Key , sizeof( STREAM_KEY ) );
	outBuffer += sizeof( STREAM_KEY );
	int tempLen = outLen - sizeof( STREAM_KEY );
	m_StreamEncrypter.SetKey( (const unsigned char *)&tempKey.key , sizeof(tempKey.key) ); 
	if( !m_StreamEncrypter.Encrypt( inBuffer , outBuffer , inLen , tempLen ) )
		return FALSE;

	outLen = tempLen + sizeof( STREAM_KEY );
	return TRUE;
}
//------------------------------------------------------------------------
// 解密一段字符串
// inBuffer :   传入密文 /*IN*/
// outBuffer:   输出明文 /*OUT*/
// inLen	:   密文长度 /*IN*/
// outLen	:	明文长度 /*IN/OUT*/
BOOL MEncrypter::Decrypt( const unsigned char * inBuffer , 
						 unsigned char * outBuffer , 
						 int inLen , 
						 int & outLen )
{
	if( inLen < sizeof( m_LastStreamKey ) )
		return FALSE;

	STREAM_KEY	tempKey;
	des_dc( (const void *)inBuffer , (void *)&tempKey , (void *)&m_DesKey[0] );

	// 长度校验
	int nDataLen = tempKey.wLen + sizeof( STREAM_KEY );
	if( inLen < nDataLen || nDataLen > nDataLen + 4 )
		return FALSE;

	// 次数必须递增
	if( tempKey.byFlag == 0 )
	{
		if( m_LastStreamKey.byFlag != 255 )
			return FALSE;
	}else
	{
		if( tempKey.byFlag - m_LastStreamKey.byFlag != 1 )
			return FALSE;
	}

	// 解密
	inBuffer += sizeof( STREAM_KEY );
	inLen -= sizeof( STREAM_KEY );
	m_StreamEncrypter.SetKey( (const unsigned char * )&tempKey.key , sizeof(tempKey.key) ); 
	if( !m_StreamEncrypter.Decrypt( inBuffer , outBuffer , inLen , outLen ) )
		return FALSE;

	// 循环校验
	if( ENABLE_CRC_CHECK )
	{
		if( CalculateCRC( outBuffer , tempKey.wLen ) != tempKey.byCrc )
			return FALSE;
	}

	outLen = tempKey.wLen;
	m_LastStreamKey = tempKey;
	return TRUE;
}
//------------------------------------------------------------------------
// 计算某段数据的CRC码
BYTE MEncrypter::CalculateCRC( const unsigned char * buf , int nLen )
{
	unsigned long ltemp = 0;
	for( int i = 0 ; i <= nLen - 4 ; i += 4 )
	{
		ltemp += *((unsigned long *)&buf[i]);
	}

	return (BYTE)ltemp;
}
//------------------------------------------------------------------------