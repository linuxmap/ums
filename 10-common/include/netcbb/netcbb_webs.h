/******************************************************************************
ģ����  �� WEB SERVER
�ļ���  �� boardwebs.h
����ļ���
�ļ�ʵ�ֹ��ܣ�WEB-SERVERģ������ṩ�ĺ궨��ͷ�ļ�
����    ��zhanka
�汾    ��1.0.0.0.0
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
08/17/2007  1.0         zhanka      ����
******************************************************************************/
#ifndef _NETCBB_WEBS_H_
#define NETCBB_WEBS_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#define NET_WEBS_ENABLE 1
#define NET_WEBS_DISABLE 2

#define NET_WEBS_INSPECT_ENABLE 3
#define NET_WEBS_INSPECT_DISABLE 4

#define NET_WEBS_ERR_BASE 100
//����ֵ����
#define NET_WEBS_PORT_ERR   NET_WEBS_ERR_BASE+1	//�˿ڰ󶨳���
/*================================
��������NetWebsEnable
���ܣ�������ֹͣweb server
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwEnable :BRD_WEBS_ENABLE ����
                       :BRD_WEBS_DISABLE ֹͣ
����ֵ˵���� OK/ERROR
��ע: port ֵֻ��ʹ�ü򻯰汾��httpd��Ч����ligthttpd����Ч.
==================================*/
s32 NetWebsEnable(s32 port);

/*================================
��������NetWebsEnable
���ܣ�������ֹͣweb server
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����dwEnable :BRD_WEBS_ENABLE ����
                       :BRD_WEBS_DISABLE ֹͣ
����ֵ˵���� OK/ERROR
==================================*/
s32 NetWebsDisable(void);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* _NETCBB_WEBS_H_ */

