/**
*	created:		2013-4-23   15:17
*	filename: 		FKIBase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKCoreInterface.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		// 所有具备类型信息的类的基类
		class IBase : public ITypeInfomation
		{
		public :
			virtual ~IBase(){}
			virtual const std::wstring getTypeInfo() const {
				return L"IBase";
			}
		};
	}
}
//------------------------------------------------------------------------