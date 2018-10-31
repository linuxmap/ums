/*=======================================================================
ģ����      : �ļ�����������
�ļ���      : evfilesrvclient.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ��������Client��������Ϣ����
����        : ���
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/29  1.0     ���    ����
=======================================================================*/

#ifndef _EVFILESRVCLIENT_H
#define _EVFILESRVCLIENT_H

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif//WIN32

#include "osp.h"
#include "eventid.h"

/*------------------------------------------------------------------------------
  �ļ������������Ϳͻ���ҵ����Ϣ(39201-39400)
------------------------------------------------------------------------------*/

//1.1	��������

//1.1.1	ע��
    //�ͻ���֪ͨServer�����ӣ�����׼�룬��Ϣ�壺IFCSrvLoginInfo
    OSPEVENT( CLIENT_FILESRV_LOGIN_REQ,         EV_FILESRVCLIENT_BGN + 1 );
    //Server׼��Ӧ����Ϣ�壺u32(Server����ţ���Client�ĺ�����Ϣ����д)
    OSPEVENT( FILESRV_CLIENT_LOGIN_ACK,         EV_FILESRVCLIENT_BGN + 2 );
    //Server�ܾ�Ӧ����Ϣ�壺�ޣ�    ��������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_LOGIN_NACK,        EV_FILESRVCLIENT_BGN + 3 );

//1.1.2 ע��
    //�ͻ�������Server�Ͽ����ӣ���Ϣ�壺��
    OSPEVENT( CLIENT_FILESRV_LOGOUT_REQ,        EV_FILESRVCLIENT_BGN + 4 );
    //Server����Ͽ�Ӧ����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_LOGOUT_ACK,        EV_FILESRVCLIENT_BGN + 5 );
    //Server�ܾ��Ͽ�Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_LOGOUT_NACK,       EV_FILESRVCLIENT_BGN + 6 );

//1.1.3 ����
    //�ͻ�������Server��������Ϣ�壺u8(1���ն˵�¼������/0������Ƿ����ն˵�¼)
    OSPEVENT( CLIENT_FILESRV_RESET_REQ,         EV_FILESRVCLIENT_BGN + 7 );
    //Server��������Ӧ����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_RESET_ACK,         EV_FILESRVCLIENT_BGN + 8 );
    //Server�ܾ�����Ӧ����Ϣ�壺�ޣ�
    //��������Դ�CErrorString::ClientGetErrorStr��ȡ����
    //�ͻ����ϴ��汾�����������ܾ�
    OSPEVENT( FILESRV_CLIENT_RESET_NACK,         EV_FILESRVCLIENT_BGN + 9 );

//1.2 �û�

//1.2.1 ��ȡ�û��б�
    //�ͻ��������û��б���Ϣ�壺��
    OSPEVENT( CLIENT_FILESRV_GETUSERLIST_REQ,   EV_FILESRVCLIENT_BGN + 10 );
    //Server��Ӧ�ͻ����û��б�����(����Աֻ�ܿ����Լ�)��
    //��Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_GETUSERLIST_ACK,   EV_FILESRVCLIENT_BGN + 11 );
    //Server�ܾ��ͻ����û��б�����Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_GETUSERLIST_NACK,  EV_FILESRVCLIENT_BGN + 12 );

    //Server֪ͨ�ͻ����û��б�(����Աֻ�ܿ����Լ�)��
    //��Ϣ�壺u32(�û����������������MAX_FILESRV_USER_NUM) + CFCSrvUserInfo * n
    OSPEVENT( FILESRV_CLIENT_USERLIST_NOTIF,    EV_FILESRVCLIENT_BGN + 13 );

//1.2.2 ����û�
    //�ͻ�����������û�����Ϣ�壺CUserFullInfo
    OSPEVENT( CLIENT_FILESRV_ADDUSER_REQ,       EV_FILESRVCLIENT_BGN + 15 );
    //Serverͬ������û�Ӧ��(�����ᷢ��FILESRV_CLIENT_USERLIST_NOTIF)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_ADDUSER_ACK,       EV_FILESRVCLIENT_BGN + 16 );
    //Server�ܾ�����û�Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_ADDUSER_NACK,      EV_FILESRVCLIENT_BGN + 17 );

//1.2.3 �޸��û�
    //�ͻ��������޸��û�����Ϣ�壺CFCSrvUserInfo
    OSPEVENT( CLIENT_FILESRV_EDITUSER_REQ,      EV_FILESRVCLIENT_BGN + 20 );
    //Serverͬ���޸��û�Ӧ��(�����ᷢ��FILESRV_CLIENT_USERLIST_NOTIF)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_EDITUSER_ACK,      EV_FILESRVCLIENT_BGN + 21 );
    //Server�ܾ��޸��û�Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_EDITUSER_NACK,     EV_FILESRVCLIENT_BGN + 22 );

//1.2.4 ɾ���û�
    //�ͻ��������޸��û�����Ϣ�壺u32(�û���ţ�������)
    OSPEVENT( CLIENT_FILESRV_DELUSER_REQ,       EV_FILESRVCLIENT_BGN + 25 );
    //Serverͬ��ɾ���û�Ӧ��(�����ᷢ��FILESRV_CLIENT_USERLIST_NOTIF)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_DELUSER_ACK,       EV_FILESRVCLIENT_BGN + 26 );
    //Server�ܾ�ɾ���û�Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_DELUSER_NACK,      EV_FILESRVCLIENT_BGN + 27 );


//1.3 ���ù���

//1.3.1 ��ѯ�����Ƽ��汾
    //�ͻ��˲�ѯ��ǰ�����Ƽ��汾������Ϣ�壺��
    OSPEVENT( CLIENT_FILESRV_GETALLRECOMMEND_REQ,   EV_FILESRVCLIENT_BGN + 40 );
    //Server��Ӧ�����Ƽ��汾��ѯ����(��������FILESRV_CLIENT_ALLRECOMMEND_NOTIF)��
    //��Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_GETALLRECOMMEND_ACK,   EV_FILESRVCLIENT_BGN + 41 );
    //Server�ܾ������Ƽ��汾��ѯ������Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_GETALLRECOMMEND_NACK,  EV_FILESRVCLIENT_BGN + 42 );

    //Server֪ͨ�����Ƽ��汾��Ϣ����Ϣ�壺
    //u32(�汾�ܸ�����������) + u32(�ѷ��͸�����������)
    //+ u32(��ǰ���汾������������) + IFCSrvDevVerFullInfo * n
    OSPEVENT( FILESRV_CLIENT_ALLRECOMMEND_NOTIF,    EV_FILESRVCLIENT_BGN + 43 );

//1.3.2 ��ѯĳһ�豸��ʷ�汾��ϸ��Ϣ(�����Ƽ��汾)
    //�ͻ��˲�ѯĳһ�豸��ʷ�汾��ϸ��Ϣ����(�����Ƽ��汾)��
    //��Ϣ�壺IFCSrvDev
    OSPEVENT( CLIENT_FILESRV_GETDEVVERINFO_REQ,     EV_FILESRVCLIENT_BGN + 45 );
    //Server��Ӧĳһ�豸��ʷ�汾��ϸ��Ϣ��ѯ����(��������FILESRV_CLIENT_DEVVERINFO_NOTIF)��
    //��Ϣ�壺IFCSrvDev
    OSPEVENT( FILESRV_CLIENT_GETDEVVERINFO_ACK,     EV_FILESRVCLIENT_BGN + 46 );
    //Server�ܾ�ĳһ�豸��ʷ�汾��ϸ��Ϣ��ѯ������Ϣ�壺�ޣ�
    //��������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_GETDEVVERINFO_NACK,    EV_FILESRVCLIENT_BGN + 47 );

    //Server֪ͨĳһ�豸��ʷ�汾��ϸ��Ϣ(�����Ƽ��汾)����Ϣ�壺
    //u32(�汾�ܸ�����������) + u32(�ѷ��͸�����������)
    //+ u32(��ǰ���汾������������) + IFCSrvDevVerFullInfo * n
    OSPEVENT( FILESRV_CLIENT_DEVVERINFO_NOTIF,      EV_FILESRVCLIENT_BGN + 48 );

//1.3.3 ��ĳһ�汾ָ��Ϊ�Ƽ��汾
    //�ͻ���ָ��ĳһ�汾Ϊ���豸���Ƽ��汾������Ϣ�壺u32(�汾��ţ�������)
    OSPEVENT( CLIENT_FILESRV_SETRECOMMEND_REQ,  EV_FILESRVCLIENT_BGN + 50 );
    //Server��Ӧָ��ĳһ�汾Ϊ���豸���Ƽ��汾������Ϣ�壺u32(�汾��ţ�������)
    OSPEVENT( FILESRV_CLIENT_SETRECOMMEND_ACK,  EV_FILESRVCLIENT_BGN + 51 );
    //Server�ܾ�ָ��ĳһ�汾Ϊ���豸���Ƽ��汾������Ϣ�壺�ޣ�
    //��������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_SETRECOMMEND_NACK, EV_FILESRVCLIENT_BGN + 52 );

    //Server֪ͨĳһ�豸�Ƽ��汾�������Ϣ�壺
    //u32(ԭ���Ƽ��汾�豸��ţ����������Ϊ-1��˵��ԭ��û���Ƽ��汾)
    //+ IFCSrvDevVerFullInfo(�µ��Ƽ��汾)
    //����д����룬��˵��ʧ�ܣ�m_wTotalPktΪ1000��ʾ����Ϣ�����ļ��������֪ͨ, 
    //��ʱm_wCurPkt��ʾ���ȣ�����10�õ��ٷ���
    OSPEVENT( FILESRV_CLIENT_SETRECOMMEND_NOTIF,    EV_FILESRVCLIENT_BGN + 53 );

//1.3.4 ɾ��ĳһ�汾
    //�ͻ���ɾ��ĳһ�汾������Ϣ�壺
    //u32(�汾��ţ�������)
    OSPEVENT( CLIENT_FILESRV_DELDEVVER_REQ,     EV_FILESRVCLIENT_BGN + 55 );
    //Server��Ӧ�ͻ���ɾ��ĳһ�汾������Ϣ�壺
    //u32(�汾��ţ�������)
    OSPEVENT( FILESRV_CLIENT_DELDEVVER_ACK,     EV_FILESRVCLIENT_BGN + 56 );
    //Server�ܾ��ͻ���ɾ��ĳһ�汾������Ϣ�壺�ޣ�
    //��������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_DELDEVVER_NACK,    EV_FILESRVCLIENT_BGN + 57 );

    //Server֪ͨ�汾ɾ������Ϣ�壺u32(��ɾ���İ汾��ţ�������)
    //����д����룬��˵��ɾ��ʧ��
    OSPEVENT( FILESRV_CLIENT_DELDEVVER_NOTIF,   EV_FILESRVCLIENT_BGN + 58 );

//1.3.5 �޸�ĳһ�汾
    //�ͻ����޸�ĳһ�汾������Ϣ�壺
    //u32(�豸��ţ�������) + IFCHardwareVer + s8[MAX_FILESRV_BUG_REPORT_LEN]
    OSPEVENT( CLIENT_FILESRV_EDITVER_REQ,       EV_FILESRVCLIENT_BGN + 60 );
    //Server�޸�ĳһ�汾��Ӧ����Ϣ�壺
    //u32(�豸��ţ�������) + IFCHardwareVer + s8[MAX_FILESRV_BUG_REPORT_LEN]
    OSPEVENT( FILESRV_CLIENT_EDITVER_ACK,       EV_FILESRVCLIENT_BGN + 61 );
    //Server�ܾ��޸�ĳһ�汾����Ϣ�壺�ޣ�
    //��������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_EDITVER_NACK,      EV_FILESRVCLIENT_BGN + 62 );

    //Server�޸�ĳһ�汾֪ͨ����Ϣ�壺
    //u32(�豸��ţ�������) + IFCHardwareVer + s8[MAX_FILESRV_BUG_REPORT_LEN]
    OSPEVENT( FILESRV_CLIENT_EDITVER_NOTIF,     EV_FILESRVCLIENT_BGN + 63 );

//1.3.6 ��ȡ����������
    //�ͻ��˻�ȡ����������������Ϣ�壺��
    OSPEVENT( CLIENT_FILESRV_GETCFG_REQ,        EV_FILESRVCLIENT_BGN + 65 );
    //��������Ӧ�ͻ��˻�ȡ���ã���Ϣ�壺ISusConfig
    OSPEVENT( FILESRV_CLIENT_GETCFG_ACK,        EV_FILESRVCLIENT_BGN + 66 );
    //�������ܾ��ͻ��˻�ȡ���ã���Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_GETCFG_NACK,       EV_FILESRVCLIENT_BGN + 67 );

    //�����������޸�֪ͨ����Ϣ�壺ISusConfig
    OSPEVENT( FILESRV_CLIENT_CFG_NOTIF,         EV_FILESRVCLIENT_BGN + 68 );

//1.3.7 �޸ķ���������
    //�ͻ����޸ķ���������������Ϣ�壺ISusConfig
    OSPEVENT( CLIENT_FILESRV_EDITCFG_REQ,       EV_FILESRVCLIENT_BGN + 70 );
    //��������Ӧ�ͻ����޸ķ���������(��������FILESRV_CLIENT_CFG_NOTIF)����Ϣ�壺ISusConfig
    OSPEVENT( FILESRV_CLIENT_EDITCFG_ACK,       EV_FILESRVCLIENT_BGN + 71 );
    //�������ܾ��ͻ����޸����ã���Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_EDITCFG_NACK,      EV_FILESRVCLIENT_BGN + 72 );

//1.4 ��־��ѯ

//1.4.1 ��ѯ��־
    //�ͻ�����־��ѯ������Ϣ�壺ILogReqInfo
    OSPEVENT( CLIENT_FILESRV_GETLOG_REQ,        EV_FILESRVCLIENT_BGN + 75 );
    //Server��Ӧ��־��ѯ����(��������FILESRV_CLIENT_LOG_NOTIF)��
    //��Ϣ�壺u32(����Ҫ�����־�ܸ�����������)
    OSPEVENT( FILESRV_CLIENT_GETLOG_ACK,        EV_FILESRVCLIENT_BGN + 76 );
    //Server�ܾ���־��ѯ������Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_GETLOG_NACK,       EV_FILESRVCLIENT_BGN + 77 );

    //Server֪ͨ��־��Ŀ(������REQ��Client)����Ϣ�壺
    //u32(�ܸ�����������) + u32(�ѷ��͸�����������) + u32(��ǰ��������������)
    //+ ILogRetInfo * n
    OSPEVENT( FILESRV_CLIENT_LOG_NOTIF,         EV_FILESRVCLIENT_BGN + 78 );

//1.4.2 ɾ��ָ����־��Ϣ
    //�ͻ���ɾ��ָ����־��Ŀ����Ϣ�壺u32(ɾ���ܸ�����������) + u32(ÿ����־��ID��������) * n
    OSPEVENT( CLIENT_FILESRV_DELLOG_REQ,        EV_FILESRVCLIENT_BGN + 80 );
    //������ͬ��ɾ��ָ����־��Ŀ(��������FILESRV_CLIENT_DELLOG_NOTIF)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_DELLOG_ACK,        EV_FILESRVCLIENT_BGN + 81 );
    //Server�ܾ�ɾ��ָ����־��Ŀ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_DELLOG_NACK,       EV_FILESRVCLIENT_BGN + 82 );

    //Serverɾ����־��Ŀ֪ͨ����Ϣ�壺u32(ɾ���ܸ�����������) + u32(ÿ����־��ID��������) * n
    OSPEVENT( FILESRV_CLIENT_DELLOG_NOTIF,      EV_FILESRVCLIENT_BGN + 83 );

//1.4.3 �����־��Ϣ
    //�ͻ����������������־��Ϣ����Ϣ�壺��
    OSPEVENT( CLIENT_FILESRV_CLEARLOG_REQ,      EV_FILESRVCLIENT_BGN + 85 );
    //������ͬ�����������־��Ϣ(��������FILESRV_CLIENT_CLEARLOG_NOTIF)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_CLEARLOG_ACK,      EV_FILESRVCLIENT_BGN + 86 );
    //Server�ܾ����������־��Ϣ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_CLEARLOG_NACK,     EV_FILESRVCLIENT_BGN + 87 );

    //Server���������־��Ϣ֪ͨ����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_CLEARLOG_NOTIF,    EV_FILESRVCLIENT_BGN + 88 );


//1.5 �ļ��ϴ�

//1.5.1 ׼���ϴ�
    //�ͻ��˸�֪�ϴ��ļ�������Ϣ�壺IFCSrvDevVerInfo
    OSPEVENT( CLIENT_FILESRV_UPDATEPREPARE_REQ, EV_FILESRVCLIENT_BGN + 100 );
    //Serverͬ���ϴ�Ӧ����Ϣ�壺IFCSrvDevVerInfo
    OSPEVENT( FILESRV_CLIENT_UPDATEPREPARE_ACK, EV_FILESRVCLIENT_BGN + 101 );
    //Server�ܾ��ϴ�Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_UPDATEPREPARE_NACK,EV_FILESRVCLIENT_BGN + 102 );

//1.5.2 ��֪�ļ���
    //�ͻ����ϴ��ļ�׼������Ϣ�壺s8[MAX_FILESRV_FILENAME_LEN](׼�������ϴ����ļ���)
    OSPEVENT( CLIENT_FILESRV_SENDFILENAME_REQ,  EV_FILESRVCLIENT_BGN + 105 );
    //Serverͬ���ϴ�ָ���ļ�����Ϣ�壺u16(ÿһ������󳤶ȣ�������)
    OSPEVENT( FILESRV_CLIENT_SENDFILENAME_ACK,  EV_FILESRVCLIENT_BGN + 106 );
    //Server�ܾ��ϴ�ָ���ļ�����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_SENDFILENAME_NACK, EV_FILESRVCLIENT_BGN + 107 );

//1.5.3 �ϴ��ļ�
    //�ͻ����ϴ��ļ�����Ϣ�壺u16(��ǰ������������) + u8[](�����ļ�)����Ҫ��дm_wTotalPkt��m_wCurPkt
    OSPEVENT( CLIENT_FILESRV_UPLOADFILE_REQ,    EV_FILESRVCLIENT_BGN + 110 );
    //Server����ָ���ļ�����Ϣ�壺�ޣ���Ҫ��дm_wCurPkt
    OSPEVENT( FILESRV_CLIENT_UPLOADFILE_ACK,    EV_FILESRVCLIENT_BGN + 111 );
    //Server�ܾ�����ָ���ļ�����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_UPLOADFILE_NACK,   EV_FILESRVCLIENT_BGN + 112 );

//1.5.4 �ļ��ϴ�֪ͨ
    //Server����ָ���ļ����֪ͨ(����ʾREQ�Ŀͻ���)����Ϣ�壺s8[MAX_FILESRV_FILENAME_LEN](�ļ���)
    OSPEVENT( FILESRV_CLIENT_ONEFILEEND_NOTIF,  EV_FILESRVCLIENT_BGN + 115 );
    //Server���������ļ����֪ͨ(����ʾREQ�Ŀͻ���)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_ALLFILEEND_NOTIF,  EV_FILESRVCLIENT_BGN + 116 );

//1.5.5 �ļ��������֪ͨ
    //Server֪ͨ�ļ��������(�ͻ����ϴ���Ϻ󣬷�����������ȣ����������ļ�����)��
    //��Ϣ�壺u16(���ȣ���ȷ��%ǰС�����һλ��������)
//    OSPEVENT( FILESRV_CLIENT_FILEPROGRESS_NOTIF, EV_FILESRVCLIENT_BGN + 120 );
    //Server֪ͨ�ļ�������(����100%����)����Ϣ�壺
    //u8(�ļ�����)
    //+ [ s8[MAX_FILESRV_FILENAME_LEN](�ļ���) + u32(0Ϊ�ɹ�������Ϊ�����룬������) ]
    //  * n
    OSPEVENT( FILESRV_CLIENT_FILERESULT_NOTIF,   EV_FILESRVCLIENT_BGN + 121 );

//1.5.6 ֹͣ�ļ�����
    //Client֪ͨServerֹͣ�ļ����䣬��Ϣ�壺��
    OSPEVENT( CLIENT_FILESRV_STOPUPDATE_REQ,     EV_FILESRVCLIENT_BGN + 130 );
    //Serverͬ��ֹͣ�ļ�����Ӧ��(�������ᷢ���κ��ļ������NOTIF)����Ϣ�壺��
    OSPEVENT( FILESRV_CLIENT_STOPUPDATE_ACK,     EV_FILESRVCLIENT_BGN + 131 );
    //Server�ܾ�ֹͣ�ļ�����Ӧ����Ϣ�壺�ޣ���������Դ�CErrorString::ClientGetErrorStr��ȡ����
    OSPEVENT( FILESRV_CLIENT_STOPUPDATE_NACK,    EV_FILESRVCLIENT_BGN + 132 );

#endif//_EVFILESRVCLIENT_H
