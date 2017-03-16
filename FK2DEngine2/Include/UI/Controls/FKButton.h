/**
*	created:		2013-4-11   20:16
*	filename: 		FKButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class ImagePanel;

		class FK_EXPORT Button : public Label
		{
			public:

				FK_CONTROL( Button, Label );

				virtual void Render( Skin::Base* skin );
				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				virtual void OnMouseClickRight( int x, int y, bool bDown );
				virtual void OnMouseDoubleClickLeft( int x, int y );
				virtual bool OnKeySpace( bool bDown );

				virtual void OnPress();
				virtual void OnRightPress();

				virtual void AcceleratePressed();

				virtual bool IsDepressed() const { return m_bDepressed; }
				virtual void SetDepressed( bool b );

				virtual void SetIsToggle( bool b ) { m_bToggle = b; }
				virtual bool IsToggle() const { return m_bToggle; }
				virtual bool GetToggleState() const { return m_bToggleStatus; }
				virtual void SetToggleState( bool b );
				virtual void Toggle() { SetToggleState( !GetToggleState() ); }

				virtual void SetImage( const UITexObjSimpleInfo & strName, bool bCenter = false );

				virtual void SizeToContents();
				virtual void PostLayout( Skin::Base* pSkin );
				virtual void UpdateColours();

				virtual void SetImageAlpha( float fMultiply );

				virtual void DoAction() { OnPress(); }
				virtual void SetAction( Event::Handler* pObject, Handler::FunctionWithInformation pFunction, const FK2DEngine2::Event::Packet & packet );

			public:

				FK2DEngine2::Event::Caller	onPress;
				FK2DEngine2::Event::Caller	onRightPress;
				FK2DEngine2::Event::Caller	onDown;
				FK2DEngine2::Event::Caller	onUp;
				FK2DEngine2::Event::Caller	onDoubleClick;
				FK2DEngine2::Event::Caller	onToggle;
				FK2DEngine2::Event::Caller	onToggleOn;
				FK2DEngine2::Event::Caller	onToggleOff;

			protected:

				ImagePanel*		m_Image;

				bool	m_bDepressed;
				bool	m_bToggle;
				bool	m_bToggleStatus;

				bool	m_bCenterImage;
		};
	}
}
//------------------------------------------------------------------------