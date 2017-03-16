/**
*	created:		2013-4-16   4:30
*	filename: 		xError
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class xError
{
public:
	xError()
	{
		m_dwErrorCode = 0;
		m_szErrorMsg[0] = 0;
	}
	~xError()
	{
		m_szErrorMsg[0] = 0;
		m_dwErrorCode = 0;
	}
	void	setError( DWORD dwErrorCode, const char * pszError, ... )
	{
		m_dwErrorCode = dwErrorCode;
		va_list	vl;
		va_start( vl, pszError );
		vsprintf( m_szErrorMsg, pszError, vl );
		va_end( vl);
		m_szErrorMsg[1023] = 0;
	}
	void setError( xError & error )
	{
		setError( error.getErrorCode(), error.getErrorMsg() );
	}
	DWORD	getErrorCode(){ return m_dwErrorCode;}
	const char * getErrorMsg(){ return m_szErrorMsg;}
private:
	DWORD	m_dwErrorCode;
	char			m_szErrorMsg[1024];
};
//------------------------------------------------------------------------