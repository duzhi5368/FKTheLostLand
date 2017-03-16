/**
*	created:		2013-4-16   4:49
*	filename: 		xPacket
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "xinc.h"
//------------------------------------------------------------------------
class xPacket
{
public:
	xPacket()
	{
		m_pBuf = NULL;
		m_iSize = 0;
		m_iMaxSize = 0;
		m_bBuildInBuffer = FALSE;
	}

	xPacket( int nSize )
	{
		m_pBuf = NULL;
		m_iSize = 0;
		m_iMaxSize = 0;
		m_bBuildInBuffer = FALSE;
		create( nSize );
	}

	xPacket( char * pbuf, int nSize )
	{
		m_pBuf = NULL;
		m_iSize = 0;
		m_iMaxSize = 0;
		m_bBuildInBuffer = FALSE;
		create( pbuf, nSize );
	}

	virtual ~xPacket(void)
	{
		destroy();
	}

	BOOL	create( char * pbuf, int nSize )
	{
		destroy();
		m_bBuildInBuffer = FALSE;
		m_pBuf = pbuf;
		m_iMaxSize = nSize;
		return TRUE;
	}

	BOOL	create( int nSize )
	{
		destroy();
		if( nSize > 0 )
		{
			m_bBuildInBuffer = TRUE;
			m_pBuf = new char[nSize];
			m_iMaxSize = nSize;
		}
		return TRUE;
	}

	BOOL notcreated()
	{
		return (m_pBuf == NULL);
	}

	VOID	destroy()
	{
		if( m_bBuildInBuffer )
			delete []m_pBuf;
		m_pBuf = NULL;
		m_iMaxSize = 0;
		m_iSize = 0;
		m_bBuildInBuffer = FALSE;
	}

	BOOL	push( LPVOID lpData, int iDatasize )
	{
		if( m_iMaxSize - m_iSize < iDatasize )return FALSE;
		memcpy( m_pBuf + m_iSize, lpData, iDatasize );
		m_iSize += iDatasize;
		return TRUE;
	}

	BOOL	push( const char * pszString )
	{
		int len = (int)strlen( pszString );
		return push( (LPVOID)pszString, len );
	}

	BOOL	pop( LPVOID lpData, int iDatasize )
	{
		if( m_iSize < iDatasize )return FALSE;
		memcpy( lpData, m_pBuf + m_iSize, iDatasize );
		return free( iDatasize );
	}
	BOOL	peek( LPVOID lpData, int iDatasize )
	{
		if( m_iSize < iDatasize )return FALSE;
		memcpy( lpData, m_pBuf + m_iSize, iDatasize );
		return TRUE;
	}
	BOOL	free( int iDatasize )
	{
		if( m_iSize < iDatasize )return FALSE;
		m_iSize -= iDatasize;
		if( m_iSize != 0 )
			memmove( m_pBuf, m_pBuf + iDatasize, m_iSize );
		return TRUE;
	}
	VOID	clear()
	{
		m_iSize = 0;
	}

	int				getsize(){return m_iSize;}
	const char *	getbuf(){ return m_pBuf;}
	const char *	getfreebuf(){ return (m_pBuf + m_iSize);}
	int				getmaxsize(){return m_iMaxSize;}
	int				getfreesize(){return m_iMaxSize - m_iSize;}
	void			setsize( int nSize ){ m_iSize = nSize;}
	BOOL			addsize( int nSize )
	{
		if( nSize > getfreesize() )return FALSE;
		m_iSize += nSize;
		return TRUE;
	}
private:
	char *	m_pBuf;
	int		m_iSize;
	int		m_iMaxSize;
	BOOL	m_bBuildInBuffer;
};
//------------------------------------------------------------------------