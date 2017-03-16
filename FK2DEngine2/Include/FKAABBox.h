/**
*	created:		2013-4-23   15:05
*	filename: 		FKAABBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKVector3.h"
#include "FKLine3D.h"
#include "FKTriangle.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace math
	{
		class Aabbox
		{
		public:
			Aabbox()
				:minPoint(0,0,0),maxPoint(0,0,0){}
			Aabbox(Vector3 minPoint_,Vector3 maxPoint_)
				:minPoint(minPoint_),maxPoint(maxPoint_){
				repair();
			}
			Aabbox(float minX,float minY,float minZ,float maxX,float maxY,float maxZ)
				:minPoint(minX,minY,minZ),maxPoint(maxX,maxY,maxZ){
				repair();
			}

			void setValue (Vector3 & minPoint_,Vector3 & maxPoint_){
				minPoint = minPoint_; maxPoint = maxPoint_;
				repair();
			}
			void setValue(float minX,float minY,float minZ,float maxX,float maxY,float maxZ){
				minPoint.x = minX; minPoint.y = minY; minPoint.z = minZ;
				maxPoint.x = maxX; maxPoint.y = maxY; maxPoint.z = maxZ;
				repair();
			}
			
			bool operator == (const Aabbox & aabb) {
				return (minPoint == aabb.minPoint && maxPoint == aabb.maxPoint);
			}
			bool operator != (const Aabbox & aabb){
				return !((*this) == aabb);
			}

			void addPoint(Vector3 & point){
				if (point.x < minPoint.x) minPoint.x = point.x;
				if (point.y < minPoint.y) minPoint.y = point.y;
				if (point.z < minPoint.z) minPoint.z = point.z;
				if (point.x > maxPoint.x) maxPoint.x = point.x;
				if (point.y > maxPoint.y) maxPoint.y = point.y;
				if (point.z > maxPoint.z) maxPoint.z = point.z;
			}
			void addLine(Vector3 & start,Vector3 & end){
				addPoint(start);
				addPoint(end);
			}
			void addLine(Line3D & line){
				addPoint(line.start);
				addPoint(line.end);
			}
			void addBox(Aabbox & box){
				addPoint(box.minPoint);
				addPoint(box.maxPoint);
			}
			void addTriangle(Triangle & triangle){
				addPoint(triangle.v0);
				addPoint(triangle.v1);
				addPoint(triangle.v2);
			}
			
			bool isPointinside(Vector3 point){
				if (point.x > minPoint.x && point.x < maxPoint.x
					&& point.y > minPoint.y && point.y < maxPoint.y
					&& point.z > minPoint.z && point.z < maxPoint.z)
					return true;
				return false;
			}
			
			bool intersectWithBox(Aabbox & box){
				if (minPoint <= box.maxPoint && maxPoint >= box.minPoint)
					return true;
				return false;
			}
			
			Vector3 getCenter(){
				return (minPoint + maxPoint) / 2;
			}
			Vector3 getSize(){
				return maxPoint - minPoint;
			}
			
			/*
			front face 
			0  1
			2  3
			back face
			4  5
			6  7
			*/
			Vector3 getPoint(int index){
				Vector3 middle = getCenter();
				Vector3 size = getSize();
				switch (index)
				{
				case 0:
					return Vector3(middle.x - size.x,middle.y + size.y ,middle.z - size.z);
				case 1:
					return Vector3(middle.x + size.x,middle.y + size.y, middle.z - size.z);
				case 2:
					return Vector3(middle.x - size.x ,middle.y - size.y,middle.z - size.z);
				case 3:
					return Vector3(middle.x + size.x ,middle.y - size.y,middle.z - size.z);
				case 4:
					return Vector3(middle.x - size.x,middle.y + size.y ,middle.z + size.z);
				case 5:
					return Vector3(middle.x + size.x,middle.y + size.y, middle.z + size.z);
				case 6:
					return Vector3(middle.x - size.x ,middle.y - size.y,middle.z + size.z);
				case 7:
					return Vector3(middle.x + size.x ,middle.y - size.y,middle.z + size.z);
				}
				return Vector3(0,0,0);
			}
			
			void repair(){
				if (minPoint.x > maxPoint.x) swapf(minPoint.x,maxPoint.x);
				if (minPoint.y > maxPoint.y) swapf(minPoint.y,maxPoint.y);
				if (minPoint.z > maxPoint.z) swapf(minPoint.z,maxPoint.z);
			}
			
		public:
			Vector3 minPoint;
			Vector3 maxPoint;
		};
	}
}
//------------------------------------------------------------------------