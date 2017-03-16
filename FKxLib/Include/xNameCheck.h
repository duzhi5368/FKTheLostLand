/**
*	created:		2013-4-16   4:47
*	filename: 		xNameCheck
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
inline BOOL xCheckCharname( const char * pszName )
{
	char * p = (char*)pszName;
	while( *p )
	{
		if( *p < 0 )
		{
			if( *(p+1) != 0 )
			{
				p++;
			}
			else
				return FALSE;
		}
		else
		{
			if( *p <= 32 )
				return FALSE;
			if( *p == '\'' || *p == '\"' )
				return FALSE;
		}
		p++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL xCheckAccount( const char * pszName )
{
	int length = (int)strlen( pszName );
	if( length < 4 || length > 16 )
		return FALSE;
	return xCheckCharname( pszName );
}
//------------------------------------------------------------------------
inline BOOL xCheckBirthday( const char * pszBirthday )
{
	char	szText[40];
	o_strncpy( szText, pszBirthday, 10 );
	xStringsExpander<20> birthday( szText, '/' );
	if( birthday.getCount() != 3 )return FALSE;
	int t = atoi( birthday[0] );
	if( t < 1900 || t > 2050 )return FALSE;
	t = StringToInteger( birthday[1] );
	if( t < 1 || t > 12 )return FALSE;
	t = StringToInteger( birthday[2] );
	if( t < 1 || t > 31 )return FALSE;
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL xCheckEmail(char * pszEmail )
{
	char * p = strchr( pszEmail, '@' );
	if( p == NULL )return FALSE;
	p = (char*)pszEmail;
	while( *p )
	{
		if( *p == '-' || *p == '.' || *p == '@' || *p == '_' || (*p >= 'a' && *p <= 'z' ) || (*p >= 'A' && *p <= 'Z' ) || (*p >= '0' && *p <= '9' ) )
		{
		}
		else
			return FALSE;
		p++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL	xCheckTelephone( char * pszNumber )
{
	char * p = (char*)pszNumber;
	while( *p )
	{
		if(( *p >= '0' && *p <= '9' ) || *p == '-' )
		{
		}
		else
			return FALSE;
		p ++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL xCheckMobilePhone( const char * pszMobile )
{
	char * p = (char*)pszMobile;
	while( *p )
	{
		if( (*p >= '0' && *p <= '9' ) )
		{
		}
		else
			return FALSE;
		p ++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL xCheckIdCard( const char * pszIdCard )
{
	char * p = (char*)pszIdCard;
	while( *p )
	{
		if( (*p >= '0' && *p <= '9' ) || *p == 'x' || *p == 'X' )
		{
		}
		else
			return FALSE;
		p ++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL xCheckPassword( const char * pszPassword )
{
	char * p = (char*)pszPassword;
	int length = 0;
	while( *p )
	{
		if( *p == '\'' || 
			*p == '\"' )
			return FALSE;
		if( *p < 0 )
			return FALSE;
		length ++;
		p++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline BOOL xCheckNormalString( const char * pszPassword )
{
	char * p = (char*)pszPassword;
	while( *p )
	{
		if( *p == '\'' || 
			*p == '\"' )
			return FALSE;
		p++;
	}
	return TRUE;
}
//------------------------------------------------------------------------
inline char * xGetValidName( char * pszName, int length )
{
	char * p = (char*)pszName;
	int i = 0;
	BOOL bInHz = FALSE;
	while( *p )
	{
		i ++;
		if( bInHz )
			bInHz = FALSE;
		else
		{
			if( *p < 0 )
				bInHz = TRUE;
			else if( *p == '\'' || *p == '\"' )
				*p = '_';
		}
		if( i >= length )
			break;
		p++;
	}

	if( bInHz )
	{
		pszName[i-1] = 0;
	}
	else
		pszName[i] = 0;
	return pszName;
}
//------------------------------------------------------------------------