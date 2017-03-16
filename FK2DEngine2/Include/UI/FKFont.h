/**
*	created:		2013-4-11   17:18
*	filename: 		FKFont
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <string>
#include <list>
//------------------------------------------------------------------------
#include "FKBaseRender.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	struct Font
	{
		typedef std::list<Font*>	List;

		Font()
		{
			data = NULL;
			facename = L"Arial";
			size = 10;
			realsize = 0;
			bold = false;
		}

		UnicodeString	facename;
		float size;
		bool  bold;
		void* data;
		float realsize;	// 字体的真正大小

	};
}
//------------------------------------------------------------------------