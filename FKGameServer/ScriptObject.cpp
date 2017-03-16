/**
*	created:		2013-4-19   9:31
*	filename: 		ScriptObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\scriptobject.h"
#include ".\scriptelement.h"
#include ".\scriptobjectmgr.h"
//------------------------------------------------------------------------
CScriptObject::CScriptObject(void) : m_xPageList( TRUE )
{
	m_pPageList = NULL;
	m_pGoodsList = NULL;
	memset( m_btTradeItemType, 0, sizeof( m_btTradeItemType ) );
	this->m_pLeftPage = NULL;
	this->m_bBigBox = FALSE;
}
//------------------------------------------------------------------------
CScriptObject::~CScriptObject(void)
{
}
//------------------------------------------------------------------------
VOID	CScriptObject::Destroy()
{
	if( m_pPageList )
	{
		m_pPageList->delToTail();
		m_pPageList = NULL;
	}
	if( m_pGoodsList )
	{
		m_pGoodsList->delToTail();
		m_pGoodsList = NULL;
	}
	m_xPageList.Clear();
	m_xVarList.ClearVars();
}
//------------------------------------------------------------------------
BOOL	CScriptObject::Load( const char * pszFilename )
{
	CScriptFile file;
	if( !file.Load( pszFilename ) )
	{
		return FALSE;
	}
	if( pszFilename != this->m_szFileName )
		strncpy( this->m_szFileName, pszFilename, 1020 );
	m_bBigBox = FALSE;
	this->m_pLeftPage = NULL;
	char * pLine = file.FirstLine();

	do
	{
		if( pLine == NULL )break;

		switch( *pLine )
		{
		case	0:
			continue;
		case	'[':
			{
				char	szName[200];
				filtercopy( szName, pLine, 7, CharSetWhite );
				if( strnicmp( szName, "[Goods]", 7 ) == 0 )
				{
					CSe_Goods * pGoods = new CSe_Goods;
					if( !pGoods->Parse( file ) )
					{
						delete pGoods;
					}
					else
					{
						if( m_pGoodsList )
							m_pGoodsList->addTail( pGoods );
						else
							m_pGoodsList = pGoods;
					}
				}
				else
				{
					CSe_Page * pPage = new CSe_Page;
					if( !pPage->Parse( file ) )
					{
						delete pPage;
					}
					else
					{
						pPage->setObject( this );
						if( m_pPageList )
						{
							m_pPageList->addTail( pPage );
						}
						else
						{
							m_pPageList = pPage;
						}
						m_xPageList.Add( pPage->getName(), (LPVOID)pPage );
					}
				}
			}
			break;
		case	'+':
			{
				AddTradeItemType( (BYTE)StringToInteger( pLine+1));
			}
			break;
		case	'#':
			{
				if( strnicmp( pLine, "#version:", 9 ) == 0 )
				{
					pLine += 9;
					xStringsExtracter<4> version( pLine, ".", " \t" );
					m_Version.dwVersion = 0;
					if( version[0] )m_Version.v1 = StringToInteger( version[0] );
					if( version[1] )m_Version.v2 = StringToInteger( version[1] );
					if( version[2] )m_Version.v3 = StringToInteger( version[2] );
					if( version[3] )m_Version.v4 = StringToInteger( version[3] );
				}
				else if( strnicmp( pLine, "#var", 4 ) == 0 )
				{
					char * Params[4];
					xCharSet csWht( " \t()\"=" );
					xCharSet csSpl( " \t(),=" );
					int nParam = ExtractStrings( pLine, csWht, csSpl, Params, 4, FALSE );
					if( nParam >= 3 )
					{
						m_xVarList.AddVar( Params[1], Params[2] );
					}
				}
				else if( strnicmp( pLine, "#bigbox:", 8 ) == 0 )
				{
					m_bBigBox = TRUE;
					o_strncpy( m_szLeftPage, pLine + 8, 250 );
				}
				else
					continue;
			}
			break;
		case	';':
			break;
		}
	}while( pLine = file.NextLine());
	_splitpath( pszFilename, NULL, NULL, m_szName, NULL );
	return TRUE;
}
//------------------------------------------------------------------------
CSe_Page * CScriptObject::GetPage(  char * pszPage )
{
	char * pOName = (char*)pszPage;
	char * p = strchr( pszPage, '.' );
	if( p != NULL )
	{
		if( *(p+1) == 0 )
			return NULL;
		if( *pOName == '@' )pOName ++;
		*p = 0;
		CScriptObject * pObject = CScriptObjectMgr::GetInstance()->GetScriptObject( pOName );
		*p = '.';
		if( pObject == NULL )return NULL;
		char * pDot = p;
		if( *(p+1) != '@' )
			*p = '@';
		else
			p++;

		CSe_Page * pPage = pObject->GetPage( p );
		*pDot = '.';
		return pPage;
	}

	return (CSe_Page*)m_xPageList.ObjectOf( pszPage );
}
//------------------------------------------------------------------------
VOID	CScriptObject::AddTradeItemType( BYTE btType )
{
	if( m_btTradeItemType[btType] == 0 )
		m_btTradeItemType[btType] = 1;
}
//------------------------------------------------------------------------
BOOL	CScriptObject::IsItemTradeble( BYTE btStdMode )
{
	return m_btTradeItemType[btStdMode];
}
//------------------------------------------------------------------------
VOID	CScriptObject::Reload()
{
	Destroy();
	Load( this->m_szFileName );
}
//------------------------------------------------------------------------
CScriptObject * CScriptObject::GetLeftPage()
{
	if( !this->IsBigBox() )return NULL;
	if( this->m_pLeftPage == NULL )
		this->m_pLeftPage = CScriptObjectMgr::GetInstance()->GetScriptObject( this->m_szLeftPage );
	return m_pLeftPage;
}
//------------------------------------------------------------------------