/**
*	created:		2013-4-12   23:20
*	filename: 		FKListBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
class ListBoxRow : public Layout::TableRow
{
		FK_CONTROL_INLINE( ListBoxRow, Layout::TableRow )
		{
			SetMouseInputEnabled( true );
			SetSelected( false );
		}

		void Render( Skin::Base* skin )
		{
			skin->DrawListBoxLine( this, IsSelected(), GetEven() );
		}

		bool IsSelected() const
		{
			return m_bSelected;
		}

		void DoSelect()
		{
			SetSelected( true );
			onRowSelected.Call( this );
			Redraw();
		}

		void OnMouseClickLeft( int /*x*/, int /*y*/, bool bDown )
		{
			if ( bDown )
			{
				DoSelect();
			}
		}

		void SetSelected( bool b )
		{
			m_bSelected = b;

			// TODO: 从Skin中获取该值
			if ( b )
			{ SetTextColor( FK2DEngine2::Colors::White ); }
			else
			{ SetTextColor( FK2DEngine2::Colors::Black ); }
		}

	private:

		bool			m_bSelected;

};
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( ListBox )
{
	SetScroll( false, true );
	SetAutoHideBars( true );
	SetMargin( Margin( 1, 1, 1, 1 ) );
	m_InnerPanel->SetPadding( Padding( 2, 2, 2, 2 ) );
	m_Table = new Controls::Layout::Table( this );
	m_Table->SetColumnCount( 1 );
	m_bMultiSelect = false;
}

Layout::TableRow* ListBox::AddItem( const UITexObjSimpleInfo & strLabel, const String & strName )
{
	ListBoxRow* pRow = new ListBoxRow( this );
	m_Table->AddRow( pRow );
	pRow->SetCellText( 0, strLabel );
	pRow->SetName( strName );
	pRow->onRowSelected.Add( this, &ListBox::OnRowSelected );
	return pRow;
}

void ListBox::RemoveItem( Layout::TableRow* row )
{
	m_SelectedRows.erase( std::find( m_SelectedRows.begin(), m_SelectedRows.end(), row ) );
	m_Table->Remove( row );
}

void ListBox::Render( Skin::Base* skin )
{
	skin->DrawListBox( this );
}

void ListBox::Layout( Skin::Base* skin )
{
	BaseClass::Layout( skin );
	const FK2DEngine2::Rect & inner = m_InnerPanel->GetInnerBounds();
	m_Table->SetPos( inner.x, inner.y );
	m_Table->SetWidth( inner.w );
	m_Table->SizeToChildren( false, true );
	BaseClass::Layout( skin );
}

void ListBox::UnselectAll()
{
	std::list<Layout::TableRow*>::iterator it = m_SelectedRows.begin();

	while ( it != m_SelectedRows.end() )
	{
		ListBoxRow* pRow = static_cast<ListBoxRow*>( *it );
		it = m_SelectedRows.erase( it );
		pRow->SetSelected( false );
	}
}

void ListBox::OnRowSelected( Base* pControl )
{
	bool bClear = !FK2DEngine2::Input::IsShiftDown();

	if ( !AllowMultiSelect() ) { bClear = true; }

	SetSelectedRow( pControl, bClear );
}

Layout::TableRow* ListBox::GetSelectedRow()
{
	if ( m_SelectedRows.empty() ) { return NULL; }

	return *m_SelectedRows.begin();
}

FK2DEngine2::String ListBox::GetSelectedRowName()
{
	Layout::TableRow* row = GetSelectedRow();

	if ( !row ) { return ""; }

	return row->GetName();
}

void ListBox::Clear()
{
	UnselectAll();
	m_Table->Clear();
}

void ListBox::SetSelectedRow( FK2DEngine2::Controls::Base* pControl, bool bClearOthers )
{
	if ( bClearOthers )
	{ UnselectAll(); }

	ListBoxRow* pRow = fk_cast<ListBoxRow> ( pControl );

	if ( !pRow ) { return; }

	// TODO: 
	pRow->SetSelected( true );
	m_SelectedRows.push_back( pRow );
	onRowSelected.Call( this );
}



void ListBox::SelectByString( const UITexObjSimpleInfo & strName, bool bClearOthers )
{
	if ( bClearOthers )
	{ UnselectAll(); }

	Base::List & children = m_Table->GetChildren();

	for ( Base::List::iterator iter = children.begin(); iter != children.end(); ++iter )
	{
		ListBoxRow* pChild = fk_cast<ListBoxRow> ( *iter );

		if ( !pChild ) { continue; }

		if ( Utility::Strings::Wildcard( strName, pChild->GetText( 0 ) ) )
		{ SetSelectedRow( pChild, false ); }
	}
}

bool ListBox::OnKeyDown( bool bDown )
{
	if ( bDown )
	{
		Base::List & children = m_Table->Children;
		Base::List::const_iterator begin = children.begin();
		Base::List::const_iterator end = children.end();
		Controls::Base* sel_row = GetSelectedRow();

		if ( sel_row == NULL && !children.empty() )
		{ sel_row = children.front(); }

		Base::List::const_iterator result = std::find( begin, end, sel_row );

		if ( result != end )
		{
			Base::List::const_iterator next = result;
			++next;

			if ( next != end )
			{ result = next; }

			ListBoxRow* pRow = fk_cast<ListBoxRow> ( *result );

			if ( pRow )
			{
				pRow->DoSelect();
				Controls::VerticalScrollBar* pScroll = fk_cast<Controls::VerticalScrollBar> ( m_VerticalScrollBar );

				if ( pScroll ) { pScroll->NudgeDown( this ); }

				Redraw();
			}
		}
	}

	return true;
}

bool ListBox::OnKeyUp( bool bDown )
{
	if ( bDown )
	{
		Base::List & children = m_Table->Children;
		Base::List::const_iterator begin = children.begin();
		Base::List::const_iterator end = children.end();
		Controls::Base* sel_row = GetSelectedRow();

		if ( sel_row == NULL && !children.empty() )
		{ sel_row = children.front(); }

		Base::List::const_iterator result = std::find( begin, end, sel_row );

		if ( result != end )
		{
			if ( result != begin )
			{ --result; }

			ListBoxRow* pRow = fk_cast<ListBoxRow> ( *result );

			if ( pRow )
			{
				pRow->DoSelect();
				Controls::VerticalScrollBar* pScroll = fk_cast<Controls::VerticalScrollBar> ( m_VerticalScrollBar );

				if ( pScroll ) { pScroll->NudgeUp( this ); }

				Redraw();
			}
		}
	}

	return true;
}
//------------------------------------------------------------------------