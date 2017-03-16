/**
*	created:		2013-5-10   6:41
*	filename: 		FKSingleSocketProxy
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		最简单但低效的实现：一个线程实现单连接，可避开IThreadRoute、ILinkProxy实现问题
*/
//------------------------------------------------------------------------
#include <WinSock2.h>
#include "../../Include/Network/FKSingleSocketProxy.h"
#include "../../Include/ResMgr/ResMgrCommon.h"
//------------------------------------------------------------------------
#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#endif
//------------------------------------------------------------------------
CSingleSocketProxy::CSingleSocketProxy()
{
	m_pSink = NULL;
	m_pClientSocket = NULL;
}
//------------------------------------------------------------------------
CSingleSocketProxy::~CSingleSocketProxy()
{

}
//------------------------------------------------------------------------
extern "C" BOOL CreateSingleSocketProxy(DWORD dwSocketID,IClientSocketSink* pSink,ITrace* pTrace,/*out*/IClientSocket** ppClientSocket)
{
	Assert(ppClientSocket);

	CSingleSocketProxy* p = new CSingleSocketProxy();
	if(p == NULL)
		return FALSE;
	if(!p->Create(dwSocketID,pSink))
		return FALSE;
	*ppClientSocket = static_cast<IClientSocket*>(p);
	return TRUE;
}
//------------------------------------------------------------------------
BOOL CSingleSocketProxyHelper::MyCreateSingleSocketProxy(DWORD dwVersion,DWORD dwSocketID,IClientSocketSink* pSink,ITrace* pTrace,/*out*/IClientSocket** ppClientSocket)
{
	if(dwVersion > VERSION_SingleSocketProxy)
	{
		wchar_t buf[1024];
		wsprintf(buf,L"Error : dllCreateSingleSocketProxy() : version mismatch,%d wanted,but %d is requested\r\n",VERSION_SingleSocketProxy,dwVersion);
		OutputDebugString(buf);
		return FALSE;
	}
	return CreateSingleSocketProxy(dwSocketID,pSink,pTrace,ppClientSocket);	
}
//------------------------------------------------------------------------
BOOL CSingleSocketProxy::Create(DWORD dwSocketID,IClientSocketSink *pSink)
{
	Assert(m_ThreadRoute.Create( NULL ));

	if(!m_LinkProxyWnd.Create((IThreadRoute*)&m_ThreadRoute,NULL,TRUE,FALSE))
		return FALSE;
	Assert(m_LinkProxyWnd.AddSocket(dwSocketID,pSink,&m_pClientSocket));
	Assert(m_ThreadRoute.Start());
	return TRUE;
}
//------------------------------------------------------------------------
void CSingleSocketProxy::Close()
{
	m_ThreadRoute.Stop();
	if(m_pClientSocket)
	{
		m_LinkProxyWnd.RemoveSocket(m_pClientSocket);
		m_LinkProxyWnd.Close();
		m_pClientSocket->Release();
		m_pClientSocket = NULL;
	}
}
//------------------------------------------------------------------------