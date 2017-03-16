/**
*	created:		2013-5-10   2:04
*	filename: 		FKThreadRoute
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
/*
	线程管理：
		　　一个线程可以同时帮助管理63个外部事件。如可以将通讯事件放到主线程中，
		当通讯事件发生时，将事件通知转给通讯层处理。
			另一个重要用途是定时器服务，不需要经由内核，经由内建定时器队列可以实现不受限制数量的定时器
		定时器服务可以提供良好的状态管理
		
	实现方法：
			将每个事件放到WaitForMultiObject的EventBuf中，当某事件发生时，激活指定的调用

	结构图：
			管理程序 <=> IThreadRoute <=> 外挂模块

			管理程序如一个dialog，或一个service
	
	用途：
			1、将多个通讯ClientSocket挂接到一个线程中；
			2、一个服务器程序可以外挂多个个服务
 */
//------------------------------------------------------------------------
#define INVALID_EVENT_ID		-1
#define VERSION_ThreadRoute		1
//------------------------------------------------------------------------
struct ITrace;
struct IEventSink;
struct ITimerEventSink;
//------------------------------------------------------------------------
struct IThreadRoute
{
	// 线程状态管理
	//------------------------------------------------------------------------
	// 启动线程
	// 可将所有的外挂模块加到IThreadRoute以后，启动线程，也可以在启动的过程中外挂模块将自已的事件动态添加进来
	virtual BOOL Start() = NULL;
	
	// 主程序停止线程,可以指定等待时间dwWaitTick，以毫秒为单位
	// 注意：此接函数只能供主程序调用，ThreadRoute线程本身不能停止自已，
	//		 外挂模块因跟ThreadRoute处于同一线程，所以调用此函数将导致死锁
	virtual BOOL Stop(DWORD dwWaitTime = 3000) = NULL;
	
	// 线程死了没有?
	virtual BOOL IsRunning() = NULL;

	// 获取线程Handler
	virtual HANDLE GetThreadHandle() = NULL;

	// 激活线程
	virtual DWORD ResumeThread() = NULL;

	// 暂停线程
	virtual DWORD SuspendThread () = NULL;

	// 线程事件管理
	//------------------------------------------------------------------------
	/*
	 	功能：外挂模块将自已的一个事件挂接到当前线程中
		输入：
			hEvent		：可是hEvent、socket句柄等
			pEventSink	：当此事件发生时，回调此接口
		返回：
			dwEventID	：当此事件发生时，调用IEventSink::OnEvent(dwEventID)
	*/
	virtual BOOL AddEvent(HANDLE hEvent,IEventSink* pEventSink,/*out*/DWORD& dwEventID) = NULL;

	// 同上，不同之处在于hEvent由IThreadRoute创建和删除，推荐使用这个接口
	virtual BOOL AddEvent(IEventSink* pEventSink,/*out*/DWORD& dwEventID) = NULL;

	// 查找hEvent，由IThreadRoute自动创建事件时，用户可能需要查找此句柄
	virtual HANDLE GetEventHandle(DWORD dwEventID) = NULL;
	
	// 清除一个事件服务
	virtual BOOL RemoveEvent(DWORD dwEventID) = NULL;
	

	// 线程定时器管理
	//------------------------------------------------------------------------
	// 增加定时器
	// 注意：多次设置同一个定时器时，每个定时器都有效
	//       dwElapse有限制：dwElapse > 0 && dwElapes < 0x7FFFFFFF
	virtual BOOL SetTimer(ITimerEventSink *pTimerSink,DWORD dwIDEvent,DWORD dwElapse,DWORD dwParam = 0) = NULL;
	
	// 外挂模块请求IThreadRoute清除定时服务
	virtual BOOL KillTimer(ITimerEventSink *pTimerSink,DWORD dwIDEvent) = NULL;

	virtual void Release() = NULL;
};
//------------------------------------------------------------------------
//　外挂模块
struct IEventSink
{
	// 当事件被触发时，回调此接口，加上dwEventID参数，允许一个接口跟多个Event绑定
	virtual void OnEvent(DWORD dwEventID) = NULL;
	
	// 当线程退出时或hEvent无效时，调用此接口，一般不需实现此接口
	virtual void OnEventExit(DWORD dwEventID){;}
};
//------------------------------------------------------------------------
// 时间对象需实现的接口
// 为避免跟mud中的ITimerSink相冲突，现名为改成ITimerEventSink
struct ITimerEventSink
{
	// 时间事件发生
	// 返回值为下次执行此timer的时间，以ms为单位
	// 如果停用此timer，需返回-1，系统自动KillTimer()
	virtual DWORD OnTimer(DWORD dwTimerID = 0,DWORD dwParam = 0) = NULL;
	// 当线程退出时，调用此接口，但KillTimer()时不回调此接口。一般不需实现此接口
	virtual void OnExitTimer(DWORD dwTimerID){;}
};
//------------------------------------------------------------------------
// 调用ClientSocket.lib中的CreateThreadRoute()创建一个IThreadRoute对象
extern "C"  BOOL CreateThreadRoute(ITrace* pTrace,IThreadRoute** ppThreadRoute);
//------------------------------------------------------------------------
class CThreadRouteHelper
{
public:
	CThreadRouteHelper()
	{
		m_pThreadRoute = NULL;
	}
	~CThreadRouteHelper()
	{
		Close();
	}
	void Close()
	{
		if(m_pThreadRoute)
		{
			m_pThreadRoute->Release();
			m_pThreadRoute = NULL;
		}
	}
	BOOL Create(ITrace* pTrace)
	{
		Close();

		if(!MyCreateThreadRoute(VERSION_ThreadRoute,pTrace,&m_pThreadRoute))
		{
			return FALSE;
		}
		return m_pThreadRoute != NULL;
	}
public:
	BOOL MyCreateThreadRoute(DWORD dwQueryVersion,ITrace* pTrace,IThreadRoute** ppThreadRoute);
public:
	IThreadRoute* m_pThreadRoute;
};
//------------------------------------------------------------------------
// 通过lib方式创建IThreadRoute对象
class CThreadRouteObject
{
public:
	CThreadRouteObject()
	{
		m_pThreadRoute = NULL;
	}
	~CThreadRouteObject()
	{
		Close();
	}
	void Close()
	{
		if(m_pThreadRoute)
		{
			m_pThreadRoute->Release();
			m_pThreadRoute = NULL;
		}
	}
	BOOL Create(ITrace* pTrace)
	{
		Close();
		return CreateThreadRoute(pTrace,&m_pThreadRoute);
	}

	IThreadRoute*operator->()
	{
		return m_pThreadRoute;
	}
	IThreadRoute* m_pThreadRoute;
};
//------------------------------------------------------------------------
