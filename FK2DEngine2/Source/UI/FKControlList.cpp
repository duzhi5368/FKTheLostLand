/**
*	created:		2013-4-11   21:43
*	filename: 		FKControlList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
void ControlList::Enable()
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->SetDisabled( false );
	}
}
//------------------------------------------------------------------------
void ControlList::Disable()
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->SetDisabled( true );
	}
}
//------------------------------------------------------------------------
void ControlList::Show()
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->Show();
	}
}
//------------------------------------------------------------------------
void ControlList::Hide()
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->Hide();
	}
}
//------------------------------------------------------------------------
FK2DEngine2::UITexObjSimpleInfo ControlList::GetValue()
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		return ( *it )->GetValue();
	}

	return "";
}
//------------------------------------------------------------------------
void ControlList::SetValue( const FK2DEngine2::UITexObjSimpleInfo & value )
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->SetValue( value );
	}
}
//------------------------------------------------------------------------
void ControlList::MoveBy( const FK2DEngine2::Point & point )
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->MoveBy( point.x, point.y );
	}
}
//------------------------------------------------------------------------
void ControlList::DoAction()
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->DoAction();
	}
}
//------------------------------------------------------------------------
void ControlList::SetActionInternal( FK2DEngine2::Event::Handler* pObject, 
									void ( FK2DEngine2::Event::Handler::*f )( FK2DEngine2::Event::Info ), const FK2DEngine2::Event::Packet & packet )
{
	for ( List::const_iterator it = list.begin(); it != list.end(); ++it )
	{
		( *it )->SetAction( pObject, f, packet );
	}
}
//------------------------------------------------------------------------