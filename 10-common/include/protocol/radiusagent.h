/*****************************************************************************
ģ����      : RadiusAgent
�ļ���      : radiusagent.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���ýṹ���ӿں������塣
����        : ���Ҿ�
�汾        : V4.0  Copyright(C) 2004-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2006-08-15  4.0         ���Ҿ�      ����
******************************************************************************/
#ifndef __RADIUSAGENT_H
#define __RADIUSAGENT_H

#include "osp.h"
#include "radiusstack.h"
////////////////////////////////// �궨�� ////////////////////////////////
#define VER_RA "KDV RadiusAgent 40.01.01.00.01.060815"
#define VENDOR_ID       (u8*)"kdc"  

#define MAX_CONF_E164_LEN           (u16)64           //����E164�ų���
#define MAX_CONF_NAME_LEN           (u16)32           //����������󳤶�
#define MAX_RA_CLIENT_NAME_LEN      (u16)32           //�ͻ�������󳤶�
#define MAX_ACCOUNT_NUM_LEN         (u16)20           //�ʺ���󳤶�
#define MAX_ACCOUNT_PWD_LEN         (u16)16           //�ʺ�������󳤶�

#define LEN_ACCT_SESSION_ID         16               //�Ʒ�SessionID����(����)
#define MAX_CALLER_NUM_LEN          30               //���к�����󳤶�
#define MAX_CALLED_NUM_LEN          30               //���к�����󳤶�

//��֤���
#define RADIUS_AUTH_SUCCESS             0x00000000              //�ɹ�
#define RADIUS_AUTH_ACCT_NOT_EXIST      0x00000001              //�ʺŲ�����
#define RADIUS_AUTH_PWD_NOT_MATCH       0x00000002              //�ʺ����벻ƥ��
#define RADIUS_AUTH_ACCT_FORBID         0x00000003              //�ʺű����û�����
#define RADIUS_AUTH_PACKET_INVALID      0x00000004              //��֤����ʽ����ȷ
#define RADIUS_AUTH_TIME_OUT            0x000000ee              //��������ʱδ��Ӧ
#define RADIUS_AUTH_DB_FAIL             0x000000ef              //���ݿ����ʧ��
#define RADIUS_AUTH_OTHER_ERRPR         0x000000ff              //����

//�Ʒѽ��
#define RADIUS_ACCT_SUCCESS             0x00000000              //�ɹ�
#define RADIUS_ACCT_LACK_AUTH_ITEM      0x00000006              //ȱ����Ҫ����֤ѡ��
#define RADIUS_ACCT_LACK_ACCT_ITEM      0x00000008              //ȱ����Ҫ�ļƷ�ѡ��
#define RADIUS_ACCT_POLICY_FAIL         0x0000000c              //���Է������Ʒ�ʧ��
#define RADIUS_ACCT_NUM_IN_USE          0x000000f2              //�˺�����ʹ��
#define RADIUS_ACCT_CONF_NOT_END        0x000000e0              //������δ���� 
#define RADIUS_ACCT_CONF_ENDED          0x000000e1              //�����Ѿ����� 
#define RADIUS_ACCT_CONF_NOT_EXIST      0x000000ed              //���鲻����
#define RADIUS_ACCT_TIME_OUT            0x000000ee              //��������ʱδ��Ӧ
#define RADIUS_ACCT_DB_FAIL             0x000000ef              //���ݿ����ʧ��

//ҵ������
#define SERVICE_TYPE_ACCOUT_AUTH        0x0002              //�ʺ���֤
#define SERVICE_TYPE_TERMIN_AUTH        0x0003              //�ն˺�����֤
#define SERVICE_TYPE_CALL_AUTH          0x0004              //������֤
#define SERVICE_TYPE_PRE_CALC           0x000a              //Ԥ�����
#define SERVICE_TYPE_PRE_FEE            0x000b              //Ԥ�۷���
#define SERVICE_TYPE_REAL_FEE           0x000c              //ʵ�۷���

//�Ʒ���Ŀ
#define ACCT_ITEM_P2P                   0x0007              //��Ե�

//�Ʒ�����
#define ACCT_TYPE_BY_TIME                0x0001             //�����շ�
#define ACCT_TYPE_CALL_TRANSFOR          0x0005             //����ת��

//�Ʒѱ�־        
#define ACCT_FLAG_FREE                   0x0000             //���
#define ACCT_FLAG_CHARGE                 0x0001             //�շ�
#define ACCT_FLAG_RETURN_MONEY           0x0002             //����

//�Ʒ�״̬����
#define ACCT_STATUS_TYPE_START           0x0001              //��ʼ
#define ACCT_STATUS_TYPE_STOP            0x0002              //����
#define ACCT_STATUS_TYPE_UPDATE          0x0003              //ˢ��

//��������
#define CONF_TYPE_APPOINT                0x0001              //ԤԼ����
#define CONF_TYPE_CALLSET                0x0002              //���к�������
#define CONF_TYPE_P2P                    0x0005              //��Ե����
#define CONF_TYPE_THIRDPART              0x0006              //���������Ȼ���

//////////////////////////////// �ṹ���� //////////////////////////////

typedef u32  radAuthResult;
typedef u32  radAcctResult;

//��������
typedef struct tagConfName{
    u8   m_abyConfName[MAX_CONF_NAME_LEN+1];
    u16  m_wNameLen;
    
    tagConfName()
    {
        memset(m_abyConfName,0,sizeof(m_abyConfName));
        m_wNameLen = 0;
    }
}TConfName;

//�ͻ���Ϣ������MCU E164�� �� H323������
typedef struct tagClientInfo
{
    u8 abyClientName[MAX_RA_CLIENT_NAME_LEN+1];
    u16 m_wNameLen;    

    tagClientInfo()
    {
        memset(abyClientName,0,sizeof(abyClientName));
        m_wNameLen = 0;
    }
}TClientInfo;

//�ʻ���Ϣ������Radius��֤�ʺţ�
typedef struct tagAccountInfo{
    u8   m_abyAccoutNum[MAX_ACCOUNT_NUM_LEN+1];
    u16  m_wAccountLen;
    u8   m_abyPwd[MAX_ACCOUNT_PWD_LEN+1];
    u16  m_wPwdLen;

    tagAccountInfo()
    {
        memset(m_abyAccoutNum, 0 ,sizeof(m_abyAccoutNum));
        memset(m_abyPwd,0,sizeof(m_abyPwd));
        m_wAccountLen = 0;
        m_wPwdLen = 0;
    }
}TAccountInfo;

//��֤��Ϣ�ṹ
typedef struct tagAuthInfo{
    u32 m_dwServType;         //ҵ������(������ͨ�淶����)
    TClientInfo m_tClient;    //�ͻ�����/�ն˺���
    TAccountInfo m_tAccount;  //�˺���Ϣ(�˺�/����)   
     
    tagAuthInfo()
    {
        m_dwServType = SERVICE_TYPE_ACCOUT_AUTH;
    }
}TLibAuthInfo;

//��֤������Ӧ�ṹ
typedef struct tagAuthRspInfo{
    TClientInfo    m_tClient;
    radAuthResult  m_dwAuthResult;
    
    tagAuthRspInfo()
    {
        m_dwAuthResult = 0;
    }
    
}TLibAuthRspInfo;

//��ʼ����Ʒ���Ϣ
typedef struct tagConfAcctStartInfo{
    u8  m_abyAcctNum[MAX_ACCOUNT_NUM_LEN];       //�ͻ��ʺ�
    u16 m_wAcctNumLen;
    u8  m_abyAcctPwd[MAX_ACCOUNT_PWD_LEN];       //�ʺ�����
    u16 m_wAcctPwdLen;
    u32 m_dwServiceType;                             //ҵ�������
    u8  m_abyConfID[MAX_CONF_E164_LEN];            //����e164��
    u16 m_wConfIdLen;
    u8  m_abyConfName[MAX_CONF_NAME_LEN];        //��������
    u16 m_wConfNameLen;
    u8  m_abyAcctSessionId[LEN_ACCT_SESSION_ID];   //�Ʒ�sessionid����GKΪ����������䡣 

    u32  m_dwSiteRate;                   //��������
    u16  m_wTermNum;                     //�ն���
    u32  m_dwStartTime;                  //��ʼʱ�� UTC
    u32  m_dwStopTime;                   //����ʱ�� UTC
    u16  m_wMultiVoiceNum;               //������
    u16  m_wMultiPicNum;                  //�໭����
    u16  m_wRateAdaptNum;                //����������
    u16  m_wCascade;                     //�Ƿ�ʹ�ü���
    u16  m_wEncrypt;                     //����ģʽ
    u16  m_wDualVideo;                   //�Ƿ�ʹ��˫��
    u16  m_wDataConf;                    //�Ƿ��ٿ����ݻ���
    u16  m_wStream;                      //������ģʽ
    u32  m_dwAcctFlag;                   //�Ʒѱ�־
    u32  m_dwAcctStaus;                  //�Ʒ�״̬(��ʼ1�����2)
    u32  m_dwConfType;                   //��������

    tagConfAcctStartInfo()
    {
        memset(m_abyAcctNum,0,sizeof(m_abyAcctNum));
        m_wAcctNumLen = 0;
        memset(m_abyAcctPwd,0,sizeof(m_abyAcctNum));
        m_wAcctPwdLen = 0;
        m_dwServiceType = SERVICE_TYPE_REAL_FEE;
        memset(m_abyConfID,0,sizeof(m_abyConfID));
        m_wConfIdLen = 0;
        memset(m_abyConfName,0,sizeof(m_abyConfName));
        m_wConfNameLen = 0;
        memset(m_abyAcctSessionId,0,sizeof(m_abyAcctSessionId));
        m_dwSiteRate = 0;
        m_wTermNum = 0;
        m_dwStartTime = 0;
        m_dwStopTime = 0;
        m_wMultiVoiceNum = 0;
        m_wMultiPicNum = 0;
        m_wRateAdaptNum = 0;
        m_wCascade = 0;
        m_wEncrypt = 0;
        m_wDualVideo = 0;
        m_wDataConf = 0;
        m_wStream = 0;      
        m_dwAcctFlag = ACCT_FLAG_CHARGE;
        m_dwAcctStaus = ACCT_STATUS_TYPE_START;  
        m_dwConfType = CONF_TYPE_CALLSET;
    }

    BOOL32 SetConfName(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > MAX_CONF_NAME_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyConfName,pbyInBuf,wLen);
        m_wConfNameLen = wLen;
        return TRUE;
    }

    BOOL32 SetConfE164Id(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > MAX_CONF_E164_LEN ))
        {
            return FALSE;
        }
        memcpy(m_abyConfID,pbyInBuf,wLen);
        m_wConfIdLen = wLen;
        return TRUE;
    }
    
    BOOL32 SetAcctNum(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > MAX_ACCOUNT_NUM_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyAcctNum,pbyInBuf,wLen);
        m_wAcctNumLen = wLen;
        return TRUE;
    }

    BOOL32 SetAcctPwd(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > MAX_ACCOUNT_PWD_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyAcctPwd,pbyInBuf,wLen);
        m_wAcctPwdLen = wLen;
        return TRUE;
    }

    BOOL32 SetAcctSessionId(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > LEN_ACCT_SESSION_ID))
        {
            return FALSE;
        }
        memcpy(m_abyAcctSessionId,pbyInBuf,wLen);        
        return TRUE;
    }


    u16 GetAcctNumLen()
    {
        return m_wAcctNumLen;
    }
    
    u16 GetAcctPwdLen()
    {
        return m_wAcctPwdLen;
    }

    u16 GetConfIdLen()
    {
        return m_wConfIdLen;
    }

    u16 GetConfNameLen()
    {
        return m_wConfNameLen;
    }

    u16 GetAcctSessionId()
    {
        return LEN_ACCT_SESSION_ID;             
    }

}TLibConfAcctStartInfo;

//ֹͣ����Ʒ���Ϣ
typedef struct tagConfAcctStopInfo
{
    u8  m_abyAcctNum[MAX_ACCOUNT_NUM_LEN];       //�ͻ��ʺ�
    u16 m_wAcctNumLen;
    u8  m_abyAcctPwd[MAX_ACCOUNT_PWD_LEN];       //�ʺ�����     
    u16 m_wAcctPwdLen;
    u8  m_abyAcctSessionId[LEN_ACCT_SESSION_ID + 1];   //�Ʒ�sessionid����GKΪ����������䡣 

    tagConfAcctStopInfo()
    {
        memset(m_abyAcctNum,0,sizeof(m_abyAcctNum));
        m_wAcctNumLen = 0;
        memset(m_abyAcctPwd,0,sizeof(m_abyAcctNum));
        m_wAcctPwdLen = 0;
        memset(m_abyAcctSessionId,0,sizeof(m_abyAcctSessionId));
    }

    BOOL32 SetAcctNum(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > MAX_ACCOUNT_NUM_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyAcctNum,pbyInBuf,wLen);
        m_wAcctNumLen = wLen;
        return TRUE;
    }

    BOOL32 SetAcctPwd(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > MAX_ACCOUNT_PWD_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyAcctPwd,pbyInBuf,wLen);
        m_wAcctPwdLen = wLen;
        return TRUE;
    }

    BOOL32 SetAcctSessionId(u8* pbyInBuf, u16 wLen)
    {
        if((NULL == pbyInBuf)||(wLen > LEN_ACCT_SESSION_ID))
        {
            return FALSE;
        }
        memcpy(m_abyAcctSessionId,pbyInBuf,wLen);
        return TRUE;
    }

    u16 GetAcctNumLen()
    {
        return m_wAcctNumLen;
    }
    
    u16 GetAcctPwdLen()
    {
        return m_wAcctPwdLen;
    }

    u16 GetAcctSessionId()
    {
        return LEN_ACCT_SESSION_ID;             
    }
    
}TLibConfAcctStopInfo;


//ˢ�»���Ʒ���Ϣ(���ּƷѽ���)
typedef struct tagConfAcctUpdateInfo
{
    u8  m_abyAcctNum[MAX_ACCOUNT_NUM_LEN];       //�ͻ��ʺ�
    u16 m_wAcctNumLen;
    u8  m_abyAcctSessionId[LEN_ACCT_SESSION_ID];   //�Ʒ�sessionid����GKΪ����������䡣
    u16 m_wSessIdLen;
    
    tagConfAcctUpdateInfo()
    {
        memset(m_abyAcctNum,0,sizeof(m_abyAcctNum));
        m_wAcctNumLen = 0;
        memset(m_abyAcctSessionId,0,sizeof(m_abyAcctSessionId));
        m_wSessIdLen = 0;
    }
    
    BOOL32 SetAcctNum(u8* pbyInBuf, u16 wLen)
    {
        memset(m_abyAcctNum,0,sizeof(m_abyAcctNum));
        m_wAcctNumLen = 0;
        if((NULL == pbyInBuf)||(wLen > MAX_ACCOUNT_NUM_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyAcctNum,pbyInBuf,wLen);
        m_wAcctNumLen = wLen;
        return TRUE;
    }    
   
    BOOL32 SetAcctSessionId(u8* pbyInBuf, u16 wLen)
    {
        memset(m_abyAcctSessionId,0,sizeof(m_abyAcctSessionId));
        m_wSessIdLen = 0;
        
        if((NULL == pbyInBuf)||(wLen > LEN_ACCT_SESSION_ID))
        {
            return FALSE;
        }
        memcpy(m_abyAcctSessionId,pbyInBuf,wLen);
        m_wSessIdLen = LEN_ACCT_SESSION_ID;
        return TRUE;
    }
    
    u16 GetAcctNumLen()
    {
        return m_wAcctNumLen;
    }
    
    u16 GetSessionIdLen()
    {
        return m_wSessIdLen;
    }    
    
}TLibConfAcctUpdateInfo;

//���мƷ���Ϣ
typedef struct tagCallAcctInfo{
    u32 m_dwServiceType;                            //ҵ�������
    u32 m_dwAcctStatus;                             //�Ʒ�״̬(��ʼ1/����2)
    u8  m_abyUserName[MAX_RA_CLIENT_NAME_LEN + 1];         //�û���/�ն˺���
    u16 m_wUserNameLen;                              
    u8  m_abyAcctSessId[LEN_ACCT_SESSION_ID +1];   //һ�μƷ�ID
    u16  m_wSessIdLen;
    u8  m_abyMulSId[LEN_ACCT_SESSION_ID + 1];       //����Ʒ�Id
    u16 m_wMulSIdLen;
    u8  m_abyCallerNum[MAX_CALLER_NUM_LEN + 1];         //���к���
    u16 m_wCallerLen;
    u8  m_abyCalledNum[MAX_CALLED_NUM_LEN + 1];         //���к���
    u16 m_wCalledLen;
    u32 m_dwStartTime;                              //�Ʒѿ�ʼʱ��
    u32 m_dwStopTime;                               //�Ʒѽ���ʱ��
    u32 m_dwAcctItem;                               //�Ʒ���Ŀ
    u32 m_dwAcctType;                               //�Ʒ�����
    u32 m_dwAcctFlay;                               //�Ʒѱ�־

    tagCallAcctInfo()
    {
        memset(m_abyUserName,0,sizeof(m_abyUserName));
        m_wUserNameLen = 0;
        m_dwServiceType = SERVICE_TYPE_REAL_FEE;
        memset(m_abyAcctSessId,0,sizeof(m_abyAcctSessId));
        m_wSessIdLen = 0;
        memset(m_abyMulSId,0,sizeof(m_abyMulSId));
        m_wMulSIdLen = 0;
        memset(m_abyCallerNum,0,sizeof(m_abyCallerNum));
        m_wCallerLen = 0;
        memset(m_abyCalledNum,0,sizeof(m_abyCalledNum));
        m_wCalledLen = 0;
        m_dwStartTime = 0;
        m_dwStopTime = 0;
        m_dwAcctItem = ACCT_ITEM_P2P;
        m_dwAcctType = ACCT_TYPE_BY_TIME ;
        m_dwAcctFlay = ACCT_FLAG_CHARGE;
        m_dwAcctStatus = ACCT_STATUS_TYPE_START;
    }

    BOOL32 SetUserName(u8* pbyBuf, u16 wBufLen)
    {
        if((NULL == pbyBuf)||(wBufLen > MAX_RA_CLIENT_NAME_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyUserName,pbyBuf,wBufLen);
        m_wUserNameLen = wBufLen;
        return TRUE;
    }

    BOOL32 SetAcctSessionID(u8* pbyBuf, u16 wBufLen)
    {
        if((NULL == pbyBuf)||(wBufLen > LEN_ACCT_SESSION_ID))
        {
            return FALSE;
        }
        memcpy(m_abyAcctSessId,pbyBuf,wBufLen);
        m_wSessIdLen = wBufLen;
        return TRUE;
    }

    BOOL32 SetAcctMulSessionID(u8* pbyBuf, u16 wBufLen)
    {
        if((NULL == pbyBuf)||(wBufLen > LEN_ACCT_SESSION_ID))
        {
            return FALSE;
        }
        memcpy(m_abyMulSId,pbyBuf,wBufLen);
        m_wMulSIdLen = wBufLen;
        return TRUE;
    }

}TLibCallAcctInfo;

//�Ʒ�������Ӧ�ṹ
typedef struct tagAcctRspInfo{
    TClientInfo    m_tClientInfo;
    radAcctResult  m_dwAcctResult;   //�Ʒ�������
    u32 m_dwAcctType;                //��������:1-��ʼ 2-���� 3-����
    
    tagAcctRspInfo()
    {
        m_dwAcctResult = 0;
        m_dwAcctType = 1;
    }
}TLibAcctRspInfo;


//�ص������ṹ����
typedef void (*CBAuthResponse)(RadSessionHandle handle, TLibAuthRspInfo *ptAuthResult);          
typedef void (*CBAcctStartResponse)(RadSessionHandle handle,TLibAcctRspInfo *ptAcctStartRsp);
typedef void (*CBAcctStopResponse)(RadSessionHandle handle,TLibAcctRspInfo *ptAcctStopRsp);
typedef void (*CBAcctUpdateResponse)(RadSessionHandle handle,TLibAcctRspInfo *ptAcctUpdateRsp);

typedef struct tagRadiusAgentEvent{
    CBAuthResponse         m_pfCBAuthRsp;                //��֤��Ӧ
    CBAcctStartResponse    m_pfCBAcctStartRsp;           //�Ʒѿ�ʼ��Ӧ
    CBAcctStopResponse     m_pfCBAcctStopRsp;            //�Ʒѽ�����Ӧ
    CBAcctUpdateResponse   m_pfCBAcctUpdateRsp;          //�ƷѸ�����Ӧ

    tagRadiusAgentEvent()
    {
        m_pfCBAuthRsp = NULL;
        m_pfCBAcctStartRsp = NULL;
        m_pfCBAcctStopRsp = NULL;
        m_pfCBAcctUpdateRsp = NULL;
    }
}TRadiusAgentEvent;


//////////////////////////////// �ӿں���//////////////////////////
/*====================================================================
�������� InitRadiusStack
���ܣ�   ��ʼ��RadiusЭ��ջ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
           dwLocalIP    ����IP
           dwServerIP   ��֤������IP
           pSecret      Radius������Կ
           wSecretLen   ��Կ����
           wAuthPort     ��֤�˿�
           wAcctPort     �ƷѶ˿�
����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 InitRadiusAgent(u32 dwLocalIP,u32 dwServerIP, u8 *pSecret = NULL, u8 bySecretLen = 0, u16 wAuthPort = 1812, u16 wAcctPort = 1813);


/*====================================================================
��������  SetAgentCallBack
���ܣ�    ���ûص�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          ptAgentEvent �ص��¼�ָ��
����ֵ˵����
====================================================================*/
void SetAgentCallBack(TRadiusAgentEvent *ptAgentEvent);

/*====================================================================
��������  StartRadiusAgent
���ܣ�    ����RadiusAgent
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          
����ֵ˵����
====================================================================*/
void StartRadiusAgent();


/*====================================================================
�������� SendAuthRequest
���ܣ�   ������֤����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          tAuthInfo   ��֤��Ϣ
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 SendAuthRequest(TLibAuthInfo *ptAuthInfo,
                     u8* pbyUserData = NULL, u16 wDateLen = 0);

/*====================================================================
�������� SendConfAcctStartRequest
���ܣ�   ���Ϳ�ʼ����Ʒ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
        tAcctStartInfo  ����Ʒ���Ϣ
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 SendConfAcctStartRequest(TLibConfAcctStartInfo *ptAcctStartInfo,
                              u8* pbyUserData = NULL, u16 wDateLen = 0);


/*====================================================================
�������� SendConfAcctStopRequest
���ܣ�   ֹͣ����Ʒ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          tAcctStopInfo  �Ʒ�ֹͣ��Ϣ
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 SendConfAcctStopRequest(TLibConfAcctStopInfo *ptAcctStopInfo,
                             u8* pbyUserData = NULL, u16 wDateLen = 0);

/*====================================================================
�������� SendConfAcctUpdateRequest
���ܣ�   ˢ�»���Ʒ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          tAcctUpdateInfo  �Ʒ�ֹͣ��Ϣ
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 SendConfAcctUpdateRequest(TLibConfAcctUpdateInfo *ptAcctUpdateInfo,
                             u8* pbyUserData = NULL, u16 wDateLen = 0);

/*====================================================================
�������� GetUserData
���ܣ�   ��radius session�ж����ݴ���û�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 GetUserData(RadSessionHandle hSession, u8* pbyBuf, u16 wInLen, u16 &wOutLen);

/*====================================================================
�������� SendCallAcctStartRequest
���ܣ�   ���Ϳ�ʼ���мƷ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
        tCallStartInfo  ����Ʒ���Ϣ
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 SendCallAcctStartRequest(TLibCallAcctInfo *ptCallStartInfo);


/*====================================================================
�������� SendCallAcctStoptRequest
���ܣ�   ���ͽ������мƷ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
        tCallStopInfo  ����Ʒ���Ϣ
����ֵ˵�������ͳɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 SendCallAcctStoptRequest(TLibCallAcctInfo *ptCallStopInfo);


/*====================================================================
�������� �ر�Radius Session
���ܣ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 CloseSession(RadSessionHandle hSession);


/*====================================================================
�������� ֹͣRadiusAgent
���ܣ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
BOOL32 StopRadiusAgent();








 


#endif //__RADIUSAGENT_H
