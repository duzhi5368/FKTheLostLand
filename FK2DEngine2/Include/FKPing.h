/**
*	created:		2013-5-8   21:40
*	filename: 		FKPing
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <winsock2.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Ping
	{
		//------------------------------------------------------------------------
		#pragma pack(1)
		//------------------------------------------------------------------------
		#define ICMP_ECHOREPLY	0
		#define ICMP_ECHOREQ	8
		#define PING_TIME_OUT	0xfffffffe
		#define PING_ERROR		0xffffffff
		//------------------------------------------------------------------------
		// IP Header -- RFC 791
		typedef struct tagIPHDR
		{
			u_char  VIHL;			// Version and IHL
			u_char	TOS;			// Type Of Service
			short	TotLen;			// Total Length
			short	ID;				// Identification
			short	FlagOff;		// Flags and Fragment Offset
			u_char	TTL;			// Time To Live
			u_char	Protocol;		// Protocol
			u_short	Checksum;		// Checksum
			struct	in_addr iaSrc;	// Internet Address - Source
			struct	in_addr iaDst;	// Internet Address - Destination
		}IPHDR, *PIPHDR;
		//------------------------------------------------------------------------
		// ICMP Header - RFC 792
		typedef struct tagICMPHDR
		{
			u_char	Type;			// Type
			u_char	Code;			// Code
			u_short	Checksum;		// Checksum
			u_short	ID;				// Identification
			u_short	Seq;			// Sequence
			char	Data;			// Data
		}ICMPHDR, *PICMPHDR;
		//------------------------------------------------------------------------
		#define REQ_DATASIZE 32		// Echo Request Data size
		//------------------------------------------------------------------------
		// ICMP Echo Request
		typedef struct tagECHOREQUEST
		{
			ICMPHDR icmpHdr;
			DWORD	dwTime;
			char	cData[REQ_DATASIZE];
		}ECHOREQUEST, *PECHOREQUEST;
		//------------------------------------------------------------------------
		// ICMP Echo Reply
		typedef struct tagECHOREPLY
		{
			IPHDR	ipHdr;
			ECHOREQUEST	echoRequest;
			char    cFiller[256];
		}ECHOREPLY, *PECHOREPLY;
		//------------------------------------------------------------------------
		#pragma pack()
		//------------------------------------------------------------------------
		bool Init();
		int  Ping( const char* pAddress );
		void Release();
		// 根据Ping值获取服务器状态
		const wchar_t* GetPingState( int nPingValue );
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------