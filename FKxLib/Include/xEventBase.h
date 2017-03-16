/**
*	created:		2013-4-16   4:24
*	filename: 		xEventBase
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class xEventSender;
class xEventListener
{
public:
	virtual VOID OnEvent( xEventSender * pSender, int iEvent, int iParam, LPVOID lpParam ) = 0;
};

class xEventSender
{
public:
	xEventSender()
	{
		m_pEventListener = NULL;
	}
	VOID setEventListener( xEventListener * pEventListener ){m_pEventListener = pEventListener;}
	xEventListener * getEventListener(){ return m_pEventListener;}
	VOID sendEvent( int iEvent, int iParam, LPVOID lpParam ){ if( m_pEventListener) m_pEventListener->OnEvent( this, iEvent, iParam, lpParam );}
protected:
	xEventListener * m_pEventListener;
};
//------------------------------------------------------------------------