/*=============================================================================
ģ   ��   ��: ���ܷ�������ѯ�ⶨ��
��   ��   ��: nmsinttestcom.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: ��Ϣ����/�ṹ����
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2005/07/26  4.0     ���        ����
=============================================================================*/

#ifndef _NMSINTTESTCOM_20050726_H_
#define _NMSINTTESTCOM_20050726_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvtype.h"
#include "eventid.h"

#define EV_SVR_TEST_REQ         (u8)(EV_TEST_SVR_BGN + 1)   //��ѯͬ���������ؽ��
#define EV_SVR_TEST_QRY         (u8)(EV_TEST_SVR_BGN + 2)

#define SVR_QUERY_EQP_STAMP         (u8)1   //����豸�ĸ澯ʱ��� u32
#define SVR_QUERY_EQP_LINK          (u8)2   //����豸����·״̬ u8
#define	SVR_QUERY_CONFIG            (u8)3   //���������ò�ѯ TSvrConfig
#define SVR_QUERY_TIME              (u8)4   //���ϵͳ��ǰʱ���Ƿ��ָ��ʱ����� time_t
#define SVR_QUERY_EQP_ISEXIST       (u8)5   //����豸�Ƿ���� BOOL32
#define SVR_QUERY_CMD_RET           (u8)6   //��ѯ�ϴβ����Ľ�� u32
#define SVR_QUERY_ALLUSERNAME       (u8)7   //��ѯ�����û��� �û�������
#define SVR_QUERY_EQP_VER           (u8)8   //��ѯ�豸�汾�� �汾���ַ���

#define SVR_START_CM_LOOP_CMD       (u8)20  //��ʼ������ѯ
#define SVR_STOP_CM_LOOP_CMD        (u8)21  //ֹͣ������ѯ
#define SVR_START_FM_LOOP_CMD       (u8)22  //��ʼ�澯��ѯ
#define SVR_STOP_FM_LOOP_CMD        (u8)23  //ֹͣ�澯��ѯ

#endif  //  _NMSINTTESTCOM_20050726_H_