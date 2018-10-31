#ifndef _NETCBB_DHCPS_H_
#define _NETCBB_DHCPS_H_
#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */


/*�궨��*/
/* DHCP-Server �ص���������Ϣ���ַ*/
#define DHCPS_MSG_BASE			                    (u32)80000

/* DHCP-Server ���������*/
#define DHCPS_MAX_ETH_NUM			                (u32)16

/*�ṹ�嶨��*/
/* dhcp �������� DNS  ������Ϣ */
typedef struct{
    u8 IsAssignDns;                   /* 0: ��ָ��(����Ĭ�� dns ������); 1: ָ�� */
	u32 dwDnsIp;                      /* ������ : DNS��IP��ַ */
    s8 achDnsName[128];               /* ������ : DNS ������ ���� */
}TDhcpServerDnsInfo;

/* dhcp �������������ṹ�嶨�� */
typedef struct{
    u32 dwNetMask;                 /* ������ : ����*/
	u32 dwSubNetMask;              /* ������ : ��������*/
	u32 dwIpPoolStart;             /* ������ : ��ʼ����ĵ�ַ*/
	u32 dwIpPoolEnd;               /* ������ : ��ֹ����ĵ�ַ*/
	u32 dwRoutes;                  /* ������ : Ĭ�����ػ���·������ַ*/
	u32 dwEthIp;                   /* ������ : ������ַ*/
	u32 dwEthId;                   /* ���� ID */
}TDhcpServerEthInfo;

/* dhcp ��������������Ϣ�ṹ�嶨�� */
typedef struct{
	TDhcpServerEthInfo achTDhcpServerEthInfo[DHCPS_MAX_ETH_NUM];
    u32 dwDhcpServerEthCount;                             /* dhcp-server ������Ŀ */
	TDhcpServerDnsInfo tTDhcpServerDnsInfo;
}TDhcpServerConfInfo;

typedef struct
{
	u32 dwDhcpsIsRun;       /* 0:ֹͣ; 1: ���� */  
}TNetDhcpsState;

/*�ص��������Ͷ���*/
/*================================
��������NetDhcpsNotifyCallBack
���ܣ���DHCP-Server  ֪ͨ�û��Ļص�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwMsgID���¼����ͣ����������Ϣ���Ͷ���(��ʱ����Ҫ�ص������δ�����κλص�ֵ)
		      pMsg������¼�������ƥ�����Ϣ���ݣ���������Ϣ����˵��
����ֵ˵���� ��ʱ����Ϊ0���Ժ������չ
==================================*/
typedef int(*NetDhcpsNotifyCallBack)(u32 dwMsgID, void* pMsg);


/*�����ӿڶ���*/
/*================================
��������NetDhcpsStart
���ܣ�����DHCP-Server����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptTDhcpsServerConfInfo��dhcp-server ������Ϣ�ṹ��ָ��
		      ptDhcpsCallBack���ϲ�ע��Ļص�����ָ��
����ֵ˵���� OK/ERROR
==================================*/
s32 NetDhcpsStart(TDhcpServerConfInfo  *ptDhcpServerConfInfo,  NetDhcpsNotifyCallBack  ptDhcpsCallBack);


/*================================
��������NetDhcpsStop
���ܣ��ر�DHCP-Server  ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵���� OK/ERROR
==================================*/
s32 NetDhcpsStop();


/*================================
��������NetDhcpsGetState
���ܣ��õ�dhcp-server ����״̬
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵���� OK/ERROR
==================================*/
s32 NetDhcpsGetState(TNetDhcpsState *tNetdhcpsState);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */
#endif