/**
*	created:		2013-4-12   17:54
*	filename: 		FKTreeNode
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKButton.h"
#include "FKScrollControl.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class TreeControl;

		class FK_EXPORT TreeNode : public Base
		{
			public:

				FK_CONTROL( TreeNode, Base );

				virtual TreeNode* AddNode( const UITexObjSimpleInfo & strLabel );

				virtual void SetText( const UITexObjSimpleInfo & text );
				virtual const UITexObjSimpleInfo & GetText();
				virtual void SetImage( const UITexObjSimpleInfo & text );

				virtual void Open();
				virtual void Close();

				virtual void ExpandAll();

				virtual Button* GetButton();

				virtual void Render( Skin::Base* skin );
				virtual void Layout( Skin::Base* skin );
				virtual void PostLayout( Skin::Base* skin );

				virtual void SetRoot( bool b ) { m_bRoot = b; }
				virtual void SetTreeControl( TreeControl* pCtrl ) { m_TreeControl = pCtrl; }

				virtual void SetSelectable( bool b ) { m_bSelectable = b; }
				virtual bool IsSelected() { return m_bSelected; }
				virtual void SetSelected( bool b, bool FireEvents = true );

				virtual void DeselectAll();

				virtual Controls::Base::List & GetChildNodes();

				Event::Caller	onNamePress;
				Event::Caller	onRightPress;
				Event::Caller	onSelectChange;
				Event::Caller	onSelect;
				Event::Caller	onUnselect;

				void OnToggleButtonPress( Base* control );
				void OnDoubleClickName( Base* control );
				void OnRightPress( Base* control );
				void OnClickName( Base* control );

			protected:

				TreeControl*	m_TreeControl;
				Button*			m_ToggleButton;
				Button*			m_Title;

				bool			m_bRoot;
				bool			m_bSelected;
				bool			m_bSelectable;
		};

	}
}
//------------------------------------------------------------------------