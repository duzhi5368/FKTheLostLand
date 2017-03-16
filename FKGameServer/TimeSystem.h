/**
*	created:		2013-4-19   0:05
*	filename: 		TimeSystem
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
class CTimeEventObject
{
public:
	virtual VOID OnMinuteChange( CSystemTime & curTime ){}
	virtual VOID OnHourChange( CSystemTime & curTime ){}
	virtual VOID OnDayChange( CSystemTime & curTime ){}
	virtual VOID OnMonthChange( CSystemTime & curTime ){}
	virtual VOID OnYearChange( CSystemTime & curTime ){}
};
//------------------------------------------------------------------------
class CTimeSystem:
	public xSingletonClass<CTimeSystem>
{
public:
	CTimeSystem(void);
	virtual ~CTimeSystem(void);
	VOID	Update();
	BOOL	RegisterTimeEvent( CTimeEventObject * pTimeEvent );
	WORD	GetCurrentTime(){ return m_wTime;}
protected:
	VOID 	OnMinuteChange();
	VOID 	OnHourChange();
	VOID 	OnDayChange();
	VOID 	OnMonthChange();
	VOID 	OnYearChange();
private:
	CServerTimer m_tmrUpdate;
	CSystemTime m_curTime;
	CSystemTime m_startupTime;
	xPtrQueue<CTimeEventObject> m_xTimeEventObjectQueue;
	WORD m_wTime;
};
//------------------------------------------------------------------------