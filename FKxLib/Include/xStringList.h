/**
*	created:		2013-4-16   4:51
*	filename: 		xStringList
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xinc.h"
//------------------------------------------------------------------------
template < UINT nCacheSize >
class xStringList
{
	typedef struct string_def
	{
		string_def()
		{
			memset( this, 0, sizeof( *this ) );
		}
		DWORD dwKey;
		char * pszString;
		LPVOID lpObject;
	}STRING_DEF;

public:
	xStringList( BOOL ignCase = FALSE )
	{
		m_pStringArray = NULL;
		m_nStringCount = 0;
		m_nCurArraySize = 0;
		m_bIgnCase = ignCase;
		m_pFileName = NULL;
	}
	~xStringList()
	{
		if( m_pStringArray != NULL )
		{
			delete []m_pStringArray;
			m_pStringArray = 0;
		}
		if( m_pFileName )
			delete []m_pFileName;

	}

	BOOL IsIgnCase(){ return m_bIgnCase;}
	VOID SetIgnCase( BOOL bFlag ){ m_bIgnCase = bFlag;}

	void Clear()
	{
		for( UINT n = 0;n < m_nStringCount;n ++ )
		{
			m_pStringArray[n].lpObject = NULL;
			m_pStringArray[n].dwKey = 0;
			if( this->m_pStringArray[n].pszString )
			{
				delete []this->m_pStringArray[n].pszString;
			}
			m_pStringArray[n].pszString = NULL;
		}
		m_nStringCount = 0;
		
	}

	int	IndexOf( const char * pszString1 )
	{
		if( *pszString1 == 0 )return -1;
		char	pszString[260];
		o_strncpy( pszString, pszString1, 256 );
		if( this->m_bIgnCase )
			q_strupper( pszString );

		DWORD	dwKey = MakeKey( pszString );
		DWORD	s = 0, m = 0, e = m_nStringCount;

		while( s < e )
		{
			m = (s+e)/2;
			if( dwKey == m_pStringArray[m].dwKey )
			{
				if( strcmp( m_pStringArray[m].pszString, pszString ) == 0 )return m;
				DWORD count = m>m_nStringCount/2?(m_nStringCount/2):m;
				for( DWORD ptr = 1;ptr < count+1;ptr ++ )
				{
					if( dwKey == m_pStringArray[m-ptr].dwKey )
					{
						if( strcmp( m_pStringArray[m-ptr].pszString, pszString ) == 0 )return (m-ptr);
					}
					else if( dwKey != m_pStringArray[m+ptr].dwKey )
						return -1;
					if( dwKey == m_pStringArray[m+ptr].dwKey )
					{
						if( strcmp( m_pStringArray[m+ptr].pszString, pszString ) == 0 )return (m+ptr);
					}
				}
				return -1;
			}
			if( dwKey < m_pStringArray[m].dwKey )
			{
				if( e == m )
					return -1;
				e = m;
			}
			else
			{
				if( s == m )
					return -1;
				s = m;
			}
		}
		return -1;
	}

	int	Add( const char * pszString1, LPVOID lpObject = NULL )
	{
		if( *pszString1 == 0 )return -1;
		char	pszString[260];
		o_strncpy( pszString, pszString1, 256 );
		if( this->m_bIgnCase )
			q_strupper( pszString );

		DWORD dwKey = MakeKey( pszString );
		UINT	nLeft = this->m_nCurArraySize - this->m_nStringCount;

		if( nLeft < 1 )
		{
			if( !IncArraySize( nCacheSize ))
			{
				return -1;
			}
		}

		int index = FindFitIndex( dwKey );
		if( index == -1 )
		{
			return -1;
		}

		if( index < (int)m_nStringCount )
		{
			memmove( m_pStringArray+index+1, m_pStringArray+index, sizeof( STRING_DEF ) * (m_nStringCount - index ) );
		}

		m_pStringArray[index].dwKey = dwKey;
		m_pStringArray[index].lpObject = lpObject;
		m_pStringArray[index].pszString = copystring( pszString );
		m_nStringCount++;
		return index;
	}

	LPVOID ObjectOf( const char * pszString )
	{
		int index = IndexOf( pszString );
		if( index == -1 )return NULL;
		return m_pStringArray[index].lpObject;
	}

	BOOL	Delete( const char * pszString )
	{
		int index = IndexOf( pszString );
		return Delete( index );
	}

	BOOL	Delete( int index )
	{
		if( index < 0 || index >= (int)m_nStringCount )
			return FALSE;
		m_nStringCount --;
		delete []m_pStringArray[index].pszString;
		if( m_nStringCount == index )return TRUE;
		memmove( m_pStringArray+index, m_pStringArray+index+1, sizeof( STRING_DEF ) * (m_nStringCount - index)  );
		return TRUE;
	}

	STRING_DEF * operator []( int index )
	{
		if( index < 0 || index >= (int)m_nStringCount )
			return NULL;
		return m_pStringArray+index;
	}

	UINT GetCount(){ return m_nStringCount;}

	BOOL	LoadFromFile( const char * pszFilename )
	{
		char * filename = copystring( pszFilename );
		if( m_pFileName )delete []m_pFileName;
		m_pFileName = filename;

		CStringFile sf( m_pFileName );
		BOOL	bFlag = FALSE;
		char * p = NULL;
		for( int i = 0;i < sf.GetLineCount();i ++ )
		{
			p = TrimEx( sf[i] );
			if( p[0] == 0 )continue;
			if( m_bIgnCase )
			{
				q_strupper(p);
			}
			if( IndexOf(p) != -1 )
				continue;
			if( Add( p ) != -1 )
				bFlag = TRUE;
		}
		return bFlag;
	}
	
	BOOL	SaveToFile( const char * pszFilename )
	{
		char * filename = copystring( pszFilename );
		if( m_pFileName )delete []m_pFileName;
		m_pFileName = filename;

		FILE * fp = fopen( m_pFileName, "w" );
		if( fp == NULL )return FALSE;
		for( UINT i = 0;i < m_nStringCount;i ++ )
		{
			fputs( m_pStringArray[i].pszString, fp );
			fputs( "\n", fp );
		}
		fclose( fp );
		return TRUE;
	}
	const char * GetFileName()
	{
		return m_pFileName;
	}
	void SetFileName( const char * pszFilename )
	{
		if( m_pFileName )delete []m_pFileName;
		m_pFileName = copystring( pszFilename );
	}
protected:
	DWORD	MakeKey( const char * pszString )
	{
		char * p = (char*)pszString;
		DWORD	dwKey = 0;
		while( *p )
		{
			dwKey += (BYTE)*p;
			p++;
		}
		return dwKey;
	}

	int FindFitIndex( DWORD dwKey )
	{
		for( UINT n = 0;n < m_nStringCount;n ++ )
		{
			if( dwKey < m_pStringArray[n].dwKey )
				return n;
		}
		return m_nStringCount;
	}

	BOOL	IncArraySize( UINT nSize )
	{
		STRING_DEF * pArray = new STRING_DEF[ nSize + m_nCurArraySize ];
		if( pArray == NULL )return FALSE;
		if( m_nStringCount > 0 )
			memcpy( pArray, m_pStringArray, sizeof( STRING_DEF ) * m_nStringCount );
		delete []m_pStringArray;
		m_pStringArray = pArray;
		m_nCurArraySize += nSize;
		return TRUE;
	}

	STRING_DEF	*m_pStringArray;
	UINT	m_nStringCount;
	UINT	m_nCurArraySize;
	BOOL	m_bIgnCase;
	char	*	m_pFileName;
};
//------------------------------------------------------------------------
template <UINT nMax> 
class xVarList
{
public:
	typedef struct tagVariable
	{
		tagVariable()
		{
			pszValue = NULL;
		}
		char	* pszValue;
	}Variable;
	xVarList() : m_xList( TRUE )
	{
	}

	VOID ClearVars()
	{
		UINT nCount = m_xList.GetCount();

		for( UINT i = 0;i < nCount;i ++ )
		{
			Variable * pVar = (Variable*)m_xList[i]->lpObject;
			if( pVar )
			{
				if( pVar->pszValue )
					delete []pVar->pszValue;
				delete pVar;
			}
		}
		m_xList.Clear();
	}

	VOID DelVar( const char * pszName )
	{
		Variable * pVar = (Variable*)m_xList.ObjectOf( pszName );
		if( pVar == NULL )
			return;
		m_xList.Delete( pszName );
		if( pVar->pszValue )
			delete []pVar->pszValue;
		delete pVar;
	}

	VOID AddVar( const char * pszName, char * pszValue )
	{
		if( pszValue == NULL )pszValue = "";
		Variable * pVar = (Variable*)m_xList.ObjectOf( pszName );
		if( pVar == NULL )
		{
			pVar = new Variable;
			m_xList.Add( pszName, (LPVOID)pVar );
		}
		else
		{
			if( pVar->pszValue )
			{
				delete []pVar->pszValue;
				pVar->pszValue = NULL;
			}
		}
		if( pszValue )
			pVar->pszValue = copystring( pszValue );
	}

	char * GetVarValue( const char * pszName )
	{
		Variable * pVar = (Variable*)m_xList.ObjectOf( pszName );
		if( pVar == NULL )return NULL;
		if( pVar->pszValue == NULL )return "";
		return pVar->pszValue;
	}

	xStringList<nMax> * GetList(){ return &m_xList;}

	BOOL	LoadFromFile( const char * pszFile )
	{
		CStringFile sf( pszFile );
		char * pLine = "";
		for( UINT i = 0;i < (UINT)sf.GetLineCount();i ++ )
		{
			pLine = TrimEx( sf[i] );
			if( *pLine == 0 || *pLine == '#' )continue;
			xStringsExtracter<2> svar( pLine, "=", " \t\"" );
			if( svar.getCount() < 2 )continue;
			AddVar( svar[0], svar[1] );
		}
		return TRUE;
	}

	VOID	SaveToFile( const char * pszFile )
	{
		FILE * fp = NULL;
		fp = fopen( pszFile, "w" );
		if( fp == NULL )return;
		
		for( UINT n = 0;n < m_xList.GetCount();n ++ )
		{
			Variable * var = (Variable *)m_xList[n]->lpObject;
			char * pVal =var->pszValue;
			if( pVal == NULL )
				pVal = "";
			fprintf( fp, "%s = \"%s\"\n", m_xList[n]->pszString, pVal );
		}
		fclose( fp );
	}

protected:
	xStringList<nMax> m_xList;
};
//------------------------------------------------------------------------