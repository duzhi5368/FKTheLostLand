/**
*	created:		2013-5-1   21:51
*	filename: 		FKISceneMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKISceneMgr.h"
#include "../Include/FK2DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S2D
		{
			FKISceneManager::~FKISceneManager()
			{
				std::set<std::wstring> subs = theSwitchboard.GetSubscriptionsFor(this);
				std::set<std::wstring>::iterator it = subs.begin();
				while (it != subs.end())
				{
					theSwitchboard.UnsubscribeFrom(this, *it);
					++it;
				}
			}
			int  FKISceneManager::Add( FK2DEngine2::scene::IScene* scene, int nIndex )
			{
				if( scene == NULL )
				{
					return -1;
				}
				std::map< int,FK2DEngine2::scene::IScene* >::iterator Ite = m_vecSceneList.find(nIndex);
				if( Ite != m_vecSceneList.end() )
				{
					return Ite->first;
				}
				int nReallyIndex = nIndex;
				if( nIndex == -1 )
				{
					if( m_vecSceneList.size() == 0 )
					{
						nReallyIndex = 1;
					}
					else
					{
						Ite = m_vecSceneList.end();
						nReallyIndex = Ite->first + 1;
					}
				}
				Ite = m_vecSceneList.find( nReallyIndex );
				if( Ite != m_vecSceneList.end() )
				{
					// Error accour
					return Ite->first;
				}
				m_vecSceneList.insert( std::make_pair( nReallyIndex, scene ) );
				return nReallyIndex;
			}

			void  FKISceneManager::RleaseAllScene()
			{

			}

			FK2DEngine2::scene::IScene*  FKISceneManager::GetSceneByIndex( int nIndex )
			{
				std::map< int,FK2DEngine2::scene::IScene* >::iterator Ite = m_vecSceneList.find(nIndex);
				if( Ite != m_vecSceneList.end() )
				{
					return Ite->second;
				}
				return NULL;
			}

			void  FKISceneManager::SetCurScene( int nIndex )
			{
				std::map< int,FK2DEngine2::scene::IScene* >::iterator Ite;
				if( nIndex != -1 )
				{
					Ite = m_vecSceneList.find( m_nCurIndex );
					if( Ite != m_vecSceneList.end() )
					{
						Ite->second->OnLeave();
						theWorld.Remove( Ite->second );
					}
				}

				m_nCurIndex = -1;

				Ite = m_vecSceneList.find(nIndex);
				if( Ite != m_vecSceneList.end() )
				{
					Ite->second->OnEnter();
					theWorld.Add( Ite->second );
					m_nCurIndex = Ite->first;
				}	
			}
		}
	}
}