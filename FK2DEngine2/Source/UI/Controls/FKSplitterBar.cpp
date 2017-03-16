/**
*	created:		2013-4-12   1:03
*	filename: 		FKSplitterBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../../Include/FKUIOutSideHead.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace Controls;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( SplitterBar )
{
	SetTarget( this );
	RestrictToParent( true );
}

void SplitterBar::Layout( Skin::Base* /*skin*/ )
{
	MoveTo( X(), Y() );
}
//------------------------------------------------------------------------