/**
*	created:		2013-4-12   1:09
*	filename: 		FKProperties
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "FKLabel.h"
#include "Property/FKBaseProperty.h"
#include "Property/FKText.h"
#include "FKSplitterBar.h"
#include "../FKSkin.h"
#include "../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{

		class PropertyRow;

		class FK_EXPORT Properties : public Base
		{
			public:

				FK_CONTROL( Properties, Base );

				virtual void PostLayout( FK2DEngine2::Skin::Base* skin );

				PropertyRow* Add( const UITexObjSimpleInfo & text, const UITexObjSimpleInfo & value = L"" );
				PropertyRow* Add( const UITexObjSimpleInfo & text, Property::Base* pProp, const UITexObjSimpleInfo & value = L"" );
				PropertyRow* Find( const UITexObjSimpleInfo & text );

				virtual int GetSplitWidth();

				virtual void Clear();

			protected:

				virtual void OnSplitterMoved( Controls::Base* control );

				Controls::SplitterBar*	m_SplitterBar;

		};
		//------------------------------------------------------------------------
		class FK_EXPORT PropertyRow : public Base
		{
			public:

				FK_CONTROL( PropertyRow, Base );

				virtual Label* GetLabel() { return m_Label; }
				virtual void SetProperty( Property::Base* prop );
				virtual Property::Base* GetProperty() { return m_Property; }

				virtual void Layout( FK2DEngine2::Skin::Base* skin );
				virtual void Render( FK2DEngine2::Skin::Base* skin );

				virtual bool IsEditing() { return m_Property && m_Property->IsEditing(); }
				virtual bool IsHovered() { return BaseClass::IsHovered() || ( m_Property && m_Property->IsHovered() ); }
				virtual void OnEditingChanged();
				virtual void OnHoverChanged();

				Event::Caller	onChange;

			protected:

				void OnPropertyValueChanged( FK2DEngine2::Controls::Base* control );

				Label*			m_Label;
				Property::Base*	m_Property;

				bool			m_bLastEditing;
				bool			m_bLastHover;

		};
	}
}
//------------------------------------------------------------------------