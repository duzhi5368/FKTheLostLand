/**
*	created:		2013-4-11   19:55
*	filename: 		FKBaseProperty
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../../FKUIOutSideHead.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class FK_EXPORT Base : public FK2DEngine2::Controls::Base
			{
				public:

					FK_CONTROL_INLINE( Base, FK2DEngine2::Controls::Base )
					{
						SetHeight( 17 );
					}

					virtual UITexObjSimpleInfo GetPropertyValue() = 0;

					virtual void SetPropertyValue( const UITexObjSimpleInfo & v, bool bFireChangeEvents = false ) = 0;

					virtual bool IsEditing() = 0;

					virtual void DoChanged()
					{
						Event::Information info;
						info.String = GetPropertyValue();
						onChange.Call( this, info );
					}

					void OnPropertyValueChanged( FK2DEngine2::Controls::Base* /*control*/ )
					{
						DoChanged();
					}

					Event::Caller	onChange;
			};
		}
	}
}
//------------------------------------------------------------------------