/**
*	created:		2013-4-12   13:31
*	filename: 		FKFolderOpen
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
void FK2DEngine2::Dialogs::FolderOpenEx( bool bUseSystem, const String & Name, const String & StartPath, 
										FK2DEngine2::Event::Handler* pHandler, FK2DEngine2::Event::Handler::FunctionWithInformation fnCallback )
{
	if ( bUseSystem && FK2DEngine2::Platform::FolderOpen( Name, StartPath, pHandler, fnCallback ) )
	{
		return;
	}

	//
	// TODO: 
	//
}
//------------------------------------------------------------------------