/**
*	created:		2013-4-27   20:30
*	filename: 		FKTraceMutex
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CTraceMutex
{
public:
	CTraceMutex()
	{
		m_hObject = NULL;
	}
	~CTraceMutex(){::CloseHandle(m_hObject);}
	BOOL Create()
	{
		m_hObject = ::CreateMutex(NULL, FALSE, NULL);
		return m_hObject != NULL;
	}
	BOOL Lock(DWORD dwTimeout = INFINITE)
	{
		if (m_hObject == NULL)
			return FALSE;

		if (::WaitForSingleObject(m_hObject, dwTimeout) == WAIT_OBJECT_0)
			return TRUE;
		else
			return FALSE;
	}
	BOOL Unlock()
	{
		if (m_hObject == NULL)
			return FALSE;
		return ::ReleaseMutex(m_hObject);
	}
public:
	HANDLE m_hObject;
};
//------------------------------------------------------------------------