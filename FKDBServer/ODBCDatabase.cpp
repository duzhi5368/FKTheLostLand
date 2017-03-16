/**
*	created:		2013-4-15   23:57
*	filename: 		ODBCDatabase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\odbcdatabase.h"
#include "server.h"
//------------------------------------------------------------------------
#define	PROCESSMESSAGESODBC( handletype, handle, logstring, connid, strsql )	{ProcessMessagesODBC( handletype, handle, logstring, connid, strsql );}
//------------------------------------------------------------------------
void ProcessMessagesODBC(	SQLSMALLINT plm_handle_type,	//出现错误时所使用的ODBC句柄类型，取值为：SQL_HANDLE_ENV ，SQL_HANDLE_DBC ，SQL_HANDLE_STMT
							SQLHANDLE plm_handle,			//出现错误时所使用的ODBC句柄
							char *logstring,				//标题字符串
							int ConnInd, 					//指明句柄是否为DBC句柄
							char* strSql )
{
	CServer * pServer = CServer::GetInstance();
	CIOConsole * pConsole = (CIOConsole*)pServer->GetIoConsole();
	RETCODE		plm_retcode = SQL_SUCCESS;
	UCHAR		plm_szSqlState[MAXBUFLEN] = "";
	UCHAR		plm_szErrorMsg[MAXBUFLEN] = "";
	SDWORD		plm_pfNativeError = 0L;
	SWORD		plm_pcbErrorMsg = 0;
	SQLSMALLINT	plm_cRecNmbr = 1;
	SDWORD		plm_SS_MsgState = 0, plm_SS_Severity = 0;
	SQLINTEGER	plm_Rownumber = 0;
	USHORT		plm_SS_Line;
	SQLSMALLINT	plm_cbSS_Procname, plm_cbSS_Srvname;
	SQLCHAR		plm_SS_Procname[MAXNAME], plm_SS_Srvname[MAXNAME];

	pConsole->OutPut( 255, "%s\n", logstring );
	LOG("%s", logstring);
	while (plm_retcode != SQL_NO_DATA_FOUND) 
	{
		plm_retcode = SQLGetDiagRec(plm_handle_type, 
			plm_handle,
			plm_cRecNmbr, 
			plm_szSqlState, 
			&plm_pfNativeError,
			plm_szErrorMsg, 
			MAXBUFLEN - 1, 
			&plm_pcbErrorMsg);

		// Note that if the application has not yet made a
		// successful connection, the SQLGetDiagField
		// information has not yet been cached by ODBC
		// Driver Manager and these calls to SQLGetDiagField
		// will fail.
		if (plm_retcode != SQL_NO_DATA_FOUND) 
		{
			if (ConnInd) 
			{
				plm_retcode = SQLGetDiagField(
					plm_handle_type, 
					plm_handle, 
					plm_cRecNmbr,
					SQL_DIAG_ROW_NUMBER, 
					&plm_Rownumber,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, 
					plm_handle, 
					plm_cRecNmbr,
					SQL_DIAG_SS_LINE, 
					&plm_SS_Line,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, 
					plm_handle, 
					plm_cRecNmbr,
					SQL_DIAG_SS_MSGSTATE, 
					&plm_SS_MsgState,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, 
					plm_handle, 
					plm_cRecNmbr,
					SQL_DIAG_SS_SEVERITY, 
					&plm_SS_Severity,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, 
					plm_handle, 
					plm_cRecNmbr,
					SQL_DIAG_SS_PROCNAME, 
					&plm_SS_Procname,
					sizeof(plm_SS_Procname),
					&plm_cbSS_Procname);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, 
					plm_handle, 
					plm_cRecNmbr,
					SQL_DIAG_SS_SRVNAME, 
					&plm_SS_Srvname,
					sizeof(plm_SS_Srvname),
					&plm_cbSS_Srvname);
			}
			
			pConsole->OutPut( RGB(0,255,0),"szSqlState = %s\n",plm_szSqlState);
			LOG("szSqlState = %s",plm_szSqlState);
			pConsole->OutPut( RGB(0,255,0),"pfNativeError = %d\n",plm_pfNativeError);
			LOG("pfNativeError = %d",plm_pfNativeError);
			pConsole->OutPut( RGB(0,255,0),"szErrorMsg = %s\n",plm_szErrorMsg);
			LOG("szErrorMsg = %s",plm_szErrorMsg);
			pConsole->OutPut( RGB(0,255,0),"pcbErrorMsg = %d\n\n",plm_pcbErrorMsg);
			LOG("pcbErrorMsg = %d",plm_pcbErrorMsg);
			DPRINT(RGB( 0, 255, 0 ), "strSql = %s\n", strSql);
			LOG("strSql = %s", strSql);
			if (ConnInd) 
			{
				pConsole->OutPut( RGB(0,255,0),"ODBCRowNumber = %d\n", plm_Rownumber);
				LOG("ODBCRowNumber = %d", plm_Rownumber);
				pConsole->OutPut( RGB(0,255,0),"SSrvrLine = %d\n", plm_Rownumber);
				LOG("SSrvrLine = %d", plm_Rownumber);
				pConsole->OutPut( RGB(0,255,0),"SSrvrMsgState = %d\n",plm_SS_MsgState);
				LOG("SSrvrMsgState = %d",plm_SS_MsgState);
				pConsole->OutPut( RGB(0,255,0),"SSrvrSeverity = %d\n",plm_SS_Severity);
				LOG("SSrvrSeverity = %d",plm_SS_Severity);
				pConsole->OutPut( RGB(0,255,0),"SSrvrProcname = %s\n",plm_SS_Procname);
				LOG("SSrvrProcname = %s",plm_SS_Procname);
				pConsole->OutPut( RGB(0,255,0),"SSrvrSrvname = %s\n\n",plm_SS_Srvname);
				LOG("SSrvrSrvname = %s",plm_SS_Srvname);
			}
		}
		plm_cRecNmbr++;
	}
}
//------------------------------------------------------------------------
CODBCDatabase::CODBCDatabase(void)
{
	m_hEnv = NULL;
}
//------------------------------------------------------------------------
CODBCDatabase::~CODBCDatabase(void)
{
	UnInit();
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDatabase::Init()
{
	if ( SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv ) != SQL_SUCCESS )
		return SE_ODBC_SQLALLOCHANDLEFAIL;

	if ( SQLSetEnvAttr( m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER ) != SQL_SUCCESS )
		return SE_ODBC_SQLSETENVATTRFAIL;
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDatabase::UnInit()
{
	if ( m_hEnv )
	{
		SQLFreeHandle( SQL_HANDLE_ENV, m_hEnv );
		m_hEnv = NULL;
		return SE_OK;
	}
	return SE_DB_NOTINITED;
}
//------------------------------------------------------------------------
CVirtualDBConnection * CODBCDatabase::GetConnection()
{
	CODBCDBConnection * pConnection = NULL;
	UINT id = m_DbConnections.New( &pConnection );
	if( id == 0 || pConnection == NULL )
		return NULL;
	pConnection->SetId( id );
	pConnection->SetDatabase( this );
	pConnection->Init(m_hEnv);
	return pConnection;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDatabase::DelConnection( CVirtualDBConnection * pConnection )
{
	if( pConnection == NULL )
		return SE_INVALIDPARAM;
	CODBCDBConnection * pConnectionT = (CODBCDBConnection *)pConnection;
	pConnectionT->UnInit();
	m_DbConnections.Del(pConnectionT->GetId());
	return SE_OK;
}
//------------------------------------------------------------------------
CODBCDBConnection::CODBCDBConnection()
{
	m_hDBConn = NULL;
	m_pDatabase = NULL;
	m_Id = 0;
	m_pUnit = NULL;
}
//------------------------------------------------------------------------
CODBCDBConnection::~CODBCDBConnection()
{
	UnInit();
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDBConnection::Init(void *hEnv)
{
	int nResult;

	nResult = SQLAllocHandle( SQL_HANDLE_DBC,hEnv , &m_hDBConn );
	if ( nResult != SQL_SUCCESS )
	{
		return SE_ODBC_SQLALLOCHANDLEFAIL;
	}
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDBConnection::UnInit()
{
	if( m_hDBConn != NULL )
	{
		SQLFreeHandle( SQL_HANDLE_DBC, m_hDBConn );
		m_hDBConn = NULL;
		return SE_OK;
	}
	return SE_DB_NOTINITED;
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDBConnection::Connect(  const char * pservername, const char * pdbname, const char * pId, const char * pPassword )
{
	int nResult;
	char ConnStr[200];		//连接数据库字符串
	char szBuffer[1025];
	SWORD swStrLen; 
	sprintf(ConnStr,"DRIVER={SQL Server};SERVER=%s;UID=%s;PWD=%s;DATABASE=%s",pservername,pId,pPassword,pdbname);
	nResult = SQLDriverConnect( m_hDBConn, NULL, (SQLCHAR *)ConnStr, (SQLSMALLINT)strlen(ConnStr),
		(SQLCHAR *)szBuffer,(SQLSMALLINT)strlen(szBuffer),&swStrLen,SQL_DRIVER_COMPLETE_REQUIRED); 
	if ( nResult != SQL_SUCCESS )
	{
		if ( nResult != SQL_SUCCESS_WITH_INFO )
		{
			return SE_ODBC_SQLCONNECTFAIL;
		}
	}
	UINT id = this->m_DataUnits.New( &m_pUnit );
	if( id != 0 && m_pUnit != NULL )
		m_pUnit->SetId( id );
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDBConnection::Disconnect()
{
	if( SQLDisconnect( m_hDBConn ) != SQL_SUCCESS )
		return SE_ODBC_SQLDISCONNECTFAIL;
	return SE_OK;
}
//------------------------------------------------------------------------
CVirtualDataUnit * CODBCDBConnection::GetDataUnit()
{
	if( m_pUnit )
	{
		m_pUnit->SetDBConnection( this );
		m_pUnit->Init( m_hDBConn );
	}
	return m_pUnit;
	CODBCDataUnit * pUnit = NULL;
	UINT id = m_DataUnits.New( &pUnit);
	if( id == 0 || pUnit == NULL )return NULL;
	pUnit->SetId(id);
	pUnit->SetDBConnection(this);
	pUnit->Init(m_hDBConn);
	return pUnit;
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDBConnection::DelDataUnit( CVirtualDataUnit * pDataUnit )
{
	if( pDataUnit == NULL )
		return SE_INVALIDPARAM;
	CODBCDataUnit * pUnit = (CODBCDataUnit *)pDataUnit;
	pDataUnit->UnInit();
	return SE_OK;
}
//------------------------------------------------------------------------
CODBCDataUnit::CODBCDataUnit()
{
	m_hStmt		= NULL;

	m_nRowCount	= 0;
	m_nCols		= 0;
}
//------------------------------------------------------------------------
CODBCDataUnit::~CODBCDataUnit()
{
	UnInit();
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::Init(void *hDBConn)
{
	if( m_hStmt )
		UnInit();
	if ( SQLAllocHandle( SQL_HANDLE_STMT, hDBConn, &m_hStmt ) != SQL_SUCCESS )
	{
		return SE_ODBC_SQLALLOCHANDLEFAIL;
	}
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::UnInit()
{
	if ( m_hStmt )
	{
		SQLFreeHandle( SQL_HANDLE_STMT, m_hStmt );
		m_hStmt = NULL;
		return SE_OK;
	}
	return SE_DB_NOTINITED;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::Operation( const char * desc,... )
{
	char	szBuff[4096];
	va_list	vl;
	va_start( vl, desc );
	vsprintf( szBuff, desc, vl );
	va_end( vl);

	szBuff[4000] = '\0';
	m_nCurCols = 0;
	int nResult = SQLExecDirectA( m_hStmt, (BYTE *) szBuff, SQL_NTS );
	if ( nResult != SQL_SUCCESS )
	{
		PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "SQLExecDirectA", 0 , szBuff);
		if ( nResult != SQL_SUCCESS_WITH_INFO )
			return SE_ODBC_SQLEXECDIRECTFAIL;
	}
	nResult = PrepareColAndRow();
	if( nResult != SE_OK )
		return SE_FAIL;
	if( m_nCols == 0 )
		return SE_OK;
	return MoveNext();
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::GetData( const char * pszColName,int type, LPVOID lpBuffer, int & size )
{
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::GetData( int nCol,int type, LPVOID lpBuffer, int & size )
{
	int nResult;

	if( size == 0 )
	{
		//	普通变量
		nResult = SQLGetData( m_hStmt, nCol, type,(SQLINTEGER*) lpBuffer, 0,(SQLINTEGER*) &size );
		if( nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO )
		{
			m_nCurCols = nCol;
			return SE_OK;
		}
		PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "ERROR at CODBCDataUnit::GetData", 0, "" );
		return SE_FAIL;
	}

	nResult = SQLGetData( m_hStmt, nCol, SQL_C_CHAR,(SQLINTEGER*) lpBuffer, size,(SQLINTEGER*) &size );
	if( nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO )
	{
		m_nCurCols = nCol;
		return SE_OK;
	}
	PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "ERROR at CODBCDataUnit::GetData", 0, "" );
	return SE_FAIL;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::PrepareColAndRow()
{
	m_nCols = 0;
	int nResult = SQLNumResultCols( m_hStmt, (short *) &m_nCols );
	if ( nResult != SQL_SUCCESS )
	{
		PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "SQLNumResultCols", 0, "" );

		if( nResult != SQL_SUCCESS_WITH_INFO )
			return SE_ODBC_SQLNUMRESULTCOLSFAIL;
	}
	if( m_nCols == 0 )
	{
		m_nRowCount = 0;
		SQLRowCount( m_hStmt, (long *) &m_nRowCount );
	}
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::MoveNext()
{
	int nResult;
	m_nCurCols = 0;
	nResult = SQLFetch( m_hStmt );
	if ( nResult != SQL_SUCCESS )
	{
		if( nResult == SQL_NO_DATA )
			return SE_DB_NOMOREDATA;

		PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "SQLFetch", 0, "" );
		if ( nResult != SQL_SUCCESS_WITH_INFO )
			return SE_ODBC_SQLFETCHFAIL;
	}

	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::GetColDesc( int nCol, ColumnInfo * pInfo )
{
	if( nCol < 0 || nCol >= m_nCols )
		return SE_FAIL;

	int nResult = SQLDescribeColA( m_hStmt, 
		nCol + 1, 
		(SQLCHAR*) pInfo->szColName, DB_MAXBUF,
		(short *) &pInfo->nColNameSize,
		(short *) &pInfo->nColType,
		(ULONG *) &pInfo->nColSize,
		(short *) &pInfo->nAllowDecimalDigit,
		(short *) &pInfo->nAllowNull );	
	if ( nResult != SQL_SUCCESS )
	{
		if ( nResult != SQL_SUCCESS_WITH_INFO )
			return SE_ODBC_SQLDESCRIBECOLFAIL;
	}
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR CODBCDataUnit::UpdateImage( const char * pszTableName, const char * pszColName, const char * pszCondition, LPVOID lpData, int datasize )
{
	SQLCHAR	szSQLStr[1024];
	sprintf( (char*)szSQLStr, "update %s set %s = ? where %s", pszTableName, pszColName, pszCondition );
	int nResult = SQLPrepare(m_hStmt,szSQLStr,SQL_NTS);
	if( nResult != SQL_SUCCESS )
	{
		PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "SQLPrepare", 0, "");
		if( nResult != SQL_SUCCESS_WITH_INFO )
			return SE_FAIL;
	}
	SQLINTEGER	cb1;
	SQLPOINTER  pToken;

	cb1 = SQL_LEN_DATA_AT_EXEC( datasize );
	nResult = SQLBindParameter( m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_LONGVARBINARY, datasize, 0, (SQLPOINTER)lpData, 0, &cb1 );
	if( nResult != SQL_SUCCESS )
	{
		PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "SQLBindParameter", 0, "");
		if( nResult != SQL_SUCCESS_WITH_INFO )
			return SE_FAIL;
	}

	nResult = SQLExecute(m_hStmt);
	nResult = SQLParamData(m_hStmt, &pToken);
	if( nResult == SQL_NEED_DATA )
	{
		nResult = SQLPutData( m_hStmt, (SQLPOINTER)lpData, (SQLLEN)datasize );
		if( nResult != SQL_SUCCESS )
		{
			PROCESSMESSAGESODBC( SQL_HANDLE_STMT, m_hStmt, "SQLPutData", 0, "");
			if( nResult != SQL_SUCCESS_WITH_INFO )
				return SE_FAIL;
		}
	}
	return SE_OK;
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( /*int nCol,*/ DWORD & val )
{
	m_nCurCols ++;
	int size = 0;
	return GetData( m_nCurCols, SQL_INTEGER, &val, size );
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( /*int nCol,*/ WORD & val )
{
	m_nCurCols ++;
	int size = 0;
	return GetData( m_nCurCols, SQL_SMALLINT, &val, size );
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( /*int nCol,*/ BYTE & val )
{
	m_nCurCols ++;
	int size = 0;
	return GetData( m_nCurCols, SQL_TINYINT, &val, size );	//SQL_TINYINT,暂时改为SQL_SMALLINT，177溢出？
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( /*int nCol,*/ int & val )
{
	m_nCurCols ++;
	int size = 0;
	return GetData( m_nCurCols, SQL_INTEGER, &val, size );
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( /*int nCol,*/ short & val )
{
	m_nCurCols ++;
	int size = 0;
	return GetData( m_nCurCols, SQL_SMALLINT, &val, size );
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( /*int nCol,*/ char & val )
{
	m_nCurCols ++;
	int size = 0;
	return GetData( m_nCurCols, SQL_TINYINT, &val, size );
}
//------------------------------------------------------------------------
SERVER_ERROR	CODBCDataUnit::GetValue( char * pszString, int size )
{
	m_nCurCols ++;
	SERVER_ERROR sr = GetData( m_nCurCols, SQL_C_CHAR, (LPVOID)pszString, size );
	return sr;
}
//------------------------------------------------------------------------