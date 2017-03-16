/**
*	created:		2013-4-16   4:26
*	filename: 		xStringsExpander
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
template<int maxindex>
class xStringsExpander
{
public:
	xStringsExpander( char * pszString, int Delim )
	{
		m_iCount = SearchParam( pszString, m_pStrings, maxindex, Delim );
	}
	const char * getString( int index )
	{
		if( index >= m_iCount || index < 0 )return NULL;
		return m_pStrings[index];
	}

	int getCount(){ return m_iCount;}

	const char * operator []( int index )
	{
		return getString( index );
	}
private:
	char	*	m_pStrings[maxindex];
	int	m_iCount;
};
//------------------------------------------------------------------------