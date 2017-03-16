/**
*	created:		2013-4-16   4:44
*	filename: 		xIocpUnit
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "xsupport.h"
//------------------------------------------------------------------------
class xIocpUnit;
//------------------------------------------------------------------------
typedef struct tagOverlappedEx
{
	OVERLAPPED	ol;
	DWORD	dwFlag;
	DWORD	dwNumberOfBytes;
}OVERLAPPED_EX;
//------------------------------------------------------------------------
typedef struct tag_IocpUnit
{
	tag_IocpUnit()
	{
		memset( this, 0, sizeof( *this ) );
	}
	OVERLAPPED_EX ol;
	xIocpUnit * pUnit;
}IOCP_UNIT;
//------------------------------------------------------------------------
enum iocpunit_type
{
	IO_NOTSET,	// 未初始化
	IO_READ,	// 读取
	IO_SEND,	// 发送
	IO_ACCEPT,	// 接受
};
//------------------------------------------------------------------------
class xIocpUnit : public xEventSender
{
public:
	enum	eventid
	{
		IUE_ID	=	10000,
		IUE_READ,
		IUE_SEND,
		IUE_ACCEPT,
	};

	xIocpUnit(void);
	virtual ~xIocpUnit(void);

	VOID	OnComplete( DWORD dwNumberOfBytes, DWORD dwCompletionKey );

	iocpunit_type getType(){return m_type;}
	void setType( iocpunit_type type ){ m_type = type;}

	LPVOID	 getData(){ return m_lpData;}
	void	setData( LPVOID lpData ){ m_lpData = lpData;}

	OVERLAPPED_EX * getOverlappedEx(){return &m_UnitStruct.ol;}
	OVERLAPPED * getOverlapped(){ return &m_UnitStruct.ol.ol;}
private:
	iocpunit_type	m_type;
	IOCP_UNIT	m_UnitStruct;
	LPVOID	m_lpData;
};
//------------------------------------------------------------------------