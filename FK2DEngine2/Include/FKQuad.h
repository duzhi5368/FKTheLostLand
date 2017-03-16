/**
*	created:		2013-4-23   14:57
*	filename: 		FKQuad
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKVector3.h"
#include "FKMatrix4.h"
#include "FKVertex.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		/*
			v0 ---- v1
			|        |
			|        |
			v2 ---- v3
		*/
		class Quad
		{
		public:
			Quad():v0(0,0,0),v1(0,0,0),v2(0,0,0),v3(0,0,0){}
			Quad(const Vector3 & mv0, const Vector3 & mv1,const Vector3 & mv2,const Vector3 &mv3)
				: v0(mv0),v1(mv1),v2(mv2),v3(mv3){}
			Quad(float x0,float y0,float z0,
				 float x1,float y1,float z1,
				 float x2,float y2,float z2,
				 float x3,float y3,float z3):v0(x0,y0,z0),v1(x1,y1,z1),v2(x2,y2,z2),v3(x3,y3,z3){}
			void SetValue(const Vector3 & mv0, const Vector3 & mv1,const Vector3 & mv2,const Vector3 & mv3){
				v0 = mv0; v1= mv1; v2 = mv2; v3 = mv3;
			}
			void SetValue(float x0,float y0,float z0,
						  float x1,float y1,float z1,
						  float x2,float y2,float z2,
						  float x3,float y3,float z3){
				v0.x = x0; v0.y = y0; v0.z = z0;
				v1.x = x1; v1.y = y1; v1.z = z1;
				v2.x = x2; v2.y = y2; v2.z = z2;
				v3.x = x3; v3.y = y3; v3.z = z3;
			}
			bool operator == (const Quad & q){
				if (v0 == q.v0 && v1 == q.v1 && v2 == q.v2 && v3 == q.v3)
					return true;
				return false;
			}
			bool operator != (const Quad & q){
				return !((*this) == q);
			}
			Vector3 GetCenter(){
				return (v0 + v1 + v2 + v3) / 4.0;
			}
			void Transform(Matrix4 & m4){
				m4.MultiplyVector3(v0);
				m4.MultiplyVector3(v1);
				m4.MultiplyVector3(v2);
				m4.MultiplyVector3(v3);
			}
		public:
			Vertex v0,v1,v2,v3;
		};
	}
}
//------------------------------------------------------------------------