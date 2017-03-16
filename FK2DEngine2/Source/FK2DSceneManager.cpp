/**
*	created:		2013-4-23   22:10
*	filename: 		FK2DSceneManager
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FK2DSceneManager.h"
#include "../Include/FKISceneMgr.h"
#include "../Include/FKActor.h"
//------------------------------------------------------------------------
#define MAX_TIMESTEP 1.0f
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S2D
		{
				C2DSceneManager* C2DSceneManager::s_World = NULL;

				C2DSceneManager& C2DSceneManager::GetInstance()
				{
					if (s_World == NULL)
					{
						s_World = new C2DSceneManager();
					}
					return *s_World;
				}
				C2DSceneManager* C2DSceneManager::GetInstancePtr()
				{
					if (s_World == NULL)
					{
						s_World = new C2DSceneManager();
					}
					return s_World;
				}

			    C2DSceneManager::C2DSceneManager()
				{
					_simulateOn = true;
					_initialized = false;
					_gameManager = NULL;
					_elementsLocked = false;
				}

				C2DSceneManager::~C2DSceneManager()
				{
					delete [] indexBuffer;
					unsigned char * tempBuffer = (unsigned char *)(vertexBuffer);
					delete [] tempBuffer;
				}
				
				bool C2DSceneManager::init2DSceneManager(FK2DEngine2::video::IVideoDriver * videoDriver_,int bufferLength_,
					float width,float height,float zdepth)
				{
					videoDriver = videoDriver_;
					vertexBufferLength = bufferLength_;
					unsigned char * tempBuffer = new unsigned char [vertexBufferLength * sizeof(FK2DEngine2::math::Vertex)];
					vertexBuffer = (FK2DEngine2::math::Vertex *)(tempBuffer);
					vertexBufferPointer = 0;
					indexBufferLength = vertexBufferLength * 6 / 4;
					indexBuffer = new unsigned short [indexBufferLength];
					currentTexture = NULL;

					projection2DMatrix.Make2DProjection((float)width,(float)height,(float)zdepth);
					nowType = E_2DRENDER_LIST_QUAD;
					unsigned short n = 0;
					for ( int i = 0; i < indexBufferLength ; i += 6)
					{
						indexBuffer[i] = n;
						indexBuffer[i + 1] = n + 1;
						indexBuffer[i + 2] = n + 2;
						indexBuffer[i + 3] = n + 1;
						indexBuffer[i + 4] = n + 3;
						indexBuffer[i + 5] = n + 2;
						n += 4;
					}
					return true;
				}

				bool C2DSceneManager::shut2DSceneManager()
				{
					return true;
				}

				bool C2DSceneManager::begin2DScene()
				{
					videoDriver->setVideodriverState(FK2DEngine2::video::E_VIDEODRIVER_STATE_LIGHTING,false);
					FK2DEngine2::math::Matrix4 m4;
					m4.MakeIdentity();
					videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_WORLD,m4);
					videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_VIEW,m4);
					videoDriver->setTransform(FK2DEngine2::video::E_TRANSFORM_MATRIX_PROJECTION,projection2DMatrix);
					currentTexture = NULL;
					return true;
				}

				void C2DSceneManager::renderUI( FK2DEngine2::Controls::Canvas * uiCanvas )
				{
					if( uiCanvas != NULL )
					{
						uiCanvas->RenderCanvas();
					}
				}

				void C2DSceneManager::drawAll( FK2DEngine2::Controls::Canvas * uiCanvas )
				{
					TickAndRender();
				}

				bool C2DSceneManager::end2DScene()
				{
					renderBuffer();
					return true;
				}

				void C2DSceneManager::RenderPixel(S2DPixel pixel,float x,float y,float z)
				{
					renderBuffer();
					nowType = E_2DRENDER_LIST_OTHER;
					currentTexture = pixel.texture;
					videoDriver->setTexture(pixel.texture);
					pixel.pixel.x += x; pixel.pixel.y += y; pixel.pixel.z += z;
					videoDriver->drawPixel(pixel.pixel);
				}

				void C2DSceneManager::RenderLine(S2DLine line,float x,float y,float z)
				{
					renderBuffer();
					nowType = E_2DRENDER_LIST_OTHER;
					currentTexture = line.texture;
					videoDriver->setTexture(line.texture);
					line.line.start.x  += x; line.line.start.y += y; line.line.start.z += z;
					line.line.end.x += x; line.line.end.y += y; line.line.end.z += z;
					videoDriver->drawLine(line.line);
				}

				void C2DSceneManager::RenderTriangle(S2DTriangle triangle,float x,float y,float z)
				{
					triangle.triangle.v0.x += x; triangle.triangle.v0.y += y; triangle.triangle.v0.z += z;
					triangle.triangle.v1.x += x; triangle.triangle.v1.y += y; triangle.triangle.v1.z += z;
					triangle.triangle.v2.x += x; triangle.triangle.v2.y += y; triangle.triangle.v2.z += z;
					if (nowType != E_2DRENDER_LIST_TRIANGLE || triangle.texture != currentTexture || vertexBufferPointer + 3 > vertexBufferLength)
					{
						renderBuffer();
						nowType = E_2DRENDER_LIST_TRIANGLE;
						currentTexture = triangle.texture;
						videoDriver->setTexture(triangle.texture);
					}
					memcpy(&vertexBuffer[vertexBufferPointer],&(triangle.triangle),sizeof(FK2DEngine2::math::Triangle));
					vertexBufferPointer += 3;
				}

				void C2DSceneManager::RenderQuad(S2DQuad quad,float x,float y,float z)
				{
					quad.quad.v0.x += x; quad.quad.v0.y += y; quad.quad.v0.z += z;
					quad.quad.v1.x += x; quad.quad.v1.y += y; quad.quad.v1.z += z;
					quad.quad.v2.x += x; quad.quad.v2.y += y; quad.quad.v2.z += z;
					quad.quad.v3.x += x; quad.quad.v3.y += y; quad.quad.v3.z += z;

					if (nowType != E_2DRENDER_LIST_QUAD || quad.texture != currentTexture || vertexBufferPointer  + 4 > vertexBufferLength)
					{
						renderBuffer();
						nowType = E_2DRENDER_LIST_QUAD;
						currentTexture = quad.texture;
						videoDriver->setTexture(quad.texture);
					}
					memcpy(&vertexBuffer[vertexBufferPointer],&(quad.quad),sizeof(FK2DEngine2::math::Quad));
					vertexBufferPointer += 4;
				}
				void C2DSceneManager::RenderActor(FK2DEngine2::actor::CActor* actor)
				{
					if( actor == NULL )
					{
						return;
					}

					S2DQuad actorQuad = actor->GetRenderQuad();
					actorQuad.quad.v0.x += actor->GetPosition().X; 
					actorQuad.quad.v0.y += actor->GetPosition().Y; 
					actorQuad.quad.v0.z += actor->GetLayer();
					actorQuad.quad.v1.x += actor->GetPosition().X; 
					actorQuad.quad.v1.y += actor->GetPosition().Y; 
					actorQuad.quad.v1.z += actor->GetLayer();
					actorQuad.quad.v2.x += actor->GetPosition().X; 
					actorQuad.quad.v2.y += actor->GetPosition().Y; 
					actorQuad.quad.v2.z += actor->GetLayer();
					actorQuad.quad.v3.x += actor->GetPosition().X; 
					actorQuad.quad.v3.y += actor->GetPosition().Y; 
					actorQuad.quad.v3.z += actor->GetLayer();

					if (nowType != E_2DRENDER_LIST_QUAD || actorQuad.texture != currentTexture || 
						vertexBufferPointer  + 4 > vertexBufferLength)
					{
						renderBuffer();
						nowType = E_2DRENDER_LIST_QUAD;
						currentTexture = actorQuad.texture;
						videoDriver->setTexture(actorQuad.texture);
					}
					memcpy(&vertexBuffer[vertexBufferPointer],&(actorQuad.quad),sizeof(FK2DEngine2::math::Quad));
					vertexBufferPointer += 4;
				}
				
				void C2DSceneManager::RenderQuadEx(S2DQuad quad,float x,float y,float z,float angle,float scalex,float scaley)
				{
					quad.quad.v0.x += x; quad.quad.v0.y += y; quad.quad.v0.z += z;
					quad.quad.v1.x += x; quad.quad.v1.y += y; quad.quad.v1.z += z;
					quad.quad.v2.x += x; quad.quad.v2.y += y; quad.quad.v2.z += z;
					quad.quad.v3.x += x; quad.quad.v3.y += y; quad.quad.v3.z += z;
					FK2DEngine2::math::Matrix4 m4;
					m4.MakeRotationXYPlane(angle);
					quad.quad.Transform(m4);
					m4.MakeScaling(scalex,scaley,1.0f);
					quad.quad.Transform(m4);
					if (nowType != E_2DRENDER_LIST_QUAD || quad.texture != currentTexture || vertexBufferPointer + 4 > vertexBufferLength)
					{
						renderBuffer();
						nowType = E_2DRENDER_LIST_QUAD;
						currentTexture = quad.texture;
						videoDriver->setTexture(quad.texture);
					}
					memcpy(&vertexBuffer [vertexBufferPointer],&(quad.quad),sizeof(FK2DEngine2::math::Quad));
					vertexBufferPointer += 4;
				}

				void C2DSceneManager::renderBuffer()
				{
					if (vertexBufferPointer != 0)
					{
						switch (nowType)
						{
						case E_2DRENDER_LIST_TRIANGLE:
							videoDriver->drawTriangleList((FK2DEngine2::math::Triangle *)(vertexBuffer),vertexBufferPointer / 3);
							break;
						case E_2DRENDER_LIST_QUAD:
							videoDriver->drawIndexTriangleList((FK2DEngine2::math::Vertex *)(vertexBuffer),vertexBufferPointer
								,indexBuffer,vertexBufferPointer / 4 * 2);
							break;
						}
						vertexBufferPointer = 0;
					}
				}

				void C2DSceneManager::LoadLevel( std::wstring levelName )
				{
					// todo:
				}

				const float	C2DSceneManager::GetDT()
				{
					return _dt;
				}

				void C2DSceneManager::Simulate(bool simRunning)
				{
					float frame_dt = CalculateNewDT();
					if (_gameManager)
					{
						_gameManager->Update(frame_dt);
					}
					if (simRunning)
					{
						theSwitchboard.SendAllMessages();

						_elementsLocked = true;
						UpdateRenderables(frame_dt);
						CleanupRenderables();
						_elementsLocked = false; 

						ProcessDeferredAdds();
						ProcessDeferredLayerChanges();
						ProcessDeferredRemoves();

						theSwitchboard.Update(frame_dt);
					}
				}

				const bool C2DSceneManager::StartSimulation()
				{
					return _simulateOn = true;
				}

				const bool C2DSceneManager::StopSimulation()
				{
					return _simulateOn = false;
				}

				void C2DSceneManager::Add(FK2DEngine2::scene::IRenderable *newElement, int layer)
				{
					if (newElement == NULL)
					{
						LogWarn( L"增加一个空渲染对象");
						return;
					}

					//Check to see if it's an Actor; give it a name if it doesn't have one
					FK2DEngine2::actor::CActor *a = dynamic_cast<FK2DEngine2::actor::CActor*> (newElement);
					if (a != NULL)
					{
						// Ensures that the actor has a unique, non-empty name. 
						a->SetName(a->GetName());
					}

					// If we're not locked, add directly to _elements.
					if (!_elementsLocked)
					{
						newElement->m_nLayer = layer;
						_layers[layer].push_back(newElement);
					}
					// If we're locked, add to _deferredAdds and we'll add the new
					// Renderable after we're done updating all the _elements.
					else
					{
						RenderableLayerPair addMe;
						addMe._layer = layer;
						addMe._renderable = newElement;
						_deferredAdds.push_back( addMe );
					}
				}

				void C2DSceneManager::Add(FK2DEngine2::scene::IRenderable *newElement, std::wstring layer)
				{
					Add(newElement, GetLayerByName(layer));
				}

				void C2DSceneManager::Remove(FK2DEngine2::scene::IRenderable *oldElement)
				{
					if (oldElement == NULL)
					{
						return;
					}

					if (_elementsLocked)
					{
						_deferredRemoves.push_back(oldElement);
						return;
					}

					// First, make sure that it isn't deferred in the _deferredAdds list.
					std::vector<RenderableLayerPair>::iterator it = _deferredAdds.begin();
					while (it != _deferredAdds.end())
					{
						if ((*it)._renderable == oldElement)
						{
							_deferredAdds.erase(it);
							return;
						}
						++it;
					}

					// If we didn't find it in the deferred list, find/remove it from the layers.
					bool found = false;
					// Find the layer that matches the elements layer.
					RenderLayers::iterator layer = _layers.find(oldElement->m_nLayer);
					// Found the layer (list of renderables).
					if ( layer != _layers.end() )
					{
						// Now that we have the list of elements for this layer, let's remove the requested element.
						//rb - TODO - Cache off vector.
						std::vector<IRenderable*>::iterator element = (*layer).second.begin();
						for ( ; element != (*layer).second.end(); ++element )
						{
							// Found it.
							if ( (*element) == oldElement )
							{
								// Remove the element.
								element = (*layer).second.erase(element);
								found = true;
								// Nothing else to do.
								break;
							}
						}
						if (!found)
						{
							//log or error handle
						}
					}
				}
				void C2DSceneManager::UpdateLayer(FK2DEngine2::scene::IRenderable* element, int newLayer)
				{
					if (element->m_nLayer == newLayer)
						return;

					RenderableLayerPair layerChange;
					layerChange._layer = newLayer;
					layerChange._renderable = element;
					_deferredLayerChanges.push_back( layerChange );
				}

				void C2DSceneManager::UpdateLayer(FK2DEngine2::scene::IRenderable* element, std::wstring newLayerName)
				{
					UpdateLayer(element, GetLayerByName(newLayerName));
				}

				void C2DSceneManager::NameLayer(std::wstring name, int number)
				{
					_layerNames[name] = number;
				}

				const int C2DSceneManager::GetLayerByName(std::wstring name)
				{
					std::map<std::wstring,int>::iterator it = _layerNames.find(name);
					if (it != _layerNames.end())
					{
						return it->second;
					}
					else
					{
						return 0;
					}
				}

				void C2DSceneManager::SetSceneMgr(FKISceneManager* scene)
				{
					if ( (_gameManager != NULL) || ( scene == NULL ) )
					{
						return;
					}

					_gameManager = scene;
				}

				void C2DSceneManager::UnloadAll()
				{
					CFKRenderableIterator it = theWorld.GetFirstRenderable();
					while (it != GetLastRenderable())
					{
						IRenderable* renderable = (*it);
						if( _gameManager != NULL && _gameManager->IsProtectedFromUnloadAll(renderable))
						{
							// Let the persistent actors know that we're unloading the level.
							FK2DEngine2::actor::CActor* actor = dynamic_cast<FK2DEngine2::actor::CActor*>(renderable);
							if (actor)
								actor->LevelUnloaded();
							++it;
							continue;
						}

						it = it.erase( it );
						renderable->Destroy();
						delete renderable;
					}
				}
				void C2DSceneManager::ReceiveMessage(FK2DEngine2::event::CMessage *m)
				{
					if (m->GetMessageName() == L"")
					{
						// todo:
					}
				}
				float C2DSceneManager::CalculateNewDT()
				{
					_currTime = timeGetTime();
					_dt = FK2DEngine2::math::CMathUtil::Clamp((_currTime - _prevTime), 0.0f, MAX_TIMESTEP);
					_prevTime = _currTime;
					return _dt;
				}

				void C2DSceneManager::UpdateRenderables(float frame_dt)
				{
					FK2DEngine2::scene::CFKRenderableIterator it = theWorld.GetFirstRenderable();
					while (it != theWorld.GetLastRenderable())
					{
						(*it)->Update(frame_dt);
						++it;
					}
				}
				void C2DSceneManager::CleanupRenderables()
				{
					FK2DEngine2::scene::CFKRenderableIterator it = theWorld.GetFirstRenderable();
					while (it != theWorld.GetLastRenderable())
					{
						if ((*it)->IsDestroyed())
						{
							delete *it; 
							it = it.erase(it);
						}
						else
						{
							++it;
						}
					}
				}
				void C2DSceneManager::DrawRenderables()
				{
					FK2DEngine2::scene::CFKRenderableIterator it = theWorld.GetFirstRenderable();
					while (it != theWorld.GetLastRenderable())
					{
						(*it)->Render();
						++it;
					}
				}

				void C2DSceneManager::TickAndRender()
				{
					Simulate(_simulateOn);

					// 渲染管理的对象队列
					DrawRenderables();

					// GameMgr渲染
					if (_gameManager)
						_gameManager->Render();
				}

				void C2DSceneManager::ProcessDeferredAdds()
				{
					std::vector<RenderableLayerPair>::iterator it = _deferredAdds.begin();
					while(it != _deferredAdds.end())
					{
						Add( (*it)._renderable, (*it)._layer );
						++it;
					}

					_deferredAdds.clear();
				}

				void C2DSceneManager::ProcessDeferredLayerChanges()
				{
					std::vector<RenderableLayerPair>::iterator it = _deferredLayerChanges.begin();
					while(it != _deferredLayerChanges.end())
					{
						Remove((*it)._renderable);
						Add( (*it)._renderable, (*it)._layer );
						++it;
					}
					_deferredLayerChanges.clear();
				}

				void C2DSceneManager::ProcessDeferredRemoves()
				{
					RenderList::iterator it = _deferredRemoves.begin();
					while(it != _deferredRemoves.end())
					{
						Remove(*it);
						++it;
					}
					_deferredRemoves.clear();
				}
		}
	}
}
//------------------------------------------------------------------------