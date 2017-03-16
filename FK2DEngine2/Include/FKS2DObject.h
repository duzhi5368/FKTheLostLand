/**
*	created:		2013-4-23   22:04
*	filename: 		FKS2DObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKVertex.h"
#include "FKLine3D.h"
#include "FKTriangle.h"
#include "FKQuad.h"

#include "FKSColor.h"
#include "FKITexture.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace scene
	{
		namespace S2D
		{
			struct S2DTextureObjects
			{
				FK2DEngine2::video::ITexture * texture;
				S2DTextureObjects():texture(NULL){}
			};

			struct S2DPixel : public S2DTextureObjects
			{
				FK2DEngine2::math::Vertex pixel;
			};

			struct S2DLine : public S2DTextureObjects
			{
				FK2DEngine2::math::Line3D line;
			};

			struct S2DTriangle : public S2DTextureObjects
			{
				FK2DEngine2::math::Triangle triangle;
			};

			struct S2DQuad : public S2DTextureObjects
			{
				FK2DEngine2::math::Quad quad;
				void makeRect(float width,float height,float lowTx = 0.0f,float lowTy = 0.0f,float highTx = 1.0f,
					float highTy = 1.0f,FK2DEngine2::video::SColor color = FK2DEngine2::video::SColor::white()){
					//quad.v0.SetValue(- width / 2, -height / 2,0,color.getDwordValue(),lowTx,lowTy);
					//quad.v1.SetValue(width / 2, -height /2 ,0, color.getDwordValue(),highTx,lowTy);
					//quad.v2.SetValue(- width /2,height /2, 0,color.getDwordValue(),lowTx,highTy);
					//quad.v3.SetValue(width /2,height /2,0,color.getDwordValue(),highTx,highTy);
						quad.v0.SetValue(0, 0,0,color.getDwordValue(),lowTx,lowTy);
						quad.v1.SetValue(width, 0 ,0, color.getDwordValue(),highTx,lowTy);
						quad.v2.SetValue(0,height, 0,color.getDwordValue(),lowTx,highTy);
						quad.v3.SetValue(width,height,0,color.getDwordValue(),highTx,highTy);
				}
			};
		}
	}
}
//------------------------------------------------------------------------