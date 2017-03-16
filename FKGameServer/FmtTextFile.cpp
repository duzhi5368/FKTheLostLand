/**
*	created:		2013-4-18   23:19
*	filename: 		FmtTextFile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\fmttextfile.h"
//------------------------------------------------------------------------
CFmtTextFile::~CFmtTextFile(void)
{

}
//------------------------------------------------------------------------
CFmtTextFile::CFmtTextFile( const char * pszStruct, const char * pszFile, BOOL bCSV )
{
	int	sptr = 0;
	char szNumber[200];
	int	nptr = 0;
	int	eptr = 0;
	m_iStructElements = 0;
	m_iMaxParams = 0;

	fmt_struct_element * pTail = NULL;
	m_pStructDesc = NULL;

	while ( pszStruct[sptr] )
	{
		char dtype = tolower(pszStruct[sptr++]);

		nptr = 0;
		while( pszStruct[sptr] >= '0' && pszStruct[sptr] <= '9' )
		{
			szNumber[nptr++] = pszStruct[sptr++];
		}
		szNumber[nptr] = 0;
		fmt_type type;

		switch( dtype )
		{
		case	's':
			type = FT_STRING;
			break;
		case	'b':
			type = FT_BYTE;
			break;
		case	'w':
			type = FT_WORD;
			break;
		case	'd':
			type = FT_DWORD;
			break;
		default:
			continue;
		}
		if( pTail == NULL )
		{
			m_pStructDesc = new fmt_struct_element;
			pTail = m_pStructDesc;
		}
		else
		{
			pTail->pNext = new fmt_struct_element;
			pTail = pTail->pNext;
		}
		pTail->wType = (WORD)type;
		pTail->wLength = StringToInteger(szNumber);
		if( pTail->wLength == 0 )pTail->wLength = 1;
		if( type != FT_STRING )
			m_iMaxParams += pTail->wLength;
		else
			m_iMaxParams += 1;
		m_iStructElements ++;
	}

	Params = new char*[m_iMaxParams];
	m_bLoaded = Load( pszFile , bCSV );
}
//------------------------------------------------------------------------
BOOL CFmtTextFile::Load( const char * pszFile, BOOL bCSV )
{
	if( pszFile == NULL )return FALSE;
	m_sfFile.Destroy();
	if( !m_sfFile.LoadFile(pszFile) )return FALSE;
	m_bCSV = bCSV;
	m_bLoaded = TRUE;
	return TRUE;
}
//------------------------------------------------------------------------
static char g_szFmtTempLine[4096];
//------------------------------------------------------------------------
BOOL	CFmtTextFile::GetStruct( int line, LPVOID lpStruct )
{
	if( !m_bLoaded )return FALSE;
	char * p = (char*)lpStruct;
	int ptr = 0;
	int eptr = 0;
	if( line >= m_sfFile.GetLineCount()  )return FALSE;
	if( *m_sfFile[line] == '#' )return FALSE;
	o_strncpy(g_szFmtTempLine, m_sfFile[line], 4095 );
	nParam = SearchParam( g_szFmtTempLine, Params, m_iMaxParams, (m_bCSV?',':'/') );
	int bytewidth = 0;
	if( nParam != m_iMaxParams )
	{
		return FALSE;
	}

	int pptr = 0;
	fmt_struct_element *pStructElement = m_pStructDesc;
	fmt_struct_element *pCurElement = NULL;
	while( pStructElement )
	{
		pCurElement = pStructElement;
		pStructElement = pStructElement->pNext;
		switch( pCurElement->wType )
		{
		case	FT_STRING:
			strncpy( p+ptr, Params[pptr++], pCurElement->wLength );
			ptr += pCurElement->wLength;
			continue;
		case	FT_BYTE:
			bytewidth = 1;
			break;
		case	FT_WORD:
			bytewidth = 2;
			break;
		case	FT_DWORD:
			bytewidth = 4;
			break;
		default:
			continue;
		}
		for( int j = 0;j <pCurElement->wLength;j ++ )
		{
			if( pptr >= m_iMaxParams )return FALSE;
			int t = StringToInteger( Params[pptr++]);
			memcpy( p+ptr, &t, bytewidth);
			ptr+= bytewidth;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------------