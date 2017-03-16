/**
*	created:		2013-4-16   4:41
*	filename: 		xIndexObject
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class xIndexObject
{
public:
	xIndexObject(void)
	{
		Clean();
	}
	UINT getId(){return m_Id;}
	VOID setId( UINT id ){ m_Id = id;}
	virtual VOID Clean()
	{
		m_Id = 0;
	}
private:
	UINT	m_Id;
};
//------------------------------------------------------------------------