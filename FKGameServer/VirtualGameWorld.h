/**
*	created:		2013-4-19   0:09
*	filename: 		VirtualGameWorld
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CVirtualObject;
//------------------------------------------------------------------------
class CVirtualGameWorld
{
public:
	virtual BOOL AddObject(CVirtualObject * pObject ) = 0;
	virtual BOOL DelObject(CVirtualObject * pObject ) = 0;
	virtual CVirtualObject * GetObject( UINT nObjectId ) = 0;
	virtual CVirtualObject * NewObject() = 0;
	virtual BOOL DelObject(CVirtualObject * pObject ) = 0;
};
//------------------------------------------------------------------------