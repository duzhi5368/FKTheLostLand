/**
*	created:		2013-4-19   14:24
*	filename: 		PhysicsMap
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\physicsmap.h"
#include ".\logicmap.h"
#include <stdlib.h>
//------------------------------------------------------------------------
CPhysicsMap::CPhysicsMap(void): m_iWidth(0),m_iHeight(0),m_pBlockLayer(NULL),m_iMaxBlockElements(0)
{
	m_szMapName[0] = 0;
}
//------------------------------------------------------------------------
CPhysicsMap::~CPhysicsMap(void)
{
}
//------------------------------------------------------------------------
BOOL	CPhysicsMap::LoadMap( const char * pszFilename )
{
	_splitpath( pszFilename, NULL, NULL, m_szMapName, NULL );
	FILE * fp = fopen( pszFilename, "rb" );
	if( fp == NULL )return FALSE;
	DWORD	dwTemp;
	fread( &dwTemp, 4, 1, fp );
	fread( &m_iWidth, 4, 1, fp );
	fread( &m_iWidth, 4, 1, fp );
	fread( &m_iHeight, 4, 1, fp );
	//	make up block layer
	int f = m_iWidth*m_iHeight;

	m_iMaxBlockElements = (f + 31)/32;
	m_pBlockLayer = new DWORD[m_iMaxBlockElements];
	ZeroMemory( m_pBlockLayer, sizeof( DWORD ) * m_iMaxBlockElements );

	fseek( fp, (long)dwTemp, SEEK_SET );

	BYTE flag;
	int	elemindex = 0,bitindex = 0;
	while( f-- )
	{
		fread( &flag, 1, 1, fp );
		if( flag & 1 )
			m_pBlockLayer[elemindex] |= (1<<bitindex);
		if( flag & 2 )
			fread( &dwTemp, 2, 1, fp );
		if( flag & 4 )
			fread( &dwTemp, 2, 1, fp );
		if( flag & 8 )
			fread( &dwTemp, 4, 1, fp );
		if( flag & 16 )
			fread( &dwTemp, 1, 1, fp );
		if( flag & 32 )
			fread( &flag, 1, 1, fp );
		if( flag & 64 )
			fread( &flag, 1, 1, fp );
		if( flag & 128 )
			fread( &flag, 1, 1, fp );
		bitindex++;
		if( bitindex >= 32 )
		{
			bitindex = 0,elemindex ++;
			if( elemindex >= m_iMaxBlockElements )
				break;
		}
	}
	fclose( fp );
	q_strupper( m_szMapName );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CPhysicsMap::LoadCache( const char * pszCacheFilename )
{
	_splitpath( pszCacheFilename, NULL, NULL, m_szMapName, NULL );
	FILE * fp = fopen( pszCacheFilename, "rb" );
	if( fp == NULL )return FALSE;
	DWORD	dwTemp = 0;
	fread( &dwTemp, 4, 1, fp );
	if( dwTemp != *(DWORD*)"DMC0" )return FALSE;
	fread( &this->m_iWidth, sizeof( int ), 1, fp );
	fread( &this->m_iHeight, sizeof( int ), 1, fp );
	fread( &this->m_iMaxBlockElements, sizeof( int ), 1, fp );
	int f = (m_iWidth*m_iHeight + 31 ) / 32;
	if( m_iMaxBlockElements < f )m_iMaxBlockElements = f;
	m_pBlockLayer = new DWORD[m_iMaxBlockElements];
	ZeroMemory( m_pBlockLayer, sizeof( DWORD ) * m_iMaxBlockElements );
	fread( m_pBlockLayer, sizeof( DWORD ), m_iMaxBlockElements, fp );
	fclose( fp );
	q_strupper( m_szMapName );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CPhysicsMap::SaveCache( const char * pszPath )
{
	char	szFilename[256];
	_makepath( szFilename, NULL, pszPath, m_szMapName, ".PMC" );
	FILE * fp = fopen( szFilename, "wb" );
	if( fp == NULL )return FALSE;
	fwrite( (void*)"DMC0", 4, 1, fp );
	fwrite( &m_iWidth, sizeof( int ), 1, fp );
	fwrite( &m_iHeight, sizeof( int ), 1, fp );
	fwrite( &m_iMaxBlockElements, sizeof( int ), 1, fp );
	int f = (m_iWidth * m_iHeight + 31 ) / 32;
	if( m_iMaxBlockElements > f )f = m_iMaxBlockElements;
	fwrite( (void*)m_pBlockLayer, sizeof( DWORD ), f, fp );
	fclose( fp );
	return TRUE;
}
//------------------------------------------------------------------------
BOOL	CPhysicsMap::IsBlocked( int x, int y )
{
	//	坐标非法，返回阻挡
	if( !VerifyPos(x,y))return TRUE;
	//	阻挡信息为空，返回无阻挡
	if( m_pBlockLayer == NULL )return FALSE;
	int f = y * m_iWidth + x;
	x = f / 32;
	y = f % 32;
	return ((m_pBlockLayer[x] & (1<<y)) != 0);
}
//------------------------------------------------------------------------