/**
*	created:		2013-4-16   1:18
*	filename: 		xIntHash
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
template < int maxcount >
class CIntHash
{
	typedef struct __IHNode
	{
		__IHNode *	pNext;
		int		ivalue;
		int		iptr;
		USHORT	flag;
		USHORT	High;
	}IHNode,*PIHNode;
public:
	BOOL HAdd( int ikey, int ivalue )
	{
		USHORT	s1 = ikey & 0xffff;
		USHORT	s2 = (ikey & 0xffff0000) >> 16;
		PIHNode	pnode;
		int p;
		int		timecnt = 0;
		if( m_HashBuffer[s1].flag == 0 )
		{
			m_HashBuffer[s1].ivalue = ivalue;
			m_HashBuffer[s1].High = s2;
			m_HashBuffer[s1].flag = 1;
		}
		else
		{
			pnode = &m_HashBuffer[s1];
			while( pnode->pNext != NULL )
			{
				timecnt ++;
				if( timecnt >= 1000 )
					return FALSE;
				pnode = pnode->pNext;
			}
			p = m_IdMaker.GetId();
			pnode->pNext = &m_HashNodes[p];
			m_HashNodes[p].iptr = p;
			pnode->pNext->flag = 1;
			pnode->pNext->ivalue = ivalue;
			pnode->pNext->High = s2;
			pnode->pNext->pNext = NULL;
		}
		return TRUE;

	};
	PIHNode Find( int ikey )
	{
		USHORT	s1 = ikey & 0xffff;
		USHORT	s2 = (ikey & 0xffff0000) >> 16;
		int timecnt = 0;
		PIHNode pnode;
		pnode = &m_HashBuffer[s1];
		while( NULL != pnode )
		{
			timecnt ++;
			if( timecnt >= 1000 )
				return NULL;
			if( pnode->flag != 0 )
			{
				if( pnode->High == s2 )
				{
					return pnode;
				}
			}
			pnode = pnode->pNext;
		}
		return NULL;
	};
	int HGet( int ikey )
	{
		PIHNode pnode = Find( ikey );
		if( pnode == NULL )
			return 0;
		return pnode->ivalue;
	};
	int HDel( int ikey )
	{
		USHORT	s1 = ikey & 0xffff;
		USHORT	s2 = (ikey & 0xffff0000) >> 16;
		int timecnt = 0;
		PIHNode pnode,pnode2 = NULL;
		pnode = &m_HashBuffer[s1];
		while( NULL != pnode )
		{
			timecnt ++;
			if( timecnt >= 1000 )
				return FALSE;
			if( pnode->flag != 0 )
			{
				if( pnode->High == s2 )
				{
					if( pnode2 == NULL )
					{
						pnode->flag = 0;
						pnode->High = 0;
						pnode->ivalue = 0;
					}
					else
					{
						pnode2->pNext = pnode->pNext;
						m_IdMaker.DelId( pnode->iptr );
					}
					return TRUE;
				}
			}
			pnode2 = pnode;
			pnode = pnode->pNext;
		}
		return FALSE;
	};
	CIntHash()
	{
		memset( (void*)m_HashBuffer, 0, sizeof( IHNode ) * (0xffff+1) );
	};
	~CIntHash()
	{
	};
private:
	IHNode	m_HashBuffer[0xffff+1];
	IHNode	m_HashNodes[maxcount+1];
	CIdMaker<maxcount>	m_IdMaker;
};
//------------------------------------------------------------------------