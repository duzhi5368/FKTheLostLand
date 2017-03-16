/**
*	created:		2013-4-15   22:00
*	filename: 		AppDB
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "virtualdatabase.h"
//------------------------------------------------------------------------
class CAppDB
{
public:
	CAppDB(void);
	virtual ~CAppDB(void);
public:
	SERVER_ERROR OpenDataBase( const char * pszServer, const char * pszDBName, const char * pszId, const char * pszPassword );
	SERVER_ERROR OpenWebDB( const char * pszServer, const char * pszDBName, const char * pszId, const char * pszPassword );
public:
	// ≥ı ºªØ
	VOID	DoInit();
	// ≤‚ ‘¥˙¬Î
	VOID	Test();
private:
	CVirtualDatabase * m_pDatabase;
	CVirtualDBConnection * m_pDBConnection;
	CVirtualDatabase * m_pWebDB;
	CVirtualDBConnection * m_pWebDBConnection;
};
//------------------------------------------------------------------------