/**
*	created:		2013-4-16   4:41
*	filename: 		xIndexPtrList
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
template<class T>
class xQueue
{
public:
	xQueue()
	{
		m_varArray = NULL;
		m_iMax = 0;
		clear();
	}
	~xQueue()
	{
		clear();
		destroy();
	}


	BOOL	create( int size )
	{
		destroy();
		if( size > 0 )
		{
			m_iMax = size;
			m_varArray = new T[m_iMax];
			clear();
			return TRUE;
		}
		return FALSE;
	}

	VOID destroy()
	{
		if( m_varArray != NULL )
		{
			delete []m_varArray;
			m_varArray = NULL;
		}
		m_iMax = 0;
	}

	VOID	clear()
	{
		m_iPut = 0;
		m_iGet = 0;
		m_bFull = FALSE;
	}

	BOOL	pop( T & var )
	{
		if( m_varArray == NULL )return FALSE;
		if( m_iGet == m_iPut && m_bFull == FALSE )return FALSE;
		var = m_varArray[m_iGet];
		m_iGet++;
		m_iGet %= m_iMax;
		if( m_bFull )m_bFull = FALSE;
		return TRUE;
	}
	BOOL push( T var )
	{
		if( m_varArray == NULL )return FALSE;
		if( m_bFull )return FALSE;
		m_varArray[m_iPut] = var;
		m_iPut ++;
		m_iPut %= m_iMax;
		if( m_iPut == m_iGet )m_bFull = TRUE;
		return TRUE;
	}

private:
	BOOL m_bFull;
	int m_iGet;
	int m_iPut;
	int	m_iMax;
	T * m_varArray;
};
//------------------------------------------------------------------------
template<class T>
class xIndexPtrList
{
public:

	xIndexPtrList(void)
	{
		m_varArray = NULL;
		m_iMax = 0;
		m_iArrayPtr = 0;
		m_nCount = 0;
	}

	virtual ~xIndexPtrList(void)
	{
		destroy();
	}

	BOOL	create( int nSize )
	{
		if( nSize > 0 )
		{
			destroy();
			if( !m_freeQueue.create( nSize ) )
				return FALSE;
			m_varArray = new T*[nSize];
			memset( m_varArray, 0, sizeof( T*) * nSize );
			m_iMax = nSize;
			return TRUE;
		}
		return FALSE;
	}

	VOID destroy()
	{
		if( m_varArray != NULL )
		{
			delete []m_varArray;
			m_varArray = NULL;
		}
		m_freeQueue.destroy();
		m_iMax = 0;
		m_nCount = 0;
	}

	UINT	addObject( T * pt )
	{
		UINT id = 0;
		if( pt == NULL )return 0;
		id = findObject( pt );
		if( id > 0 )return id;
		if( m_iArrayPtr >= m_iMax )
		{
			if( !m_freeQueue.pop( id ) )
				return 0;
		}
		else
			id = ++m_iArrayPtr;
		m_varArray[id-1] = pt;
		this->m_nCount ++;
		return id;
	}

	BOOL delObject( UINT id )
	{
		if( getObject( id ) == NULL )return FALSE;
		m_varArray[id-1] = NULL;
		if( id == m_iArrayPtr )
			m_iArrayPtr --;
		else
			m_freeQueue.push( id );
		m_nCount --;
		return TRUE;
	}

	BOOL	delObject( T * pt )
	{
		UINT	id = findObject( pt );
		if( id == 0 )return FALSE;
		return delObject( id );
	}

	T * getObject( UINT id )
	{
		if( id == 0 || id > m_iMax )return NULL;
		return m_varArray[id-1];
	}

	UINT findObject( T * pt )
	{
		for( UINT i = 0;i < m_iArrayPtr;i ++ )
		{
			if( m_varArray[i] == pt )return (i+1);
		}
		return 0;
	}

	UINT	getCount()
	{
		return m_nCount;
	}
public:
	UINT getMax(){ return m_iMax;}
	UINT getCurPtr(){ return m_iArrayPtr;}
private:
	xQueue<UINT>	m_freeQueue;
	T ** m_varArray;
	UINT m_iMax;
	UINT	m_iArrayPtr;
	UINT	m_nCount;
};
//------------------------------------------------------------------------
template<class T>
class xIndexPtrListHelper
{
public:
	xIndexPtrListHelper( xIndexPtrList<T> & list )
	{
		m_iPtr = 0;
		m_pIndexPtrList = &list;
	}
	xIndexPtrListHelper()
	{
		m_iPtr = 0;
	}
	~xIndexPtrListHelper()
	{
		m_iPtr = 0;
	}

	VOID setPtrList( xIndexPtrList<T> & list )
	{
		m_iPtr = 0;
		m_pIndexPtrList = &list;
	}

	T * first()
	{
		T * pt = NULL;
		for( m_iPtr = 1;m_iPtr < m_pIndexPtrList->getCurPtr();m_iPtr ++ )
		{
			pt = m_pIndexPtrList->getObject( m_iPtr );
			if( pt )
				return pt;
		}
		return NULL;
	}
	T * next()
	{
		T * pt = NULL;
		m_iPtr ++;
		for( ;m_iPtr < m_pIndexPtrList->getCurPtr();m_iPtr ++ )
		{
			pt = m_pIndexPtrList->getObject( m_iPtr );
			if( pt )
				return pt;
		}
		return NULL;
	}
protected:
	UINT m_iPtr;
	xIndexPtrList<T> * m_pIndexPtrList;
};
//------------------------------------------------------------------------