/**
*	created:		2013-4-23   15:27
*	filename: 		FKResourceMap
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#	if (_MSC_VER <= 1200)
#		pragma warning(disable:4786)
#	endif
//------------------------------------------------------------------------
#include <map>
#include <string>

#include "FKIBase.h"
#include "FKIResource.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		class CResourceMap : public IBase
		{
		public :
			virtual const std::wstring getTypeInfo() const {
				return L"CResourceMap";
			}
			virtual ~CResourceMap();
			CResourceMap();
			//! 向资源表中增加一个资源 【内部会调用一次 addRef】
			virtual bool addResource(IResource * resource);
			//! 根据资源名获取资源
			virtual IResource * getResourceByName(const std::wstring & resourceName);
			//! 释放一个资源 【内部会调用一次 delRef 】
			virtual void freeResource(IResource * resource);	
			virtual void freeResource(const std::wstring & resourceName);
			//! 释放全部资源
			virtual void freeAllResource();
		private:
			typedef std::map<std::wstring,IResource *> TResourceMap;
			typedef TResourceMap::iterator TResourceMapIterator;
			TResourceMap resourceMap;
		};
	}
}
//------------------------------------------------------------------------