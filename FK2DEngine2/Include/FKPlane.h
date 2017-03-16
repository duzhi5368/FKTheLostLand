/**
*	created:		2013-4-23   14:55
*	filename: 		FKPlane
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <cmath>
#include "FKVector3.h"
#include "FKVector4.h"
#include "FKMatrix4.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		class Plane
		{
		public:
			Plane() : normal(1,0,0),distance(0){}
			Plane(const Vector3 & mnormal,float mdistance):normal(mnormal) ,distance(mdistance){}
			// n * p + d = 0  distance = -d;
			Plane(Vector3 &v1, Vector3 & v2, Vector3 & v3){
				normal = ((v2 - v1).CrossProduct(v3 - v1)).Normalize3D();
				distance = normal.DotProduct(v1);
			}
			// ax + by + cz + d = 0 distance = -d;
			Plane(float a, float b, float c, float d){
				Vector3 n(a,b,c);
				float length = n.GetAbsoluteValue3D();
				d /= length; n /= length;
				normal = n; distance = -d;
			}
			void SetValue(const Vector3 & mnormal,float mdistance){
				normal = mnormal; distance = mdistance;
			}
			void SetValue(Vector3 & v1, Vector3 & v2, Vector3 & v3){
				normal = ((v2 - v1).CrossProduct(v3 - v1)).Normalize3D();
				distance = normal.DotProduct(v1);
			}
			// ax + by + cz + d = 0 distnace = -d;
			void SetValue(float a, float b, float c, float d){
				Vector3 n(a,b,c);
				float length = n.GetAbsoluteValue3D();
				d /= length; n /= length;
				normal = n; distance = -d;
			}
			// n * p + d = 0 在平面上
			// n * p + d > 0 在平面的正面
			// n * p + d < 0 在平面的反面
			// return n * p + d;  distance = -d;
			float DistanceFrom(Vector3 & point){
				float dis = point.DotProduct(normal);
				return (dis - distance);
			}
			void Normalize(){
				float length = normal.GetAbsoluteValue3D();
				normal /= length;
				distance /= length;
			}
			void Transform(Matrix4 & m4){
				Vector4 v4(normal.x,normal.y,normal.z,distance);
				m4.MultiplyVector4(v4);
				normal.x = v4.x; normal.y = v4.y; normal.z = v4.z;
				distance = v4.w;
			}
			
		public:
			// plane : normal * point - distance = 0 
			Vector3 normal;
			float distance;
		};
	}
}
//------------------------------------------------------------------------