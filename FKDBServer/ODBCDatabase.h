/**
*	created:		2013-4-15   23:51
*	filename: 		ODBCDatabase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "virtualdatabase.h"

#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>
//------------------------------------------------------------------------
class CODBCDataUnit : public CVirtualDataUnit
{
private:
	int			m_nRowCount;
	int			m_nCols;
	int			m_nCurCols;
public:
	CODBCDataUnit();
	~CODBCDataUnit();
	VOID SetId( UINT id ){m_Id = id;}
	UINT GetId() { return m_Id;}
	VOID SetDBConnection( CVirtualDBConnection * pConnection ){ m_pConnection = pConnection;}
	CVirtualDBConnection * GetDBConnection(){ return m_pConnection;}
public:
	SERVER_ERROR	Init(void *);
	SERVER_ERROR	UnInit();

	int	GetColCount(){return m_nCols;}
	int GetRowCount(){return m_nRowCount;}

	SERVER_ERROR	GetData( const char * pszColName,int type, LPVOID lpBuffer, int & size );
	SERVER_ERROR	GetData( int nCol,int type, LPVOID lpBuffer, int & size );
	SERVER_ERROR	GetValue(/* int nCol,*/ DWORD & val );
	SERVER_ERROR	GetValue(/* int nCol,*/ WORD & val );
	SERVER_ERROR	GetValue(/* int nCol, */BYTE & val );
	SERVER_ERROR	GetValue(/* int nCol, */int & val );
	SERVER_ERROR	GetValue(/* int nCol,*/ short & val );
	SERVER_ERROR	GetValue( /*int nCol,*/ char & val );
	SERVER_ERROR	GetValue( char * pszString, int size );

	SERVER_ERROR	UpdateImage( const char * pszTableName, const char * pszColName, const char * pszCondition, LPVOID lpData, int datasize );

	SERVER_ERROR	Operation( const char * desc,... );
	SERVER_ERROR	MoveNext();
	SERVER_ERROR	GetColDesc( int nCol, ColumnInfo * pInfo );
private:
	SERVER_ERROR	PrepareColAndRow();
	SQLHSTMT	m_hStmt;
	UINT		m_Id;
	CVirtualDBConnection * m_pConnection;
};
//------------------------------------------------------------------------
class CODBCDBConnection : public CVirtualDBConnection
{
public:
	CODBCDBConnection();
	~CODBCDBConnection();
	VOID SetId( UINT id ){m_Id = id;}
	UINT GetId() { return m_Id;}
	VOID SetDatabase( CVirtualDatabase * pDatabase ){ m_pDatabase = pDatabase;}
	CVirtualDatabase * GetDatabase(){ return m_pDatabase;}
public:
	SERVER_ERROR	Init(void *);
	SERVER_ERROR	UnInit();

	SERVER_ERROR	Connect( const char * pservername, const char * pdbname,  const char * pId, const char * pPassword );
	SERVER_ERROR	Disconnect();
	CVirtualDataUnit * GetDataUnit();
	SERVER_ERROR	DelDataUnit( CVirtualDataUnit * pDataUnit );
	UINT GetFreeUnitCount(){ return m_DataUnits.GetCount();}

private:
	CIndexList<CODBCDataUnit, MAX_DATAUNIT > m_DataUnits;
	CODBCDataUnit * m_pUnit;
	SQLHDBC		m_hDBConn;
	UINT	m_Id;
	CVirtualDatabase * m_pDatabase;
};
//------------------------------------------------------------------------
class CODBCDatabase : public CVirtualDatabase
{
public:
	CODBCDatabase(void);
	virtual ~CODBCDatabase(void);
	SERVER_ERROR	Init();
	SERVER_ERROR	UnInit();
	CVirtualDBConnection * GetConnection();
	SERVER_ERROR	DelConnection( CVirtualDBConnection * pConnection );
private:
	CIndexList<CODBCDBConnection, MAX_CONNECTION > m_DbConnections;
	SQLHENV		m_hEnv;
};
//------------------------------------------------------------------------