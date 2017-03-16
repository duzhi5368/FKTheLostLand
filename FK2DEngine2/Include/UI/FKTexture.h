/**
*	created:		2013-4-11   22:25
*	filename: 		FKTexture
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <string>
//------------------------------------------------------------------------
#include "../FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	struct STextureInfo
	{
		UITexObjSimpleInfo	name;
		void*	data;
		bool	failed;
		int		width;
		int		height;

		STextureInfo()
		{
			data = NULL;
			width = 4;
			height = 4;
			failed = false;
		}

		~STextureInfo()
		{
		}

		void Load( const UITexObjSimpleInfo & str, FK2DEngine2::video::Base* render )
		{
			name = str;
			FK2DEngine2::Debug::AssertCheck( render != NULL, "No renderer!" );
			render->LoadTexture( this );
		}

		void Release( FK2DEngine2::video::Base* render )
		{
			render->FreeTexture( this );
		}

		bool FailedToLoad() const
		{
			return failed;
		}
	};

}
//------------------------------------------------------------------------