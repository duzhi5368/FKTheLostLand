/**
*	created:		2013-4-16   1:07
*	filename: 		xRand
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
// 获取一个指定值内的随机数
inline int Getrand(int base = 0)
{ 
	int value = ((rand() & 0xffff) << 16) | (rand() & 0xffff );
	if( base == 0 )
		return 0;
	return (value%base);
}
//------------------------------------------------------------------------
inline int Getrand( int base, int count )
{
	int i = 0;
	int sum = 0;
	if( count == 0 )
	{
		count = 1;
	}
	for( i = 0;i < count;i ++ )
	{
		sum += Getrand( base );
	}
	return ( sum / count );
}
//------------------------------------------------------------------------
inline int	GetRangeRand( int r1, int r2 )
{
	int rr = r1;
	if( r2 < r1 )r1 = r2, r2 = rr;
	return (r1+Getrand( r2 - r1+1));
}
//------------------------------------------------------------------------