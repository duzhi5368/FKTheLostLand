/**
*	created:		2013-4-16   4:21
*	filename: 		xSingleton
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
template <class T>
class xSingletonClass
{
public:
	xSingletonClass()
	{
		m_pInstance = (T*)this;
	}
	static T * GetInstance()
	{
		if( m_pInstance == NULL )
			m_pInstance = new T;
		return m_pInstance;
	}
protected:
	static T* m_pInstance;
};
template <class T>
T * xSingletonClass<T>::m_pInstance = (T*)NULL;
//------------------------------------------------------------------------