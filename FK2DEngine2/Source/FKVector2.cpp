/**
*	created:		2013-4-28   23:40
*	filename: 		FKVector2
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKVector2.h"
#include "../Include/FKMathUtil.h"
#include <math.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		Vector2 Vector2::Zero(0.0f, 0.0f);
		Vector2 Vector2::One(1.0f, 1.0f);
		Vector2 Vector2::UnitX(1.0f, 0.0f);
		Vector2 Vector2::UnitY(0.0f, 1.0f);

		Vector2::Vector2(float x, float y)
			: X(x)
			, Y(y)
		{}

		Vector2::Vector2(float value)
			: X(value)
			, Y(value)
		{}

		Vector2::Vector2()
			: X(0)
			, Y(0)
		{}

		float Vector2::Length()
		{
			return sqrt(LengthSquared());
		}

		float Vector2::LengthSquared()
		{
			return (X * X) + (Y * Y);
		}

		float Vector2::Distance(const Vector2& value1, const Vector2& value2)
		{
			return Vector2(value1 - value2).Length();
		}

		float Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2)
		{
			return Vector2(value1 - value2).LengthSquared();

		}

		float Vector2::Dot(const Vector2& value1, const Vector2& value2)
		{
			return ((value1.X * value2.X) + (value1.Y * value2.Y));
		}

		void Vector2::Normalize()
		{
			float len = Length();


			if( len < 1e-7f )
			{
				if( Y > X )
					*this = UnitY;
				else
					*this = UnitX;
			}
			else
			{
				*this = *this / len;
			}
		}

		Vector2 Vector2::Normalize(const Vector2& value)
		{
			Vector2 retVal(value);
			retVal.Normalize();
			return retVal;
		}

		Vector2 Vector2::Reflect(const Vector2& vector, const Vector2& normal)
		{
			return vector - (normal * 2.0f * Dot(vector, normal));
		}

		Vector2 Vector2::Min(const Vector2& value1, const Vector2& value2)
		{
			return Vector2(CMathUtil::Min(value1.X, value2.X), CMathUtil::Min(value1.Y, value2.Y));
		}

		Vector2 Vector2::Max(const Vector2& value1, const Vector2& value2)
		{
			return Vector2(CMathUtil::Max(value1.X, value2.X), CMathUtil::Max(value1.Y, value2.Y));
		}

		Vector2 Vector2::Clamp(const Vector2& value, const Vector2& min, const Vector2& max)
		{
			return Vector2(CMathUtil::Clamp(value.X, min.X, max.X), CMathUtil::Clamp(value.Y, min.Y, max.Y));
		}

		Vector2 Vector2::Lerp(const Vector2& value1, const Vector2& value2, float amount)
		{
			return Vector2( CMathUtil::Lerp( value1.X, value2.X, amount ), CMathUtil::Lerp( value1.Y, value2.Y, amount ) );
		}
		Vector2 Vector2::Negate(const Vector2& value)
		{
			return -value;
		}

		Vector2 Vector2::Rotate(const Vector2& value, const float radians)
		{
			float c = cos(radians);
			float s = sin(radians);
			return Vector2(value.X*c-value.Y*s,value.Y*c+value.X*s);
		}

		bool Vector2::operator==(const Vector2 &v) const
		{
			return X == v.X && Y == v.Y;
		}

		bool Vector2::operator!=(const Vector2 &v) const
		{
			return !(*this == v);
		}

		Vector2 Vector2::operator-() const
		{
			return Vector2::Zero - *this;
		}

		Vector2 Vector2::operator-(const Vector2 &v) const
		{
			return Vector2(X - v.X, Y - v.Y);
		}

		Vector2 Vector2::operator+(const Vector2 &v) const
		{
			return Vector2(X + v.X, Y + v.Y);
		}

		Vector2 Vector2::operator/(float divider) const
		{
			return Vector2(X / divider, Y / divider);
		}

		Vector2 Vector2::operator*(float scaleFactor) const
		{
			return Vector2(X * scaleFactor, Y * scaleFactor);
		}
	}
}