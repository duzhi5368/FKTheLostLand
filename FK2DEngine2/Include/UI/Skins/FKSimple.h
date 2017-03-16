/**
*	created:		2013-4-11   22:50
*	filename: 		FKSimple
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Skin
	{
		class Simple : public FK2DEngine2::Skin::Base
		{
		public:

			Simple( FK2DEngine2::video::Base* renderer ) : FK2DEngine2::Skin::Base( renderer )
			{
			}

			FK2DEngine2::Color m_colBorderColor;
			FK2DEngine2::Color m_colControlOutlineLight;
			FK2DEngine2::Color m_colControlOutlineLighter;
			FK2DEngine2::Color m_colBG;
			FK2DEngine2::Color m_colBGDark;
			FK2DEngine2::Color m_colControl;
			FK2DEngine2::Color m_colControlBorderHighlight;
			FK2DEngine2::Color m_colControlDarker;
			FK2DEngine2::Color m_colControlOutlineNormal;
			FK2DEngine2::Color m_colControlBright;
			FK2DEngine2::Color m_colControlDark;
			FK2DEngine2::Color m_colHighlightBG;
			FK2DEngine2::Color m_colHighlightBorder;
			FK2DEngine2::Color m_colToolTipBackground;
			FK2DEngine2::Color m_colToolTipBorder;
			FK2DEngine2::Color m_colModal;

			Simple()
			{
				m_colBorderColor			= FK2DEngine2::Color( 80, 80, 80, 255 );
				m_colBG						= FK2DEngine2::Color( 248, 248, 248, 255 );
				m_colBGDark					= FK2DEngine2::Color( 235, 235, 235, 255 );
				m_colControl				= FK2DEngine2::Color( 240, 240, 240, 255 );
				m_colControlBright			= FK2DEngine2::Color( 255, 255, 255, 255 );
				m_colControlDark			= FK2DEngine2::Color( 214, 214, 214, 255 );
				m_colControlDarker			= FK2DEngine2::Color( 180, 180, 180, 255 );
				m_colControlOutlineNormal	= FK2DEngine2::Color( 112, 112, 112, 255 );
				m_colControlOutlineLight	= FK2DEngine2::Color( 144, 144, 144, 255 );
				m_colControlOutlineLighter	= FK2DEngine2::Color( 210, 210, 210, 255 );
				m_colHighlightBG			= FK2DEngine2::Color( 192, 221, 252, 255 );
				m_colHighlightBorder		= FK2DEngine2::Color( 51, 153, 255, 255 );
				m_colToolTipBackground		= FK2DEngine2::Color( 255, 255, 225, 255 );
				m_colToolTipBorder			= FK2DEngine2::Color( 0, 0, 0, 255 );
				m_colModal = FK2DEngine2::Color( 25, 25, 25, 150 );
				m_DefaultFont.facename	= L"MiFK2DEngine2crosoft Sans Serif";
				m_DefaultFont.size		= 11;
			}

			virtual void DrawGenericPanel( Controls::Base* control )
			{
				// TODO.
			}

			virtual void DrawButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled )
			{
				int w = control->Width();
				int h = control->Height();
				DrawButton( w, h, bDepressed, bHovered );
			}

			virtual void DrawWindowCloseButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled )
			{
				// TODO.
				DrawButton( control, bDepressed, bHovered, bDisabled );
			}

			virtual void DrawWindowMaximizeButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled, bool bMaximized )
			{
				// TODO.
				DrawButton( control, bDepressed, bHovered, bDisabled );
			}

			virtual void DrawWindowMinimizeButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled )
			{
				// TODO.
				DrawButton( control, bDepressed, bHovered, bDisabled );
			}

			virtual void DrawMenuItem( FK2DEngine2::Controls::Base* control, bool bSubmenuOpen, bool bChecked )
			{
				if ( bSubmenuOpen || control->IsHovered() )
				{
					m_Render->SetDrawColor( m_colHighlightBG );
					m_Render->DrawFilledRect( control->GetRenderBounds() );
					m_Render->SetDrawColor( m_colHighlightBorder );
					m_Render->DrawLinedRect( control->GetRenderBounds() );
				}

				if ( bChecked )
				{
					m_Render->SetDrawColor( Color( 0, 0, 0, 255 ) );
					FK2DEngine2::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );
					DrawCheck( r );
				}
			}

			virtual void DrawMenuStrip( FK2DEngine2::Controls::Base* control )
			{
				int w = control->Width();
				int h = control->Height();
				m_Render->SetDrawColor( FK2DEngine2::Color( 246, 248, 252, 255 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( 0, 0, w, h ) );
				m_Render->SetDrawColor( FK2DEngine2::Color( 218, 224, 241, 150 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( 0, h * 0.4f, w, h * 0.6f ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( 0, h * 0.5f, w, h * 0.5f ) );
			}

			virtual void DrawMenu( FK2DEngine2::Controls::Base* control, bool bPaddingDisabled )
			{
				int w = control->Width();
				int h = control->Height();
				m_Render->SetDrawColor( m_colControlBright );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( 0, 0, w, h ) );

				if ( !bPaddingDisabled )
				{
					m_Render->SetDrawColor( m_colControl );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 0, 22, h ) );
				}

				m_Render->SetDrawColor( m_colControlOutlineNormal );
				m_Render->DrawLinedRect( FK2DEngine2::Rect( 0, 0, w, h ) );
			}

			virtual void DrawShadow( FK2DEngine2::Controls::Base* control )
			{
				int w = control->Width();
				int h = control->Height();
				int x = 4;
				int y = 6;
				m_Render->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 10 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( x, y, w, h ) );
				x += 2;
				m_Render->DrawFilledRect( FK2DEngine2::Rect( x, y, w, h ) );
				y += 2;
				m_Render->DrawFilledRect( FK2DEngine2::Rect( x, y, w, h ) );
			}

			virtual void DrawButton( int w, int h, bool bDepressed, bool bHovered, bool bSquared = false )
			{
				if ( bDepressed )	{ m_Render->SetDrawColor( m_colControlDark ); }
				else if ( bHovered ) { m_Render->SetDrawColor( m_colControlBright ); }
				else				{ m_Render->SetDrawColor( m_colControl ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, w - 2, h - 2 ) );

				if ( bDepressed )	{ m_Render->SetDrawColor( m_colControlDark ); }
				else if ( bHovered ) { m_Render->SetDrawColor( m_colControl ); }
				else				{ m_Render->SetDrawColor( m_colControlDark ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, h * 0.5, w - 2, h * 0.5 - 2 ) );

				if ( !bDepressed )
				{
					m_Render->SetDrawColor( m_colControlBright );
					m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 1, 1, w - 2, h - 2 ), bSquared );
				}
				else
				{
					m_Render->SetDrawColor( m_colControlDarker );
					m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 1, 1, w - 2, h - 2 ), bSquared );
				}

				// 边线
				m_Render->SetDrawColor( m_colControlOutlineNormal );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 0, 0, w, h ), bSquared );
			}

			virtual void DrawRadioButton( FK2DEngine2::Controls::Base* control, bool bSelected, bool bDepressed )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				// 内部颜色
				if ( control->IsHovered() )	{ m_Render->SetDrawColor( FK2DEngine2::Color( 220, 242, 254, 255 ) ); }
				else { m_Render->SetDrawColor( m_colControlBright ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h - 2 ) );

				// 边线
				if ( control->IsHovered() )	{ m_Render->SetDrawColor( FK2DEngine2::Color( 85, 130, 164, 255 ) ); }
				else { m_Render->SetDrawColor( m_colControlOutlineLight ); }

				m_Render->DrawShavedCornerRect( rect );
				m_Render->SetDrawColor( FK2DEngine2::Color( 0,  50,  60, 15 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w - 4, rect.h - 4 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w * 0.3f, rect.h - 4 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w - 4, rect.h * 0.3f ) );

				if ( control->IsHovered() )	{ m_Render->SetDrawColor( FK2DEngine2::Color( 121, 198, 249, 255 ) ); }
				else { m_Render->SetDrawColor( FK2DEngine2::Color( 0, 50, 60, 50 ) ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 3, 1, rect.h - 5 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 3, rect.y + 2, rect.w - 5, 1 ) );

				if ( bSelected )
				{
					m_Render->SetDrawColor( FK2DEngine2::Color( 40, 230, 30, 255 ) );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w - 4, rect.h - 4 ) );
				}
			}


			virtual void DrawCheckBox( FK2DEngine2::Controls::Base* control, bool bSelected, bool bDepressed )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				// 内部颜色
				if ( control->IsHovered() )	{ m_Render->SetDrawColor( FK2DEngine2::Color( 220, 242, 254, 255 ) ); }
				else { m_Render->SetDrawColor( m_colControlBright ); }

				m_Render->DrawFilledRect( rect );

				// 边线
				if ( control->IsHovered() )	{ m_Render->SetDrawColor( FK2DEngine2::Color( 85, 130, 164, 255 ) ); }
				else { m_Render->SetDrawColor( m_colControlOutlineLight ); }

				m_Render->DrawLinedRect( rect );
				m_Render->SetDrawColor( FK2DEngine2::Color( 0,  50,  60, 15 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w - 4, rect.h - 4 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w * 0.3f, rect.h - 4 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w - 4, rect.h * 0.3f ) );

				if ( control->IsHovered() )	{ m_Render->SetDrawColor( FK2DEngine2::Color( 121, 198, 249, 255 ) ); }
				else { m_Render->SetDrawColor( FK2DEngine2::Color( 0, 50, 60, 50 ) ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, 1, rect.h - 4 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2, rect.y + 2, rect.w - 4, 1 ) );

				if ( bDepressed )
				{
					m_Render->SetDrawColor( Color( 100, 100, 100, 255 ) );
					FK2DEngine2::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );
					DrawCheck( r );
				}
				else if ( bSelected )
				{
					m_Render->SetDrawColor( Color( 0, 0, 0, 255 ) );
					FK2DEngine2::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );
					DrawCheck( r );
				}
			}

			virtual void DrawGroupBox( FK2DEngine2::Controls::Base* control, int textStart, int textHeight, int textWidth )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				rect.y += textHeight * 0.5f;
				rect.h -= textHeight * 0.5f;
				FK2DEngine2::Color m_colDarker			= FK2DEngine2::Color( 0,  50,  60, 50 );
				FK2DEngine2::Color m_colLighter		= FK2DEngine2::Color( 255, 255, 255, 150 );
				m_Render->SetDrawColor( m_colLighter );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y + 1, textStart - 3, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1 + textStart + textWidth, rect.y + 1, rect.w - textStart + textWidth - 2, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, ( rect.y + rect.h ) - 1, rect.w - 2, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y + 1, 1, rect.h ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( ( rect.x + rect.w ) - 2, rect.y + 1, 1, rect.h - 1 ) );
				m_Render->SetDrawColor( m_colDarker );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y, textStart - 3, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1 + textStart + textWidth, rect.y, rect.w - textStart - textWidth - 2, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, ( rect.y + rect.h ) - 1, rect.w - 2, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x, rect.y + 1, 1, rect.h - 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( ( rect.x + rect.w ) - 1, rect.y + 1, 1, rect.h - 1 ) );
			}

			virtual void DrawTextBox( FK2DEngine2::Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				bool bHasFocus = control->HasFocus();
				// 内部颜色
				m_Render->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 255 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h - 2 ) );
				m_Render->SetDrawColor( m_colControlOutlineLight );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y, rect.w - 2, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x, rect.y + 1, 1, rect.h - 2 ) );
				m_Render->SetDrawColor( m_colControlOutlineLighter );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, ( rect.y + rect.h ) - 1, rect.w - 2, 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( ( rect.x + rect.w ) - 1, rect.y + 1, 1, rect.h - 2 ) );

				if ( bHasFocus )
				{
					m_Render->SetDrawColor( FK2DEngine2::Color( 50, 200, 255, 150 ) );
					m_Render->DrawLinedRect( rect );
				}
			}

			virtual void DrawTabButton( FK2DEngine2::Controls::Base* control, bool bActive, int dir )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				bool bHovered = control->IsHovered();

				if ( bHovered ) { m_Render->SetDrawColor( m_colControlBright ); }
				else		   { m_Render->SetDrawColor( m_colControl ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h - 1 ) );

				if ( bHovered ) { m_Render->SetDrawColor( m_colControl ); }
				else		   { m_Render->SetDrawColor( m_colControlDark ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, rect.h * 0.5, rect.w - 2, rect.h * 0.5 - 1 ) );
				m_Render->SetDrawColor( m_colControlBright );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h ) );
				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 0, 0, rect.w, rect.h ) );
			}

			virtual void DrawTabControl( FK2DEngine2::Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				m_Render->SetDrawColor( m_colControl );
				m_Render->DrawFilledRect( rect );
				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawLinedRect( rect );
			}

			virtual void DrawWindow( FK2DEngine2::Controls::Base* control, int topHeight, bool inFocus )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				if ( inFocus )
				{ m_Render->SetDrawColor( FK2DEngine2::Color( 87, 164, 232, 230 ) ); }
				else
				{ m_Render->SetDrawColor( FK2DEngine2::Color( 87 * 0.70, 164 * 0.70, 232 * 0.70, 230 ) ); }

				int iBorderSize = 5;
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y + 1, rect.w - 2, topHeight - 1 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y + topHeight - 1, iBorderSize, rect.h - 2 - topHeight ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + rect.w - iBorderSize, rect.y + topHeight - 1, iBorderSize, rect.h - 2 - topHeight ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 1, rect.y + rect.h - iBorderSize, rect.w - 2, iBorderSize ) );

				m_Render->SetDrawColor( FK2DEngine2::Color( m_colControlDark.r, m_colControlDark.g, m_colControlDark.b, 230 ) );
				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + iBorderSize + 1, rect.y + topHeight, rect.w - iBorderSize * 2 - 2, rect.h - topHeight - iBorderSize - 1 ) );

				m_Render->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 100 ) );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2 ) );

				m_Render->SetDrawColor( m_colBorderColor );

				m_Render->SetDrawColor( m_colControlOutlineNormal );
				m_Render->DrawLinedRect( FK2DEngine2::Rect( rect.x + iBorderSize, rect.y + topHeight - 1, rect.w - 10, rect.h - topHeight - ( iBorderSize - 1 ) ) );

				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( rect.x, rect.y, rect.w, rect.h ) );
			}

			virtual void DrawHighlight( FK2DEngine2::Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				m_Render->SetDrawColor( FK2DEngine2::Color( 255, 100, 255, 255 ) );
				m_Render->DrawFilledRect( rect );
			}

			virtual void DrawScrollBar( FK2DEngine2::Controls::Base* control, bool isHorizontal, bool bDepressed )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				if ( bDepressed )
				{ m_Render->SetDrawColor( m_colControlDarker ); }
				else
				{ m_Render->SetDrawColor( m_colControlBright ); }

				m_Render->DrawFilledRect( rect );
			}

			virtual void DrawScrollBarBar( Controls::Base* control, bool bDepressed, bool isHovered, bool isHorizontal )
			{
				//TODO:
				DrawButton( control, bDepressed, isHovered, false );
			}

			virtual void DrawTabTitleBar( FK2DEngine2::Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				m_Render->SetDrawColor( FK2DEngine2::Color( 177, 193, 214, 255 ) );
				m_Render->DrawFilledRect( rect );
				m_Render->SetDrawColor( m_colBorderColor );
				rect.h += 1;
				m_Render->DrawLinedRect( rect );
			}

			virtual void DrawProgressBar( FK2DEngine2::Controls::Base* control, bool isHorizontal, float progress )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				FK2DEngine2::Color FillColour( 0, 211, 40, 255 );

				if ( isHorizontal )
				{
					//Background
					m_Render->SetDrawColor( m_colControlDark );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h - 2 ) );
					//Right half
					m_Render->SetDrawColor( FillColour );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w * progress - 2, rect.h - 2 ) );
					m_Render->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 150 ) );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h * 0.45f ) );
				}
				else
				{
					//Background
					m_Render->SetDrawColor( m_colControlDark );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h - 2 ) );
					//Top half
					m_Render->SetDrawColor( FillColour );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1 + ( rect.h * ( 1 - progress ) ), rect.w - 2, rect.h * progress - 2 ) );
					m_Render->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 150 ) );
					m_Render->DrawFilledRect( FK2DEngine2::Rect( 1, 1, rect.w * 0.45f, rect.h - 2 ) );
				}

				m_Render->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 150 ) );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 1, 1, rect.w - 2, rect.h - 2 ) );
				m_Render->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 70 ) );
				m_Render->DrawShavedCornerRect( FK2DEngine2::Rect( 2, 2, rect.w - 4, rect.h - 4 ) );
				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawShavedCornerRect( rect );
			}

			virtual void DrawListBox( FK2DEngine2::Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				m_Render->SetDrawColor( m_colControlBright );
				m_Render->DrawFilledRect( rect );
				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawLinedRect( rect );
			}

			virtual void DrawListBoxLine( FK2DEngine2::Controls::Base* control, bool bSelected, bool bEven )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				if ( bSelected )
				{
					m_Render->SetDrawColor( m_colHighlightBorder );
					m_Render->DrawFilledRect( rect );
				}
				else if ( control->IsHovered() )
				{
					m_Render->SetDrawColor( m_colHighlightBG );
					m_Render->DrawFilledRect( rect );
				}
			}


			virtual void DrawSlider( FK2DEngine2::Controls::Base* control, bool bIsHorizontal, int numNotches, int barSize )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				if ( bIsHorizontal )
				{
					rect.y += rect.h * 0.4;
					rect.h -= rect.h * 0.8;
				}
				else
				{
					rect.x += rect.w * 0.4;
					rect.w -= rect.w * 0.8;
				}

				m_Render->SetDrawColor( m_colBGDark );
				m_Render->DrawFilledRect( rect );
				m_Render->SetDrawColor( m_colControlDarker );
				m_Render->DrawLinedRect( rect );
			}

			virtual void DrawComboBox( FK2DEngine2::Controls::Base* control, bool bIsDown, bool bIsMenuOpen )
			{
				DrawTextBox( control );
			}

			virtual void DrawKeyboardHighlight( FK2DEngine2::Controls::Base* control, const FK2DEngine2::Rect & r, int iOffset )
			{
				FK2DEngine2::Rect rect = r;
				rect.x += iOffset;
				rect.y += iOffset;
				rect.w -= iOffset * 2;
				rect.h -= iOffset * 2;
				//draw the top and bottom
				bool skip = true;

				for ( int i = 0; i < rect.w * 0.5; i++ )
				{
					m_Render->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 255 ) );

					if ( !skip )
					{
						m_Render->DrawPixel( rect.x + ( i * 2 ), rect.y );
						m_Render->DrawPixel( rect.x + ( i * 2 ), rect.y + rect.h - 1 );
					}
					else
					{ skip = !skip; }
				}

				skip = false;

				for ( int i = 0; i < rect.h * 0.5; i++ )
				{
					m_Render->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 255 ) );

					if ( !skip )
					{
						m_Render->DrawPixel( rect.x , rect.y + i * 2 );
						m_Render->DrawPixel( rect.x + rect.w - 1, rect.y + i * 2 );
					}
					else
					{ skip = !skip; }
				}
			}

			virtual void DrawToolTip( FK2DEngine2::Controls::Base* control )
			{
				FK2DEngine2::Rect rct = control->GetRenderBounds();
				rct.x -= 3;
				rct.y -= 3;
				rct.w += 6;
				rct.h += 6;
				m_Render->SetDrawColor( m_colToolTipBackground );
				m_Render->DrawFilledRect( rct );
				m_Render->SetDrawColor( m_colToolTipBorder );
				m_Render->DrawLinedRect( rct );
			}

			virtual void DrawScrollButton( FK2DEngine2::Controls::Base* control, int iDirection, bool bDepressed, bool bHovered, bool bDisabled )
			{
				DrawButton( control, bDepressed, false, false );
				m_Render->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 240 ) );
				FK2DEngine2::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );

				if ( iDirection == FK2DEngine2::Pos::Top ) { DrawArrowUp( r ); }
				else if ( iDirection == FK2DEngine2::Pos::Bottom ) { DrawArrowDown( r ); }
				else if ( iDirection == FK2DEngine2::Pos::Left ) { DrawArrowLeft( r ); }
				else { DrawArrowRight( r ); }
			}

			virtual void DrawComboDownArrow( FK2DEngine2::Controls::Base* control, bool bHovered, bool bDown, bool bOpen, bool bDisabled )
			{
				m_Render->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 240 ) );
				FK2DEngine2::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );
				DrawArrowDown( r );
			}

			virtual void DrawNumericUpDownButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bUp )
			{
				m_Render->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 240 ) );
				FK2DEngine2::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );

				if ( bUp ) { DrawArrowUp( r ); }
				else { DrawArrowDown( r ); }
			}

			virtual void DrawTreeButton( Controls::Base* control, bool bOpen )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				rect.x += 2;
				rect.y += 2;
				rect.w -= 4;
				rect.h -= 4;
				m_Render->SetDrawColor( m_colControlBright );
				m_Render->DrawFilledRect( rect );
				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawLinedRect( rect );
				m_Render->SetDrawColor( m_colBorderColor );

				if ( !bOpen )
				{ m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + rect.w / 2,	rect.y + 2,				1,			rect.h - 4 ) ); }

				m_Render->DrawFilledRect( FK2DEngine2::Rect( rect.x + 2,			rect.y + rect.h / 2,		rect.w - 4,	1 ) );
			}

			virtual void DrawTreeControl( Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				m_Render->SetDrawColor( m_colControlBright );
				m_Render->DrawFilledRect( rect );
				m_Render->SetDrawColor( m_colBorderColor );
				m_Render->DrawLinedRect( rect );
			}

			void DrawTreeNode( Controls::Base* ctrl, bool bOpen, bool bSelected, int iLabelHeight, int iLabelWidth, int iHalfWay, int iLastBranch, bool bIsRoot )
			{
				if ( bSelected )
				{
					GetRender()->SetDrawColor( Color( 0, 150, 255, 100 ) );
					GetRender()->DrawFilledRect( FK2DEngine2::Rect( 17, 0, iLabelWidth + 2, iLabelHeight - 1 ) );
					GetRender()->SetDrawColor( Color( 0, 150, 255, 200 ) );
					GetRender()->DrawLinedRect( FK2DEngine2::Rect( 17, 0, iLabelWidth + 2, iLabelHeight - 1 ) );
				}

				Base::DrawTreeNode( ctrl, bOpen, bSelected, iLabelHeight, iLabelWidth, iHalfWay, iLastBranch, bIsRoot );
			}

			virtual void DrawStatusBar( Controls::Base* control )
			{
				// TODO.
			}

			void DrawColorDisplay( Controls::Base* control, FK2DEngine2::Color color )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();

				if ( color.a != 255 )
				{
					GetRender()->SetDrawColor( FK2DEngine2::Color( 255, 255, 255, 255 ) );
					GetRender()->DrawFilledRect( rect );
					GetRender()->SetDrawColor( FK2DEngine2::Color( 128, 128, 128, 128 ) );
					GetRender()->DrawFilledRect( FK2DEngine2::Rect( 0, 0, rect.w * 0.5, rect.h * 0.5 ) );
					GetRender()->DrawFilledRect( FK2DEngine2::Rect( rect.w * 0.5, rect.h * 0.5, rect.w * 0.5, rect.h * 0.5 ) );
				}

				GetRender()->SetDrawColor( color );
				GetRender()->DrawFilledRect( rect );
				GetRender()->SetDrawColor( FK2DEngine2::Color( 0, 0, 0, 255 ) );
				GetRender()->DrawLinedRect( rect );
			}

			virtual void DrawModalControl( Controls::Base* control )
			{
				if ( control->ShouldDrawBackground() )
				{
					FK2DEngine2::Rect rect = control->GetRenderBounds();
					GetRender()->SetDrawColor( m_colModal );
					GetRender()->DrawFilledRect( rect );
				}
			}

			virtual void DrawMenuDivider( Controls::Base* control )
			{
				FK2DEngine2::Rect rect = control->GetRenderBounds();
				GetRender()->SetDrawColor( m_colBGDark );
				GetRender()->DrawFilledRect( rect );
				GetRender()->SetDrawColor( m_colControlDarker );
				GetRender()->DrawLinedRect( rect );
			}

			virtual void DrawMenuRightArrow( Controls::Base* control )
			{
				DrawArrowRight( control->GetRenderBounds() );
			}

			virtual void DrawSlideButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHorizontal )
			{
				DrawButton( control, bDepressed, control->IsHovered(), control->IsDisabled() );
			}

			virtual void DrawCategoryHolder( Controls::Base* ctrl ) {}
			virtual void DrawCategoryInner( Controls::Base* ctrl, bool bCollapsed ) {}
		};
	}
}
//------------------------------------------------------------------------