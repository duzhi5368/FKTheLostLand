/**
*	created:		2013-4-16   0:59
*	filename: 		xTime
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#define MAXTIME	(DWORD(0xffffffff))
//------------------------------------------------------------------------
//是否闰年
inline	BOOL	IsRunYear( int Year )
{
	if( (Year % 100) == 0 )
	{
		if((Year % 400 ) != 0 )
			return FALSE;
		return TRUE;
	}
	else if( (Year & 0x3 ) != 0 )
		return FALSE;
	return TRUE;
}
//------------------------------------------------------------------------
// 计算两个时间点之间经过了多少秒
DWORD	GetT1toT2Second( SYSTEMTIME & t1, SYSTEMTIME & t2 );
//------------------------------------------------------------------------
// 转换字符串为时间
inline VOID	GetTimeFromString( SYSTEMTIME & t, const char * pszString )
{
	try
	{
		char temp[10];
		sscanf( pszString, "%hu %hu %hu %hu:%hu%s", &t.wMonth, &t.wDay, &t.wYear, &t.wHour, &t.wMinute, temp);
		if(strcmp(temp,"AM") == 0)
		{

		}else if(strcmp(temp,"PM") == 0)
		{
			t.wHour +=12;
		}
	}
	catch(...)
	{
		memset( &t, 0, sizeof( t ) );
	}
}
//------------------------------------------------------------------------
// 获取某年某月内的天数
inline WORD	GetMonthDays( WORD year, WORD month )
{
	static WORD wDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if( month == 0 || month > 12 )return 0;
	WORD	wRet = wDays[month-1];
	if( month == 2 && IsRunYear( year ) )
		wRet ++;
	return wRet;
}
//------------------------------------------------------------------------
// 系统时间的封装
class CSystemTime
{
private:
	SYSTEMTIME	m_stTime;
public:
	WORD	GetYear(){return m_stTime.wYear;}
	WORD	GetMonth(){return m_stTime.wMonth;}
	WORD	GetDay(){return m_stTime.wDay;}
	WORD	GetHour(){return m_stTime.wHour;}
	WORD	GetMinute(){return m_stTime.wMinute;}
	WORD	GetSecond(){return m_stTime.wSecond;}
	WORD	GetMilliSeconds(){return m_stTime.wMilliseconds;}
	WORD	GetDayOfWeek(){ return m_stTime.wDayOfWeek;}
	CSystemTime( CSystemTime & st )
	{
		m_stTime = st.m_stTime;
	}
	CSystemTime( SYSTEMTIME & st )
	{
		ZeroMemory( &m_stTime, sizeof( SYSTEMTIME ));
		m_stTime = st;
	}
	CSystemTime( const char * pszString )
	{
		ZeroMemory( &m_stTime, sizeof( SYSTEMTIME ));
		GetTimeFromString(m_stTime, pszString );
	}
	CSystemTime()
	{
		ZeroMemory( &m_stTime, sizeof( SYSTEMTIME ));
		GetLocalTime( &m_stTime );
	}
	DWORD	GetToTimeSecond( CSystemTime & st )
	{
		return GetT1toT2Second(m_stTime, st.m_stTime);
	}
	CSystemTime & operator +(DWORD time)//time的时间单位是秒
	{
		m_stTime.wSecond += time;
		time = m_stTime.wSecond / 60 ;
		m_stTime.wSecond %= 60;

		m_stTime.wMinute += time;
		time = m_stTime.wMinute / 60 ;
		m_stTime.wMinute %= 60;

		m_stTime.wHour += time;
		time = m_stTime.wHour / 12 ;
		m_stTime.wHour %= 12;

		//只加到小时，避开应天数月份的计算。
		return (*this);
	}
	CSystemTime & operator =( SYSTEMTIME & st )
	{
		m_stTime = st;
		return (*this);
	}
	CSystemTime & operator =( CSystemTime & st )
	{
		m_stTime = st.m_stTime;
		return (*this);
	}
	CSystemTime & operator =( const char * pszString )
	{
		GetTimeFromString(m_stTime, pszString );
		return (*this);
	}
	BOOL	operator ==( CSystemTime & _st )
	{
		SYSTEMTIME & st = _st.m_stTime;
		if( m_stTime.wMilliseconds != st.wMilliseconds )return FALSE;
		if( m_stTime.wSecond != st.wSecond )return FALSE;
		if( m_stTime.wMinute != st.wMinute )return FALSE;
		if( m_stTime.wHour != st.wHour )return FALSE;
		if( m_stTime.wDay != st.wDay )return FALSE;
		if( m_stTime.wMonth != st.wMonth )return FALSE;
		if( m_stTime.wYear != st.wYear )return FALSE;
		return TRUE;
	}
	BOOL	operator > ( CSystemTime & _st )
	{
		SYSTEMTIME	& st = _st.m_stTime;
		if( m_stTime.wYear != st.wYear )return (m_stTime.wYear > st.wYear);
		if( m_stTime.wMonth != st.wMonth )return (m_stTime.wMonth > st.wMonth);
		if( m_stTime.wDay != st.wDay )return (m_stTime.wDay > st.wDay);
		if( m_stTime.wHour != st.wHour )return (m_stTime.wHour > st.wHour);
		if( m_stTime.wMinute != st.wMinute )return (m_stTime.wMinute > st.wMinute);
		if( m_stTime.wSecond != st.wSecond )return (m_stTime.wSecond > st.wSecond);
		if( m_stTime.wMilliseconds != st.wMilliseconds )return (m_stTime.wMilliseconds > st.wMilliseconds);
		return FALSE;
	}
	BOOL	operator < (CSystemTime & _st )
	{
		SYSTEMTIME	& st = _st.m_stTime;
		if( m_stTime.wYear != st.wYear )return (m_stTime.wYear < st.wYear);
		if( m_stTime.wMonth != st.wMonth )return (m_stTime.wMonth < st.wMonth);
		if( m_stTime.wDay != st.wDay )return (m_stTime.wDay < st.wDay);
		if( m_stTime.wHour != st.wHour )return (m_stTime.wHour < st.wHour);
		if( m_stTime.wMinute != st.wMinute )return (m_stTime.wMinute < st.wMinute);
		if( m_stTime.wSecond != st.wSecond )return (m_stTime.wSecond < st.wSecond);
		if( m_stTime.wMilliseconds != st.wMilliseconds )return (m_stTime.wMilliseconds < st.wMilliseconds);
		return FALSE;
	}
	BOOL	operator >= ( CSystemTime & _st )
	{
		return !(operator <( _st ));
	}
	BOOL	operator <= ( CSystemTime & _st )
	{
		return !(operator > (_st) );
	}
	BOOL	operator != ( CSystemTime & _st )
	{
		return !(operator == (_st ));
	}
	VOID GetDesc(char* date)
	{
		//06  5 2009 10:18AM
		if(m_stTime.wHour >= 12)
		{
			sprintf(date,"%2d %2d %4d %2d:%02dPM",m_stTime.wMonth,m_stTime.wDay, m_stTime.wYear, m_stTime.wHour - 12, m_stTime.wMinute);
		}
		else
		{
			sprintf(date,"%2d %2d %4d %2d:%02dAM",m_stTime.wMonth,m_stTime.wDay, m_stTime.wYear, m_stTime.wHour, m_stTime.wMinute);
		}
	}

	string GetDescEx()
	{
		//2009年12月10日17点25分
		char buf[256];
		sprintf(buf, "%d年%d月%d日%d时%d分", m_stTime.wYear, m_stTime.wMonth, m_stTime.wDay, m_stTime.wHour, m_stTime.wMinute);
		return buf;
	}
};
//------------------------------------------------------------------------
inline DWORD GetTimeToTime(DWORD t1,DWORD t2 )
{
	return (t1<=t2?(t2-t1):(MAXTIME-t1+t2));
}
//------------------------------------------------------------------------
class CServerTimer
{
public:
	CServerTimer():m_dwSavedTime(0),m_dwTimeoutTime(0)
	{
	}
	static inline DWORD	GetTime()
	{
		return timeGetTime();
	}
	VOID	Savetime()
	{
		m_dwSavedTime = timeGetTime();
	}
	VOID Savetime( DWORD newTimeOut )
	{
		SetTimeOut( newTimeOut );
		Savetime();
	}
	static BOOL	IsTimeOut( DWORD starttime, DWORD timeout )
	{
		DWORD	dwTime = timeGetTime();
		if( GetTimeToTime(starttime, dwTime)+m_dwAllowTimeJump >= timeout )
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOL	IsTimeOut( DWORD dwTimeOut )
	{
		DWORD	dwTime = timeGetTime();
		if( GetTimeToTime(m_dwSavedTime, dwTime)+m_dwAllowTimeJump >= dwTimeOut )
		{
			return TRUE;
		}
		return FALSE;
	}
	VOID	SetTimeOut( DWORD	dwTimeOut)
	{
		m_dwSavedTime = timeGetTime();
		m_dwTimeoutTime = dwTimeOut;
	}
	BOOL	IsTimeOut()
	{
		DWORD	dwTime = timeGetTime();
		if( GetTimeToTime(m_dwSavedTime, dwTime)+m_dwAllowTimeJump>= m_dwTimeoutTime )
			return TRUE;
		return FALSE;
	}
	DWORD	GetTimeOut(){ return m_dwTimeoutTime;}
	DWORD	GetSavedTime(){ return m_dwSavedTime;}
	VOID	SetSavedTime( DWORD dwTime ){ m_dwSavedTime = dwTime;}

	static DWORD GetTimeJump(){ return m_dwAllowTimeJump;}
	static VOID	SetTimeJump( DWORD dwTimeJump ){ m_dwAllowTimeJump = dwTimeJump;}

	// 距离上次保存，过了多少时间
	DWORD   GetTimeFromSave()
	{
		return (GetTimeToTime(m_dwSavedTime, timeGetTime()));
	}

private:
	static DWORD m_dwAllowTimeJump;
	DWORD	m_dwSavedTime;
	DWORD	m_dwTimeoutTime;
};
//------------------------------------------------------------------------