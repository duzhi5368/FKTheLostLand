/**
*	created:		2013-4-12   13:41
*	filename: 		FKTile
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBase.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Layout
		{
			class FK_EXPORT Tile : public Base
			{
				public:

					FK_CONTROL_INLINE( Tile, Base )
					{
						Dock( Pos::Fill );
						SetTileSize( 22, 22 );
					}

					void PostLayout( Skin::Base* skin )
					{
						FK2DEngine2::Rect	bounds = GetInnerBounds();
						FK2DEngine2::Point pos = Point( bounds.x, bounds.y );

						for ( Base::List::iterator it = Children.begin(); it != Children.end(); ++it )
						{
							Base* pChild = *it;

							if ( pChild->GetDock() != Pos::None ) { continue; }

							pChild->SetPos( pos.x + ( m_TileSize.x / 2 ) - ( pChild->Width() / 2 ), pos.y + ( m_TileSize.y / 2 ) - ( pChild->Height() / 2 ) );
							pos.x = pos.x + m_TileSize.x;

							if ( pos.x + m_TileSize.x > bounds.x + bounds.w )
							{
								pos.x = bounds.x;
								pos.y += m_TileSize.y;
							}
						}
					}

					void SetTileSize( int x, int y )
					{
						m_TileSize = Point( x, y );
					}

				private:

					Point	m_TileSize;
			};
		}
	}
}
//------------------------------------------------------------------------