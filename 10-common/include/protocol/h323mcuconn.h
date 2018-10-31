#ifndef H323MCUCONN_H_
#define H323MCUCONN_H_
#include "osp.h"
#include "kdvtype.h"
#include "time.h"
#define MMCU_API
#define MMCU_OK					(u16)0
#define MMCU_FALSE				(u16)1


typedef void (*PCascadeHandler)(s32 nMsgID, u8 *pbyBuffer, u32 dwBufLen, u32 dwUserDatad);

    extern void NewConnection(u32 hListenNode, u32 hNode, u32* phAppNode);
    extern void DispatchCascadeMsg(u32 hNode, u32 hAppNode, u8 *pBuf, s32 nLen);


//�˻���Ҳ������h323adapter.h�� ע��ṹͬ������
//#ifndef _H323ADAPTER_H
#ifndef _H323ADAPTER_H

#ifndef H323CASCADE_H_ 

//ý������
//guzh [12/14/2007] ������Χȷ��
//guzh [03/27/2008] ������ʷԭ��a_typeEnd��v_typeEnd�ȷ�Χ��׼ȷ������������ʹ��
//��ֱ��ʹ�� IsAudioType, IsAudioType, IsDataType�Ƚӿ�
enum  PayloadType 
{
    emPayloadTypeBegin = 0,
        //��Ƶ��ʽ
        a_typeBegin,
        a_g711a,
        a_g711u,
        a_g722,
        a_g7231,
        a_g728,
        a_g729,
        a_mp3,
        
        a_g723,
        a_g7221,//����a_g7221c
        
        // guzh
        a_mpegaaclc = 11,
        a_mpegaacld = 12,
        
        // �������ϰ汾����
        v_mpeg4 = 17,    
        v_h262 = 18,
        
        a_typeGeneric = 48,   // �ڲ�ʹ��
        
        a_typeEnd = 49,
        
        //��Ƶ��ʽ
        v_typeBegin = 50,	
        v_h261,
        v_h263,
        v_h263plus,
        v_h264,
        //v_mpeg4,
        //v_h262,
        v_generic = 97,
        v_extended = 98,
        v_typeEnd = 99,
        
        //���ݸ�ʽ
        d_typeBegin = 100,	
        d_t120,
        d_h224,
        d_typeEnd = 149,
        
        t_h235 = 150, //�ڲ�ʹ��
        t_mmcu,       //����ͨ��
        t_none,       //��ͨ����֧��, �����ڼ���
        t_nonStandard,
        t_huawei,
        
    emPayloadTypeEnd = 255
};

//�ֱ���
typedef enum
{    
    emResolutionBegin,
        emSQCIF,
        emQCIF,
        emCIF,
        emCIF2,
        emCIF4,
        emCIF16,
        
        em352240,
        em704480,
        em640480,
        em800600,
        em1024768,
        
        emAUTO,

        // High Definition Resolutions
        emW4CIF,        // Wide4CIF 16:9 1024*576
        emHD720p,       // 720p 1280*720
        emSXGA,         // SXGA 1280*1024
        emUXGA,         // UXGA 1600*1200
        emHD1080p,      // 1080p  1920*1080
        emHD1080i,      // 1080i  1920*1088
        
    emResolutionEnd
}emResolution;

#endif

enum H323MCUMsgType
{
    CASCADE_MSGTYPE_BEGINNING,
        
        H_CASCADE_REGUNREG_REQ,   //[IN]&[OUT]:[TRegUnRegReq]	register request
        H_CASCADE_REGUNREG_RSP,   //[IN]&[OUT]:[TRegUnRegRsp]	register response
        
        H_CASCADE_NEWROSTER_NTF,  //[IN]&[OUT]:[TRosterList]  roster notify
        
        H_CASCADE_PARTLIST_REQ,   //[IN]&[OUT]:[TReq]         request part list 
        H_CASCADE_PARTLIST_RSP,   //[IN]&[OUT]:[TPartListMsg + n*sizeof(TPart)] reponse part list (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_INVITEPART_REQ, //[IN]&[OUT]:[TInvitePartReq]  invite part request
        H_CASCADE_INVITEPART_RSP, //[IN]&[OUT]:[Tsp]             invite part response
        H_CASCADE_NEWPART_NTF,    //[IN]&[OUT]:[TPart]           new part notify
        
        H_CASCADE_CALL_ALERTING_NTF, //[IN]&[OUT]:[TCallNtf]
        
        H_CASCADE_REINVITEPART_REQ, //[IN]&[OUT]:[TReInviteReq]    reinvite part request
        H_CASCADE_REINVITEPART_RSP, //[IN]&[OUT]:[Tsp]        reinvite part response
        
        H_CASCADE_DISCONNPART_REQ, //[IN]&[OUT]:[TPartReq]     disconnect part request
        H_CASCADE_DISCONNPART_RSP, //[IN]&[OUT]:[Tsp]         disconnect part response
        H_CASCADE_DISCONNPART_NTF, //[IN]&[OUT]:[TDiscPartNF] disconnect part notify
        
        
        H_CASCADE_DELETEPART_REQ, //[IN]&[OUT]:[TPartReq]		delete part request
        H_CASCADE_DELETEPART_RSP, //[IN]&[OUT]:[Tsp]			delete part response
        H_CASCADE_DELETEPART_NTF, //[IN]&[OUT]:[TPartNtf]   delete part notify (whether or not local)
        
        H_CASCADE_SETIN_REQ,      //[IN]&[OUT]:[TSetInReq]    request video in
        H_CASCADE_SETIN_RSP,      //[IN]&[OUT]:[Tsp]          response msg
        
        H_CASCADE_SETOUT_REQ,     //[IN]&[OUT]:[TSetOutReq]//��Ƶ������Լ�������(��Ƶ����:MCU->MT)
        H_CASCADE_SETOUT_RSP,     //[IN]&[OUT]:[Tsp]//��Ƶ������Լ���Ӧ��(��Ƶ����:MCU->MT)
        
        H_CASCADE_OUTPUT_NTF,     //[IN]&[OUT]:[TPartOutputNtf]      video output notify (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_NEWSPEAKER_NTF, //[IN]&[OUT]:[TNewSpeakerNtf]      newSpeaker output notify (dwpid ==0 ��ʾ�Է���MCU)
        
        H_CASCADE_AUDIOINFO_REQ,  //[IN]&[OUT]:[TConfVideInfoReq]         audio info request 
        H_CASCADE_AUDIOINFO_RSP,  //[IN]&[OUT]:[TConfAudioInfo]    audio info response
        
        H_CASCADE_VIDEOINFO_REQ,  //[IN]&[OUT]:[pReq]          conference videoinfo request 
        H_CASCADE_VIDEOINFO_RSP,  //[IN]&[OUT]:[TConfVideoInfo] conference videoinfo response
        
        
        H_CASCADE_CONFVIEW_CHG_NTF,//[IN]&[OUT]:[TConfViewChgNtf] conference view format(layout geometry)change notify
        
        H_CASCADE_PARTMEDIACHAN_REQ,   //[IN]&[OUT]:[TPartMediaChanReq] ��������Ա��/�ر���/��Ƶ/����ͨ��
        H_CASCADE_PARTMEDIACHAN_RSP,   //[IN]&[OUT]:[TRsp]    response
        H_CASCADE_PARTMEDIACHAN_NTF,   //[IN]&[OUT]:[TPartMediaChanNtf] �����Ա����/��Ƶ/����ͨ����/�رյ�֪ͨ

        H_CASCADE_GETMCUSERVICELIST_REQ, //[IN]&[OUT]:[TReq] ��ȡMCU�ϵķ���ģ���б��������Ϣ
		H_CASCADE_GETMCUSERVICELIST_RSP,//[IN]&[OUT]:[��ʱδ����]  response

		H_CASCADE_GETMUCCONFLIST_REQ,//[IN]&[OUT]:[TMCUConfListReq] ��ȡMCU�ϵ�ǰ�ٿ������л�����б�
		H_CASCADE_GETMUCCONFLIST_RSP,//[IN]&[OUT]:[��ʱδ����]
  
        H_CASCADE_GETCONFGIDBYNAME_REQ,//[IN]&[OUT]:[TGetConfIDByNameReq] ͨ���������ֻ�û���ID��������Ϣ
        H_CASCADE_GETCONFGIDBYNAME_RSP,//[IN]&[OUT]:[��ʱδ����]
		
        H_CASCADE_GET_CONFPROFILE_REQ,//[IN]&[OUT]:[TConfProfileReq] ��ȡMCU�ϵ�ǰ�ٿ������л����profile
		
        H_CASCADE_GET_CONFPROFILE_RSP,//[IN]&[OUT]:[��ʱδ����]

        H_CASCADE_NONSTANDARD_REQ,//[IN]&[OUT]:[TNonStandardReq] �Ǳ�(�Զ���)������Ϣ
        H_CASCADE_NONSTANDARD_RSP,//[IN]&[OUT]:[TNonStandardRsp] �Ǳ�(�Զ���)response��Ϣ
		H_CASCADE_NONSTANDARD_NTF,//[IN]&[OUT]:[TNonStandardMsg] �Ǳ�(�Զ���)notify��Ϣ
		//
        H_CASCADE_NOT_SUPPORTED,
		//Ŀǰ���ǻ���֧��,����radmuc֧�ֵ���Ϣ����
        H_CASCADE_VA_REQ,       //[IN]&[OUT]:[TVAReq]
        H_CASCADE_VA_RSP,       //[IN]&[OUT]:[TRsp]

        H_CASCADE_RELEASECONTROL_OF_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_RELEASECONTROL_OF_CONF_RSP,//[IN]&[OUT]:[]

        H_CASCADE_TAKECONTROL_OF_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_TAKECONTROL_OF_CONF_RSP,//[IN]&[OUT]:[]

        H_CASCADE_ALLPART_SETOUT_REQ,//[IN]&[OUT]:[]
        H_CASCADE_ALLPART_SETOUT_RSP,//[IN]&[OUT]:[]
        
        H_CASCADE_CREATE_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_CREATE_CONF_RSP,//[IN]&[OUT]:[]
        
        H_CASCADE_TERMINATE_CONF_REQ,//[IN]&[OUT]:[]
        H_CASCADE_TERMINATE_CONF_RSP,//[IN]&[OUT]:[]

        H_CASCADE_UNDEFINED_REQ,//[IN]&[OUT]:[]
        H_CASCADE_UNDEFINED_RSP,//[IN]&[OUT]:[]
        H_CASCADE_UNDEFINED_NTF,//[IN]&[OUT]:[]


        //add 2007.04.28
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_REQUEST,//[IN]&[OUT]:TSetLayoutAutoswitchReq
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_RESPONSE,

        CASCADE_MSGTYPE_ENDING
};

#ifndef H323CASCADE_H_

#define CASCADE_PORT		    (s32)3337
#define CASCADE_USERNAME_MAXLEN     (s32)32
#define CASCADE_USERPASS_MAXLEN     (s32)32 
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
		emEPTypeCascConf                    //mcu,���Ҳμ��˼�������
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
typedef struct tagRequest
{
    s32  m_nReqID;//��ˮ��/ϵ�к�
	s8   m_aszUserName[CASCADE_USERNAME_MAXLEN];//�ʺ�
	s8   m_aszUserPass[CASCADE_USERPASS_MAXLEN];//����
	//�����ʺź�����
	inline void SetUserNameAndPass(const s8 * aszUserName, const s8 *aszUserPass)
	{
		strncpy(m_aszUserName, aszUserName, CASCADE_USERNAME_MAXLEN-1);
		m_aszUserName[CASCADE_USERNAME_MAXLEN-1] = '\0';
		strncpy(m_aszUserPass, aszUserPass, CASCADE_USERPASS_MAXLEN-1);
		m_aszUserPass[CASCADE_USERPASS_MAXLEN-1] = '\0';
	}

	tagRequest()
	{
		memset(this, 0, sizeof(*this));
	};
}TReq;


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
    emReturnValue_Ok = 0, //request��Ϣ�ѵõ���ȷ�Ĵ���
    emReturnValue_Error,//һ���Դ��󣬴���ԭ����
    emReturnValue_PartNotFound,//�������в�����������Ϣ��PIDָʾ�Ļ����Ա
    emReturnValue_ConfNotFound,//������Ϣ��confIDָ���Ļ����鲻����
    emReturnValue_ChannelNotFound,//�����Ա����Ƶ/��Ƶͨ��������
    emReturnValue_NoPermission,//�û���Ȩ�޲�����������Ϣ��������
    emReturnValue_XmlBadParams,//������Ϣ���ֶ��������ֶε�ֵ����/��Χ����
    emReturnValue_TimeOut,//������Ϣ����ʱ
    emReturnValue_NoResources,//mcuû���㹻����Դ������������Ϣ������Ƶ��Դ��Ҫ��
    emReturnValue_Invalid//������Ч,���ᱻ����
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
typedef struct tagRegUnReg: public TReq     //��Զ�mcuע��ע����������Ϣ
{
    BOOL32 m_bReg;               //true:ע��;false ע��
}TRegUnRegReq;

//������л��鼶����ע��/ע���Ļ�Ӧ��Ϣ(�ɹ� m_emReturnValΪtrue������)
typedef struct tagRegUnRegRsp :public TRsp 
{
	BOOL32 m_bReg;  //true:ע��;false ע��            
}TRegUnRegRsp;

//
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
    
     BOOL32 FindPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 &nPartIndex)
     {
         for(nPartIndex =0; nPartIndex < m_dwPartCount; nPartIndex++)
         {
             if(m_tPartOutInfo[nPartIndex].IsEmptyPart())
             {
                 return FALSE;
             }
             if(m_tPartOutInfo[nPartIndex].IsSamePart(dwPartId, bLocal))
             {
                 return TRUE;
             }
         }
         return FALSE;
     }

public: 
    tagSetOutReq(){memset(this, 0, sizeof(*this)); }

    inline s32 GetPartCount(){ return m_dwPartCount;}

    s32 AddNewPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 nOutViewID, s32 m_nOutVideoSchemeID)
    {
             s32 nPartIndex = 0;
             if( FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
             {
                 return E_ALREADY_EXISTED;
             }
             if(nPartIndex >= PART_NUM)
             {
                 return E_TOO_MANY_ITEMS;
             }
             m_tPartOutInfo[nPartIndex].m_nOutViewID = nOutViewID;
             m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID = m_nOutVideoSchemeID;
             m_tPartOutInfo[nPartIndex].SetPartGid(dwPartId, bLocal);
             m_dwPartCount++;
             return S_RIGHT;
    }
    ////////////////
    s32 DelPartViewOutItem(u32 dwPartId, BOOL32 bLocal)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        for(; nPartIndex < m_dwPartCount-1; nPartIndex++)
        {
            memcpy(&(m_tPartOutInfo[nPartIndex]), 
                   &(m_tPartOutInfo[nPartIndex + 1]), sizeof(TViewOutInfo));
        }
        m_dwPartCount--;
        return S_RIGHT;
    }
    
    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 &nViewId, s32 &nVideoSchemeId)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        nViewId        = m_tPartOutInfo[nPartIndex].m_nOutViewID;
        nVideoSchemeId = m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID;
        return S_RIGHT;
    }

    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        tPartViewOut.m_nOutViewID        = m_tPartOutInfo[nPartIndex].m_nOutViewID;
        tPartViewOut.m_nOutVideoSchemeID = m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID;
        tPartViewOut.m_dwPID             = m_tPartOutInfo[nPartIndex].m_dwPID;
        tPartViewOut.m_bLocal            = m_tPartOutInfo[nPartIndex].m_bLocal;
        return S_RIGHT;
    }

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 nViewId, s32 nVideoSchemeId)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        m_tPartOutInfo[nPartIndex].m_nOutViewID        = nViewId;
        m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID = nVideoSchemeId;
        return S_RIGHT;
    }

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut)
    {
        s32 nPartIndex = 0;
        if(! FindPartViewOutItem(dwPartId, bLocal, nPartIndex))
        {
            return E_NOT_EXISTED;
        }
        m_tPartOutInfo[nPartIndex].m_nOutViewID        = tPartViewOut.m_nOutViewID;
        m_tPartOutInfo[nPartIndex].m_nOutVideoSchemeID = tPartViewOut.m_nOutVideoSchemeID;
    }

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


//���黨�����һ��,��ʾһ������Ա�Ļ�����Ϣ
typedef struct tagTRosterItem:public TPartID
{
    emConnState  m_emConnState;    //����״̬
}TRosterItem, *PTRosterItem;

//���黨����֪ͨ
typedef struct tagRosterList:public TNtf
{
    s32          m_nCount;               //�������¼����Ŀ
    TRosterItem  m_atRoster[PART_NUM];   //��¼���б�
private: 
    BOOL32 FindRosterItem(u32 dwPartId, BOOL32 bLocal, s32 &nIndex)
    {
        for(nIndex =0; nIndex < m_nCount; nIndex++)
        {
            if(m_atRoster[nIndex].IsEmptyPart())
            {
                return FALSE;
            }
            if(m_atRoster[nIndex].IsSamePart(dwPartId, bLocal))
            {
                return TRUE;
            }
        }
        return FALSE;
    }

public:

    inline tagRosterList(){ memset(this, 0, sizeof(*this));}

    BOOL32 AddRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState)
    {
        s32  nRosterIndex = 0;
        if( FindRosterItem(dwPartId, bLocal, nRosterIndex))
        {
            return E_ALREADY_EXISTED;
        }

        if( nRosterIndex >= PART_NUM)
        {
            return E_TOO_MANY_ITEMS;
        }
        m_atRoster[nRosterIndex].m_dwPID = dwPartId;
        m_atRoster[nRosterIndex].m_bLocal = bLocal;
        m_atRoster[nRosterIndex].m_emConnState = emState;
        m_nCount ++;
        return S_RIGHT;
    }
    
    BOOL32 DelRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState)
    {
        s32  nRosterIndex = 0;
        if(! FindRosterItem(dwPartId, bLocal, nRosterIndex))
        {
            return E_NOT_EXISTED;
        }
        for(; nRosterIndex < m_nCount-1; nRosterIndex++)
        {
            memcpy(&(m_atRoster[nRosterIndex]), 
                &(m_atRoster[nRosterIndex + 1]), sizeof(TRosterItem));
        }
        m_nCount--;
        return S_RIGHT;
    } 
    
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
    BOOL32 FindViewPos(s32 nViewID, u8 bySubframeIndex, s32 &nIndex)
    {
        for(nIndex =0; nIndex < m_nViewCount; nIndex++)
        {
            if(m_anViewPos[nIndex].m_nViewID == 0)
            {
                return FALSE;
            }
            if(m_anViewPos[nIndex].m_nViewID == nViewID && m_anViewPos[nIndex].m_bySubframeIndex ==bySubframeIndex)
            {
                return TRUE;
            }
        }
        return FALSE;
    }

public:
    tagPartVideoInfo()
    {
        memset(this,0,sizeof(*this));
    }
    BOOL32 AddViewPos(s32 nViewID,u8 bySubframeIndex)
    {
        s32  nVPosIndex = 0;
        if(nViewID == 0)
        {
            return S_RIGHT;
        }
        if(FindViewPos(nViewID, bySubframeIndex, nVPosIndex))
        {
            return E_ALREADY_EXISTED;
        }
        
        if( nVPosIndex >= MAX_VIEWS_PER_CONF)
        {
            return E_TOO_MANY_ITEMS;
        }
        
        m_anViewPos[nVPosIndex].m_nViewID         = nViewID;
        m_anViewPos[nVPosIndex].m_bySubframeIndex = bySubframeIndex;

        m_nViewCount ++;
        return S_RIGHT;
    }
   
    BOOL32 DelViewPos(s32 nViewID,u8 bySubframeIndex)
    {
        s32  nVPosIndex = 0;
        if(! FindViewPos(nViewID, bySubframeIndex, nVPosIndex))
        {
            return E_NOT_EXISTED;
        }
        for(; nVPosIndex < m_nViewCount-1; nVPosIndex++)
        {
            memcpy(&(m_anViewPos[nVPosIndex]), 
                &(m_anViewPos[nVPosIndex + 1]), sizeof(TViewPos));
        }
        m_nViewCount--;
        return S_RIGHT;
    }

    BOOL32 IsViewPosExist(s32 nViewID, u8 bySubframeIndex)
    {
        s32  nVPosIndex = 0;
        if(! FindViewPos(nViewID, bySubframeIndex, nVPosIndex))
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }

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


/*
 *����ߵ���Ϣ
*/
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
    TPartVideoInfo m_tPartVideoInfo;  //��Ƶ���������Ϣ
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
        s32 nStrLen = (nNameLen >= STR_LEN ? STR_LEN -1 : nNameLen );
        strncpy(m_aszPartName, pszName, nStrLen);
        m_aszPartName[nStrLen] = '\0';

        if(pszDescr != NULL && nDescrLen > 0)
        {
            nStrLen = (nDescrLen >= STR_LEN ? STR_LEN -1 : nDescrLen );
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

//������������ߵ���Ϣ
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

    s32 DelPart(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return E_NOT_EXISTED;
         }
         for(; nPartIndex < m_dwPartCount-1; nPartIndex++)
         {
             memcpy(&(m_atParts[nPartIndex]), 
                 &(m_atParts[nPartIndex + 1]), sizeof(TPart));
         }
         m_dwPartCount--;
         return S_RIGHT;
     }
    
     s32 Disconnect(u32 dwPartId, BOOL32 bLocal, u32 dwNewPartId)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return E_NOT_EXISTED;
         }
         if(m_atParts[nPartIndex].GetConnState() == emConnStateDisconnected)
         {
             return E_ALREADY_EXISTED;
         }
         m_atParts[nPartIndex].m_dwPID = dwNewPartId;
         m_atParts[nPartIndex].SetConnState(emConnStateDisconnected);
         memset(&(m_atParts[nPartIndex].m_tPartVideoInfo), 0, sizeof(TPartVideoInfo));
         
         return S_RIGHT;
     }
    
     TPart *GetPart(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return NULL;
         }
         return &(m_atParts[nPartIndex]);
     }

     inline TPart *GetLocalMCU()
     {
         return GetPart(CACSCONF_ID, TRUE);
     }

     inline TPart *GetPeerMCU()
     {
         return GetPart(CACSCONF_ID, FALSE);
     }

     BOOL32 IsPartExist(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nPartIndex = 0;
         if(! FindPart(dwPartId, bLocal, nPartIndex))
         {
             return FALSE;
         }
         return TRUE;
     }
     
     inline TPart *GetItemByIndex(s32 nPosFrom)
     {
         return (nPosFrom >= 0 && m_dwPartCount > nPosFrom ? &m_atParts[nPosFrom] : NULL);
     }
     
}TConfPartInfo;

//�Է�MCU�����ӻ���Ļ�Ӧ�б�
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
    void BuildToPartListRsp(TConfPartInfo &tConfPart)
    {
        s32 nMemSize = 0;
        nMemSize = tConfPart.m_dwPartCount * sizeof(TPart);
        memcpy(&m_atParts[0], &tConfPart.m_atParts[0], nMemSize);
        m_nSnapShot = tConfPart.m_nSnapShot;
        m_dwPartCount = tConfPart.m_dwPartCount ;
        m_bLastPack = TRUE;
        m_emReturnVal = emReturnValue_Ok;
    }
    
    BOOL32 ExtractConfPartList(TConfPartInfo &tConfPart)
    {
        s32 nIndex      = 0;
        while( nIndex < m_dwPartCount)
        {
            tConfPart.AddPart(m_atParts[nIndex]);
            nIndex ++;
        }
        if(m_bLastPack)        
        {
            tConfPart.m_nSnapShot = m_nSnapShot;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}TPartListRsp,*PTPartListRsp;


//PartList��Ϣ�շ�ͷ�ṹ�������m_dwPartCount��TPart�ṹ
typedef struct tagPartListMsg: public TRsp
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //����Ŀ���ֵ
    BOOL32 m_bLastPack;         //whether or not last pack��used only while receiving
} TPartListMsg,*PTPartListMsg;


//�����ն˼������Ĳ���
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
    
    void SetBasicInviteeParam(const s8 *pszDialStr, s32 nStrLen, u32 dwCallRate)
    {
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(m_aszDialStr, pszDialStr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';           
        }
        m_dwCallRate = dwCallRate;
    }

    void GetBasicInviteeParam(s8 *pszDialStr, s32 nStrLen, u32 *pdwCallRate)
    {
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(pszDialStr, m_aszDialStr, nStrLen);
            pszDialStr[nStrLen] = '\0';
        }
        if(pdwCallRate)
        {
            *pdwCallRate = m_dwCallRate;
        }
        return;
    }

    inline void SetInviteeSetInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo, sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo GetInviteeSetInAndOutAttr()
    {
       return m_tPartVideoInfo;
    }
  
}TInvitePart,*PTInvitePart;


/*
  ���������뼶���������Ϣ��  
*/
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
            //strncpy(pszDialStr, m_aszDialStr, nStrLen);
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
    
    void SetPartSetInParam(u32 dwPartId, BOOL32 bLocal, s32 nViewID, u8 bySubFrameIndex)
    {
        m_dwPID =  dwPartId;
        m_bLocal = bLocal;
        m_nViewID = nViewID;
        m_bySubFrameIndex = bySubFrameIndex;
    }

    void GetPartSetInParam(s32 *pdwPartId, BOOL32 *pbLocal, s32 *pnViewID, u8 *pbySubFrameIndex)
    {
        if(pdwPartId)
        {
            *pdwPartId = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        if(pnViewID)
        {
            *pnViewID = m_nViewID;
        }
        if(pbySubFrameIndex)
        {
            *pbySubFrameIndex = m_bySubFrameIndex;
        }
    }
    
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
     BOOL32 FindSpeaker(u32 dwPartId, BOOL32 bLocal, s32 &nMixerIndex)
     {
         for(nMixerIndex =0; nMixerIndex < m_byMixerCount; nMixerIndex++)
         {
             if(m_tMixerList[nMixerIndex].m_nMixerID == 0 || m_tMixerList[nMixerIndex].m_dwSpeakerPID == 0)
             {
                 return FALSE;
             }
             if(m_tMixerList[nMixerIndex].IsSpeakerExist(dwPartId, bLocal))
             {
                 return TRUE;
             }
         }
         return FALSE;
     }
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
     
     BOOL32 AddNewSpeaker(u32 dwPartId, BOOL32 bLocal, s32 nMixerId)
     {
         s32 nMixerIndex = 0;
         if(FindSpeaker(dwPartId, bLocal, nMixerIndex))
         {
             m_tMixerList[nMixerIndex].m_nMixerID = nMixerId;
             return FALSE;
         }
         if(nMixerIndex >= MAX_MIXERS_PER_CONF)
         {
             return FALSE;
         }

         m_tMixerList[nMixerIndex].m_dwSpeakerPID = dwPartId;
         m_tMixerList[nMixerIndex].m_bLocal       = bLocal;
         m_tMixerList[nMixerIndex].m_nMixerID     = nMixerId;

         m_byMixerCount++;
         return TRUE;   
     }
     
     BOOL32 DelSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nMixerIndex = 0;
         if(! FindSpeaker(dwPartId, bLocal, nMixerIndex))
         {
             return E_NOT_EXISTED;
         }
         
         if(IsCurrentSpeaker(dwPartId, bLocal))
         {
             m_byDefaultMixerIndex = 0;
         }

         for(; nMixerIndex < m_byMixerCount-1; nMixerIndex++)
         {
             memcpy(&(m_tMixerList[nMixerIndex]), 
                 &(m_tMixerList[nMixerIndex + 1]), sizeof(TAudioMixerInfo));
         }

         m_byMixerCount--;
         return S_RIGHT;        
     }
     
     inline void GetCurrentSpeaker(u32 &dwPartId, BOOL32 &bLocal)
     {
         dwPartId = m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID;
         bLocal   = m_tMixerList[m_byDefaultMixerIndex].m_bLocal;
     }

     s32 SetCurrentSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         s32 nMixerIndex = 0;
         if(FindSpeaker(dwPartId, bLocal, nMixerIndex))
         {
             m_byDefaultMixerIndex = nMixerIndex;
             return S_RIGHT;
         }
         s32 nNewMixerId = (nMixerIndex + 1) * 10;
         AddNewSpeaker(dwPartId, bLocal, nNewMixerId);
         m_byDefaultMixerIndex = nMixerIndex;
         return nNewMixerId;
     }

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
        BOOL32 FindView(s32 nViewId, s32 &nViewIndex)
        {
            for(nViewIndex =0; nViewIndex < m_byConfViewCount; nViewIndex++)
            {
                if(m_atViewInfo[nViewIndex].m_nViewId == 0)
                {
                    return FALSE;
                }
                if(m_atViewInfo[nViewIndex].m_nViewId == nViewId)
                {
                    return TRUE;
                }
            }
            return FALSE;
        }
        
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
        s32 AddView(TView &tView, BOOL32 bDefaultView = FALSE, BOOL32 bReplace = TRUE)
        {
            s32 nViewIndex = 0;
            if( FindView(tView.GetViewId(), nViewIndex))
            {
                if(bReplace)
                {
                    memcpy(&m_atViewInfo[nViewIndex], &tView, sizeof(TView));
                    if(bDefaultView)
                    {
                        m_byDefaultViewIndex = (u8)nViewIndex;
                    }
                    return S_REPLACED;
                }
                else
                {
                    if(bDefaultView)
                    {
                        m_byDefaultViewIndex = (u8)nViewIndex;
                    }
                    return E_ALREADY_EXISTED;
                }
            }

            if(nViewIndex >= MAX_VIEWS_PER_CONF)
            {
                return E_TOO_MANY_ITEMS;
            }

            memcpy(&m_atViewInfo[nViewIndex], &tView, sizeof(TView));
            if(bDefaultView)
            {
               m_byDefaultViewIndex = (u8)nViewIndex;
            }

            m_byConfViewCount++;
            return S_RIGHT;  
        }
        
        s32 DelView(s32 nViewId)
        {
            s32 nViewIndex = 0;
            if(! FindView(nViewId, nViewIndex))
            {
                return E_NOT_EXISTED;
            }
            if(nViewIndex == m_byDefaultViewIndex)
            {
                m_byDefaultViewIndex = 0;
            }
            memmove(&m_atViewInfo[nViewIndex], &m_atViewInfo[nViewIndex +1],
                   sizeof(TView) * (m_byConfViewCount - nViewIndex - 1));
            
            m_byConfViewCount--;
            return S_RIGHT;
        }
        
        s32 GetView(s32 nViewId, TView **pptView)
        {
            s32 nViewIndex = 0;
            if(! FindView(nViewId, nViewIndex))
            {
                *pptView = NULL;
                 return E_NOT_EXISTED;
            }
            if(pptView)
            {
                *pptView = &m_atViewInfo[nViewIndex];
                return nViewIndex;
            }
            return FALSE;
        }
        
        BOOL32 IsViewExist(s32 nViewId)
        {
            s32 nViewIndex = 0;
            if(! FindView(nViewId, nViewIndex))
            {
                return FALSE;
            }
            return TRUE;
        }
        inline TView* GetItemByIndex(s32 nIndex)
        {
           return nIndex >= 0 && nIndex < m_byConfViewCount ?
               &m_atViewInfo[nIndex] : NULL;
        }
        
        inline s32 GetDefaultViewId()
        { 
            return m_atViewInfo[m_byDefaultViewIndex].GetViewId();
        }

        void DelPartRelationship(s32 nPId, BOOL32 bLocal)
        {
            s32 nIndex            = 0;
            TView *ptView         = NULL;
            TPartID *ptPartId     = NULL;
            s32     nContributors = 0;
            while(ptView = GetItemByIndex(nIndex))
            {
                ptView->GetCurrentContributerList(&ptPartId, nContributors, NULL);
                while(nContributors-- > 0)
                {
                    if((ptPartId + nContributors)->IsSamePart(nPId, bLocal))
                    {
                        //will 
                        (ptPartId + nContributors)->SetEmpty();
                    }
                }           
                nIndex ++;
            }
        }
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

#endif	//H323CASCADE_H_

//��ʼ��������
BOOL32 MMcuStackInit(u16 wListenPort,BOOL32 bSockInit = FALSE);
//���ʼ��������
BOOL32 MMcuStackClean(BOOL32 bSockClean = FALSE);



/*====================================================================
������      ��MMcuEncodeToXml
����        ��ҵ�����ݽ���XML����
�������˵����[IN]nMsgID         : ������Ϣ�ţ�H323MCUMsgType��
              [IN]pbyBuffer      : ҵ����������
              [IN]dwBufLen       : ҵ���������ݳ���
              [OUT]pbyXmlBuf     : XML����������
              [IN]dwXmlBufLen    : XML���������泤��
����ֵ˵��  ��s32         : XML����������
====================================================================*/
s32 MMcuEncodeToXml( s32 nMsgID, 
                     u8 *pbyBuffer, 
                     u32 dwBufLen, 
                     u8 *pbyXmlBuf, 
                     const u32 dwXmlBufLen );

/*====================================================================
������      ��MMcuDecodeFromXml
����        ��XML�������Ϊҵ������
�������˵����[IN]pXmlBuf           : XML���ݻ���
              [IN]nXmlLen           : XML���ݳ���
              [OUT]pResultBuf       : ����������
              [IN]dwResultBufLen    : ���������泤��
����ֵ˵��  ��s32         : ҵ�����ݳ���
====================================================================*/
s32 MMcuDecodeFromXml( u8 *pXmlBuf, 
                       s32 nXmlLen, 
                       u8 * pResultBuf, 
                       const u32 dwResultBufLen );

//�µĻ��鼶���ɹ�֪ͨ
#define 	H_CASCADE_NEW_CALL_NTF   (s32)CASCADE_MSGTYPE_ENDING  
//���鼶���Ͽ�֪ͨ
#define     H_CASCADE_DROP_CALL_NTF  (s32)(H_CASCADE_NEW_CALL_NTF+1)

API void mmcusetlog(u8 level);
API void mmcuhelp();

#endif //!_H323ADAPTER_H


class CXMLTree;
class CMCUCascade
{
public:
    CMCUCascade();
    ~CMCUCascade();
    MMCU_API u16  Connect( u32 dwPeerIP, u16 wPeerPort );
    MMCU_API u16  Disconnect();
    MMCU_API u16  SendMsg(s32 nMsgID, u8 *pbyBuffer, u32 dwBufLen);
    //ת��XML
    MMCU_API  s32  EncodeToXml( s32 nMsgID, u8 *pbyData, u32 dwDataLen, u8 *pbyXmlBuf, const u32 dwXmlBufLen );
    //����XML
    MMCU_API  s32  DecodeFromXml(u8 *pXmlBuf, s32 nXmlLen, u8 * pDataBuf, const u32 dwDataBufLen);
    MMCU_API u16  SetSrcConfId(u8 *pbyBuf, s32 nLen);
    MMCU_API u16  SetDstConfId(u8 *pbyBuf, s32 nLen);
	MMCU_API u16  RegisterEventHandler(PCascadeHandler pMsgCallback, u32 dwUserData);
    
public:
    u32             m_dwCookie;
	u32             m_dwPeerCookie;
    u32			    m_dwUserData;
    PCascadeHandler m_pfAppHandler;
	u32             m_dwNode;
	SEMHANDLE       m_hSem; 
    u8				m_abySrcConfID[CONFID_BYTELEN];
    u8				m_abyDstConfID[CONFID_BYTELEN];
    u8				m_abyChairID[CONFID_BYTELEN];
	u8*             m_pbyTcpBuf;
	s32             m_nTcpBufLen;
	u8*             m_pbyBackUp; 

    u32             m_dwLocalIP;
    u16             m_wLocalPort;
    u32             m_dwPeerIP;
    u16             m_wPeerPort;

public:
    MMCU_API u16  Init();
    MMCU_API u16  UnInit();
	void DoRcvMsg(u8 *pBuf, s32 nLen);
	s8*  BuildPid(u32 dwPid, BOOL32 bLocal = TRUE);
    BOOL32 ExtractPid(const s8* pszPID, u32 *pdwPid, BOOL32 *pbLocal=NULL);
	s32  AddPartToTree(TPart &tPart, s32 nParentNode, s32 nBrotherNode = -1); 
    
    s32 AddConfViewToRsp(TView &tViewInfo,  BOOL32 bFullInfo, s32 nParentNode, s32 nBrotherNode);
    s32 AddVideoSchemeToView(TOutPutVideoSchemeInfo &tVideoSchemeInfo, s32 nParentNode, s32 nBrotherNode);   
    s32 AddGeomtryToView(u8 nSubFrameCount,  s32 nParentNode, s32 nBrotherNode); 
        
    BOOL32 OnTcpIntegrity(u8 *pBuf, s32 nLen, u8** ppbyIntPack, s32 *pnIntSize);
    friend void NewConnection(u32 hListenNode, u32 hNode, u32* phAppNode);
    friend void DispatchCascadeMsg(u32 hNode, u32 hAppNode, u8 *pBuf, s32 nLen);
	friend CMCUCascade * RegMsgAssociateWithMMcu(u8 *pBuf, s32 nLen);
	friend CMCUCascade * FindCasIns(u8 abySrcConfID[CONFID_BYTELEN], u8 abyDstConfID[CONFID_BYTELEN]);
	void DoDefaultMsgResponse(CXMLTree *pXMLTree, const s8* pszLable);
        
private://Rcv
    s32 OnRsp(CXMLTree *pcTree, /*const s8 *pszFlag, */H323MCUMsgType emMsgType, u8* pchBuf, const u32 dwBufLen);
	s32 OnNonStandardMsgReq( CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnNonStandardMsgRsp(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnNonStandardMsgNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnRegUnRegReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnRegUnRegRsp(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnNewNeighborNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnCallNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnNewPartNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnGetPartListReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnGetPartListRsp(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnCMVideoReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnCMVideoRsp(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnCMAudioReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnCMAudioRsp(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnOutputLayoutNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnNewSpeakerNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnSetInLayoutReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnInvitePartReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnReInvitePartReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnPartDelReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnPartDiscNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnPartDiscReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnPartDelNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnSetOutLayoutReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnLayoutChgNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnPartMediaChanReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnPartMediaChanNtf(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);
    s32 OnVASetInReq(CXMLTree *pcTree, u8* pchBuf, const u32 dwBufLen);

    void OnMcuServiceListReq(CXMLTree *pcTree);
    void OnMcuConfListReq(CXMLTree *pcTree);
    void OnMcuConfProfileReq(CXMLTree *pcTree);
    void OnMcuConfIdByNameReq(CXMLTree *pcTree);
    void OnMcuServiceListRsp(CXMLTree *pcTree);
    void OnMcuConfListRsp(CXMLTree *pcTree);
    void OnMcuConfProfileRsp(CXMLTree *pcTree);
    void OnMcuConfIdByNameRsp(CXMLTree *pcTree);

    //2007.04.28
    s32 OnSetLayoutAutoswitchReq(CXMLTree *pXMLTree, u8* pchBuf, const u32 dwBufLen);
	s32 OnSetLayoutAutoswitchRsp(CXMLTree *pXMLTree, u8* pchBuf, const u32 dwBufLen);
	

    s32 ParsePartInfo(CXMLTree *pcTree,s32 nFromNode,TPart *ptPart);
    BOOL32 ParseVideoInfo(CXMLTree *pcTree,s32 nFromNode,TView *ptVideo);
    
private://Send
private://Send
    CXMLTree* ToNonStandardMsgReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToNonStandardMsgRsp(u8 *pBuf, s32 nLen);
	CXMLTree* ToNonStandardMsgNtf(u8 *pBuf, s32 nLen);

    CXMLTree* ToMcuServiceListReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToMcuConfListReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToMcuConfProfileReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToMcuConfIdByNameReq(u8 *pBuf, s32 nLen);
	//
    CXMLTree* ToMcuServiceListRsp(u8 *pBuf, s32 nLen);
    CXMLTree* ToMcuConfListRsp(u8 *pBuf, s32 nLen);
    CXMLTree* ToMcuConfProfileRsp(u8 *pBuf, s32 nLen);
    CXMLTree* ToMcuConfIdByNameRsp(u8 *pBuf, s32 nLen);
	
//////////////////////////////////////////////////////////////////////////
    CXMLTree* ToRegUnRegReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToRegUnRegRsp(u8 *pBuf, s32 nLen);
    CXMLTree* ToNewRosterNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToInvitePartReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToRsp(u8 *pBuf, s32 nLen, const s8 *pszLable);
	CXMLTree* ToCallNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToNewPartNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToPartListReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToPartListRsp(u8 *pBuf, s32 nLen, BOOL32 &bFinished, s32 nStartPartIndex, s32 nEncodedPartNum = 3);
    CXMLTree* ToReInvitePartReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToDiscPartReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToDiscPartNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToDelPartReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToDelPartNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToSetInReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToOutputNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToAudioInfoReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToAudioInfoRsp(u8 *pBuf, s32 nLen);
    CXMLTree* ToVideoInfoReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToVideoInfoRsp(u8 *pBuf, s32 nLen);
    CXMLTree* ToNewSpeakerNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToSetOutLayoutReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToLayoutChgNtf(u8 *pBuf, s32 nLen);
    CXMLTree* ToPartMediaChanReq(u8 *pBuf, s32 nLen);
    CXMLTree* ToPartMediaChanNtf(u8 *pBuf, s32 nLen);

    CXMLTree* ToMcuSetLayoutAutoswitchRequest(u8* pbyBuffer, s32 nBufLen);
	CXMLTree* ToMcuSetLayoutAutoswitchResponse(u8* pbyBuffer, s32 nLen);
};
#endif





















