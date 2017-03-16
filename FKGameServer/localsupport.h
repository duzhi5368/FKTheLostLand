/**
*	created:		2013-4-18   23:59
*	filename: 		localsupport
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma	once
//------------------------------------------------------------------------
#define	INDEXEDTABLE_SEGMENT_CACHE	2048
//------------------------------------------------------------------------
template<int MAXCOUNT>
class xIdAllocorEx
{
public:
	xIdAllocorEx()
	{
		memset( m_IdCache, 0, sizeof( m_IdCache ) );
		m_nIdPtr = 0;
		m_nCacheCount = 0;
	}
	UINT	allocid()
	{
		return (++m_nIdPtr);
	}
	VOID freeid(UINT id)
	{
	}
	BOOL isused(UINT id)
	{
		return TRUE;
	}
private:
	UINT m_IdCache[MAXCOUNT];
	UINT m_nCacheCount;
	UINT m_nIdPtr;
};
//------------------------------------------------------------------------
template<int MAXCOUNT>
class xIdAllocor
{
public:
	xIdAllocor()
	{
		for( UINT i = 0;i < MAXCOUNT;i ++ )
		{
			m_NextFree[i] = i + 1;
		}
		m_iFree = 0;
		m_iCount = 0;
	}
	UINT	allocid()
	{
		if( m_iFree >= MAXCOUNT )return 0;
		UINT id = m_iFree + 1;
		m_iFree = m_NextFree[m_iFree];
		m_NextFree[id-1] = 0xffffffff;
		m_iCount ++;
		return id;
	}
	VOID freeid(UINT id)
	{
		if(id == 0 || id > MAXCOUNT )return;
		id --;
		if( m_NextFree[id] != 0xffffffff )return;
		m_NextFree[id] = m_iFree;
		m_iFree = id;
		m_iCount --;
	}
	BOOL isused(UINT id)
	{
		return (id>0&&id<=MAXCOUNT&&m_NextFree[id-1]==0xffffffff);
	}
	UINT	getcount(){ return m_iCount;}
	BOOL isfull(){ return (m_iCount >= MAXCOUNT);}
private:
	UINT	m_NextFree[MAXCOUNT+1];
	UINT	m_iFree;
	UINT	m_iCount;
};
//------------------------------------------------------------------------
int getintegerinside( char * buffer, int begin, int end )
{
	char * p = buffer;

	char * pret = NULL;
	int iret = 0;
	while( *p )
	{
		if( *p == begin )
			pret = p+1;
		if( pret != NULL && *p == end )
		{
			*p = 0;
			iret = StringToInteger( pret );
			*p = end;

			return iret;
		}
		p++;
	}
	return 0;
}
//------------------------------------------------------------------------
char * getstringinside( char * buffer, int begin, int end )
{
	char * p = buffer;

	char * pret = NULL;

	while( *p )
	{
		if( *p == begin )
			pret = p+1;
		if( pret != NULL && *p == end )
		{
			*p = 0;
			return pret;
		}
		p++;
	}
	return NULL;

}
//------------------------------------------------------------------------
char * gettoedge( char * buffer, int begin, int end )
{
	char * p = buffer;
	int level = 0;
	while( *p )
	{
		if( *p == begin )
		{
			level ++;
		}
		else if( *p == end )
		{
			level --;
			if( level == 0 )
				return (p+1);
		}
	}
	return NULL;
}
//------------------------------------------------------------------------
static int	GetMsgFromString( const char * pszString, char * pMsgBuffer )
{
	MIRMSG	header;
	char * pMsg = pMsgBuffer;

	char * Params[200];
	char	szBuffer[2048];
	char	szBinBuffer[1024];
	int		binPtr = 0;
	o_strncpy( szBuffer, pszString, 2047 );

	int nParam = SearchParam( szBuffer, Params, 200, '|' );
	if( nParam < 5 )return 0;

	header.dwFlag = (DWORD)StringToInteger( Params[0] );
	header.wCmd = (WORD)StringToInteger( Params[1] );
	header.wParam[0] = (WORD)StringToInteger( Params[2] );
	header.wParam[1] = (WORD)StringToInteger( Params[3] );
	header.wParam[2] = (WORD)StringToInteger( Params[4] );
	*pMsg++ = '#';
	pMsg += _CodeGameCode( (BYTE*)&header, MSGHEADERSIZE, (BYTE*)pMsg );
	char	c;
	for( int i = 5;i < nParam;i ++ )
	{
		if( *(Params[i]+1) == ':' )
		{
			c = *Params[i];
			Params[i] += 2;
			switch( c )
			{
			case	'w':
			case	'W':
				*(WORD*)(szBinBuffer+binPtr) = (WORD)StringToInteger( Params[i] );
				binPtr += 2;
				break;
			case	'D':
			case	'd':
				*(DWORD*)(szBinBuffer+binPtr) = (DWORD)StringToInteger( Params[i] );
				binPtr += 4;
				break;
			case	'B':
			case	'b':
				*(BYTE*)(szBinBuffer+binPtr) = (BYTE)StringToInteger( Params[i] );
				binPtr += 1;
				break;
			case	's':
			case	'S':
				strcpy( szBinBuffer+binPtr, Params[i] );
				binPtr += (int)strlen( Params[i] );
				break;
			default:
				break;
			}
			continue;
		}
		strcpy( szBinBuffer+binPtr, Params[i] );
		binPtr += (int)strlen( Params[i] );
	}
	if( binPtr > 0 )
	{
		*(szBinBuffer+binPtr) = 0;
		pMsg += _CodeGameCode( (BYTE*)szBinBuffer, binPtr, (BYTE*)pMsg );
	}
	*pMsg++ = '!';
	return (int)(pMsg-pMsgBuffer);
}
//------------------------------------------------------------------------
inline void replaceOutPair( char * pszString, int PairL, int PairR, int ReplaceTo )
{
	char * p = pszString;
	int	PairLevel = 0;
	int tLevel = 0;
	BOOL	bErase = FALSE;
	while( *p )
	{
		if( *p == ' ' || *p == '\t' )
		{
			if( tLevel == 0 )
				tLevel = 1;
		}
		else if( *p == PairL )
		{
			PairLevel ++;
			if( PairLevel == 1 && tLevel != 2 )
			{
				*p = ReplaceTo;
				bErase = TRUE;
			}
		}
		else if( *p == PairR )
		{
			if( PairLevel == 1 && bErase )
				*p = ReplaceTo;
			PairLevel --;
		}
		else 
		{
			if( tLevel == 1 )
				tLevel = 2;
		}
		p++;
	}
}
//------------------------------------------------------------------------