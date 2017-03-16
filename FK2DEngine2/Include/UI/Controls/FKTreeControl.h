/**
*	created:		2013-4-12   17:56
*	filename: 		FKTreeControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKTreeNode.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT TreeControl : public TreeNode
		{
			public:

				FK_CONTROL( TreeControl, TreeNode );

				virtual void Render( Skin::Base* skin );

				virtual void OnChildBoundsChanged( FK2DEngine2::Rect oldChildBounds, Base* pChild );

				ScrollControl* Scroller() { return m_ScrollControl; }

				virtual void Clear();

				virtual void Layout( Skin::Base* skin );
				virtual void PostLayout( Skin::Base* skin );

				virtual void AllowMultiSelect( bool b ) { m_bAllowMultipleSelection = b; }

				virtual void OnNodeAdded( TreeNode* pNode );

			private:

				void OnNodeSelection( Controls::Base* control );

				ScrollControl*		m_ScrollControl;
				bool				m_bAllowMultipleSelection;

		};
	}
}
//------------------------------------------------------------------------