/**
*	created:		2013-4-11   22:32
*	filename: 		FKControlFactory
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
	namespace ControlFactory
	{
		//------------------------------------------------------------------------
		class Base;
		typedef std::list< ControlFactory::Base* > List;

		List & GetList();
		ControlFactory::Base* Find( const FK2DEngine2::String & name );
		Controls::Base* Clone( Controls::Base* pEnt, ControlFactory::Base* pFactory );
		//------------------------------------------------------------------------
		class Property
		{
		public:

			typedef std::list<Property*> List;

			virtual FK2DEngine2::String				Name() = 0;
			virtual FK2DEngine2::String				Description() = 0;

			virtual FK2DEngine2::UnicodeString		GetValue( FK2DEngine2::Controls::Base* ctrl ) = 0;
			virtual void							SetValue( FK2DEngine2::Controls::Base* ctrl, const FK2DEngine2::UnicodeString & str ) = 0;

			virtual int								OptionNum() { return 0; }
			virtual FK2DEngine2::UnicodeString		OptionGet( int i ) { return L"";}

			virtual int								NumCount() { return 0; };
			virtual FK2DEngine2::String				NumName( int i ) { return "unknown"; };
			virtual float							NumGet( FK2DEngine2::Controls::Base* ctrl, int i ) { return 0.0f; };
			virtual void							NumSet( FK2DEngine2::Controls::Base* ctrl, int i, float f ) {};

			inline void NumSet( FK2DEngine2::Controls::Base* ctrl, const FK2DEngine2::String & str, float f )
			{
				for ( int i = 0; i < NumCount(); i++ )
				{
					if ( NumName( i ) == str ) { NumSet( ctrl, i, f ); }
				}
			};
		};
		//------------------------------------------------------------------------
		class PropertyBool : public Property
		{
		public:

			static const FK2DEngine2::UnicodeString		True;
			static const FK2DEngine2::UnicodeString		False;

			virtual int								OptionNum() { return 2; }
			virtual FK2DEngine2::UnicodeString		OptionGet( int i ) { if ( i == 0 ) { return False; } return True; }
		};
		//------------------------------------------------------------------------
		class Base
		{
		public:

			Base();

			virtual FK2DEngine2::String Name() = 0;
			virtual FK2DEngine2::String BaseName() = 0;

			virtual FK2DEngine2::Controls::Base* CreateInstance( FK2DEngine2::Controls::Base* parent ) = 0;

			Base* GetBaseFactory();
			void AddProperty( Property* pProp );

			Property* GetProperty( const FK2DEngine2::String & name );
			void SetControlValue( FK2DEngine2::Controls::Base* ctrl, const FK2DEngine2::String & name, const FK2DEngine2::UnicodeString & str );

			const Property::List & Properties() { return m_Properties; }

			virtual void AddChild( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* child,
				const FK2DEngine2::Point & pos );

			virtual void AddChild( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* child,
				int iPage = 0 );

			virtual bool ChildTouched( FK2DEngine2::Controls::Base* ctrl, FK2DEngine2::Controls::Base* pChildControl ) { return false; };

			virtual void SetParentPage( FK2DEngine2::Controls::Base* ctrl, int i );
			virtual int GetParentPage( FK2DEngine2::Controls::Base* ctrl );

		protected:

			Property::List	m_Properties;
		};
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------
#define FK_CONTROL_FACTORY_CONSTRUCTOR( ThisName, BaseName )\
	typedef BaseName BaseClass;\
	typedef ThisName ThisClass;\
	ThisName() : BaseClass()
//------------------------------------------------------------------------
#define FK_CONTROL_FACTORY( ThisName ) \
	void FKCONTROLFACTORY##ThisName()\
{\
	new ThisName();\
}
//------------------------------------------------------------------------
#define DECLARE_FK_CONTROL_FACTORY( ThisName )\
	extern void FKCONTROLFACTORY##ThisName();\
	FKCONTROLFACTORY##ThisName();
//------------------------------------------------------------------------
#define FK_CONTROL_FACTORY_PROPERTY( _name_, _description_ )\
	public:\
	FK2DEngine2::String Name() { return #_name_; }\
	FK2DEngine2::String Description() { return _description_; }
//------------------------------------------------------------------------