/**
*	created:		2013-4-28   23:31
*	filename: 		FKActor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKIRenderable.h"
#include "FKMessage.h"
#include "FKVector2.h"
#include "UI/FKStructures.h"
#include "FKInterval.h"
#include "FKITexture.h"
#include "FKS2DObject.h"
#include <vector>
#include <set>
#include <map>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
		// 精灵动画最大帧数
		#define MAX_SPRITE_FRAMES 64

		enum spriteAnimationType
		{
			SAT_None,
			SAT_Loop,
			SAT_PingPong,
			SAT_OneShot
		};

		enum actorDrawShape
		{
			ADS_Square,
			ADS_Circle			// 圆形不能使用纹理
		};

		class CActor : public FK2DEngine2::scene::IRenderable ,  public FK2DEngine2::event::CMessageListener
		{
		public:
			CActor();
			virtual ~CActor();
		public:
			void SetSize(float x, float y = -1.f); 
			void SetSize( FK2DEngine2::math::Vector2 newSize );
			const FK2DEngine2::math::Vector2 GetSize();

			virtual void SetPosition(float x, float y);
			virtual void SetPosition(FK2DEngine2::math::Vector2 pos);
			const FK2DEngine2::math::Vector2 GetPosition();

			void SetRotation(float rotation);
			const float GetRotation();

			void SetColor(float r, float g, float b, float a=1.0f);
			void SetColor(FK2DEngine2::Color color);
			const FK2DEngine2::Color GetColor();

			void SetAlpha(float newAlpha);
			const float GetAlpha();

			void SetDrawShape( actorDrawShape drawShape );
			const actorDrawShape GetDrawShape();

			void SetLayer(int layerIndex);
			void SetLayer(std::wstring layerName);

			void SetUVs(const FK2DEngine2::math::Vector2 upright, const FK2DEngine2::math::Vector2 lowleft);
			void GetUVs(FK2DEngine2::math::Vector2 &upright, FK2DEngine2::math::Vector2 &lowleft) const;

			void MoveTo(FK2DEngine2::math::Vector2 newPosition, float duration, 
				bool smooth=false, std::wstring onCompletionMessage=L"");
			void RotateTo(float newRotation, float duration, 
				bool smooth=false, std::wstring onCompletionMessage=L"");
			void ChangeColorTo(FK2DEngine2::Color newColor, float duration, 
				bool smooth=false, std::wstring onCompletionMessage=L"");
			void ChangeSizeTo(FK2DEngine2::math::Vector2 newSize, float duration, 
				bool smooth=false, std::wstring onCompletionMessage=L"");
			void ChangeSizeTo(float newSize, float duration, 
				bool smooth=false, std::wstring onCompletionMessage=L"");

			const int GetSpriteTexture(int frame = 0);
			bool SetSprite(std::wstring filename, int frame = 0,bool optional=false);
			void ClearSpriteInfo();
			void LoadSpriteFrames(std::wstring firstFilename);
			void PlaySpriteAnimation(float delay, spriteAnimationType animType = SAT_Loop,
				int startFrame = -1, int endFrame = -1, const wchar_t* animName = NULL);
			bool IsSpriteAnimPlaying(){return (_spriteFrameDelay > 0);}
			virtual void AnimCallback(std::wstring animName) {}
			virtual void ReceiveMessage(FK2DEngine2::event::CMessage* message) {}
			virtual void Update(float dt);
			virtual void Render();
			CActor* GetSelf(){return this;}
			static CActor* Create(std::wstring archetype);
			virtual const std::wstring GetActorClassName() { return L"Actor"; }

			virtual void LevelUnloaded() {}

			void SetSpriteFrame(int frame);
			const int GetSpriteFrame() { return _spriteCurrentFrame; }

			const bool IsTagged(std::wstring tag);
			void Tag(std::wstring newTag);
			void Untag(std::wstring oldTag);
			const std::set<std::wstring> GetTags();

			const std::wstring SetName(std::wstring newName);
			const std::wstring GetName();
			static const CActor* GetNamed(std::wstring nameLookup);
			FK2DEngine2::video::ITexture* GetTexture(){return _renderQuad.texture;}
			FK2DEngine2::scene::S2D::S2DQuad& GetRenderQuad(){ return _renderQuad;}
		protected:
			FK2DEngine2::math::Vector2	_size;
			FK2DEngine2::math::Vector2	_position;
			FK2DEngine2::Color			_color;
			float						_rotation;
			FK2DEngine2::scene::S2D::S2DQuad _renderQuad;

			FK2DEngine2::math::Vector2 	UV_rightup;
			FK2DEngine2::math::Vector2 	UV_leftlow;

			actorDrawShape				_drawShape;

			int							_spriteCurrentFrame;
			int							_spriteNumFrames;
			float						_spriteFrameDelay;
			float						_spriteCurrentFrameDelay;
			int							_spriteTextureReferences[MAX_SPRITE_FRAMES];
			spriteAnimationType 		_spriteAnimType;
			int							_spriteAnimStartFrame;
			int							_spriteAnimEndFrame;
			int							_spriteAnimDirection;

			std::set<std::wstring>		_tags;
			std::wstring				_name;
			static std::map<std::wstring, CActor*> _nameList;

			std::wstring							_currentAnimName;
		private:
			void SetSpriteTexture(int texRef, int frame = 0);
			void UpdateSpriteAnimation(float dt);

			FK2DEngine2::math::CInterval<FK2DEngine2::math::Vector2>	_positionInterval; 
			std::wstring												_positionIntervalMessage;
			FK2DEngine2::math::CInterval<float>							_rotationInterval; 
			std::wstring												_rotationIntervalMessage;
			FK2DEngine2::math::CInterval<FK2DEngine2::Color>			_colorInterval; 
			std::wstring												_colorIntervalMessage;
			FK2DEngine2::math::CInterval<FK2DEngine2::math::Vector2>	_sizeInterval; 
			std::wstring												_sizeIntervalMessage;
		};

		typedef std::vector<CActor*>		ActorList;
		typedef std::set<CActor*>			ActorSet;
	}
}