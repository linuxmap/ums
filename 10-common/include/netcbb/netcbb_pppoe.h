/******************************************************************************
ģ����  �� PPPOE
�ļ���  �� pppoeModule.h
����ļ���
�ļ�ʵ�ֹ��ܣ�PPPOEģ�����Ҫͷ�ļ�
����    ��������
�汾    ��1.0.0.0.0
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
05/09/2005  1.0         ������      ����
******************************************************************************/
/*#ifndef _DAVINCI_  ����arm�°������ļ���������²�����*/

#ifndef _NETCBB_PPPOE_H_
#define _NETCBB_PPPOE_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

//#include "kdvtype.h"

/*��غ궨��*/

/*PPPOEģ��İ汾�Ŷ���*/
#define PPPOE_VERSION               "2.4.5"

/*��PPPOEģ��������Debugģʽʱ��һЩ��Ҫ��Ϣ������ļ�·��*/
#define PPPOE_DUMP_FILE             "/ramdisk/pppoeDump.txt"

/*��PPPOEģ�����־�ļ�·��*/
#define PPPOE_LOG_FILE              "/ramdisk/pppoelog.txt"

/*PPPOE����ʱʹ�õ��û�������󳤶�*/
#define MAX_USENAME_LEN             (u16)255

/*PPPOE����ʱʹ�õ��������󳤶�*/
#define MAX_PASSWORD_LEN            (u16)255

/*PPPOE����ʱʹ�õ�ָ��ISP���������ֵ���󳤶�*/
#define MAX_SERVERNAME_LEN          (u16)255


/*PPPOE�汾��Ϣ����󳤶�*/
#define MAX_VERSION_LEN             (u16)255


/*��С���ų��Դ���*/
#define MIN_DIAL_RETRY              (u16)1

/*��󲦺ų��Դ���*/
#define MAX_DIAL_RETRY              (u16)10

/*Ĭ�ϵĲ��ų��Դ����������ô�������Ϊ����ʧ��*/
#define DEFAULT_DIAL_RETRY          (u16)3

/*��С�ķ���lcp-echo��ʱ����*/
#define MIN_LCP_ECHO_INTERVAL       (u16)1

/*���ķ���lcp-echo��ʱ����*/
#define MAX_LCP_ECHO_INTERVAL       (u16)255

/*���ӽ����Ժ󣬷���LCP-ECHO����Ĭ��ʱ����(��λ����)*/
#define DEFAULT_LCPECHO_INTERVAL    (u16)20

/*��С��lco-echo��ʱ����*/
#define MIN_LCPECHO_TIMEOUT         (u16)1

/*����lco-echo��ʱ����*/
#define MAX_LCPECHO_TIMEOUT         (u16)255

/*���ӽ����Ժ󣬷���LCP-ECHO����Ĭ�ϳ�ʱ��ʱ*/
#define DEFAULT_LCPECHO_TIMEOUT     (u16)3

/*��С���Զ�����ʱ����*/
#define MIN_AUTODIAL_INTERVAL       (u16)0

/*�����Զ�����ʱ����*/
#define MAX_AUTODIAL_INTERVAL       (u16)10

/*�������ٴ��Զ����ŵ�Ĭ�ϵȴ�ʱ��(��λ����)*/
#define DEFAULT_AUTODIAL_INTERVAL   (u16)1

/*�ϲ�ҵ��������PPPOEģ��ӿ�ʱ������ֵͳһ����*/
/*���óɹ�ʱ�ķ���ֵ*/
#define PPPOE_OK                    (u16)0

/*û��ָ���û���ʱ�ķ���ֵ*/
#define PPPOE_INIT_NO_USERNAME      (u16)1

/*û��ָ����½����ʱ�ķ���ֵ*/
#define PPPOE_INIT_NO_PASSWORD      (u16)2

/*��ʼ��ʱ����Ĳ������������Сֵ��Χ֮��*/
#define PPPOE_INIT_PARAM_INVALIDE   (u16)3

/*û�г�ʼ��*/
#define PPPOE_START_NO_INIT         (u16)4

/*û��ע��ص�����*/
#define PPPOE_START_NO_REGCALLBACK  (u16)5

/*ע��Ļص�����Ϊ��ָ��*/
#define PPPOE_CALLBACK_NULL         (u16)6

/*û�п���PPPOE����*/
#define PPPOE_NOT_RUNNING           (u16)7

/*��ȡ�汾��Ϣʱ�����ָ��ΪNULL*/
#define PPPOE_PARAMETER_NULL        (u16)8

/*�����ܵ�ʧ��*/
#define PPPOE_CREAT_PIPE_FAILED     (u16)9

/*�����ӽ���ʧ��*/
#define PPPOE_CREAT_PROGRESS_FAILED (u16)10


/*ע�⣺�ϲ�ҵ����������յ���Щ��Ϣ�Ļص������н��й���Ĵ���Ӧ�þ��췵�أ�
�����ܵ���pppoeģ���PppoeStart()��PppoeStop()������������������*/

/*PPPOEģ������ϲ�ҵ�����ע��Ļص���������֪ͨ��Ϣ����ϢID�Ŷ���*/
/*��ϢID�Ļ�ַ--------����1ǧ����Ϣ���ԣ�9000--10000��*/
#define PPPOE_MSG_BASE              (u32)9000

/*��Ϊ�û����������벻��ȷ�����PPPOEģ�鲦�������֤ʧ�ܵ�֪ͨ��Ϣ*/
/*��Ϣ����--- �ṹ��TAuthFailed*/
#define PPPOE_AUTH_FAILED_MSG       (u32)(PPPOE_MSG_BASE + 1)
	
/*���ų�ʱ֪ͨ��Ϣ*/
/*��Ϣ����--- ��*/
#define PPPOE_DIAL_TIMEOUT_MSG      (u32)(PPPOE_MSG_BASE + 2)

/*����֪ͨ��Ϣ,��Ϣ�������»�õ�IP��ַ*/
/*��Ϣ����--- �ṹ��TConnNotify*/
#define PPPOE_LINK_UP_MSG           (u32)(PPPOE_MSG_BASE + 3)

/*����֪ͨ��Ϣ*/
/*��Ϣ����--- ��*/
#define PPPOE_LINK_DOWN_MSG         (u32)(PPPOE_MSG_BASE + 4)

/*�Ҳ���ָ����ISP������֪ͨ��Ϣ*/
/*��Ϣ����--- �ṹ�� TNoServer*/
#define PPPOE_NO_REQUIREDSERVER_MSG (u32)(PPPOE_MSG_BASE + 5)
#define PPPOE_DIALING_MSG		(u32)(PPPOE_MSG_BASE + 6)

/*�Ҳ�������������ʱ�����*/
#define PPPOE_GENERAL_SERVER_ERROR_MSG     (u32)(PPPOE_MSG_BASE + 7)
	
/**************************************************************/
/*��ؽṹ�嶨��*/

/*�ϲ�ҵ������ʼ��PPPOEģ��ʱʹ�õĽṹ��*/
typedef struct  PppoeInitParam{
    char      abyUserName [MAX_USENAME_LEN];/*����ʱʹ�õ��û���,������*/
    char      abyPassword [MAX_PASSWORD_LEN]; /*����ʱʹ�õ�����,������*/
    char      abyServerName[MAX_SERVERNAME_LEN];/*ָ�����ŷ����̵�����,���Բ���*/
    BOOL32    bAutoDialEnable;/*�Ƿ�����������Զ�����,Ĭ�ϲ��Զ�����,ֻ�������Զ����ź��ز��������ز�ʱ��������塣������Ч*/
    BOOL32    bDefaultRouteEnable;/*�Ƿ������Զ˵ĵ�ַ��ΪĬ�����أ�Ĭ�ϲ���Ϊ����*/
    BOOL32    bDebug;/*�Ƿ���debugģʽ����pppoe��Ĭ�ϲ�������debugģʽ*/
    u32       dwAutoDialInterval;/*�������ٴ��Զ�������Ҫ�ȴ���ʱ�䣨�������ó�0s��*/
    u16       wDialRetryTimes;/*���ų��ԵĴ���������ﵽ�ô�����û����Ӧ�򲦺�ʧ��,Ĭ��Ϊ10��Ϊ0�������Ʋ���*/
    u16       wLcpEchoSendInterval;/*���ӽ����󣬷���LCP-ECHO����ʱ����,Ĭ������Ϊ20*/
    u16       wLcpEchoRetryTimes;/* ���ͼ���LCP-ECHO��û�еõ���Ӧ����Ϊ���ӶϿ�,Ĭ������Ϊ3*/
    u32       dwEthID;/*PPPOE������Ҫ�󶨵���̫����ID�ţ���0��ʼ��*/
}TPppoeInitParam;



/*�ϲ�ҵ�����ע��Ļص����Ͷ���*/
/*����˵����u32 dwMsgID---��Ϣ��ID��,��PPPOEģ�����
                u8 *pbyMsg -----ָ����Ϣ���ݵ�ָ��,��PPPOEģ�����
                u32 dwMsgLen����Ϣ���ݵ���Ч����,��PPPOEģ�����*/
typedef void ( *TPppoeCallBack )( u32 dwMsgID,u8 *pbyMsg,u32 dwMsgLen );


/*�й�PPPOEģ�����ͳ����Ϣ�Ľṹ��*/
typedef struct PppoeStates{
    BOOL32  bPppoeRunning;/*PPPOE�Ƿ����У�TRUR�����У�FALSE��û������*/
    u32     dwLocalIpAddr;/*����IP��ַ,������*/
    u32     dwPeerIpAddr;/*�Զ�IP��ַ,������*/
    char    abyServerName[MAX_SERVERNAME_LEN];/*ISP Server������*/
    u32     dwLinkKeepTimes;/*��·������ʱ��*/
    u32     dwLinkDownTimes;/*��·�����Ĵ���ͳ��*/
    u32     dwPktsSend;/*�ܹ����͵����ݰ���--��������Э����Լ��ϲ�ҵ���������ݰ�*/
    u32     dwPktsRecv;/*�ܹ����յ����ݰ���*/
    u32     dwBytesSend;/*�ܹ����͵��ֽ���*/
    u32     dwBytesRecv;/*�ܹ����յ��ֽ���*/
}TPppoeStates;

/*�����ϲ�ҵ�����ע��Ļص�����������֤ʧ��ʱ��Ϣ�����ݽṹ��*/
typedef struct AuthFailed{
    char      abyUserName [MAX_USENAME_LEN];/*ҵ�������Ĳ���ʱʹ�õ��û���*/
    char      abyPassword [MAX_PASSWORD_LEN]; /*ҵ�������Ĳ���ʱʹ�õ����� */
}TAuthFailed;

/*�����ϲ�ҵ�����ע��Ļص��������ͽ���֪ͨ��Ϣ�Ľṹ��*/
typedef struct ConnNotify{
    u32     dwOurIpAddr;/*���ϻ�õ�IP��ַ,������*/
    u32     dwPeerIpAddr;/*�Զ˵�IP��ַ*/
    u32     dwDnsServer1;/*DNS Server1,������*/
    u32     dwDnsServer2;/*DNS Server1,������*/
}TConnNotify;

/*֪ͨҵ������Ҳ���ָ����ISP Server����Ϣ�ṹ��*/
typedef struct NoServer{
    char      abyServerName[MAX_SERVERNAME_LEN];/*ISP Server������*/
}TNoServer;

/*�洢PPPOE�汾��Ϣ�Ľṹ��*/
typedef struct Version{
    char      abyVersion[MAX_VERSION_LEN];
}TVersion;



/*��������*/
/*================================
��������PppoeStart
���ܣ�����PPPoE����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����gtPppoeInitParam
�������˵������ 
����ֵ˵����OK
			  ERROR
			  �ο�netcbb_def.h
��ע: ԭPppoeInit��PppoeCallBackReg��������NetPppoeStart��			  
==================================*/
s32 NetPppoeStart (TPppoeInitParam *ptPppoeInitParam, TPppoeCallBack ptNotifyCallBack);

/*================================
��������PppoeStop
���ܣ�ֹͣPPPoE����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�������
�������˵������ 
����ֵ˵����#define PPPOE_ OK						0
			#define PPPOE_NOT_RUNNING				6
==================================*/
s32 NetPppoeStop (void);

/*================================
��������PppoeStatesDump
���ܣ���ȡPPPoEģ���ͳ����Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�������
�������˵����TPppoeStates	*ptPppoeStates---ָ����ͳ�ƽ����ָ�� 
����ֵ˵���� ��
��ע: ���ṩ֧��
==================================*/
void NetPppoeStatesDump (TPppoeStates	*ptPppoeStates);

/*================================
��������Pppoever
���ܣ���ȡPPPoEģ��İ汾��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�������
�������˵����TVersion *ptVersion---ָ���Ű汾��Ϣ��ָ��
����ֵ˵����#define OK				       
			#define 	ERROR
==================================*/
s32 NetPppoeVer (TVersion *ptVersion);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /*_NETCBB_PPPOE_H_*/
