/*****************************************************************************
ģ����      : KDV RS
�ļ���      : radiusinterface.h
����ļ�    : 
�ļ�ʵ�ֹ���: Radius ������֤/�Ʒѽӿڶ��塣�� mcu �Լ� gk ���á�
����        : ���Ҿ�
�汾        : V4.0  Copyright(C) 2004-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2006-10-17  4.0         ���Ҿ�         ����
2007-03-13  4.0         ���Ҿ�       ����sessionid error
******************************************************************************/
#ifndef ___RADIUSINTERFACE_H
#define ___RADIUSINTERFACE_H

#include "osp.h"
#include "kdvdef.h"
#include "eventid.h"

/*****************************���ȶ���**********************************************/
#define LEN_RADIUS_SESSION_ID    (u16)16          //����ƷѻỰid   
#define MAX_RADIUS_ACCT_NUM_LEN       (u16)20         //����Ʒ��ʺ���󳤶�
#define MAX_RADIUS_ACCT_PWD_LEN       (u16)16          //������󳤶�
#define MAX_CONF_NAME_LEN             (u16)32          //����������󳤶�
#define MAX_CONF_E164_LEN             (u16)64     //E164����󳤶�


/*****************************�Ʒѽ�����붨��**********************************************/
#define RADIUS_INTER_ACCTING_SUCCESS          0x00000000              //�Ʒ�����ɹ�
#define RADIUS_INTER_ACCT_NOT_EXIST           0x00000001              //�ʺŲ�����
#define RADIUS_INTER_INVALID_PWD              0x00000002              //�ʺ����벻ƥ��
#define RADIUS_INTER_CONF_NOT_END             0x000000e0              //������δ����
#define RADIUS_INTER_CONF_NOT_EXIST           0x000000ed              //���鲻���ڻ��ѽ���
#define RADIUS_INTER_TIME_OUT                 0x000000ee              //��������ʱδ��Ӧ
#define RADIUS_INTER_DB_FAIL                  0x000000ef              //���ݿ����ʧ��
#define RADIUS_INTER_GK_NOT_SUPPORT_ACCT      0x000000f0              //GKδ�����Ʒѹ���
#define RADIUS_INTER_GK_OP_FAILED             0x000000f1              //GK�ƷѲ���ʧ��
#define RADIUS_INTER_ACCT_IN_USE              0x000000f2              //�˺�����ʹ��
#define RADIUS_INTER_SESSION_ID_NULL          0x000000f3              //�ƷѻỰIDΪ��
#define RADIUS_INTER_GK_INSTANCE_FULL         0x000000f4              //GK�Ʒ�ʵ����
#define RADIUS_INTER__OTHER_ERRPR             0x000000ff              //��������


/*******************����Ʒ�App�ż��˿ڶ���**********************************************/
//GK��RadiusӦ�ú�
#define AID_GK_RADIUS_CLIENT             (AID_GKS_BGN + 5)

#define  IN
#define  OUT
/*******************����Ʒ�����¼��Ŷ���**********************************************/
OSPEVENT(GKRADIUS_START, GKOSPEVENT_END - 100);

//mcu����Ʒ�ע����Ϣ
OSPEVENT(EV_MG_CONF_ACCTING_REG, GKRADIUS_START + 1);
OSPEVENT(EV_GM_CONF_ACCTING_REG_RSP, GKRADIUS_START + 2);  

//��ʼ����Ʒ�����
OSPEVENT(EV_MG_CONF_ACCTING_START, GKRADIUS_START + 3);  
//��ʼ����Ʒ�������Ӧ
OSPEVENT(EV_GM_CONF_ACCTING_START_RSP, GKRADIUS_START + 4);

//ֹͣ����Ʒ�����
OSPEVENT(EV_MG_CONF_ACCTING_STOP, GKRADIUS_START + 5);
//ֹͣ����Ʒ�������Ӧ
OSPEVENT(EV_GM_CONF_ACCTING_STOP_RSP, GKRADIUS_START + 6);

//����Ʒ�״̬�ϱ�GK��֪ͨ����Ϣ�� u8(�Ʒѻ������ byConfNum) + TAcctSessionId[byConfNum]; ��ʱ����
OSPEVENT(EV_MG_CONF_ACCTING_STATUS_NTF, GKRADIUS_START + 7);

//����Ʒ�״̬�쳣֪ͨ����Ϣ�� u8(�Ʒ�״̬�쳣������� byConfNum) + TAcctSessionId[byConfNum]; ʵʱ����
OSPEVENT(EV_GM_CONF_ACCTING_STATUS_NTF, GKRADIUS_START + 8);


OSPEVENT(GKRADIUS_END, GKRADIUS_START + 50);



/*******************���ö�ٳ�������**********************************************/
//�Ʒ���������
typedef enum 
{
    emRadReqType_START = (u32)1,  
    emRadReqype_STOP = (u32)2,
   emRadReqType_UPDATE = (u32)3,
}ERadiusReqType;


/*******************�ṹ�嶨��**********************************************/
//�Ʒ�����ỰID�ṹ(����16B)
typedef struct tagAcctSessionId
{
    u8 m_abyContent[LEN_RADIUS_SESSION_ID];  //GK ����ļƷѱ�ʾ 
                                                   //�������ָ�������Ʒ������Լ�ƥ�俪ʼ�ͽ�������

    tagAcctSessionId()
    {
        memset(m_abyContent,0,sizeof(m_abyContent));
    }

    BOOL32 SetAcctSessionId(IN u8* pBuf, IN u16 wBufLen)
    {
        if((NULL == pBuf)||(wBufLen > LEN_RADIUS_SESSION_ID))
        {
            return FALSE;
        }
        memcpy(m_abyContent,pBuf,wBufLen);
        return TRUE;
    }

    BOOL32 GetAcctSessionId(IN OUT u8 *pBuf, IN u16 wBufLen, OUT u16 &wOutLen)
    {
        if((wBufLen < LEN_RADIUS_SESSION_ID)||(NULL == pBuf))
        {
            wOutLen = 0;
            return FALSE;
        }
        else
        {
            wOutLen = LEN_RADIUS_SESSION_ID;
            memcpy(pBuf,m_abyContent,LEN_RADIUS_SESSION_ID);
            return TRUE;
        }
    }   

    u8* GetAcctSessionId()
    {
        return m_abyContent;
    }

    u16 GetAcctSessionIdLen()
    {
        return LEN_RADIUS_SESSION_ID;
    }
    
    //�ж�session id �Ƿ�Ϊ��
    BOOL32 IsSessionIdNull()  
    {
        u8 abyTmp[LEN_RADIUS_SESSION_ID] = {0};
        if(0 == memcmp(abyTmp,m_abyContent,LEN_RADIUS_SESSION_ID))  //ȫ0��session id ��Ϊnull
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }  
    }
}TAcctSessionId;

//�Ʒ��ʺŽṹ
typedef struct tagConfAcctNum
{
    u8  m_abyAcctNum[MAX_RADIUS_ACCT_NUM_LEN];        
    u16 m_wAcctNumLen;
    
    tagConfAcctNum()
    {
        memset(m_abyAcctNum,0,sizeof(m_abyAcctNum));
        m_wAcctNumLen = 0;        
    }
    
    BOOL32 SetAcctNum(IN u8* pBuf, IN u16 wBufLen)
    {
        if((NULL == pBuf)||(wBufLen > MAX_RADIUS_ACCT_NUM_LEN))
        {
            return FALSE;
        }
        memset(m_abyAcctNum,0,sizeof(m_abyAcctNum));
        memcpy(m_abyAcctNum,pBuf,wBufLen);
        m_wAcctNumLen= htons(wBufLen);
        return TRUE;
    }

    BOOL32 GetAcctNum(IN OUT u8 *pBuf, IN u16 wBufLen, OUT u16 &wOutLen)
    {
        u16 wTmp = ntohs(m_wAcctNumLen);
        if((wBufLen < ntohs(m_wAcctNumLen))||(NULL == pBuf))
        {
            wOutLen = 0;
            return FALSE;
        }
        else
        {
            wOutLen = ntohs(m_wAcctNumLen);
            memcpy(pBuf,m_abyAcctNum,wOutLen);
            return TRUE;
        }
    }

    u16 GetAcctNumLen()
    {
        return ntohs(m_wAcctNumLen);   
    }   
}TConfAcctNum;

//�Ʒ��ʺ�����ṹ
typedef struct tagConfAcctPwd{
    u8  m_abyAcctPwd[MAX_RADIUS_ACCT_PWD_LEN];       
    u16 m_wAcctPwdLen;
    
    tagConfAcctPwd()
    {
        memset(m_abyAcctPwd,0,sizeof(m_abyAcctPwd));
        m_wAcctPwdLen = 0;               
    }
    
    BOOL32 SetAcctPwd(IN u8* pBuf, IN u16 wBufLen)
    {
        if((NULL == pBuf)||(wBufLen > MAX_RADIUS_ACCT_PWD_LEN))
        {
            return FALSE;
        }
        memset(m_abyAcctPwd,0,sizeof(m_abyAcctPwd));
        memcpy(m_abyAcctPwd,pBuf,wBufLen);
        m_wAcctPwdLen = htons(wBufLen);
        return TRUE;
    }

    BOOL32 GetAcctPwd(IN OUT u8 *pBuf, IN u16 wBufLen, OUT u16 &wOutLen)
    {
        if((wBufLen < ntohs(m_wAcctPwdLen))||(NULL == pBuf))
        {
            wOutLen = 0;
            return FALSE;
        }
        else
        {
            wOutLen = ntohs(m_wAcctPwdLen);
            memcpy(pBuf,m_abyAcctPwd,wOutLen);
            return TRUE;
        }
    }

    u16 GetAcctPwdLen()
    {
        return ntohs(m_wAcctPwdLen);   
    }  

}TConfAcctPwd;

//��ʼ�Ʒ�������Ϣ�ṹ
typedef struct tagConfAcctStartReq
{
    u32 m_dwSeqNum;                        //�Ʒ��������к�
    TConfAcctNum m_tAcctNum;               //�Ʒ��ʺ�
    TConfAcctPwd m_tAcctPwd;               //�Ʒ��ʺ�����
    u8  m_abyConfName[MAX_CONF_NAME_LEN];   //��������
    u16 m_wConfNameLen;
    u8 m_abyConfId[MAX_CONF_E164_LEN];      //����E164��
    u16 m_wConfIdLen;
    u32  m_dwSiteRate;                   //��������
    u16  m_wTermNum;                     //�ն���
    u16  m_wMulVoiceNum;                 //������
    u16  m_wMulPicNum;                   //�໭����
    u16  m_wRateAdapNum;                 //����������
    u16  m_wUseCasd;                     //�Ƿ�ʹ�ü���(1:ʹ�� 0:��ʹ��)
    u16  m_wUseEncrypt;                  //�Ƿ�ʹ�ü���
    u16  m_wUseDualVideo;                //�Ƿ�ʹ��˫��
    u16  m_wUseDataConf;                 //�Ƿ��ٿ����ݻ���
    u16  m_wUseStream;                   //�Ƿ�ʹ����ý���鲥

    tagConfAcctStartReq()
    {
        m_dwSeqNum = 0;
        //m_emReqType = htonl(emRadReqType_START);
        memset(&m_tAcctNum,0,sizeof(m_tAcctNum));
        memset(&m_tAcctPwd,0,sizeof(m_tAcctPwd));
        memset(m_abyConfName,0,sizeof(m_abyConfName));
        m_wConfNameLen = 0;
        memset(m_abyConfId,0,sizeof(m_abyConfId));
        m_wConfIdLen = 0;
        m_dwSiteRate = 0;
        m_wTermNum = 0;
        m_wMulVoiceNum = 0;
        m_wMulPicNum = 0;
        m_wRateAdapNum = 0;
        m_wUseCasd = 0;
        m_wUseEncrypt = 0;
        m_wUseDualVideo = 0;
        m_wUseDataConf = 0;
        m_wUseStream = 0;      
    }

    //���ݳ�Ա��������
    
    //��Ϣ���к�
    void SetSeqNum(u32 dwSeqNum)
    {
        m_dwSeqNum = htonl(dwSeqNum);
    }
    u32 GetSeqNum()
    {
        return ntohl(m_dwSeqNum);
    }

    BOOL32 SetAcctNum(IN u8* pbyBuf, IN u16 wBufLen)
    {
        return m_tAcctNum.SetAcctNum(pbyBuf,wBufLen);
    }

    TConfAcctNum & GetAcctNum()
    {
        return m_tAcctNum;
    }

    BOOL32 SetAcctPwd(IN u8* pbyBuf, IN u16 wBufLen)
    {
        return m_tAcctPwd.SetAcctPwd(pbyBuf,wBufLen);
    }
    
    TConfAcctPwd& GetAcctPwd()
    {
        return m_tAcctPwd;
    }

    //��������
    BOOL32 SetConfName(IN u8* pBuf, IN u16 wBufLen)
    {
        if((NULL == pBuf)||(wBufLen > MAX_CONF_NAME_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyConfName,pBuf,wBufLen);
        m_wConfNameLen = htons(wBufLen);
        return TRUE;
    }
    BOOL32 GetConfName(IN OUT u8 *pBuf, IN u16 wBufLen, OUT u16 &wOutLen)
    {
        if((wBufLen < ntohs(m_wConfNameLen))||(NULL == pBuf))
        {
            wOutLen = 0;
            return FALSE;
        }
        else
        {
            wOutLen = ntohs(m_wConfNameLen);
            memcpy(pBuf,m_abyConfName,wOutLen);
            return TRUE;
        }
    }
    u16 GetConfNameLen()
    {
        return ntohs(m_wConfNameLen);   
    }

    //����Id(E164)����
    BOOL32 SetConfId(IN u8* pBuf, IN u16 wBufLen)
    {
        if((NULL == pBuf)||(wBufLen > MAX_CONF_E164_LEN))
        {
            return FALSE;
        }
        memcpy(m_abyConfId,pBuf,wBufLen);
        m_wConfIdLen = htons(wBufLen);
        return TRUE;
    }
    BOOL32 GetConfId(IN OUT u8 *pBuf, IN u16 wBufLen, OUT u16 &wOutLen)
    {
        if((wBufLen < ntohs(m_wConfIdLen))||(NULL == pBuf))
        {
            wOutLen = 0;
            return FALSE;
        }
        else
        {
            wOutLen = ntohs(m_wConfIdLen);
            memcpy(pBuf,m_abyConfId,wOutLen);
            return TRUE;
        }
    }
    u16 GetConfIdLen()
    {
        return ntohs(m_wConfIdLen);
    }

    //��������
    void SetSiteRate(u32 dwSiteRate)
    {
        m_dwSiteRate = htonl(dwSiteRate);
    }
    u32 GetSiteRate()
    {
        return ntohl(m_dwSiteRate);
    }

    //�ն���
    void SetTermNum(u16 mTermNum)
    {
        m_wTermNum = htons(mTermNum) ;
    }
    u16 GetTermNum()
    {
        return ntohs(m_wTermNum);
    }

    //������
    void SetMulVoiceNum(u16 mMulVoiceNum)
    {
        m_wMulVoiceNum = htons(mMulVoiceNum)  ;
    }
    u16 GetMulVoiceNum()
    {
        return ntohs(m_wMulVoiceNum);
    }

    //�໭����
    void SetMulPicNum(u16 mMulPicNum)
    {
        m_wMulPicNum = htons(mMulPicNum)  ;
    }
    u16 GetMulPicNum()
    {
        return ntohs(m_wMulPicNum);
    }

    //����������
    void SetRateAdapNum(u16 mRateAdapNum)
    {
        m_wRateAdapNum = htons(mRateAdapNum)  ;
    }
    u16 GetRateAdapNum()
    {
        return ntohs(m_wRateAdapNum);
    }

    //�Ƿ�ʹ�ü���
    void SetUseCascade(u16 mCascade)
    {
        m_wUseCasd = htons(mCascade);
    }
    u16 GetUseCascade()
    {
        return ntohs(m_wUseCasd);
    }

    //�Ƿ�ʹ�ü���
    void SetUseEncrypt(u16 mEncrypt)
    {
        m_wUseEncrypt = htons(mEncrypt);
    }
    u16 GetUseEncrypt()
    {
        return ntohs(m_wUseEncrypt);
    }

    //�Ƿ�ʹ��˫��
    void SetUseDualVideo(u16 mDualVideo)
    {
        m_wUseDualVideo = htons(mDualVideo);
    }
    u16 GetUseDualVideo()
    {
        return ntohs(m_wUseDualVideo);
    }

    //�Ƿ�ʹ�����ݻ���
    void SetUseDataConf(u16 mDataConf)
    {
        m_wUseDataConf = htons(mDataConf)  ;
    }
    u16 GetUseDataConf()
    {
        return ntohs(m_wUseDataConf);
    }
    
    //�Ƿ�ʹ����ý���鲥
    void SetUseStream(u16 mStream)
    {
         m_wUseStream =htons(mStream)  ;
    }
    u16 GetUseStream()
    {
        return ntohs(m_wUseStream);
    }    
}TConfAcctStartReq;

//ֹͣ�Ʒ�����ṹ
typedef struct tagConfAcctStopReq
{
    u32 m_dwSeqNum;                                   //�Ʒ��������к�
    TConfAcctNum   m_tAcctNum;                        //�ʺ�
    TConfAcctPwd   m_tAcctPwd;                        //����
    TAcctSessionId m_tSessionId;                      //�ƷѻỰid
    
 
    tagConfAcctStopReq()
    {
        m_dwSeqNum = 0;
        memset(&m_tSessionId,0,sizeof(TAcctSessionId));
        memset(&m_tAcctNum,0,sizeof(TConfAcctNum));
        memset(&m_tAcctPwd,0,sizeof(TConfAcctPwd));
    }

     //�Ựid
    BOOL32 SetSessionId(IN u8* pbyBuf, IN u16 wBufLen)
    {
        return m_tSessionId.SetAcctSessionId(pbyBuf,wBufLen);
    }

    TAcctSessionId& GetSessionId()
    {
        return m_tSessionId;
    }
    
    //��Ϣ���к�
    void SetSeqNum(u32 dwSeqNum)
    {
        m_dwSeqNum = htonl(dwSeqNum);
    }
    u32 GetSeqNum()
    {
        return ntohl(m_dwSeqNum);
    }

    BOOL32 SetAcctNum(IN u8* pbyBuf, IN u16 wBufLen)
    {
        return m_tAcctNum.SetAcctNum(pbyBuf,wBufLen);
    }

    TConfAcctNum & GetAcctNum()
    {
        return m_tAcctNum;
    }

    BOOL32 SetAcctPwd(IN u8* pbyBuf, IN u16 wBufLen)
    {
        return m_tAcctPwd.SetAcctPwd(pbyBuf,wBufLen);
    }
    
    TConfAcctPwd& GetAcctPwd()
    {
        return m_tAcctPwd;
    }
    
}TConfAcctStopReq;

//����Ʒ�Ӧ��ṹ
typedef struct tagConfAcctRsp
{
    u32 m_dwSeqNum;                 //��Ӧ��Ϣ���к�(���������к���ͬ)
    u32 m_emReqType;               //��Ӧ�ļƷ���������
    u32 m_dwRspVal;                //�ƷѲ������
    TAcctSessionId m_tSessionId;   //�Ʒ�id. ���ڼƷѿ�ʼ�������·���ģ����ڼƷѽ�������ͬ������Ϣһ��
                    

    tagConfAcctRsp()
    {
        m_dwSeqNum = 0;
        m_emReqType = htonl(1);
        m_dwRspVal = 0;
        memset(&m_tSessionId,0,sizeof(m_tSessionId));
    }

    //���к�
    void SetSeqNum(u32 dwSeqNum)
    {
        m_dwSeqNum = htonl(dwSeqNum);
    }
    u32 GetSeqNum()
    {
        return ntohl(m_dwSeqNum);
    }

    //��������
    void SetRequestType(u32 emReqType)
    {
        m_emReqType = htonl(emReqType);
    }
    ERadiusReqType GetRequsetType()
    {
        return ERadiusReqType(ntohl(m_emReqType));
    } 

    //�Ựid
    BOOL32 SetSessionId(IN u8 *pbyBuf, IN u16 wBufLen)
    {
        return m_tSessionId.SetAcctSessionId(pbyBuf,wBufLen);
    }

    TAcctSessionId& GetSessionId()
    {
        return m_tSessionId;
    }

    //�Ʒѽ��
    void SetResponseValue(u32 dwRspVal)
    {
        m_dwRspVal = htonl(dwRspVal);
    }

    u32 GetResponseValue()
    {
        return  ntohl(m_dwRspVal);
    }
    
}TConfAcctRsp;











#endif //___RADIUSINTERFACE_H






















