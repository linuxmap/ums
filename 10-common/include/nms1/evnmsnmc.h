/*=============================================================================
ģ   ��   ��: ���ܷ�����
��   ��   ��: evnmsnmc.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: NMS-NMC��Ϣ����
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2005/09/07  4.0     ���        ����
=============================================================================*/

#ifndef _EVNMSNMC_20050907_H_
#define _EVNMSNMC_20050907_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "eventid.h"

//�������Ϳͻ��˽�����Ϣ

//������������
OSPEVENT( EV_CLT_OPER_REQ,                      EV_CLTSVR_BGN + 0 );
//����������
OSPEVENT( EV_CLT_OPER_RET,                      EV_CLTSVR_BGN + 1 );

//�¿ͻ��˽�������
OSPEVENT( EV_CLT_NEWSESSION_REQ,                EV_CLTSVR_BGN + 2 );
//����������
OSPEVENT( EV_CLT_NEWSESSION_RET,                EV_CLTSVR_BGN + 3 );

//�ͻ����˳�����
OSPEVENT( EV_CLT_QUIT_REQ,                      EV_CLTSVR_BGN + 4 );
//�˳��������
OSPEVENT( EV_CLT_QUIT_RET,                      EV_CLTSVR_BGN + 5 );

//�澯�㲥��Ϣ
OSPEVENT( EV_BC_FM_ALARM,                       EV_CLTSVR_BGN + 6 );

//���øı�ˢ�¹㲥��Ϣ
OSPEVENT( EV_BC_CM_REFRESH,                     EV_CLTSVR_BGN + 7 );

//��������ǰ̨��·�ı�㲥��Ϣ
OSPEVENT( EV_BC_CM_LINKCHANGE,                  EV_CLTSVR_BGN + 8 );

//����״̬�㲥��Ϣ
OSPEVENT( EV_BC_CM_BOARD_STATUS,                EV_CLTSVR_BGN + 9 );

//�������˳�
OSPEVENT( EV_SRV_QUIT,                          EV_CLTSVR_BGN + 10 );

//ֹͣFTP
OSPEVENT( EV_CLT_STOP_FTP,                      EV_CLTSVR_BGN + 11 );

//Ftp��չ
OSPEVENT( EV_CLT_FTP_PROC,                      EV_CLTSVR_BGN + 12 );

//���ܹ�����״̬�����ı��¼�, �����������塢ɾ�������
OSPEVENT( EV_CLT_FRAMEWORK_STATUS,              EV_CLTSVR_BGN + 13 );

//�忨״̬�ı�
OSPEVENT( EV_CLT_BOARD_STATUS,                  EV_CLTSVR_BGN + 14 );

//�澯���˸���, �ͻ��˷���������, ����Ҫ����
OSPEVENT( EV_CLT_ALARM_FILTER,                  EV_CLTSVR_BGN + 15 );

    //�豸�ı���¼�
    //һ����˵�����ܿͻ����ڽ������������һ���豸����ɾ����һ���豸��ʱ��
    //Ҫ�����ܷ����������¼�EV_CLT_COMMAND_DEVICE�����ܷ������ڽ��յ���
    //�¼��Ժ󣬸����е����ܿͻ��˷���EV_CLT_BROADCAST_DEVICE��֪ͨ
    //���ھ���ı�����ݣ���CM_EQUIP_ADD��CM_EQUIP_DEL
//���ܿͻ��˷��͸����ܷ��������豸�޸�֪ͨ�����������豸��ɾ���豸��
OSPEVENT( EV_CLT_COMMAND_DEVICE,                EV_CLTSVR_BGN + 16 );
//�����ܷ��������͸����ܿͻ��˵��豸���֪ͨ
OSPEVENT( EV_CLT_BROADCAST_DEVICE,              EV_CLTSVR_BGN + 17 );

    //�û��ı���¼�
    //һ����˵�����ܿͻ����ڽ������������һ���û�����ɾ����һ���û���ʱ��
    //Ҫ�����ܷ����������¼�EV_CLT_COMMAND_USER�����ܷ������ڽ��յ����¼�
    //�Ժ󣬸����е����ܿͻ��˷���EV_CLT_BROADCAST_USER��֪ͨ
    //���ھ���ı�����ݣ���SM_USER_ADD��SM_USER_DEL��
//���ܿͻ��˷��͸����ܷ��������û����֪ͨ�������û������ӡ�ɾ����
OSPEVENT( EV_CLT_COMMAND_USER,                  EV_CLTSVR_BGN + 18 );
//�����ܷ��������͸����ܿͻ��˵��û����֪ͨ
OSPEVENT( EV_CLT_BROADCAST_USER,                EV_CLTSVR_BGN + 19 );

    //��ı���¼�
    //һ����˵�����ܿͻ����ڽ������������һ�������ɾ����һ�����ʱ��
    //Ҫ�����ܷ����������¼�EV_CLT_COMMAND_GROUP�����ܷ������ڽ��յ����¼�
    //�Ժ󣬸����е����ܿͻ��˷���EV_CLT_BROADCAST_GROUP��֪ͨ
    //���ھ���ı�����ݣ���SM_GROUP_ADD��SM_GROUP_DEL��
//���ܿͻ��˷��͸����ܷ��������û����֪ͨ�������û������ӡ�ɾ����
OSPEVENT( EV_CLT_COMMAND_GROUP,                 EV_CLTSVR_BGN + 20 );
//�����ܷ��������͸����ܿͻ��˵��û����֪ͨ
OSPEVENT( EV_CLT_BROADCAST_GROUP,               EV_CLTSVR_BGN + 21 );

//�ͻ��˵õ�������������Ϣ����
OSPEVENT( EV_CLT_GET_SVR_CFG_REQ,               EV_CLTSVR_BGN + 22 );
//��������ͻ��˷����Լ���������Ϣ
OSPEVENT( EV_CLT_GET_SVR_CFG_RET,               EV_CLTSVR_BGN + 23 );

//�ļ�����ʧ��
OSPEVENT( EV_NMS_NMC_UPDATE_FAIL,               EV_CLTSVR_BGN + 25 );


//////////////////////////////////////////////////////////////////////////
//�¼�����,��CNmsMsg���¼���λ
#define UNKNOWN_EVENT       (u8)~0		// δ֪����������
#define EVENT_CTRL_BEGIN    (u8)1
#define COMMON_CM_CTRL      (u8)EVENT_CTRL_BEGIN + 0        // 1��CM��ͨ����
#define FTP_CTRL            (u8)EVENT_CTRL_BEGIN + 1        // 2��Ftp����
#define COMMON_FM_CTRL      (u8)EVENT_CTRL_BEGIN + 2		// 3��FM��ͨ����
#define REMOTE_CTRL         (u8)EVENT_CTRL_BEGIN + 3        // 4��Զ�̿���
#define COMMON_SM_CTRL      (u8)EVENT_CTRL_BEGIN + 4        // 5��SM��ͨ����
#define EVENT_CTRL_END      (u8)127

//�¼�����,��CNmsMsg���¼���λ
//���ÿ��Ʋ�����������
#define CM_SYNC_CONFIG          (u8)1   //����ͬ��
#define CM_SYNC_TIME            (u8)2   //ʱ��ͬ��
#define CM_QUERY_SINGLE_BOARD   (u8)3   //��ѯ����忨��Ϣ
#define CM_QUERY_VERSION        (u8)4  //��ѯ����汾�� 

//Ftp���Ʋ�����������
#define FTP_PUT_FILE        (u8)1       // �ϴ��ļ�
#define FTP_GET_FILE        (u8)2       // �����ļ�
#define FTP_FILE_RENAME     (u8)3       // �ϴ������ļ���, ֪ͨ�ն��޸��ļ���

//���Ͽ��Ʋ�����������
#define FM_SYNC_ALARM       (u8)1       // �澯ͬ��

//��ȫ���Ʋ�����������
#define SM_PASSWORD_CHANGE  (u8)1       // �޸�����

//Զ�̿��Ʋ�����������
#define RPC_RESTART         (u8)1   //����
#define RPC_STOP            (u8)2   //ֹͣ
#define RPC_SELFTEST        (u8)3   //�Լ�
#define RPC_BITERRTEST      (u8)4   //�������

//����
#define BOARD_REMOTE_RESTART    (u8)10  //���帴λ
#define BOARD_SYNC_TIME         (u8)11  //����ʱ��ͬ��
#define BOARD_BIRERROR_TEST     (u8)12  //�����������
#define BOARD_SEL_TEST          (u8)13  //�����Բ�
#define BOARD_E1LINK_CFG        (u8)14  //E1��·����

//////////////////////////////////////////////////////////////////////////

// �豸�㲥�����豸���޸�
#define CM_DEVICE_ADD       (u8)1   // ����һ���豸
#define CM_DEVICE_DEL       (u8)2   // ɾ��һ���豸
#define CM_DEVICE_MODIFY    (u8)3   // �޸��豸

// �û��㲥�����û��ı��
#define SM_USER_ADD         (u8)1   // ����һ���û�
#define SM_USER_DEL         (u8)2   // ɾ��һ���û�
#define SM_USER_MODIFY      (u8)3   // �޸��û�����
#define SM_USER_LINK        (u8)4   // �û����齨������
#define SM_USER_UNLINK      (u8)5   // ��������

// ��㲥������ı��
#define SM_GROUP_ADD        (u8)1   // ����һ����
#define SM_GROUP_DEL        (u8)2   // ɾ��һ����
#define SM_GROUP_MODIFY     (u8)3   // �޸�������
#define SM_GROUP_ASSIGN     (u8)4   // ����ӳ�Ա�û�
#define SM_GROUP_UNASSIGN   (u8)5   // ɾ����Ա�û�
#define SM_GROUP_PRIV_ADD   (u8)6   // �û����Ȩ��
#define SM_GROUP_PRIV_DEL   (u8)7   // �û�ɾ��Ȩ��

#endif  //  _EVNMSNMC_20050907_H_