/**
*	created:		2013-5-8   21:41
*	filename: 		FKPing
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKPing.h"
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Ping
	{
		//------------------------------------------------------------------------
		int			MyPing(LPCSTR pstrHost);
		void		ReportError(LPCSTR pstrFrom);
		int			WaitForEchoReply(SOCKET s);
		u_short		in_cksum(u_short *addr, int len);
		int			SendEchoRequest(SOCKET, LPSOCKADDR_IN);
		DWORD		RecvEchoReply(SOCKET, LPSOCKADDR_IN, u_char *);
		//------------------------------------------------------------------------
		bool Init()
		{
			WSADATA wsaData;
			WORD wVersionRequested = MAKEWORD(1,1);
			int nRet = WSAStartup(wVersionRequested, &wsaData);
			if( nRet )
			{
				return false;
			}
			if (wsaData.wVersion != wVersionRequested)
			{
				return false;
			}
			return true;
		}
		//------------------------------------------------------------------------
		int  Ping( const char* pAddress )
		{
			return MyPing( pAddress );
		}
		//------------------------------------------------------------------------
		void Release()
		{
			WSACleanup();
		}
		//------------------------------------------------------------------------
		// 根据Ping值获取服务器状态
		const wchar_t* GetPingState( int nPingValue )
		{
			switch( nPingValue )
			{
			case PING_TIME_OUT:
				return L"关闭";
			case PING_ERROR:
				return L"未知";
			break;
			}

			if( nPingValue >= 0 && nPingValue <= 100 )
			{
				return L"流畅";
			}
			if( nPingValue > 100 && nPingValue <= 300 )
			{
				return L"一般";
			}
			if( nPingValue > 300 && nPingValue < 1000 )
			{
				return L"较慢";
			}
			return L"很慢";
		}
		//------------------------------------------------------------------------
		int MyPing(LPCSTR pstrHost)
		{
			SOCKET	  rawSocket;
			LPHOSTENT lpHost;
			struct    sockaddr_in saDest;
			struct    sockaddr_in saSrc;
			DWORD	  dwTimeSent;
			DWORD	  dwElapsed;
			u_char    cTTL;
			int       nLoop;
			int       nRet;

			rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
			if (rawSocket == SOCKET_ERROR) 
			{
				ReportError("socket()");
				return PING_ERROR;
			}
			lpHost = gethostbyname(pstrHost);
			if (lpHost == NULL)
			{
				return PING_ERROR;
			}

			saDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
			saDest.sin_family = AF_INET;
			saDest.sin_port = 0;

			for (nLoop = 0; nLoop < 4; nLoop++)
			{
				SendEchoRequest(rawSocket, &saDest);
				nRet = WaitForEchoReply(rawSocket);
				if (nRet == SOCKET_ERROR)
				{
					ReportError("select()");
					break;
				}
				if (!nRet)
				{
					return PING_TIME_OUT;
				}
				dwTimeSent = RecvEchoReply(rawSocket, &saSrc, &cTTL);
				dwElapsed = GetTickCount() - dwTimeSent;
				nRet = closesocket(rawSocket);
				if (nRet == SOCKET_ERROR)
				{
					ReportError("closesocket()");
				}
				return dwElapsed;
			}
			nRet = closesocket(rawSocket);
			if (nRet == SOCKET_ERROR)
			{
				ReportError("closesocket()");
			}
			return PING_ERROR;
		}
		//------------------------------------------------------------------------
		// SendEchoRequest()
		// Fill in echo request header
		// and send to destination
		int SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr) 
		{
			static ECHOREQUEST echoReq;
			static int nId = 1;
			static int nSeq = 1;
			int nRet;

			// Fill in echo request
			echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
			echoReq.icmpHdr.Code		= 0;
			echoReq.icmpHdr.Checksum	= 0;
			echoReq.icmpHdr.ID			= nId++;
			echoReq.icmpHdr.Seq			= nSeq++;

			// Fill in some data to send
			for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
				echoReq.cData[nRet] = ' '+nRet;

			// Save tick count when sent
			echoReq.dwTime				= GetTickCount();

			// Put data in packet and compute checksum
			echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq, sizeof(ECHOREQUEST));

			// Send the echo request  								  
			nRet = sendto(s,						/* socket */
						 (LPSTR)&echoReq,			/* buffer */
						 sizeof(ECHOREQUEST),
						 0,							/* flags */
						 (LPSOCKADDR)lpstToAddr, /* destination */
						 sizeof(SOCKADDR_IN));   /* address length */

			if (nRet == SOCKET_ERROR) 
				ReportError("sendto()");
			return (nRet);
		}
		//------------------------------------------------------------------------
		// RecvEchoReply()
		// Receive incoming data
		// and parse out fields
		DWORD RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) 
		{
			ECHOREPLY echoReply;
			int nRet;
			int nAddrLen = sizeof(struct sockaddr_in);

			// Receive the echo reply	
			nRet = recvfrom(s,					// socket
							(LPSTR)&echoReply,	// buffer
							sizeof(ECHOREPLY),	// size of buffer
							0,					// flags
							(LPSOCKADDR)lpsaFrom,	// From address
							&nAddrLen);			// pointer to address len

			// Check return value
			if (nRet == SOCKET_ERROR) 
				ReportError("recvfrom()");

			// return time sent and IP TTL
			*pTTL = echoReply.ipHdr.TTL;
			return(echoReply.echoRequest.dwTime);   		
		}
		//------------------------------------------------------------------------
		// What happened?
		void ReportError(LPCSTR pWhere)
		{
			// fprintf(stderr,"\n%s error: %d\n",WSAGetLastError());
		}
		//------------------------------------------------------------------------
		// WaitForEchoReply()
		// Use select() to determine when
		// data is waiting to be read
		int WaitForEchoReply(SOCKET s)
		{
			struct timeval Timeout;
			fd_set readfds;

			readfds.fd_count = 1;
			readfds.fd_array[0] = s;
			Timeout.tv_sec = 5;
			Timeout.tv_usec = 0;

			return(select(1, &readfds, NULL, NULL, &Timeout));
		}
		//------------------------------------------------------------------------
		// Mike Muuss' in_cksum() function
		// and his comments from the original
		// ping program
		//
		// * Author -
		// *	Mike Muuss
		// *	U. S. Army Ballistic Research Laboratory
		// *	December, 1983

		/*
		 *			I N _ C K S U M
		 *
		 * Checksum routine for Internet Protocol family headers (C Version)
		 *
		 */
		u_short in_cksum(u_short *addr, int len)
		{
			register int nleft = len;
			register u_short *w = addr;
			register u_short answer;
			register int sum = 0;

			/*
			 *  Our algorithm is simple, using a 32 bit accumulator (sum),
			 *  we add sequential 16 bit words to it, and at the end, fold
			 *  back all the carry bits from the top 16 bits into the lower
			 *  16 bits.
			 */
			while( nleft > 1 )  {
				sum += *w++;
				nleft -= 2;
			}

			/* mop up an odd byte, if necessary */
			if( nleft == 1 ) {
				u_short	u = 0;

				*(u_char *)(&u) = *(u_char *)w ;
				sum += u;
			}

			/*
			 * add back carry outs from top 16 bits to low 16 bits
			 */
			sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
			sum += (sum >> 16);			/* add carry */
			answer = ~sum;				/* truncate to 16 bits */
			return (answer);
		}
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------