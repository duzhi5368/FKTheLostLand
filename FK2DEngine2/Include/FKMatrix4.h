/**
*	created:		2013-4-23   14:35
*	filename: 		FKMatrix4
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <cmath>
#include <memory.h>
#include "FKVector4.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		 /*  使用DX的矩阵定义，未使用openGL的矩阵定义
						0  1  2  3
						4  5  6  7
		(x,y,z,h)		8  9  10 11  = (x1,y1,z1,h1)
						12 13 14 15					*/
	   class Matrix4
	   {
	   public:
		   Matrix4(){}
		   Matrix4(float m00,float m01,float m02,float m03,
				   float m10,float m11,float m12,float m13,
				   float m20,float m21,float m22,float m23,
				   float m30,float m31,float m32,float m33)
				   :a00(m00),a01(m01),a02(m02),a03(m03),
					a10(m10),a11(m11),a12(m12),a13(m13),
					a20(m20),a21(m21),a22(m22),a23(m23),
					a30(m30),a31(m31),a32(m32),a33(m33){}
		   // virtual ~Matrix4(){}
		   void SetValue(float m00,float m01,float m02,float m03,
						 float m10,float m11,float m12,float m13,
						 float m20,float m21,float m22,float m23,
						 float m30,float m31,float m32,float m33)
		   {
			   a00 = m00 ; a01 = m01; a02 = m02; a03 = m03;
			   a10 = m10 ; a11 = m11; a12 = m12; a13 = m13; 
			   a20 = m20 ; a21 = m21; a22 = m22; a23 = m23;
			   a30 = m30 ; a31 = m31; a32 = m32; a33 = m33;
		   }
		   float & operator ()(int row,int col){
			   return a[row * 4 + col];
		   }
		   Matrix4 & operator = (const Matrix4 & m4){
			   memcpy(this,&m4,16 * sizeof(float));
			   return (*this);
		   }
		   Matrix4 operator - (){
			   return Matrix4(-a00,-a01,-a02,-a03,
							  -a10,-a11,-a12,-a13,
							  -a20,-a21,-a22,-a23,
							  -a30,-a31,-a32,-a33);
		   }
		   Matrix4 & operator +=(const Matrix4 & m4){
			   int index;
			   for (index = 0; index <16; index ++)
				   a[index] += m4.a[index];
			   return (*this);
		   }
		   Matrix4 operator +(const Matrix4 & m4){
			   Matrix4 c;
			   int index;
			   for (index = 0; index < 16; index ++)
				   c.a[index] = a[index] + m4.a[index];
			   return c;
		   }
		   Matrix4 & operator -= (const Matrix4 & m4){
			   int index;
			   for (index = 0; index < 16; index ++)
				   a[index] -= m4.a[index];
			   return (*this);
		   }
		   Matrix4 operator - (const Matrix4 & m4){
			   Matrix4 c;
			   int index;
			   for (index = 0; index < 16; index ++)
				   c.a[index] = a[index] - m4.a[index];
			   return c;
		   }
		   // 这个函数用的很多，不推荐使用循环指令实现
		   /* 0  1  2  3
			  4  5  6  7
			  8  9  10 11
			  12 13 14 15 */
		   Matrix4 operator *(const Matrix4 & m4)
		   {
			   Matrix4 c;
			   c.a[0] = a[0] * m4.a[0] + a[1] * m4.a[4] + a[2] * m4.a[8] + a[3] * m4.a[12];
			   c.a[1] = a[0] * m4.a[1] + a[1] * m4.a[5] + a[2] * m4.a[9] + a[3] * m4.a[13];
			   c.a[2] = a[0] * m4.a[2] + a[1] * m4.a[6] + a[2] * m4.a[10] + a[3] * m4.a[14];
			   c.a[3] = a[0] * m4.a[3] + a[1] * m4.a[7] + a[2] * m4.a[11] + a[3] * m4.a[15];

			   c.a[4] = a[4] * m4.a[0] + a[5] * m4.a[4] + a[6] * m4.a[8] + a[7] * m4.a[12];
			   c.a[5] = a[4] * m4.a[1] + a[5] * m4.a[5] + a[6] * m4.a[9] + a[7] * m4.a[13];
			   c.a[6] = a[4] * m4.a[2] + a[5] * m4.a[6] + a[6] * m4.a[10] + a[7] * m4.a[14];
			   c.a[7] = a[4] * m4.a[3] + a[5] * m4.a[7] + a[6] * m4.a[11] + a[7] * m4.a[15];

			   c.a[8] = a[8] * m4.a[0] + a[9] * m4.a[4] + a[10] * m4.a[8] + a[11] * m4.a[12];
			   c.a[9] = a[8] * m4.a[1] + a[9] * m4.a[5] + a[10] * m4.a[9] + a[11] * m4.a[13];
			   c.a[10] = a[8] * m4.a[2] + a[9] * m4.a[6] + a[10] * m4.a[10] + a[11] * m4.a[14];
			   c.a[11] = a[8] * m4.a[3] + a[9] * m4.a[7] + a[10] * m4.a[11] + a[11] * m4.a[15];

			   c.a[12] = a[12] * m4.a[0] + a[13] * m4.a[4] + a[14] * m4.a[8] + a[15] * m4.a[12];
			   c.a[13] = a[12] * m4.a[1] + a[13] * m4.a[5] + a[14] * m4.a[9] + a[15] * m4.a[13];
			   c.a[14] = a[12] * m4.a[2] + a[13] * m4.a[6] + a[14] * m4.a[10] + a[15] * m4.a[14];
			   c.a[15] = a[12] * m4.a[3] + a[13] * m4.a[7] + a[14] * m4.a[11] + a[15] * m4.a[15];
			   return c;
		   }
		   Matrix4 & operator *=(const Matrix4 & m4){
			   (*this) = (*this) * m4;
			   return (*this);
		   }
		   Matrix4 & MakeIdentity(){
			   SetValue(1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						0,0,0,1);
			   return (*this);
		   }
		   
		   // 基本矩阵操作函数
		   Matrix4 & MakeTranslation(float dx,float dy,float dz){
			   SetValue(1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						dx,dy,dz,1);
			   return (*this);
		   }
		   Matrix4 & MakeRotationXYPlane(float angle){
			   float sina = (float)sin(angle);
			   float cosa = (float)cos(angle);
			   SetValue(cosa,sina,0,0,
						-sina,cosa,0,0,
						0,0,1,0,
						0,0,0,1);
			   return (*this);
		   }
		   Matrix4 & MakeRotationXZPlane(float angle){
			   float sina = (float)sin(angle);
			   float cosa = (float)cos(angle);
			   SetValue(cosa,0,sina,0,
						0, 1,0,0,
						-sina ,0,cosa,0,
						0,0,0,1);
			   return (*this);
		   }
		   Matrix4 & MakeRotationYZPlane(float angle){
			   float sina = (float)sin(angle);
			   float cosa = (float)cos(angle);
			   SetValue(1,0,0,0,
						0,cosa,sina,0,
						0,-sina,cosa,0,
						0,0,0,1);
			   return (*this);
		   }
		   Matrix4 & MakeRotation(Vector3 & v3){
			   float sx = (float)sin (v3.x);
			   float cx = (float)cos (v3.x);
			   float sy = (float)sin (v3.y);
			   float cy = (float)cos (v3.y);
			   float sz = (float)sin (v3.z);
			   float cz = (float)cos (v3.z);
			   
			   SetValue(cy * cz ,cy * sz,-sy,0,
						sx*sy*cz-cx*sz ,sx*sy*sz+cx*cz,sx*cy,0,
						cx*sy*cz+sx*sz ,cx*sy*sz-sx*cz,cx*cy,0,
						0,0,0,1);
			   return (*this);
		   }
		   Matrix4 & MakeScaling(float sx,float sy,float sz){
			   SetValue(sx,0,0,0,
						0,sy,0,0,
						0,0,sz,0,
						0,0,0,1);
			   return (*this);
		   }

		   // World矩阵转为View视图矩阵
		   Matrix4 & MakeLookAtLeftHand(Vector3 & eye, Vector3 & at,Vector3 & up){
			   Vector3 zaxis = (at - eye).Normalize3D();
			   Vector3 xaxis = (up.CrossProduct(zaxis)).Normalize3D();
			   Vector3 yaxis = zaxis.CrossProduct(xaxis);
			   SetValue(xaxis.x ,yaxis.x ,zaxis.x ,0,
						xaxis.y ,yaxis.y, zaxis.y ,0,
						xaxis.z ,yaxis.z,zaxis.z , 0,
						-eye.DotProduct(xaxis),-eye.DotProduct(yaxis),-eye.DotProduct(zaxis),1);
			   return (*this);
		   }
		   Matrix4 & MakeLookAtRightHand(Vector3 & eye ,Vector3 & at,Vector3 & up){
			   Vector3 zaxis = (eye -at).Normalize3D();
			   Vector3 xaxis = (up.CrossProduct(zaxis)).Normalize3D();
			   Vector3 yaxis = zaxis.CrossProduct(xaxis);
			   SetValue(xaxis.x ,yaxis.x ,zaxis.x ,0,
						xaxis.y ,yaxis.y, zaxis.y ,0,
						xaxis.z ,yaxis.z,zaxis.z , 0,
						-eye.DotProduct(xaxis),-eye.DotProduct(yaxis),-eye.DotProduct(zaxis),1);
			   return (*this);
		   }

		   // view矩阵转为projection投影矩阵
		   // x : 0 - width y : 0 - height z : - depth - depth
		   // to x : -1.0 - 1.0 y : -1.0 - 1.0 z : -1.0 - 1.0
		   Matrix4 & Make2DProjection(float width,float height,float depth){
			   float a = width / 2; 
			   float b = height / 2;
			   Matrix4 translation ; 
			   translation.MakeTranslation( -a,-b,0);
			   Matrix4 scale ;
			   scale.MakeScaling(1/a,-1/b,1/depth);
			   (*this) = translation * scale ;
			   return (*this);
		   }
		   Matrix4 & MakeOrthoLeftHand(float w , float h ,float zn, float zf){
			   if (equalsf(zn,zf)) {
				   zn= 1.0f; zf = 1000.0f;
			   }
			   SetValue(2 / w,0,0,0,
						0,2/h,0,0,
						0,0,1/(zf - zn),0,
						0,0,zn / (zn - zf),1);
			   return (*this);
		   }
		   Matrix4 & MakeOrthoRightHand(float w, float h ,float zn ,float zf){
				if (equalsf(zn,zf)) {
				   zn= 1.0f; zf = 1000.0f;
			   }
				SetValue(2 / w, 0,0,0,
						 0,2 / h, 0,0,
						 0,0,1 / (zn -zf),0,
						 0,0,zn / (zn - zf), 1);
				return (*this);
		   }
		   Matrix4 & MakePerspectiveLeftHand(float w,float h,float zn,float zf){
			   if (equalsf(zn,zf)) {
				   zn= 1.0f; zf = 1000.0f;
			   }
			   SetValue( 2* zn / w, 0,0,0,
						0,2 * zn /h,0,0,
						0,0,zf / (zf - zn),1,
						0,0,zn * zf / (zn - zf),0);
			   return (*this);
		   }
		   Matrix4 & MakePerspectiveRightHand(float w,float h,float zn,float zf){
			   if (equalsf(zn,zf)){
				   zn = 1.0f;  zf = 1000.0f;
			   }
			   SetValue(2 * zn /w , 0,0,0,
						0,2 * zn / h,0,0,
						0,0,zf / (zn - zf),-1,
						0,0,zn * zf / (zn - zf),0);
			   return (*this);
		   }
		   Matrix4 & MakePerspectiveFovLeftHand(float fovy,float aspect,float zn,float zf){
			   if (equalsf(zn,zf)){
				   zn = 1.0f;  zf = 1000.0f;
			   }
				float h = 1.0f/ (float)tan(fovy / 2);
				float w = h / aspect;
				SetValue(w,0,0,0,
						 0,h,0,0,
						 0,0,zf / (zf - zn),1,
						 0,0,zn * zf /(zn - zf),0 );
				return (*this);
		   }
		   Matrix4 & MakePerspectiveFovRightHand(float fovy , float aspect,float zn,float zf){
			   if (equalsf(zn,zf)){
				   zn = 1.0f;  zf = 1000.0f;
			   }
			   float h = 1.0f / (float )tan (fovy / 2);
			   float w = h / aspect ;
			   SetValue(w,0,0,0,
						0,h,0,0,
						0,0,zf / (zn - zf),-1,
						0,0,zn * zf / (zn -zf),0);
			   return (*this);
		   }
		   /* (x,y,z,1) 0 1 2 3
						4 5 6 7
						8 9 10 11
						12 13 14 15
		  */
		   Vector3 & MultiplyVector3(Vector3 & v3){
			   Vector3 vt;
			   vt.x = v3.x * a[0] + v3.y * a[4] + v3.z * a[8] + a[12];
			   vt.y = v3.x * a[1] + v3.y * a[5] + v3.z * a[9] + a[13];
			   vt.z = v3.x * a[2] + v3.y * a[6] + v3.z * a[10] + a[14];
			   v3 = vt;
			   return v3;
		   }
			/* (x,y,z,w) 0 1 2 3
						4 5 6 7
						8 9 10 11
						12 13 14 15
		  */
		   Vector4 & MultiplyVector4(Vector4 & v4){
			   Vector4 vt;
			   vt.x = v4.x * a[0] + v4.y * a[4] + v4.z * a[8] + v4.w * a[12];
			   vt.y = v4.x * a[1] + v4.y * a[5] + v4.z * a[9] + v4.w * a[13];
			   vt.z = v4.x * a[2] + v4.y * a[6] + v4.z * a[10] + v4.w * a[14];
			   vt.w = v4.x * a[3] + v4.y * a[7] + v4.z * a[11] + v4.w * a[15];
			   v4 = vt;
			   return v4;
		   }
	   public:
		   union 
		   {
			   struct 
			   {
				   float a00,a01,a02,a03;
				   float a10,a11,a12,a13;
				   float a20,a21,a22,a23;
				   float a30,a31,a32,a33;
			   };
			   float a[16];
		   };
	   };
   }
}
//------------------------------------------------------------------------