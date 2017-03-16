/**
*	created:		2013-4-11   20:13
*	filename: 		FKText
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "FKBase.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace ControlsInternal
	{
		class FK_EXPORT Text : public Controls::Base
		{
			public:

				FK_CONTROL( Text, Controls::Base );

				virtual ~Text();
				FK2DEngine2::Font* GetFont();

				void SetString( const UITexObjSimpleInfo & str );

				void Render( Skin::Base* skin );
				void Layout( Skin::Base* skin );

				void RefreshSize();

				void SetFont( FK2DEngine2::Font* pFont );

				const UITexObjSimpleInfo & GetText() const { return m_String; }

				FK2DEngine2::Rect GetCharacterPosition( int iChar );
				int GetClosestCharacter( FK2DEngine2::Point p );

				int Length() const { return ( int ) m_String.GetUnicode().size(); }

				virtual void SetTextColor( const FK2DEngine2::Color & col ) { m_Color = col; }
				virtual void SetTextColorOverride( const FK2DEngine2::Color & col ) { m_ColorOverride = col; }

				virtual void OnScaleChanged();

				inline const FK2DEngine2::Color & TextColor() const { return m_Color; }

				virtual void TextChanged() { m_bTextChanged = true; }
				virtual bool Wrap() { return m_bWrap; }
				virtual void SetWrap( bool b ) { if ( m_bWrap == b ) { return; } m_bWrap = b; m_bTextChanged = true; Invalidate(); }

				virtual Text* GetLine( int i );
				virtual int GetLineFromChar( int i );
				virtual int GetStartCharFromLine( int i );
				virtual int GetEndCharFromLine( int i );
				virtual int GetCharPosOnLine( int i );
				virtual int NumLines();

				virtual void SetPassword( bool b ){ m_bPassword = b; }

			private:

				virtual void RefreshSizeWrap();

				FK2DEngine2::UITexObjSimpleInfo		m_String;
				FK2DEngine2::Font*			m_Font;
				FK2DEngine2::Color			m_Color;
				FK2DEngine2::Color			m_ColorOverride;

				bool				m_bWrap;
				bool				m_bTextChanged;
				bool				m_bPassword;

				typedef std::list<Text*> TextLines;
				TextLines		m_Lines;
		};
	}
}
//------------------------------------------------------------------------