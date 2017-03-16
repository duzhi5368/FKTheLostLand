/**
*	created:		2013-4-19   0:06
*	filename: 		TimeSystem
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "StdAfx.h"
#include ".\timesystem.h"
#include ".\gameworld.h"
//------------------------------------------------------------------------
CTimeSystem::CTimeSystem(void)
{
	m_tmrUpdate.Savetime();
	m_startupTime = CSystemTime();
	m_xTimeEventObjectQueue.create( 64 );
	m_wTime = m_startupTime.GetHour() * 4 + m_startupTime.GetMinute() / 15;
}
//------------------------------------------------------------------------
CTimeSystem::~CTimeSystem(void)
{
}
//------------------------------------------------------------------------
VOID CTimeSystem::Update()
{
	if( m_tmrUpdate.IsTimeOut( 60000 ) )
	{
		m_tmrUpdate.Savetime();
		CSystemTime stOld = m_curTime;
		m_curTime = CSystemTime();
		if( stOld.GetYear() != m_curTime.GetYear() )
			OnYearChange();
		if( stOld.GetMonth() != m_curTime.GetMonth() )
			OnMonthChange();
		if( stOld.GetDay() != m_curTime.GetDay() )
			OnDayChange();
		if( stOld.GetHour() != m_curTime.GetHour() )
			OnHourChange();
		if( stOld.GetMinute() != m_curTime.GetMinute() )
			OnMinuteChange();
	}
}
//------------------------------------------------------------------------
BOOL	CTimeSystem::RegisterTimeEvent( CTimeEventObject * pTimeEvent )
{
	if( pTimeEvent == NULL )return FALSE;
	if( this->m_xTimeEventObjectQueue.push( pTimeEvent ) )
		return TRUE;
	return FALSE;
}
//------------------------------------------------------------------------
VOID CTimeSystem::OnMinuteChange()
{
	int count = m_xTimeEventObjectQueue.getcount();
	CTimeEventObject * pEventObject = NULL;
	for( int i = 0;i < count;i ++ )
	{
		pEventObject = m_xTimeEventObjectQueue.pop();
		if( pEventObject == NULL )continue;
		pEventObject->OnMinuteChange( m_curTime );
		m_xTimeEventObjectQueue.push( pEventObject );
	}
}
//------------------------------------------------------------------------
VOID CTimeSystem::OnHourChange()
{
	int count = m_xTimeEventObjectQueue.getcount();
	CTimeEventObject * pEventObject = NULL;
	for( int i = 0;i < count;i ++ )
	{
		pEventObject = m_xTimeEventObjectQueue.pop();
		if( pEventObject == NULL )continue;
		pEventObject->OnHourChange( m_curTime );
		m_xTimeEventObjectQueue.push( pEventObject );
	}
}
//------------------------------------------------------------------------
VOID CTimeSystem::OnDayChange()
{
	int count = m_xTimeEventObjectQueue.getcount();
	CTimeEventObject * pEventObject = NULL;
	for( int i = 0;i < count;i ++ )
	{
		pEventObject = m_xTimeEventObjectQueue.pop();
		if( pEventObject == NULL )continue;
		pEventObject->OnDayChange( m_curTime );
		m_xTimeEventObjectQueue.push( pEventObject );
	}
}
//------------------------------------------------------------------------
VOID CTimeSystem::OnMonthChange()
{
	int count = m_xTimeEventObjectQueue.getcount();
	CTimeEventObject * pEventObject = NULL;
	for( int i = 0;i < count;i ++ )
	{
		pEventObject = m_xTimeEventObjectQueue.pop();
		if( pEventObject == NULL )continue;
		pEventObject->OnMonthChange( m_curTime );
		m_xTimeEventObjectQueue.push( pEventObject );
	}
}
//------------------------------------------------------------------------
VOID CTimeSystem::OnYearChange()
{
	int count = m_xTimeEventObjectQueue.getcount();
	CTimeEventObject * pEventObject = NULL;
	for( int i = 0;i < count;i ++ )
	{
		pEventObject = m_xTimeEventObjectQueue.pop();
		if( pEventObject == NULL )continue;
		pEventObject->OnYearChange( m_curTime );
		m_xTimeEventObjectQueue.push( pEventObject );
	}
}
//------------------------------------------------------------------------