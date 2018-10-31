#ifndef _H323CONFNONSTDSTRUCT_H
#define _H323CONFNONSTDSTRUCT_H

//#include "cm.h"
#include <time.h>
#include <math.h>

#include "kdv323common.h"


//#define IPV6_NAME_LEN		(u16)64  //IPv6��ַ������
// #define INVALID_NODEID      RV_PVT_INVALID_NODEID
// #define TYPE_NONE           RV_ADDRESS_TYPE_NONE         //��ʾΪδ�����ַ
// #define TYPE_IPV4           RV_ADDRESS_TYPE_IPV4         //��ʾ֧��IPv4��ַ
// #define TYPE_IPV6           RV_ADDRESS_TYPE_IPV6         //��ʾ֧��IPv6��ַ
//#define TYPE_SCTP           RV_NET_SCTP         //��ʾͬ��֧��IPv4��IPv6��ַ

//#define LEN_MTNUM_PERCONF	(u16)192				//ÿ�������е���������



//�޸����kdvpts����һ��
//#define KDV_NSM_MAX_LEN        (s32)1300  //��ʱ1300�ֽ�
/*#define KDV_NSM_MAX_LEN        (s32)(1024*10)  */

// �Ǳ���Ϣ����Ŷ���
// typedef enum
// {
// 	KDVP_NSM_SUCCESS		= 0,  
// 	KDVP_NSM_SER_DB_ERR,
// 
// #ifdef _KDV_V50
// 	KDVP_NSM_TIMEOUT_ERR,				//2
// 	KDVP_NSM_NOTE164_ERR,				//3
// 	KDVP_NSM_DATA_ERR,                  //4
// 	KDVP_NSM_MCU_NOIDLEVPU,             //5  û���㹻�����Ŀ���ý�崦����
// 	KDVP_NSM_MCU_MINIMEDIACONFMTNUM,    //6  ����С��ý���������ն�����
// 	KDVP_NSM_MCU_MAXCONFNUM,            //7  �Ѵ���������
// 	KDVP_NSM_MCU_ENCRYPEERR,            //8  ��������ģʽ����
// 	KDVP_NSM_MCU_CONFNOTEXIST,          //9  ���鲻����
// 	KDVP_NSM_MCU_MAXMTNUM,              //10 �ﵽ���λ���Ա��
// 	KDVP_NSM_GK_MPCD_DISCONNECTED,      //11 MPCD��GK����
// 	KDVP_NSM_MCU_CONFRESUMING,          //12 MCU�����ָ���
// 	KDVP_NSM_MCU_PASSERR,               //13 �����������
// 	KDVP_NSM_MCU_NSATPMS,               //14 ������Ȩ��
// 	KDVP_NSM_MCU_NSATDADDR,             //15 û���鲥��ַ
// 	KDVP_NSM_MCU_CONFE164REPEAT,        //16 ����E164���ظ�
// 	KDVP_NSM_MCU_UNDEFINED,             //17
// #endif //_KDV_V50
// 
// };




//�Ǳ��������
enum NonstandardType 
{
    emNonstandardTypeInvalidType = 0,
    emNonstandardTypeRequest,
    emNonstandardTypeResponse,
    emNonstandardTypeCommand,
    emNonstandardTypeIndication
};

//�������:makeTerminalBroadcaster��sendThisSource�Ĳ�����ʽ
enum CtrlMode 
{
	mode_invalid = -1,
	mode_command,
	mode_request
};

typedef enum
{
	emChanUnkown = 0,
	emChanVideo1 = 1,
	emChanAudio	 = 2,
	emChanVideo2 = 3
}emChanID;

typedef enum
{
    emComUnkown  = 0,
    emComRS232   = 1,
    emComRS422   = 2,
    emComRS485   = 3,
    emComEnd
    
}emComType;


/*
�ù�����Ҫ�����ڻ�����A�ն˴Ӵ��ڶ��������� ͨ�����紫����Զ� 
��Ϣ����
  1.��������    //������ 1 -RS232��������  2 =RS422 3=RS485 
  2.���ݳ���
  3.����
*/
typedef struct tagCOMData
{
    emComType  m_emComType;
    s32 m_nDataLen;
    s8  m_achData[128];
    
public:
    tagCOMData()
    {
        Clear();
    }

    void Clear()
    {
        m_emComType = emComUnkown;
        memset(m_achData, 0, sizeof(m_achData));
        m_nDataLen = 0;
    }

    void host2net(BOOL32 bhton)
    {
        s32 nType = m_emComType;
        if (bhton)
        {
            m_emComType  = (emComType)htonl(nType);
            m_nDataLen   = htonl(m_nDataLen);
        }
        else
        {
            m_emComType  = (emComType)ntohl(nType);
            m_nDataLen   = ntohl(m_nDataLen);
        }
    }

    void SetComType(emComType emType)
    {
        m_emComType = emType;
    }

    emComType GetComType()
    {
        return m_emComType;
    }

    void SetComData(s8 *pData, s32 nLen)
    {
        if (NULL == pData || nLen < 0)
        {
            return;
        }

        m_nDataLen = Minimum(nLen, (s32)sizeof(m_achData));
        memset(m_achData, 0, sizeof(m_achData));
        memcpy(m_achData, pData, m_nDataLen);
        m_achData[m_nDataLen] = '\0';
    }

    s32 GetComDataLen()
    {
        return m_nDataLen;
    }

    s8* GetComData()
    {
        return m_achData;
    }

}TCOMDATA, *PTCOMDATA;

typedef struct tagChanMultiCast
{
	u8  m_byChanID;    //1��Ƶ��2��Ƶ��3�ڶ�·��Ƶ
	u32 m_dwIP;        //�鲥��ַ
	u16 m_wPort;       //�鲥�˿�
	//add by yj for ipv6
	u8          m_byIPType;                                 //֧�ֵ� IP��ַ����
	u8          m_dwIP_ipv6[IPV6_NAME_LEN];			         //�鲥��ַipv6����������;
	s16         m_swScopeId;                                //��ȡ������ IPv6 ��ַ��Χ��ʶ��
	//end

    tagChanMultiCast()
    {
        Clear();
    }

    void Clear()
    {
        m_byChanID = emChanUnkown;
        m_dwIP = 0;
        m_wPort = 0;
		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
	    memset(m_dwIP_ipv6, 0, sizeof(m_dwIP_ipv6));
		m_swScopeId = -1;
        //end
    }

    void host2net(BOOL32 bhton)
    {
        if (bhton)
        {
            m_dwIP  = htonl(m_dwIP);
            m_wPort = htons(m_wPort);
        }
        else
        {
            m_dwIP  = ntohl(m_dwIP);
            m_wPort = ntohs(m_wPort);
        }
    }

    void SetChanID(u8 byChan)
    {
        m_byChanID = byChan;
    }
	
    u8 GetChanID()
    {
        return m_byChanID;
    }

    //add by yj for ipv6
	//����ip��ַ����
	void SetChanAddr_Type (u8 byIPType)
	{
		m_byIPType = byIPType;
	}
	u8 GetChanAddr_Type( )
	{
		return	m_byIPType;
	}
	//����ScopeId(ipv6)ֵ
	s16 GetChanAddr_Ipv6_ScopeId( )
	{
		return	m_swScopeId;
	}
	void SetChanAddr_Ipv6_ScopeId(s16 swScopeId)
	{
		m_swScopeId = swScopeId;
	}
	//����Э��ջ����IP(ipv6)
	void SetChanAddr_Ipv6(u8 *dwIP_ipv6)
	{
		memcpy(m_dwIP_ipv6, dwIP_ipv6, sizeof(m_dwIP_ipv6));	
	}
	u8 *GetChanAddr_Ipv6()
	{
		return m_dwIP_ipv6;
	}
	

	//end

    void SetChanAddr(u32 ip, u16 port)
    {
        m_dwIP = ip;
        m_wPort = port;
    }

    u32 GetChanIp()
    {
        return m_dwIP;
    }

    u16 GeChantPort()
    {
        return m_wPort;
    }
    
}TCHANMULTICAST, *PTCHANMULTICAST;

/*
�������г�������ָʾ
*/
typedef struct tagCapInfo
{   
    s32  m_nVendor;                     //����ID
    BOOL32 m_bIsMCU;                      //FALSE:MT, TRUE:MCU
    BOOL32 m_bMix;                        //����
    BOOL32 m_bVAC;                        //��������
    BOOL32 m_bCustomVMP;                  //���ƻ���ϳ�
    BOOL32 m_bAutoVMP;                    //�Զ�����ϳ�
    BOOL32 m_bEndConf;                    //��������
    BOOL32 m_bInvateMt;                   //�����ն�
    BOOL32 m_bDropMt;                     //ɾ���ն�
    BOOL32 m_bSelSpeaker;                 //ָ��/ȡ��������
    BOOL32 m_bSelChair;                   //ָ��/������ϯ
    BOOL32 m_bSelSource;                  //ѡ���ն�
    BOOL32 m_bFECC;                       //Զ������ͷң��
    BOOL32 m_bQuiet;                      //Զ�˾���
    BOOL32 m_bMute;                       //Զ������
    BOOL32 m_bConfReq;                    //�������봦��
    BOOL32 m_bOnlineList;                 //�����ն��б�
    BOOL32 m_bOfflineList;                //�����ն��б�
    BOOL32 m_bSelSpeakingUser;            //����
    BOOL32 m_bPicSwitch;                  //���໭���л�
    BOOL32 m_bMustSeeSpeaker;             //ǿ�ƹ㲥
    //...                                
                            

    tagCapInfo()
    {
        Clear();
    }

    void Clear();

}TCAPINFO, *PTCAPINFO;


typedef struct tagMultiPic
{
	u8  m_byMcuNo;
	u8  m_byStyle;//emPicStyle
	TTERLABEL m_tTer[16];
	
	tagMultiPic()
	{
		Clear();
	}

	void Clear()
	{
		m_byMcuNo = 0;
		m_byStyle = 0;
		memset(m_tTer, 0, sizeof(m_tTer));//HuaweiĬ�϶�Ϊ0
	}
	
}TMultiPic, *PTMultiPic;












///////////////////ȫ������ ////////////////////////

#ifndef H323CASCADE_H_

#define CASCADE_PORT		    (s32)3337
/*#define CASCADE_USERNAME_MAXLEN     (s32)32*/
/*#define CASCADE_USERPASS_MAXLEN     (s32)32 */
#define CASCADE_NONSTANDARDMSG_MAXLEN (u32)1536
#define PART_NUM			     (s32)192//
#define STR_LEN                  (s32)16
#define CONFID_BYTELEN                   (s32)12// 
#define PID_POS                          (s32)4//
//#define MAX_VIEWS_PER_CONF               (s32)2
#define MAX_VIEWS_PER_CONF               (s32)4
#define MAX_GEOMETRYS_PER_VIEW           (s32)5
#define MAX_SUBFRAMES_PER_GEOMETRY       (s32)16
#define MAX_VIDEOSCHEMES_PER_VIEW        (s32)4
#define MAX_MIXERS_PER_CONF              (s32)16

#define MCU_PID                          (u32)0XFFFFFFFF
#define CACSCONF_ID                      (u32)0XFFFFFFFF
#define EMPTY_MT_PID                     (u32)0x0


#define E_TOO_MANY_ITEMS                 (s32)-1
#define E_ALREADY_EXISTED                (s32)-2
#define E_INVALID_PARAMETER              (s32)-3
#define E_NOT_EXISTED                    (s32)-4
#define E_SUBFRAMES_CONTRIBUTERS_UNMATCH (s32)-5
//#define S_RIGHT                             (s32)1
#define S_REPLACED                       (s32)2
#define S_RIGHT                          (s32)1

enum emConnState
{
	    emConnStateUnknown,                 //��MT,MCU������״̬δ֪����������δ
		emConnStateConnected,               //"connected"
		emConnStateDisconnected,            //"disconnected"
		emConnStateConnecting               //"alerting"
};

enum emEPType
{
    	emEPTypeUndefined,                  //��������
		emEPTypeMCU,                        //mcu,��������һ����ͨ�ն˵���ݲμӼ���������ǻ���
		emEPTypeTerminal,                   //��ͨ�ն�
		emEPTypeCascConf,                    //mcu,���Ҳμ��˼�������
		emEPTypeTerPhone                    //�绰�ն� [2012/05/03]		
};


//time config struct
typedef struct tagTimeSpec
{
    s8 day;
    s8 hour;
    s8 minute;
    s8 second;
    s16 year;
    s8 month;
}TTimeSpec,*PTTimeSpec;

//��׼����ͷ,������������Ļ���
// typedef struct tagRequest
// {
//     s32  m_nReqID;//��ˮ��/ϵ�к�
// 	s8   m_aszUserName[CASCADE_USERNAME_MAXLEN];//�ʺ�
// 	s8   m_aszUserPass[CASCADE_USERPASS_MAXLEN];//����
// 	//�����ʺź�����
// 	inline void SetUserNameAndPass(const s8 * aszUserName, const s8 *aszUserPass)
// 	{
// 		strncpy(m_aszUserName, aszUserName, CASCADE_USERNAME_MAXLEN-1);
// 		m_aszUserName[CASCADE_USERNAME_MAXLEN-1] = '\0';
// 		strncpy(m_aszUserPass, aszUserPass, CASCADE_USERPASS_MAXLEN-1);
// 		m_aszUserPass[CASCADE_USERPASS_MAXLEN-1] = '\0';
// 	}
// }TReq;


//�Ǳ꼶����Ϣ�Ļ���
typedef struct tagNonStandardMsg
{
	s32 m_nMsgLen;//��Ϣ����
	u8	m_abyMsgBuf[CASCADE_NONSTANDARDMSG_MAXLEN];//��Ϣ��
}TNonStandardMsg;

//�Ǳ�(�Զ���)������Ϣ
typedef struct tagNonStandardReq: public TReq, public TNonStandardMsg{}TNonStandardReq;

//response��Ϣ�ķ���ֵ�ֶ�
enum emReturnValue
{
    emReturnValue_Ok				= 0,	//request��Ϣ�ѵõ���ȷ�Ĵ���
    emReturnValue_Error				= 1,	//һ���Դ��󣬴���ԭ����
    emReturnValue_PartNotFound		= 2,	//�������в�����������Ϣ��PIDָʾ�Ļ����Ա
    emReturnValue_ConfNotFound		= 3,	//������Ϣ��confIDָ���Ļ����鲻����
    emReturnValue_ChannelNotFound	= 4,	//�����Ա����Ƶ/��Ƶͨ��������
    emReturnValue_NoPermission		= 5,	//�û���Ȩ�޲�����������Ϣ��������
    emReturnValue_XmlBadParams		= 6,	//������Ϣ���ֶ��������ֶε�ֵ����/��Χ����
    emReturnValue_TimeOut			= 7,	//������Ϣ����ʱ
    emReturnValue_NoResources		= 8,	//mcuû���㹻����Դ������������Ϣ������Ƶ��Դ��Ҫ��
    emReturnValue_Invalid			= 9		//������Ч,���ᱻ����
};
typedef struct tagResponse           //Request��Ϣ�Ļ�Ӧ��Ϣ(response��Ϣ)
{                           
    s32    m_nReqID;//��ˮ��/ϵ�к�,��ƥ��request�е���ˮ��/ϵ�к�
    emReturnValue m_emReturnVal;//request������ָʾ��
    tagResponse()
    {
        m_emReturnVal = emReturnValue_Ok;
        m_nReqID =((s32)time(NULL))%((s32)0x7fffffff);
    }
}TRsp;

//�Ǳ�(�Զ���)response��Ϣ
typedef struct tagNonStandardRsp: public TRsp, public TNonStandardMsg{}TNonStandardRsp;


//֪ͨ������Ϣ(notification)�Ļ���
typedef struct tagNotification
{
    s32    m_nCookie;//cookieֵ
}TNtf;

//��ȡMCU�ϵķ����б��������Ϣ,����Զ�mcu�����mcu�������Ѿ�����ķ���ģ�����Ϣ
#define TMCUServiceListReq TReq

//��ȡMCU�ϵ�ǰ�ٿ������л��������Ϣ���б�
typedef struct tagMCUConfListReq: public TReq
{
	s32 m_nSnapShot;//MCU����ֵ
}TMCUConfListReq;

//ͨ���������ֻ�û���ID��������Ϣ
typedef struct tagGetConfIDByNameReq:public TReq
{
	s8 m_aszConfName[STR_LEN];//��������
	s8 m_aszConfPass[STR_LEN];//��������,mcu�����ߵ�����Ҳͬ����Ч
}TGetConfIDByNameReq;

//������л��鼶����ע��ע������
// typedef struct tagRegUnReg: public TReq     //��Զ�mcuע��ע����������Ϣ
// {
//     BOOL32 m_bReg;               //true:ע��;false ע��
// }TRegUnRegReq;

//������л��鼶����ע��/ע���Ļ�Ӧ��Ϣ(�ɹ� m_emReturnValΪtrue������)
typedef struct tagRegUnRegRsp :public TRsp 
{
	BOOL32 m_bReg;  //true:ע��;false ע��            
}TRegUnRegRsp;


typedef struct tagPartID           //����μ��ߵ�ID,Ψһ�ı�ʾ����MCU������һ��������
                                  //����m_dwPID��0xffffffff��ʾ�����ӻ���;
{
    u32         m_dwPID;          // part id
    BOOL32      m_bLocal;         // true:����μ���ֱ���뱾��MCU���� 
                                 // false:����μ���ֱ����Զ�MCU����
    tagPartID ()
    {
        m_dwPID = 0;
        m_bLocal =FALSE;
    }
    inline BOOL32 IsSamePart(tagPartID tPeerPart)
    {
        if(m_dwPID == tPeerPart.m_dwPID && m_bLocal == tPeerPart.m_bLocal)
        {
            return TRUE;
        }
        return FALSE;
    }
    inline BOOL32 IsSamePart(u32 dwPID, BOOL32 bLocal)
    {
        if(m_dwPID == dwPID && m_bLocal == bLocal)
        {
            return TRUE;
        }
        return FALSE;
    }
    inline u32    GetPid() { return m_dwPID ;}
    inline void   SetPid(u32 dwPID) { m_dwPID = dwPID;}
    inline BOOL32 IsLocalPart(){ return m_bLocal;}
    inline BOOL32 IsRemotePart(){ return !m_bLocal;}
    inline BOOL32 IsEmptyPart(){ return m_dwPID == EMPTY_MT_PID;}
    inline void   SetEmpty(){ m_dwPID = EMPTY_MT_PID; m_bLocal = FALSE; }
    inline void   SetIsLocalPart(BOOL32 bLocal = TRUE) { m_bLocal = bLocal; }
    //
    inline BOOL32 IsLocalKdvMCU(){  return (m_dwPID  == CACSCONF_ID && m_bLocal);}
    inline BOOL32 IsRemoteRadMcu(){ return (m_dwPID == CACSCONF_ID && !m_bLocal);}

    inline void SetPartGid(u32 dwPid, BOOL32 bLocal)
    {
        m_dwPID  = dwPid;
        m_bLocal = bLocal;
    }
    
    inline void GetPartGid(u32 *pdwPid, BOOL32 *pbLocal)
    {
        if(pdwPid)
        {
            *pdwPid = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        return;
    }
}TPartID;

//��ȡMCU�ϵ�ǰ�ٿ������л����profile
//������ʱδ����������Ӧ��Ϣ�Ľṹ
typedef struct tagConfProfileReq:public TReq
{
    s32 m_nSnapShot;//
}TConfProfileReq;

//
typedef struct tagPartReq: public TPartID, public TReq{}TPartReq;

//�·�����(Floor)֪ͨ
typedef struct tagNewSpeakerNtf:public TPartID,public TNtf
{
    s32 m_nMixerID;  //Mixer ID
    tagNewSpeakerNtf(){memset(this, 0, sizeof(*this)); }
}TNewSpeakerNtf,*PTNewSpeakerNtf;

//
typedef enum 
{
        emMediaTypeNone,    //unknown,invalid
        emMediaTypeVideo,   //video
        emMediaTypeAudio,   //audio
        emMediaTypeData     //data
}emMediaType;               //ý������

typedef enum 
{
    emDirectionNone,       //unknown,invalid
    emDirectionIn,        //���ն˵�MCU
    emDirectionOut       //��MCU���ն�
}emMuteDirection;          //ĳһ��ý����������

typedef struct tagPartMediaChan:public TPartID
{
    emMediaType      m_emMediaType;        //ý������
    emMuteDirection  m_emMuteDirection;    //ý������������
    BOOL32           m_bMute;              //true:�жϸ÷����������false:�򿪸÷����ý������
    tagPartMediaChan(){memset(this, 0, sizeof(*this)); }
}TPartMediaChan; 

//�����Ա��/��/����ͨ����/�ر�֪ͨ
typedef struct tagPartMediaChanNtf:public TPartMediaChan,public TNtf{}TPartMediaChanNtf;

//�����Ա��/��/����ͨ����/�ر�����
typedef struct tagPartMediaChanReq:public TPartMediaChan,public TReq{}TPartMediaChanReq;

// һ����MCU���ն˵���Ƶ����淶�Ķ���
typedef struct tagViewOutInfo:public TPartID 
{    
    s32 m_nOutViewID;         //LayoutID,����Ļ�����ͼID
    s32 m_nOutVideoSchemeID;  //VideoSchemeID,��Ƶ�������ID
}TViewOutInfo,*PTViewOutInfo;

//����MCU�����Ƶ���������Ա
typedef struct tagSetOutReq :public TReq
{
    s32              m_dwPartCount;           //����MCU�����Ƶ���Լ����ն���Ŀ
    TViewOutInfo     m_tPartOutInfo[PART_NUM];//��Ƶ����淶���б�ÿһ���б�Ԫ�ض�����һ���ն˵���Ƶ�������

private:
    
     BOOL32 FindPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 &nPartIndex);

public: 
    tagSetOutReq(){memset(this, 0, sizeof(*this)); }

    inline s32 GetPartCount(){ return m_dwPartCount;}

    s32 AddNewPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 nOutViewID, s32 m_nOutVideoSchemeID);
 
    ////////////////
    s32 DelPartViewOutItem(u32 dwPartId, BOOL32 bLocal);
    
    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 &nViewId, s32 &nVideoSchemeId);

    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut);

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 nViewId, s32 nVideoSchemeId);

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut);

    inline TViewOutInfo * GetItemByIndex(s32 nIndex)
    { return (nIndex >= 0 && nIndex < m_dwPartCount) ? &(m_tPartOutInfo[nIndex]) : NULL; }

}TSetOutReq,*PTSetOutReq;

//MCU�����Ƶ���������Ա��֪ͨ
typedef struct tagPartOutputNtf:public TPartID,public TNtf
{
    s32 m_nViewID; //�ն�������Ļ�����ͼID
    inline tagPartOutputNtf()
    {
        m_nViewID = m_dwPID = 0;
        m_bLocal = FALSE;
    }
}TPartOutputNtf, *PTPartOutPutNtf;


// ���黨�����һ��,��ʾһ������Ա�Ļ�����Ϣ
typedef struct tagTRosterItem:public TPartID
{
    emConnState  m_emConnState;    //����״̬
}TRosterItem, *PTRosterItem;

// ���黨����֪ͨ
typedef struct tagRosterList:public TNtf
{
    s32          m_nCount;               //�������¼����Ŀ
    TRosterItem  m_atRoster[PART_NUM];   //��¼���б�
private: 
    BOOL32 FindRosterItem(u32 dwPartId, BOOL32 bLocal, s32 &nIndex);

public:

    inline tagRosterList(){ memset(this, 0, sizeof(*this));}

    BOOL32 AddRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState);
    
    BOOL32 DelRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState);
    
    inline TRosterItem * GetItemByIndex(s32 nIndex)
    { return (nIndex >= 0 && nIndex < m_nCount) ? &(m_atRoster[nIndex]) : NULL; }

}TRosterList, *PTRosterList;

//������ͼ�Ӵ��ڵ�λ�ñ�־
typedef struct 
{
    s32  m_nViewID;//������ͼID
    u8   m_bySubframeIndex;//�Ӵ����ڻ�����ͼ��λ��(���մ����Ҵ��ϵ��µ�˳���0��ʼ����)
}TViewPos;

//(voice activate)������������,�ѵ�ǰ˵����/�����������Ļ����Ա����Ƶ��������ͼ���Ǹ��Ӵ�����
typedef struct tagVAReq:public TReq, public TViewPos{}TVAReq;

//�����Ա����Ƶ���������Ϣ
typedef struct tagPartVideoInfo
{
    s32       m_nViewCount;                    //�ն�(�����Ա)����Ƶ�ܹ����������ͼ��Ŀ
    TViewPos  m_anViewPos[MAX_VIEWS_PER_CONF]; //�ն�����Щ��ͼ��
    s32       m_nOutputViewID;                 //�ն˽����ĸ���ͼ
    s32       m_nOutVideoSchemeID;             //���뵽�ն˵���Ƶ����ID(��һ������֧�����ֻ����ʽ)                        
    
private:
    BOOL32 FindViewPos(s32 nViewID, u8 bySubframeIndex, s32 &nIndex);

public:
    tagPartVideoInfo()
    {
        memset(this,0,sizeof(*this));
    }
    BOOL32 AddViewPos(s32 nViewID,u8 bySubframeIndex);
   
    BOOL32 DelViewPos(s32 nViewID,u8 bySubframeIndex);

    BOOL32 IsViewPosExist(s32 nViewID, u8 bySubframeIndex);

    inline void SetVideoSpec(s32 nNewLID, s32 nNewSchemeID, s32 *nOldLID = NULL, s32 *nOldSchemeID = NULL)
    {
        if(nOldLID)
        {
            *nOldLID = m_nOutputViewID;
        }
        if(nOldSchemeID)
        {
            *nOldSchemeID = m_nOutVideoSchemeID;
        }
        m_nOutputViewID        = nNewLID;
        m_nOutVideoSchemeID = nNewSchemeID;
        return;
    }

    inline void GetVideoSpec(s32 *pnLID, s32 *pnSchemeID)
    {
        if(pnLID)
        {
            *pnLID = m_nOutputViewID;
        }
        if(pnSchemeID)
        {
            *pnSchemeID = m_nOutVideoSchemeID;
        }
    }

}TPartVideoInfo,*PTPartVideoInfo;


/*
 *����ߵ���Ƶ����Ƶ���������ͳ����Ϣ����������������/���ܵİ���Ŀ���������Ŀ��
 ����(jitter)�����,Ŀǰû�о��嶨��
*/
typedef struct tagPartAVStatis
{
  u32 m_dwTotalInBandWidth;
  u32 m_dwTotalOutBandWidth;
  u32 m_dwUnused_AudioIn;
  u32 m_dwUnused_AudioOut;
  u32 m_dwUnused_VideoIn;
  u32 m_dwUnused_VideoOut;
  // Currently We Define the bandwith with fixed value
  // because we did not decide to get extra info about part
  // Once we change to get the extra info, we should rewrite this code here.
  tagPartAVStatis()
  {
      m_dwTotalInBandWidth = 437720;
      m_dwTotalOutBandWidth = 437720; 
      m_dwUnused_AudioIn  = 0;
      m_dwUnused_AudioOut = 0;
      m_dwUnused_VideoIn  = 0;
      m_dwUnused_VideoOut = 0;
      
  }
}TPartAVStatis;

// 
// /*
//  *����ߵ���Ϣ
// */
typedef struct tagPart:public TPartID
{
    s8			m_aszPartName[STR_LEN];     //part name
    s8			m_aszDialStr[STR_LEN];      //dial string
    u32			m_dwIP;            //part ip
    emEPType	m_emEPType;        //part type
    s8          m_aszEPDesc[STR_LEN];       //part des(product id)
    PayloadType m_emVideoIn;       //video in format (H263��G711.....None)
    PayloadType m_emVideoOut;      //.....
    PayloadType m_emVideo2In;      //.....
    PayloadType m_emVideo2Out;     //..... 
    PayloadType m_emAudioIn;       //.....
    PayloadType m_emAudioOut;      //..... 
    BOOL32      m_bDataMeeting;    //data meeting  
    BOOL32      m_bVideoMuteIn;    //whether or not video in mute(no camera)
    BOOL32      m_bVideoMuteOut;   //....(no dispaly)
    BOOL32      m_bAudioMuteIn;    //....(no mic)
	BOOL32      m_bAudioMuteOut;   //....(no audio player)
    BOOL32      m_bInvited;        //whether or not is Invited
    BOOL32      m_bMaster;         //whether or not Master ternial
    TTimeSpec   m_tStartTime;      //call start time
    emConnState m_emConnState;     //connect state
    BOOL32      m_bFECCEnable;     //whether or not enable FECC
    TPartVideoInfo m_tPartVideoInfo;   //��Ƶ���������Ϣ
    TPartAVStatis  m_tAVStatis;    //��Ƶ��Ƶ�������ͳ����Ϣ

    tagPart()
    {
        memset(this, 0, sizeof(*this));
    }
    inline void SetVideoAttr(PayloadType emVideoIn, PayloadType emVideoOut, 
                                PayloadType emVideo2In, PayloadType emVideo2Out, 
                                BOOL32 bVideoMuteIn, BOOL32 bVideoMuteOut)
    {
         m_emVideoIn      = emVideoIn;      
         m_emVideoOut     = emVideoOut; 
         m_emVideo2In      = emVideo2In;      
         m_emVideo2Out     = emVideo2Out; 
         m_bVideoMuteIn   = bVideoMuteIn;    
         m_bVideoMuteOut  = bVideoMuteOut;   
    }

    inline void GetVideoAttr(PayloadType *pemVideoIn, PayloadType *pemVideoOut, 
                                PayloadType *pemVideo2In, PayloadType *pemVideo2Out,
                                BOOL32 *pbVideoMuteIn, BOOL32 *pbVideoMuteOut)
    {
        if(pemVideoIn)
        { 
            *pemVideoIn = m_emVideoIn;
        }
        if(pemVideoOut)
        { 
            *pemVideoOut = m_emVideoOut; 
        }
        if(pemVideo2In)
        { 
            *pemVideo2In = m_emVideo2In;
        }
        if(pemVideo2Out)
        { 
            *pemVideo2Out = m_emVideo2Out; 
        }
        if(pbVideoMuteIn)
        { 
            *pbVideoMuteIn = m_bVideoMuteIn;
        }
        if(pbVideoMuteOut)
        { 
            *pbVideoMuteOut = m_bVideoMuteOut;
        }
        return;
    }
    
    inline void SetViewInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo,sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo* GetViewInAndOutAttr()
    {
        return &m_tPartVideoInfo;
    }
    
    inline void SetAudioAttr(PayloadType emAudioIn, PayloadType emAudioOut, BOOL32 bAudioMuteIn, BOOL32 bAudioMuteOut)
    {
        m_emAudioIn      = emAudioIn;      
        m_emAudioOut     = emAudioOut;     
        m_bAudioMuteIn   = bAudioMuteIn;    
        m_bAudioMuteOut  = bAudioMuteOut;   
    }

    inline void GetAudioAttr(PayloadType *pemAudioIn, PayloadType *pemAudioOut, BOOL32 *pbAudioMuteIn, BOOL32 *pbAudioMuteOut)
    {
        if(pemAudioIn)
        { 
            *pemAudioIn = m_emAudioIn;
        }
        if(pemAudioOut)
        { 
            *pemAudioOut = m_emAudioOut; 
        }
        if(pbAudioMuteIn)
        { 
            *pbAudioMuteIn = m_bAudioMuteIn;
        }
        if(pbAudioMuteOut)
        { 
            *pbAudioMuteOut = m_bAudioMuteOut;
        }
        return;
    }

    inline void SetNameAttr(const s8 *pszName, s32 nNameLen, const s8 *pszDescr, s32 nDescrLen)
    {
        // assert(pszName != NULL);
        s32 nStrLen = (nNameLen >= sizeof(m_aszPartName) ? sizeof(m_aszPartName) - 1 : nNameLen );
        strncpy(m_aszPartName, pszName, nStrLen);
        m_aszPartName[nStrLen] = '\0';

        if(pszDescr != NULL && nDescrLen > 0)
        {
            nStrLen = (nDescrLen >= sizeof(m_aszDialStr) ? sizeof(m_aszDialStr) -1 : nDescrLen );
            strncpy(m_aszDialStr, pszDescr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';
        }
        else
        {
            m_aszDialStr[0] = '\0';
        }
    }

    inline void GetNameAttr(s8 *pszName, s32 nNameLen, s8 *pszDescr, s32 nDescrLen)
    {
        if(pszName != NULL && nNameLen > 0)
        {
            s32 nStrLen = (nNameLen >= STR_LEN ? STR_LEN -1 : nNameLen );
            strncpy(pszName, m_aszPartName, nStrLen);
            pszName[nStrLen] = '\0';  
        }

        if(pszDescr != NULL && nDescrLen > 0)
        {
            s32 nStrLen = (nDescrLen >= STR_LEN ? STR_LEN -1 : nDescrLen);
            strncpy(pszDescr, m_aszDialStr, nStrLen);     
            pszDescr[nStrLen] = '\0';
        }
    }

    inline void SetDialStr(const s8 *pszDialStr, s32 nLen)
    {
       if(pszDialStr !=NULL && nLen >0)
       {
           s32 nStrLen = (nLen >= STR_LEN ? STR_LEN -1 : nLen);
           strncpy(m_aszDialStr, pszDialStr, nStrLen);
           m_aszDialStr[nStrLen] = '\0';
       }
    }

    inline s8 * GetDialStr() { return this->m_aszDialStr; }

    inline void SetEntityAttr(emConnState emState, emEPType emEntityType, BOOL32 bFECCEnable, BOOL32 bMaster, BOOL32 bInvited)
    {
        m_emConnState    = emState;  
        m_emEPType       = emEntityType;
        m_bFECCEnable    = bFECCEnable;     
        m_bMaster        = bMaster;       
        m_bInvited       = bInvited;       
    }
    inline BOOL32 IsFECCEnable(){ return m_bFECCEnable;}
    inline BOOL32 IsMaster() { return m_bMaster;}
    inline BOOL32 IsInvited() { return m_bInvited;}
    inline emConnState GetConnState() { return m_emConnState;}
    inline void   SetConnState(emConnState emState) { m_emConnState = emState;}
    inline void   StopAsVideoSrc() { m_tPartVideoInfo.m_nViewCount = 0;}
    inline BOOL32 IsVideoSrc() { return (m_tPartVideoInfo.m_nViewCount > 0);}
    inline u32    GetTotalBandWith() { return m_tAVStatis.m_dwTotalInBandWidth + m_tAVStatis.m_dwTotalOutBandWidth;}

    inline void GetEntityAttr(emConnState *pemState, BOOL32 *pbFECCEnable, BOOL32 *pbMaster, BOOL32 *pbInvited)
    {
        if(pemState)
        { 
            *pemState = m_emConnState;
        }
        if(pbFECCEnable)
        { 
            *pbFECCEnable = m_bFECCEnable; 
        }
        if(pbMaster)
        { 
            *pbMaster = m_bMaster;
        }
        if(pbInvited)
        { 
            *pbInvited = m_bInvited;
        }
        return;
    }
    inline void GetVideoScheme(s32 *pnViewId, s32 *pnVideoSchemeId)
    {
        m_tPartVideoInfo.GetVideoSpec(pnViewId,pnVideoSchemeId);
    }
    inline void SetVideoScheme(s32 nViewId, s32 nVideoSchemeId)
    {
        m_tPartVideoInfo.SetVideoSpec(nViewId, nVideoSchemeId, NULL, NULL);
    }
}TPart,*PTPart;

// ������������ߵ���Ϣ
typedef struct tagConfPartInfo
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //����Ŀ���ֵ
        //The first Element Denotes MCU, The Record series from second Denote Terminals 
    TPart  m_atParts[PART_NUM]; // part list 
 private:
     BOOL32 FindPart(u32 dwPartId, BOOL32 bLocal, s32 &nIndex)
	 {
		 for(nIndex =0; nIndex < m_dwPartCount; nIndex++)
		 {
			 if(m_atParts[nIndex].IsEmptyPart())
			 {
				 return FALSE;
			 }
			 if(m_atParts[nIndex].IsSamePart(dwPartId, bLocal))
			 {
				 return TRUE;
			 }
		 }
		 return FALSE;
	}
		 
 public:
     void Clear()
     {
         memset(this, 0, sizeof(*this));
     }
     tagConfPartInfo()
     {
         memset(this, 0, sizeof(*this));
     }
     s32 AddPart(TPart &tPart, BOOL32 bReplace = TRUE)
	 {
		 s32  nPartIndex = 0;
		 if(FindPart(tPart.m_dwPID, tPart.m_bLocal, nPartIndex))
		 {
			 if(bReplace)
			 {
				 memcpy(&m_atParts[nPartIndex], &tPart, sizeof(TPart));
				 return S_RIGHT;
			 }
			 else
			 {
				 return E_ALREADY_EXISTED;
			 }
		 }
		 if( nPartIndex >= PART_NUM)
		 {
			 return E_TOO_MANY_ITEMS;
		 }
		 
		 memcpy(&m_atParts[nPartIndex], &tPart, sizeof(TPart));
		 m_dwPartCount ++;
		 return S_RIGHT;
}

    s32 DelPart(u32 dwPartId, BOOL32 bLocal);
    
     s32 Disconnect(u32 dwPartId, BOOL32 bLocal, u32 dwNewPartId);
    
     TPart *GetPart(u32 dwPartId, BOOL32 bLocal);

     inline TPart *GetLocalMCU()
     {
         return GetPart(CACSCONF_ID, TRUE);
     }

     inline TPart *GetPeerMCU()
     {
         return GetPart(CACSCONF_ID, FALSE);
     }

     BOOL32 IsPartExist(u32 dwPartId, BOOL32 bLocal);
     
     inline TPart *GetItemByIndex(s32 nPosFrom)
     {
         return (nPosFrom >= 0 && m_dwPartCount > nPosFrom ? &m_atParts[nPosFrom] : NULL);
     }
     
}TConfPartInfo;

// �Է�MCU�����ӻ���Ļ�Ӧ�б�
typedef struct tagPartListRsp :public TConfPartInfo,public TRsp
{
   BOOL32 m_bLastPack;			//whether or not last pack��used only while receiving
   public:
    tagPartListRsp() { m_emReturnVal = emReturnValue_Ok; m_bLastPack = TRUE;}
    void Clear()
    { 
        memset(this, 0, sizeof(*this));
        m_emReturnVal = emReturnValue_Ok; 
        m_bLastPack = TRUE;
    }
    void BuildToPartListRsp(TConfPartInfo &tConfPart);
    
    BOOL32 ExtractConfPartList(TConfPartInfo &tConfPart);
  
}TPartListRsp,*PTPartListRsp;

//PartList��Ϣ�շ�ͷ�ṹ�������m_dwPartCount��TPart�ṹ
typedef struct tagPartListMsg: public TRsp
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //����Ŀ���ֵ
    BOOL32 m_bLastPack;         //whether or not last pack��used only while receiving
} TPartListMsg,*PTPartListMsg;


// �����ն˼������Ĳ���
typedef struct tagInvitePart
{
    s8   m_aszDialStr[STR_LEN];   //dial string ("123"��"100.1.1.1"��"h323id")
    u32  m_dwCallRate;                //call rate (kbps)
    
    //optional,advanced invitation parameter
    TPartVideoInfo m_tPartVideoInfo;
    
    tagInvitePart()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void SetBasicInviteeParam(const s8 *pszDialStr, s32 nStrLen, u32 dwCallRate);

    void GetBasicInviteeParam(s8 *pszDialStr, s32 nStrLen, u32 *pdwCallRate);

    inline void SetInviteeSetInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo, sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo GetInviteeSetInAndOutAttr()
    {
       return m_tPartVideoInfo;
    }
  
}TInvitePart,*PTInvitePart;


// /*
//   ���������뼶���������Ϣ��  
// */
typedef struct tagInvitePartReq: public TReq
{
	s32          m_nCount;           //ͬʱ��Ҫ��Ķ������Ŀ
    TInvitePart  m_atPart[PART_NUM]; //�����������Ϣ
public:
     tagInvitePartReq()
     {
        memset(this, 0, sizeof(*this));
     }

     inline BOOL32 AddInvitee(TInvitePart &tInvitee)
     {
         if(m_nCount >= PART_NUM)
         {
             return FALSE;
         }
         memcpy(&m_atPart[m_nCount], &tInvitee,sizeof(TInvitePart));
         m_nCount++;
         return TRUE;
     }

     inline TInvitePart *GetItemByIndex(s32 nPos)
     { return (nPos >= 0 && nPos < m_nCount) ? &(m_atPart[nPos]) : NULL; }

}TInvitePartReq;

//����Ҫ���Ѿ��Ͽ����ն˼������
typedef struct tagReinvitePartReq: public TPartID, public TReq{}TReInvitePartReq;

//MCU_MCU_CALL_ALERTING_NTF ��Ϣ��
typedef struct tagCallNtf : public TPartID, public TNtf
{
	s8   m_aszDialStr[STR_LEN];   //dial string ("123"��"100.1.1.1"��"h323id")
   
    tagCallNtf()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void inline GetPartCallingParam(s32 *pdwPartId, BOOL32 *pbLocal,s8 *pszDialStr, s32 nStrLen)
    {
        if(pdwPartId)
        {
            *pdwPartId = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(pszDialStr, m_aszDialStr, nStrLen);
            pszDialStr[nStrLen] = '\0';
        }
    }

    void inline SetPartCallingParam(u32 dwPartId, BOOL32 bLocal,s8 *pszDialStr, s32 nStrLen)
    {
        m_dwPID  = dwPartId;
        m_bLocal = bLocal;
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(m_aszDialStr, pszDialStr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';
        }
    }
}TCallNtf;

//�����ն����ͼ�񵽻����ĳ����ͼ
typedef struct tagSetInReq:public TPartID, public TReq
{
    s32 m_nViewID;          //ͼ���������Ļ�����ͼ
    u8  m_bySubFrameIndex;  //������ͼ�е���ͼ��(subframe)����
    tagSetInReq()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void SetPartSetInParam(u32 dwPartId, BOOL32 bLocal, s32 nViewID, u8 bySubFrameIndex);

    void GetPartSetInParam(s32 *pdwPartId, BOOL32 *pbLocal, s32 *pnViewID, u8 *pbySubFrameIndex);
    
}TSetInReq;

/*
 *����ߴӼ��������жϿ���ͨ�棬
*/
typedef struct tagDiscPartNF : public TPartID, public TNtf
{
    u32 m_dwNewPID;   //new part id
    tagDiscPartNF()
    {
        m_dwNewPID = 0;
    }
}TDiscPartNF,*PTDiscPartNF;

//��������Ϣ�����ܻ��ж��speaker������ֻ���ƶ�һ��
typedef struct tagAudioMixerInfo
{
    s32    m_nMixerID;             //mixer ID
    u32    m_dwSpeakerPID;         //speaker Pid
    BOOL32 m_bLocal;               //romote or local?
    tagAudioMixerInfo()
    {
        m_nMixerID = m_dwSpeakerPID = 0;
        m_bLocal = FALSE;
    }
    inline BOOL32 IsSpeakerExist(u32 dwPartId, BOOL32 bLocal)
    {
        return (m_dwSpeakerPID == dwPartId && m_bLocal == bLocal);
    }
}TAudioMixerInfo, *PTAudioMixerInfo;

//MCU�Ļ���������Ϣ
typedef struct tagConfAudioInfo:public TRsp
{
    u8 m_byMixerCount;                                 //��������Ŀ
    u8 m_byDefaultMixerIndex;                          //ȱʡ����������������ʾ,��Ҳ�ǵ�ǰ���ڲ����Ļ�����
    s32 m_nSnapShot;                                    //�������ֵ
    TAudioMixerInfo m_tMixerList[MAX_MIXERS_PER_CONF]; //�������б�

 private:
     BOOL32 FindSpeaker(u32 dwPartId, BOOL32 bLocal, s32 &nMixerIndex);

 public:
     tagConfAudioInfo()
     {
         memset(this, 0, sizeof(*this));
         m_emReturnVal = emReturnValue_Ok;
         m_nSnapShot = 0;
     }

     void Clear(void)
     {
         memset(this, 0, sizeof(*this));
         m_emReturnVal = emReturnValue_Ok;
         m_nSnapShot = 0;
     }
     
     BOOL32 AddNewSpeaker(u32 dwPartId, BOOL32 bLocal, s32 nMixerId);
     
     BOOL32 DelSpeaker(u32 dwPartId, BOOL32 bLocal);
     
     inline void GetCurrentSpeaker(u32 &dwPartId, BOOL32 &bLocal)
     {
         dwPartId = m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID;
         bLocal   = m_tMixerList[m_byDefaultMixerIndex].m_bLocal;
     }

     s32 SetCurrentSpeaker(u32 dwPartId, BOOL32 bLocal);

     inline BOOL32 IsCurrentSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         return (m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID == dwPartId
                && m_tMixerList[m_byDefaultMixerIndex].m_bLocal == bLocal);
     }
}TConfAudioInfo;



//������ͼ���β��ֱ��֪ͨ
typedef struct tagConfViewChgNtf: public TNtf
{
    s32                   m_nViewID;                                 //�������β��ֱ仯�Ļ�����ͼID
    u8                    m_dwSubFrameCount;                           //�仯��ļ��β��ֻ��ֳɵ���ͼ����Ŀ(subframe)
}TConfViewChgNtf;

//MCU����Ƶ�������
typedef struct tagOutPutVideoSchemeInfo
{
    s32           m_nOutputVideoSchemeID;   //��Ƶ�������ID
    u32           m_dwMaxRate;              //max rate (kbps)
    u32           m_dwMinRate;              //min rate (kbps)
    BOOL32        m_bCanUpdateRate;         // whether or not enable update rate
    s32           m_nFrameRate;             // frame rate (30��25)
    PayloadType   m_emPayLoad;              // payload    (h261,h263,etc)
    tagOutPutVideoSchemeInfo()
    {
        memset(this, 0, sizeof(*this));
    }
}TOutPutVideoSchemeInfo,*PTOutPutVideoSchemeInfo;


//һ��������ͼ�Ķ��壬������һϵ�еļ��β��֣�һϵ�е���ͼ��ƵԴ(��pid����־)���б�
//�Լ���ѡ������û�����ͼ�ļ�����Ƶ�������(rad mcu ������ĸ�).
typedef struct tagViewInfo
{
    s32                m_nViewId;                                           //������ͼ ID
    emResolution       m_emRes;                                             //������ͼͼ��ķֱ���
    u8                 m_byCurrentGeometryIndex;                            //������ͼ��ǰ����ʹ��(���)�ļ��β���,���ڼ��β����б��е�����������
    u8                 m_byGeometryCount;                                   //���β��ֵ���Ŀ
    u8                 m_abyGeometryInfo[MAX_GEOMETRYS_PER_VIEW];            //���β����б�
    u8                 m_byContributePIDCount;                              //������ͼ����ƵԴ����Ŀ
    TPartID            m_atContributePIDs[MAX_SUBFRAMES_PER_GEOMETRY];         //��ƵԴ�б�
    u8                 m_byVideoSchemeCount;                                //��ѡ����Ƶ���������Ŀ
    TOutPutVideoSchemeInfo    m_atVideoSchemeList[MAX_VIDEOSCHEMES_PER_VIEW];     //��Ƶ��������б�
  
    //add 2007.04.28
    BOOL32             m_bAutoSwitchStatus;
    BOOL32             m_bDynamic;
    s32                m_nAutoSwitchTime;
    s32                m_nVideoRole;
    

    inline tagViewInfo()
    {
        memset(this, 0, sizeof(*this));
    }
    
    inline void SetViewResolution(emResolution emRes)
    {
        m_emRes = emRes;
    }
    
    inline emResolution GetViewResolution()
    {
        return m_emRes;
    }
    
    inline void GetCurrentContributerList(TPartID **pptContributerParts, s32 &nArrayLen, s32 *pnCurrentSubframes)
    {
        if(pptContributerParts)
        {
           *pptContributerParts = m_atContributePIDs;
            nArrayLen = m_byContributePIDCount;
        }
        if(pnCurrentSubframes)
        {
           *pnCurrentSubframes = m_abyGeometryInfo[m_byCurrentGeometryIndex];
        }
        return;
    }

    inline BOOL32 SetCurrentContributerList(TPartID *ptContributerParts, s32 nArrayLen)
    {
        if(ptContributerParts != NULL && nArrayLen > 0)
        {
            s32 nSubFrameCount = 0;
            nSubFrameCount =(nArrayLen <= MAX_SUBFRAMES_PER_GEOMETRY ?
                                     nArrayLen : MAX_SUBFRAMES_PER_GEOMETRY);
            s32 nIndex = 0;
            while(nIndex < MAX_SUBFRAMES_PER_GEOMETRY && m_abyGeometryInfo[nIndex] != 0 && m_abyGeometryInfo[nIndex] != nSubFrameCount)
            {
                nIndex ++;
            }
            if(nIndex >= MAX_SUBFRAMES_PER_GEOMETRY)
            {
                return FALSE;
            }
            if(m_abyGeometryInfo[nIndex] == 0)
            {
                m_byContributePIDCount ++;
                m_byGeometryCount ++;
                m_abyGeometryInfo[nIndex] = nSubFrameCount;  
            }
            m_byCurrentGeometryIndex = nIndex;
            memcpy(m_atContributePIDs, ptContributerParts, sizeof(TPartID)*nSubFrameCount);
        }
        else
        {
            m_byGeometryCount        = 1;
            m_abyGeometryInfo[0]     = 1;
            m_byCurrentGeometryIndex = 0;
            m_byContributePIDCount   = 0;
        }
        return TRUE;
    }

    inline void SetGeometryList(u8 *pbyGeometryList, s32 nItemCount, s32 nIndexCurrentGeometry = 0)
    {
        s32 nGeometryCount = 0;
        nGeometryCount = (nItemCount < MAX_GEOMETRYS_PER_VIEW ?
                         nItemCount : MAX_GEOMETRYS_PER_VIEW);
        memcpy(m_abyGeometryInfo, pbyGeometryList,nGeometryCount * sizeof(u8));
        m_byGeometryCount = nGeometryCount;
        m_byCurrentGeometryIndex = ((m_byGeometryCount -1 > nIndexCurrentGeometry) ?
                                    nIndexCurrentGeometry : m_byGeometryCount -1);
        return;
    }
    
    inline void GetGeometryList(u8 **ppbyGeometryList, s32 *pnItemCount, s32 *pnIndexCurrentGeometry = NULL)
    {
        if(ppbyGeometryList && pnItemCount) 
        {
            *ppbyGeometryList = m_abyGeometryInfo;
            *pnItemCount      = m_byGeometryCount;
        }
        if(pnIndexCurrentGeometry)
        {
            *pnIndexCurrentGeometry = m_byCurrentGeometryIndex;
        }
        return;
    }
    
    inline void SetVideoSchemeList(TOutPutVideoSchemeInfo *ptSchemeList, s32 nItemCount)
    {
        this->m_byVideoSchemeCount = nItemCount;
        memcpy(this->m_atVideoSchemeList, ptSchemeList, nItemCount * sizeof(TOutPutVideoSchemeInfo));
    }

    inline void GetVideoSchemeList(TOutPutVideoSchemeInfo **pptSchemeList, s32 &nItemCount)
    {
        *pptSchemeList = this->m_atVideoSchemeList;
        nItemCount = this->m_byVideoSchemeCount;
        return;
    }
    
    inline s32 GetViewId() { return m_nViewId;}
    inline void SetViewId(s32 nViewId) { m_nViewId = nViewId;}

}TView, *PTView;

//
typedef struct tagConfVideInfoReq: public TReq
{
    u8          m_bFullInfo;    //�Ƿ������ͼ��β�����ͼ
    tagConfVideInfoReq(){ m_bFullInfo = TRUE; }
}TConfVideInfoReq;

//���������ڵ���MCU�ϵ���Ƶ���������Ϣ
typedef struct tagConfVideoInfo:public TRsp
{
    u8          m_byConfViewCount;                              //������ͼ����Ŀ
    //Ĭ��ʹ�õĻ�����ͼ,������MCUֱ�����ն˻���MCU�����ӽ���ʱû��ָ��������ͼ��Ϣ��
    //��Ĭ�Ϲۿ��û�����ͼ
    u8          m_byDefaultViewIndex;                            //Ĭ�ϻ�����ͼ����
    u8          m_bFullInfo;                                     //�Ƿ��ͼ��β�����ͼ
    s32         m_nSnapShot;                                     //�������ֵ
    TView       m_atViewInfo[MAX_VIEWS_PER_CONF]; //������ͼ�б�
    
    private:
        BOOL32 FindView(s32 nViewId, s32 &nViewIndex);
        
    public:

        inline tagConfVideoInfo()
        {
            m_byConfViewCount = m_byDefaultViewIndex = 0;
            m_emReturnVal = emReturnValue_Ok;
            m_bFullInfo = TRUE;
        }
        inline void Clear(void)
        {
            memset(this, 0, sizeof(*this));
            m_byConfViewCount = m_byDefaultViewIndex = 0;
            m_emReturnVal = emReturnValue_Ok;
        }
        s32 AddView(TView &tView, BOOL32 bDefaultView = FALSE, BOOL32 bReplace = TRUE);
        
        s32 DelView(s32 nViewId);
        
        s32 GetView(s32 nViewId, TView **pptView);
        
        BOOL32 IsViewExist(s32 nViewId);

        inline TView* GetItemByIndex(s32 nIndex)
        {
           return nIndex >= 0 && nIndex < m_byConfViewCount ?
               &m_atViewInfo[nIndex] : NULL;
        }
        
        inline s32 GetDefaultViewId()
        { 
            return m_atViewInfo[m_byDefaultViewIndex].GetViewId();
        }

        void DelPartRelationship(s32 nPId, BOOL32 bLocal);
     
}TConfVideoInfo;


//add 2007.04.28
typedef struct tagAutoswitchReq: public TReq     //
{
  
    s32         m_nLid;
    s32         m_nAutoSwitchTime;
    s32         m_nAutoSwitchLevel;
    BOOL32      m_bAutoSwitchOn;

public: 
    tagAutoswitchReq()
    {
        Clear();
    }


    void Clear()
    {
        memset(this, 0, sizeof(tagAutoswitchReq));
    }
    
    void SetLid(s32 nLid)
    {
        m_nLid = nLid;
    }

    s32  GetLid()
    {
        return m_nLid;
    }

    void SetAutoSwitchTime(s32 nTime)
    {
        m_nAutoSwitchTime = nTime;
    }

    s32 GetAutoSwitchTime()
    {
        return m_nAutoSwitchTime;
    }

    void SetAutoSwitchLevel(s32 nLevel)
    {
        m_nAutoSwitchLevel = nLevel;
    }

    s32 GetAutoSwitchLevel()
    {
        return m_nAutoSwitchLevel;
    }
    
    void SetAutoSwitchOn(BOOL32 bOn)
    {
        m_bAutoSwitchOn = bOn;
    }

    BOOL32 GetAutoSwitchOn()
    {
        return m_bAutoSwitchOn;
    }

}TAutoswitchReq, *PTAutoswitchReq;

typedef struct tagAutoswitchRsp: public TRsp{}TAutoswitchRsp, PTAutoswitchRsp;

#endif //_H323CONFNONSTDSTRUCT_H

/////////////////////////  ��kdv323adapter.h������ļ���������Ϣ�ͽṹ�� end    /////////
//������������ʶ�� mt<-->mcu���ݶ��˷Ǳ����ݳ���Ϊһ��BYTE�����ڴ洢������ʶ����
//��Ӧ�Ǳ���Ϣh_ctrl_KedaManuProduct					= 1121
typedef struct tagKedaManuProduct
{
	u8	m_byAgentID; //�ݶ��˷Ǳ����ݳ���Ϊһ��BYTE�����ڴ洢������ʶ����
	tagKedaManuProduct()
	{
		m_byAgentID = 0;
	}
}TKedaManuProduct;

#endif	//_H323CONFNONSTDSTRUCT_H


