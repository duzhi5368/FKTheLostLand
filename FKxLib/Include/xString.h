/**
*	created:		2013-4-16   1:01
*	filename: 		xString
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
// ×Ö·û´®×ª»»ÎªInt
inline int	StringToInteger( const char * pszString )
{
	int ret = 0;
	if( pszString == NULL )return 0;
	if( *pszString == '0' && *(pszString+1) == 'x' )
	{
		sscanf( pszString, "0x%x", &ret );
		return ret;
	}
	return atoi( pszString );
}
//------------------------------------------------------------------------
// °²È«×Ö·û´®¿½±´
inline char * o_strncpy( char * pdest, const char * psrc, int length )
{
	strncpy( pdest, psrc, length );
	pdest[length] = 0;
	return pdest;
}
//------------------------------------------------------------------------
// Öð×Ö·û×ª»»Ð¡Ð´
inline char * q_strupper( char * pString )
{
	char * p = pString;

	while( *p )
	{
		*p = toupper(*p);
		p ++;
	}
	return pString;
}
//------------------------------------------------------------------------
// Öð×Ö·û×ª»»Ð¡Ð´
inline char * StringUpper( char * pString, char * out, int length = -1 )
{
	if( length == -1 )
		length = (int)strlen( pString );
	int i;
	for(i = 0;i < length;i ++ )
	{
		out[i] = toupper( pString[i] );
	}
	out[i] = 0; 
	return out;
}
//------------------------------------------------------------------------
// »ñÈ¡Ò»¸ö×Ö·û´®±»·Ö¸î·û·Ö¸îºóµÄÊýÁ¿
inline int GetWordCount( const char * pString, int spliter )
{
	if( pString  == NULL )return 0;
	if( spliter == 0 )return (int)(strlen( pString ));
	char * p = (char*)pString;
	int retcount = 0;
	while( p != '\0' )
	{
		if( *p == spliter )
			retcount ++;
		p ++;
	}
	return (retcount+1);
}
//------------------------------------------------------------------------
// ×Ö·û´®¿½±´
inline char * copystring( const char * pszString )
{
	int len = (int)strlen( pszString );
	if( len > 0 )
	{
		char * p = new char[len+1];
		strncpy( p, pszString, len+1);
		return p;
	}
	return NULL;

}
//------------------------------------------------------------------------
// ÒÆ³ý×Ö·û´®ÖÐµÄ¿Õ¸ñ
inline char * removespace( char * pszString )
{
	char * p1=pszString, * p2=pszString;
	bool	binstring = false;
	while( *p1 != 0 )
	{
		if( *p1 == '\'' || *p1 == '\"' )
			binstring = !binstring;
		if( !binstring )
		{
			if( *p1 == ' ' || *p1 == '	' )
			{
				p1++;
				continue;
			}
		}
		*p2++=*p1++;
	}
	*p2=0;
	return pszString;
}
//------------------------------------------------------------------------
// ×Ö·û´®·Ö¸î
inline char * Trim( char * pString )
{
	int len = (int)strlen( pString );
	char * p = pString;

	while( *p == ' ' || *p == '	' )p++,len--;
	while( *(p+len-1) == ' ' || *(p+len-1) =='	' )len--,*(p+len) = 0;
	return p;
}
//------------------------------------------------------------------------
// ×Ö·û´®·Ö¸î
inline int SearchParam( char * buffer, char ** Params, int maxparam, int spliter )
{
	char * pbuffer = Trim( buffer );
	int len = (int)strlen( buffer );
	if( len == 0 )return 0;
	char * p = strchr( pbuffer, spliter );
	int count = 0;
	Params[0] = pbuffer;
	while( p )
	{
		*p++ = 0;
		Params[count++] = Trim( Params[count] );
		if( count >= maxparam )return count;
		Params[count] = p;
		p = strchr( p, spliter );
	}
	Params[count++] = Trim( Params[count] );
	return count;
}
//------------------------------------------------------------------------
