/**
*	created:		2013-4-11   17:20
*	filename: 		FKSkin
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBaseRender.h"
#include "FKFont.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class Base;
	}

	namespace Skin
	{
		namespace Symbol
		{
			static const unsigned char None				= 0;
			static const unsigned char ArrowRight		= 1;
			static const unsigned char Check			= 2;
			static const unsigned char Dot				= 3;
		}

		class FK_EXPORT Base
		{
			public:

				Base( FK2DEngine2::video::Base* renderer = NULL )
				{
					m_DefaultFont.facename = L"Arial";
					m_DefaultFont.size = 10.0f;
					m_Render = renderer;
				}

				virtual ~Base()
				{
					ReleaseFont( &m_DefaultFont );
				}

				virtual void ReleaseFont( FK2DEngine2::Font* fnt )
				{
					if ( !fnt ) { return; }

					if ( !m_Render ) { return; }

					m_Render->FreeFont( fnt );
				}

				virtual void DrawGenericPanel( Controls::Base* control ) = 0;

				virtual void DrawButton( Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled ) = 0;
				virtual void DrawTabButton( Controls::Base* control, bool bActive, int dir ) = 0;
				virtual void DrawTabControl( Controls::Base* control ) = 0;
				virtual void DrawTabTitleBar( Controls::Base* control ) = 0;

				virtual void DrawMenuItem( Controls::Base* control, bool bSubmenuOpen, bool bChecked ) = 0;
				virtual void DrawMenuStrip( Controls::Base* control ) = 0;
				virtual void DrawMenu( Controls::Base* control, bool bPaddingDisabled ) = 0;
				virtual void DrawMenuRightArrow( Controls::Base* control ) = 0;

				virtual void DrawRadioButton( Controls::Base* control, bool bSelected, bool bDepressed ) = 0;
				virtual void DrawCheckBox( Controls::Base* control, bool bSelected, bool bDepressed ) = 0;
				virtual void DrawGroupBox( Controls::Base* control, int textStart, int textHeight, int textWidth ) = 0;
				virtual void DrawTextBox( Controls::Base* control ) = 0;

				virtual void DrawWindow( FK2DEngine2::Controls::Base* control, int topHeight, bool inFocus ) = 0;
				virtual void DrawWindowCloseButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled ) = 0;
				virtual void DrawWindowMaximizeButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled, bool bMaximized ) = 0;
				virtual void DrawWindowMinimizeButton( FK2DEngine2::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled ) = 0;

				virtual void DrawHighlight( Controls::Base* control ) = 0;
				virtual void DrawStatusBar( Controls::Base* control ) = 0;

				virtual void DrawShadow( Controls::Base* control ) = 0;
				virtual void DrawScrollBarBar( Controls::Base* control, bool bDepressed, bool isHovered, bool isHorizontal ) = 0;
				virtual void DrawScrollBar( Controls::Base* control, bool isHorizontal, bool bDepressed ) = 0;
				virtual void DrawScrollButton( Controls::Base* control, int iDirection, bool bDepressed, bool bHovered, bool bDisabled ) = 0;
				virtual void DrawProgressBar( Controls::Base* control, bool isHorizontal, float progress ) = 0;

				virtual void DrawListBox( Controls::Base* control ) = 0;
				virtual void DrawListBoxLine( Controls::Base* control, bool bSelected, bool bEven ) = 0;

				virtual void DrawSlider( Controls::Base* control, bool bIsHorizontal, int numNotches, int barSize ) = 0;
				virtual void DrawSlideButton( Controls::Base* control, bool bDepressed, bool bHorizontal ) = 0;

				virtual void DrawComboBox( Controls::Base* control, bool bIsDown, bool bIsMenuOpen ) = 0;
				virtual void DrawComboDownArrow( Controls::Base* control, bool bHovered, bool bDown, bool bOpen, bool bDisabled ) = 0;
				virtual void DrawKeyboardHighlight( Controls::Base* control, const FK2DEngine2::Rect & rect, int offset ) = 0;
				virtual void DrawToolTip( Controls::Base* control ) = 0;

				virtual void DrawNumericUpDownButton( Controls::Base* control, bool bDepressed, bool bUp ) = 0;

				virtual void DrawTreeButton( Controls::Base* control, bool bOpen ) = 0;
				virtual void DrawTreeControl( Controls::Base* control ) = 0;
				virtual void DrawTreeNode( Controls::Base* ctrl, bool bOpen, bool bSelected, int iLabelHeight, int iLabelWidth, int iHalfWay, int iLastBranch, bool bIsRoot );

				virtual void DrawPropertyRow( Controls::Base* control, int iWidth, bool bBeingEdited, bool bHovered );
				virtual void DrawPropertyTreeNode( Controls::Base* control, int BorderLeft, int BorderTop );
				virtual void DrawColorDisplay( Controls::Base* control, FK2DEngine2::Color color ) = 0;
				virtual void DrawModalControl( Controls::Base* control ) = 0;
				virtual void DrawMenuDivider( Controls::Base* control ) = 0;

				virtual void DrawCategoryHolder( Controls::Base* ctrl ) = 0;
				virtual void DrawCategoryInner( Controls::Base* ctrl, bool bCollapsed ) = 0;

				virtual void SetRender( FK2DEngine2::video::Base* renderer )
				{
					m_Render = renderer;
				}
				virtual FK2DEngine2::video::Base* GetRender()
				{
					return m_Render;
				}

				virtual void DrawArrowDown( FK2DEngine2::Rect rect );
				virtual void DrawArrowUp( FK2DEngine2::Rect rect );
				virtual void DrawArrowLeft( FK2DEngine2::Rect rect );
				virtual void DrawArrowRight( FK2DEngine2::Rect rect );
				virtual void DrawCheck( FK2DEngine2::Rect rect );


				struct
				{
					struct Window_t
					{
						FK2DEngine2::Color TitleActive;
						FK2DEngine2::Color TitleInactive;

					} Window;

					struct Label_t
					{
						FK2DEngine2::Color Default;
						FK2DEngine2::Color Bright;
						FK2DEngine2::Color Dark;
						FK2DEngine2::Color Highlight;

					} Label;

					struct Tree_t
					{
						FK2DEngine2::Color Lines;
						FK2DEngine2::Color Normal;
						FK2DEngine2::Color Hover;
						FK2DEngine2::Color Selected;

					} Tree;

					struct Properties_t
					{
						FK2DEngine2::Color Line_Normal;
						FK2DEngine2::Color Line_Selected;
						FK2DEngine2::Color Line_Hover;
						FK2DEngine2::Color Column_Normal;
						FK2DEngine2::Color Column_Selected;
						FK2DEngine2::Color Column_Hover;
						FK2DEngine2::Color Label_Normal;
						FK2DEngine2::Color Label_Selected;
						FK2DEngine2::Color Label_Hover;
						FK2DEngine2::Color Border;
						FK2DEngine2::Color Title;

					} Properties;

					struct Button_t
					{
						FK2DEngine2::Color Normal;
						FK2DEngine2::Color Hover;
						FK2DEngine2::Color Down;
						FK2DEngine2::Color Disabled;

					} Button;

					struct Tab_t
					{
						struct Active_t
						{
							FK2DEngine2::Color Normal;
							FK2DEngine2::Color Hover;
							FK2DEngine2::Color Down;
							FK2DEngine2::Color Disabled;
						} Active;

						struct Inactive_t
						{
							FK2DEngine2::Color Normal;
							FK2DEngine2::Color Hover;
							FK2DEngine2::Color Down;
							FK2DEngine2::Color Disabled;
						} Inactive;

					} Tab;

					struct Category_t
					{
						FK2DEngine2::Color Header;
						FK2DEngine2::Color Header_Closed;

						struct Line_t
						{
							FK2DEngine2::Color Text;
							FK2DEngine2::Color Text_Hover;
							FK2DEngine2::Color Text_Selected;
							FK2DEngine2::Color Button;
							FK2DEngine2::Color Button_Hover;
							FK2DEngine2::Color Button_Selected;
						} Line;

						struct LineAlt_t
						{
							FK2DEngine2::Color Text;
							FK2DEngine2::Color Text_Hover;
							FK2DEngine2::Color Text_Selected;
							FK2DEngine2::Color Button;
							FK2DEngine2::Color Button_Hover;
							FK2DEngine2::Color Button_Selected;
						} LineAlt;

					} Category;

					FK2DEngine2::Color ModalBackground;
					FK2DEngine2::Color TooltipText;

				} Colors;


			public:

				virtual FK2DEngine2::Font* GetDefaultFont()
				{
					return &m_DefaultFont;
				}

				virtual void SetDefaultFont( const FK2DEngine2::UnicodeString & strFacename, float fSize = 10.0f )
				{
					m_DefaultFont.facename = strFacename;
					m_DefaultFont.size = fSize;
				}

			protected:

				FK2DEngine2::Font m_DefaultFont;
				FK2DEngine2::video::Base* m_Render;

		};
	};
}
//------------------------------------------------------------------------