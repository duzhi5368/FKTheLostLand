/**
*	created:		2013-4-23   14:40
*	filename: 		FKVector3
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <cmath>
#include "FKMathMacro.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		class Vector3
		{
		public:
			Vector3() : x(0),y(0),z(0) {}
			Vector3(float mx,float my,float mz) : x(mx) ,y(my), z(mz) {}
			Vector3(const Vector3 & v3): x(v3.x),y(v3.y),z(v3.z){}
			//virtual ~Vector3(){}
			void SetValue(float mx,float my,float mz){
				x = mx; y = my; z = mz; 
			}
			Vector3 & operator = (const Vector3 & v3){
				x = v3.x ; y = v3.y ; z = v3.z;
				return (*this);
			}
			Vector3 operator - (){
				return Vector3(-x,-y,-z);
			}
			Vector3 operator + (const Vector3 & v3){
				return Vector3(x + v3.x ,y + v3.y, z + v3.z);
			}
			Vector3 & operator += (const Vector3 & v3){
				x += v3.x; y += v3.y; z += v3.z;
				return (* this);
			}
			Vector3 operator - (const Vector3 & v3){
				return Vector3(x - v3.x, y - v3.y, z -v3.z);
			}
			Vector3 & operator -= (const Vector3 & v3){
				x -= v3.x; y -= v3.y; z -= v3.z;
				return (*this);
			}
			Vector3 operator * (float m){
				return Vector3 (x * m, y * m,z * m);
			}
			Vector3 & operator *= (float m){
				x *= m; y *=m; z *= m;
				return (*this);
			}
			float DotProduct(const Vector3 & v3){
				return x * v3.x + y * v3.y + z * v3.z;
			}
			Vector3 CrossProduct(const Vector3 & v3){
				return Vector3(y * v3.z - z * v3.y ,z * v3.x - x * v3.z , x * v3.y - y * v3.x );
			}
			Vector3 operator / (float m){
				return Vector3(x / m,y / m, z / m);
			}
			Vector3 & operator /= (float m){
				x /= m; y /= m; z /= m;
				return (* this);
			}
			bool operator == (const Vector3 &v3){
				if (equalsf(x,v3.x) && equalsf(y,v3.y) && equalsf(z,v3.z) )
					return true;
				return false;
			}
			bool operator != (const Vector3 & v3){
				return !((*this) == v3);
			}
			bool operator < (const Vector3 & v3){
				return (x < v3.x && y < v3.y && z < v3.z);
			}
			bool operator > (const Vector3 & v3){
				return (x > v3.x && y > v3.y && z > v3.z);
			}
			bool operator <= (const Vector3 & v3){
				return (x <= v3.x && y <= v3.y && z <= v3.z);
			}
			bool operator >= (const Vector3 & v3){
				return (x >= v3.x && y >= v3.y && z >= v3.z);
			}
			float GetAbsoluteValue3D(){
				return (float)sqrt (x * x + y * y + z * z);
			}
			float GetAbsoluteValue3DSquare(){
				return (x * x + y * y + z *z);
			}
			float GetDistanceFrom(const Vector3 & v3){
				float dx = x - v3.x;
				float dy = y - v3.y;
				float dz = z - v3.z;
				return (float)sqrt(x * x + y * y + z *z);
			}
			float GetDistanceFromSquare(const Vector3 & v3){
				float dx = x - v3.x;
				float dy = y - v3.y;
				float dz = z - v3.z;
				return (x * x + y * y + z *z);
			}
			float GetAngleXY(){
				return (float)atan2 (y,x); // arctan (y/x)
			}
			float GetAngleXZ(){
				return (float)atan2(z,x); // arctan (z/x)
			}
			float GetAngleYZ(){
				return (float)atan2(z,y); // arctan (z/y)
			}
			Vector3 & Normalize3D(){
				float len = GetAbsoluteValue3D();
				if (equalsf(len,0.0f)) return (*this);
				len = (float)1.0 / len ;
				x *= len; y *= len; z *=len;
				return (*this);
			}
			void SetLength3D (float length){
				Normalize3D();
				(*this) *= length;
			}
		public :
			union 
			{
				float v[3];
				struct 
				{
					float x,y,z;
				};
			};
		};
	}
}
//------------------------------------------------------------------------