/**
*	created:		2013-4-11   21:40
*	filename: 		FKEvents
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Event;
//------------------------------------------------------------------------
Handler::Handler()
{
}
//------------------------------------------------------------------------
Handler::~Handler()
{
	CleanLinks();
}
//------------------------------------------------------------------------
void Handler::CleanLinks()
{
	std::list<Caller*>::iterator iter = m_Callers.begin();

	while ( iter != m_Callers.end() )
	{
		Caller* pCaller = *iter;
		UnRegisterCaller( pCaller );
		pCaller->RemoveHandler( this );
		iter = m_Callers.begin();
	}
}
//------------------------------------------------------------------------
void Handler::RegisterCaller( Caller* pCaller )
{
	m_Callers.push_back( pCaller );
}
//------------------------------------------------------------------------
void Handler::UnRegisterCaller( Caller* pCaller )
{
	m_Callers.remove( pCaller );
}
//------------------------------------------------------------------------
Caller::Caller()
{
}
//------------------------------------------------------------------------
Caller::~Caller()
{
	CleanLinks();
}
//------------------------------------------------------------------------
void Caller::CleanLinks()
{
	std::list<handler>::iterator iter;

	for ( iter = m_Handlers.begin(); iter != m_Handlers.end(); ++iter )
	{
		handler & h = *iter;
		h.pObject->UnRegisterCaller( this );
	}

	m_Handlers.clear();
}
//------------------------------------------------------------------------
void Caller::Call( Controls::Base* pThis )
{
	static FK2DEngine2::Event::Information info;
	info.Control = pThis;
	Call( pThis, info );
}
//------------------------------------------------------------------------
void Caller::Call( Controls::Base* pThis, FK2DEngine2::Event::Info information )
{
	FK2DEngine2::Event::Information info;
	info = information;
	info.ControlCaller	= pThis;
	std::list<handler>::iterator iter;

	for ( iter = m_Handlers.begin(); iter != m_Handlers.end(); ++iter )
	{
		handler & h = *iter;
		info.Packet = &h.Packet;

		if ( h.fnFunction )
		{ ( h.pObject->*h.fnFunction )( pThis ); }

		if ( h.fnFunctionInfo )
		{ ( h.pObject->*h.fnFunctionInfo )( info ); }

		if ( h.fnFunctionBlank )
		{ ( h.pObject->*h.fnFunctionBlank )(); }
	}
}
//------------------------------------------------------------------------
void Caller::AddInternal( Event::Handler* pObject, Event::Handler::Function pFunction )
{
	handler h;
	h.fnFunction = pFunction;
	h.pObject = pObject;
	m_Handlers.push_back( h );
	pObject->RegisterCaller( this );
}
//------------------------------------------------------------------------
void Caller::AddInternal( Event::Handler* pObject, Handler::FunctionWithInformation pFunction )
{
	AddInternal( pObject, pFunction, FK2DEngine2::Event::Packet() );
}
//------------------------------------------------------------------------
void Caller::AddInternal( Event::Handler* pObject, Handler::FunctionWithInformation pFunction, const FK2DEngine2::Event::Packet & packet )
{
	handler h;
	h.fnFunctionInfo	= pFunction;
	h.pObject			= pObject;
	h.Packet			= packet;
	m_Handlers.push_back( h );
	pObject->RegisterCaller( this );
}
//------------------------------------------------------------------------
void Caller::AddInternal( Event::Handler* pObject, Handler::FunctionBlank pFunction )
{
	handler h;
	h.fnFunctionBlank = pFunction;
	h.pObject = pObject;
	m_Handlers.push_back( h );
	pObject->RegisterCaller( this );
}
//------------------------------------------------------------------------
void Caller::RemoveHandler( Event::Handler* pObject )
{
	pObject->UnRegisterCaller( this );
	std::list<handler>::iterator iter = m_Handlers.begin();

	while ( iter != m_Handlers.end() )
	{
		handler & h = *iter;

		if ( h.pObject == pObject )
		{
			iter = m_Handlers.erase( iter );
		}
		else
		{
			++iter;
		}
	}
}
//------------------------------------------------------------------------