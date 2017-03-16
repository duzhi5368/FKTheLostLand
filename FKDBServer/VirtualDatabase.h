/**
*	created:		2013-4-15   23:56
*	filename: 		VirtualDatabase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "..\FKPublicLib\public.h"
//------------------------------------------------------------------------
#define DB_MAXBUF		256
#define MAX_CONNECTION	255
#define MAX_DATAUNIT	32
#define MAXBUFLEN		1024
//------------------------------------------------------------------------
typedef struct tagDBIMAGE
{
	int	size;
	LPVOID * pImage;
}DBIMAGE;
//------------------------------------------------------------------------
typedef struct tagDBSTRING
{
	int	size;
	CHAR * pString;
}DBSTRING;
//------------------------------------------------------------------------
typedef struct tagColumnInfo
{
	int  nColNameSize;
	char szColName[DB_MAXBUF];
	int  nColType;
	int  nColSize;
	int  nAllowDecimalDigit;
	int  nAllowNull;
}ColumnInfo;
//------------------------------------------------------------------------
class CVirtualDataUnit
{
public:
	virtual SERVER_ERROR	Init(void *) = 0;
	virtual SERVER_ERROR	UnInit() = 0;

	virtual int				GetColCount() = 0;
	virtual int 			GetRowCount() = 0;

	virtual SERVER_ERROR	GetData( const char * pszColName,int type, LPVOID lpBuffer, int & size ) = 0;
	virtual SERVER_ERROR	GetData( int nCol,int type, LPVOID lpBuffer, int & size ) = 0;
	virtual SERVER_ERROR	GetValue( /*int nCol, */DWORD & val ) = 0;
	virtual SERVER_ERROR	GetValue( /*int nCol,*/ WORD & val ) = 0;
	virtual SERVER_ERROR	GetValue(/* int nCol,*/ BYTE & val ) = 0;
	virtual SERVER_ERROR	GetValue(/* int nCol,*/ int & val ) = 0;
	virtual SERVER_ERROR	GetValue( /*int nCol,*/ short & val ) = 0;
	virtual SERVER_ERROR	GetValue( /*int nCol, */char & val ) = 0;
	virtual SERVER_ERROR	GetValue( char * pszString, int size ) = 0;

	virtual SERVER_ERROR	UpdateImage( const char * pszTableName, const char * pszColName, const char * pszCondition, LPVOID lpData, int datasize ) = 0;

	virtual SERVER_ERROR	Operation( const char * desc,... ) = 0;
	virtual SERVER_ERROR	MoveNext() = 0;
	virtual SERVER_ERROR	GetColDesc( int nCol, ColumnInfo * pInfo ) = 0;
};
//------------------------------------------------------------------------
class CVirtualDBConnection
{
public:
	virtual SERVER_ERROR	Init(void *) = 0;
	virtual SERVER_ERROR	UnInit() = 0;

	virtual SERVER_ERROR	Connect( const char * pservername, const char * pdbname, const char * pId, const char * pPassword ) = 0;
	virtual SERVER_ERROR	Disconnect() = 0;
	virtual CVirtualDataUnit * GetDataUnit() = 0;
	virtual SERVER_ERROR	DelDataUnit( CVirtualDataUnit * pDataUnit ) = 0;
	virtual UINT GetFreeUnitCount() = 0;
};
//------------------------------------------------------------------------
class CVirtualDatabase
{
public:
	virtual SERVER_ERROR	Init() = 0;
	virtual SERVER_ERROR	UnInit() = 0;
	virtual CVirtualDBConnection * GetConnection() = 0;
	virtual SERVER_ERROR	DelConnection( CVirtualDBConnection * pConnection ) = 0;
};
//------------------------------------------------------------------------