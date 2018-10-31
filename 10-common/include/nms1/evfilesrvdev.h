/*=======================================================================
ģ����      : �ļ�����������
�ļ���      : evfilesrvdev.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ���������ն˽�������Ϣ����
����        : ���
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/28  1.0     ���    ����
=======================================================================*/

#ifndef _EVFILESRVDEV_H
#define _EVFILESRVDEV_H

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif//WIN32

#include "osp.h"
#include "eventid.h"

// #define EV_FILESRVDEV_BEGIN                         (u16)39100

/*------------------------------------------------------------------------------
  �ļ��������������豸(MCU/MT/����)ҵ����Ϣ(39101-39200)
------------------------------------------------------------------------------*/

//1.1	��������

//1.1.1	ע��
    //�豸֪ͨServer�����ӣ�����׼�룬��Ϣ�壺IDevLoginInfo
    OSPEVENT( DEV_FILESRV_LOGIN_REQ,          EV_FILESRVDEV_BGN + 1 );
    //Server׼��Ӧ����Ϣ�壺u32(Server����ţ������򣬸��豸�ĺ�����Ϣ����д)
    OSPEVENT( FILESRV_DEV_LOGIN_ACK,          EV_FILESRVDEV_BGN + 2 );
    //Server�ܾ�Ӧ����Ϣ�壺�ޣ�    ��������Դ�CErrorString::MtGetErrorStr��ȡ����
    OSPEVENT( FILESRV_DEV_LOGIN_NACK,         EV_FILESRVDEV_BGN + 3 );

    //Server���ļ���������ȡ�汾ʧ��֪ͨ����Ϣ�壺�ޣ���������Դ�MtGetErrorStr��ȡ����
    OSPEVENT( FILESRV_DEV_GETFILEERROR_NOTIF, EV_FILESRVDEV_BGN + 4 );
    //Server׼�����°汾�������豸��ʼ��ȡ�ļ�֪ͨ����Ϣ�壺IDevVerInfo
    OSPEVENT( FILESRV_DEV_FILEPREPARE_NOTIF,  EV_FILESRVDEV_BGN + 5 );

//1.1.2 ��ȡ�ļ�׼��״̬
    //�豸����Server���汾�Ƿ�׼���ã���Ϣ�壺��
    //(FILESRV_DEV_LOGIN_ACK֮��ǰ������NOTIF֮ǰ���Բ��ϲ�ѯ�Ƿ�׼����)
//    OSPEVENT( DEV_FILESRV_FILEPREPARE_REQ,    EV_FILESRVDEV_BGN + 10 );
    //ServerӦ��汾׼��״̬����Ϣ�壺u8(׼���ɹ���1����δ�ɹ���0)
//    OSPEVENT( FILESRV_DEV_FILEPREPARE_ACK,    EV_FILESRVDEV_BGN + 11 );
    //Server�ܾ��汾׼��״̬Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::GetFileSrvErrorStr��ȡ����
//    OSPEVENT( FILESRV_DEV_FILEPREPARE_NACK,   EV_FILESRVDEV_BGN + 12 );

//1.1.3 ��ע��
    //�豸����Server�Ͽ����ӣ���Ϣ�壺��
    OSPEVENT( DEV_FILESRV_LOGOUT_REQ,         EV_FILESRVDEV_BGN + 20 );
    //Serverͬ��Ͽ�Ӧ����Ϣ�壺��
    OSPEVENT( FILESRV_DEV_LOGOUT_ACK,         EV_FILESRVDEV_BGN + 21 );
    //Server�ܾ��Ͽ�Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::MtGetErrorStr��ȡ����
    OSPEVENT( FILESRV_DEV_LOGOUT_NACK,        EV_FILESRVDEV_BGN + 22 );

//1.2 �ļ�����

//1.2.1 ָ���ļ�
    //�豸����Server����ָ���ļ�����Ϣ�壺s8[MAX_FILESRV_FILENAME_LEN](��'\0'�ļ���)
    OSPEVENT( DEV_FILESRV_LOADFILE_REQ,       EV_FILESRVDEV_BGN + 30 );
    //Server�ļ�����׼�����Ӧ����Ϣ�壺u16(ָ���ļ��ܰ�����������)
    OSPEVENT( FILESRV_DEV_LOADFILE_ACK,       EV_FILESRVDEV_BGN + 31 );
    //Server�ܾ��ļ�����׼��Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::MtGetErrorStr��ȡ����
    OSPEVENT( FILESRV_DEV_LOADFILE_NACK,      EV_FILESRVDEV_BGN + 32 );

//1.2.2 �����ļ�
    //�豸����Server�����ļ��飬��Ϣ�壺u16(�ļ�SliceNo��������)
    OSPEVENT( DEV_FILESRV_GETFILE_REQ,        EV_FILESRVDEV_BGN + 35 );
    //Server�����ļ�����Ϣ�壺u16(��ǰ����İ�SliceNo��������) + u16(��ǰ������������) + u8[](�����ļ�)
    OSPEVENT( FILESRV_DEV_GETFILE_ACK,        EV_FILESRVDEV_BGN + 36 );
    //Server�ܾ������ļ�����Ϣ�壺�ޣ���������Դ�CErrorString::MtGetErrorStr��ȡ����
    OSPEVENT( FILESRV_DEV_GETFILE_NACK,       EV_FILESRVDEV_BGN + 37 );


#endif//_EVFILESRVDEV_H
