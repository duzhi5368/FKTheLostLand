/**
*	created:		2013-4-11   20:12
*	filename: 		FKLabel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
#include "FKText.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT Label : public Controls::Base
		{
			public:

				FK_CONTROL( Label, Controls::Base );
				virtual void PreDelete( FK2DEngine2::Skin::Base* skin );

				virtual void SetText( const UITexObjSimpleInfo & str, bool bDoEvents = true );

				virtual const UITexObjSimpleInfo & GetText() const { return m_Text->GetText(); }

				virtual void Render( Skin::Base* /*skin*/ ) {}

				virtual void PostLayout( Skin::Base* skin );

				virtual void SizeToContents();

				virtual void SetAlignment( int iAlign );
				virtual int GetAlignment();

				virtual void SetFont( FK2DEngine2::UnicodeString strFacename, int iSize, bool bBold );

				virtual void SetFont( FK2DEngine2::Font* pFont ) { m_Text->SetFont( pFont ); }
				virtual FK2DEngine2::Font* GetFont() { return m_Text->GetFont(); }
				virtual void SetTextColor( const FK2DEngine2::Color & col ) { m_Text->SetTextColor( col ); }
				virtual void SetTextColorOverride( const FK2DEngine2::Color & col ) { m_Text->SetTextColorOverride( col ); }
				inline const FK2DEngine2::Color & TextColor() const { return m_Text->TextColor(); }

				virtual int TextWidth() { return m_Text->Width(); }
				virtual int TextRight() { return m_Text->Right(); }
				virtual int TextHeight() { return m_Text->Height(); }
				virtual int TextX() { return m_Text->X(); }
				virtual int TextY() { return m_Text->Y(); }
				virtual int TextLength() { return m_Text->Length(); }

				FK2DEngine2::Rect GetCharacterPosition( int iChar );

				virtual void SetTextPadding( const Padding & padding ) { m_Text->SetPadding( padding ); Invalidate(); InvalidateParent(); }
				virtual const Padding & GetTextPadding() { return m_Text->GetPadding(); }

				inline int Alignment() const { return m_iAlign; }

				virtual void MakeColorNormal() { SetTextColor( GetSkin()->Colors.Label.Default ); }
				virtual void MakeColorBright() { SetTextColor( GetSkin()->Colors.Label.Bright ); }
				virtual void MakeColorDark() { SetTextColor( GetSkin()->Colors.Label.Dark ); }
				virtual void MakeColorHighlight() { SetTextColor( GetSkin()->Colors.Label.Highlight ); }

				virtual UITexObjSimpleInfo GetValue() { return GetText(); }
				virtual void SetValue( const UITexObjSimpleInfo & strValue ) { return SetText( strValue ); }

				virtual bool Wrap() { return m_Text->Wrap(); }
				virtual void SetWrap( bool b ) { m_Text->SetWrap( b ); }

				virtual void OnBoundsChanged( FK2DEngine2::Rect oldChildBounds );
				virtual void SetPassword( bool b ){ m_Text->SetPassword(b); }

			protected:

				virtual void OnTextChanged() {};

				FK2DEngine2::Font*					m_CreatedFont;
				ControlsInternal::Text*				m_Text;
				int m_iAlign;


		};
	}
}
//------------------------------------------------------------------------