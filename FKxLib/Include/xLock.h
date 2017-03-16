/**
*	created:		2013-4-16   1:21
*	filename: 		xLock
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CLockableObject
{
public:
	CLockableObject(){}
	virtual	~CLockableObject(){}
	virtual	void Lock() = 0;
	virtual	void Unlock() = 0;
	virtual	BOOL TryLock() = 0;
};
//------------------------------------------------------------------------
class CriticalSection:public CLockableObject
{
public:
	CriticalSection()
	{
		InitializeCriticalSection( &m_critical_sec );
	};
	~CriticalSection()
	{
		DeleteCriticalSection( &m_critical_sec );
	};
	virtual void Lock()
	{
		EnterCriticalSection( &m_critical_sec );
	}
	virtual void Unlock()
	{
		LeaveCriticalSection( &m_critical_sec );
	}
	virtual BOOL	TryLock()
	{
		return TryEnterCriticalSection(&m_critical_sec );
	}
private:
	CRITICAL_SECTION	m_critical_sec;
};
//------------------------------------------------------------------------
class CLock
{
public:
	CLock(CLockableObject * pLockable)
	{
		m_pLockable = pLockable;
		m_pLockable->Lock();
	}
	~CLock()
	{
		m_pLockable->Unlock();
	}
private:
	CLockableObject * m_pLockable;
};
//------------------------------------------------------------------------
class CriticalSectionLock
{
public:
	CriticalSectionLock( CRITICAL_SECTION*	pCritSect )
	{
		m_pCritSect = pCritSect;
		EnterCriticalSection( pCritSect );
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection( m_pCritSect );
	}
private:
	CRITICAL_SECTION*	m_pCritSect;
};
//------------------------------------------------------------------------
class CriticalSectionProtector
{
public:
	VOID	Lock()
	{
		m_critical_sec.Lock();
	}
	VOID	UnLock()
	{
		m_critical_sec.Unlock();
	}
protected:
	CriticalSection	m_critical_sec;
};
//------------------------------------------------------------------------
#define	THREAD_PROTECT			CLock locker( &m_CriticalSection );
#define	THREAD_PROTECT_DEFINE	CriticalSection	m_CriticalSection;
//------------------------------------------------------------------------