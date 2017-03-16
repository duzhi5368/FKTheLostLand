/**
*	created:		2013-4-23   14:59
*	filename: 		FKTriangle
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKVector3.h"
#include "FKMatrix4.h"
#include "FKPlane.h"
#include "FKVertex.h"
//------------------------------------------------------------------------
namespace FK2DEngine2 
{
	namespace math
	{
		class Triangle
		{
		public:
			Triangle():v0(0,0,0),v1(0,0,0),v2(0,0,0){}
			Triangle(const Vector3 & mv0,const Vector3 & mv1,const Vector3 &mv2):v0(mv0),v1(mv1),v2(mv2){}
			Triangle(float x0,float y0,float z0,
					 float x1,float y1,float z1,
					 float x2,float y2,float z2):v0(x0,y0,z0),v1(x1,y1,z1),v2(x2,y2,z2){}
			void SetValue(const Vector3 & mv0, const Vector3 & mv1,const Vector3 & mv2){
				v0 = mv0; v1 = mv1; v2 = mv2;
			}
			void SetValue(float x0,float y0,float z0,
						  float x1,float y1,float z1,
						  float x2,float y2,float z2){
				v0.x = x0; v0.y = y0; v0.z = z0;
				v1.x = x1; v1.y = y1; v1.z = z1;
				v2.x = x2; v2.y = y2; v2.z = z2;
			}
			bool operator == (const Triangle & t){
				if (v0 == t.v0 && v1 == t.v1 && v2 == t.v2)
					return true;
				return false;
			}
			bool operator != (const Triangle & t){
				return !((*this) == t);
			}
			Plane GetPlane(){
				return Plane(v0,v1,v2);
			}
			Vector3 GetNormalVector(){
				return (GetPlane().normal);
			}
			Vector3 GetCenter(){
				return (v0 + v1 + v2) / 3.0;
			}
			void Transform(Matrix4 & m4){
				m4.MultiplyVector3(v0);
				m4.MultiplyVector3(v1);
				m4.MultiplyVector3(v2);
			}
		public:				
			Vertex v0,v1,v2;
		};
	}
}
//------------------------------------------------------------------------