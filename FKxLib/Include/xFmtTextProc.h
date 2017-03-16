/**
*	created:		2013-4-16   4:39
*	filename: 		xFmtTextProc
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xExtractString.h"
//------------------------------------------------------------------------
class xVariableProvider
{
public:
	virtual char * GetVariableValue( const char * pszVariable ){ return NULL; }
	virtual VOID SetVariableValue( const char * pszVariable, const char * pszValue ){}
	virtual VOID ClrVariable( const char * pszVariable ){}
	virtual BOOL AddVariable( const char * pszVariable, const char * pszValue ){return FALSE;}
};
//------------------------------------------------------------------------
inline int ProcFmtText( const char * pszText, char * pszOutBuffer, int iOutBufferSize, xVariableProvider * pVariableProvider )
{
	char * p = (char*)pszText;

	BOOL	bCatch = FALSE;
	BOOL	bStartCommand = FALSE;
	char	szCommand[256] = "";
	char	szTemp[512] = "";
	int catchtargetptr = 0;
	int targetptr = 0;
	int cmdptr = 0;

	iOutBufferSize -= 1;	//	保留一个0结尾

	for( int i = 0;i < (int)strlen( pszText );i ++ )
	{
		if( *(pszText + i ) == '<' )
		{
			bCatch = TRUE;
			catchtargetptr = targetptr;
		}
		else if( *(pszText + i ) == '>' && bCatch )
		{
			bCatch = FALSE;
			if( bStartCommand )
			{
				szCommand[cmdptr] = 0;
				
				char * p = pVariableProvider->GetVariableValue( TrimEx(szCommand) );

				if( p == NULL )
				{
					sprintf( szTemp, "<$%s>", szCommand );
					p = szTemp;
				}
				cmdptr = (int)strlen( p );
				if( ( cmdptr + targetptr )>= iOutBufferSize )
				{
					break;
				}
				memcpy( pszOutBuffer + targetptr, p, cmdptr );
				targetptr += cmdptr;
				bStartCommand = FALSE;
				continue;
			}
		}
		else if( *(pszText + i ) == '$' && bCatch )
		{
			if( !bStartCommand )
			{
				bStartCommand = TRUE;
				cmdptr = 0;
				targetptr = catchtargetptr;	//	恢复到CATCH的地方
				continue;
			}
		}
		else if( *(pszText + i ) != ' ' && *(pszText+i) != '\t' )
		{
			if( !bStartCommand )
			{
				if( bCatch )bCatch = FALSE;
			}
		}
		if( bStartCommand )
		{
			szCommand[cmdptr++] = *(pszText + i );
		}
		else
		{
			pszOutBuffer[targetptr++] = *(pszText + i );
			if( targetptr >= iOutBufferSize )
				break;
		}
	}
	pszOutBuffer[targetptr] = 0;
	return targetptr;
}
//------------------------------------------------------------------------