/******************************************************************************
ģ����  �� DHCP-CLIENT
�ļ���  �� boardsntp.h
����ļ���
�ļ�ʵ�ֹ��ܣ�SNTP-CLIENTģ������ṩ�ĺ궨��ͷ�ļ�
����    ��������
�汾    ��1.0.0.0.0
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
07/14/2006  1.0         ������      ����
******************************************************************************/
#ifndef _NETCBB_SNTP_H_
#define _NETCBB_SNTP_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */


/*�궨��*/

/*������SNTP-Servr����ʱ��ͬ����ʱ��������Сֵ*/
#define SNTP_INTERVEL_MIN                       (u32)64
/*������SNTP-Servr����ʱ��ͬ����ʱ���������ֵ*/
#define SNTP_INTERVEL_MAX                       (u32)1024
 

/*SNTP�е���������SNTP-Serverͬ��ʱ��ʱ�ص���������Ϣ���ַ*/
#define SNTP_MSG_BASE			                (u32)40000
/*��SNTP-Serverͬ��ʱ��Уʱ�ɹ�����Ϣ�壺��*/
#define SNTP_SYNC_TIME_SUCCESS_MSG				(u32)( SNTP_MSG_BASE+1)
/*��SNTP-Serverͬ��ʱ��Уʱʧ�ܣ���Ϣ�壺��*/
#define SNTP_SYNC_TIME_FAILED_MSG				(u32)( SNTP_MSG_BASE+2)

/*�ص��������Ͷ���*/

/*================================
��������NetSNTPSyncTimeCallBack
���ܣ�������ͬ��SNTP-Serverͬ��ϵͳʱ��ʱ��֪ͨ�û���������Ļص�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwMsgID���¼����ͣ����������Ϣ���Ͷ���
		      pMsg������¼�������ƥ�����Ϣ���ݣ�Ŀǰ������ΪNULL���Ժ����
			  ��չ
����ֵ˵���� ��ʱ����Ϊ0���Ժ������չ
==================================*/
typedef int(*NetSNTPSyncTimeCallBack)(u32  dwMsgID ,void*  pMsg);


/*�����ӿڶ���*/

/*================================
��������NetSNTPStart
���ܣ�����SNTP-Client�˹���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwServerIp�� SNTP-Server��IP��ַ�������ֽ���
		                          dwSyncTimeInterval����SNTP-Server����ʱ��ͬ����ʱ������
		                          ����Ϊ��λ����Χ��64s~1024s�������ù���֮�󣬵ײ�
		                          �ᰴ���û����õ�ʱ������ÿ��һ��ʱ�����
		                          SNTP-Serverͬ��ϵͳʱ�䲢���õ�����ϵͳ��
����ֵ˵���� OK/ERROR
��ע: ���ṩ֧��
==================================*/
s32 NetSNTPStart(u32  dwServerIp,  u32  dwSyncTimeInterval,NetSNTPSyncTimeCallBack  ptCallBack);


/*================================
��������NetSNTPStop
���ܣ��ر�SNTP-Client�˹���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵������
����ֵ˵���� OK/ERROR
��ע: ���ṩ֧��
==================================*/
s32 NetSNTPStop (void);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /*_NETCBB_SNTP_H_*/
