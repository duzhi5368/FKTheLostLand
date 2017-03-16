/**
*	created:		2013-4-16   4:49
*	filename: 		xServerObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class xIocpServer;
//------------------------------------------------------------------------
class xServerObject
{
public:
	xServerObject(void);
	virtual ~xServerObject(void);

	xIocpServer * getServer(){ return m_pxIocpServer;}
	void	setServer( xIocpServer * pServer ){ m_pxIocpServer = pServer;}

private:
	xIocpServer * m_pxIocpServer;
};
//------------------------------------------------------------------------