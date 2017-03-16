/**
*	created:		2013-4-11   22:06
*	filename: 		FKHook
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKUIOutSideHead.h"
#include <list>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Hook
	{
		class FK_EXPORT BaseHook
		{
			public:

				virtual bool OnControlClicked( FK2DEngine2::Controls::Base*, int /*iMouseX*/, int /*iMouseY*/ ) { return false; };
		};

		typedef std::list<BaseHook*> HookList;

		FK_EXPORT HookList & GetHookList();

		FK_EXPORT void AddHook( BaseHook* pHook );
		FK_EXPORT void RemoveHook( BaseHook* pHook );

		template< typename fnc >
		bool  CallHook( fnc f )
		{
			for ( HookList::iterator it = GetHookList().begin(); it != GetHookList().end(); ++it )
			{
				if ( ( ( *it )->*f )() ) { return true; }
			}

			return false;
		}

		template< typename fnc, typename AA >
		bool CallHook( fnc f, AA a )
		{
			for ( HookList::iterator it = GetHookList().begin(); it != GetHookList().end(); ++it )
			{
				if ( ( ( *it )->*f )( a ) ) { return true; }
			}

			return false;
		}

		template< typename fnc, typename AA, typename AB >
		bool CallHook( fnc f, AA a, AB b )
		{
			for ( HookList::iterator it = GetHookList().begin(); it != GetHookList().end(); ++it )
			{
				if ( ( ( *it )->*f )( a, b ) ) { return true; }
			}

			return false;
		}

		template< typename fnc, typename AA, typename AB, typename AC >
		bool CallHook( fnc f, AA a, AB b, AC c )
		{
			for ( HookList::iterator it = GetHookList().begin(); it != GetHookList().end(); ++it )
			{
				if ( ( ( *it )->*f )( a, b, c ) ) { return true; }
			}

			return false;
		}
	}

}
//------------------------------------------------------------------------