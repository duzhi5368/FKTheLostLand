/**
*	created:		2013-4-12   23:18
*	filename: 		FKListBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
#include "Layout/FKTable.h"
#include "FKScrollControl.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class ScrollControl;

		class FK_EXPORT ListBox : public ScrollControl
		{
			public:

				FK_CONTROL( ListBox, ScrollControl );

				typedef std::list<Layout::TableRow*> Rows;

				Layout::TableRow* AddItem( const UITexObjSimpleInfo & strLabel, const String & strName = "" );

				void RemoveItem( Layout::TableRow* row );

				void Render( Skin::Base* skin );
				void Layout( Skin::Base* skin );

				void UnselectAll();

				void SetAllowMultiSelect( bool bMultiSelect ) { m_bMultiSelect = bMultiSelect; }
				bool AllowMultiSelect() const { return m_bMultiSelect; }

				const ListBox::Rows & GetSelectedRows() { return m_SelectedRows; }

				virtual Layout::TableRow* GetSelectedRow();
				virtual FK2DEngine2::String GetSelectedRowName();

				virtual void SetSelectedRow( FK2DEngine2::Controls::Base* pRow, bool bClearOthers = true );
				virtual void SelectByString( const UITexObjSimpleInfo & wstring, bool bClearOthers = true );

				FK2DEngine2::Event::Caller	onRowSelected;

				Controls::Layout::Table* GetTable() { return m_Table; }
				virtual void Clear();

				void SetColumnCount( int iCount ) { m_Table->SetColumnCount( iCount ); }
				void SetColumnWidth( int iCount, int iSize ) { m_Table->SetColumnWidth( iCount, iSize ); }

			protected:


				void OnRowSelected( Base* pControl );
				bool OnKeyDown( bool bDown );
				bool OnKeyUp( bool bDown );

				Controls::Layout::Table*		m_Table;
				ListBox::Rows					m_SelectedRows;

				bool m_bMultiSelect;
		};
	}
}
//------------------------------------------------------------------------