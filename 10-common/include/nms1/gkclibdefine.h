/*****************************************************************************
ģ����      : GkcLib
�ļ���      : GkcLibDefine.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ������CGkcLibInterface��Ҫ�õĺꡢ�ṹ��ö�ٵȡ�
              ͬʱ���������д�����Ϣ��

����        : �º��
ģ��汾    : V4.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��(n/m/d)      �ļ��汾        �޸���      �޸�����
2005/08/08         1.0             �º��     ����
******************************************************************************/
#ifndef GKCLIBDEFINE_H
#define GKCLIBDEFINE_H

#include "kdvgk.h"

//GkcLib�ڲ�Ӧ�ú�
#define AID_GKCONSOLE       AID_GKC_BGN
#define AID_INTE_TEST_GKC   AID_GKC_BGN + 1
#define AID_UNIT_TEST_GKC   AID_GKC_BGN + 2

//�ӿں�������
#define GKC_OPERATE_SUCCESS				    		(u32)0 //�����ɹ�
//��Ϣ���ͻ�ӿ�����������ʱ�Ĵ����
#define OSP_ALWAYS_INIT								(u32)50	//�Ѿ���ʼ��
#define NO_WINDOW_IS_SUCH_HWND						(u32)51	//���ھ��������һ����Ч����
#define OSP_NOT_INIT								(u32)52	//û�г�ʼ��
#define FAIL_TO_CONNECT_GK							(u32)53	//������GK����ʧ��
#define FAIL_TO_SEND_MSG_TO_GK						(u32)54	//��·æ��������Ϣ��GKʧ��
#define OPERATE_MUST_IN_IDLE_STATE					(u32)55	//ֻ��δ�ɹ���GK��������ִ�иò���
#define OPERATE_MUST_IN_NORMAL_STATE				(u32)56	//ֻ�е��ɹ���GK��������ִ�иò���
#define OPERATE_MUST_WAIT							(u32)57	//GKæ�����ڴ���ǰһ������


//GKC�ȴ�GK�ظ�ʱ�䣬OSP��ʱ(����Ϊ��λ)
#define DEFAULT_TIMEOUT         (DWORD)8000

//����OSP��ʱ���¼�����
#define EV_SET_TIMER			EV_MC_BGN
#define EV_KILL_TIMER			EV_MC_BGN + 1

//////////////////////////////////////////////////////////////////////////
// ��ؽṹ����
//////////////////////////////////////////////////////////////////////////

enum EGkcState //����̨״̬����
{
    GKC_STATE_IDLE                  = 0,
	GKC_STATE_NORMAL				= 1,
	GKC_WAIT_CONNECTTO_GK			= 2,
	GKC_WAIT_GET_USERLIST			= 3,
	GKC_WAIT_ADD_USER				= 4,
	GKC_WAIT_DEL_USER				= 5,
	GKC_WAIT_MODIFY_USER			= 6,
	GKC_WAIT_MODIFY_USERPASS		= 7,
	GKC_WAIT_USER_IS_EXIST			= 8,
	GKC_WAIT_GET_BASECFG			= 9,
	GKC_WAIT_SET_BASECFG			= 10,
	GKC_WAIT_GET_IPRNGLIST			= 11,
	GKC_WAIT_ADD_IPRNG				= 12,
	GKC_WAIT_DEL_IPRNG				= 13,
	GKC_WAIT_MODIFY_IPRNG			= 14,
	GKC_WAIT_GET_SUBNET_BANDLIST	= 15,
	GKC_WAIT_ADD_SUBNET_BANDWIDTH	= 16,
	GKC_WAIT_DEL_SUBNET_BANDWIDTH	= 17,
	GKC_WAIT_MODIFY_SUBNET_BANDWIDTH= 18,
	GKC_WAIT_SUBNET_BANDWIDTH		= 19,
	GKC_WAIT_GET_PASSWORD_LIST		= 20,
	GKC_WAIT_ADD_PASSWORD			= 21,
	GKC_WAIT_DEL_PASSWORD			= 22,
	GKC_WAIT_MODIFY_PASSWORD		= 23,
	GKC_WAIT_GET_ENDPOINTLIST		= 24,
	GKC_WAIT_ADD_ENDPOINT			= 25,
	GKC_WAIT_DEL_ENDPOINT			= 26,
	GKC_WAIT_MODIFY_ENDPOINT		= 27,
	GKC_WAIT_ENDPOINT				= 28,
	GKC_WAIT_GET_REG_ENDPOINTLIST	= 29,
	GKC_WAIT_DEL_REG_ENDPOINT		= 30,
	GKC_WAIT_GET_ENDPOINT_CALLLIST	= 31,
	GKC_WAIT_DEL_ENDPOINT_CALL	    = 32,
	GKC_WAIT_GET_PREFIX				= 33,
	GKC_WAIT_SET_PREFIX				= 34,
//	GKC_WAIT_GET_PREFIXRULES		= 35,
//	GKC_WAIT_SET_PREFIXRULES		= 36,
	GKC_WAIT_GET_GKREG_STATUS		= 37,   
	GKC_WAIT_ADD_PREFIX				= 38,
	GKC_WAIT_DEL_PREFIX				= 39,
	GKC_WAIT_ADD_NEIGHBORGK			= 40,
	GKC_WAIT_GET_NEIGHBORGK			= 41,
	GKC_WAIT_DEL_NEIGHBORGK			= 42,
	GKC_WAIT_GET_AUTHMETHOD			= 43,	
	GKC_WAIT_SET_AUTHMETHOD         = 44,
    GKC_WAIT_GET_ONEUSER			= 45,
    GKC_WAIT_GET_ETHNETPORT         = 46,
    GKC_WAIT_SET_ETHNETPORT         = 47,
    GKC_WAIT_SET_RADIUS             = 48,
    GKC_WAIT_GET_RADIUS             = 49,
	GKC_WAIT_GET_IPFORBIDLIST       = 50
};

//Ϊ���ϲ㷽��ʹ��,��װʵ����֤����(��ʽ)�Ĳ���
class CGkAuthMothod
{
public:
    CGkAuthMothod()
    {
        m_dwGkAuthMothod = 0;
    };
public:
    //������֤���Ե�32λֵ
    void SetAuthMethod(u32 dwGkAuthMothod)
    {
        m_dwGkAuthMothod = dwGkAuthMothod;
    }

    /*=============================================================================
    �� �� ��:GetNetAuthMethod
    ��    ��:��ȡ��������֤����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��������֤����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/12/26  4.0     ���    ����
    =============================================================================*/
    u32 GetNetAuthMethod(void) const
    { 
        return htonl( m_dwGkAuthMothod );
    }

    //��ȡ��֤���Ե�32λֵ
    u32 GetAuthMethod() const
    {
        return m_dwGkAuthMothod;
    }

    //���ò���Ҫ��֤
    void SetNotAuth()
    {
        m_dwGkAuthMothod = 0;
    };
    
    //�Ƿ���Ҫ��֤
    bool IsNeedAuth() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthIPForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthPassword
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    
    //����ip��֤������Ч
    void SetAuthIPAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPAllow;       
    };

    //����ip��֤��ֹ��Ч
    void SetAuthIPForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPForbid;
    };
    
    //�Ƿ�ip��֤������Ч
    bool IsAuthIPAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //�Ƿ�ip��֤��ֹ��Ч
    bool IsAuthIPForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //����ʵ����֤������Ч
    void SetAuthAliasAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasAllow;       
    };

    //����ʵ����֤��ֹ��Ч
    void SetAuthAliasForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasForbid;
    };
    
    //�Ƿ�ʵ����֤������Ч
    bool IsAuthAliasAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //�Ƿ�ʵ����֤��ֹ��Ч
    bool IsAuthAliasForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //����������֤
    void SetAuthPassword()
    {
        m_dwGkAuthMothod |= emAuthMethod_AuthPassword;
    };

    //�Ƿ�������֤
    bool IsAuthPassword() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthPassword) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    u32 m_dwGkAuthMothod; //��֤����32λֵ
};


//////////////////////////////////////////////////////////////////////////
// �����Զ��崰����Ϣ��������Ϣ���ݼ��ӿ�˵����
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//��½��ע��
//////////////////////////////////////////////////////////////////////////
//��½�ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_CONNECT_GK_SUCCESS     WM_USER + 1
//��½ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_CONNECT_GK_FAILED      WM_USER + 2
//�������֪ͨ(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DISCONNECT_FROM_GK_NOTIFY     WM_USER + 3

//////////////////////////////////////////////////////////////////////////
// ����ʱ��Ϣ
//////////////////////////////////////////////////////////////////////////
//��ȡ��ע��H323ʵ���б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_REGISTER_ENDPOINT_LIST_SUCCESS    WM_USER + 10
//��ȡ��ע��H323ʵ���б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_REGISTER_ENDPOINT_LIST_FAILED     WM_USER + 11

//ǿ��ע����ע��H323ʵ��ɹ�(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_UNREGISTER_ENDPOINT_SUCCESS    WM_USER + 12
//ǿ��ע����ע��H323ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_UNREGISTER_ENDPOINT_FAILED     WM_USER + 13

//��ȡʵ������б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_CALL_LIST_SUCCESS    WM_USER + 14
//��ȡʵ������б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_CALL_LIST_FAILED     WM_USER + 15

//ǿ�ƽ������гɹ�(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_STOP_CALL_SUCCESS    WM_USER + 16
//ǿ�ƽ�������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_STOP_CALL_FAILED     WM_USER + 17

//ʵ��ע��֪ͨ(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_ENDPOINT_REGISTER_NOTIFY   WM_USER + 20

//ʵ��ע��֪ͨ(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_ENDPOINT_UNREGISTER_NOTIFY   WM_USER + 21

//ʵ�����֪ͨ(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_CALL_NOTIFY   WM_USER + 22

//ʵ����н���֪ͨ(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_STOP_CALL_NOTIFY   WM_USER + 23

//ʵ����д���ı�֪ͨ(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_CALL_BANDWIDTH_CHANGE_NOTIFY   WM_USER + 24

//////////////////////////////////////////////////////////////////////////
// ������Ϣ -- ��������
//////////////////////////////////////////////////////////////////////////
//��ȡGK�������óɹ�(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_GET_BASECFG_SUCCESS    WM_USER + 30
//��ȡGK��������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_BASECFG_FAILED     WM_USER + 31

//����GK�������óɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_BASECFG_SUCCESS    WM_USER + 32
//����GK��������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_SET_BASECFG_FAILED     WM_USER + 33

//��ȡGK�����б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_PREFIX_LIST_SUCCESS    WM_USER + 34
//��ȡGK�����б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_PREFIX_LIST_FAILED     WM_USER + 35

//�������ųɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_PREFIX_SUCCESS    WM_USER + 36
//��������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_PREFIX_FAILED     WM_USER + 37

//ɾ�����ųɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_PREFIX_SUCCESS    WM_USER + 38
//ɾ������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_PREFIX_FAILED     WM_USER + 39

//��ȡ�ٽ�GK�������б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_NEIGHBOR_GK_LIST_SUCCESS    WM_USER + 40
//��ȡ�ٽ�GK�������б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_NEIGHBOR_GK_LIST_FAILED     WM_USER + 41

//�����ٽ�GK�������ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_NEIGHBOR_GK_SUCCESS    WM_USER + 42
//�����ٽ�GK������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_NEIGHBOR_GK_FAILED     WM_USER + 43

//ɾ���ٽ�GK�������ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_NEIGHBOR_GK_SUCCESS    WM_USER + 44
//ɾ���ٽ�GK������ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_NEIGHBOR_GK_FAILED     WM_USER + 45

//��ȡGK��֤��ʽ�ɹ�(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_GET_AUTH_METHOD_SUCCESS    WM_USER + 46
//��ȡGK��֤��ʽʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_AUTH_METHOD_FAILED     WM_USER + 47

//����GK��֤��ʽ�ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_AUTH_METHOD_SUCCESS    WM_USER + 48
//����GK��֤��ʽʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_SET_AUTH_METHOD_FAILED     WM_USER + 49

//���ñ���GKʹ�����ڳɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_ETH_NETPORT_SUCCESS    WM_USER + 50
//���ñ���GKʹ������ʧ��(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_SET_ETH_NETPORT_FAILED     WM_USER + 51

//��ȡ����GKʹ�����ڳɹ�(WPARAM)(u8),(LPARAM)(NULL)
#define GKC_DISP_GET_ETH_NETPORT_SUCCESS    WM_USER + 52
//��ȡ����GKʹ������ʧ��(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_GET_ETH_NETPORT_FAILED     WM_USER + 53

//����Radius�������ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_RADIUS_SUCCESS         WM_USER + 54
//����Radius������ʧ��(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_SET_RADIUS_FAILED          WM_USER + 55

//��ȡRadius�������ɹ�(WPARAM)(TRadiusConfigInfo),(LPARAM)(NULL)
#define GKC_DISP_GET_RADIUS_SUCCESS         WM_USER + 56
//��ȡRadius������ʧ��(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_GET_RADIUS_FAILED          WM_USER + 57

//////////////////////////////////////////////////////////////////////////
// ������Ϣ -- ���δ�������
//////////////////////////////////////////////////////////////////////////
//��ȡ���μ�����б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_SUBNET_BANDWIDTH_LIST_SUCCESS    WM_USER + 60
//��ȡ���μ�����б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_SUBNET_BANDWIDTH_LIST_FAILED     WM_USER + 61

//�������μ����ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_SUBNET_BANDWIDTH_SUCCESS    WM_USER + 62
//�������μ����ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_SUBNET_BANDWIDTH_FAILED     WM_USER + 63

//ɾ�����μ����ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_SUBNET_BANDWIDTH_SUCCESS    WM_USER + 64
//ɾ�����μ����ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_SUBNET_BANDWIDTH_FAILED     WM_USER + 65

//�޸����μ����ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_SUBNET_BANDWIDTH_SUCCESS    WM_USER + 66
//�޸����μ����ʧ��
#define GKC_DISP_MODIFY_SUBNET_BANDWIDTH_FAILED     WM_USER + 67

//////////////////////////////////////////////////////////////////////////
// ������Ϣ -- IP��Χ��֤����
//////////////////////////////////////////////////////////////////////////
//��ȡ��֤IP��Χ�б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_LIST_SUCCESS    WM_USER + 70
//��ȡ��֤IP��Χ�б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_LIST_FAILED     WM_USER + 71

//������֤IP��Χ�ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_IP_RANGE_SUCCESS    WM_USER + 72
//������֤IP��Χʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_IP_RANGE_FAILED     WM_USER + 73

//ɾ����֤IP��Χ�ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_IP_RANGE_SUCCESS    WM_USER + 74
//ɾ����֤IP��Χʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_IP_RANGE_FAILED     WM_USER + 75

//�޸���֤IP��Χ�ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_IP_RANGE_SUCCESS    WM_USER + 76
//�޸���֤IP��Χʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_IP_RANGE_FAILED     WM_USER + 77

//////////////////////////////////////////////////////////////////////////
// ������Ϣ -- ʵ����֤����
//////////////////////////////////////////////////////////////////////////
//��ȡ��֤ʵ���б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_ENDPOINT_LIST_SUCCESS    WM_USER + 80
//��ȡ��֤ʵ���б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_ENDPOINT_LIST_FAILED     WM_USER + 81

//������֤ʵ��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_ENDPOINT_SUCCESS    WM_USER + 82
//������֤ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_ENDPOINT_FAILED     WM_USER + 83

//ɾ����֤ʵ��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_ENDPOINT_SUCCESS    WM_USER + 84
//ɾ����֤ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_ENDPOINT_FAILED     WM_USER + 85

//�޸���֤ʵ��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_ENDPOINT_SUCCESS    WM_USER + 86
//�޸���֤ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_ENDPOINT_FAILED     WM_USER + 87

//////////////////////////////////////////////////////////////////////////
// �û�������Ϣ
//////////////////////////////////////////////////////////////////////////
//��ȡ�û���Ϣ�б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_USER_LIST_SUCCESS    WM_USER + 90
//��ȡ�û���Ϣ�б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_USER_LIST_FAILED     WM_USER + 91

//�����û��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_USER_SUCCESS    WM_USER + 92
//�����û�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_USER_FAILED     WM_USER + 93

//ɾ���û��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_USER_SUCCESS    WM_USER + 94
//ɾ���û�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_USER_FAILED     WM_USER + 95

//�޸��û��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_USER_SUCCESS    WM_USER + 96
//�޸��û�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_USER_FAILED     WM_USER + 97

//�޸��û�����ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_USER_PASSWORD_SUCCESS    WM_USER + 98
//�޸��û�����ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_USER_PASSWORD_FAILED     WM_USER + 99

//////////////////////////////////////////////////////////////////////////
// ������Ϣ -- ʵ����֤����
//////////////////////////////////////////////////////////////////////////
//��ȡ��֤ʵ���б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_PASSWORD_LIST_SUCCESS    WM_USER + 100
//��ȡ��֤ʵ���б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_PASSWORD_LIST_FAILED     WM_USER + 101

//������֤ʵ��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_PASSWORD_SUCCESS    WM_USER + 102
//������֤ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_PASSWORD_FAILED     WM_USER + 103

//ɾ����֤ʵ��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_PASSWORD_SUCCESS    WM_USER + 104
//ɾ����֤ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_PASSWORD_FAILED     WM_USER + 105

//�޸���֤ʵ��ɹ�(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_PASSWORD_SUCCESS    WM_USER + 106
//�޸���֤ʵ��ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_PASSWORD_FAILED     WM_USER + 107

//��ȡ��֤IP��Χ�б�ɹ�(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_FORBID_LIST_SUCCESS    WM_USER + 108
//��ȡ��֤IP��Χ�б�ʧ��(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_FORBID_LIST_FAILED     WM_USER + 109


//�ڲ�dlgͨ����Ϣ

#define GKC_SET_IP_AUTHOR			WM_USER + 200

#define GKC_SET_ENTITY_AUTHOR		WM_USER + 201

#define GKC_SET_PASSWORD_AUTHOR		WM_USER + 202

//��־�ļ���(���·��)
#define GKC_LOG										(LPSTR)"gkc.txt"

#endif //#define GKCLIBDEFINE_H
