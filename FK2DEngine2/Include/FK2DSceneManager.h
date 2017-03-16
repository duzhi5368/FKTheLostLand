/**
*	created:		2013-4-23   22:07
*	filename: 		FK2DSceneManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKI2DSceneManager.h"
#include "FKActor.h"
#include "FKRenderableIterator.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S2D
		{
			class FKISceneManager;

			#define theWorld		FK2DEngine2::scene::S2D::C2DSceneManager::GetInstance()
			#define theWorldPtr		FK2DEngine2::scene::S2D::C2DSceneManager::GetInstancePtr()

			typedef enum
			{
				E_2DRENDER_LIST_TRIANGLE,
				E_2DRENDER_LIST_QUAD,
				E_2DRENDER_LIST_OTHER
			}E_2DRENDER_LIST_TYPE;

			struct RenderableLayerPair
			{
				FK2DEngine2::scene::IRenderable*	_renderable;
				int									_layer;
			};

			class C2DSceneManager : public I2DSceneManager
			{
			public :
				virtual const std::wstring getTypeInfo() const {
					return L"C2DSceneManager";
				}
			public:
				static C2DSceneManager&	GetInstance();
				static C2DSceneManager* GetInstancePtr();
			public:
				C2DSceneManager();
				virtual ~C2DSceneManager();
				
				virtual bool 	init2DSceneManager(FK2DEngine2::video::IVideoDriver * videoDriver_,int bufferLength,
					float width,float height,float zdepth);
				virtual bool 	shut2DSceneManager();

				virtual bool 	begin2DScene();
				virtual void 	renderUI( FK2DEngine2::Controls::Canvas * uiCanvas );
				virtual void	drawAll( FK2DEngine2::Controls::Canvas * uiCanvas );
				virtual bool 	end2DScene();

				virtual void 	RenderPixel(S2DPixel pixel,float x,float y,float z);
				virtual void 	RenderLine(S2DLine line,float x,float y,float z);
				virtual void 	RenderTriangle(S2DTriangle triangle,float x,float y,float z);
				virtual void 	RenderQuad(S2DQuad quad,float x,float y,float z);
				virtual void	RenderActor(FK2DEngine2::actor::CActor* actor);
				virtual void 	RenderQuadEx(S2DQuad quad,float x,float y,float z,float angle,float scalex,float scaley);

				void			LoadLevel( std::wstring levelName );
				const float		GetDT();

				void			Simulate(bool simRunning);
				const bool		StartSimulation();
				const bool		StopSimulation();

				void 			Add(FK2DEngine2::scene::IRenderable *newElement, int layer = 0);
				void 			Add(FK2DEngine2::scene::IRenderable *newElement, std::wstring layer);
				void 			Remove(FK2DEngine2::scene::IRenderable *oldElement);
				void 			UpdateLayer(FK2DEngine2::scene::IRenderable* element, int newLayer);
				void			UpdateLayer(FK2DEngine2::scene::IRenderable* element, std::wstring newLayerName);
				void			NameLayer(std::wstring name, int number);
				const int		GetLayerByName(std::wstring name);
				RenderLayers&	GetLayers() { return _layers; }
				float			GetCurrentTimeSeconds() { return ( float(_currTime) ); }
				float			GetTimeSinceSeconds( float lastTime ) {return GetCurrentTimeSeconds() - lastTime;}

				void					SetSceneMgr(FKISceneManager* scene);
				FKISceneManager*		GetSceneMgr(){ return _gameManager; }

				CFKRenderableIterator GetFirstRenderable()
				{
					CFKRenderableIterator iter;
					return iter.begin(); 
				}
				CFKRenderableIterator GetLastRenderable()
				{
					CFKRenderableIterator iter;
					return iter.end();
				}

				void			UnloadAll();
				virtual void	ReceiveMessage(FK2DEngine2::event::CMessage *m);
			protected:
				void			renderBuffer();
				float			CalculateNewDT();
				void			UpdateRenderables(float frame_dt);
				void			CleanupRenderables();
				void			DrawRenderables();
				void			TickAndRender();
				void 			ProcessDeferredAdds();
				void 			ProcessDeferredLayerChanges();
				void 			ProcessDeferredRemoves();
			private:
				FK2DEngine2::math::Vertex *			vertexBuffer;
				int									vertexBufferLength;
				int									vertexBufferPointer;
				unsigned short *					indexBuffer;
				int									indexBufferLength;
				E_2DRENDER_LIST_TYPE				nowType;
				FK2DEngine2::video::ITexture *		currentTexture;
				FK2DEngine2::video::IVideoDriver *	videoDriver;
				FK2DEngine2::math::Matrix4			projection2DMatrix;
				float 								_prevTime;
				float 								_currTime;
				float 								_dt;
				bool 								_simulateOn;
				bool 								_initialized;
				RenderLayers						_layers;
				std::vector<RenderableLayerPair>	_deferredAdds;	
				std::vector<RenderableLayerPair>	_deferredLayerChanges;
				std::vector<FK2DEngine2::scene::IRenderable*> _deferredRemoves;
				std::map<std::wstring, int>			_layerNames;
				bool								_elementsLocked;
				FKISceneManager *					_gameManager;
			private:
				static C2DSceneManager*				s_World;
			};
		}
	}
}
//------------------------------------------------------------------------