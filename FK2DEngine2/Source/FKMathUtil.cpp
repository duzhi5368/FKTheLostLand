/**
*	created:		2013-4-29   16:47
*	filename: 		FKMathUtil
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKMathUtil.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{

		const float CMathUtil::E = 2.718282f;
		const float CMathUtil::Log10E = 0.4342945f;
		const float CMathUtil::Log2E = 1.442695f;
		const float CMathUtil::Pi = 3.141593f;
		const float CMathUtil::PiOver2 = 1.570796f;
		const float CMathUtil::PiOver4 = 0.7853982f;
		const float CMathUtil::TwoPi = 6.283185f;
		const float CMathUtil::MaxFloat = 3.402823E+38f;
		const float CMathUtil::MinFloat = -3.402823E+38f;
		const float CMathUtil::Epsilon = 0.000001f;
		//------------------------------------------------------------------------
		float CMathUtil::ToDegrees(float radians)
		{
			return (radians * 57.29578f);
		}

		float CMathUtil::ToRadians(float degrees)
		{
			return (degrees * 0.01745329f);
		}

		Vector2 CMathUtil::VectorFromAngle(float angle_in_degrees)
		{
			return Vector2(cos(ToRadians(angle_in_degrees)), sin(ToRadians(angle_in_degrees)));
		}

		float CMathUtil::AngleFromVector(const Vector2& v1)
		{
			Vector2 localVector = v1;

			localVector.Normalize();
			return atan( localVector.Y / localVector.X );	
		}

		float CMathUtil::AngleFromVectors(const Vector2& v1, const Vector2& v2)
		{	
			return atan2(v1.Y, v1.X) - atan2(v2.Y, v2.X);
		}


		int CMathUtil::RoundToInt(double x)
		{
			return ((int)(floor(x+0.5)));
		}

		int CMathUtil::RandomInt(int maximum)
		{
			static bool firstTime = true;
			if (firstTime) 
			{
				firstTime = false;
				srand((int)time(NULL));
			}
			if (maximum <= 0) 
			{
				return 0;
			}
			return (rand() % maximum);
		}

		int CMathUtil::RandomIntInRange(int min, int max)
		{
			return RandomInt(max-min) + min;
		}

		int CMathUtil::RandomIntWithError(int target, int error)
		{
			return RandomIntInRange(target-error, target+error);
		}

		float CMathUtil::RandomFloat(float maximum)
		{
			const float bigNumber = 10000.0f;
			float randFloat = (float)RandomInt((int)bigNumber);
			randFloat = randFloat/bigNumber;
			return randFloat*maximum;
		}

		float CMathUtil::RandomFloatInRange(float min, float max)
		{
			return RandomFloat(max-min) + min;
		}

		float CMathUtil::RandomFloatWithError(float target, float error)
		{
			return RandomFloatInRange(target-error, target+error);
		}

		bool CMathUtil::RandomBool()
		{
			return CMathUtil::RandomInt(2) > 0;
		}

		Vector2 CMathUtil::RandomVector()
		{
			return RandomVector(Vector2(1.0f));//.Normalize();
		}

		Vector2 CMathUtil::RandomVector(Vector2 maxValues)
		{
			return RandomVector(Vector2::Zero, maxValues);
		}

		Vector2 CMathUtil::RandomVector(Vector2 minValues, Vector2 maxValues)
		{
			return Vector2(RandomFloatInRange(minValues.X, maxValues.X), RandomFloatInRange(minValues.Y, maxValues.Y));
		}

		bool CMathUtil::FuzzyEquals(float value1, float value2, float epsilon)
		{
			float a = value1 - value2;
			if (fabs(a) < epsilon)
			{
				return true;
			}
			return false;
		}


		bool CMathUtil::FuzzyEquals(Vector2 v1, Vector2 v2, float epsilon)
		{
			if ( (CMathUtil::FuzzyEquals(v1.X, v2.X, epsilon)) && (CMathUtil::FuzzyEquals(v1.Y, v2.Y, epsilon)) )
			{
				return true;
			}
			return false;
		}

		float CMathUtil::DeltaAngle(float A1, float A2)
		{
			// Find the difference
			float Delta = A2 - A1;

			// If change is larger than PI
			if(Delta > Pi)
			{
				// Flip to negative equivalent
				Delta = Delta - (TwoPi);
			}
			else if(Delta < -Pi)
			{
				// Otherwise, if change is smaller than -PI
				// Flip to positive equivalent
				Delta = Delta + (TwoPi);
			}

			// Return delta in [-PI,PI] range
			return Delta;
		}

		float CMathUtil::VectorDeltaAngle(Vector2 v1, Vector2 v2)
		{
			return acos( Vector2::Dot(v1, v2) );
		}
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------