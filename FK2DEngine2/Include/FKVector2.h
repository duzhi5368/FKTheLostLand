/**
*	created:		2013-4-28   23:35
*	filename: 		FKVector2
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		class Vector2
		{
		public:
			float X;
			float Y;
		public:
			static Vector2 Zero;
			static Vector2 One;
			static Vector2 UnitX;
			static Vector2 UnitY;
		public:
			Vector2(float x, float y);
			Vector2(float value);
			Vector2();
		public:
			float	Length();
			float	LengthSquared();
			void	Normalize();
		public:
			static float Distance(const Vector2& value1, const Vector2& value2);
			static float DistanceSquared(const Vector2& value1, const Vector2& value2);
			static float Dot(const Vector2& value1, const Vector2& value2);
			static Vector2 Normalize(const Vector2& value);
			static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
			static Vector2 Min(const Vector2& value1, const Vector2& value2);
			static Vector2 Max(const Vector2& value1, const Vector2& value2);
			static Vector2 Clamp(const Vector2& value, const Vector2& min, const Vector2& max);
			static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
			static Vector2 Negate(const Vector2& value);
			static Vector2 Rotate(const Vector2& value, const float radians);
		public:
			bool operator==(const Vector2 &v) const;
			bool operator!=(const Vector2 &v) const;

			Vector2 operator-() const;
			Vector2 operator-(const Vector2 &v) const;
			Vector2 operator+(const Vector2 &v) const;
			Vector2 operator/(float divider) const;
			Vector2 operator*(float scaleFactor) const;
		};

		struct Vec2i
		{
			int X, Y;
			Vec2i(int x, int y) : X(x), Y(y) {}
			Vec2i() : X(0), Y(0) {}
		};
	}
}