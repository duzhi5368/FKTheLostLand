/**
*	created:		2013-4-29   17:16
*	filename: 		FKActor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKActor.h"
#include "../Include/FKSwitchboard.h"
#include "../Include/FKLogger.h"
#include "../Include/FKStringConvert.h"
#include "../Include/FKTagCollection.h"
#include "../Include/FKIEngine.h"
#include "../Include/FKIResource.h"
#include "../Include/FK2DSceneManager.h"
#include <map>
#include <sstream>
//------------------------------------------------------------------------
using FK2DEngine2::math::Vector2;
using FK2DEngine2::Color;
using FK2DEngine2::event::CMessage;
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
		//------------------------------------------------------------------------
		std::map<std::wstring, CActor*> CActor::_nameList;
		//------------------------------------------------------------------------
		CActor::CActor()
		{
			SetColor(1.0f, 1.0f, 1.0f);
			SetAlpha(1.0f);
			SetSize(1.0f);
			SetRotation(0.0f);
			SetPosition(0.0f, 0.0f);
			SetUVs(FK2DEngine2::math::Vector2(0.f, 0.f), FK2DEngine2::math::Vector2(1.f, 1.f));
			_name = L"";

			_spriteNumFrames = 0;
			_spriteCurrentFrame = 0;
			_spriteTextureReferences[0] = -1; 
			_spriteFrameDelay = 0.0f;

			m_nLayer = 0;

			_drawShape = ADS_Square;
		}
		//------------------------------------------------------------------------
		CActor::~CActor()
		{
			g_pEngineInstance->getVideoDriver()->freeTexture( _renderQuad.texture );

			std::set<std::wstring>::iterator it = _tags.begin();
			while (it != _tags.end())
			{
				std::wstring tag = *it;
				it++;
				Untag(tag);
			}

			CActor::_nameList.erase(_name);

			std::set<std::wstring> subs = theSwitchboard.GetSubscriptionsFor(this);
			it = subs.begin();
			while (it != subs.end())
			{
				theSwitchboard.UnsubscribeFrom(this, *it);
				++it;
			}
		}
		//------------------------------------------------------------------------
		void CActor::Update(float dt)
		{
			UpdateSpriteAnimation(dt);

			if (_positionInterval.ShouldStep())
			{
				SetPosition(_positionInterval.Step(dt));
				if (!_positionInterval.ShouldStep())
				{
					if (_positionIntervalMessage != L"")
					{
						theSwitchboard.Broadcast(new CMessage(_positionIntervalMessage, this));
					}
				}
			}
			if (_rotationInterval.ShouldStep())
			{
				SetRotation(_rotationInterval.Step(dt));
				if (!_rotationInterval.ShouldStep())
				{
					if (_rotationIntervalMessage != L"")
					{
						theSwitchboard.Broadcast(new CMessage(_rotationIntervalMessage, this));
					}
				}
			}
			if (_colorInterval.ShouldStep())
			{
				SetColor(_colorInterval.Step(dt));
				if (!_colorInterval.ShouldStep())
				{
					if (_colorIntervalMessage != L"")
					{
						theSwitchboard.Broadcast(new CMessage(_colorIntervalMessage, this));
					}
				}
			}
			if (_sizeInterval.ShouldStep())
			{
				FK2DEngine2::math::Vector2 newSize = _sizeInterval.Step(dt);
				SetSize(newSize.X, newSize.Y);
				if (!_sizeInterval.ShouldStep())
				{
					if (_sizeIntervalMessage != L"")
					{
						theSwitchboard.Broadcast(new CMessage(_sizeIntervalMessage, this));
					}
				}
			}
		}
		//------------------------------------------------------------------------
		void CActor::UpdateSpriteAnimation(float dt)
		{
			if (_spriteFrameDelay > 0.0f)
			{
				_spriteCurrentFrameDelay -= dt;

				if (_spriteCurrentFrameDelay < 0.0f)
				{
					while (_spriteCurrentFrameDelay < 0.0f)
					{
						if (_spriteAnimType == SAT_Loop)
						{
							if (_spriteCurrentFrame == _spriteAnimEndFrame)
								_spriteCurrentFrame = _spriteAnimStartFrame;
							else
								++_spriteCurrentFrame;
						}
						else if (_spriteAnimType == SAT_PingPong)
						{
							if (_spriteAnimDirection == 1)
							{
								if (_spriteCurrentFrame == _spriteAnimEndFrame)
								{
									_spriteAnimDirection = -1;
									_spriteCurrentFrame = _spriteAnimEndFrame - 1;
								}
								else
									++_spriteCurrentFrame;

							}
							else
							{
								if (_spriteCurrentFrame == _spriteAnimStartFrame)
								{
									_spriteAnimDirection = 1;
									_spriteCurrentFrame = _spriteAnimStartFrame + 1;
								}
								else 
								{
									--_spriteCurrentFrame; 
								}
							}
						}
						else if (_spriteAnimType == SAT_OneShot)
						{
							// If we're done with our one shot and they set an animName, let them know it's done.
							if (_spriteCurrentFrame == _spriteAnimEndFrame)
							{
								// Needs to get called before callback, in case they start a new animation.
								_spriteAnimType = SAT_None;

								if (_currentAnimName.length() > 0) 
								{
									AnimCallback(_currentAnimName);
								}
							}
							else
							{
								_spriteCurrentFrame += _spriteAnimDirection;
							}
						}

						_spriteCurrentFrameDelay += _spriteFrameDelay;
					}
				}
			}
		}
		//------------------------------------------------------------------------
		void CActor::SetDrawShape( actorDrawShape drawShape )
		{
			_drawShape = drawShape;
		}
		//------------------------------------------------------------------------
		const actorDrawShape CActor::GetDrawShape()
		{
			return _drawShape;
		}
		//------------------------------------------------------------------------
		void CActor::MoveTo(FK2DEngine2::math::Vector2 newPosition, float duration, bool smooth, std::wstring onCompletionMessage)
		{
			_positionInterval = FK2DEngine2::math::CInterval<FK2DEngine2::math::Vector2>(_position, newPosition, duration, smooth);
			_positionIntervalMessage = onCompletionMessage;
		}
		//------------------------------------------------------------------------
		void CActor::RotateTo(float newRotation, float duration, bool smooth, std::wstring onCompletionMessage)
		{
			_rotationInterval = FK2DEngine2::math::CInterval<float>(_rotation, newRotation, duration, smooth);
			_rotationIntervalMessage = onCompletionMessage;
		}
		//------------------------------------------------------------------------
		void CActor::ChangeColorTo(FK2DEngine2::Color newColor, float duration, bool smooth, std::wstring onCompletionMessage)
		{
			_colorInterval = FK2DEngine2::math::CInterval<FK2DEngine2::Color>(_color, newColor, duration, smooth);
			_colorIntervalMessage = onCompletionMessage;
		}
		//------------------------------------------------------------------------
		void CActor::ChangeSizeTo(FK2DEngine2::math::Vector2 newSize, float duration, bool smooth, std::wstring onCompletionMessage)
		{
			_sizeInterval = FK2DEngine2::math::CInterval<FK2DEngine2::math::Vector2>(_size, newSize, duration, smooth);
			_sizeIntervalMessage = onCompletionMessage;
			_renderQuad.makeRect( newSize.X, newSize.Y );
		}
		//------------------------------------------------------------------------
		void CActor::ChangeSizeTo(float newSize, float duration, bool smooth, std::wstring onCompletionMessage)
		{
			ChangeSizeTo(FK2DEngine2::math::Vector2(newSize, newSize), duration, smooth, onCompletionMessage);
		}
		//------------------------------------------------------------------------
		void CActor::Render()
		{
			theWorld.RenderActor( this );
		}
		//------------------------------------------------------------------------
		void CActor::SetSize(float x, float y)
		{
			float sizeX, sizeY;
			if (x < 0.0f)
				sizeX = 0.0f;
			else
				sizeX = x;
			if (y <= 0.f)
				sizeY = x;
			else
				sizeY = y;
			_size = FK2DEngine2::math::Vector2(sizeX, sizeY);
			_renderQuad.makeRect( _size.X, _size.Y );
		}
		//------------------------------------------------------------------------
		void CActor::SetSize(FK2DEngine2::math::Vector2 newSize)
		{
			if (newSize.X < 0.0f)
			{
				newSize.X = 0.0f;
			}
			if (newSize.Y < 0.0f)
			{
				newSize.Y = 0.0f;
			}
			_size = newSize;
			_renderQuad.makeRect( _size.X, _size.Y );
		}
		//------------------------------------------------------------------------
		const FK2DEngine2::math::Vector2 CActor::GetSize()
		{
			return _size;
		}
		//------------------------------------------------------------------------
		void CActor::SetPosition(float x, float y)
		{
			_position.X = x;
			_position.Y = y;
		}
		//------------------------------------------------------------------------
		void CActor::SetPosition(FK2DEngine2::math::Vector2 pos)
		{
			_position = pos;
		}
		//------------------------------------------------------------------------
		const FK2DEngine2::math::Vector2 CActor::GetPosition()
		{
			return _position;
		}
		//------------------------------------------------------------------------
		void CActor::SetRotation(float rotation)
		{
			_rotation = rotation;
		}
		//------------------------------------------------------------------------
		const float CActor::GetRotation()
		{
			return _rotation;
		}
		//------------------------------------------------------------------------
		const FK2DEngine2::Color CActor::GetColor()
		{
			return _color;
		}
		//------------------------------------------------------------------------
		void CActor::SetColor(float r, float g, float b, float a)
		{
			_color = FK2DEngine2::Color(r, g, b, a);
		}
		//------------------------------------------------------------------------
		void CActor::SetColor(FK2DEngine2::Color color)
		{
			_color = color;
		}
		//------------------------------------------------------------------------
		void CActor::SetAlpha(float newAlpha)
		{
			_color.a = newAlpha;
		}
		//------------------------------------------------------------------------
		const float CActor::GetAlpha()
		{
			return _color.a;
		}
		//------------------------------------------------------------------------
		void CActor::SetSpriteTexture(int texRef, int frame)
		{
			frame = FK2DEngine2::math::CMathUtil::Clamp(frame, 0, MAX_SPRITE_FRAMES - 1);

			// Make sure to bump the number of frames if this frame surpasses it.
			if (frame >= _spriteNumFrames)
			{
				_spriteNumFrames = frame + 1;
			}

			_spriteTextureReferences[frame] = texRef;
		}
		//------------------------------------------------------------------------
		const int CActor::GetSpriteTexture(int frame)
		{
			frame = FK2DEngine2::math::CMathUtil::Clamp(frame, 0, _spriteNumFrames - 1);

			return _spriteTextureReferences[frame];
		}
		//------------------------------------------------------------------------
		bool CActor::SetSprite(std::wstring filename, int frame, bool optional)
		{
			if( !g_pEngineInstance->getResourceMap() )
			{
				LogError( L"引擎资源表尚未初始化。");
				return false;
			}
			_renderQuad.texture = g_pEngineInstance->getVideoDriver()->loadTexture( filename, filename );
			FK2DEngine2::core::IResource *pTexture = g_pEngineInstance->getResourceMap()->getResourceByName( filename );
			int textureReference = 0;
			if( pTexture == NULL )
			{
				textureReference = -1;
			}
			else
			{
				textureReference = pTexture->getRef();
			}
			if (textureReference == -1)
			{
				return false;
			}

			SetSpriteTexture(textureReference, frame);
			return true;
		}
		//------------------------------------------------------------------------
		void CActor::ClearSpriteInfo()
		{
			for (int i=0; i<_spriteNumFrames; ++i)
			{
				_spriteTextureReferences[i] = -1;
			}
			_spriteAnimType = SAT_None;
			_spriteFrameDelay = 0.0f;
			_spriteCurrentFrame = 0;
		}
		//------------------------------------------------------------------------
		void CActor::SetSpriteFrame(int frame)
		{
			frame = FK2DEngine2::math::CMathUtil::Clamp(frame, 0, _spriteNumFrames - 1);

			if (_spriteTextureReferences[frame] == -1)
			{
				LogWarn( L"动画帧 : %d 的纹理不存在", frame );
			}

			_spriteCurrentFrame = frame;
		}
		//------------------------------------------------------------------------
		void CActor::PlaySpriteAnimation(float delay, spriteAnimationType animType, int startFrame, int endFrame, const wchar_t* _animName)
		{
			startFrame = FK2DEngine2::math::CMathUtil::Clamp(startFrame, 0, _spriteNumFrames-1);
			endFrame = FK2DEngine2::math::CMathUtil::Clamp(endFrame, 0, _spriteNumFrames-1);

			_spriteAnimDirection = startFrame > endFrame ? -1 : 1;

			_spriteCurrentFrameDelay = _spriteFrameDelay = delay;
			_spriteAnimType= animType;
			_spriteAnimStartFrame = _spriteCurrentFrame = startFrame;
			_spriteAnimEndFrame = endFrame;
			if (_animName)
				_currentAnimName = _animName;
		}
		//------------------------------------------------------------------------
		void CActor::LoadSpriteFrames(std::wstring firstFilename)
		{
			int extensionLocation = firstFilename.rfind(L".");
			int numberSeparator = firstFilename.rfind(L"_");
			int numDigits = extensionLocation - numberSeparator - 1;

			// Clear out the number of frames we think we have.
			_spriteNumFrames = 0;

			bool bValidNumber = true;
			// So you're saying I've got a chance?
			if (numberSeparator > 0 && numDigits > 0)
			{
				// Now see if all of the digits between _ and . are numbers (i.e. test_001.jpg).
				for (int i=1; i<=numDigits; ++i)
				{
					char digit = firstFilename[numberSeparator+i];
					if (digit < '0' || digit > '9')
					{
						bValidNumber = false;
						break;
					}
				}
			}

			// If these aren't valid, the format is incorrect.
			if (numberSeparator == (int)std::wstring::npos || numDigits <= 0 || !bValidNumber)
			{
				LogWarn( L"LoadSpriteFrames() 失败: %s" , firstFilename );

				if (!SetSprite(firstFilename, 0))
					return;
			}

			// If we got this far, the filename format is correct.
			std::wstring numberString;
			// The number wstring is just the digits between the '_' and the file extension (i.e. 001).
			numberString.append(firstFilename.c_str(), numberSeparator+1, numDigits);

			// Get our starting numberical value.
			int number = _wtoi(numberString.c_str());

			std::wstring baseFilename;
			// The base name is everything up to the '_' before the number (i.e. somefile_).
			baseFilename.append( firstFilename.c_str(), numberSeparator+1);

			std::wstring extension;
			// The extension is everything after the number (i.e. .jpg).
			extension.append(firstFilename.c_str(), extensionLocation, firstFilename.length() - extensionLocation);

			// Keep loading until we stop finding images in the sequence.
			while (true)
			{
				// Build up the filename of the current image in the sequence.
				std::wstring newFilename = baseFilename + numberString + extension;

				// Were we able to load the file for this sprite?
				if (!SetSprite(newFilename, _spriteNumFrames, true /*optional*/))
				{
					break;
				}

				// Verify we don't go out of range on our hard-coded frame limit per sprite.
				if (_spriteNumFrames >= MAX_SPRITE_FRAMES)
				{
					LogWarn( L"精灵帧数超长：%d", MAX_SPRITE_FRAMES );
					break;
				}

				// Bump the number to the next value in the sequence.
				++number;

				// Serialize the numerical value to it so we can retrieve the wstring equivalent.
				std::wstring newNumberString = FK2DEngine2::core::IntToString(number);

				// We assume that all the files have as many numerical digits as the first one (or greater) (i.e. 01..999).
				// See if we need to pad with leading zeros.
				int numLeadingZeros = numDigits - (int)newNumberString.length();

				// Do the leading zero padding.
				for (int i=0; i<numLeadingZeros; ++i)
				{
					newNumberString = L"0" + newNumberString;
				}

				// Save off the newly formulated number wstring for the next image in the sequence.
				numberString = newNumberString;
			}
		}
		//------------------------------------------------------------------------
		void CActor::SetUVs(const FK2DEngine2::math::Vector2 lowleft, const FK2DEngine2::math::Vector2 upright)
		{
			UV_rightup = upright;
			UV_leftlow = lowleft;
		}
		//------------------------------------------------------------------------
		void CActor::GetUVs(FK2DEngine2::math::Vector2 &lowleft, FK2DEngine2::math::Vector2 &upright) const
		{
			upright = UV_rightup;
			lowleft = UV_leftlow;
		}
		//------------------------------------------------------------------------
		const bool CActor::IsTagged(std::wstring tag)
		{
			std::set< std::wstring >::iterator it = _tags.find(tag);
			if (it != _tags.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//------------------------------------------------------------------------
		void CActor::Tag(std::wstring newTag)
		{
			std::vector< std::wstring > tags = FK2DEngine2::core::SplitString(newTag, L", ");
			for(unsigned int i=0; i < tags.size(); i++)
			{
				tags[i] = FK2DEngine2::core::ToLower(tags[i]);
				_tags.insert(tags[i]);
				theTagList.AddObjToTagList(this, tags[i]);
			}
		}
		//------------------------------------------------------------------------
		void CActor::Untag(std::wstring oldTag)
		{
			_tags.erase(oldTag);
			theTagList.RemoveObjFromTagList(this, oldTag);
		}
		//------------------------------------------------------------------------
		const std::set< std::wstring > CActor::GetTags()
		{
			return _tags;
		}
		//------------------------------------------------------------------------
		const std::wstring CActor::SetName(std::wstring newName)
		{
			if(newName.length() == 0)
			{
				newName = GetActorClassName();
			}

			newName[0] = toupper(newName[0]);

			if (CActor::GetNamed(newName) == NULL)
			{
				_name = newName;
			}
			else
			{
				int counter = 1;
				std::wostringstream iteratedName;
				do 
				{
					iteratedName.str(L"");
					iteratedName << newName << counter++;
				} while(CActor::GetNamed(iteratedName.str()) != NULL);

				_name = iteratedName.str();
			}

			CActor::_nameList[_name] = this;

			return _name;
		}
		//------------------------------------------------------------------------
		const std::wstring CActor::GetName()
		{
			return _name;
		}
		//------------------------------------------------------------------------
		const CActor* CActor::GetNamed(std::wstring nameLookup)
		{
			std::map<std::wstring,CActor*>::iterator it = _nameList.find(nameLookup);
			if (it == _nameList.end())
			{
				return NULL;
			}
			else
			{
				return it->second;
			}
		}
		//------------------------------------------------------------------------
		CActor* CActor::Create(std::wstring archetype)
		{
			std::wstring markerTag = L"Actor";
			ActorSet tagged = theTagList.GetObjectsTagged(markerTag);
			if (tagged.size() > 1)
			{
				LogWarn( L"多于一个Actor被标签为 %s( %s )", markerTag ,archetype );
			}
			if (tagged.size() < 1)
			{
				LogError( L"创建Actor标签失败 ( %s )",archetype );
				return NULL;
			}
			ActorSet::iterator it = tagged.begin();
			CActor* forReturn = *it;
			if (forReturn != NULL)
			{
				forReturn->Untag(markerTag);	
			}
			return forReturn;
		}
		//------------------------------------------------------------------------
		void CActor::SetLayer(int layerIndex)
		{
			theWorld.UpdateLayer(this, layerIndex);
		}
		//------------------------------------------------------------------------
		void CActor::SetLayer(std::wstring layerName)
		{
			theWorld.UpdateLayer(this, layerName);
		}
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------