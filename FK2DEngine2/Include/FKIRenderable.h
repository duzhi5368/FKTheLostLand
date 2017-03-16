/**
*	created:		2013-4-28   20:25
*	filename: 		FKIRenderable
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <vector>
#include <map>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		class IRenderable
		{
		public:
			IRenderable() : m_nLayer( 0 ), m_bDeleteMe(false) {};
			virtual ~IRenderable(){};
		public:
			virtual void	Update( float dt ) = 0;
			virtual void	Render() = 0;
			bool			IsDestroyed() {return m_bDeleteMe;}
			int				GetLayer() {return m_nLayer;}
			virtual void	Destroy()
			{
				if( IsDestroyed() )
					return;
				PreDestroy(); 
				m_bDeleteMe = true;
			}
		protected:
			virtual void	PreDestroy() {}
		public:
			int			m_nLayer;		// 所在层级
			bool		m_bDeleteMe;	// 是否删除自己
		};

		typedef std::vector<FK2DEngine2::scene::IRenderable*>	RenderList;
		typedef std::map<int, RenderList>						RenderLayers;
	}
}
//------------------------------------------------------------------------