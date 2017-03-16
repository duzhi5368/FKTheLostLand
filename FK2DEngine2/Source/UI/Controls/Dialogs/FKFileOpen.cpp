/**
*	created:		2013-4-12   13:23
*	filename: 		FKFileOpen
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Dialogs;
//------------------------------------------------------------------------
void FK2DEngine2::Dialogs::FileOpenEx( bool bUseSystem, const String & Name, const String & StartPath, const String & Extension,
									  FK2DEngine2::Event::Handler* pHandler, FK2DEngine2::Event::Handler::FunctionWithInformation fnCallback )
{
	if ( bUseSystem && FK2DEngine2::Platform::FileOpen( Name, StartPath, Extension, pHandler, fnCallback ) )
	{
		return;
	}

	//
	// TODO:
	//
}
//------------------------------------------------------------------------