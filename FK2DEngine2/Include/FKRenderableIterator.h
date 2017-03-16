/**
*	created:		2013-4-30   16:12
*	filename: 		FKRenderableIterator
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIRenderable.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		class CFKRenderableIterator : public std::iterator< std::forward_iterator_tag, IRenderable* >
		{
		public:
			CFKRenderableIterator() : _ptr(NULL)
			{
			}

			IRenderable* operator*()
			{
				return (_ptr);
			}

			CFKRenderableIterator& begin();
			CFKRenderableIterator& end();

			bool operator!=( const CFKRenderableIterator& iter ) const;
			CFKRenderableIterator& erase( CFKRenderableIterator& item_to_remove );
			const CFKRenderableIterator& operator++();

		private:	
			RenderLayers::iterator _layerIterator;
			RenderList::iterator _myIterator;
			IRenderable *_ptr;
		};
	}
}
//------------------------------------------------------------------------