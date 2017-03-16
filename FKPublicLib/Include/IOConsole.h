/**
*	created:		2013-4-16   5:10
*	filename: 		IOConsole
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <windows.h>
//------------------------------------------------------------------------
class CInputListener
{
public:
	virtual void OnInput( const char * pszString ) = 0;
};
//------------------------------------------------------------------------
class CIOConsole
{
public:
	CIOConsole(void);
	virtual ~CIOConsole(void);
	void OutPut(  DWORD dwColor, const char * pszString, ...);
public:
	virtual void OutPutStatic(  DWORD dwColor, const char * pszString ){};
	virtual void Input( const char * pszString ){if( m_pInputListener != NULL)m_pInputListener->OnInput(pszString);}
	CInputListener * GetInputListener(){return m_pInputListener;}
	void	SetInputListener( CInputListener * pInputListener ){ m_pInputListener = pInputListener;}
protected:
	CInputListener * m_pInputListener;
};
//------------------------------------------------------------------------