/**
*	created:		2013-4-29   17:32
*	filename: 		FKInterval
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKMathUtil.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		template<class T>
		class CInterval
		{
		public:
			CInterval(T start, T end, float duration, bool smooth=false) :
				_start(start),
				_end(end),
				_current(start),
				_duration(duration),
				_timer(0.0f),
				_shouldStep(true),
				_smoothStep(smooth)
			{
			}
			
			CInterval()
			{
				_shouldStep = false;
			}

			T Step(float dt)
			{
				if (!_shouldStep)
				{
					return _current;
				}

				_timer += dt;

				if (_timer >= _duration)
				{
					_current = _end;
					_shouldStep = false;
				}
				else
				{
					float stepRatio = _timer / _duration;
					if (_smoothStep)
					{
						//smooth step
						_current = CMathUtil::SmoothStep(_start, _end, stepRatio);
					}
					else
					{
						//simple lerp
						_current = CMathUtil::Lerp(_start, _end, stepRatio);
					}
				}

				return _current;
			}
			
			float GetCurrent()
			{
				return _current;
			}

			bool ShouldStep()
			{
				return _shouldStep;
			}
			
		private:
			T _start;
			T _end;
			T _current;
			
			float _duration;
			float _timer;
			
			bool _shouldStep;
			bool _smoothStep;
		};
	}
}
//------------------------------------------------------------------------