/*****************************************************************************
ģ����      : ���ݻ���ϵͳ��ģ��
�ļ���      : dccommon.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ���ݻ���ϵͳ��ģ�鹲�õĳ�������
����        : ����
�汾        : 4.0
-----------------------------------------------------------------------------
�޸ļ�¼:
����(D/M/Y)     �汾     �޸���      �޸�����
16/08/2005      0.1      ����        ��V3.6��ֲ
******************************************************************************/

#ifndef _DCCCOMMON_H
#define _DCCCOMMON_H

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif

#include "osp.h"
#include "kdvdef.h"
#include "eventid.h"
#include "errorid.h"

//��־������
#define     LOGLVL_EXCEPTION		 0	 //�쳣
#define     LOGLVL_IMPORTANT	     1	 //��Ҫ��־
#define     LOGLVL_DEBUG1		     254 //һ��������Ϣ
#define     LOGLVL_DEBUG2	         255 //����������Ϣ

//���ݻ��������181
#define AID_DCSERVER        (AID_DCS_BGN)       // DCServer App ID
#define AID_DCS_CALLMODULE  (AID_DCS_BGN + 1)   // DCServer��CallModuleʹ�õ�App ID
#define AID_INT_TEST_DCS    (AID_DCS_BGN + 2)   // DCServer���ɲ���App ID
#define AID_UNIT_TEST_DCS   (AID_DCS_BGN + 3)   // DCServer��Ԫ����App ID
#define AID_DCCLIB_SIM      (AID_DCS_BGN + 4)   // DCCLib׮ģ��App ID
#define AID_MT_SIM          (AID_DCS_BGN + 5)   // �ն�׮ģ��App ID
#define AID_DCSGUARD        (AID_DCS_BGN + 6)   // DCSGuard App ID

//���ݻ������̨201
#define AID_DCCONSOLE       (AID_DCC_BGN)       //DCConsole App ID
#define AID_INTE_TEST_DCC   (AID_DCC_BGN + 1)   //DCConsole���ɲ��� App ID
#define AID_UNIT_TEST_DCC   AID_INTE_TEST_DCC   //DCConsole��Ԫ���� App ID

const u16 MAX_E164NUM_LENGTH        = 16;   //E164���볤��

const u16 DCC_TESTAPP_LISTENPORT    = 3000; //20Ĭ�϶˿�
const u16 DCS_DEFAULT_PORT          = 1503; //T120Ĭ�϶˿�

const u8  DCS_INS_NUM	            = 32;                       //APP���ʵ��
const u8  DCS_CONF_MAX_NUM	        = 32;                       //���������
const u8  MAX_HEIGHT_IN_DATACONF    = 16;                       //���ݻ���������߶�
const u8  MAX_CONNECTION_PER_MT     = 32;                       //���ݻ�����ÿ���ڵ������������ֱ���ϼ��ڵ㣫ֱ���¼��ڵ㣩
extern u32 MAX_MT_PER_DATACONF/*       = 128*/;	                    //���ݻ��������ն�֧����
const u8  MAX_MT_IN_DATACONF        = MAX_CONNECTION_PER_MT;	//���ݻ��������ʾ�ն�֧����

const u8 MAX_MTENTRY_NUM            = 128;  //��ַ������ն���
const u8 MAX_CONFENTRY_NUM          = 64;   //��ַ�����ģ����
const u8 MAX_DCUSER_NUM             = 64;   //��ַ������û���

const char * const CONF_NAME_NUM = "120";   //Ĭ�ϻ����� ���ֶ�

const u8 MT_IS_ONLINE				= 1;    //�ն�����
const u8 MT_NOT_ONLINE				= 0;    //�ն˲�����

const u8 DCUSER_IS_ONLINE			= 1;    //�û�����
const u8 DCUSER_NOT_ONLINE			= 0;    //�û�������

const u8 DCUSER_ADMINISTRATOR		= 2;    //����Ա
const u8 DCUSER_OPERATOR			= 1;    //����Ա
const u8 DCUSER_READONLY			= 0;    //ֻ���û�

const u8 CONF_ENABLE_APPSHARING   = 0x01;   //��������Ӧ�ù�����
const u8 CONF_ENABLE_WHITEBOARD   = 0x02;   //��������װ幦��
const u8 CONF_ENABLE_FILETRANSFER = 0x04;   //���������ļ����书��
const u8 CONF_ENABLE_CHAT         = 0x08;   //�����������칦��

const u8 CONF_ENABLE_ACCEPTMTCALL = 0x01;   //���������ն���������
const u8 CONF_ENABLE_AUTOINVITEMT = 0x02;   //�Զ����������ն�
const u8 CONF_ENABLE_LOCKED       = 0x04;   //���鱻����
const u8 CONF_ENABLE_TMMANUAL     = 0x08;   //�����ֶ���ֹ
const u8 CONF_SUPPORT_CHAIRMAN    = 0x10;   //����֧����ϯ
const u8 CONF_NEED_PASSWORD       = 0x20;   //������Ҫ����

const u8 MAX_USER_LENGTH			= 16;	//�û�����󳤶�
const u8 MAX_PASSWORD_LENGTH		= 16;	//�û�������󳤶�
const u8 MAX_ALIAS_LENGTH			= 32;	//������󳤶�
const u8 MAX_EMAIL_LENGTH			= 32;	//Email��ַ��󳤶�(unicode��ʽ����)

const u8 MAX_DC_CONFNAME_LENGTH		= 32;	//���ݻ����������󳤶�
const u8 MAX_DC_PASSWORD_LENGTH		= 16;	//���ݻ������������󳤶�
const u8 MAX_NODENAME_LENGTH		= 32;   //�ն�����󳤶�
const u8 MAX_NODEPHONE_LENGTH		= 16;   //�绰������󳤶�(unicode��ʽ����)
const u8 MAX_NODELOCATION_LENGTH	= 32;   //�ն�λ����󳤶�(unicode��ʽ����)
const u8 MAX_MT_INFO_LENGTH     	= 64;	//�ն˱�ע��󳤶�
const u8 MAX_CONFNAME_NUM_LENGTH	= 16;   //���������ֶ���󳤶�
const u8 MAX_CONFNAME_TXT_LENGTH	= 64;   //�������ı�����󳤶�


//DCSGuard��DCServer֮�����Ϣ
//��ѯ����
OSPEVENT( DCSGUARD_DCS_POLL_REQ,                EV_DCSDCSGUARD_BGN );	
//��ѯӦ��
OSPEVENT( DCS_DCSGUARD_POLL_ACK,                EV_DCSDCSGUARD_BGN + 1 );


//DCConsole��DCServer֮�����Ϣ

//DCConsole������DCServer������DCC->DCC->DCS����Ϣ��ΪTDCUser
OSPEVENT( DCC_DCS_CONNECT_REQ,                  EV_DCSDCC_BGN );	
//DCS��DCC�����ɹ���DCS->DCC����Ϣ��ΪTDCUser
OSPEVENT( DCS_DCC_CONNECT_ACK,                  EV_DCSDCC_BGN + 1 );
//DCS�ܾ�������DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_CONNECT_NACK,                 EV_DCSDCC_BGN + 2 );

//DCConsole������DCServer������DCC->DCC����Ϣ��Ϊu32
OSPEVENT( DCC_DCS_DISCONNECT_REQ,               EV_DCSDCC_BGN + 6);	
//DCS��DCC�����ɹ���DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DISCONNECT_ACK,               EV_DCSDCC_BGN + 7 );
//DCS�ܾ�������DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DISCONNECT_NACK,              EV_DCSDCC_BGN + 8 );

//DCConsole����DCServer���͵�ַ����Ϣ��DCC->DCS������Ϣ��
OSPEVENT( DCC_DCS_GET_ADDRBOOK_REQ,             EV_DCSDCC_BGN +	12 );
//DCS���͵�ַ����ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_ADDRBOOK_ACK,             EV_DCSDCC_BGN + 13 );
//DCS�ܾ����͵�ַ����DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_ADDRBOOK_NACK,            EV_DCSDCC_BGN + 14 );

//DCConsole����DCServer�����նˣ�DCC->DCS����Ϣ��ΪTDCBaseMt
OSPEVENT( DCC_DCS_ADD_MTENTRY_REQ,				EV_DCSDCC_BGN +	18 );
//DCS���������ն���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_ADD_MTENTRY_ACK,			    EV_DCSDCC_BGN + 19 );
//DCS�ܾ������նˣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_ADD_MTENTRY_NACK,			    EV_DCSDCC_BGN + 20 );
//DCS���������ն�����֪ͨ,DCS->DCC,��Ϣ��ΪTDCBaseMt����
OSPEVENT( DCS_DCC_ADD_MTENTRY_NOTIF,            EV_DCSDCC_BGN +	21 );

//DCConsole����DCServerɾ���նˣ�DCC->DCS����Ϣ��ΪTDCBaseMt
OSPEVENT( DCC_DCS_DEL_MTENTRY_REQ,				EV_DCSDCC_BGN +	25 );
//DCS����ɾ���ն���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DEL_MTENTRY_ACK,				EV_DCSDCC_BGN + 26 );
//DCS�ܾ�ɾ���նˣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DEL_MTENTRY_NACK,			    EV_DCSDCC_BGN + 27 );
//DCS���������ն�ɾ��֪ͨ,DCS->DCC,��Ϣ��ΪTDCBaseMt
OSPEVENT( DCS_DCC_DEL_MTENTRY_NOTIF,            EV_DCSDCC_BGN +	28 );

//DCConsole����DCServer�޸��նˣ�DCC->DCS����Ϣ��ΪTDCBaseMt
OSPEVENT( DCC_DCS_MODIFY_MTENTRY_REQ,			EV_DCSDCC_BGN +	32 );
//DCS�����޸��ն���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_MODIFY_MTENTRY_ACK,			EV_DCSDCC_BGN + 33 );
//DCS�ܾ��޸��նˣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_MODIFY_MTENTRY_NACK,		    EV_DCSDCC_BGN + 34 );
//DCS���������ն��޸�֪ͨ,DCS->DCC,��Ϣ��ΪTDCBaseMt
OSPEVENT( DCS_DCC_MODIFY_MTENTRY_NOTIF,         EV_DCSDCC_BGN +	35 );

//DCConsole����DCServer���ӻ���ģ�壬DCC->DCS����Ϣ��ΪTDataConfTemplate
OSPEVENT( DCC_DCS_ADD_CONFENTRY_REQ,			EV_DCSDCC_BGN +	39 );
//DCS�������ӻ���ģ����ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_ADD_CONFENTRY_ACK,			EV_DCSDCC_BGN + 40 );
//DCS�ܾ����ӻ���ģ�壬DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_ADD_CONFENTRY_NACK,			EV_DCSDCC_BGN + 41 );
//DCS�������ͻ���ģ������֪ͨ,DCS->DCC,��Ϣ��ΪTDataConfTemplate
OSPEVENT( DCS_DCC_ADD_CONFENTRY_NOTIF,          EV_DCSDCC_BGN +	42 );

//DCConsole����DCServerɾ������ģ�壬DCC->DCS����Ϣ��ΪCConfId
OSPEVENT( DCC_DCS_DEL_CONFENTRY_REQ,			EV_DCSDCC_BGN +	46 );
//DCS����ɾ������ģ����ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DEL_CONFENTRY_ACK,			EV_DCSDCC_BGN + 47 );
//DCS�ܾ�ɾ������ģ�壬DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DEL_CONFENTRY_NACK,			EV_DCSDCC_BGN + 48 );
//DCS�������ͻ���ģ��ɾ��֪ͨ,DCS->DCC,��Ϣ��ΪCConfId
OSPEVENT( DCS_DCC_DEL_CONFENTRY_NOTIF,          EV_DCSDCC_BGN +	49 );

//DCConsole����DCServer�޸Ļ���ģ�壬DCC->DCS����Ϣ��ΪTDataConfTemplate
OSPEVENT( DCC_DCS_MODIFY_CONFENTRY_REQ,		    EV_DCSDCC_BGN +	53 );
//DCS�����޸Ļ���ģ����ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_MODIFY_CONFENTRY_ACK,		    EV_DCSDCC_BGN + 54 );
//DCS�ܾ��޸Ļ���ģ�壬DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_MODIFY_CONFENTRY_NACK,		EV_DCSDCC_BGN + 55 );
//DCS�������ͻ���ģ���޸�֪ͨ,DCS->DCC,��Ϣ��ΪTDataConfTemplate
OSPEVENT( DCS_DCC_MODIFY_CONFENTRY_NOTIF,       EV_DCSDCC_BGN +	56 );

//DCConsole����DCServer���ͻ����б�DCC->DCS������Ϣ��
OSPEVENT( DCC_DCS_GET_CONFLIST_REQ,             EV_DCSDCC_BGN +	60 );
//DCS���ͻ����б���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_CONFLIST_ACK,             EV_DCSDCC_BGN + 61 );
//DCS�ܾ����ͻ����б�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_CONFLIST_NACK,            EV_DCSDCC_BGN + 62 );

//DCConsole����DCServer�������飬DCC->DCS����Ϣ��ΪTDataConfFullInfo
OSPEVENT( DCC_DCS_CREATE_CONF_REQ,				EV_DCSDCC_BGN +	66 );
//DCS���ʹ���������ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_CREATE_CONF_ACK,				EV_DCSDCC_BGN + 67 );
//DCS�ܾ��������飬DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_CREATE_CONF_NACK,			    EV_DCSDCC_BGN + 68 );
//DCS�������ͻ���״̬֪ͨ,DCS->DCC,��Ϣ��ΪTDataConfFullInfo
OSPEVENT( DCS_DCC_CONF_NOTIF,                   EV_DCSDCC_BGN +	69 );

//DCConsole����DCServer�������飬DCC->DCS����Ϣ��ΪCConfId
OSPEVENT( DCC_DCS_TERM_CONF_REQ,			    EV_DCSDCC_BGN +	73 );
//DCS���ͽ���������ɣ�DCS->DCC������Ϣ��	
OSPEVENT( DCS_DCC_TERM_CONF_ACK,			    EV_DCSDCC_BGN + 74 );
//DCS�ܾ��������飬DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_TERM_CONF_NACK,			EV_DCSDCC_BGN + 75 );
//DCS�������ͻ������֪ͨ,DCS->DCC,��Ϣ��ΪCConfId
OSPEVENT( DCS_DCC_TERM_CONF_NOTIF,           EV_DCSDCC_BGN +	76 );

//DCConsole����DCServerָ����ϯ��DCC->DCS����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCC_DCS_SPEC_CHAIRMAN_REQ,			EV_DCSDCC_BGN +	80 );
//DCS����ָ����ϯ��ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_SPEC_CHAIRMAN_ACK,			EV_DCSDCC_BGN + 81 );
//DCS�ܾ�ָ����ϯ��DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_SPEC_CHAIRMAN_NACK,			EV_DCSDCC_BGN + 82 );
//DCSָ����ϯ֪ͨ��DCS->DCC����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCS_DCC_SPEC_CHAIRMAN_NOTIF,			EV_DCSDCC_BGN + 83 );

//DCConsole����DCServerȡ����ϯ��DCC->DCS����Ϣͷ�������Ч������Ϣ��
OSPEVENT( DCC_DCS_CANCEL_CHAIRMAN_REQ,		    EV_DCSDCC_BGN +	87 );
//DCS����ȡ����ϯ��ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_CANCEL_CHAIRMAN_ACK,		    EV_DCSDCC_BGN + 88 );
//DCS�ܾ�ȡ����ϯ��DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_CANCEL_CHAIRMAN_NACK,		    EV_DCSDCC_BGN + 89 );
//DCSȡ����ϯ֪ͨ��DCS->DCC����Ϣͷ�������Ч������Ϣ��
OSPEVENT( DCS_DCC_CANCEL_CHAIRMAN_NOTIF,		EV_DCSDCC_BGN + 90 );

//DCConsole����DCServer�����նˣ�DCC->DCS����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCC_DCS_INVITE_MT_REQ,					EV_DCSDCC_BGN +	94 );
//DCS���������ն���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_INVITE_MT_ACK,					EV_DCSDCC_BGN + 95 );
//DCS�ܾ������նˣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_INVITE_MT_NACK,					EV_DCSDCC_BGN + 96 );
//DCS�ն˼���֪ͨ��DCS->DCC����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCS_DCC_INVITE_MT_NOTIF,					EV_DCSDCC_BGN + 97 );

//DCConsole����DCServer�˳��նˣ�DCC->DCS����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCC_DCS_EJECT_MT_REQ,					EV_DCSDCC_BGN +	101 );
//DCS�����˳��ն���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_EJECT_MT_ACK,					EV_DCSDCC_BGN + 102 );
//DCS�ܾ��˳��նˣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_EJECT_MT_NACK,					EV_DCSDCC_BGN + 103 );
//DCS�ն��˳�֪ͨ��DCS->DCC����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCS_DCC_EJECT_MT_NOTIF,					EV_DCSDCC_BGN + 104 );

//DCS�ն����ߡ��˳�֪ͨ��DCS->DCC����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCS_DCC_MTSTATUS_NOTIF,				EV_DCSDCC_BGN + 108 );

//DCConsole����DCServer�û��б�DCC->DCS����Ϣ��Ϊ��
OSPEVENT( DCC_DCS_GET_USERLIST_REQ,			    EV_DCSDCC_BGN + 112 );
//DCS����û���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_USERLIST_ACK,			    EV_DCSDCC_BGN + 113 );
//DCS�ܾ�����û���DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_USERLIST_NACK,			EV_DCSDCC_BGN +	114 );

//DCConsole����DCServer����û���DCC->DCS����Ϣ��ΪTDCUser
OSPEVENT( DCC_DCS_ADD_DCC_USER_REQ,			    EV_DCSDCC_BGN + 118 );
//DCS����û���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_ADD_DCC_USER_ACK,			    EV_DCSDCC_BGN + 119 );
//DCS�ܾ�����û���DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_ADD_DCC_USER_NACK,			EV_DCSDCC_BGN +	120 );
//DCS����û�֪ͨ��DCS->DCC����Ϣ��ΪTDCUser����
OSPEVENT( DCS_DCC_ADD_DCC_USER_NOTIF,			EV_DCSDCC_BGN +	121 );

//DCConsole����DCServerɾ���û���DCC->DCS����Ϣ��ΪTDCUser
OSPEVENT( DCC_DCS_DEL_DCC_USER_REQ,			    EV_DCSDCC_BGN + 125 );
//DCSɾ���û���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DEL_DCC_USER_ACK,			    EV_DCSDCC_BGN + 126 );
//DCS�ܾ�ɾ���û���DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_DEL_DCC_USER_NACK,			EV_DCSDCC_BGN + 127 );
//DCSɾ���û�֪ͨ��DCS->DCC��Ϊ��Ϣ��TDCUser
OSPEVENT( DCS_DCC_DEL_DCC_USER_NOTIF,			EV_DCSDCC_BGN + 128 );

//DCConsole����DCServer�޸��û���DCC->DCS����Ϣ��ΪTDCUser
OSPEVENT( DCC_DCS_MODIFY_DCC_USER_REQ,			EV_DCSDCC_BGN + 132 );
//DCS�޸��û���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_MODIFY_DCC_USER_ACK,			EV_DCSDCC_BGN + 133 );
//DCS�ܾ��޸��û���DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_MODIFY_DCC_USER_NACK,			EV_DCSDCC_BGN +	134 );
//DCS�޸��û�֪ͨ��DCS->DCC����Ϣ��ΪTDCUser
OSPEVENT( DCS_DCC_MODIFY_DCC_USER_NOTIF,		EV_DCSDCC_BGN +	135 );

//DCConsole����DCServerɾ���նˣ�DCC->DCS����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCC_DCS_REMOVE_MT_REQ,					EV_DCSDCC_BGN +	139 );
//DCS����ɾ���ն���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_REMOVE_MT_ACK,					EV_DCSDCC_BGN + 140 );
//DCS�ܾ�ɾ���նˣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_REMOVE_MT_NACK,					EV_DCSDCC_BGN + 141 );
//DCS�ն�ɾ��֪ͨ��DCS->DCC����Ϣͷ�������Ч����Ϣ��ΪTDCMt
OSPEVENT( DCS_DCC_REMOVE_MT_NOTIF,					EV_DCSDCC_BGN + 142 );

//DCConsole����DCServer����ָ��DCServer�ϵĻ����б�DCC->DCS����Ϣ��ΪTDCSConfInfo
OSPEVENT( DCC_DCS_GET_REMOTE_CONFLIST_REQ,			EV_DCSDCC_BGN +	146 );
//DCS����ָ��DCServer�ϵĻ����б���ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_REMOTE_CONFLIST_ACK,			EV_DCSDCC_BGN + 147 );
//DCS�ܾ�����ָ��DCServer�ϵĻ����б�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_GET_REMOTE_CONFLIST_NACK,			EV_DCSDCC_BGN + 148 );
//DCS����ָ��DCServer�ϵĻ����б�֪ͨ��DCS->DCC����Ϣ��ΪTDCSConfInfo
OSPEVENT( DCS_DCC_GET_REMOTE_CONFLIST_NOTIF,		EV_DCSDCC_BGN + 149 );

//DCConsole����DCServer����ָ��DCServer�ϵ�ָ�����飬DCC->DCS����Ϣ��ΪTDCSConfInfo
OSPEVENT( DCC_DCS_JOIN_REMOTE_CONF_REQ,				EV_DCSDCC_BGN +	153 );
//DCS���ͼ���ָ��DCServer�ϵ�ָ��������ɣ�DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_JOIN_REMOTE_CONF_ACK,				EV_DCSDCC_BGN + 154 );
//DCS�ܾ�����ָ��DCServer�ϵ�ָ�����飬DCS->DCC������Ϣ��
OSPEVENT( DCS_DCC_JOIN_REMOTE_CONF_NACK,			EV_DCSDCC_BGN + 155 );
//DCS����ָ��DCServer�ϵ�ָ������֪ͨ��DCS->DCC����Ϣͷ�������Ч����Ϣ��ΪTDataConfFullInfo
OSPEVENT( DCS_DCC_JOIN_REMOTE_CONF_NOTIF,			EV_DCSDCC_BGN + 156 );

//DCConsole������DCServerc����������Ϣ��
OSPEVENT( DCC_DCS_RESTART_SERVER_REQ,           EV_DCSDCC_BGN + 157);	
//DCServerc�����ɹ�������Ϣ��
OSPEVENT( DCS_DCC_RESTART_SERVER_ACK,           EV_DCSDCC_BGN + 158);	
//DCServerc�ܾ�����������Ϣ��
OSPEVENT( DCS_DCC_RESTART_SERVER_NACK,          EV_DCSDCC_BGN + 159);

//�Զ�����֪ͨ   ��Ϣ��TParamPeerCap
OSPEVENT( GK_DCS_PEER_CAP_NOTIFY,				    EV_DCSDCC_BGN +	160 );
//�Զ�RTCP/RTP��ַ֪ͨ  ��Ϣ��TParamPeerAddr
OSPEVENT( GK_DCS_PEER_DATAADDR_NOTIF,				EV_DCSDCC_BGN + 161 );
//�����º���   ��Ϣ��TCallHandle
OSPEVENT( GK_DCS_NEWCALL_CREATE_NOTIF,				EV_DCSDCC_BGN + 162 );
//�º��е���   ��Ϣ��TParamNewCall
OSPEVENT( GK_DCS_NEWCALL_COMMING_NOTIF,				EV_DCSDCC_BGN + 163 );
//��������֪ͨ   ��Ϣ��TCallHandle
OSPEVENT( GK_DCS_CALL_CONNECT_NOTIF,				EV_DCSDCC_BGN + 164 );
//���жϿ�֪ͨ   ��Ϣ��TCallHandle
OSPEVENT( GK_DCS_CALL_DISCONNECT_NOTIF,				EV_DCSDCC_BGN + 165 );
//�µ��ŵ�����   ��Ϣ��TCallHandle
OSPEVENT( GK_DCS_NEWCHAN_CREATE_NOTIF,				EV_DCSDCC_BGN + 166 );
//Э��ջ��ʼ�����
OSPEVENT( GK_DCS_INIT_STACK_RESULT,                 EV_DCSDCC_BGN + 167 );
//��GKע����
OSPEVENT( GK_DCS_REGISTER_RESULT,                   EV_DCSDCC_BGN + 168 );
//������GKע������
OSPEVENT( GK_DCS_REGISTER_REQUEST,                  EV_DCSDCC_BGN + 169 );


//������GKע������
OSPEVENT( DCS_WATCHDOG_CONNECT_REQ,                  EV_DCSDCC_BGN + 170 );


//////////////////////////////////////////////////////////////////////////
//Error ID
//�ɹ�
const u16 ERROR_DCS_SUCCESS                  = ERR_DCS_BGN + 0;
//δ֪����
const u16 ERROR_DCS_UNKNOWN					 = ERR_DCS_BGN + 1;
//��������������ڴ�����
const u16 ERROR_DCS_BUSY                     = ERR_DCS_BGN + 2;
//�û�����
//�û�������
const u16 ERROR_DCS_DCUSER_NOT_EXIST         = ERR_DCS_BGN + 10;
//�û��������
const u16 ERROR_DCS_DCUSER_PASSWORD_ERROR    = ERR_DCS_BGN + 11;
//�û���Ȩ���д������
const u16 ERROR_DCS_DCUSER_ERROR_LEVEL       = ERR_DCS_BGN + 12;
//�û��Ѵ��ڣ��޷����
const u16 ERROR_DCS_DCUSER_EXISTED           = ERR_DCS_BGN + 13;
//�û�����
const u16 ERROR_DCS_DCUSER_ONLINE            = ERR_DCS_BGN + 14;
//�û�������
const u16 ERROR_DCS_DCUSER_FULL              = ERR_DCS_BGN + 15;
//����ɾ���Լ����ʻ�
const u16 ERROR_DCS_NO_DEL_SELF              = ERR_DCS_BGN + 16;

//�ն���Ϣ����
//MtEntry�Ѵ���
const u16 ERROR_DCS_MTENTRY_EXISTED          = ERR_DCS_BGN + 20;
//MtEntry������
const u16 ERROR_DCS_MTENTRY_NOT_EXIST        = ERR_DCS_BGN + 21;
//MtEntry����
const u16 ERROR_DCS_MTENTRY_FULL             = ERR_DCS_BGN + 22;

//����ģ�岿��
//ConfEntry����
const u16 ERROR_DCS_CONFENTRY_EXISTED        = ERR_DCS_BGN + 40;
//ConfEntry������
const u16 ERROR_DCS_CONFENTRY_NOT_EXIST      = ERR_DCS_BGN + 41;
//ConfEntry����
const u16 ERROR_DCS_CONFENTRY_FULL           = ERR_DCS_BGN + 42;

//���鲿��
//���鲻����
const u16 ERROR_DCS_CONF_NOT_EXIST			    = ERR_DCS_BGN + 60;
//�ն˲�����
const u16 ERROR_DCS_MT_NOT_EXIST				= ERR_DCS_BGN + 61;
//�ն˲�����
const u16 ERROR_DCS_MT_NOT_ONLINE			    = ERR_DCS_BGN + 62;
//���鲻֧����ϯ
const u16 ERROR_DCS_CONF_NOT_SUPPORT_CHAIRMAN   = ERR_DCS_BGN + 63;
//�����ն�����
const u16 ERROR_DCS_CONF_MT_FULL                = ERR_DCS_BGN + 64;
//�ն�����
const u16 ERROR_DCS_MT_ONLINE				    = ERR_DCS_BGN + 65;
//����û����ϯ
const u16 ERROR_DCS_CONF_NO_CHAIRMAN			= ERR_DCS_BGN + 66;
//�����Ѵ���
const u16 ERROR_DCS_CONF_EXISTED			    = ERR_DCS_BGN + 67;
//����������
const u16 ERROR_DCS_CONF_FULL			        = ERR_DCS_BGN + 68;
//�ܾ��ն˼�����������
const u16 ERROR_DCS_USER_REJECT                 = ERR_DCS_BGN + 69;
//�ܾ����ͻ����б�
const u16 ERROR_DCS_REJECT_CONFLIST             = ERR_DCS_BGN + 70;
//�ܾ�DCS����Զ�˻���
const u16 ERROR_DCS_REJECT_CONF                 = ERR_DCS_BGN + 71;
//�����������
const u16 ERROR_DCS_WRONG_PASSWD                = ERR_DCS_BGN + 72;
//�ն���Ϣ�������������
const u16 ERROR_INFO_LACK                       = ERR_DCS_BGN + 73;
//������û��ע�ᵽGK
const u16 ERROR_DCS_NO_REGISTER_GK              = ERR_DCS_BGN + 74;
//Զ�˻��鱻�������޷�����
const u16 ERROR_DCS_REMOTECONF_LOCK             = ERR_DCS_BGN + 75;

//���ݿⲿ��
const u16 ERROR_DCS_DB_ERROR                    = ERR_DCS_BGN + 80;

#endif // _DCCCOMMON_H
