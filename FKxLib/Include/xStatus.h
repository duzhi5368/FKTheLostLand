/**
*	created:		2013-4-16   4:50
*	filename: 		xStatus
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
const int MAX_FLAG_NUM = 5;
const int MAX_FLAG_LEN = 32;
const int MAX_STATUS_NUM = MAX_FLAG_NUM * MAX_FLAG_LEN;
const int MAX_STATUS_PARAM = 4;
//------------------------------------------------------------------------
class xStatus
{
private:
	DWORD	m_dwFlag[MAX_FLAG_NUM];
	DWORD	m_dwParam[MAX_STATUS_NUM][MAX_STATUS_PARAM];
	DWORD	m_dwLastTime[MAX_STATUS_NUM];
	CServerTimer	m_timer[MAX_STATUS_NUM];
public:
	xStatus()
	{
		memset( this, 0, sizeof( *this ) );
	}

	DWORD	GetFlag(int idx)
	{
		if(idx >= 0 && idx < MAX_FLAG_NUM)
			return m_dwFlag[idx];

		return 0;
	}

	VOID	AddTime( int index, DWORD dwTime )
	{
		if( IsSeted(index ) )
		{
			m_dwLastTime[index] += dwTime;
		}
	}

	VOID DecTime( int index, DWORD dwTime )
	{
		if( IsSeted( index ) )
		{
			if( m_dwLastTime[index] > dwTime )
				m_dwLastTime[index] -= dwTime;
			else
				m_dwLastTime[index] = 1000;	//°°±£¡Ù£±√Î÷”
		}
	}

	DWORD	GetParam(int index, int paramIdx = 0)
	{
		if(paramIdx < 0 || paramIdx >= MAX_STATUS_PARAM)
			return 0;

		if( !IsSeted(index))
			return 0;

		return m_dwParam[index][paramIdx];
	}

	VOID	SetParam( int index, DWORD dwParam0 = 0,  DWORD dwParam1 = 0, DWORD dwParam2 = 0, DWORD dwParam3 = 0 )
	{
		m_dwParam[index][0] = dwParam0;
		m_dwParam[index][1] = dwParam1;
		m_dwParam[index][2] = dwParam2;
		m_dwParam[index][3] = dwParam3;
	}

	VOID Clean(){ memset( this, 0, sizeof( *this ) );}

	BOOL SetStatus( int index, DWORD dwLastTime = 0, DWORD dwParam0 = 0, DWORD dwParam1 = 0, DWORD dwParam2 = 0, DWORD dwParam3 = 0 )
	{
		if( index < 0 || index >= MAX_STATUS_NUM )
			return FALSE;

		int flagIdx = index / MAX_FLAG_LEN;

		DWORD	f = (1<<(index % MAX_FLAG_LEN));
		m_dwFlag[flagIdx] |= f;
		
		m_dwLastTime[index] = dwLastTime;
		m_timer[index].Savetime();
		SetParam(index, dwParam0, dwParam1, dwParam2, dwParam3);

		return TRUE;
	}

	BOOL ClrStatus( int index )
	{
		if( index < 0 || index >= MAX_STATUS_NUM )
			return FALSE;

		int flagIdx = index / MAX_FLAG_LEN;

		DWORD	f = (1<<(index % MAX_FLAG_LEN));
		if( m_dwFlag[flagIdx] & f )
			m_dwFlag[flagIdx] ^= f;
		return TRUE;
	}

	BOOL IsSeted( int index )
	{
		if( index < 0 || index >= MAX_STATUS_NUM )
			return FALSE;

		int flagIdx = index / MAX_FLAG_LEN;

		DWORD	f = (1<<(index % MAX_FLAG_LEN));
		return ((m_dwFlag[flagIdx] & f ) != 0 );
	}

	BOOL IsTimeOut( int index )
	{
		if( !IsSeted( index ) )return FALSE;
		if( m_dwLastTime[index] == 0xffffffff )return FALSE;
		return m_timer[index].IsTimeOut(m_dwLastTime[index]);
	}

	//  £”‡ ±º‰
	DWORD GetTimeOut( int index )
	{
		if( !IsSeted(index)) return 0;
		if( m_dwLastTime[index] == 0xffffffff)return 0;
		DWORD dwTimeOut = GetTimeToTime( m_timer[index].GetSavedTime(), timeGetTime() );
		if( m_dwLastTime[index] > dwTimeOut )
			return (m_dwLastTime[index] - dwTimeOut);
		return 0;
	}

	BOOL SetStatusTime(int index,DWORD time)
	{
		if( !IsSeted(index) ) return FALSE;
		m_dwLastTime[index] = time;
		m_timer[index].Savetime();
		return TRUE;
	}
};
//------------------------------------------------------------------------