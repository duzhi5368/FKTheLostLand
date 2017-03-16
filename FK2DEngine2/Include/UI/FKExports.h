/**
*	created:		2013-4-11   16:50
*	filename: 		FKExports
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
// FK2DEngine2_COMPILE_DLL 编译为动态库
#if defined(FK2DEngine2_COMPILE_DLL)
	#ifdef _WIN32
		#if defined(__GNUC__)
			#define FK_EXPORT __attribute__((dllexport))
		#else
			#define FK_EXPORT __declspec(dllexport)
		#endif
	#endif
//------------------------------------------------------------------------
// FK2DEngine2_COMPILE_STATIC 编译为静态库
#elif defined(FK2DEngine2_COMPILE_STATIC)

	#define FK_EXPORT

// USE_FK2DEngine2_DLL 动态链接使用本库
#elif defined( USE_FK2DEngine2_DLL )

	#ifdef _WIN32
		#ifdef __GNUC__
			#define FK_EXPORT __attribute__((dllimport))
		#else
			#define FK_EXPORT __declspec(dllimport)
		#endif
	#endif

// 否则，默认静态使用本库
#else

	#define FK_EXPORT

#endif
//------------------------------------------------------------------------
#ifndef FK_EXPORT
	#define FK_EXPORT
#endif
//------------------------------------------------------------------------