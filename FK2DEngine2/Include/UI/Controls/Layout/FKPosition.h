/**
*	created:		2013-4-12   13:33
*	filename: 		FKPosition
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKLabel.h"
#include "../../FKUtility.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Layout
		{
			class FK_EXPORT Position : public Base
			{
				public:

					FK_CONTROL_INLINE( Position, Base )
					{
						SetPosition( Pos::Left | Pos::Top );
					}

					void PostLayout( Skin::Base* skin )
					{
						for ( Base::List::iterator it = Children.begin(); it != Children.end(); ++it )
						{
							Base* pChild = *it;

							if ( pChild->GetDock() != Pos::None ) { continue; }

							pChild->Position( m_iPosition );
						}
					}

					void SetPosition( int p )
					{
						if ( m_iPosition == p ) { return; }

						m_iPosition = p;
						Invalidate();
					}

				private:

					int		m_iPosition;
			};

			class FK_EXPORT Center : public Position
			{
					FK_CONTROL_INLINE( Center, Position )
					{
						SetPosition( Pos::Center );
					}
			};
		}
	}
}
//------------------------------------------------------------------------