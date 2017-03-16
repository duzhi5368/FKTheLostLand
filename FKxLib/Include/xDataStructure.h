/**
*	created:		2013-4-16   1:36
*	filename: 		xDataStructure
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#ifndef MAKEWORD
#define MAKEWORD(lo, hi)      	((WORD)(((BYTE)(lo)) | ((WORD)((BYTE)(hi))) << 8))
#endif
#define MAKEDWORD(lo, hi)     	((DWORD)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
#define LOWORD(l)           	((WORD)(l))
#define HIWORD(l)           	((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           	((BYTE)(w))
#define HIBYTE(w)           	((BYTE)(((WORD)(w) >> 8) & 0xFF))
//------------------------------------------------------------------------
// 池内存管理标示
#define	POOLMEMORYFLAG			MAKEDWORD(MAKEWORD('F','K'),MAKEWORD('M','P')
// 对象池缓冲大小
#define	OBJECTPOOLCACHESIZE		4096
//------------------------------------------------------------------------
template < class T , int MAXCOUNT>
class CIndexList
{
	typedef struct	_node_
	{
		T		*		data;
		_node_	*		pnext;
		_node_	*		pprev;
		unsigned int	nextfree;

	}st_node;
	BOOL _Clean()
	{
		for( int i = 0;i <= MAXCOUNT;i ++ )
		{
			m_pArray[i].data = NULL;
			m_pArray[i].pnext = NULL;
			m_pArray[i].pprev = NULL;
			m_pArray[i].nextfree = i + 1;
		}
		m_pArray[MAXCOUNT].data = NULL;
		m_pArray[MAXCOUNT].nextfree = 0;
		m_pArray[MAXCOUNT].pnext = NULL;
		m_pArray[MAXCOUNT].pprev = NULL;
		m_free = 1;
		m_pHead = &m_pArray[0];
		m_pTail = m_pHead;
		m_pThrough = m_pHead;
		m_totel = 0;
		m_bLocked = FALSE;
		return TRUE;
	}
public:
	CIndexList()
	{
		m_pArray = NULL;
		m_pArray = new st_node[MAXCOUNT + 1];
		_Clean();
	}
	VOID	Clean()
	{
		for( int i = 0;i <= MAXCOUNT;i ++ )
		{
			m_pArray[i].pnext = NULL;
			m_pArray[i].pprev = NULL;
			m_pArray[i].nextfree = i + 1;
		}
		m_pArray[MAXCOUNT].nextfree = 0;
		m_pArray[MAXCOUNT].pnext = NULL;
		m_pArray[MAXCOUNT].pprev = NULL;
		m_free = 1;
		m_pHead = &m_pArray[0];
		m_pTail = m_pHead;
		m_pThrough = m_pHead;
		m_totel = 0;
		m_bLocked = FALSE;

	}
	virtual ~CIndexList()
	{
		for( int i = 0;i < MAXCOUNT;i ++ )
		{
			if( m_pArray[i].data != NULL )
			{
				delete m_pArray[i].data;
				m_pArray[i].data = NULL;
			}
		}
		if( m_pArray != NULL )
			delete [] m_pArray;
	}

public:
	unsigned int GetCount()
	{
		return m_totel;
	}
	int Reset()
	{
		CLock m_lock(&m_CriticalSection);
		m_pThrough = m_pHead;
		return 1;
	}
	VOID		Lock()
	{
		m_CriticalSection.Lock();
	}
	VOID		UnLock()
	{
		m_CriticalSection.Unlock();
	}
	T * First()
	{
		if( m_pHead == NULL )
			return NULL;
		m_pThrough = m_pHead->pnext;
		if( m_pThrough != NULL )
			return m_pThrough->data;
		return NULL;
	}
	T * Cur()
	{
		if( m_pThrough != NULL && m_pThrough != m_pHead )
			return m_pThrough->data;
		return NULL;
	}
	T * Next()
	{
		if( m_pThrough != NULL )
			m_pThrough = m_pThrough->pnext;
		if( m_pThrough != NULL )
			return m_pThrough->data;
		return NULL;
	}
	T * End()
	{
		if( m_pTail != NULL )
			return m_pTail->data;
		return NULL;
	}
	unsigned int New( T ** t )
	{
		CLock m_lock(&m_CriticalSection);
		unsigned int id = 0;
		id = AllocId();
		if( id == 0 || id > MAXCOUNT )
			return 0;
		if( m_pArray[id].data == NULL )
			m_pArray[id].data = new T;

		*t = m_pArray[id].data;
		m_pTail->pnext = &m_pArray[id];
		m_pArray[id].pprev = m_pTail;
		m_pArray[id].pnext = NULL;
		m_pTail = &m_pArray[id];
		m_totel ++;
		return id;
	}
	int	Del( unsigned int id )
	{
		CLock m_lock(&m_CriticalSection);
		if( id > MAXCOUNT || id == 0 )
			return 0;
		if( m_pArray[id].pprev == NULL && m_pArray[id].pnext == NULL )
			return 0;
		if( m_pArray[id].pprev != NULL )
		{
			if( m_pThrough == &m_pArray[id] )
				m_pThrough = m_pArray[id].pprev;
			m_pArray[id].pprev->pnext = m_pArray[id].pnext;
		}
		else
			return 0;
		if( m_pArray[id].pnext != NULL )
			m_pArray[id].pnext->pprev = m_pArray[id].pprev;
		else
			m_pTail = m_pTail->pprev;

		m_pArray[id].pprev = NULL;
		m_pArray[id].pnext = NULL;
		ResaveId( id );
		m_totel --;
		return 1;
	}
	T *	Get( unsigned int id )
	{
		CLock m_lock(&m_CriticalSection);
		if( id == 0 )
			return NULL;
		if( id <= MAXCOUNT )
		{
			if( m_pArray[id].pnext == NULL && m_pArray[id].pprev == NULL )
				return NULL;
			return m_pArray[id].data;
		}
		return NULL;
	}
private:
	unsigned int AllocId()
	{
		CLock m_lock(&m_CriticalSection);
		unsigned int ret = m_free;
		if( ret != 0 )
			m_free = m_pArray[ret].nextfree;
		return ret;
	}
	int ResaveId( unsigned int id )
	{
		CLock m_lock(&m_CriticalSection);
		if( id > MAXCOUNT || id == 0 )
			return 0;
		m_pArray[id].nextfree = m_free;
		m_free = id;
		return 1;
	}
private:
	BOOL	m_bLocked;
	CriticalSection	m_CriticalSection;
	unsigned int	m_free;
	unsigned int	m_totel;
	st_node	*		m_pArray;
	st_node *		m_pHead;
	st_node *		m_pThrough;
	st_node *		m_pTail;
};
//------------------------------------------------------------------------
template < class T>
class CIndexListEx
{
	typedef struct	_node_
	{
		_node_()
		{
			memset( this, 0, sizeof( *this));
		}
		T		*		data;
		_node_	*		pnext;
		_node_	*		pprev;
		unsigned int	nextfree;
	}st_node;
	BOOL _Clean()
	{
		if( m_pArray == NULL )return FALSE;
		for( unsigned int i = 0;i <= MAXCOUNT;i ++ )
		{
			m_pArray[i].nextfree = i + 1;
		}

		m_pArray[MAXCOUNT].nextfree = 0;
		m_free = 1;
		m_pHead = &m_pArray[0];
		m_pTail = m_pHead;
		m_pThrough = m_pHead;
		m_totel = 0;
		m_bLocked = FALSE;
		return TRUE;
	}
	BOOL	IsCreated()
	{
		return ( m_pArray != NULL );
	}
public:
	int	GetMaxCount()
	{
		return MAXCOUNT;
	}
	int	GetFreeCount()
	{
		return MAXCOUNT - GetCount();
	}
	CIndexListEx()
	{
		m_pArray = NULL;
		MAXCOUNT = 0;
	}
	BOOL	Create( UINT maxcount )
	{
		if( m_pArray != NULL )
			Destroy();

		MAXCOUNT = (unsigned int)maxcount;
		m_pArray = new st_node[MAXCOUNT+1];
		if( !_Clean() )
		{
			delete [] m_pArray;
			return FALSE;
		}
		return TRUE;
	}
	VOID	Destroy()
	{
		if( !IsCreated() )return;
		for( UINT i = 0;i < MAXCOUNT;i ++ )
		{
			if( m_pArray[i].data != NULL )
				delete m_pArray[i].data;
		}
		delete []m_pArray;
	}
	VOID	Clean()
	{
		if( !IsCreated() )return;
		for( int i = 0;i <= MAXCOUNT;i ++ )
		{
			m_pArray[i].pnext = NULL;
			m_pArray[i].pprev = NULL;
			m_pArray[i].nextfree = i + 1;
		}

		m_pArray[MAXCOUNT].nextfree = 0;
		m_pArray[MAXCOUNT].pnext = NULL;
		m_pArray[MAXCOUNT].pprev = NULL;
		m_free = 1;
		m_pHead = &m_pArray[0];
		m_pTail = m_pHead;
		m_pThrough = m_pHead;
		m_totel = 0;
		m_bLocked = FALSE;

	}
	virtual ~CIndexListEx()
	{
		Destroy();
	}
public:
	unsigned int GetCount()
	{
		if( !IsCreated() )return 0;
		return m_totel;
	}
	int Reset()
	{
		if( !IsCreated() )return FALSE;
		m_pThrough = m_pHead;
		return 1;
	}
	VOID Lock()
	{
		m_CriticalSection.Lock();
	}
	VOID UnLock()
	{
		m_CriticalSection.Unlock();
	}
	T * First()
	{
		if( !IsCreated() )return NULL;
		if( m_pHead == NULL )
			return NULL;
		m_pThrough = m_pHead->pnext;
		if( m_pThrough != NULL )
			return m_pThrough->data;
		return NULL;
	}
	T * Cur()
	{
		if( !IsCreated() )return NULL;
		if( m_pThrough != NULL && m_pThrough != m_pHead )
			return m_pThrough->data;
		return NULL;
	}
	T * Next()
	{
		if( !IsCreated() )return NULL;
		if( m_pThrough != NULL )
			m_pThrough = m_pThrough->pnext;
		if( m_pThrough != NULL )
			return m_pThrough->data;
		return NULL;
	}
	T * End()
	{
		if( !IsCreated() )return NULL;
		if( m_pTail != NULL )
			return m_pTail->data;
		return NULL;
	}
	unsigned int New( T ** t )
	{
		*t = NULL;
		if( !IsCreated() )return 0;
		unsigned int id = 0;
		id = AllocId();
		if( id == 0 || id > (unsigned int)MAXCOUNT )
			return 0;
		if( m_pArray[id].data == NULL )
			m_pArray[id].data = new T;

		*t = m_pArray[id].data;
		m_pTail->pnext = &m_pArray[id];
		m_pArray[id].pprev = m_pTail;
		m_pArray[id].pnext = NULL;
		m_pTail = &m_pArray[id];
		m_totel ++;
		return id;
	}
	int	Del( unsigned int id )
	{
		if( !IsCreated() )return 0;

		if( id > (unsigned int)MAXCOUNT || id == 0 )
			return 0;
		if( m_pArray[id].pprev == NULL && m_pArray[id].pnext == NULL )
			return 0;
		if( m_pArray[id].pprev != NULL )
		{
			if( m_pThrough == &m_pArray[id] )
				m_pThrough = m_pArray[id].pprev;
			m_pArray[id].pprev->pnext = m_pArray[id].pnext;
		}
		else
			return 0;
		if( m_pArray[id].pnext != NULL )
			m_pArray[id].pnext->pprev = m_pArray[id].pprev;
		else
			m_pTail = m_pTail->pprev;

		m_pArray[id].pprev = NULL;
		m_pArray[id].pnext = NULL;
		ResaveId( id );
		m_totel --;
		return 1;
	}
	T *	Get( unsigned int id )
	{
		if( !IsCreated() )return NULL;

		if( id == 0 )
			return NULL;
		if( id <= MAXCOUNT )
		{
			if( m_pArray[id].pnext == NULL && m_pArray[id].pprev == NULL )
				return NULL;
			return m_pArray[id].data;
		}
		return NULL;
	}
private:
	unsigned int AllocId()
	{
		if( !IsCreated() )return 0;
		unsigned int ret = m_free;
		if( ret != 0 )
			m_free = m_pArray[ret].nextfree;
		return ret;
	}
	int ResaveId( unsigned int id )
	{
		if( !IsCreated() )return 0;
		if( id > (unsigned int)MAXCOUNT || id == 0 )
			return 0;
		m_pArray[id].nextfree = m_free;
		m_free = id;
		return 1;
	}
private:
	UINT MAXCOUNT;
	BOOL	m_bLocked;
	CriticalSection	m_CriticalSection;
	unsigned int	m_free;
	unsigned int	m_totel;
	st_node	*		m_pArray;
	st_node *		m_pHead;
	st_node *		m_pThrough;
	st_node *		m_pTail;
};
//------------------------------------------------------------------------
template < class T>
class CIndexArrayEx
{
	typedef struct	_node_
	{
		_node_()
		{
			data = NULL;
			nextfree = 0;
		}
		T		*		data;
		unsigned int	nextfree;
	}st_node;
	BOOL _Clean()
	{
		if( m_pArray == NULL )return FALSE;

		int	i = 0;
		for( i = 0;i <= MAXCOUNT;i ++ )
		{
			m_pArray[i].nextfree = i + 1;
		}

		m_pArray[MAXCOUNT].nextfree = 0;

		m_free = 1;
		m_totel = 0;
		m_bLocked = FALSE;
		return TRUE;
	}
	BOOL	IsCreated()
	{
		return ( m_pArray != NULL );
	}
public:
	int	GetMaxCount()
	{
		return MAXCOUNT;
	}
	int	GetFreeCount()
	{
		return MAXCOUNT - GetCount();
	}
	CIndexArrayEx()
	{
		m_pArray = NULL;
		MAXCOUNT = 0;
	}
	BOOL	Create( int maxcount )
	{
		if( m_pArray != NULL )
			Destroy();

		MAXCOUNT = (unsigned int)maxcount;
		m_pArray = new st_node[MAXCOUNT+1];
		if( !_Clean() )
		{
			delete [] m_pArray;
			return FALSE;
		}
		return TRUE;
	}
	VOID	Destroy()
	{
		if( !IsCreated() )return;
		for( int i = 0;i < MAXCOUNT;i ++ )
		{
			if( m_pArray[i].data != NULL )
				delete m_pArray[i].data;
		}
		delete []m_pArray;
	}
	VOID	Clean()
	{
		if( !IsCreated() )return;
		for( int i = 0;i <= MAXCOUNT;i ++ )
		{
			m_pArray[i].nextfree = i + 1;
		}
		m_pArray[MAXCOUNT].nextfree = 0;
		m_free = 1;
		m_totel = 0;
		m_bLocked = FALSE;

	}
	virtual ~CIndexArrayEx()
	{
		Destroy();
	}

public:
	unsigned int GetCount()
	{
		if( !IsCreated() )return 0;
		return m_totel;
	}
	VOID		Lock()
	{
		m_CriticalSection.Lock();
	}
	VOID		UnLock()
	{
		m_CriticalSection.Unlock();
	}
	unsigned int New( T ** t )
	{
		*t = NULL;
		if( !IsCreated() )return 0;
		unsigned int id = 0;
		id = AllocId();
		if( id == 0 || id > (unsigned int)MAXCOUNT )
			return 0;
		if( m_pArray[id].data == NULL )
			m_pArray[id].data = new T;

		*t = m_pArray[id].data;
		m_totel ++;
		return id;
	}
	int	Del( unsigned int id )
	{
		if( !IsCreated() )return 0;
		if( id > (unsigned int)MAXCOUNT || id == 0 )
			return 0;
		ResaveId( id );
		m_totel --;
		return 1;
	}
	T *	Get( unsigned int id )
	{
		if( !IsCreated() )return NULL;
		if( id == 0 )
			return NULL;
		if( id <= MAXCOUNT )
		{
			if( m_pArray[id].pnext == NULL && m_pArray[id].pprev == NULL )
				return NULL;
			return m_pArray[id].data;
		}
		return NULL;
	}
private:
	unsigned int AllocId()
	{
		if( !IsCreated() )return 0;
		unsigned int ret = m_free;
		if( ret != 0 )
			m_free = m_pArray[ret].nextfree;
		return ret;
	}
	int ResaveId( unsigned int id )
	{
		if( !IsCreated() )return 0;
		if( id > (unsigned int)MAXCOUNT || id == 0 )
			return 0;
		m_pArray[id].nextfree = m_free;
		m_free = id;
		return 1;
	}
private:
	int				MAXCOUNT;
	BOOL			m_bLocked;
	CriticalSection	m_CriticalSection;
	unsigned int	m_free;
	unsigned int	m_totel;
};
//------------------------------------------------------------------------
template < class T , int MAXCOUNT>
class CDataQueue  
{
public:
	unsigned int GetCount()
	{
		return (unsigned int )(( m_pPut + m_nMax - m_pGet )%m_nMax );
	}
	BOOL GetData(T *msg)
	{
		if(	msg == NULL)return FALSE;
		if( m_pGet == m_pPut) return FALSE;
		memcpy((void*)msg,(void*)&m_pdataqueue[m_pGet],sizeof( T ));
		m_pGet++;
		if( m_pGet >= m_nMAX ) m_pGet = 0;
		return TRUE;
	};
	BOOL PutData(T *msg)
	{
		if(msg == NULL)return FALSE;
		memcpy((void*)&m_pdataqueue[m_pPut],(void*)msg,sizeof( T ));
		m_pPut ++;
		if(m_pPut >= m_nMAX)m_pPut = 0;
		return TRUE;
	};
	void	Clear()				
	{
		m_pGet = 0;
		m_pPut = 0;
	}
	CDataQueue()
	{
		m_pdataqueue = new T[MAXCOUNT];
		m_nMAX = MAXCOUNT;
		m_pGet = 0;
		m_pPut = 0;
	};
	virtual ~CDataQueue()
	{
		if( m_pdataqueue != NULL )
			delete m_pdataqueue;
	};

private:
	int	m_pGet;
	int	m_pPut;
	T	* m_pdataqueue;
	int	m_nMAX;
};
//------------------------------------------------------------------------
#define	SSTRING_LENGTH	20
typedef CHAR SSTRING[SSTRING_LENGTH];
//------------------------------------------------------------------------
class CNameHash
{
	typedef struct	_2_hashnode
	{
		_2_hashnode *		pNext;
		LPVOID				data;
		SSTRING				key;
		UINT				id;
	}HashNode2;
	int c1;
public:
	CNameHash()
	{
		memset( (void*)m_HashData, 0, sizeof( HashNode2 ) * (0xffff+1) );
		m_Count = 0;
		c1 = 0;
	}
	~CNameHash()
	{
	}
	int GetC1(){return c1;}
protected:
	HashNode2	m_HashData[0xffff+1];
	int				m_Count;
	CIndexList<HashNode2, 0xffff>	m_HashDataMollocer;
private:
	HashNode2 * NewNode()
	{
		HashNode2 * p;
		UINT	id = m_HashDataMollocer.New(&p);
		if( id == 0)
			return 0;
		p->id = id;
		memset( (void*)p, 0, sizeof( HashNode2));
		c1++;
		return (p);
	}
	void DelNode( HashNode2 * pNode )
	{
		if( pNode == 0 )
			return;
		c1 --;
		m_HashDataMollocer.Del(pNode->id);
	}
	BOOL Del( HashNode2 * pNode)
	{
		return FALSE;
	}
	HashNode2 * FindLastByCode( const char * key, WORD wHashCode )
	{
		int time=0;
		HashNode2 * pNode = &m_HashData[wHashCode];
		while( (pNode->pNext != NULL) && time < 1000)
		{
			if( pNode->pNext->data != 0)
			{
				if( strncmp( key, pNode->pNext->key, SSTRING_LENGTH) == 0 )
				{
					return pNode;
				}
			}
			pNode = pNode->pNext;
			time ++;
		}
		return NULL;
	}
	HashNode2 * Find( const char * key )
	{
		WORD	wCode = MakeHashCode(key);
		return FindByCode(key, wCode);
	}
	HashNode2 * FindByCode( const char * key, WORD	wHashCode)
	{
		int time=0;
		HashNode2 * pNode = &m_HashData[wHashCode];
		while( (pNode != NULL) && time < 1000)
		{
			if( pNode->data != 0)
			{
				if( strncmp( key, pNode->key, SSTRING_LENGTH) == 0 )
				{
					return pNode;
				}
			}
			pNode = pNode->pNext;
			time ++;
		}
		return NULL;
	}
	WORD	MakeHashCode( const char * key)
	{
		int i = 0;
		DWORD	t = 0;
		char * pt = (char*)&t;
		while( key[i] )
		{
			pt[i&0x3] ^= key[i++];
		}
		return (WORD)(t%(0xffff+1));
	}
public:
	BOOL	HAdd( const char * key, LPVOID lpValue )
	{
		if( key == NULL )
			return FALSE;
		if( lpValue == NULL )
			return FALSE;
		WORD	wHashCode = MakeHashCode(key);
		if( FindByCode(key, wHashCode)!= NULL)
			return FALSE;
		HashNode2 * pNode = &m_HashData[wHashCode], * pNextNode = pNode->pNext;
		if( pNode->data != NULL )
		{
			pNode->pNext  = NewNode();
			if(!pNode->pNext)
				return FALSE;
			pNode = pNode->pNext;
			pNode->pNext = pNextNode;
		}
		strncpy( pNode->key, key, SSTRING_LENGTH);
		pNode->data = lpValue;
		m_Count ++;
		return TRUE;
	}
	BOOL	HDel(const  char * key )
	{
		HashNode2	* pNode;
		WORD	wCode = MakeHashCode(key);
		pNode = FindLastByCode(key, wCode);
		if( pNode == NULL )
		{
			if( strncmp( m_HashData[wCode].key, key, SSTRING_LENGTH ) == 0 )
			{
				m_HashData[wCode].data = 0;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			HashNode2 * p2 = pNode->pNext;
			pNode->pNext = pNode->pNext->pNext;
			p2->data = 0;
			DelNode( p2 );
		}
		m_Count --;
		return TRUE;
	}
	LPVOID HGet(const char * key )
	{
		WORD	wCode = MakeHashCode(key);
		HashNode2 * pNode = FindByCode(key, wCode);
		if( pNode != NULL )
			return pNode->data;
		return NULL;
	}
};
//------------------------------------------------------------------------
template <class T, int MaxCount>
class CDQueue
{
public:
	CDQueue()
	{
		Clean();
	}
	~CDQueue()
	{
		Clean();
	}
	int		GetBuffer( T * pt )
	{
		int count = GetCount();
		if(pt == 0 || count == 0)
			return count;
		if( m_bpass )
		{
			memcpy( pt, m_data, count * sizeof( T ) );
		}
		else
		{
			if( m_put > m_get )
				memcpy( pt, m_data + m_get , count * sizeof( T ));
			else
			{
				memcpy( pt, m_data + m_get , (MaxCount - m_get) * sizeof( T ));
				memcpy( pt + (MaxCount - m_get), m_data, m_put * sizeof( T ));
			}
		}
		return count;
	}
	BOOL	Push( T & t)
	{
		CLock m_lock(&m_CriticalSection);
		if( m_put == m_get && m_bpass )
			return FALSE;
		memcpy( &m_data[m_put], &t, sizeof( T ));
		m_put = ((m_put + 1)%MaxCount);
		if( m_put == m_get )
			m_bpass = TRUE;
		return TRUE;
	}
	BOOL	Pop( T & t)
	{
		CLock m_lock(&m_CriticalSection);
		if( m_put == m_get && m_bpass == FALSE )
			return FALSE;
		else
		{
			m_bpass = FALSE;
			memcpy( &t, &m_data[m_get], sizeof( T ));
			m_get = ((m_get + 1 )%MaxCount);
		}
		return TRUE;
	}
	int	GetCount()
	{
		CLock m_lock(&m_CriticalSection);
		if( m_get > m_put )
			return (MaxCount - m_get + m_put);
		if( m_put > m_get )
			return (m_put - m_get);
		if( m_put == m_get && m_bpass )
			return MaxCount;
		return 0;
	}
	VOID	Clean()
	{
		m_put = 0;
		m_get = 0;
		m_through = 0;
		memset( m_data, 0, sizeof( m_data ));
		m_bpass = FALSE;
	}
	VOID		Lock()
	{
		m_CriticalSection.Lock();
	}
	VOID		Unlock()
	{
		m_CriticalSection.Unlock();
	}
	BOOL	IsLocked()
	{
		if( m_CriticalSection.TryLock())
		{
			m_CriticalSection.Unlock();
			return TRUE;
		}
		return FALSE;
	}
	T * First()
	{
		m_through = m_get;
		if( GetCount() == 0 )
			return NULL;
		return &m_data[m_through];
	}
	T * Last()
	{
		if( GetCount() == 0 )
			return NULL;
		m_through = m_put - 1;
		if( m_put < 0 )
			m_put += MaxCount;
		return &m_data[m_through];
	}
	T * Next()
	{
		m_through ++;
		if( m_through >= MaxCount )
		{
			m_through = 0;
		}
		if( m_through == m_put )
		{
			return NULL;
		}
		return &m_data[m_through];
	}
private:
	CriticalSection	m_CriticalSection;
	T	m_data[MaxCount+1];
	BOOL	m_bpass;
	int	m_put;
	int	m_get;
	int	m_through;
};
//------------------------------------------------------------------------
template <class T>
class xListHost
{
public:
	class xListNode
	{
		xListNode * m_pNext;
		xListNode * m_pPrev;
		xListHost<T> * m_pHost;
		T * m_pObject;
	public:
		xListNode() :
		  m_pObject(NULL),m_pNext(NULL),m_pPrev(NULL),m_pHost(NULL)
		  {
		  }
		  xListNode( T * pObject ) : 
		  m_pObject(pObject),m_pNext(NULL),m_pPrev(NULL),m_pHost(NULL)
		  {

		  }
		  ~xListNode()
		  {
			  m_pNext = NULL;
			  m_pPrev = NULL;
			  m_pObject = NULL;
		  }
		  xListNode * getNext(){ return m_pNext;}
		  xListNode * getPrev(){ return m_pPrev;} 
		  xListHost<T> * getHost(){ return m_pHost;}
		  void	setObject( T * pObject ){ m_pObject = pObject;}
		  T * getObject(){ return m_pObject;}
		  void	setNext( xListNode * pNext ){ m_pNext = pNext;}
		  void	setPrev( xListNode * pPrev ){ m_pPrev = pPrev;}
		  void	setHost( xListHost<T> * pHost ){ m_pHost = pHost;}
		  BOOL	Leave()
		  {
			  if( m_pHost == NULL )return FALSE;
			  return m_pHost->removeNode( this );
		  }
		  BOOL	Enter( xListHost<T> * pHost )
		  {
			  return pHost->addNode( this );
		  }
		  BOOL	BelongTo( xListHost<T> * pHost )
		  {
			  return ( pHost == m_pHost );
		  }
	};
private:
	xListNode * m_pHead;
	int	m_iNodeCount;
public:
	xListHost() : m_pHead(NULL),m_iNodeCount(0){}
	xListHost(LPVOID pListener) : m_pHead(NULL),m_iNodeCount(0){}
	~xListHost(){}
	xListNode * getHead(){ return m_pHead;}

	BOOL	removeNode( xListNode * pNode )
	{ 
		if( pNode == NULL )return FALSE;
		if( pNode->getHost() != this )return FALSE;

		xListNode * pNext = pNode->getNext();
		xListNode * pPrev = pNode->getPrev();
		if( pNext != NULL )pNext->setPrev(pPrev);
		if( pPrev != NULL )pPrev->setNext(pNext);

		if( m_pHead == pNode )
			m_pHead = pNext;
		pNode->setNext(NULL);
		pNode->setPrev(NULL);
		pNode->setHost(NULL);
		m_iNodeCount--;
		assert(m_iNodeCount>=0);
		return TRUE;
	}
	BOOL	addNode( xListNode * pNode )
	{
		if( pNode == NULL )return FALSE;
		pNode->Leave();
		pNode->setHost(this);
		pNode->setPrev(NULL);
		pNode->setNext(m_pHead);
		if( m_pHead != NULL )
			m_pHead->setPrev(pNode);
		m_pHead = pNode;
		m_iNodeCount++;
		return TRUE;
	}

	int	getCount(){ return m_iNodeCount;}
};
//------------------------------------------------------------------------
template <class T>
class xListHelper
{
public:
	xListHelper( xListHost<T> * pList )
	{
		setList( pList );
	}

	xListHelper()
	{
		m_pList = NULL;
		m_pNode = NULL;
	}

	void setList( xListHost<T> * pList )
	{
		m_pList = pList;
		if( m_pList )
			m_pNode = m_pList->getHead();
	}

	xListHost<T> * getList()
	{
		return m_pList;
	}

	T * first()
	{
		if( m_pList == NULL )return NULL;
		m_pNode = m_pList->getHead();
		if( m_pNode )
		{
			T * pObject = m_pNode==NULL?NULL:m_pNode->getObject();
			m_pNode = m_pNode->getNext();
			return pObject;
		}
		return NULL;
	}

	T * next()
	{
		if( m_pList == NULL )return NULL;
		if( m_pNode )
		{
			T * pObject = m_pNode==NULL?NULL:m_pNode->getObject();
			m_pNode = m_pNode->getNext();
			return pObject;
		}
		return NULL;
	}

private:
	typename xListHost<T>::xListNode * m_pNode;
	typename xListHost<T> * m_pList;
};
//------------------------------------------------------------------------
template<class T>
class xPtrQueue
{
	T ** m_pQueue;
	BOOL	m_bFull;
	int		m_iPush;
	int		m_iPop;
	int	m_iMaxSize;
	THREAD_PROTECT_DEFINE;
public:
	xPtrQueue():m_iMaxSize(0),m_bFull(FALSE)
	{
		m_pQueue = NULL;
		m_iPush = 0;
		m_iPop = 0;
	}
	xPtrQueue(int size):m_iMaxSize(size),m_bFull(FALSE)
	{
		m_pQueue = NULL;
		create( size );
	}
	~xPtrQueue()
	{
		destroy();
	}

	BOOL	create( int nSize )
	{
		destroy();
		m_pQueue = new T*[nSize];
		m_iMaxSize = nSize;
		return TRUE;
	}

	VOID	destroy()
	{
		if( m_pQueue != NULL )
			delete []m_pQueue;
		m_pQueue = NULL;
		m_iPush = 0;
		m_iPop = 0;
		m_iMaxSize = 0;
		m_bFull = FALSE;
	}

	BOOL	push( T * p )
	{
		THREAD_PROTECT;
		if( p == NULL )return FALSE;
		if( m_bFull )return FALSE;

		m_pQueue[m_iPush++] = p;
		if( m_iPush >= m_iMaxSize )m_iPush = 0;
		if( m_iPush == m_iPop )m_bFull = TRUE;
		return TRUE;
	}

	T * pop()
	{
		THREAD_PROTECT;
		if( !m_bFull && m_iPush == m_iPop )return NULL;

		int p = m_iPop ++;
		m_bFull = FALSE;

		if( m_iPop >= m_iMaxSize )m_iPop = 0;
		return m_pQueue[p];
	}

	VOID clear()
	{
		THREAD_PROTECT;
		m_bFull = FALSE;
		m_iPush = 0;
		m_iPop = 0;
	}

	int getcount()
	{
		if( m_bFull )return m_iMaxSize;
		if( m_iPush < m_iPop )
			return (m_iPush + m_iMaxSize - m_iPop);
		return (m_iPush - m_iPop );
	}

};
//------------------------------------------------------------------------
template < class T > 
class xObjectPool
{
	typedef struct _object_desc_
	{
		_object_desc_():node(&object),dwFlag(POOLMEMORYFLAG)
		{
		}
		DWORD	dwFlag;
		typename xListHost<T>::xListNode  node;
		T object;
	}OBJECT_DESC;
public:
	xObjectPool()
		:m_xUsedObjects(NULL),m_xFreeObjects(NULL)
	{
		CacheObjects();
	}
	T * newObject()
	{
		THREAD_PROTECT;
		if( m_xFreeObjects.getCount() == 0 )
		{
			OBJECT_DESC * pObject = NewObjectDesc();
			m_xUsedObjects.addNode( &pObject->node );
			return &pObject->object;
		}
		else
		{
			xListHost<T>::xListNode * pNode = m_xFreeObjects.getHead();
			if( pNode == NULL )
				return NULL;
			m_xFreeObjects.removeNode( pNode );
			m_xUsedObjects.addNode( pNode );
			return pNode->getObject();
		}
		return NULL;
	}
	VOID deleteObject( T * pObject )
	{
		THREAD_PROTECT;
		BYTE * pStart = (BYTE*)pObject;
		pStart -= sizeof( xListHost<T>::xListNode )+sizeof( DWORD );
		OBJECT_DESC * pObjectDesc = (OBJECT_DESC*)pStart;
		if( pObjectDesc->dwFlag != POOLMEMORYFLAG )return;
		m_xUsedObjects.removeNode( &pObjectDesc->node );
		m_xFreeObjects.addNode( &pObjectDesc->node );
	}
	int	getCount()
	{
		return (m_xUsedObjects.getCount() + m_xFreeObjects.getCount());
	}
	int	getFreeCount()
	{
		return m_xFreeObjects.getCount();
	}
	int	getUsedCount()
	{
		return m_xUsedObjects.getCount();
	}
	typename xListHost<T>::xListNode * GetUsedHeadNode()
	{
		return m_xUsedObjects.getHead();
	}
	typename xListHost<T>::xListNode * GetFreeHeadNode()
	{
		return m_xFreeObjects.getHead();
	}
private:
	CriticalSection	m_CriticalSection;
	OBJECT_DESC * NewObjectDesc()
	{
		if( m_nCachePtr >= m_nCacheSize )
			CacheObjects();
		return &m_pCache[m_nCachePtr++];
	}
	VOID CacheObjects()
	{
		m_nCacheSize = OBJECTPOOLCACHESIZE > sizeof( OBJECT_DESC )?4:(OBJECTPOOLCACHESIZE+sizeof( OBJECT_DESC)-1)/sizeof(OBJECT_DESC);
		m_pCache = new OBJECT_DESC[m_nCacheSize];
		m_nCachePtr = 0;
	}
	OBJECT_DESC * m_pCache;
	UINT	m_nCachePtr;
	UINT	m_nCacheSize;
	xListHost<T> m_xUsedObjects;
	xListHost<T> m_xFreeObjects;
};
//------------------------------------------------------------------------
template<class T>
class xAutoPtrArray
{
public:
	xAutoPtrArray( UINT max )
	{
		m_pArray = NULL;
		Create( max );
	}
	xAutoPtrArray()
	{
		m_pArray = NULL;
		m_iMax = 0;
		m_iCount = 0;
	}
	~xAutoPtrArray()
	{
		m_iMax = 0;
		m_iCount = 0;
		delete []m_pArray;
	}
	BOOL	Create( UINT max )
	{
		m_pArray = new T*[max];
		m_iMax = max;
		Clean();
		return TRUE;
	}
	VOID Clean()
	{
		if( m_pArray != NULL )
			memset( m_pArray, 0, sizeof( T *) * m_iMax );
		m_iCount = 0;
	}
	UINT Add( T * pt )
	{
		if( m_iCount == m_iMax )return (UINT)-1;
		m_pArray[m_iCount++] = pt;
		return (m_iCount -1);
	}
	T * Get( UINT index )
	{
		if( index >= m_iCount )
			return NULL;
		return m_pArray[index];
	}
	BOOL Del( T * pt )
	{
		for( UINT i = 0;i < m_iCount;i ++ )
		{
			if( m_pArray[i] == pt )
			{
				return Del( i );
			}
		}
		return FALSE;
	}
	BOOL Del( UINT index )
	{
		if( index >= m_iCount )return FALSE;
		m_iCount --;
		UINT ileft = m_iCount - index;
		if( ileft > 0 )
		{
			memmove( m_pArray + index, m_pArray+index+1, sizeof( T * ) * ileft );
		}
		return TRUE;
	}
	T * operator []( UINT index )
	{
		return Get( index );
	}
	UINT	GetCount(){return m_iCount;}
	UINT operator  [] ( T * pt )
	{
		for( UINT i = 0;i < m_iCount;i++)
		{
			if( m_pArray[i] == pt )
				return i;
		}
		return (UINT)-1;
	}
	UINT	GetMaxCount(){ return m_iMax;}

	BOOL Insert( T * pt, UINT Index = 0 )
	{
		if( Index >= m_iCount )return (Add( pt )!=0xffffffff);
		if( m_iCount >= m_iMax )return FALSE;
		memmove( m_pArray + Index+1, m_pArray + Index, sizeof( T* ) * (m_iCount - Index) );
		m_pArray[Index] = pt;
		m_iCount++;
		return TRUE;
	}

	BOOL ResetSize(UINT size)
	{
		T ** pArray = m_pArray;
		int iCount = m_iCount;

		Create(size);

		for( UINT i = 0;i < iCount;i++)
		{
			Add(pArray[i]);
		}

	}
private:
	T ** m_pArray;
	UINT	m_iCount;
	UINT	m_iMax;
};
//------------------------------------------------------------------------