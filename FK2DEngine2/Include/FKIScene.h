/**
*	created:		2013-5-1   21:31
*	filename: 		FKIScene
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIRenderable.h"
#include "FKMessage.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		class IScene : public IRenderable, public FK2DEngine2::event::CMessageListener
		{
		public:
			IScene();
			virtual ~IScene();
		public:
			virtual void	OnEnter(){};
			virtual void	OnLeave();
			virtual void	Update( float dt ){};
			virtual void	Render(){};
			virtual void	ReceiveMessage(FK2DEngine2::event::CMessage *message) {}
		protected:
			std::vector<IRenderable*> _objects;
		};
	}
}