/**
*	created:		2013-4-16   4:54
*	filename: 		xTimeTick
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "time.h"
//------------------------------------------------------------------------
#define SECOND_PER_DAY	(86400)
#define SECOND_PER_HOUR	(3600)
#define SECOND_PER_MIN	(60)
#define MAX_TIME_TICK	(1514735999)
//------------------------------------------------------------------------
inline
unsigned long GetCurrentTimeTick()
{
	return (unsigned long)time(NULL);
}
//------------------------------------------------------------------------
inline
unsigned long GetTimeTick(int year, int month, int day, int hour, int min, int sec)
{
	tm t = {sec, min, hour, day, month - 1, year - 1900};

	return (unsigned long)mktime(&t);
}
//------------------------------------------------------------------------
inline//年年月月日日时时分分
unsigned long GetTimeTick(int dateTime)
{
	int year  = dateTime / 100000000 + 2000;
	int month = dateTime / 1000000 % 100;
	int day   = dateTime / 10000 % 100;
	int hour  = dateTime / 100 % 100;
	int min	  = dateTime % 100;
	return GetTimeTick(year, month, day, hour, min, 0);
}
//------------------------------------------------------------------------
inline
void GetDateTimeFromTimeTick(unsigned long timeTick, int& year, int& month, int& day, int& hour, int& min, int& sec)
{
	static unsigned long YEAR2008_2018[] = {1199116800, 1230739200, 1262275200, 1293811200, 1325347200, 1356969600, 1388505600, 1420041600, 1451577600, 1483200000, 1514736000};
	static unsigned long LEAPY_MON_TICK[] = {2678400, 2505600, 2678400, 2592000, 2678400, 2592000, 2678400, 2678400, 2592000, 2678400, 2592000, 2678400};
	static unsigned long NLEAPY_MON_TICK[] = {2678400, 2419200, 2678400, 2592000, 2678400, 2592000, 2678400, 2678400, 2592000, 2678400, 2592000, 2678400};

	int delta_year = 0;
	while(timeTick >= YEAR2008_2018[delta_year])delta_year++;
	year = 2007 + delta_year;

	unsigned long left_tick = timeTick - YEAR2008_2018[delta_year-1];
	unsigned long* pTick = NULL;
	if (0 == year % 4)
	{
		pTick = LEAPY_MON_TICK;
	}
	else
	{
		pTick = NLEAPY_MON_TICK;
	}

	for (int i = 0; i < sizeof(LEAPY_MON_TICK)/sizeof(LEAPY_MON_TICK[0]); i++)
	{
		if (left_tick > pTick[i])
		{
			left_tick -= pTick[i];
		}
		else
		{
			month = i + 1;
			break;
		}
	}

	day = 1;
	while(left_tick >= 86400)
	{
		left_tick -= 86400;
		day++;
	}

	hour = 0;
	while(left_tick >= 3600)
	{
		left_tick -= 3600;
		hour++;
	}

	min = 0;
	while(left_tick >= 60)
	{
		left_tick -= 60;
		min++;
	}

	sec = left_tick;
}
//------------------------------------------------------------------------
inline//2009年12月10日17点25分
string GetDescFromTimeTick(DWORD timeTick)
{
	int y, m, d, h, min, s;
	GetDateTimeFromTimeTick(timeTick, y, m, d, h, min, s);

	char buf[256];
	sprintf(buf, "%d年%d月%d日%d时%d分", y, m, d, h, min);

	return buf;
}
//------------------------------------------------------------------------
inline
unsigned long DiffDayFromTick(unsigned long t1, unsigned long t2)// t1-t2
{
	if(t1 < t2)
		return 0;

	unsigned long diff = t1 - t2;
	return diff / 86400;
}
//------------------------------------------------------------------------
inline
unsigned long DiffHourFromTick(unsigned long t1, unsigned long t2)
{
	if(t1 < t2)
		return 0;

	return (t1 - t2)/3600;
}
//------------------------------------------------------------------------
inline
unsigned long DiffMinFromTick(unsigned long t1, unsigned long t2)
{
	if(t1 < t2)
		return 0;

	return (t1 - t2) / 60;
}
//------------------------------------------------------------------------
inline
unsigned long DiffSecFromTick(unsigned long t1, unsigned long t2)
{
	if(t1 < t2)
		return 0;

	return (t1 - t2);
}
//------------------------------------------------------------------------