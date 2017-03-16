/**
*	created:		2013-4-11   21:56
*	filename: 		FKDragAndDrop
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <sstream>
//------------------------------------------------------------------------
#include "FKSkin.h"
#include "FKStructures.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace DragAndDrop
	{
		extern FK_EXPORT Package*	CurrentPackage;
		extern FK_EXPORT FK2DEngine2::Controls::Base*	SourceControl;
		extern FK_EXPORT FK2DEngine2::Controls::Base*	HoveredControl;

		bool FK_EXPORT Start( FK2DEngine2::Controls::Base* pControl, Package* pPackage );

		bool FK_EXPORT OnMouseButton( FK2DEngine2::Controls::Base* pHoveredControl, int x, int y, bool bDown );
		void FK_EXPORT OnMouseMoved( FK2DEngine2::Controls::Base* pHoveredControl, int x, int y );

		void FK_EXPORT RenderOverlay( FK2DEngine2::Controls::Canvas* pCanvas, Skin::Base* skin );

		void FK_EXPORT ControlDeleted( FK2DEngine2::Controls::Base* pControl );
	}

}
//------------------------------------------------------------------------