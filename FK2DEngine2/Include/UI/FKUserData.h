/**
*	created:		2013-4-11   17:32
*	filename: 		FKUserData
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	class UserDataStorage
	{
			struct ValueBase
			{
				virtual ~ValueBase() {}
				virtual void DeleteThis() = 0;
			};

			template<typename T> struct Value : public ValueBase
			{
				T val;

				Value( const T & v )
				{
					val = v;
				}

				virtual void DeleteThis()
				{
					delete this;
				}
			};

		public:

			UserDataStorage()
			{
			}

			~UserDataStorage()
			{
				std::map< FK2DEngine2::String, void*>::iterator it = m_List.begin();
				std::map< FK2DEngine2::String, void*>::iterator itEnd = m_List.end();

				while ( it != itEnd )
				{
					( ( ValueBase* ) it->second )->DeleteThis();
					++it;
				}
			}

			template<typename T>
			void Set( const FK2DEngine2::String & str, const T & var )
			{
				Value<T>* val = NULL;
				std::map< FK2DEngine2::String, void*>::iterator it = m_List.find( str );

				if ( it != m_List.end() )
				{
					( ( Value<T>* ) it->second )->val = var;
				}
				else
				{
					val = new Value<T> ( var );
					m_List[ str ] = ( void* ) val;
				}
			};

			bool Exists( const FK2DEngine2::String & str )
			{
				return m_List.find( str ) != m_List.end();
			};

			template <typename T>
			T & Get( const FK2DEngine2::String & str )
			{
				Value<T>* v = ( Value<T>* ) m_List[ str ];
				return v->val;
			}

			std::map< FK2DEngine2::String, void*>	m_List;
	};
};
//------------------------------------------------------------------------