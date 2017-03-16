/**
*	created:		2013-4-12   18:01
*	filename: 		FKPropertyTree
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "../../FKUIOutSideHead.h"
#include "../FKSkin.h"
#include "FKTreeControl.h"
#include "FKProperties.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class PropertyTreeNode : public TreeNode
		{
			public:

				FK_CONTROL_INLINE( PropertyTreeNode, TreeNode )
				{
					m_Title->SetTextColorOverride( GetSkin()->Colors.Properties.Title );
				}

				virtual void Render( Skin::Base* skin )
				{
					skin->DrawPropertyTreeNode( this, m_InnerPanel->X(), m_InnerPanel->Y() );
				}

		};

		class PropertyTree : public TreeControl
		{
			public:

				FK_CONTROL_INLINE( PropertyTree, TreeControl )
				{
				}

				Properties* Add( const UITexObjSimpleInfo & text );
				Properties* Find( const UITexObjSimpleInfo & text );
		};

	}
}
//------------------------------------------------------------------------