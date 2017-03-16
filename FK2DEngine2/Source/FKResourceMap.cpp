/**
*	created:		2013-4-23   15:30
*	filename: 		FKResourceMap
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKLogger.h"
#include "../Include/FKResourceMap.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core
	{
		CResourceMap::~CResourceMap()
		{
		}
		
		CResourceMap::CResourceMap()
		{
			resourceMap.clear();
		}

		bool CResourceMap::addResource(IResource * resource)
		{
			if (resource == NULL)
				return false;
			resource->addRef();
			std::pair<TResourceMapIterator,bool> ret;
			ret = resourceMap.insert(TResourceMap::value_type(resource->getObjectName(),resource));
			return ret.second;
		}

		IResource * CResourceMap::getResourceByName(const std::wstring & resourceName)
		{
			TResourceMapIterator it = resourceMap.find(resourceName);
			if (it != resourceMap.end())
			{
				return (*it).second;
			}
			return NULL;
		}

		void CResourceMap::freeResource(IResource * resource)
		{
			TResourceMapIterator it;
			for (it = resourceMap.begin(); it != resourceMap.end(); it ++)
			{
				if ((*it).second == resource)
					break;
			}
			if (it != resourceMap.end())
			{
				resourceMap.erase(it);
			}
			resource->decRef();
		}
		void CResourceMap::freeResource(const std::wstring & resourceName)
		{
			TResourceMapIterator it = resourceMap.find(resourceName);
			if (it != resourceMap.end())
			{
				(*it).second->decRef();
				resourceMap.erase(it);
			}
		}
		
		void CResourceMap::freeAllResource()
		{
			TResourceMapIterator it;
			int i = 0;
			for (it = resourceMap.begin(); it != resourceMap.end(); it ++)
				(*it).second->decRef();
			resourceMap.clear();
		}
	}
}
//------------------------------------------------------------------------