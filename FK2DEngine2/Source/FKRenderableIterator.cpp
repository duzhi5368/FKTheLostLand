/**
*	created:		2013-4-30   16:18
*	filename: 		FKRenderableIterator
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKRenderableIterator.h"
#include "../Include/FK2DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		CFKRenderableIterator& CFKRenderableIterator::begin()
		{
			if (theWorld.GetLayers().size() == 0)
			{
				return end();
			}
			_layerIterator = theWorld.GetLayers().begin();
			while ((_layerIterator->second.size() == 0))
			{
				if (_layerIterator != theWorld.GetLayers().end())
				{
					return end();
				}
				_layerIterator++;
			}
			_myIterator = _layerIterator->second.begin();
			_ptr = *_myIterator;
			return *this;
		}

		CFKRenderableIterator& CFKRenderableIterator::end()
		{
			_ptr = 0;
			return *this;
		}

		bool CFKRenderableIterator::operator!=( const CFKRenderableIterator& iter ) const
		{
			return ( _ptr != iter._ptr );
		}

		CFKRenderableIterator& CFKRenderableIterator::erase( CFKRenderableIterator& item_to_remove )
		{
			IRenderable* pValueToErase = *item_to_remove;

			RenderLayers::iterator layerElements = theWorld.GetLayers().find( pValueToErase->GetLayer() );
			if (layerElements != theWorld.GetLayers().end())
			{
				RenderList::iterator element = (*layerElements).second.begin();

				while ( element != (*layerElements).second.end() )
				{
					if ( *element == pValueToErase)
					{					
						_myIterator = (*layerElements).second.erase(element);

						// Have to force to next layer.
						// Let our ++ operator do it's magic.
						if ( _myIterator == (*layerElements).second.end() )
						{
							++item_to_remove;
						}
						else
						{
							_ptr = *_myIterator;
						}

						return *this;
					}
					++element;
				}
			}
			return *this;
		}

		const CFKRenderableIterator& CFKRenderableIterator::operator++()
		{
			if (_myIterator == _layerIterator->second.end())
			{
				if (_layerIterator == theWorld.GetLayers().end())
				{
					_ptr = 0;
					return *this;
				}
			}
			else
				++_myIterator;

			// See if we've reached the end of the vector for the current layer.
			if (_myIterator == _layerIterator->second.end())
			{
				++_layerIterator;
				// Go through layers until you reach the end or a non-empty layer.
				while (_layerIterator != theWorld.GetLayers().end() && _layerIterator->second.size() == 0)
					++_layerIterator;

				if (_layerIterator != theWorld.GetLayers().end() && _layerIterator->second.size() > 0)
				{	
					_myIterator = _layerIterator->second.begin();
				}
				else
					_ptr = NULL;
			}
			if (_ptr)
				_ptr = *_myIterator;

			return *this;
		}
	}
}