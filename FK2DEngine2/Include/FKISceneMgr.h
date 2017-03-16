/**
*	created:		2013-4-30   16:02
*	filename: 		FKISceneMgr
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKSwitchboard.h"
#include "FKIRenderable.h"
#include "FKIScene.h"
#include <map>
//------------------------------------------------------------------------
// 外界继承接口
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S2D
		{
			class FKISceneManager : public FK2DEngine2::scene::IRenderable, public FK2DEngine2::event::CMessageListener
			{
			public:
				FKISceneManager():m_nCurIndex(-1){}
				virtual ~FKISceneManager();
				virtual int Add( FK2DEngine2::scene::IScene* scene, int nIndex = -1 );
				virtual void RleaseAllScene();
				virtual FK2DEngine2::scene::IScene* GetSceneByIndex( int nIndex );
				virtual void SetCurScene( int nIndex );
				virtual void Render(){}
				virtual void Update(float dt){}
				virtual bool IsProtectedFromUnloadAll( FK2DEngine2::scene::IRenderable* renderable ) {return false;} 
				virtual void ReceiveMessage(FK2DEngine2::event::CMessage* message) {}
			private:
				std::map< int,FK2DEngine2::scene::IScene* >	m_vecSceneList;
				int											m_nCurIndex;
			};
		}
	}
}
//------------------------------------------------------------------------