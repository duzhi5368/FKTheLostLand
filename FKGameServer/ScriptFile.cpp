/**
*	created:		2013-4-19   9:33
*	filename: 		ScriptFile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptfile.h"
//------------------------------------------------------------------------
CScriptFile::CScriptFile(void)
{
	m_nLineIndex = 0;
	m_pData = NULL;
}
//------------------------------------------------------------------------
CScriptFile::~CScriptFile(void)
{
	if( m_pData )
		delete []m_pData;
	m_fScript.Destroy();
}
//------------------------------------------------------------------------
BOOL	CScriptFile::Load( const char * pszFileName )
{
	o_strncpy( m_szFileName, pszFileName, 1020 );
	return ProtectedLoad();
}
//------------------------------------------------------------------------
VOID	CScriptFile::Close()
{
	m_nLineIndex = 0;
	m_fScript.Destroy();
}
//------------------------------------------------------------------------
char * CScriptFile::FirstLine()
{
	this->m_nLineIndex = 0;
	return CurrentLine();
}
//------------------------------------------------------------------------
char * CScriptFile::NextLine()
{
	this->m_nLineIndex ++;
	return CurrentLine();
}
//------------------------------------------------------------------------
char * CScriptFile::PrevLine()
{
	if( m_nLineIndex > 0 )
		m_nLineIndex --;
	return CurrentLine();
}
//------------------------------------------------------------------------
char * CScriptFile::CurrentLine()
{
	char * p = m_fScript[m_nLineIndex];
	if( p )
	{
		char * pl = strchr( p, ';' );
		if( pl )*pl = 0;
		return TrimEx( p );
	}
	return NULL;
}
//------------------------------------------------------------------------
UINT	CScriptFile::GetCurrentLineNumber()
{
	return m_nLineIndex;
}
//------------------------------------------------------------------------
// º”√‹∑Ω Ω
enum	e_encypttype
{
	ET_NONE, 
	ET_KEYFILE,
	ET_PASSWORD,
	ET_DEFAULTMASK,
};
//------------------------------------------------------------------------
typedef struct tagEncyptHeader
{
	DWORD	dwMagic;
	char	szAuthor[64];
	char	szDesc[256];
	char	szLisence[256];
	char	szKeyDesc[64];
	DWORD	dwEncyptType;
	DWORD	dwEncyptFlag;
	DWORD	dwDataSize;
	BYTE	btKeyCrc[256];
}EncyptHeader;
//------------------------------------------------------------------------
BYTE	g_btKeyBuffer[1024];
BYTE	g_btKeyCrc[256];
//------------------------------------------------------------------------
VOID	MakeDefaultKeyBuffer()
{
	memset( (void*)g_btKeyCrc, 0, sizeof( g_btKeyCrc ) );
	memset( (void*)g_btKeyBuffer, 0x88, sizeof( g_btKeyBuffer ) );
	int size = 0;
}
//------------------------------------------------------------------------
BOOL	CScriptFile::ProtectedLoad()
{
	int iDataSize = 0;
	m_pData = LoadFile( m_szFileName, iDataSize );
	if( m_pData == NULL )return FALSE;
	BYTE * pData = m_pData;
	if( *(DWORD*)m_pData == *(DWORD*)"DMC0" )
	{
		EncyptHeader * pHeader = (EncyptHeader*)m_pData;
		pData = m_pData + sizeof( EncyptHeader );
		if( iDataSize < (int)(pHeader->dwDataSize + sizeof( EncyptHeader ) ) )
		{
			delete []m_pData;
			return FALSE;
		}

		switch( pHeader->dwEncyptType )
		{
		case ET_NONE:
			{

			}
			break;
		case ET_KEYFILE:
			break;
		case ET_PASSWORD:
			break;
		case ET_DEFAULTMASK:
			{
				MakeDefaultKeyBuffer();
				if( memcmp( (void*)g_btKeyCrc, (void*)pHeader->btKeyCrc, sizeof( pHeader->btKeyCrc ) ) != 0 )
				{
					delete []m_pData;
					return FALSE;
				}
				for( int i = 0;i < (int)pHeader->dwDataSize;i ++ )
				{
					pData[i] ^= g_btKeyBuffer[i%1024];	
				}
			}
			break;
		default:
			delete []m_pData;
			return FALSE;
		}
		iDataSize = pHeader->dwDataSize;
	}
	return m_fScript.SetData( (char*)pData, iDataSize );
}
//------------------------------------------------------------------------