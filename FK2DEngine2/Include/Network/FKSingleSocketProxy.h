/**
*	created:		2013-5-10   6:39
*	filename: 		FKSingleSocketProxy
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKCThreadRoute.h"
#include "FKLinkProxyWnd.h"
#include <winsock2.h>
//------------------------------------------------------------------------
class CSingleSocketProxy : public IClientSocket
{
public:
	void Close();
	CSingleSocketProxy();
	~CSingleSocketProxy();

	BOOL Create(DWORD dwSocketID,IClientSocketSink *pSink);

	// 当前通道标识
	virtual DWORD GetSocketID()
	{
		return 0;
	}

	// 发起连接，连接结果：当收到OnConnectOK()时，表示连接成功，收到OnConnectError()时表示连接失败
	// 返回：用户可忽略返回结果
	virtual BOOL Connect(LPCSTR szServerAddress, WORD wServerPort,NET_PROXY_OPTION* pProxyOption = NULL)
	{
		return m_pClientSocket && m_pClientSocket->Connect(szServerAddress,wServerPort,pProxyOption);
	}

	// 关闭此连接，下次可以再次调用Connect()发起连接
	// 不会回调IClientSocketSink::OnConnectClose()
	virtual BOOL CloseConnect()
	{
		return m_pClientSocket && m_pClientSocket->CloseConnect();
	}

	// 先立即发送，数据发不通时才将数据放入发送队列等待下次发送
	// 输入：nLen不能超过MAX_SOCKET_RAW_DATA_LEN,buf不能为空
	// 返回：如果socket发送失败，系统将在OnSocketError()中返回出错信息，因此不必在发送错误后关键连接
	//		 如果发送错或参数错，返回FALSE
	//		 如果发送成功，但网络层忙，返回WSA_IO_INCOMPLETE，这个返回值在文件传送等大量数据传送时很有用
	virtual int Send(LPCSTR buf,int nLen)
	{
		if(m_pClientSocket == NULL)
			return FALSE;
		int nReturn = m_pClientSocket->Send(buf,nLen);

		// 触发事件
		CLinkProxyWnd::LINK_NOTE *pNode = new CLinkProxyWnd::LINK_NOTE(m_pClientSocket->GetSocketID(),NULL,0,0);
		if(pNode)
			::PostMessage(m_LinkProxyWnd.m_hWnd,WM_LINK_MSG,CLinkProxyWnd::linkDataSending,(LPARAM)pNode);

		return nReturn;
	}

	// 当收到OnDataArrived()通知时，才能调用此接口接收数据
	// 输入：nBufLen为buf大小
	// 返回：buf中含有长度为nLen的数据
	virtual BOOL Recv(int nBufLen,/*out*/char* buf,/*out*/int& nLen)
	{
		return m_pClientSocket && m_pClientSocket->Recv(nBufLen,buf,nLen);
	}

	// 查询当前是否在连接状态
	virtual BOOL IsConnected()
	{
		return m_pClientSocket && m_pClientSocket->IsConnected();
	}

	/* 切换到下一个状态
	   如：
		  应用层的登录态和运行态由两个类来实现，都实现IClientSocketSink
		  当登录完成以后，调用此函数从登录态切换到运行态
	*/
	virtual void GotoNextState(IClientSocketSink* pSink)
	{
		m_pSink = pSink;
	}

	// 将来可以获取一些内部数据，如当前发送队列长度、收发速度、当前socket是否阻塞等。暂不支持此功能。
	virtual BOOL ioctrl(DWORD dwCmd,DWORD dwParam,/*out*/void* pData)
	{
		return m_pClientSocket && m_pClientSocket->ioctrl(dwCmd,dwParam,pData);
	}

	// 释放对象
	virtual void Release()
	{
		Close();
		delete this;
	}
private:
	CThreadRoute		m_ThreadRoute;
	CLinkProxyWnd		m_LinkProxyWnd;
	IClientSocketSink*	m_pSink;
	IClientSocket*		m_pClientSocket;
};
//------------------------------------------------------------------------