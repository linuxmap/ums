#ifndef _FCNET_H_
#define _FCNET_H_

#include "kdvtype.h"

#define			INTERFCNET_VERION		"INTERFCNET.40.0.0.01.071224"

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ע����ģ���漰������ip ��Ϊu32������
	��������:��λbit/s
	����ʱ�䵥λ:millisecond
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*
������
*/
//��ȷ����ֵ
#define		INTERFCNET_OK					(u16)0
#define		INTERFCNET_ERROR_BASE			(u16)16500
//ip��Ч
#define		INTERFCNET_INVALID_IP			INTERFCNET_ERROR_BASE + 1
//�����ź�������
#define		INTERFCNET_SEM_CREATE			INTERFCNET_ERROR_BASE + 2
//�ڴ治��
#define		INTERFCNET_NO_MEMORY			INTERFCNET_ERROR_BASE + 3
//����ģ���ʼ��ʧ��
#define		INTERFCNET_DCB_START			INTERFCNET_ERROR_BASE + 4
//����ģ���˳�ʧ��
#define		INTERFCNET_DCB_STOP				INTERFCNET_ERROR_BASE + 5
//ͨ������
#define		INTERFCNET_CHANNEL_FULL			INTERFCNET_ERROR_BASE + 6
//��ģ��û�г�ʼ��
#define		INTERFCNET_NOT_INIT				INTERFCNET_ERROR_BASE + 7
//ͨ�����������ģ��ʧ��
#define		INTERFCNET_ADD_FC_FAIL			INTERFCNET_ERROR_BASE + 8
//������ģ��ɾ��ͨ����ʧ��
#define		INTERFCNET_DEL_FC_FAIL			INTERFCNET_ERROR_BASE + 9
//����ͨ�������ؼ���ʧ��
#define		INTERFCNET_TRIGGER_FC_FAIL		INTERFCNET_ERROR_BASE + 10
//������ʧ��
#define		INTERFCNET_BAND_DETECT_FAIL		INTERFCNET_ERROR_BASE + 11
//
#define		INTERFCNET_NULL_POINT		INTERFCNET_ERROR_BASE + 12
//////////////////////////////////////////////////////////////////////////

//Ĭ��ͨ����
#define			INTERFCNET_DEFAULT_CHANNEL_NUM		(u32)256
//Ĭ��fc��ʱ����ʱֵ�����룩
#define			INTERFCNET_DEFAULT_TIMEOUT_MILLIS	(u32)5000

/**/
//fc��ʱ���ص�ʱ,fcnet������ͳ������(����)
#define			FCNET_STAIS_TYPE_REQ	1
//fc��ʱ���ص�ʱ,fcnet������ͳ������ķ�����Ϣ(��Ӧ)
#define			FCNET_STAIS_TYPE_ACK	2

/**/
//���ؼ���ʱ,�����ֵ,��Сֵ,ƽ��ֵ
typedef enum
{
		STATIS_USE_VALUE_AVERAGE	=	0,		//ȡƽ��ֵ
		STATIS_USE_VALUE_MAX		=	1,		//ȡ���ֵ
		STATIS_USE_VALUE_MIN		=	2		//ȡ��Сֵ
}TStatisValueType;


//�̶��ֶΣ�fcnet��u8��ʽ����medianet��medianet��u8��ʽԭ������fcnet
typedef struct tagStatisFixField
{
	u64 m_dwTimestamp;				//��ͨ���ı���ͳ�ư���ʱ���
	u32 m_dwSrcRtpIp;					//Դip
	u16 m_wSrcRtpPort;					//Դport
	u16 m_wTargetRtcpPort;				//Ŀ��port?????
	u32 m_dwTargetRtcpIp;				//Ŀ��ip����ʶ������ͨ����	
	u32 m_dwFcTimeOutTimeStamp;			//fc��ʱ��ʱ���
	u64	m_qwSendOutTimeStamp;			//
	u64 m_qwSendInTimeStamp;			//
}TStatisFixField;

//�仯�ֶΣ���medianet��u8��ʽ����fcnet����ʱ��
//�����ڹ̶��ֶκ�����ṹ���ֶ�˳���ڹ̶��ֶκ��������
typedef struct tagStatisVaryField
{
	u32 m_dwRecvPackNum;//���ε��հ���
	u32 m_dwExptPackNum;//���ε���������
	u32 m_dwRecvdBytes;//���ε��յ����ֽ���
	u32	m_dwReserved;			//
	u64	m_qwRtcpInTimeStamp;	//
	u64 m_qwRtcpOutTimeStamp;	//
}TStatisVaryField;

//����mediasnd�����ÿ��fc��ʱ����ʱͳ����Ϣ
typedef struct tagPackStatis
{
	u8 m_byCommandType;				//
	u8 m_byAlignField;				//????
	u16 m_wAlignField;				//????
	u64 m_dwRtt;					//��ͨ�����ӳ�
	double m_llLostFraction;		//������
	u32 m_dwCompareField;			//������ȷ���ж�,Ŀǰû��
	TStatisFixField m_tStatisFixField;
	TStatisVaryField m_tStatisVaryField;
}TPackStatis;



/*===============================
typedef void (*BDNOTICECB)(u32 dwIp, u32 dwBandWidth, u32 dwContext);
//���ض�̬����֪ͨ�ص�
u32 dwip: Ŀ��ip����ʶͨ����
u32 dwBd��ͨ����Ľ������
u32 dwContext���û�����
================================*/
typedef void (*BDNOTICECB)(u32 dwIp, u32 dwBandWidth, u32 dwContext);

/*===============================
typedef void(*BDDETECTCB)(u32 dwTargetIp, u32 dwBandWidth, u32 dwContext);
//������֪ͨ�ص�
u32 dwip: Ŀ��ip����ʶͨ����
u32 dwBd��ͨ����Ľ������
u32 dwContext���û�����
================================*/
typedef void(*BDDETECTCB)(u32 dwTargetIp, u32 dwBandWidth, u32 dwContext);


/*
���ϲ�ӿ�
*/
/*==================================
u16 InitFcNet(u16 wCtrlPort, u16 wStartDataPort, u16 wDataPortNum, u32 dwTotalGrpNum=0 )
������           ���ϲ��û�Ҫ������ʱע�ᡢ���أ����ڱ������нӿڵ�ָ���˿���
//                  ��������������(����)���粻ָ�������˿ڣ�����ȱʡ�Ķ˿���������
//                  ��Σ���ģ�齫����ָ����ʼ�˿ںźͶ˿������ں������ܵļ�ⷢ����
//                  ѡȡָ����Χ�ڿ��õĶ˿ڽ��м����������(����)��
//                  ��������ģ��Ҳ������ȫ�ָ���ƽ����ģ�顢��ȡ���ӿڵ��������
//                  ��������ز����������Ҫ����Դ
//��ʼ��
//�����ڴ���mediasnd֮ǰ����
u16 wCtrlPort:�����������port����Ϊtcp����
u16 wStartDataPort����������port,��Ϊudp
u16 wDataPortNum��ͬʱ�����ж����⣬��Ϊ�������õ�����port��
u16 wInnerStartPort:ģ���ڲ�ʹ�õĶ˿ڿ��÷�Χ��ʼֵ
u16 wInnerPortNum:ģ���ڲ�ʹ�ö˿ڶ������������0��ʾֻ����ʼֵ���ã�
					1��ʾ���ö˿ڷ�ΧΪ[start_inner_port, start_inner_port+1]����������
u32 dwTotalGrpNum:ͨ��������=0��ȡĬ��ֵ:INTERFCNET_DEFAULT_CHANNEL_NUM
====================================*/
u16 InitFcNet(u16 wCtrlPort, u16 wStartDataPort, u16 wDataPortNum, u16 wInnerStartPort, u16 wInnerPortNum, u32 dwTotalGrpNum=0 );
u16 QuitFcNet();

/*=================================
u16 RegisterChnlGrp(u32 dwChnlGrpIp, BDNOTICECB pBdNoticeCb, u32 dwContext, u32 dwFcTimeInterval=0);
//��ָ��ʱ������ȥ��ָ���Զ˵�ͨ��������/�����Զ���������
u32 dwIp��Ŀ��ip
u32 dwFcTimeInterval������ʱ����,=0��ȡĬ��ֵINTERFCNET_DEFAULT_TIMEOUT_MILLIS;
						�Ժ���ƣ�����ȡֵ��ΧΪ<100, 600000>��Ϊ�Ͼ�ȷ�ظ�������ʵ���շ������
						��ֵ�������÷�ΧΪ<500, 5000>
BDNOTICECB pBdNoticeCb������֪ͨ�ص�����
u32 dwContext���û�����
==================================*/
u16 RegisterChnlGrp(u32 dwChnlGrpIp, BDNOTICECB pBdNoticeCb, u32 dwContext, u32 dwFcTimeInterval=0);
//�رն�ȥ��ָ���Զ˵�ͨ�������������
u16 UnregisterChnlGrp(u32 dwChnlGrpIp);


/*========================================================
u16 DcbDetect(u32 dwTargetIp, u32 dwInitBandWidth, u32 dwContext, BDDETECTCB pBdDetectCb);
//���ӱ��˵�ָ����ַ��ȫ�̿��ô���
u32 dwTargetIp:Ŀ��ip
u16 wPort:�Զ˼�������˿�
u32 dwInitBandWidth:���ʱ��ʼ�������,����Ϊ�����ڼ��ټ�����
u32 dwContext:��������
BDDETECTCB pBdDetectCb:������֪ͨ�ص�
=========================================================*/
u16 DcbDetect(u32 dwTargetIp, u16 wPort, u32 dwInitBandWidth, u32 dwContext, BDDETECTCB pBdDetectCb);
/*
//����ȫ��Ĭ������
u16 DcbIfDefRateSet(int, int);//dcb_if_def_rate_set(int, int);
//���ýӿڿ��ô���
u16 DcbIfAvlBwSet(int, int);//dcb_if_avl_bw_set(int, int);
//�����㷨���滻����
u16 DcbFcAlgSet(const char*, unsigned int, ...);//dcb_fc_alg_set(const char*, unsigned int, ...);
//���ؾ����㷨���滻����
u16 DcbLbAlgSet(unsigned int, ...);//dcb_lb_alg_set(unsigned int, ...);
//��ȡָ��ͨ����ĸ�������ȫ�ָ��ر�
u16 DcbLoadblcGet(const char*, struct load_proportion*);//dcb_loadblc_get(const char*, struct load_proportion*);
//����ָ��ͨ����ĸ�������ȫ�ָ��ر�
u16	DcbLoadblcSet(const char*, struct load_proportion*);//dcb_loadblc_set(const char*, struct load_proportion*);
*/

/*
//��medianet�ӿ�
*/
/*==================================
u16 RegisterChannel(u32 dwChalGrpIp, u16 wTargetRtcpPort, u32 dwSrcRtpIp, u16 wSrcRtpPort, const CKdvMediaSnd* pcMediaSnd);
//�����Ӽ�ע��mediasnd����
u32 dwIp��Ŀ��ip,��ʶ���ڵ�ͨ����
const CKdvMediaSnd* pcMediaSnd��ͨ��
===================================*/
u16 RegisterChannel(u32 dwChalGrpIp, u16 wTargetRtcpPort, u32 dwSrcRtpIp, u16 wSrcRtpPort, void* pcMediaSnd);
u16 UnregisterChannel(u32 dwChnlGrpIp, u16 wTargetRtcpPort, u32 dwSrcRtpIp, u16 wSrcRtpPort, void* pcMediaSnd);

/*=======================================================
u16 NoticePackStatis(const TPackStatis& tPackStatis, const CKdvMediaSnd* pcMediaSnd, u32 dwChalGrpIp);
//����mediasnd�����յ�rtcp��Ӧ���������Ӽ�֪ͨͳ����Ϣ
const TPackStatis& tPackStatis��ͳ����Ϣ�ṹ
const CKdvMediaSnd* pcMediaSnd��ͨ��
u32 dwIp��ͨ����ip
========================================================*/
u16 NoticePackStatis( u8* pBuf, u16 wBufLen);



API void fcnetver();

#endif

