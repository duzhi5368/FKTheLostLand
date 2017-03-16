/**
*	created:		2013-5-10   5:35
*	filename: 		FKClientLink
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKClientSocket.h"
#include "FKSocketPacket.h"
#include "FKStreamEncrypt.h"
#include <vector>
using namespace std;
#include "FKStackFrame.h"
//------------------------------------------------------------------------
#pragma warning( disable : 4018 )
//------------------------------------------------------------------------
// 加密失败		
#define  RESULT_ENCRYPT_FAILED		225
//------------------------------------------------------------------------
class CClientLink : public IClientSocketSink,public IClientLink
{
public:
	CClientLink()
	{
		m_pSocket = NULL;
		m_pSink = NULL;
		m_bLocalIClientSocket = FALSE;

		m_pEncryptRcv = NULL;
		m_pEncryptSnd = NULL;
	}
	virtual ~CClientLink()
	{
		Close();
		if( m_pEncryptRcv )
		{
			m_pEncryptRcv->Release();
			m_pEncryptRcv = NULL;
		}
		if( m_pEncryptSnd )
		{
			m_pEncryptSnd->Release();
			m_pEncryptSnd = NULL;
		}
		if(m_bLocalIClientSocket)
		{
			if(m_pSocket)
			{
				m_pSocket->Release();
				m_pSocket = NULL;
			}
			m_bLocalIClientSocket = FALSE;
		}
	}
	void Close()
	{
		m_SocketPacket.Close();
	}

	BOOL Create(DWORD dwSocketID,IClientLinkSink* pSink,IClientSocket* pSocket,ITrace* pTrace)
	{
		if(pSocket != NULL)
			m_pSocket = pSocket;
		else 
		{
			if(!CreateSingleSocketProxy(dwSocketID,static_cast<IClientSocketSink*>(this),pTrace,&m_pSocket))
				return FALSE;
			m_bLocalIClientSocket = TRUE;
		}
		m_SocketPacket.Create(m_pSocket);
		m_pSink = pSink;
		return SetEncryptStrategy();
	}
	virtual void OnConnectError(DWORD dwSocketID,LPCSTR szMsg,DWORD dwErrorCode)
	{
		Close();
		m_pSink->OnConnectError(dwSocketID,szMsg,dwErrorCode);
	}
	virtual void OnConnectOK(DWORD dwSocketID)
	{
		m_pSink->OnConnectOK(dwSocketID);
	}
	virtual void OnDataArrived(DWORD dwSocketID)
	{
		char* pBuf; int nLen;

		while( (nLen = m_SocketPacket.OnDataArrived(&pBuf)) > 0 )
		{
			// 解密
			if( !m_pEncryptRcv->Decrypt( (const unsigned char * )pBuf , 
					 					 ( unsigned char * )pBuf,
										 nLen,
										 nLen ) )
			{
				m_pSink->OnConnectClose(dwSocketID,"数据包解密失败!",0);
				m_pSocket->CloseConnect();
				return;
			}

			m_pSink->OnRecv(dwSocketID,pBuf,nLen);
		}

		if(nLen < 0)
		{
			m_pSink->OnConnectClose(dwSocketID,"收到非法数据",0);
			m_pSocket->CloseConnect();
		}
	}
	virtual void OnConnectClose(DWORD dwSocketID,LPCSTR szMsg,DWORD dwErrorCode)
	{
		Close();
		m_pSink->OnConnectClose(dwSocketID,szMsg,dwErrorCode);
	}

	// 当前通道标识
	virtual DWORD GetSocketID()
	{
		if(m_pSocket)
			return m_pSocket->GetSocketID();
		else 
			return -1;
	}

	// 发起连接，连接结果：当收到OnConnectOK()时，表示连接成功，收到OnConnectError()时表示连接失败
	// 返回：用户可忽略返回结果，但参数错时也会返回FALSE
	virtual int Connect(LPCSTR szServerAddress, WORD wServerPort,NET_PROXY_OPTION* pProxyOption)
	{
		Close();
		return m_pSocket->Connect(szServerAddress,wServerPort,pProxyOption);
	}

	virtual void GotoNextState(IClientLinkSink* pSink)
	{
		m_pSink = pSink;
	}

	// 关闭此连接，下次可以再次调用Connect()发起连接
	// 不会回调IClientSocketSink::OnConnectClose()
	virtual BOOL CloseConnect()
	{
		Close();
		if(m_pSocket == NULL)
			return FALSE;
		return m_pSocket->CloseConnect();
	}

	BOOL GetCallList( void ** pList , int & nLen ,int nVer )
	{
		if( nVer != VERSION_CLIENTLINK )
			return FALSE;

		if( pList == NULL || nLen < m_StackList.size()+m_StackFrame.GetSize() )
			return FALSE;

		memcpy( pList , &m_StackList[0] , m_StackList.size()*sizeof(DWORD));
		nLen = m_StackList.size();

		int nCount = nLen - m_StackList.size();
		if( !m_StackFrame.GetStackList( pList+m_StackList.size() ,nCount ) )
			return FALSE;
		
		nLen += m_StackFrame.GetSize();
		
		m_StackFrame.Clear();
		return TRUE;
	}


	/* 功能：发送数据包
	 输入：nLen不能超过MAX_SOCKET_RAW_DATA_LEN,buf不能为空

	 返回：发送错或参数错，返回FALSE
		   返回WSA_IO_INCOMPLETE：
			   表示数据已经递交给通讯层，但未立即发送出去
			   在文件传送等大量数据传送时，可以考虑减慢数据发送的速度


	 说明：  1、发送算法为先立即发送，数据发不通时，才将数据放入发送队列等待下次发送，同时返回WSA_IO_INCOMPLETE
			 2、如果socket发送失败，会通过回调OnConnectClose通知错信息，因此一般不必对发送错误作出出错处理
	*/
	virtual int Send(LPCSTR buf,int nLen)
	{
		// 加密？
		//...
		if( !m_pSocket->IsConnected() )
			return 0;
		
		int nOutLen = sizeof( m_Buf );
		if( !m_pEncryptSnd->Encrypt( (const unsigned char *)buf , 
									 (unsigned char *)(m_Buf+2) , 
									 nLen ,
									 nOutLen ) )
		{
				CloseConnect();
				return RESULT_ENCRYPT_FAILED;
		}

		// 检查Hook
		void * pReturn = 0;
		__asm{
			mov eax , dword ptr[ebp+4]
			mov dword ptr [pReturn],eax
		}
	
		int i = 0;
		for( ; i < m_StackList.size() ; i++ )
		{
			if( m_StackList[i] == pReturn )
				break;
		}

		if( i >= m_StackList.size() )
			m_StackList.push_back(pReturn);

		*(WORD*)m_Buf = (WORD)nOutLen;
		BOOL bReturn = m_pSocket->Send(m_Buf,nOutLen+2);
		
		m_StackFrame.SaveStack(10);
		return bReturn;

	}

	// 查询当前是否在连接状态
	virtual BOOL IsConnected()
	{
		return m_pSocket && m_pSocket->IsConnected();
	}

	virtual BOOL ioctrl(DWORD dwCmd,DWORD dwParam,/*out*/void* pData)
	{
		return m_pSocket && m_pSocket->ioctrl(dwCmd,dwParam,pData);
	}

	// 释放对象
	virtual void Release()
	{
		Close();
		delete this;
	}

public:
	// 设置接收数据的解密策略
	void SelEncrypt_Rcv( IStreamEncrypt * pStrategy );	
	// 设置发送数据的加密策略
	void SelEncrypt_Snd( IStreamEncrypt * pStrategy );	
	// 设置加密策略
	BOOL SetEncryptStrategy();

private:
	IClientLinkSink*	m_pSink;
	IClientSocket*		m_pSocket;
	BOOL				m_bLocalIClientSocket;			// m_pSocket是否为CClientLink内部创建的
	CClientSocketPacket	m_SocketPacket;					// 解最外层包
	IStreamEncrypt	 *	m_pEncryptRcv;					// 解密策略
	IStreamEncrypt	 *	m_pEncryptSnd;					// 加密策略
	char				m_Buf[MAX_SOCKET_DATA_LEN];		// 数据发送缓冲区
	vector< void * >	m_StackList;
	CStackFrame			m_StackFrame;
};
//------------------------------------------------------------------------