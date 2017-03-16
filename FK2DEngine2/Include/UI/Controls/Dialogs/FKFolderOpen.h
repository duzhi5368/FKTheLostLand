/**
*	created:		2013-4-12   13:29
*	filename: 		FKFolderOpen
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Dialogs
	{
		// 使用方式：:
		// FK2DEngine2::Dialogs::FileOpen( true, "Open Map", "C:\my\folder\", "My Map Format|*.bmf", this, &MyClass::OpenFilename );
		void FK_EXPORT FolderOpenEx( bool bUseSystem, const String & Name, const String & StartPath,
			FK2DEngine2::Event::Handler* pHandler = NULL, FK2DEngine2::Event::Handler::FunctionWithInformation fnCallback = NULL );

		// 实际函数，若 bUseSystem 设置为true,则表示使用系统模态界面
		template< typename A>
		void FolderOpen( bool bUseSystem, const String & Name, const String & StartPath, FK2DEngine2::Event::Handler* pHandler = NULL, A fnCallback = NULL )
		{
			FolderOpenEx( bUseSystem, Name, StartPath, pHandler, static_cast<FK2DEngine2::Event::Handler::FunctionWithInformation>( fnCallback ) );
		}


	}
}
//------------------------------------------------------------------------