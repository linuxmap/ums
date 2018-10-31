#ifndef _NETCBB_INTERFACE_H_
#define _NETCBB_INTERFACE_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

/*��̫����صĽṹ����*/
/* ��̫�������ṹ */
typedef struct{
    u32 dwIpAdrs;/*�����ֽ���*/
    u32 dwIpMask; /*�����ֽ���*/
    u8  byMacAdrs[6];
}TNetEthParam;

/* ��̫��mac��ַ�ṹ*/
typedef struct{
    u8  byMacAdrs[6];
}TNetEthMac;

/* ��̫�������ṹ */
typedef struct{
    u32 dwIpNum;/*��Ч��IP��ַ��*/
    TNetEthParam atNetEthParam[IP_ADDR_MAX_NUM];/*���IP��ַ����Ϣ������*/
}TNetEthParamAll;

/* ����·�ɲ����ṹ */
typedef struct{
    u32 byEthId;		 /*����id*/	
    u32 dwDesIpNet;      /* Ŀ�������������ֽ���	*/
    u32 dwDesIpMask;     /* ���룬�����ֽ���	*/
    u32 dwGwIpAdrs;      /* ����ip��ַ�������ֽ���*/
    u32 dwRoutePri;		 /* ·�����ȼ�(1-255)��Ĭ��Ϊ0*/
}TNetIpRouteParam;

/*���·�ɲ����ṹ */
typedef struct{
    u32 dwIpRouteNum;    /* �õ���ʵ��·�ɸ��� */
    TNetIpRouteParam tNetIpRouteParam[IP_ROUTE_MAX_NUM];
}TNetAllIpRouteInfo;


#define NETCBB_IP_CONFLICT	1
#define NETCBB_MAC_CONFLICT	2
/*IP��ַ��ͻ�ص��������Ͷ���*/
typedef void (*TIpConflictCallBack)(u32 dwType, u8 *pbyMacAddr, u32 dwIpAdrs);

/*TPingCallBack�ص��ķ���ֵ����Ӧ����ΪnResult*/
#define PING_REPLY     0
#define PING_TIMEOUT   1   /*�ݲ�֧��*/
#define PING_ERROR     2
/*NetPing�ӿڴ�������ṹ��*/
typedef struct{
    s32 nPktSize;/*Ҫping�����ݱ��Ĵ�С�����ֽ�Ϊ��λ*/
    s32 nTimeOut;/*ping�ĳ�ʱֵ������Ϊ��λ*/
    s32 nTtl;/*TTLֵ*/
}TPingOpt;

/*Ping�ص��������Ͷ���*/
/*����˵����
ֻ֧��nResult��������ֵ�ṩping�ķ���ֵ.�����ֵΪ0
*/
typedef int(*TPingCallBack)(s32 nResult,s32 nTtl,s32 nTripTime,s32 nUserID,s32 nErrType,s32 nErrCode);

/*================================
��������NetGetEthParam
���ܣ���ȡ��̫����������ip��mask��mac
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId --- ��̫��ID�ţ�0~x��;
                TNetEthParam *ptNetEthParam --- �����̫����Ϣ�Ľṹָ�롣
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
==================================*/
s32 NetGetEthParam(u32 byEthId, TNetEthParam *ptNetEthParam);

/*================================
��������NetGetEthMac
���ܣ���ȡ��̫��mac��ַ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵���� byEthId --- ��̫��ID�ţ�0~x��;
                TNetEthMac *ptNetEthMac  --- �����̫����Ϣ�Ľṹָ�롣
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
��ע: ��api���ṩ֧�֣���NetGetEthParam���غϵط���
==================================*/
s32 NetGetEthMac(u32 byEthId, TNetEthMac *ptNetEthMac);

/*================================
��������NetGetEthParam
���ܣ���ȡһ�����������е���̫�����������IP��ַ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId --- ��̫��ID�ţ�0~x��;
                NetEthParamAll *ptNetEthParamAll --- �����̫����Ϣ�Ľṹָ�롣
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
==================================*/
s32 NetGetEthParamAll(u32 byEthId, TNetEthParamAll *ptNetEthParamAll);


/*================================

��������NetGetEthParamSecIP
���ܣ���ȡһ�����������еڶ�IP��ַ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId --- ��̫��ID�ţ�0~x��;
                NetEthParamAll *ptNetEthParamAll --- �����̫����Ϣ�Ľṹָ�룬�˽ṹ��
                ���ڷ��صڶ�IP��ַ�ģ����صĵ�ַ������dwIpNumָ�����ṹ�е�
                atNetEthParam�����Աֻ��IP ��Mask��Ч, Mac ��ַû��Ч
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
��ע:���ṩ֧�֣���NetGetEthParamAll�ظ�����ȡNetGetEthParamAll�ĵ�2��3������Ի�ȡ����Ӧ��ip
==================================*/
s32 NetGetEthParamSecIP(u32 byEthId, TNetEthParamAll *ptNetEthParamAll);


/*================================
��������NetSetEthParam
���ܣ�������̫������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId����̫���ı�ţ�0 ~ X��X�Ӳ�ͬ���Ӷ�����
                byIpOrMac��Ϊ��������ѡ��(��Netcbb_def.h����صĺ궨��),����
                                     ������IP,�ڶ�IP��Mac.
                                       Net_SET_IP_AND_MASK         1       ����IP��ַ����������
                                       Net_SET_MAC_ADDR            2       ����MAC��ַ(��mac���ܲ�֧�֣���ʵ������)
                                       Net_SET_ETH_ALL_PARAM       3       ������̫����IP��ַ�����������MAC��ַ(��֧��)
                                       Net_SET_ETH_SEC_IP          4       ������̫���ڶ�IP ��ַ
                ptNetEthParam��ָ�����趨ֵ��TNetEthParam���ݽṹ��ָ��
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
==================================*/
s32 NetSetEthParam(u32 byEthId, u32 byIpOrMac, TNetEthParam *ptNetEthParam);


/*================================
��������NetDelEthParamSecIP
���ܣ�ɾ���ڶ�IP��ַ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId����̫���ı�ţ�0 ~ X��X�Ӳ�ͬ���Ӷ�����
                ptNetEthParam��ָ�����趨ֵ��TNetEthParam���ݽṹ��ָ��
                                           �ṹ��ֻ��IP�� Mask��Ч.
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
��ע :���ṩ֧�֣���NetDelEthParamIPAndMask�ظ���
==================================*/
s32 NetDelEthParamSecIP(u32 byEthId, TNetEthParam *ptNetEthParam);


/*================================
��������NetDelEthParamIPAndMask
���ܣ�ɾ��ָ�� IP��ַ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId����̫���ı�ţ�0 ~ X��X�Ӳ�ͬ���Ӷ�����               
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
==================================*/
s32 NetDelEthParamIPAndMask(u32 byEthId, TNetEthParam *ptNetEthParam);


/*================================
��������NetDelEthParam
���ܣ�ɾ��ָ������̫���ӿ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  byEthId����̫���ı�ţ�0 ~ X��X�Ӳ�ͬ���Ӷ�����
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
ע�⣺��Linux�£�һ�����ڿ������ö��IP��ַ���ýӿڻ�ɾ���ýӿ��ϵ�����IP��ַ��
==================================*/
s32 NetDelEthParam(u32 byEthId);


/*================================
��������NetSetDefGateway
���ܣ�����Ĭ������ip
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����  dwGateway��Ĭ������ip��ַ�������ͣ�������
����ֵ˵���� ������ERROR���ɹ�����OK��ERROR = -1 ; OK = 0
==================================*/
s32 NetSetDefGateway(u32 byEthId, u32 dwGateway);

/*================================
��������NetGetDefGateway
���ܣ���ȡĬ������ip
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵���� ��
����ֵ˵���� ���󷵻�ERROR=-1���ɹ�����OK=0
==================================*/
 s32 NetGetDefGateway(u32 *pdwGateway);

/*================================
��������NetDelDefGateway
���ܣ�ɾ��Ĭ������ip
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵���� ��
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK ERROR = -1 ; OK = 0
==================================*/
s32 NetDelDefGateway(void);

/*================================
��������NetGetNextHopIpAddr
���ܣ���ȡͨ��ָ��ip�ĵ�һ��·��ip��ַ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwDstIpAddr��Ŀ��ip��ַ�������ͣ�������
		    dwDstMask��Ŀ�����룬�����ͣ�������
����ֵ˵���� �ɹ����ص�һ��·��ip��ַ��������
��ע : �ݲ�֧�֣����岻��ʵ�ֽ��鷳����ȫ������NetPing ���жϵ�ַ�Ƿ���Ե��
==================================*/
u32 NetGetNextHopIpAddr(u32 dwDstIpAddr,u32 dwDstMask);

/*================================
��������NetAddOneIpRoute
���ܣ�����һ��·
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptNetIpRouteParam��ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK. ERROR = -1 ; OK = 0
==================================*/
s32 NetAddOneIpRoute(u32 byEthId, TNetIpRouteParam *ptNetIpRouteParam);

/*================================
��������NetDelOneIpRoute
���ܣ�ɾ��һ��·
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptNetIpRouteParam��ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK
==================================*/
s32 NetDelOneIpRoute(u32 byEthId, TNetIpRouteParam *ptNetIpRouteParam);

/*================================
��������NetGetAllIpRoute
���ܣ���ȡ����·����Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptNetAllIpRouteInfo��ָ���ŷ���·����Ϣ��TNetAllIpRouteInfo�ṹָ��
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK. ERROR = -1 ; OK = 0
==================================*/
s32 NetGetAllIpRoute(TNetAllIpRouteInfo *ptNetAllIpRouteInfo);

/*================================
��������NetIpConflictCallBackReg
���ܣ�ע��ip��ַ��ͻʱ�ص�����,���豸��IP��ַ���ⲿ�豸��ͻʱ������øú���֪ͨҵ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptFunc��ִ��ҵ�����ע��Ļص�����ָ��
����ֵ˵���� ���󷵻�ERROR���ɹ�����OK. ERROR = -1 ; OK = 0
==================================*/
s32 NetIpConflictCallBackReg (TIpConflictCallBack  ptFunc);

/*================================
��������NetIpOnceConflicted
���ܣ���ѯϵͳ�Ƿ�����ip��ַ��ͻ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵������
����ֵ˵���� TRUE or FALSE
==================================*/
BOOL32 NetIpOnceConflicted (void);

/*================================
��������NetPing
���ܣ���̫��ping�ӿ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����pchDestIP:Ping��Ŀ��IP��ַ��Ϊ���ʮ����
              ptPingOpt��Ping�Ĳ����ṹ��ָ��
              nUserID:�û�ID��־���û����ֲ�ͬ���û�����
              ptCallBackFunc:Ping����Ļص�����
����ֵ˵���� TRUE--����Ĳ����Ϸ����ú������óɹ������Ƿ�pingͨ��Ҫ�û�ע��Ļص��������ж�
             FALSE--����Ĳ����Ƿ����ú�������ʧ��
==================================*/
BOOL32 NetPing(char* pchDestIP,TPingOpt* ptPingOpt,s32 nUserID,TPingCallBack ptCallBackFunc);

/*================================
��������NetSetDscp
���ܣ�����ip��ͷdscpֵ(0-63)
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����nSockfd ; Ҫ���õ��׽���������
              byDscp ; Ҫ���õ�dscpֵ(0-63)
����ֵ˵���� OK/ERROR ERROR = -1 ; OK = 0
             OK �ɹ�; ERROR ʧ��
==================================*/
s32 NetSetDscp(s32 nSockfd, u8 byDscp);

/*================================
��������NetInterfaceShutdown
���ܣ��ر���ѡ�ӿ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����byEthId����̫���ı��		

����ֵ˵���� OK/ERROR ERROR = -1 ; OK = 0
==================================*/
s32 NetInterfaceShutdown(u32 byEthId);

/*================================
��������NetInterfaceNoShutdown
���ܣ�����ѡ�ӿ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����byEthId����̫���ı��			

����ֵ˵���� OK/ERROR ERROR = -1 ; OK = 0
==================================*/
s32 NetInterfaceNoShutdown(u32 byEthId);

/*================================
��������NetCheckTheSameNet
���ܣ�У���������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwIpAddr   :  ip ��ַ
              dwMask     :  ����
              dwGateway  :  ����

����ֵ˵���� OK : У��ɹ�, ��ͬһ������
             NET_NOT_THE_SAME_NET  : ����ͬһ������
             NET_INVALID_PARAMETER : �����������
==================================*/
s32 NetCheckTheSameNet(u32 dwIpAddr, u32 dwMask,u32 dwGateway);

/*================================
��������NetGetEthNum
���ܣ������������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵���� *pnEthNum: ָ����Ҫ��ȡ�Ķ˿ں�
����ֵ˵���� OK                �ɹ�
                                     ERROR          ʧ��
==================================*/
s32 NetGetEthNum(s32 *pnEthNum);
#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /*_NETCBB_INTERFACE_H_*/
