/**
*	created:		2013-4-23   15:03
*	filename: 		FKVertex
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKMathMacro.h"
#include "FKVector3.h"
#include "FKVector4.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		// 使用DX顶点格式 D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1
		class Vertex : public Vector3
		{
		public:
			Vertex(): color(0xff000000),tx(0.0),ty(0.0){}
			Vertex(float x,float y,float z):Vector3(x,y,z),color(0xff000000),tx(0.0),ty(0.0){}
			Vertex(float x,float y,float z,DWORD mcolor,float mtx,float mty):Vector3(x,y,z),color(mcolor),tx(mtx),ty(mty){}
			Vertex(const Vector3 & v3) :Vector3(v3),color(0xff000000),tx(0.0),ty(0.0){}
			//Vertex(const Vertex & v):Vector3(v.x ,v.y,v.z),color(v.color),tx(v.tx),ty(v.ty){}
			void SetValue(float mx,float my,float mz){
				x = mx; y = my; z = mz;
			}
			void SetValue(float mx,float my,float mz,DWORD mcolor,float mtx,float mty){
				x = mx; y = my; z= mz; color = mcolor; tx= mtx; ty= mty;
			}
			void SetValue(float mx,float my,float mz,float norx,float nory,float norz,DWORD mcolor,float mtx,float mty){
				x = mx; y = my; z = mz; 
				normal.x = norx; normal.y = nory; normal.z = norz;
				color = mcolor; tx = mtx; ty = mty;
			}
			operator Vector3 & (){
				return (* ((Vector3 *)this) );
			}
		public:
			Vector3 normal;
			DWORD color;
			float tx,ty;
		};
	}
}
//------------------------------------------------------------------------