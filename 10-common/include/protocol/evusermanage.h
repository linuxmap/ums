/*****************************************************************************
   ģ����      : �û�����
   �ļ���      : umev.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: �û�������Ϣ����
   ����        : zhangsh
   �汾        : V0.9  Copyright(C) 2001-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2003/11/25  1.0         zhangsh        ����
******************************************************************************/
#ifndef _UMEV_H_
#define _UMEV_H_

#include "osp.h"
#include "eventid.h"
/**********************************************************
 ����Ϊ��¼��Ϣ
************************************CLogin**********************/
//�ͻ��������¼��Ϣ,��Ϣ��ΪCLoginRequest
OSPEVENT(MCS_UM_LOGIN_REQ,	EV_UM_BGN);
//�ͻ��������¼ȷ��Ӧ��,��Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_LOGIN_ACK,	EV_UM_BGN+1);
//�ͻ��������¼�ܾ�Ӧ��,��Ϣ��Ϊ�����[u32]
OSPEVENT(UM_MCS_LOGIN_NACK,	EV_UM_BGN+2);
/**********************************************************
 ����Ϊ����û���Ϣ
**********************************************************/
//�ͻ�������û�����,��Ϣ��ΪCUserFullInfo
OSPEVENT(MCS_UM_ADDUSER_REQ,	EV_UM_BGN+3);
//�ͻ�������û�ȷ�ϣ���Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_ADDUSER_ACK,	EV_UM_BGN+4);
//�ͻ�������û��ܾ�����Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_ADDUSER_NACK,	EV_UM_BGN+5);
/**********************************************************
 ����Ϊɾ���û���Ϣ
**********************************************************/
//�ͻ���ɾ���û�����,��Ϣ��ΪCUserFullInfo
OSPEVENT(MCS_UM_DELUSER_REQ,	EV_UM_BGN+6);
//�ͻ���ɾ���û�ȷ�ϣ���Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_DELUSER_ACK,	EV_UM_BGN+7);
//�ͻ���ɾ���û��ܾ�����Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_DELUSER_NACK,	EV_UM_BGN+8);
/**********************************************************
 ����Ϊ�����û���Ϣ��Ϣ
**********************************************************/
//�ͻ��˸����û���Ϣ����,��Ϣ��Ϊ���û���ϢCUserFullInfo
OSPEVENT(MCS_UM_CHANGEPWD_REQ,	EV_UM_BGN+9);
//�ͻ��˸����û���ϢӦ��,��Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_CHANGEPWD_ACK,	EV_UM_BGN+10);
//�ͻ��˸����û���Ϣ�ܾ�,��Ϣ��ΪCUserFullInfo
OSPEVENT(UM_MCS_CHANGEPWD_NACK,	EV_UM_BGN+11);
/**********************************************************
 ����Ϊ�õ������û���Ϣ
**********************************************************/
////�ͻ��˵õ������û���Ϣ������Ϣ���
OSPEVENT(MCS_UM_GETALLUSER_REQ,	EV_UM_BGN+12);
////�ͻ��˵õ������û���Ϣȷ�ϣ���Ϣ���
OSPEVENT(UM_MCS_GETALLUSER_ACK,	EV_UM_BGN+13);
////�ͻ��˵õ������û���Ϣ�ܾ�����Ϣ������
OSPEVENT(UM_MCS_GETALLUSER_NACK,EV_UM_BGN+14);
//�ͻ��˵õ������û���Ϣȷ�ϣ���Ϣ��ΪCLongMessage+15*CUserFullInfo
OSPEVENT(UM_MCS_GETALLUSER_NOTIF,EV_UM_BGN+15);
////�ͻ���ɾ�������û�����
OSPEVENT(MCS_UM_DELUSERALL_REQ,EV_UM_BGN+16);
////�ͻ���ɾ�������û�ȷ��
OSPEVENT(MCS_UM_DELUSERALL_ACK,EV_UM_BGN+17);
////�ͻ���ɾ�������û��ܾ�
OSPEVENT(MCS_UM_DELUSERALL_NACK,EV_UM_BGN+18);
//�û������ʼ������
OSPEVENT(MCS_UM_INIT_CMD,EV_UM_BGN+19);

#endif
