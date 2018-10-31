/*****************************************************************************
ģ����      : quantumsock
�ļ���      : quantumsock.cpp
����ļ�    : quantumsock.h
�ļ�ʵ�ֹ���: ����h.323 stack��socket�շ������Ա�ʵ�����Ӽ��ܡ����ӽ�����ع���.
����        : Τ����
�汾        : V1.0  Copyright(C) 2003-2004 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾        �޸���      �߶���		   �޸�����
2013/12/10	1.0         Τ����				       ����
******************************************************************************/

// QuantumSock.h: interface for the CQuantumSock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUANTUMSOCK_H__1E09844C_1E11_41B0_80E9_E7C48AFBC5E2__INCLUDED_)
#define AFX_QUANTUMSOCK_H__1E09844C_1E11_41B0_80E9_E7C48AFBC5E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rvstdio.h"
#include "rvaddress.h"
#include "rvlock.h"
#include "rvthread.h"
#include "rvsocket.h"
#include "cmH245GeneralDefs.h"
#include "cmintr.h"


//#define _REVERSE_BUF_
#define _TCP_ENC_
//#define _UDP_ENC_
#define _XOR_KEY 8

#ifndef _MSC_VER
//#undef FAR
#define FAR
#include <sys/socket.h>
#else
#define socklen_t RvInt32
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define TPKT_HEADER_SIZE	4
#define _LEN_OF_TPKT_HDR_   4
#define _LEN_OF_KEDA_HDR_	4
#define _KEDA323_UDP_HDR_	"keda"

	void		SetupHAPP	(HAPP hApp,RvBool bKeDaStandard,RvBool bQuantumCall);
#ifdef WIN32
	RvInt32		kdvrecvfrom (RvSocket s, RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, struct sockaddr FAR *from, RvInt32 FAR * fromlen);
	RvInt32		kdvsendto	(RvSocket s, const char FAR * buf, int len, int flags, const struct sockaddr FAR *to, int tolen);
#else
	RvInt32		kdvsendto	(RvSocket s, const RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, const struct sockaddr FAR *to, RvInt32 tolen);
	RvInt32		kdvrecvfrom	(RvSocket s, RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, struct sockaddr FAR *from, socklen_t * fromlen);
#endif
	RvInt32		kdvsend		(RvSocket s, const RvUint8 FAR * buf, RvInt32 len, RvInt32 flags, RvUint8* pCallID);
	RvInt32		kdvrecv		(RvSocket s, RvUint8 FAR * buf, RvInt32 len, RvInt32 flags);

	RVAPI void		kdv323logon ();
	RVAPI void		kdv323logoff();
	RVAPI void		kdv323savefile(RvBool bSaveRecv, RvBool bSaveSend);
	
#if defined(__cplusplus)
}
#endif

#endif // !defined(AFX_QUANTUMSOCK_H__1E09844C_1E11_41B0_80E9_E7C48AFBC5E2__INCLUDED_)

