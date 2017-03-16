/**
*	created:		2013-4-11   17:30
*	filename: 		FKControlList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	struct Point;
	class UITexObjSimpleInfo;

	namespace Controls
	{
		class Base;
	}

	namespace Event
	{
		class Handler;
		struct Information;
		struct Packet;

		typedef const FK2DEngine2::Event::Information & Info;
	}

	template < typename TYPE >
	class TEasyList
	{
	public:

		typedef std::list<TYPE> List;

		void Add( TYPE pControl )
		{
			if ( Contains( pControl ) ) { return; }

			list.push_back( pControl );
		}

		void Remove( TYPE pControl )
		{
			list.remove( pControl );
		}

		void Add( const List & list )
		{
			for ( typename List::const_iterator it = list.begin(); it != list.end(); ++it )
			{
				Add( *it );
			}
		}

		void Add( const TEasyList<TYPE> & list )
		{
			Add( list.list );
		}

		bool Contains( TYPE pControl ) const
		{
			typename List::const_iterator it = std::find( list.begin(), list.end(), pControl );
			return it != list.end();
		}

		inline void Clear()
		{
			list.clear();
		}

		List list;
	};

	class ControlList : public TEasyList<FK2DEngine2::Controls::Base*>
	{
	public:

		void Enable();
		void Disable();

		void Show();
		void Hide();

		FK2DEngine2::UITexObjSimpleInfo GetValue();
		void SetValue( const FK2DEngine2::UITexObjSimpleInfo & value );

		template <typename T>
		void SetAction( FK2DEngine2::Event::Handler* ob,
			void ( T::*f )( FK2DEngine2::Event::Info ),
			const FK2DEngine2::Event::Packet & packet )
		{
			SetActionInternal( ob,
				static_cast<void ( FK2DEngine2::Event::Handler::* )( FK2DEngine2::Event::Info ) > ( f ),
				packet );
		}

		void MoveBy( const FK2DEngine2::Point & point );

		void DoAction();

	protected:

		void SetActionInternal( FK2DEngine2::Event::Handler* pObject,
			void ( FK2DEngine2::Event::Handler::*f )( FK2DEngine2::Event::Info ),
			const FK2DEngine2::Event::Packet & packet );
	};

};
//------------------------------------------------------------------------