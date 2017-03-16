/**
*	created:		2013-4-16   4:37
*	filename: 		xExtractString
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class xCharSet
{
public:
	xCharSet()
	{
		clear();
	}

	xCharSet( const char * pszTable )
	{
		clear();
		for(int i = 0;i < (int)strlen( pszTable );i ++ )
			addChar( pszTable[i] );
	}

	xCharSet( DWORD dwFlags[] )
	{
		for( int i = 0;i < 8;i ++ )
		{
			m_dwFlags[i] = dwFlags[i];
		}
	}

	~xCharSet()
	{
	}

	BOOL	charIn( char c )
	{
		BYTE	bc = (BYTE)c;
		int index = bc >> 5;
		int ptr = bc & 31;
		if( m_dwFlags[index] & (1<<ptr) )
			return TRUE;
		return FALSE;
	}

	VOID addChar( char c )
	{
		BYTE	bc = (BYTE)c;
		int index = bc >> 5;
		int ptr = bc & 31;
		m_dwFlags[index] |= 1<<ptr;
	}

	VOID clear()
	{
		memset( m_dwFlags, 0, sizeof( m_dwFlags ) );
	}

	xCharSet & operator +( xCharSet & charset )
	{
		DWORD dwFlags[8];
		for( int i = 0;i < 8;i ++ )
		{
			dwFlags[i] = m_dwFlags[i] | charset.m_dwFlags[i];
		}
		xCharSet tmp = xCharSet( dwFlags );
		return tmp;
	}

	xCharSet & operator +=( xCharSet & charset )
	{
		for( int i = 0;i < 8;i ++ )
		{
			m_dwFlags[i] |= charset.m_dwFlags[i];
		}
		return (*this);
	}

	xCharSet & operator =( xCharSet & charset )
	{
		for( int i = 0;i < 8;i ++ )
		{
			m_dwFlags[i] = charset.m_dwFlags[i];
		}
		return (*this);
	}
protected:
	DWORD	m_dwFlags[8];
};
//------------------------------------------------------------------------
static xCharSet CharSetWhite( " \t" );
static xCharSet CharSetCR( "\r\n" );
static xCharSet CharSetLowerCharacter( "abcdefghijklmnopqrstuvwxyz" );
static xCharSet CharSetUpperCharacter( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
static xCharSet CharSetDigit( "0123456789" );
static xCharSet CharSetOperator( "+-*/\\()[]{}\";'<>,.?!~`#$%^&|_=" );
//------------------------------------------------------------------------
static char * TrimEx( char * pszString, xCharSet & whiteset = CharSetWhite )
{
	while( *pszString && whiteset.charIn( *pszString ) )
		pszString ++;
	if( pszString[0] == 0 )return pszString;
	char * pWhite = NULL;
	int ptr = 0;
	while( *(pszString+ptr) )
	{
		if( whiteset.charIn( *(pszString+ptr) ) )
		{
			if( pWhite == NULL )pWhite = pszString+ptr;
		}
		else
			pWhite = NULL;
		ptr++;
	}
	if( pWhite )*pWhite = 0;
	return pszString;
}
//------------------------------------------------------------------------
inline int ExtractStrings( char * pszString, xCharSet & whiteset, xCharSet & delimset, char ** Params, int iArraySize, BOOL bKeepEmpty = TRUE, BOOL bKeepString = TRUE )
{
	int ptr = 0;
	int nStringCount = 0;
	char * pStart = pszString;
	char	cTemp = 0;
	BOOL	bKeep = FALSE;

	while( *(pszString+ptr) )
	{
		if( bKeepString && *(pszString +ptr) == '\"' )
			bKeep = !bKeep;
		
		if( !bKeep && delimset.charIn( *(pszString+ptr) ) )
		{
			*(pszString+ptr) = 0;
			pStart = TrimEx( pStart, whiteset );
			if( pStart[0] != 0 || bKeepEmpty )
			{
				Params[nStringCount++] = pStart;
				if( nStringCount >= iArraySize )
					return nStringCount;
			}
			pStart = pszString+ptr+1;
		}
		ptr++;
	}
	if( *pStart != 0 || nStringCount > 0 )
	{
		pStart = TrimEx( pStart, whiteset );
		if( pStart[0] != 0 || bKeepEmpty )
		{
			Params[nStringCount++] = pStart;
		}
	}
	return nStringCount;
}
//------------------------------------------------------------------------
template <UINT MaxCount>
class xStringsExtracter
{
public:
	xStringsExtracter()
	{
		clear();
	}

	xStringsExtracter( char * pszString, int delim)
	{
		ExtractString( pszString, delim );
	}

	xStringsExtracter( char * pszString, const char * pszDelimTable = "/", const char * pszWhiteTable = " \t", BOOL	bKeepEmpty = TRUE, BOOL bKeepString = TRUE  )
	{
		ExtractString( pszString, pszDelimTable, pszWhiteTable, bKeepEmpty, bKeepString );
	}

	VOID ExtractString( char * pszString, const char * pszDelimTable = "/", const char * pszWhiteTable = " \t", BOOL	bKeepEmpty = TRUE, BOOL bKeepString = TRUE  )
	{
		clear();
		m_nStringCount = (UINT)ExtractStrings( pszString, xCharSet( pszWhiteTable), xCharSet( pszDelimTable ), m_pStrings, MaxCount, bKeepEmpty, bKeepString );
	}

	VOID ExtractString( char * pszString, int delim )
	{
		clear();
		m_nStringCount = SearchParam( pszString, m_pStrings, MaxCount, delim );
	}

	VOID clear()
	{
		memset( m_pStrings, 0, sizeof( m_pStrings ) );
		m_nStringCount = 0;
	}

	UINT getCount(){ return m_nStringCount;}
	char * getString( UINT ptr ){ if( ptr > m_nStringCount )return NULL; return m_pStrings[ptr];}
	char * operator []( UINT ptr ){ return getString( ptr );}

protected:
	UINT	m_nStringCount;
	char * m_pStrings[MaxCount];
};
//------------------------------------------------------------------------
class xStringParse
{
public:
	xStringParse( char * pszString, int spliter )
	{
		m_pString = pszString;
		m_pCurString = pszString;
		m_iSpliter = spliter;
	}

	~xStringParse()
	{
	}
	
	char * first()
	{
		return next();
	}

	char * next()
	{
		char * p = m_pString;
		while( *p )
		{
			if( *p == m_iSpliter )
			{
				*p = 0;
				m_pCurString = m_pString;
				m_pString = p+1;
				return m_pCurString;
			}
			p++;
		}
		if( p == m_pString )
			return NULL;
		m_pCurString = m_pString;
		m_pString = p;
		return m_pCurString;
	}

	char * cur()
	{
		return m_pCurString;
	}
protected:
	int	m_iSpliter;
	char * m_pString;
	char * m_pCurString;
};
//------------------------------------------------------------------------
inline char * filtercopy( char * pDest, const char * pSource, int iMaxSize, xCharSet & filterSet = CharSetWhite )
{
	int counter = 0;
	char * p = (char*)pSource;
	char c = 0;
	while( c = *p++ )
	{
		if( filterSet.charIn( c ) )continue;
		*(pDest + counter++) = c;
		if( counter >= iMaxSize )
			break;
	}
	*(pDest + counter ) = 0;
	return pDest;
}
//------------------------------------------------------------------------