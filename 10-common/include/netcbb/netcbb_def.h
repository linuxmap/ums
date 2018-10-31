#ifndef _NETCBB_DEF_H_
#define _NETCBB_DEF_H_
#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

/*api ����ֵ�����붨�壬���еķ���ֵ���Ѿ�ͳһ��ҵ����Դ���һ��������������ֵ������ͷ�ļ�������һһ����*/
#define NET_BASE_ERROR				1100
#define NET_IF_BASE_ERROR			    	1200
#define NET_E1_BASE_ERROR			1300

/*������4��TIMEOUT����ֵ�����Բ�ȡ��Ӧ�Ĵ�ʩ,�������µ��ö�Ӧ�������ߺ��ԡ�*/
#define NET_IPC_SENDC_TIMEOUT			NET_BASE_ERROR+1		/*client ������Ϣ��ʱ*/
#define NET_IPC_RECVC_TIMEOUT			NET_BASE_ERROR+2		/*client ������Ϣ��ʱ*/
#define NET_IPC_SENDD_TIMEOUT			NET_BASE_ERROR+3		/*daemon������Ϣ��ʱ*/
#define NET_IPC_RECVD_TIMEOUT			NET_BASE_ERROR+4		/*daemon������Ϣ��ʱ*/
#define NET_INVALID_PARAMETER			NET_BASE_ERROR+5		/*��Ч�Ĳ���*/
#define NET_CALLBACK_NULL			    NET_BASE_ERROR+6		/*�ص�����û�ж���*/
#define NET_FORK_ERROR				    NET_BASE_ERROR+7		/*�����ӽ���ʧ��*/
#define NET_PROCESS_NOT_EXIST		    NET_BASE_ERROR+8		/*���̲�����*/
#define NET_MODULE_INIT_ERROR			NET_BASE_ERROR+9		/*ģ������ʧ��*/
#define NET_GET_MODULE_INFO_ERROR 	    NET_BASE_ERROR+10		/*��ȡģ����Ϣʧ��*/
#define NET_NOT_THE_SAME_NET 	        NET_BASE_ERROR+11		/*�����������ͬһ������*/ 
		

#define NET_IF_NOT_EXIST 			    NET_IF_BASE_ERROR+1		/*�ӿڲ�����*/ 
#define NET_IF_ADDR_NOT_EXIST           NET_IF_BASE_ERROR+2     /*��ַ������*/





#define IP_ROUTE_MAX_NUM 		        10
#define IP_ADDR_MAX_NUM	                16                      /*��Linux��һ�����ڿ������õ�����IP��ַ*/
#define NET_MAX_VERSION_LEN	            255		                /*�汾�ŵ���󳤶�*/		


/* NetSetEthParam������byIpOrMac����ֵ�ĺ궨�� */
#define Net_SET_IP_AND_MASK         1      /* ����IP��ַ���������� */
#define Net_SET_MAC_ADDR            2      /* ����MAC��ַ */
#define Net_SET_ETH_ALL_PARAM       3      /* ������̫����IP��ַ�����������MAC��ַ */
#define Net_SET_ETH_SEC_IP          4      /* ������̫���ڶ�IP ��ַ */


#define NET_DEF_FILE_PATH_LEN			100
#define NET_DEF_FILE_LEN				32
#define NET_DEF_STR_LEN				32
#define NET_DEF_STR_LEN_LONGER		100

#ifdef __cplusplus 
} 
#endif /* __cplusplus */
#endif
