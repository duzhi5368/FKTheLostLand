/**
*	created:		2013-4-16   1:18
*	filename: 		xIdMaker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
template < int MAXCOUNT>
class CIdMaker
{
public:
	CIdMaker()
	{
		int i = 0;
		for( i = 0;i < MAXCOUNT;i ++ )
		{
			m_NextFree[i] = i + 1;
		}
		m_NextFree[MAXCOUNT] = 0;
		m_Free = 0;
	}
	~CIdMaker()
	{

	}
	int	GetId()
	{
		int retid = m_Free +1;
		if( retid <= 0 || retid > MAXCOUNT )
			return 0;
		m_Free = m_NextFree[m_Free];
		return retid;
	}
	BOOL DelId( int id )
	{
		if( id <= 0 || id > MAXCOUNT )
			return FALSE;
		m_NextFree[id-1] = m_Free;
		m_Free = id -1;
		return TRUE;
	}
private:
	int	m_Free;
	int m_NextFree[MAXCOUNT + 1];
};
//------------------------------------------------------------------------