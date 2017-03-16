/**
*	created:		2013-4-29   22:39
*	filename: 		FKTagCollection
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKActor.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
		//------------------------------------------------------------------------
		#define theTagList TagCollection::GetInstance()
		//------------------------------------------------------------------------
		class TagCollection
		{
		public:
			static TagCollection& GetInstance();
			ActorSet GetObjectsTagged(std::wstring findTag);
			std::set<std::wstring> GetTagList();
			void AddObjToTagList(CActor* obj, std::wstring tag);
			void RemoveObjFromTagList(CActor* obj, std::wstring tag);

		protected:
			TagCollection();
			static TagCollection* s_TagCollection;

		private:
			std::map<std::wstring, ActorSet> _tagMappings;
		};
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------