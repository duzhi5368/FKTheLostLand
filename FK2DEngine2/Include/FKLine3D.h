/**
*	created:		2013-4-23   14:26
*	filename: 		FKLine3D
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <cmath>
#include "FKVector3.h"
#include "FKVertex.h"
#include "FKMatrix4.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		class Line3D
		{
		public:
			Line3D() : start(0,0,0) ,end(1,1,1){}
			Line3D(const Vector3 & mstart,const Vector3 & mend) : start(mstart),end(mend){}
			Line3D(float x1,float y1,float z1,float x2,float y2,float z2):start(x1,y1,z1),end(x2,y2,z2){}
			Line3D(const Line3D & l3) : start(l3.start) ,end(l3.end){}
			// virtual ~Line3D(){}
			void SetValue(const Vector3 & mstart,const Vector3 & mend){
				start = mstart; end = mend;
			}
			void SetValue(float x1,float y1,float z1,float x2,float y2,float z2){
				start.SetValue(x1,y1,z1); end.SetValue(x2,y2,z2);
			}
			// ²Ù×÷·ûÖØÔØ
			Line3D & operator = (const Line3D & l3){
				start = l3.start; end = l3.end;
				return (*this);
			}
			Line3D operator - (){
				return Line3D(-start,-end);
			}
			Line3D operator + (const Line3D & l3){
				return Line3D (start + l3.start ,end + l3.end );
			}
			Line3D operator + (const Vector3 & v3){
				return Line3D (start + v3, end + v3);
			}
			Line3D & operator += (const Vector3 & v3){
				start += v3; end += v3;
				return (*this);
			}
			Line3D & operator += (const Line3D & l3){
				start += l3.start ;end += l3.end;
				return (*this);
			}
			Line3D operator - (const Vector3 & v3){
				return Line3D (start - v3, end - v3);
			}
			Line3D operator - (const Line3D & l3){
				return Line3D (start - l3.start ,end - l3.end );
			}
			Line3D & operator -= (const Vector3 & v3){
				start -= v3; end -= v3;
				return (*this);
			}
			Line3D & operator -= (const Line3D & l3){
				start -= l3.start ;end -= l3.end ;
				return (*this);
			}
			bool operator == (const Line3D & l3){
				if (start == l3.start && end == l3.end )
					return true;
				return false;
			}
			bool operator != (const Line3D & l3){
				return !((*this) == l3);
			}
			float Getlength(){
				return start.GetDistanceFrom(end);
			}
			float GetLengthSquare(){
				return start.GetDistanceFromSquare(end);
			}
			Vector3 GetMiddle(){
				return (start + end) / (float) 0.5;
			}
			Vector3 GetVector(){
				return end - start;
			}
			Vector3 GetClosestPoint(Vector3 & point){
				Vector3 lv = end - start;
				Vector3 sp = point - start;
				float d = lv.GetAbsoluteValue3D();
				lv /= d;
				float length = lv.DotProduct(sp);
				if (length <= (float) 0.0)
					return start;
				else if (length >= d)
					return end;
				return (start + lv * length);
			}
			float GetDistanceFromPoint(Vector3 & point){
				Vector3 closest = GetClosestPoint(point);
				Vector3 dis = closest - point;
				return dis.GetAbsoluteValue3D();
			}
			void Transform(Matrix4 & m4)
			{
				m4.MultiplyVector3(start);
				m4.MultiplyVector3(end);
			}
		public:
			Vertex start,end;
		};
	}
}
//------------------------------------------------------------------------