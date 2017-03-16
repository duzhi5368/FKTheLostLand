/**
*	created:		2013-5-1   21:36
*	filename: 		FKIScene
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKIScene.h"
#include "../Include/FK2DSceneManager.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		IScene::IScene()
		{

		}
		IScene::~IScene()
		{
			std::set<std::wstring> subs = theSwitchboard.GetSubscriptionsFor(this);
			std::set<std::wstring>::iterator it = subs.begin();
			while (it != subs.end())
			{
				theSwitchboard.UnsubscribeFrom(this, *it);
				++it;
			}
		}
		void IScene::OnLeave()
		{
			std::vector<IRenderable*>::iterator it = _objects.begin();
			while(_objects.end() != it)
			{
				theWorld.Remove(*it);
				delete *it;
				it++;
			}
			_objects.clear();
		}
	}
}