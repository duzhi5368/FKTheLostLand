/**
*	created:		2013-5-10   2:10
*	filename: 		FKSocketPacket
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKClientSocket.h"
//------------------------------------------------------------------------
class CClientSocketPacket
{
public:
	enum 
	{
		MaxDataLen = MAX_SOCKET_RAW_DATA_LEN,		// 用户数据的最大长度
		MaxDataHeaderLen = 256,						// 多层命令封装以后，所以封装头的总的可能长度
		MaxBufferLen = (MaxDataLen + MaxDataHeaderLen) 
	};

	CClientSocketPacket()
	{
		m_pClientSocket = NULL;
		m_nBegin = 0;
		m_nEnd = 0;
	}
	void Close()
	{
		m_nBegin = 0;
		m_nEnd = 0;
	}
	BOOL Create(IClientSocket* pClientSocket)
	{
		m_pClientSocket = pClientSocket;
		return TRUE;
	}

	/*
	 功能：读取数据游流，并解出一个数据包
	
	 格式：wDataLen + data[wDataLen]
	
	 返回一个包数据长度，*ppBufBegin为缓冲区起始地址,指向m_buf中的某个位置 
		返回0表示包未收齐，等待下次OnDataArrived()事件到达
		返回负数表示严重失败
	*/
	int OnDataArrived(char** ppBufBegin)
	{
		if(m_pClientSocket == NULL)
			return 0;
		// 当前缓冲区中是否有数据？ CClientLink中是否有这种数据迁移导致的错误？
		if(m_nEnd - m_nBegin > 1)
		{ 
beginrecvdata:
			// 如果剩余的数据已经装满缓冲，但包还未收齐，需要把数据移到缓冲开头
			int nNextPacketLen = (int) *(WORD*)(m_buf + m_nBegin);
			int nLeft = m_nEnd - m_nBegin;
			int nExpectLen = 2 + nNextPacketLen;		// 包总长
			if(nNextPacketLen <= 0 || nExpectLen > MaxBufferLen)
			{ // 单个包不允许过大或等于0
#ifdef _DEBUG
				OutputDebugString(L"Error : CClientSocketPacket::OnDataArrived() : nPacketLen error!!\r\n");
				__asm int 3;
#endif
				m_nBegin = m_nEnd = 0;					// 严重出错，清0
				return -1;
			}
			else if(nExpectLen <= nLeft)
			{ // 收齐了一个包
				*ppBufBegin = m_buf + m_nBegin + 2;
				if(nExpectLen < nLeft)
					m_nBegin += nExpectLen;		// 还有其它包在缓冲中
				else
				{ // ==
					m_nBegin = 0; m_nEnd = 0;			// 当前刚好是一个包
				}
				
				// 解密数据包？
				//.....

				return nNextPacketLen;
			}
			else if(m_nBegin  + nExpectLen > MaxBufferLen)
			{ // 缓冲区已经无法放下最后一个包
				memmove(m_buf,m_buf + m_nBegin,m_nEnd - m_nBegin);
				m_nEnd = m_nEnd - m_nBegin; m_nBegin = 0;
			}
		}
		else if(m_nEnd - m_nBegin == 1)
		{ // 最极端的情况:只收到长度wDataLen的一个低字节，因而无法计算出nNextPacketLen
			m_buf[0] = m_buf[m_nBegin];
			m_nBegin = 0; m_nEnd = 1;
		}
		int nLen;
		if(!m_pClientSocket->Recv(MaxBufferLen - m_nEnd,m_buf + m_nEnd,nLen))
			return 0;
		if(nLen == 0)
			return 0;
		m_nEnd += nLen;
		goto beginrecvdata;	// 解出数据包
	}

	// 简单数据包发送
	int Send(LPSTR buf,int nLen)
	{
		if(m_pClientSocket)
			return FALSE;
		// 加密？
		//.......

		if(nLen > 32)
		{
			m_pClientSocket->Send((char*)&nLen,2);	// 发送长度
			return m_pClientSocket->Send(buf,nLen);
		}
		else
		{ // 如果数据量很少，不必增加m_pClientSocket->Send()一次调用的成本
			char data[1024];
			*(WORD*)data = (WORD)nLen;
			memcpy(data + 2,buf,nLen);
			return m_pClientSocket->Send(data,2 + nLen);
		}
	}

	// 把一组小包组合起来一次性发送给通讯层
	// 操作：把一组包缓冲起来，当包足够大时才真正发送出去
	int SendGroupPacket(LPCSTR buf,int nLen)
	{
		return m_pClientSocket->Send(buf,nLen);			// 发送数据
	}
	// 完成一组包的发送
	// 操作：把缓冲剩余未发送的数据发送出去
	int SendGroupPacketEnd()								// 如果是大包发送，在此真正发送数据，或发最后一个数据包
	{
		return TRUE;
	}

protected:
	IClientSocket* m_pClientSocket;
	char m_buf[MaxBufferLen]; 
	int  m_nBegin;		// 有效包开始位置，因为有可能第一个包和第二个包一起过来，第二个包的起始位置就不在0了
	int  m_nEnd;		// 上一个包可能还未接收完毕
/*
	m_buf示意图如下，d表示有数据
	+-+-+-+-+-+-+-+-+
	|d|d|d|d|d|-+-+-+
	+-+-+-+-+-+-+-+-+
 	 ^		   ^
	m_Begin	  m_nEnd
*/
};
//------------------------------------------------------------------------
