/**
*	created:		2013-5-3   17:50
*	filename: 		FKSingleton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
template <class T>
class TSingletonClass
{
public:
	TSingletonClass()
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
//------------------------------------------------------------------------
template <class T>
T * TSingletonClass<T>::m_pInstance = (T*)NULL;
//------------------------------------------------------------------------