/**
*	created:		2013-4-12   15:44
*	filename: 		FKColorSelector
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKProperties.h"
#include "../FKMenu.h"
#include "../FKHSVColorPicker.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Internal
		{
			class ColourButton : public Button
			{
				FK_CONTROL_INLINE( ColourButton, Button )
				{
					m_Color = Colors::Black;
					SetText( "" );
				}

				void Render( Skin::Base* skin )
				{
					skin->GetRender()->SetDrawColor( m_Color );
					skin->GetRender()->DrawFilledRect( GetRenderBounds() );
				}

				void SetColor( const FK2DEngine2::Color & col ) { m_Color = col; }

				FK2DEngine2::Color	m_Color;
			};
		}

		namespace Property
		{
			class ColorSelector : public Property::Text
			{
				FK_CONTROL_INLINE( ColorSelector, Property::Text )
				{
					m_Button = new Controls::Internal::ColourButton( m_TextBox );
					m_Button->Dock( Pos::Right );
					m_Button->SetWidth( 20 );
					m_Button->onPress.Add( this, &ThisClass::OnButtonPress );
					m_Button->SetMargin( Margin( 1, 1, 1, 2 ) );
				}

				void OnButtonPress( Controls::Base* control )
				{
					FK2DEngine2::Controls::Menu* pMenu = new Menu( ( FK2DEngine2::Controls::Base* )(GetCanvas()) );
					pMenu->SetSize( 256, 180 );
					pMenu->SetDeleteOnClose( true );
					pMenu->SetDisableIconMargin( true );
					FK2DEngine2::Controls::HSVColorPicker* picker = new FK2DEngine2::Controls::HSVColorPicker( pMenu );
					picker->Dock( Pos::Fill );
					picker->SetSize( 256, 128 );
					float defaultColor[3];
					FK2DEngine2::Utility::Strings::To::Floats( m_TextBox->GetText().Get(), defaultColor, 3 );
					picker->SetColor( FK2DEngine2::Color( defaultColor[0], defaultColor[1], defaultColor[2], 255 ), false, true );
					picker->onColorChanged.Add( this, &ThisClass::ColorChanged );
					pMenu->Open( Pos::Right | Pos::Top );
				}

				void ColorChanged( Controls::Base* control )
				{
					FK2DEngine2::Controls::HSVColorPicker* picker = fk_cast<FK2DEngine2::Controls::HSVColorPicker> ( control );
					FK2DEngine2::String colorStr;
					colorStr += FK2DEngine2::Utility::ToString( ( int ) picker->GetColor().r ) + " ";
					colorStr += FK2DEngine2::Utility::ToString( ( int ) picker->GetColor().g ) + " ";
					colorStr += FK2DEngine2::Utility::ToString( ( int ) picker->GetColor().b );
					m_TextBox->SetText( colorStr );
					DoChanged();
				}

				virtual UITexObjSimpleInfo GetPropertyValue()
				{
					return m_TextBox->GetText();
				}

				virtual void SetPropertyValue( const UITexObjSimpleInfo & v, bool bFireChangeEvents )
				{
					m_TextBox->SetText( v, bFireChangeEvents );
				}

				virtual bool IsEditing()
				{
					return m_TextBox == FK2DEngine2::KeyboardFocus;
				}

				virtual void DoChanged()
				{
					BaseClass::DoChanged();
					float col[3];
					FK2DEngine2::Utility::Strings::To::Floats( m_TextBox->GetText().Get(), col, 3 );
					m_Button->SetColor( FK2DEngine2::Color( col[0], col[1], col[2] ) );
				}

				Controls::Internal::ColourButton*		m_Button;
			};
		}
	}
}
//------------------------------------------------------------------------