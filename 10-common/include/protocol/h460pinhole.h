/*******************************************************************************
 *  ģ����   :                                                                 *
 *  �ļ���   : h460pinhole.h                                                *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� :                                                                 *
 *  ����     : ��С��                                                          *
 *  �汾     : V1.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  30/8/2010     4.0         ��С��      ����                                 *
 *                                                                             *
 *******************************************************************************/

#ifndef h460pinhole_h__
#define h460pinhole_h__
#include "osp.h"
#include "dataswitch.h"

typedef struct tagInitInfo
{
	u32				m_dwLocalIP;
	BOOL32			m_bStartTimeMgr;
	u32				m_dwMaxCall;
	tagInitInfo()
	{
		m_dwLocalIP		= 0;
		m_bStartTimeMgr = FALSE;
		m_dwMaxCall		= 0;
	}
}TDsInitInfo;

typedef enum
{
	pinhole_rtp,
	pinhole_rtcp,
	pinhole_tpkt,
}EMGwPinholeType;

typedef enum
{
	tcp_h225_pinhole,
	tcp_h245_pinhole,
};

typedef struct tagPinholeInfo
{
	u32             m_dwLocalIP;
	u32				m_dwDestIP;
    u16             m_wLocalPort;
	u16				m_wDestPort;
	u32				m_dwSN;
	u8				m_byPayLoad;
	u8				m_byPinholeType;
	
	tagPinholeInfo()
	{
		memset(this, 0, sizeof(tagPinholeInfo));
	}
}TGwPinholeInfo;

typedef struct tagTpktPinhole
{
	u32             m_dwCall;
	u16				m_wType;
    
	tagTpktPinhole()
	{
		memset(this, 0, sizeof(tagTpktPinhole));
	}
}TGwTpktPinhole;
typedef u32 (*DSFilterTpktFun)(TGwTpktPinhole& tTpktInfo);

API void StartupDataSwitchApp(TDsInitInfo& tInfo);

void KdvTSDestoryDataSwitch();
BOOL32 KdvTSAddManyToOne( u32  dwLocalIP, u16  wLocalPort, u32 dwLocalIfIP,
					   u32  dwDstIP, u16  wDstPort, u32  dwDstOutIfIP);
BOOL32 KdvTSRemoveAllManyToOne( u32 dwDstIP, u16 wDstPort );
BOOL32 KdvTSRemoveManyToOne( u32 dwLocalIP, u16 wLocalPort, u32 dwDstIP, u16 wDstPort );
BOOL32 KdvTSSetFilterFunc(  u32  dwIP, u16  wPort , FilterFunc pfFilter);
BOOL32 KdvTSSpecifyFwdSrc(u32 dwSrcIp, u16 wSrcPort, u32 dwMapIp, u16 wMapPort);
BOOL32 KdvTSResetFwdSrc( u32 OrigIP, u16 OrigPort);

//RTP��RTCP�Ĵ�
BOOL32 KdvTSAddPinhole(TGwPinholeInfo& tInfo, u32 dwInterval, EMGwPinholeType emType);
BOOL32 KdvTSDelPinhole(u16 wPort);

//h225��h245�Ĵ�
BOOL32 KdvTSAddTpktPinhole(TGwTpktPinhole& tInfo, u32 dwInterval, DSFilterTpktFun pCallBack);
BOOL32 KdvTSDelTpktPinhole(TGwTpktPinhole& tInfo);


#endif//h460pinhole_h__


