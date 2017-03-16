/**
*	created:		2013-4-16   4:09
*	filename: 		xStringFile
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CStringFile
{
public:
	CStringFile( const char * pszTextFile )
	{
		m_pData = NULL;
		m_iDataSize = 0;
		m_pLines = NULL;
		m_iLineCount = 0;
		m_bBuildInData = FALSE;
		LoadFile( pszTextFile );
	}
	CStringFile()
	{
		m_pData = NULL;
		m_iDataSize = 0;
		m_pLines = NULL;
		m_iLineCount = 0;
		m_bBuildInData = FALSE;
	}
	~CStringFile()
	{
		Destroy();
	}
	VOID	Destroy()
	{
		if( m_pLines != NULL )
		{
			delete []m_pLines;
			m_pLines = NULL;
		}
		m_iDataSize = 0;
		if( m_pData != NULL )
		{
			if( m_bBuildInData )delete []m_pData;
			m_pData = NULL;
		}
		m_iLineCount = 0;
	}
	VOID	MakeDeflate()
	{
		int i = 0;
		char * p;
		char * p1;
		BOOL	bInString = FALSE;
		for( i = 0;i < GetLineCount();i ++ )
		{
			p = (*this)[i];
			p1 = p;
			while( *p != '\0' )
			{
				if( *p == '\"' )bInString = !bInString;
				if( (!bInString) && ( *p == ' ' || *p == '	' ) )
				{
					p++;
					continue;
				}
				*p1++=*p++;
			}
			*p1 = 0;
		}
	}
	BOOL	LoadFile( const char * pszTextFile )
	{
		FILE	*	fp = fopen( pszTextFile, "rb" );
		if( fp == NULL )return FALSE;
		fseek( fp, 0, SEEK_END );
		m_iDataSize = ftell( fp );
		fseek( fp, 0, SEEK_SET );
		m_pData = new char [m_iDataSize+2];
		if( m_pData == NULL )return FALSE;
		m_bBuildInData = TRUE;
		fread( m_pData, m_iDataSize, 1, fp );
		fclose( fp );
		m_pData[m_iDataSize] = 0;
		m_pData[m_iDataSize+1] = 0;
		m_iLineCount = ProcData();
		return BuildLines();
	}

	BOOL	SetData( char * pData, int iSize )
	{
		m_bBuildInData = FALSE;
		m_iDataSize = iSize;
		m_pData = pData;
		m_iLineCount = ProcData();
		return BuildLines();
	}

	char * operator[]( int line )
	{
		if( line < 0 || line >= m_iLineCount )return NULL;
		return m_pLines[line];
	}
	int	GetLineCount(){return m_iLineCount;}
private:
	BOOL	BuildLines( )
	{
		if( m_iLineCount == 0 )return FALSE;
		char * p = m_pData;
		m_pLines = new char*[m_iLineCount];
		int len = 0;
		int ptr = 0;
		for( int i = 0;i < m_iLineCount;i ++ )
		{
			len = (int)strlen( p );
			if( len > 0 )
				m_pLines[ptr++] = p;
			else
				break;
			p = p+len+1;
		}
		return TRUE;
	}
	int		ProcData()
	{
		int i = 0;
		char * p = NULL;
		int linecount = 0;
		int rptr = 0;
		bool	binstring = false;
		bool	newlinestart = false;
		for( i = 0;i < m_iDataSize;i ++ )
		{
			p = m_pData + i;
			switch( *p )
			{
			case	'\n':
			case	'\r':
				{
					if( newlinestart )
					{
						*(m_pData+rptr++) = 0;
						newlinestart = false;
						linecount++;
					}
				}
				break;
			default:
				{
					*(m_pData+rptr++) = *p;
					if( !newlinestart )newlinestart = true;
				}
				break;
			}
		}
		if( newlinestart )
			linecount++;
		assert( rptr <= m_iDataSize );
		m_pData[rptr++] = 0;
		m_pData[rptr++] = 0;
		m_iDataSize = rptr;
		return linecount;
	}
	char * m_pData;
	int	   m_iDataSize;
	int	   m_iLineCount;
	char** m_pLines;
	BOOL	m_bBuildInData;
};
//------------------------------------------------------------------------