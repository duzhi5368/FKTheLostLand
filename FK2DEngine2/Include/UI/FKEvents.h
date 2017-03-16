/**
*	created:		2013-4-11   20:43
*	filename: 		FKEvents
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <list>
#include "FKExports.h"
#include "FKStructures.h"
#include "FKTextObject.h"
#include "FKControlList.h"
//------------------------------------------------------------------------
#pragma warning( disable:4407 )
//------------------------------------------------------------------------
namespace FK2DEngine2
{

	namespace Controls
	{
		class Base;
	}

	namespace Event
	{
		//------------------------------------------------------------------------
		struct Packet
		{
			Packet( FK2DEngine2::Controls::Base* pControl = NULL ) { Control = pControl; }

			FK2DEngine2::Controls::Base*	Control;
			FK2DEngine2::String				String;
			FK2DEngine2::UnicodeString		UnicodeString;
			int								Integer;
			float							Float;
			unsigned long long				UnsignedLongLong;
		};
		//------------------------------------------------------------------------
		struct Information
		{
			Information() { Init(); }
			Information( FK2DEngine2::Controls::Base* pctrl ) { Init(); Control = pctrl; }

			void Init()
			{
				ControlCaller	= NULL;
				Packet			= NULL;
				Control			= NULL;
				Integer			= 0;
			}

			FK2DEngine2::Controls::Base*	ControlCaller;
			FK2DEngine2::Event::Packet*		Packet;
			FK2DEngine2::Controls::Base*	Control;

			FK2DEngine2::ControlList		ControlList;
			FK2DEngine2::UITexObjSimpleInfo			String;
			FK2DEngine2::Point				Point;
			int								Integer;

		};
		//------------------------------------------------------------------------
		typedef const FK2DEngine2::Event::Information & Info;
		//------------------------------------------------------------------------
		class Caller;
		//------------------------------------------------------------------------
		class FK_EXPORT Handler
		{
			public:

				Handler();
				virtual ~Handler();

				void RegisterCaller( Caller* );
				void UnRegisterCaller( Caller* );

			protected:

				void CleanLinks();
				std::list<Caller*>	m_Callers;

			public:

				typedef void ( Handler::*Function )( FK2DEngine2::Controls::Base* pFromPanel );
				typedef void ( Handler::*FunctionBlank )();
				typedef void ( Handler::*FunctionWithInformation )( FK2DEngine2::Event::Info info );

		};
		//------------------------------------------------------------------------
		class FK_EXPORT Caller
		{
			public:

				Caller();
				~Caller();

				void Call( Controls::Base* pThis );
				void Call( Controls::Base* pThis, FK2DEngine2::Event::Info info );

				template <typename T> void Add( Event::Handler* ob, T f ) {	AddInternal( ob, static_cast<Handler::Function>( f ) ); }
				template <typename T> void Add( Event::Handler* ob, void ( T::*f )( FK2DEngine2::Event::Info ) ) 
					{ AddInternal( ob, static_cast<Handler::FunctionWithInformation>( f ) ); }
				template <typename T> void Add( Event::Handler* ob, void ( T::*f )( FK2DEngine2::Event::Info ), const FK2DEngine2::Event::Packet & packet )
					{ AddInternal( ob, static_cast<Handler::FunctionWithInformation>( f ), packet ); }
				template <typename T> void Add( Event::Handler* ob, void ( T::*f )() )
					{ AddInternal( ob, static_cast<Handler::FunctionBlank>( f ) ); }

				void RemoveHandler( Event::Handler* pObject );

			protected:

				void CleanLinks();
				void AddInternal( Event::Handler* pObject, Handler::Function pFunction );
				void AddInternal( Event::Handler* pObject, Handler::FunctionWithInformation pFunction );
				void AddInternal( Event::Handler* pObject, Handler::FunctionWithInformation pFunction, const FK2DEngine2::Event::Packet & packet );
				void AddInternal( Event::Handler* pObject, Handler::FunctionBlank pFunction );

				struct handler
				{
					handler()
					{
						fnFunction			= NULL;
						fnFunctionInfo		= NULL;
						fnFunctionBlank		= NULL;
						pObject				= NULL;
					}

					Handler::Function					fnFunction;
					Handler::FunctionWithInformation	fnFunctionInfo;
					Handler::FunctionBlank				fnFunctionBlank;

					Event::Handler*					pObject;
					FK2DEngine2::Event::Packet		Packet;
				};

				std::list<handler> m_Handlers;
		};
	}
}
//------------------------------------------------------------------------