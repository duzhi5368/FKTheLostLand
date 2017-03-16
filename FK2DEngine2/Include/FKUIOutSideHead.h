/**
*	created:		2013-4-25   15:13
*	filename: 		FKUIOutSideHead
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "UI/FKMacros.h"
#include "UI/FKExports.h"
#include "UI/FKAlign.h"
#include "UI/FKAnim.h"
#include "UI/FKBaseRender.h"
#include "UI/FKControlList.h"
#include "UI/FKDragAndDrop.h"
#include "UI/FKEvents.h"
#include "UI/FKFont.h"
#include "UI/FKHook.h"
#include "UI/FKInputHandler.h"
#include "UI/FKPlatform.h"
#include "UI/FKSkin.h"
#include "UI/FKStructures.h"
#include "UI/FKTextObject.h"
#include "UI/FKTexture.h"
#include "UI/FKToolTip.h"
#include "UI/FKUserData.h"
#include "UI/FKUtility.h"
#include "UI/FKWindowProvider.h"

#include "UI/Input/FKWindows.h"

#include "UI/Renderers/FKDirectX9.h"

#include "UI/Skins/FKSimple.h"
#include "UI/Skins/FKTexturedBase.h"
#include "UI/Skins/FKTexturing.h"

#include "UI/Util/FKControlFactory.h"
#include "UI/Util/FKImportExport.h"

#include "UI/Controls/Dialogs/FKFileOpen.h"
#include "UI/Controls/Dialogs/FKFileSave.h"
#include "UI/Controls/Dialogs/FKFolderOpen.h"
#include "UI/Controls/Layout/FKPosition.h"
#include "UI/Controls/Layout/FKTable.h"
#include "UI/Controls/Layout/FKTile.h"
#include "UI/Controls/Property/FKBaseProperty.h"
#include "UI/Controls/Property/FKCheckBox.h"
#include "UI/Controls/Property/FKColorSelector.h"
#include "UI/Controls/Property/FKComboBox.h"
#include "UI/Controls/Property/FKFile.h"
#include "UI/Controls/Property/FKFolder.h"
#include "UI/Controls/Property/FKText.h"
#include "UI/Controls/FKBase.h"
#include "UI/Controls/FKButton.h"
#include "UI/Controls/FKCanvas.h"
#include "UI/Controls/FKCheckBox.h"
#include "UI/Controls/FKCollapsibleCategory.h"
#include "UI/Controls/FKCollapsibleList.h"
#include "UI/Controls/FKColorPicker.h"
#include "UI/Controls/FKColorControls.h"
#include "UI/Controls/FKComboBox.h"
#include "UI/Controls/FKCrossSplitter.h"
#include "UI/Controls/FKDockBase.h"
#include "UI/Controls/FKDockedTabControl.h"
#include "UI/Controls/FKDragger.h"
#include "UI/Controls/FKFieldLabel.h"
#include "UI/Controls/FKFilePicker.h"
#include "UI/Controls/FKFolderPicker.h"
#include "UI/Controls/FKGroupBox.h"
#include "UI/Controls/FKHighlight.h"
#include "UI/Controls/FKHorizontalScrollBar.h"
#include "UI/Controls/FKHorizontalSlider.h"
#include "UI/Controls/FKHSVColorPicker.h"
#include "UI/Controls/FKImagePanel.h"
#include "UI/Controls/FKLabel.h"
#include "UI/Controls/FKLabelClickable.h"
#include "UI/Controls/FKListBox.h"
#include "UI/Controls/FKMenu.h"
#include "UI/Controls/FKMenuItem.h"
#include "UI/Controls/FKMenuStrip.h"
#include "UI/Controls/FKModal.h"
#include "UI/Controls/FKNumericUpDown.h"
#include "UI/Controls/FKPageControl.h"
#include "UI/Controls/FKProgressBar.h"
#include "UI/Controls/FKProperties.h"
#include "UI/Controls/FKPropertyTree.h"
#include "UI/Controls/FKRadioButton.h"
#include "UI/Controls/FKRadioButtonController.h"
#include "UI/Controls/FKRectangle.h"
#include "UI/Controls/FKResizer.h"
#include "UI/Controls/FKRichLabel.h"
#include "UI/Controls/FKScrollBar.h"
#include "UI/Controls/FKScrollBarBar.h"
#include "UI/Controls/FKScrollBarButton.h"
#include "UI/Controls/FKScrollControl.h"
#include "UI/Controls/FKSlider.h"
#include "UI/Controls/FKSplitterBar.h"
#include "UI/Controls/FKSplitters.h"
#include "UI/Controls/FKStatusBar.h"
#include "UI/Controls/FKTabButton.h"
#include "UI/Controls/FKTabControl.h"
#include "UI/Controls/FKTabTitleBar.h"
#include "UI/Controls/FKText.h"
#include "UI/Controls/FKTextBox.h"
#include "UI/Controls/FKToolBar.h"
#include "UI/Controls/FKTreeControl.h"
#include "UI/Controls/FKTreeNode.h"
#include "UI/Controls/FKVerticalScrollBar.h"
#include "UI/Controls/FKVerticalSlider.h"
#include "UI/Controls/FKWindowButtons.h"
#include "UI/Controls/FKWindowControl.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace core{}
	namespace math{}
	namespace video{}
	namespace input{}
	namespace audio{}

	namespace Controls
	{
		namespace Layout{}
		namespace Property{}
		namespace Internal{}
	}
	namespace Input
	{
		namespace Message{}
	}
	namespace Skin
	{
		namespace Texturing{}
		namespace Symbol{}
	}
	namespace ImportExport{}
	namespace ControlFactory{}
	namespace Align{}
	namespace Anim{}
	namespace Event{}
	namespace DragAndDrop{}
	namespace Hook{}
	namespace Key{}
	namespace Platform{}
	namespace CursorType{}
	namespace ToolTip{}
	namespace Utility{}
	namespace Dialogs{}
	namespace ControlsInternal{}
	namespace video{}
	namespace Pos{}
}
//------------------------------------------------------------------------