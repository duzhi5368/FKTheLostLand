/**
*	created:		2013-5-1   19:52
*	filename: 		FKGridActor
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKActor.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace actor
	{
		class CGridActor : public CActor
		{
		public:
			CGridActor();
			CGridActor(FK2DEngine2::Color lines, FK2DEngine2::Color axis, float interval, 
				FK2DEngine2::math::Vector2 minCoord, FK2DEngine2::math::Vector2 maxCoord);
			void SetLineColor(FK2DEngine2::Color lineCol);
			const FK2DEngine2::Color GetLineColor();
			void SetAxisColor(FK2DEngine2::Color axisCol);
			const FK2DEngine2::Color GetAxisColor();
			void SetInterval(float interval);
			const float GetInterval();
			void SetMinCoord(FK2DEngine2::math::Vector2 minCoord);
			const FK2DEngine2::math::Vector2 GetMinCoord();
			void SetMaxCoord(FK2DEngine2::math::Vector2 maxCoord);
			const FK2DEngine2::math::Vector2 GetMaxCoord();
			virtual void Render();
			virtual void Update(float dt) {}
		private:
			FK2DEngine2::Color 			_lineColor;
			FK2DEngine2::Color 			_axisColor;
			float						_interval;
			FK2DEngine2::math::Vector2	_minCoord;
			FK2DEngine2::math::Vector2	_maxCoord;
		};
	}
}