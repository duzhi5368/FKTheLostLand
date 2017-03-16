/**
*	created:		2013-4-11   20:58
*	filename: 		FKPlatform
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKStructures.h"
#include "FKEvents.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Platform
	{
		// 休眠指定毫秒
		FK_EXPORT void Sleep( unsigned int iMS );

		// 设置指定鼠标状态 状态定义参见 FKStructures.h
		FK_EXPORT void SetCursor( unsigned char iCursor );

		// 获取当前鼠标位置
		FK_EXPORT void GetCursorPos( FK2DEngine2::Point & p );

		// 获取桌面大小
		FK_EXPORT void GetDesktopSize( int & w, int & h );

		// 复制 / 粘贴时使用
		FK_EXPORT UnicodeString GetClipboardText();
		FK_EXPORT bool SetClipboardText( const UnicodeString & str );

		// 获取当前精确时间
		FK_EXPORT float GetTimeInSeconds();

		// 系统面板
		FK_EXPORT bool FileOpen( const String & Name, const String & StartPath, const String & Extension,
			FK2DEngine2::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
		FK_EXPORT bool FileSave( const String & Name, const String & StartPath, const String & Extension,
			FK2DEngine2::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
		FK_EXPORT bool FolderOpen( const String & Name, const String & StartPath, FK2DEngine2::Event::Handler* pHandler,
			Event::Handler::FunctionWithInformation fnCallback );

		// 窗口相关
		FK_EXPORT void* CreatePlatformWindow( int x, int y, int w, int h, const FK2DEngine2::String & strWindowTitle );
		FK_EXPORT void DestroyPlatformWindow( void* pPtr );
		FK_EXPORT void SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h );
		FK_EXPORT void MessagePump( void* pWindow, FK2DEngine2::Controls::Canvas* ptarget );
		FK_EXPORT bool HasFocusPlatformWindow( void* pPtr );
		FK_EXPORT void SetWindowMaximized( void* pPtr, bool bMaximized, FK2DEngine2::Point & pNewPos, FK2DEngine2::Point & pNewSize );
		FK_EXPORT void SetWindowMinimized( void* pPtr, bool bMinimized );
	}
}
//------------------------------------------------------------------------