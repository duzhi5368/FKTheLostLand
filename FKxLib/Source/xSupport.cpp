/**
*	created:		2013-4-16   0:44
*	filename: 		xSupport
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xsupport.h"
//------------------------------------------------------------------------
DWORD CServerTimer::m_dwAllowTimeJump = 0;
//------------------------------------------------------------------------
#define STONEDAY		86400
#define STONEYEAR299	31622400
#define	STONEYEARNO299	31536000 
//------------------------------------------------------------------------
static DWORD	stMonth_no299[12] = 
{
		0,													//	1
		STONEDAY * (31),									//	2
		STONEDAY * (31+28),									//	3
		STONEDAY * (31+28+31),								//	4
		STONEDAY * (31+28+31+30),							//	5
		STONEDAY * (31+28+31+30+31),						//	6
		STONEDAY * (31+28+31+30+31+30),						//	7
		STONEDAY * (31+28+31+30+31+30+31),					//	8
		STONEDAY * (31+28+31+30+31+30+31+31),				//	9
		STONEDAY * (31+28+31+30+31+30+31+31+30),			//	10
		STONEDAY * (31+28+31+30+31+30+31+31+30+31),			//	11
		STONEDAY * (31+28+31+30+31+30+31+31+30+31+30),		//	12
};
//------------------------------------------------------------------------
static DWORD	stMonth_299[12] = 
{
	0,														//	1
		STONEDAY * (31),									//	2
		STONEDAY * (31+29),									//	3
		STONEDAY * (31+29+31),								//	4
		STONEDAY * (31+29+31+30),							//	5
		STONEDAY * (31+29+31+30+31),						//	6
		STONEDAY * (31+29+31+30+31+30),						//	7
		STONEDAY * (31+29+31+30+31+30+31),					//	8
		STONEDAY * (31+29+31+30+31+30+31+31),				//	9
		STONEDAY * (31+29+31+30+31+30+31+31+30),			//	10
		STONEDAY * (31+29+31+30+31+30+31+31+30+31),			//	11
		STONEDAY * (31+29+31+30+31+30+31+31+30+31+30),		//	12
};
//------------------------------------------------------------------------
DWORD	GetT1toT2Second( SYSTEMTIME & t1, SYSTEMTIME & t2 )
{
	DWORD	st1 = 0,st2 = 0;
	if( t1.wYear == t2.wYear )
	{
		if( IsRunYear(t1.wYear))
		{
			st1 = stMonth_299[t1.wMonth-1] + (t1.wDay-1) * STONEDAY + (t1.wHour) * 3600 + (t1.wMinute) * 60 + t1.wSecond;
			st2 = stMonth_299[t2.wMonth-1] + (t2.wDay-1) * STONEDAY + (t2.wHour) * 3600 + (t2.wMinute) * 60 + t2.wSecond;
		}
		else
		{
			st1 = stMonth_no299[t1.wMonth-1] + t1.wDay * STONEDAY + t1.wHour * 3600 + t1.wMinute * 60 + t1.wSecond;
			st2 = stMonth_no299[t2.wMonth-1] + t2.wDay * STONEDAY + t2.wHour * 3600 + t2.wMinute * 60 + t2.wSecond;
		}
		st2 -= st1;
		//	计算t1过了一年的多少秒，t2过了多少秒，然后t2 - t1;
	}
	else
	{
		//	计算t1这一年剩下多少秒，t2过了一年的多少秒，t1+t2

		if( IsRunYear(t1.wYear))
			st1 = STONEYEAR299 - (stMonth_299[t1.wMonth-1] + (t1.wDay-1) * STONEDAY + (t1.wHour) * 3600 + (t1.wMinute) * 60 + t1.wSecond);
		else
			st1 = STONEYEARNO299 - (stMonth_no299[t1.wMonth-1] + (t1.wDay-1) * STONEDAY + (t1.wHour) * 3600 + (t1.wMinute) * 60 + t1.wSecond);
		if( IsRunYear(t2.wYear))
			st2 = (stMonth_299[t2.wMonth-1] + (t2.wDay-1) * STONEDAY + (t2.wHour) * 3600 + (t2.wMinute) * 60 + t2.wSecond);
		else
			st2 = (stMonth_no299[t2.wMonth-1] + (t2.wDay-1) * STONEDAY + (t2.wHour) * 3600 + (t2.wMinute) * 60 + t2.wSecond);
		st2 += st1;
		for( int i = t1.wYear+1;i < t2.wYear;i ++ )
		{
			if( IsRunYear(i))
				st2 += STONEYEAR299;
			else
				st2 += STONEYEARNO299;
		}

	}
	return st2;
}
//------------------------------------------------------------------------