/*****************************************************************************
   ģ����      : DCCLib
   �ļ���      : DCCLib.h
   ����ļ�    : DCCLib.h
                 DCCLib.cpp
   �ļ�ʵ�ֹ���: DCCLib�ṩ�Ľӿں���
   ����		   : �޽���
   �汾        : V4.0
   -----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾     �޸���      �޸�����
   15/08/05    1.0      �޽���      ����
******************************************************************************/

#if !defined(AFX_DCCLIB_H__7526EA9E_31B0_4DE8_9162_F44147157E9E__INCLUDED_)
#define AFX_DCCLIB_H__7526EA9E_31B0_4DE8_9162_F44147157E9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dcstrc.h"
#include "kdvsys.h"

//�����ļ�key
#define SECTION_USER_TABLE      _T("DCC_UserTable")
#define KEY_TABLE_AMOUNT        _T("TableAmount")
#define KEY_LOGON_LOG           _T("Logon")
#define KEY_LATEST_USER         _T("LatestUser")

/////////////////////////////////////////////////////////////////////////////////////////
//Window��Ϣ�ӿ�
//��λ(WPARAM)������ΪDCServer IP��ַ
#define		DCC_WM_USER_MSG_BEG					WM_USER + 1
//DCClib֪ͨUI����ģ���ѵõ��������б�������Ϣ(WPARAM)NULL+(LPARAM)(vector<TDCServerInfo>*)
#define		DCC_DISP_SERVERINFO_NOTIF			DCC_WM_USER_MSG_BEG

//DCClib֪ͨUI����ģ����ָ�������������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_CONNECT_ACK				DCC_WM_USER_MSG_BEG + 4
//DCClib֪ͨUI����ģ����ָ������������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_CONNECT_NACK				DCC_WM_USER_MSG_BEG + 5
//DCClib֪ͨUI����ģ����ָ��������������ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_CONNECT_TIMEOUT			DCC_WM_USER_MSG_BEG + 6

//DCClib֪ͨUI����ģ����ָ�������������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DISCONNECT_ACK				DCC_WM_USER_MSG_BEG + 10
//DCClib֪ͨUI����ģ����ָ������������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_DISCONNECT_NACK			DCC_WM_USER_MSG_BEG + 11
//DCClib֪ͨUI����ģ����ָ��������������ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DISCONNECT_TIMEOUT			DCC_WM_USER_MSG_BEG + 12

//DCClib֪ͨUI����ģ��ˢ�µ�ַ���ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_ADDRBOOK_ACK			DCC_WM_USER_MSG_BEG + 16
//DCClib֪ͨUI����ģ��ˢ�µ�ַ��ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_GET_ADDRBOOK_NACK			DCC_WM_USER_MSG_BEG + 17
//DCClib֪ͨUI����ģ��ˢ�µ�ַ����ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_ADDRBOOK_TIMEOUT		DCC_WM_USER_MSG_BEG + 18

//DCClib֪ͨUI����ģ�����ӵ�ַ���ն���Ŀ�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_ADD_MTENTRY_ACK			DCC_WM_USER_MSG_BEG + 22
//DCClib֪ͨUI����ģ�����ӵ�ַ���ն���Ŀʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_ADD_MTENTRY_NACK			DCC_WM_USER_MSG_BEG + 23
//DCClib֪ͨUI����ģ�����ӵ�ַ���ն���Ŀ��ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_ADD_MTENTRY_TIMEOUT		DCC_WM_USER_MSG_BEG + 24
//DCClib֪ͨUI����ģ���ַ����Ŀ����(WPARAM)DWORD+(LPARAM)( const vector<TDCBaseMt> * )
#define		DCC_DISP_ADD_MTENTRY_NOTIF			DCC_WM_USER_MSG_BEG + 25

//DCClib֪ͨUI����ģ��ɾ����ַ���ն���Ŀ�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DEL_MTENTRY_ACK			DCC_WM_USER_MSG_BEG + 29
//DCClib֪ͨUI����ģ��ɾ����ַ���ն���Ŀʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_DEL_MTENTRY_NACK			DCC_WM_USER_MSG_BEG + 30
//DCClib֪ͨUI����ģ��ɾ����ַ���ն���Ŀ��ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DEL_MTENTRY_TIMEOUT		DCC_WM_USER_MSG_BEG + 31
//DCClib֪ͨUI����ģ���ַ����Ŀ����(WPARAM)DWORD+(LPARAM)(const TDCBaseMt*)
#define		DCC_DISP_DEL_MTENTRY_NOTIF			DCC_WM_USER_MSG_BEG + 32

//DCClib֪ͨUI����ģ���޸ĵ�ַ���ն���Ŀ�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_MODIFY_MTENTRY_ACK			DCC_WM_USER_MSG_BEG + 36
//DCClib֪ͨUI����ģ���޸ĵ�ַ���ն���Ŀʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_MODIFY_MTENTRY_NACK		DCC_WM_USER_MSG_BEG + 37
//DCClib֪ͨUI����ģ���޸ĵ�ַ���ն���Ŀ��ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_MODIFY_MTENTRY_TIMEOUT		DCC_WM_USER_MSG_BEG + 38
//DCClib֪ͨUI����ģ���ַ����Ŀ�޸�(WPARAM)DWORD+(LPARAM)(const TDCBaseMt*)
#define		DCC_DISP_MODIFY_MTENTRY_NOTIF		DCC_WM_USER_MSG_BEG + 39

//DCClib֪ͨUI����ģ�����ӵ�ַ��������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_ADD_CONFENTRY_ACK			DCC_WM_USER_MSG_BEG + 43
//DCClib֪ͨUI����ģ�����ӵ�ַ��������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_ADD_CONFENTRY_NACK			DCC_WM_USER_MSG_BEG + 44
//DCClib֪ͨUI����ģ�����ӵ�ַ�������鳬ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_ADD_CONFENTRY_TIMEOUT		DCC_WM_USER_MSG_BEG + 45
//DCClib֪ͨUI����ģ���ַ������������(WPARAM)DWORD+(LPARAM)(const TDataConfTemplate*)
#define		DCC_DISP_ADD_CONFENTRY_NOTIF		DCC_WM_USER_MSG_BEG + 46

//DCClib֪ͨUI����ģ��ɾ����ַ��������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DEL_CONFENTRY_ACK			DCC_WM_USER_MSG_BEG + 50
//DCClib֪ͨUI����ģ��ɾ����ַ��������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_DEL_CONFENTRY_NACK			DCC_WM_USER_MSG_BEG + 51
//DCClib֪ͨUI����ģ��ɾ����ַ�������鳬ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DEL_CONFENTRY_TIMEOUT		DCC_WM_USER_MSG_BEG + 52
//DCClib֪ͨUI����ģ���ַ�����������(WPARAM)DWORD+(LPARAM)(const CConfId*)
#define		DCC_DISP_DEL_CONFENTRY_NOTIF		DCC_WM_USER_MSG_BEG + 53

//DCClib֪ͨUI����ģ���޸ĵ�ַ��������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_MODIFY_CONFENTRY_ACK		DCC_WM_USER_MSG_BEG + 57
//DCClib֪ͨUI����ģ���޸ĵ�ַ��������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_MODIFY_CONFENTRY_NACK		DCC_WM_USER_MSG_BEG + 58
//DCClib֪ͨUI����ģ���޸ĵ�ַ�������鳬ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_MODIFY_CONFENTRY_TIMEOUT	DCC_WM_USER_MSG_BEG + 59
//DCClib֪ͨUI����ģ���ַ���������޸�(WPARAM)DWORD+(LPARAM)(const TDataConfTemplate*)
#define		DCC_DISP_MODIFY_CONFENTRY_NOTIF		DCC_WM_USER_MSG_BEG + 60

//DCClib֪ͨUI����ģ��ˢ�»����б�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_CONFLIST_ACK			DCC_WM_USER_MSG_BEG + 64
//DCClib֪ͨUI����ģ��ˢ�»����б�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_GET_CONFLIST_NACK			DCC_WM_USER_MSG_BEG + 65
//DCClib֪ͨUI����ģ��ˢ�»����б�ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_CONFLIST_TIMEOUT		DCC_WM_USER_MSG_BEG + 66

//DCClib֪ͨUI����ģ�鴴������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_CREATE_CONF_ACK			DCC_WM_USER_MSG_BEG + 70
//DCClib֪ͨUI����ģ�鴴������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_CREATE_CONF_NACK			DCC_WM_USER_MSG_BEG + 71
//DCClib֪ͨUI����ģ�鴴�����鳬ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_CREATE_CONF_TIMEOUT		DCC_WM_USER_MSG_BEG + 72
//DCClib֪ͨUI����ģ�����״̬�ı�(WPARAM)DWORD+(LPARAM)(const TDataConfFullInfo*)
#define		DCC_DISP_CONF_NOTIF					DCC_WM_USER_MSG_BEG + 73

//DCClib֪ͨUI����ģ���������ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_TERM_CONF_ACK			DCC_WM_USER_MSG_BEG + 77
//DCClib֪ͨUI����ģ���������ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_TERM_CONF_NACK			DCC_WM_USER_MSG_BEG + 78
//DCClib֪ͨUI����ģ��������鳬ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_TERM_CONF_TIMEOUT		DCC_WM_USER_MSG_BEG + 79
//DCClib֪ͨUI����ģ��������(WPARAM)DWORD+(LPARAM)(const CConfId*)
#define		DCC_DISP_TERM_CONF_NOTIF			DCC_WM_USER_MSG_BEG + 80

//DCClib֪ͨUI����ģ��ָ����ϯ�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_SPEC_CHAIRMAN_ACK			DCC_WM_USER_MSG_BEG + 84
//DCClib֪ͨUI����ģ��ָ����ϯʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_SPEC_CHAIRMAN_NACK			DCC_WM_USER_MSG_BEG + 85
//DCClib֪ͨUI����ģ��ָ����ϯ��ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_SPEC_CHAIRMAN_TIMEOUT		DCC_WM_USER_MSG_BEG + 86
//DCClib֪ͨUI����ģ����ϯ�仯(WPARAM)DWORD+(LPARAM)( const CConfId* + const TDCMt* )
#define		DCC_DISP_SPEC_CHAIRMAN_NOTIF		DCC_WM_USER_MSG_BEG + 87

//DCClib֪ͨUI����ģ��ȡ����ϯ�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_CANCEL_CHAIRMAN_ACK		DCC_WM_USER_MSG_BEG + 91
//DCClib֪ͨUI����ģ��ȡ����ϯʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_CANCEL_CHAIRMAN_NACK		DCC_WM_USER_MSG_BEG + 92
//DCClib֪ͨUI����ģ��ȡ����ϯ��ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_CANCEL_CHAIRMAN_TIMEOUT	DCC_WM_USER_MSG_BEG + 93
//DCClib֪ͨUI����ģ��ȡ����ϯ֪ͨ(WPARAM)DWORD+(LPARAM)( const CConfId* )
#define		DCC_DISP_CANCEL_CHAIRMAN_NOTIF		DCC_WM_USER_MSG_BEG + 94

//DCClib֪ͨUI����ģ�������ն˳ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_INVITE_MT_ACK				DCC_WM_USER_MSG_BEG + 98
//DCClib֪ͨUI����ģ�������ն�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_INVITE_MT_NACK				DCC_WM_USER_MSG_BEG + 99
//DCClib֪ͨUI����ģ�������ն˳�ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_INVITE_MT_TIMEOUT			DCC_WM_USER_MSG_BEG + 100
//DCClib֪ͨUI����ģ���ն˼������(WPARAM)DWORD+(LPARAM)( const CConfId* + const TDCMt* )
#define		DCC_DISP_INVITE_MT_NOTIF			DCC_WM_USER_MSG_BEG + 101

//DCClib֪ͨUI����ģ���˳��ն˳ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_EJECT_MT_ACK				DCC_WM_USER_MSG_BEG + 105
//DCClib֪ͨUI����ģ���˳��ն�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_EJECT_MT_NACK				DCC_WM_USER_MSG_BEG + 106
//DCClib֪ͨUI����ģ���˳��ն˳�ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_EJECT_MT_TIMEOUT			DCC_WM_USER_MSG_BEG + 107
//DCClib֪ͨUI����ģ���ն��˳�����(WPARAM)DWORD+(LPARAM)( const CConfId* + const TDCMt* )
#define		DCC_DISP_EJECT_MT_NOTIF				DCC_WM_USER_MSG_BEG + 108

//DCClib֪ͨUI����ģ���ն�״̬�仯(WPARAM)DWORD+(LPARAM)( const CConfId* + const TDCMt* )
#define		DCC_DISP_MTSTATUS_NOTIF				DCC_WM_USER_MSG_BEG + 112

//DCClib֪ͨUI����ģ��ˢ���û��б�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_USERLIST_ACK			DCC_WM_USER_MSG_BEG + 116
//DCClib֪ͨUI����ģ��ˢ���û��б�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_GET_USERLIST_NACK			DCC_WM_USER_MSG_BEG + 117
//DCClib֪ͨUI����ģ��ˢ���û��б�ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_USERLIST_TIMEOUT		DCC_WM_USER_MSG_BEG + 118

//DCClib֪ͨUI����ģ�������û��ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_ADD_USER_ACK				DCC_WM_USER_MSG_BEG + 122
//DCClib֪ͨUI����ģ�������û�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_ADD_USER_NACK				DCC_WM_USER_MSG_BEG + 123
//DCClib֪ͨUI����ģ�������û���ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_ADD_USER_TIMEOUT			DCC_WM_USER_MSG_BEG + 124
//DCClib֪ͨUI����ģ�������û�(WPARAM)DWORD+(LPARAM)( const vector<TDCUser>* )
#define		DCC_DISP_ADD_USER_NOTIF				DCC_WM_USER_MSG_BEG + 125

//DCClib֪ͨUI����ģ��ɾ���û��ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DEL_USER_ACK				DCC_WM_USER_MSG_BEG + 129
//DCClib֪ͨUI����ģ��ɾ���û�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_DEL_USER_NACK				DCC_WM_USER_MSG_BEG + 130
//DCClib֪ͨUI����ģ��ɾ���û���ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DEL_USER_TIMEOUT			DCC_WM_USER_MSG_BEG + 131
//DCClib֪ͨUI����ģ��ɾ���û�(WPARAM)DWORD+(LPARAM)( const TDCUser* )
#define		DCC_DISP_DEL_USER_NOTIF				DCC_WM_USER_MSG_BEG + 132

//DCClib֪ͨUI����ģ���޸��û��ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_MODIFY_USER_ACK			DCC_WM_USER_MSG_BEG + 136
//DCClib֪ͨUI����ģ���޸��û�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_MODIFY_USER_NACK			DCC_WM_USER_MSG_BEG + 137
//DCClib֪ͨUI����ģ���޸��û���ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_MODIFY_USER_TIMEOUT		DCC_WM_USER_MSG_BEG + 138
//DCClib֪ͨUI����ģ���޸��û�(WPARAM)DWORD+(LPARAM)( const TDCUser* )
#define		DCC_DISP_MODIFY_USER_NOTIF			DCC_WM_USER_MSG_BEG + 139

//DCClib֪ͨUI����ģ�����������·��(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DISCONNECT					DCC_WM_USER_MSG_BEG + 143
//DCClib֪ͨUI����ģ�������ͬʱ���ӿ���̨�Ѵ�����(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_DCS_OVERFLOW				DCC_WM_USER_MSG_BEG + 144
//DCClib֪ͨUI����ģ�����̨ͬʱ���ӷ������Ѵ�����(WPARAM)NULL+(LPARAM)NULL
#define		DCC_DISP_DCC_OVERFLOW				DCC_WM_USER_MSG_BEG + 145

//DCClib֪ͨUI����ģ��ɾ���ն˳ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_REMOVE_MT_ACK				DCC_WM_USER_MSG_BEG + 149
//DCClib֪ͨUI����ģ��ɾ���ն�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_REMOVE_MT_NACK				DCC_WM_USER_MSG_BEG + 150
//DCClib֪ͨUI����ģ��ɾ���ն˳�ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_REMOVE_MT_TIMEOUT			DCC_WM_USER_MSG_BEG + 151
//DCClib֪ͨUI����ģ�����ɾ���ն�(WPARAM)DWORD+(LPARAM)( const CConfId* + const TDCMt* )
#define		DCC_DISP_REMOVE_MT_NOTIF			DCC_WM_USER_MSG_BEG + 152

//DCClib֪ͨUI����ģ������Զ��DCServer�����б�ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_REMOTE_CONFLIST_ACK	DCC_WM_USER_MSG_BEG + 156
//DCClib֪ͨUI����ģ������Զ��DCServer�����б�ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_GET_REMOTE_CONFLIST_NACK	DCC_WM_USER_MSG_BEG + 157
//DCClib֪ͨUI����ģ������Զ��DCServer�����б�ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_GET_REMOTE_CONFLIST_TIMEOUT	DCC_WM_USER_MSG_BEG + 158
//DCClib֪ͨUI����ģ��Զ��DCServer����֪ͨ(WPARAM)DWORD+(LPARAM)( const TDCSConfInfo* )
#define		DCC_DISP_GET_REMOTE_CONFLIST_NOTIF  	DCC_WM_USER_MSG_BEG + 159

//DCClib֪ͨUI����ģ���������Զ��DCServer����ɹ�(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_JOIN_REMOTE_CONF_ACK   	DCC_WM_USER_MSG_BEG + 163
//DCClib֪ͨUI����ģ���������Զ��DCServer����ʧ��(WPARAM)DWORD+(LPARAM)WORD
#define		DCC_DISP_JOIN_REMOTE_CONF_NACK	    DCC_WM_USER_MSG_BEG + 164
//DCClib֪ͨUI����ģ���������Զ��DCServer���鳬ʱ(WPARAM)DWORD+(LPARAM)NULL
#define		DCC_DISP_JOIN_REMOTE_CONF_TIMEOUT	DCC_WM_USER_MSG_BEG + 165
//DCClib֪ͨUI����ģ�����Զ��DCServer����֪ͨ(WPARAM)DWORD+(LPARAM)( const TDataConfFullInfo* )
#define		DCC_DISP_JOIN_REMOTE_CONF_NOTIF	    DCC_WM_USER_MSG_BEG + 166

//DCClib֪ͨUI����ģ������Զ��DCServer�����ɹ�  (WPARAM)NULL+(LPARAM)NULL
#define		DCC_DISP_RESTART_SERVER_ACK   	    DCC_WM_USER_MSG_BEG + 170
//DCClib֪ͨUI����ģ������Զ��DCServer����ʧ��  (WPARAM)NULL+(LPARAM)NULL
#define		DCC_DISP_RESTART_SERVER_NACK	    DCC_WM_USER_MSG_BEG + 171
//DCClib֪ͨUI����ģ������Զ��DCServer������ʱ  (WPARAM)NULL+(LPARAM)NULL
#define		DCC_DISP_RESTART_SERVER_TIMEOUT  	DCC_WM_USER_MSG_BEG + 172



//DCCLib�ڲ��Զ���WINDOWS��Ϣ��β
#define		DCC_WM_USER_MSG_END					DCC_WM_USER_MSG_BEG + 200

//��־�ļ���(���·��)
#define DCC_LOG										(LPSTR)"dcc.txt"

//���ͬʱ�ɿ��Ʒ�����
#define MAXIMUM_CONTROL_DCSERVER					(int)10
//�ӿں�������
#define DCC_RETURN_TRUE								(WORD)0 //�����ɹ�
//��Ϣ���ͻ�ӿ�����������ʱ�Ĵ����
#define OSP_ALWAYS_INIT								ERR_DCC_BGN	//�Ѿ���ʼ��
#define NO_WINDOW_IS_SUCH_HWND						ERR_DCC_BGN + 1	//���ھ��������һ����Ч����
#define OSP_NOT_INIT								ERR_DCC_BGN + 2 //û�г�ʼ��
#define FAIL_TO_CONNECT_DCS							ERR_DCC_BGN + 3 //������DCS����ʧ��
#define FAIL_TO_SEND_MSG_TO_DCS						ERR_DCC_BGN + 4 //��·æ��������Ϣ��DCSʧ��
#define OPERATE_MUST_IN_IDLE_STATE					ERR_DCC_BGN + 5 //ֻ��δ�ɹ���DCS��������ִ�иò���
#define OPERATE_MUST_IN_NORMAL_STATE				ERR_DCC_BGN + 6 //ֻ�е��ɹ���DCS��������ִ�иò���
#define OPERATE_MUST_WAIT							ERR_DCC_BGN + 7 //DCSæ�����ڴ���ǰһ������
#define CONFIGURE_FILE_INVALID						ERR_DCC_BGN + 8 //�����ļ���ʽ����
#define FAIL_TO_SEARSH_DCSERVER						ERR_DCC_BGN + 9 //��ѯ������ʧ��

//DCC_ASSERT����־�ļ����ȴ�ӡ���������Ϣ
#define DCC_ASSERT(exp)    \
{\
    if ( !( exp ) ) {\
	::OspLog( 0, "ASSERT FAILED:\nFile:%s-Line:%d-%s\n", __FILE__, __LINE__, #exp );\
    }\
}

/*====================================================================
����        ��  DCCLib��ʼ��
�������˵����  dwDCCIpAddr����Ip
                wDCCLibListenPort���������˿�
                wDCCLibTelnetPort����Telnet�˿�
                hwndBackup����UI����ģ�����������Ϣ�Ĵ��ھ��
����ֵ˵��  ��  ��
====================================================================*/
WORD DCCLibInit( DWORD dwDCCIpAddr , WORD wDCCLibListenPort , WORD wDCCLibTelnetPort , HWND hwndBackup );

/*====================================================================
����        ��  ж�ع��ܿ�
�������˵����  
����ֵ˵��  ��  ��
====================================================================*/
WORD DCCLibExit( );

/*====================================================================
����        ��  ���������������
�������˵����  dwDCSIpAddr����DCS Ip
                wDCSListenPort����DCS�����˿�
                tUser�����û���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD ConnectToServer( DWORD dwDCSIpAddr , WORD wDCSListenPort , const TDCUser& tUser );

/*====================================================================
����        ��  �Ͽ��������������
�������˵����  dwServerpAddr����������Ip
����ֵ˵��  ��  ��
====================================================================*/
WORD DisConnectFromServer( DWORD dwServerIp );

/*====================================================================
����        ��  ����DCServer������
�������˵����  dwServerpAddr����������Ip
����ֵ˵��  ��  ��
====================================================================*/
WORD ReStartDcServer( DWORD dwServerIp );

/*====================================================================
����        ��  ��ȡ�û��б�
�������˵����  dwServerIp ����������Ip
����ֵ˵��  ��  ��
====================================================================*/
WORD	GetUserList( DWORD dwServerIp );

/*====================================================================
����        ��  �����û�
�������˵����  dwServerIp ����������Ip
                tUser�����û���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD AddUser( DWORD dwServerIp , const TDCUser& tUser );

/*====================================================================
����        ��  ɾ���û�
�������˵����  dwServerIp ����������Ip
                tUser�����û���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD DelUser( DWORD dwServerIp , const TDCUser& tUser );

/*====================================================================
����        ��  �޸��û�
�������˵����  dwServerIp ����������Ip
                tUser�����û���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD ModifyUser( DWORD dwServerIp , const TDCUser& tUser );

/*====================================================================
����        ��  ˢ�µ�ַ����Ϣ
�������˵����  dwServerIp ����������Ip
����ֵ˵��  ��  ��
====================================================================*/
WORD GetAddrBook( DWORD dwServerIp );

/*====================================================================
����        ��  �����ն���Ŀ
�������˵����  dwServerIp ����������Ip
                tMt�����ն���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD AddMtEntry( DWORD dwServerIp , const TDCBaseMt& tMt );

/*====================================================================
����        ��  ɾ���ն���Ŀ
�������˵����  dwServerIp ����������Ip
                tMt�����ն���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD DelMtEntry( DWORD dwServerIp , const TDCBaseMt& tMt );

/*====================================================================
����        ��  �޸��ն���Ŀ
�������˵����  dwServerIp ����������Ip
                tMt�����ն���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD ModifyMtEntry( DWORD dwServerIp , const TDCBaseMt& tMt );

/*====================================================================
����        ��  ���ӻ���ģ��
�������˵����  dwServerIp ����������Ip
                tTemplate����ģ����Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD AddConfEntry( DWORD dwServerIp , const TDataConfTemplate& tTemplate );

/*====================================================================
����        ��  ɾ������ģ��
�������˵����  dwServerIp ����������Ip
                cConfId����ģ��Id
����ֵ˵��  ��  ��
====================================================================*/
WORD DelConfEntry( DWORD dwServerIp , const CConfId& cConfId );

/*====================================================================
����        ��  �޸Ļ���ģ��
�������˵����  dwServerIp ����������Ip
                tTemplate����ģ����Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD ModifyConfEntry( DWORD dwServerIp , const TDataConfTemplate& tTemplate );

/*====================================================================
����        ��  ��ȡ�����б�
�������˵����  dwServerIp ����������Ip
����ֵ˵��  ��  ��
====================================================================*/
WORD GetConfList( DWORD dwServerIp );

/*====================================================================
����        ��  ��������
�������˵����  dwServerIp ����������Ip
                tInfo����������Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD CreateConf( DWORD dwServerIp , const TDataConfFullInfo& tInfo );

/*====================================================================
����        ��  ��������
�������˵����  dwServerIp ����������Ip
                cConfId���������
����ֵ˵��  ��  ��
====================================================================*/
WORD TermConf( DWORD dwServerIp , const CConfId& cConfId );

/*====================================================================
����        ��  ָ����ϯ
�������˵����  dwServerIp ����������Ip
                cConfId���������
                tDcMt�����ն���Ϣ            
����ֵ˵��  ��  ��
====================================================================*/
WORD SpecChairman( DWORD dwServerIp , const CConfId& cConfId , const TDCMt& tDcMt );

/*====================================================================
����        ��  ȡ����ϯ
�������˵����  dwServerIp ����������Ip
                cConfId���������
����ֵ˵��  ��  ��
====================================================================*/
WORD CancelChairman( DWORD dwServerIp , const CConfId& cConfId );

/*====================================================================
����        ��  �����ն�
�������˵����  dwServerIp ����������Ip
                cConfId���������
                tDcMt�����ն���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD InviteMt( DWORD dwServerIp , const CConfId& cConfId , const TDCMt& tDcMt );

/*====================================================================
����        ��  �Ҷ��ն�
�������˵����  dwServerIp ����������Ip
                cConfId���������
                tDcMt�����ն���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD EjectMt( DWORD dwServerIp , const CConfId& cConfId , const TDCMt& tDcMt );

/*====================================================================
����        ��  ɾ���ն�
�������˵����  dwServerIp ����������Ip
                cConfId���������
                tDcMt�����ն���Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD RemoveMt( DWORD dwServerIp , const CConfId& cConfId , const TDCMt& tDcMt );

/*====================================================================
����        ��  ��ȡԶ�˻����б�
�������˵����  dwServerIp ����������Ip
                tDCSConfInfo����Զ�˷�������Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD GetRemoteConfList( DWORD dwServerIp , const TDCSConfInfo& tDCSConfInfo );

/*====================================================================
����        ��  ����Զ�˻���
�������˵����  dwServerIp ����������Ip
                tDCSConfInfo����Զ�˻�����Ϣ
����ֵ˵��  ��  ��
====================================================================*/
WORD ReqJoinRemoteConf( DWORD dwServerIp , const TDCSConfInfo& tDCSConfInfo );

//////////////////////////////////////////////////////////////////////////////////
/*====================================================================
����        ��  ��ȡ����������
�������˵����  wErrorCode ����������
����ֵ˵��  ��  ��
====================================================================*/
CString	DCCGetErrorDetail( WORD wErrorCode );

/*====================================================================
����        ��  ����TRC����Ļ�ļ���
�������˵����  ��
����ֵ˵��  ��  ��
====================================================================*/
API void DCCLibSetDebugTrcScreen();

/*====================================================================
����        ��  �ÿ�TRC����Ļ�ļ���
�������˵����  ��
����ֵ˵��  ��  ��
====================================================================*/
API void DCCLibSetReleaseTrcScreen();

/*====================================================================
����        ��  ����LOG����Ļ�ļ���
�������˵����  ��
����ֵ˵��  ��  ��
====================================================================*/
API void DCCLibSetDebugLogScreen();

/*====================================================================
����        ��  �ÿ�LOG����Ļ�ļ���
�������˵����  ��
����ֵ˵��  ��  ��
====================================================================*/
API void DCCLibSetReleaseLogScreen();

/*====================================================================
����        ��  DCCCLib�汾��
�������˵����  ��
����ֵ˵��  ��  ��
====================================================================*/
API void DCCLibVersion();

/*====================================================================
����        ��  �����ļ�
�������˵����  ��
����ֵ˵��  ��  ��
====================================================================*/
API	void dcclibhelp();

#endif // !defined(AFX_DCCLIB_H__7526EA9E_31B0_4DE8_9162_F44147157E9E__INCLUDED_)
