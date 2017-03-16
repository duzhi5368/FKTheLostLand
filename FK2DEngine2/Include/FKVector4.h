/**
*	created:		2013-4-23   15:00
*	filename: 		FKVector4
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <cmath>
#include "FKVector3.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{

		class Vector4 : public Vector3
		{
			public:
				Vector4 () : w(0){}
				Vector4 (float mx,float my,float mz,float mw) : Vector3(mx,my,mz) , w(mw) {}
				Vector4 (const Vector4 & v4) : Vector3(v4.x,v4.y,v4.z) , w(v4.w){}
				//virtual ~Vector4(){}
				void SetValue(float mx,float my,float mz,float mw){
					x = mx; y = my; z = mz; w = mw;
				}
				Vector4 & operator = (const Vector4 & v4){
					x = v4.x ; y = v4.y; z = v4.z ; w = v4.w;
					return (*this);
				}
				Vector4 & operator = (const Vector3 & v3){
					x = v3.x; y = v3.y; z = v3.z;
					return (*this);
				}
				Vector4 operator - (){
					return Vector4 (-x,-y,-z,-w);
				}
				Vector4 operator + (const Vector4 & v4){
					return Vector4(x + v4.x,y + v4.y ,z + v4.z,w + v4.w);
				}
				Vector4 & operator += (const Vector4 & v4){
					x += v4.x ; y+= v4.y ; z += v4.z; w += v4.w;
					return (*this);
				}
				Vector4 operator - (const Vector4 & v4){
					return Vector4 (x - v4.x, y - v4.y, z - v4.z,w - v4.w);
				}
				Vector4 & operator -= (const Vector4 & v4){
					x -= v4.x; y -= v4.y; z -= v4.z; w -= v4.w;
					return (*this);
				}
				Vector4 operator * (float m){
					return Vector4(x * m ,y *m ,z *m ,w *m);
				}
				Vector4 & operator *= (float m){
					x *= m ; y *= m; z *= m; w *= m;
					return (*this);
				}
				Vector4 operator / (float m){
					return Vector4(x / m,y / m, z / m,w /m );
				}
				Vector4 & operator /= (float m){
					x /= m; y /= m; z /= m; w/= m;
					return (*this);
				}
				bool operator == (const Vector4 & v4){
					if (equalsf(x,v4.x) && equalsf(y,v4.y) && equalsf(z,v4.z) && equalsf(w,v4.w))
						return true;
					return false;
				}
				bool operator != (const Vector4 & v4){
					return !( (*this) == v4);
				}
			public:
				float w;
		};
	}
}
//------------------------------------------------------------------------