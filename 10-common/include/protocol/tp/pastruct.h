

#ifndef _PA_STRUCT_H_
#define _PA_STRUCT_H_

#include <memory.h>
#include <time.h>
#include "kdvtype.h"
#include "patype.h"
#include "pamacro.h"
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif
//2012-3-6 add-by wuhu ����TPAAudChanCmd �ṹ
#define TP_MAX_EPID_LEN			64				//����ʱ��ID����ַ�������
#define SEPCHAR '.'
#define TP_INVALID_INDEX		0xFFFF
#define TP_MAX_STREAMNUM		3				  //�᳡�����������
#define TP_RET_OK	            0
#define PA_CONF_MAX_TURNNUM		64				//���������ѯ����

#define TP_PA_MAX_VMP_CHANNEL_NUM  25

#define PADiscussObjEnd          3              //����Ŀ�����
#define PA_MAXLEN_EQP_ALIAS      32
#define PA_VMP_MAX_IN_CHN_NUM    8
#define PA_REFRESH_LIST_EIGHT    1

#define PA_MAX_VMP_SUBCHAN		4
#define PA_STYLE_DATA_PACK_NUM		4

#define PA_APU2_MAX_CHAN_NUM	64
#define PA_MAX_ROLLCALL_NUM  64

#define PA_NUM_OF_CALLER_AND_TARGET   2

typedef struct tagTYouAreSeeing
{
	u32 m_dwVideoNum;//��Ƶ��������
	u32 m_dwAudioNum;//��Ƶ��������
	u16 m_wCNSId;     //CNSID
	u16 m_wMcuId;    //323mcuId
	BOOL32 m_bExist; //�Ƿ����
	s8  m_achMeetingName[PA_MAX_CONF_NAME_LEN + 1];//�����˻᳡��
	u16 m_wSpeakerIndex;
	
	tagTYouAreSeeing()
	{
		memset( this, 0, sizeof(tagTYouAreSeeing) );
	}
}TYouAreSeeing,*PTYouAreSeeing;

typedef struct tagTPAIPAddress
{
public:
	u32_ip m_dwIP ;
	u16 m_wPort;

	void Clear()
	{
		m_dwIP = 0;
		m_wPort = 0;
	}
	tagTPAIPAddress()
	{
		Clear();
	}
}TPAIPAddress, *PTPAIPAddress;

typedef struct tagTPAConfStatusInd
{
	u16 m_wMeetingId;//�᳡ID	
	s8  m_achConfName[PA_MAX_H323ALIAS_LEN + 1];

	time_t m_tBeginTime;
	s8	m_achChairName[PA_MAX_H323ALIAS_LEN + 1];	

	s8	m_achSpeakName[PA_MAX_H323ALIAS_LEN + 1];	
	u16	m_wChairVidSndCap;
	u16 m_wChairAudSndCap;
	BOOL32   m_bMixMotive;          // �Ƿ�������������
	BOOL32   m_bSpeakOnline;        // �������Ƿ�����

	tagTPAConfStatusInd()
	{
		memset( this, 0, sizeof(tagTPAConfStatusInd) );
	}

}TPAConfStatusInd, *PTPAConfStatusInd;

typedef struct tagTPAEpPathKey
{
	s8	m_achEpID[TP_MAX_EPID_LEN + 1];
	tagTPAEpPathKey()
	{
		Clear();
	}
	void Clear()
	{
		m_achEpID[0] = '\0';
	}
	
	BOOL32 IsRoot() const
	{
		if (0 == memcmp(m_achEpID, "root", 4))
		{
			return TRUE;
		}
		return FALSE;
	}
	
	BOOL32 IsValid() const
	{
		u8 byLast = SEPCHAR;
		u16 wIndex = 0;
		
		if (IsRoot())
		{
			return TRUE;
		}
		while (m_achEpID[wIndex] != '\0')
		{
			if (m_achEpID[wIndex] != SEPCHAR && (m_achEpID[wIndex] < '0' || m_achEpID[wIndex] > '9'))
			{
				return FALSE;
			}
			
			if (m_achEpID[wIndex] == SEPCHAR && m_achEpID[wIndex] == byLast)
			{
				return FALSE;
			}
			
			byLast = m_achEpID[wIndex];
			
			wIndex++;
			
			if (wIndex > TP_MAX_EPID_LEN)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	
	BOOL32 GetKeyPath(u16 awEpID[], u16 wMaxNum, u16& wRealNum) const 
	{
		wRealNum = 0;
		if (IsRoot())
		{
			return TRUE;
		}
		
		if (!IsValid())
		{
			return FALSE;
		}
		s8	achEpID[TP_MAX_EPID_LEN + 1];
		memcpy(achEpID, m_achEpID, TP_MAX_EPID_LEN + 1);
		
		s8* pchChar = achEpID;
		u16 wIndex = 0;
		while (*(pchChar+wIndex) != '\0')
		{
			if (*(pchChar+wIndex) == SEPCHAR)
			{
				if (wIndex == 0)
				{
					return FALSE;
				}
				*(pchChar + wIndex) = '\0';
				awEpID[wRealNum] = atoi(pchChar);
				++wRealNum;
				if (wRealNum >= wMaxNum)
				{
					return FALSE;
				}
				pchChar = pchChar + wIndex + 1;
				wIndex = 0;
				continue;
			}
			wIndex++;
		}
		return TRUE;
	}
}TPAEpPathKey;

typedef struct tagTPAEpKey
{
	u16 m_wEpID;			//�ϼ�֪ͨ�¼�ʱΪ�¼�ID
							//�¼�֪ͨ�ϼ�ʱΪ����ID���¼�ID
	TPAEpPathKey m_tKey;
	tagTPAEpKey()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_tKey.Clear();
	}
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_tKey.Clear();
	}

}TPAEpKey;

typedef struct tagTPAPollNodeChange
{
	TPAEpKey  m_tNodeInfo;
	tagTPAPollNodeChange()
	{
		memset( this, 0, sizeof(tagTPAPollNodeChange) );
	}
}TPAPollNodeChange, *PTPAPollNodeChange;

typedef struct tagTPACascadingSpeaker
{
	TPAEpKey m_tNodeKey;
	u16 m_wEpID;
	u16 m_wSpeaker;
	tagTPACascadingSpeaker()
	{
		memset( this, 0, sizeof(tagTPACascadingSpeaker) );
	}
}TPACascadingSpeaker;


typedef struct tagTPAPeerMuteCmd
{
	BOOL32 m_bMute;
	u16    m_wEpId;
	s8 m_achPeerMute[PA_MAX_H323ALIAS_LEN + 1];
	tagTPAPeerMuteCmd()
	{
		memset( this, 0, sizeof(tagTPAPeerMuteCmd) );
	}	
}TPAPeerMuteCmd, *PTPAPeerMuteCmd;

typedef struct tagTPAPeerMuteInd
{
	BOOL32 m_bMute;
	TPAEpKey m_tPeerMute;
	tagTPAPeerMuteInd()
	{
		memset( this, 0, sizeof(tagTPAPeerMuteInd) );
	}
}TPAPeerMuteInd,*PTPAPeerMuteInd;

typedef struct tagTHangupCascadingConf
{
	u16 m_wEpId;
	BOOL32 m_bClear;
	tagTHangupCascadingConf()
	{
		memset( this, 0, sizeof(tagTHangupCascadingConf) );
	}
}THangupCascadingConf, *PTHangupCascadingConf;


typedef struct tagTPAName
{
	s8				m_achAlias[PA_MAX_NAME_LEN+1];
	tagTPAName()
	{
		Clear();
	}
	void Clear()
	{
		m_achAlias[0]	= '\0';
	}
	void SetAlias(const s8* alias)
	{
		u16 len = strlen(alias)+1;
		len = min(len, PA_MAX_NAME_LEN);
		memcpy(m_achAlias, alias, len);
		m_achAlias[len] = '\0';
	}
	BOOL32 IsEmpty()
	{
		return '\0' == m_achAlias[0];
	}
}TPAName;

typedef struct tagTPAPollDstName
{
	s8				m_achAlias[PA_MAX_NAME_LEN + 1];
	u32             m_dwScreenNum;
	tagTPAPollDstName()
	{
		memset( this, 0, sizeof(tagTPAPollDstName) );
	}
	void SetAlias(const s8* alias)
	{
		u16 wlen = strlen(alias) + 1;
		wlen = min(wlen, PA_MAX_NAME_LEN);
		memcpy(m_achAlias, alias, wlen);
		m_achAlias[wlen] = '\0';
	}
}TPAPollDstName;

typedef struct tagTPAAskKeyByScreenTr
{
	u16		m_wEpID;
	u16		m_wScreenNum;
	BOOL32	m_bReqBySys;

    u32		m_dwAskType;               //��������  �����ˡ���ϯ��ѡ����ѯ�����ۡ�¼��������ǽ
    u32		m_dwRervse1;               //����
	u32		m_dwRervse2;               //����
}TPAAskKeyByScreenTr;



//��������
typedef struct tagTPAAlias
{
	EmPAAliasType	m_emType;     
	s8				m_achAlias[PA_MAX_NAME_LEN + 1];
	tagTPAAlias()
	{
		Clear();
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTPAAlias) );
	}
	void SetAlias(EmPAAliasType emType, const s8* pchAlias)
	{
		m_emType = emType;
		strncpy(m_achAlias, pchAlias, PA_MAX_NAME_LEN);
		m_achAlias[PA_MAX_NAME_LEN] = '\0';
	}
	
	
}TPAAlias, *PTPAAlias;


typedef struct tagTPAEpKeyID
{
	s8	m_achEpID[PA_MAX_EPID_LEN];
	
	tagTPAEpKeyID()
	{
		memset( this, 0, sizeof(tagTPAEpKeyID) );
	}
}TPAEpKeyID, *PTPAEpKeyID;

typedef struct tagTPAUmsVidFormat
{
	EmPAVideoFormat		m_emFormat;
	EmPAVideoResolution	m_emRes;
	EmPAProfileMask	    m_emProfile;//profile
	u16			    	m_wFrameRate;	//֡��
	u16				    m_wBitrate;
	
	tagTPAUmsVidFormat()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPAUmsVidFormat));
	}
}TPAUmsVidFormat;

typedef struct tagTPAUmsAudFormat
{
	EmPAAudioFormat		m_emFormat;
	EmPAAACSampleFreq	m_emPASampleFreq;
	EmPAAACChnlCfg		m_emPAChnlCfg;
	u8				m_byReserve1;
	u8				m_byReserve2;
	
	tagTPAUmsAudFormat()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPAUmsAudFormat));
	}
}TPAUmsAudFormat;

//�¼����ϼ����½����Ϣ
typedef struct tagTPAConfNodeUpdateTr
{
	TPAEpKeyID m_tID;						//��״��
	u16		 m_wEpID;						//���¼��е�ID
	
	u32	m_dwEpType;			//�������
	u32	m_dwCallState;		//����״̬
	u32	m_dwCallReason; 
	
	TPAAlias m_tCalledAddr;					//���д˽��ʱ�ĵ�ַ
	TPAAlias m_tConfName;					//�᳡��
	
	u16	m_wLevel;				//�᳡�ȼ�	����
	u32 m_dwRcvAlignType;
	
	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	//�����������ͨ�� 0,1,2,3,4���򣬲��ܱ��᳡��ʵ�Ǽ���������
	u16 m_wSpearkIndex;			//������ͨ������
	u16 m_wDualIndex;			//����˫��ͨ������
	EmPAVendorID		m_emVendorID;		//����ID

	tagTPAConfNodeUpdateTr()
	{	
		memset( this, 0, sizeof(tagTPAConfNodeUpdateTr) );
	}
}TPAConfNodeUpdateTr,*PTPAConfNodeUpdateTr;

//֪ͨ���½����Ϣ
typedef struct tagTPAConfNodeUpdateTrList
{
	u16		m_wNum;
	TPAConfNodeUpdateTr m_atList[PA_REFRESH_LIST_THREE];
	tagTPAConfNodeUpdateTrList()
	{
		m_wNum = 0;
	}
}TPAConfNodeUpdateTrList,*PTPAConfNodeUpdateTrList;

typedef struct tagTPAConfNodeUpdateB2NEWTr
{
	TPAEpKey m_tID;						//��״��
	u16		 m_wEpID;					//���¼��е�ID
	BOOL32	 m_bChanOpen;				//ͨ���Ƿ��
	BOOL32	 m_bSmallOpenEnc;			//С����
	BOOL32	 m_bSmallOpenDec;			//С����

	//B2����
	u16	m_wVidSnd;		
	u16	m_wVidRcv;	
	u16	m_wAudSnd;	
	u16	m_wAudRcv;
	
	TPAUmsVidFormat	m_tVidRcv;
	TPAUmsAudFormat	m_tAudRcv;
	
	TPAUmsVidFormat	m_tVidSnd;
	TPAUmsAudFormat	m_tAudSnd;

	TPAUmsVidFormat	m_tDualVidRcv;		//��������
	TPAUmsAudFormat	m_tDualAudRcv;
	
	TPAUmsVidFormat	m_tDualVidSnd;
	TPAUmsAudFormat	m_tDualAudSnd;

	//�غ�������������˳������Ƶ���� ��Ƶ���� ˫����Ƶ���� ˫����Ƶ���� ��Ƶ���� ��Ƶ���� ˫����Ƶ���� ˫����Ƶ����
	u16 m_awPd[PA_MAX_CHAN_NUM]; 
	BOOL32		m_bInPoll;					//�Ƿ�����ѯ�б���

	//
	tagTPAConfNodeUpdateB2NEWTr()
	{	
		memset( this, 0, sizeof(tagTPAConfNodeUpdateB2NEWTr) );
	}
	
}TPAConfNodeUpdateB2NEWTr;

typedef struct tagTPAConfNodeUpdateB2NEWTrList
{
	u16		m_wNum;
	TPAConfNodeUpdateB2NEWTr m_atList[PA_REFRESH_LIST_THREE];
	tagTPAConfNodeUpdateB2NEWTrList()
	{
		m_wNum = 0;
	}
}TPAConfNodeUpdateB2NEWTrList;

//֪ͨɾ�����
typedef struct tagTPAConfNodeDelTrList
{
	u16	     m_wNum;
	TPAEpKey m_atList[PA_REFRESH_LIST_FIVE];
	tagTPAConfNodeDelTrList()
	{
		memset( this, 0, sizeof(tagTPAConfNodeDelTrList) );
	}
}TPAConfNodeDelTrList, *PTPAConfNodeDelTrList;


typedef struct tagTPAAudMixEpCmdTr
{
	u16	m_wEpID;
	u16 m_wLocalID;					//�ϼ�����������
	TPAIPAddress m_tRtpAddr;		//�ϼ�����EP����
	TPAIPAddress m_tBackRtpAddr;	//������������BACKRTP��ַ
	tagTPAAudMixEpCmdTr()
	{
		m_tRtpAddr.Clear();
		m_tBackRtpAddr.Clear();
		m_wEpID = 0xffff;
		m_wLocalID = 0xffff;
	}
}TPAAudMixEpCmdTr, *PTPAAudMixEpCmdTr;

typedef struct tagTPAAudMixEpAckTr
{
	u16 m_wReason;				//ԭ��
	u16 m_wLocalID;
	TPAIPAddress m_tRtpAddr;		//�����ϼ������������
	TPAIPAddress m_tBackRtpAddr;	//EP������backrtp��ַ
	tagTPAAudMixEpAckTr()
	{
		m_wReason = 0;
		m_tRtpAddr.Clear();
		m_tBackRtpAddr.Clear();
		m_wLocalID = 255;
	}
}TPAAudMixEpAckTr, *PTPAAudMixEpAckTr;

typedef struct tagTDualInfo
{
	EmPAPayloadType m_emPayload;
	EmPAResolution  m_emReslution;
	u16				m_wFrameRate;
	u16             m_wBitRate;
	s32 m_nScreenNo;
	s32 m_nEpId;
	s8  m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	TPAIPAddress m_tVidRtp;
	TPAIPAddress m_tVidRtcp;
	TPAIPAddress m_tVidBackRtp;

	TPAIPAddress m_tAudRtp;
	TPAIPAddress m_tAudRtcp;
	TPAIPAddress m_tAudBackRtp;

	tagTDualInfo()
	{
		memset( this, 0, sizeof(tagTDualInfo) );
	}

}TDualInfo, *PTDualInfo;

typedef struct tagTDualInfoAck
{
	BOOL32    m_bAccept;
	TDualInfo m_tDualInfo;
	tagTDualInfoAck()
	{
		memset( this, 0, sizeof(tagTDualInfoAck) );
	}
}TDualInfoAck, *PTDualInfoAck;

typedef struct tagTDualRequest
{
	s8 m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	s32 m_nEpId;
	tagTDualRequest()
	{
		memset( this, 0, sizeof(tagTDualRequest) );
	}
}TDualRequest, *PTDualRequest;


typedef struct tagTPATvMonitorCmd
{
	s8				m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	u16				m_wIndex;
	u16				m_wEpID;
	TPAIPAddress	m_tVidRtp;
	TPAIPAddress	m_tVidRtcp;
	TPAIPAddress	m_tVidBackRtp;
	
	TPAIPAddress	m_tAudRtp;
	TPAIPAddress	m_tAudRtcp;
	TPAIPAddress	m_tAudBackRtp;

	u16 m_wScreenNum;
	
	tagTPATvMonitorCmd()
	{
		memset( this, 0, sizeof(tagTPATvMonitorCmd) );
		m_wScreenNum = 0xffff;
	}
}TPATvMonitorCmd;

typedef struct tagTPATvMonitorInd
{
	BOOL32			m_bAccept;
	s8				m_achCascade[PA_MAX_H323ALIAS_LEN+1];
	u16				m_wIndex;
	u16				m_wEpID;
	TPAIPAddress	m_tVidRtp;
	TPAIPAddress	m_tVidRtcp;
	TPAIPAddress	m_tVidBackRtp;
	
	TPAIPAddress	m_tAudRtp;
	TPAIPAddress	m_tAudRtcp;
	TPAIPAddress	m_tAudBackRtp;

    u16 m_wScreenNum;

	tagTPATvMonitorInd()
	{
		memset( this, 0, sizeof(tagTPATvMonitorInd) );
		m_wScreenNum = 0xffff;
	}
}TPATvMonitorInd;


typedef struct tagTPANodeCapsetTr
{
	u16 m_wSpeakindex;
	tagTPANodeCapsetTr()
	{
		memset( this, 0, sizeof(tagTPANodeCapsetTr) );
	}
}TPANodeCapsetTr;

//addy-by wuhu 2011-11-1  ����TPAConfCnsList�ṹ

typedef struct tagTPaMediaTransAddr
{
	TPAIPAddress m_tRtpAddr;
	TPAIPAddress m_tRtcpAddr;	
	TPAIPAddress m_tBackRtcpAddr;
	void Clear()
	{
		memset(this, 0, sizeof(tagTPaMediaTransAddr));
	}
	tagTPaMediaTransAddr()
	{
		Clear();
	}
}TPaMediaTransAddr;


#define PA_REFRESH_LIST_FIVE	5
#define PA_MAX_ALIAS_LEN		64				//������󳤶�
#define PA_MAX_STREAMNUM		3				//�᳡�����������


typedef struct tagTPACnsInfo
{
	u16	m_wEpID;							//�᳡ID
	u16	m_wParentEpID;						//���᳡ID
	u16 m_wChildEpID;
	u16 m_wBrotherEpID;
	
	EmPATPEndpointType m_emPAEpType;			//�������
	TPAAlias m_tCalledAddr;
	
	BOOL32	m_bOnline;			            //����״̬
	EmPACnsCallReason m_emPACallReason; 
	s8	m_achRoomName[PA_MAX_ALIAS_LEN + 1];	//�᳡��
	u16	m_wLevel;							//�᳡�ȼ�	����
	
	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	u16 m_wSpeakerNum;						//�᳡����	
	s8	m_achSpeakerName[PA_MAX_STREAMNUM][PA_MAX_ALIAS_LEN + 1];
	
	tagTPACnsInfo()
	{	
		Clear();
	}
	
	void Clear()
	{
		m_wEpID = PA_INVALID_VALUE;
		m_wParentEpID = PA_INVALID_VALUE;
		m_wChildEpID = PA_INVALID_VALUE;
		m_wBrotherEpID = PA_INVALID_VALUE;
		m_emPAEpType = emPATPEndpointTypeUMS;
		
		m_bOnline = FALSE;
		m_achRoomName[0] = '\0';
		m_wLevel = PA_INVALID_VALUE;
		
		m_bMute = FALSE;
		m_bQuiet = FALSE;
		m_wSpeakerNum = PA_INVALID_VALUE;
		m_emPACallReason = EmPACnsCallReason_Local;
	}
	
	BOOL32 operator == (const tagTPACnsInfo& tRhs)
	{
		return this->m_wEpID == tRhs.m_wEpID;
	}
}TPACnsInfo;

typedef struct tagTConfCnsList
{
	EmPAOprType	    m_emPAOpr;
	u16             m_wMcuId;
	u16			    m_wConfID; 
	u16		    	m_wNum;
	TPACnsInfo	    m_atConfCnsList[PA_REFRESH_LIST_FIVE];
	tagTConfCnsList()
	{
		m_emPAOpr = PA_OprType_Add;
		m_wConfID = PA_INVALID_VALUE;
		m_wNum = 0;
		m_wMcuId = 0;
	}
}TConfCnsList;

typedef struct tagTPAConfCnsList
{
    TConfCnsList m_tCnsList;
    tagTPAConfCnsList()
	{
		memset(this, 0, sizeof(tagTPAConfCnsList));
	}
	
}TPAConfCnsList;

typedef struct tagTPAChanSelecteCascad
{
   s32 m_nPeerID;
   u16 m_wCascadID;
}TPAChanSelecteCascad;

typedef struct tagTPAChanSelecteCascadRes
{
    u32 m_nRes;
	s8  m_achName[PA_MAX_ALIAS_LEN + 1];
	tagTPAChanSelecteCascadRes()
	{
		memset(this, 0, sizeof(tagTPAChanSelecteCascadRes));
	}
}TPAChanSelecteCascadRes;

typedef struct tagTPATmpChanSelecteCascadRes
{
	s32 m_nPeerID;
    u32 m_nRes;
	s8 m_achName[PA_MAX_ALIAS_LEN+1];
	tagTPATmpChanSelecteCascadRes()
	{
		memset(this, 0, sizeof(tagTPATmpChanSelecteCascadRes));
	}
}TPATmpChanSelecteCascadRes;

typedef struct tagTPAChanSelecteCascadCancelRes
{
	s32 m_nPeerID;
    u32 m_nRes;
}TPAChanSelecteCascadCancelRes;

typedef struct tagTPAPollCmd
{
	TPAIPAddress m_atRtpAddr[PA_MAX_STREAMNUM];
	TPAIPAddress m_atRtcpAddr[PA_MAX_STREAMNUM];	
	TPAIPAddress m_atBackRtcpAddr[PA_MAX_STREAMNUM];
	 
	u16 m_wBitrate;				//��ѯ����
	u16	m_wInterval;			//��ѯʱ����
	tagTPAPollCmd()
	{
		m_wBitrate = 0;
		m_wInterval = 0;
	}
}TPAPollCmd;

typedef struct tagTPAPollAck
{
	u16 m_wReason;
	TPAIPAddress m_atRtpAddr[PA_MAX_STREAMNUM];
	TPAIPAddress m_atRtcpAddr[PA_MAX_STREAMNUM];	
	TPAIPAddress m_atBackRtcpAddr[PA_MAX_STREAMNUM];
	tagTPAPollAck()
	{
		m_wReason = 0;
	}
}TPAPollAck;


typedef struct tagTPAViewCmd
{
	u16 m_wEpID;
	u16 m_wChanID;

	TPAIPAddress m_tRtpAddr;
	TPAIPAddress m_tRtcpAddr;	
	TPAIPAddress m_tBackRtcpAddr;

	TPAIPAddress m_tSmallRtpAddr;
	TPAIPAddress m_tSmallRtcpAddr;	
	TPAIPAddress m_tSmallBackRtcpAddr;
	
	TPAIPAddress m_tLeftRtpAddr;
	TPAIPAddress m_tLeftRtcpAddr;	
	TPAIPAddress m_tLeftBackRtcpAddr;

	TPAIPAddress m_tLeftSmallRtpAddr;
	TPAIPAddress m_tLeftSmallRtcpAddr;	
	TPAIPAddress m_tLeftSmallBackRtcpAddr;

	TPAIPAddress m_tRightRtpAddr;
	TPAIPAddress m_tRightRtcpAddr;	
	TPAIPAddress m_tRightBackRtcpAddr;

	TPAIPAddress m_tRightSmallRtpAddr;
	TPAIPAddress m_tRightSmallRtcpAddr;	
	TPAIPAddress m_tRightSmallBackRtcpAddr;

	BOOL32		 m_bMidOpen;
	BOOL32		 m_bSmallMidOpen;

	BOOL32		 m_bLeftOpen;
	BOOL32		 m_bSmallLeftOpen;

	BOOL32		 m_bRightOpen;
	BOOL32		 m_bSmallRightOpen;
	BOOL32		 m_bViewSpeaker;	//�Ƿ��ǽ���������ϯ

	u32          m_dwType;              //��ȡ����
	u16          m_wSrcScreenIndex;	    //Դ����

	//B2����
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//��Ƶ���յ�ַ	
	TPaMediaTransAddr m_tMixAddr;				//�������յ�ַ

	BOOL32			  m_bNeedBas;						//�Ƿ���Ҫ����

	tagTPAViewCmd()
	{
		m_bMidOpen = FALSE;
		m_bSmallMidOpen = FALSE;
		
		m_bLeftOpen = FALSE;
		m_bSmallLeftOpen = FALSE;

		m_bRightOpen = FALSE;
		m_bSmallRightOpen = FALSE;
		m_bViewSpeaker = FALSE;

		m_dwType = 0;
		m_wSrcScreenIndex = -1;

		m_bNeedBas = FALSE;
	}
}TPAViewCmd;

typedef struct tagTPAAdjustFrameRate
{
	u16  m_wEpID;
	u16	 m_wFrameRate;
	u16     m_wScreenIndx;
	BOOL32  m_bReset;
	tagTPAAdjustFrameRate()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wFrameRate = 0;
		m_wScreenIndx=0;
		m_bReset=FALSE;
	}
}TPAAdjustFrameRate;

typedef struct tagTPAAdjustVidRes
{
	u16  m_wEpID;
    u16  m_wScreenIndx;
	u32	 m_dwVidRes;
	BOOL32  m_bReset;
	tagTPAAdjustVidRes()
	{
		m_wEpID = TP_INVALID_INDEX;
        m_wScreenIndx = 1;
		m_dwVidRes = 0;
		m_bReset=FALSE;
	}
}TPAAdjustVidRes;


typedef struct tagTPAViewAck
{
	u16 m_wReason;
	u16 m_wChanID;

	TPAIPAddress m_tRtpAddr;
	TPAIPAddress m_tRtcpAddr;	
	TPAIPAddress m_tBackRtcpAddr;

	TPAIPAddress m_tSmallRtpAddr;
	TPAIPAddress m_tSmallRtcpAddr;	
	TPAIPAddress m_tSmallBackRtcpAddr;
	
	TPAIPAddress m_tLeftRtpAddr;
	TPAIPAddress m_tLeftRtcpAddr;	
	TPAIPAddress m_tLeftBackRtcpAddr;
	
	TPAIPAddress m_tLeftSmallRtpAddr;
	TPAIPAddress m_tLeftSmallRtcpAddr;	
	TPAIPAddress m_tLeftSmallBackRtcpAddr;
	
	TPAIPAddress m_tRightRtpAddr;
	TPAIPAddress m_tRightRtcpAddr;	
	TPAIPAddress m_tRightBackRtcpAddr;
	
	TPAIPAddress m_tRightSmallRtpAddr;
	TPAIPAddress m_tRightSmallRtcpAddr;	
	TPAIPAddress m_tRightSmallBackRtcpAddr;

	BOOL32		 m_bMidOpen;
	BOOL32		 m_bSmallMidOpen;
	
	BOOL32		 m_bLeftOpen;
	BOOL32		 m_bSmallLeftOpen;
	
	BOOL32		 m_bRightOpen;
	BOOL32		 m_bSmallRightOpen;

	//B2����
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//��Ƶ���յ�ַ	
	TPaMediaTransAddr m_tMixAddr;			      //�������յ�ַ
		
	tagTPAViewAck()
	{
		m_wReason = 0;

		m_bMidOpen = FALSE;
		m_bSmallMidOpen = FALSE;
		
		m_bLeftOpen = FALSE;
		m_bSmallLeftOpen = FALSE;

		m_bRightOpen = FALSE;
		m_bSmallRightOpen = FALSE;
	}
}TPAViewAck;

typedef struct tagTPACascadeOpenChanCmd
{
	u16 m_wEpID;
	
	TPaMediaTransAddr m_atVidAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atSmallAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_tMixAudAddr;

	BOOL32		 m_abVidOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abAudOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abSmallOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_bMixAudOpen;

	tagTPACascadeOpenChanCmd()
	{
		m_wEpID = TP_INVALID_INDEX;
		
		memset(m_abVidOpen, 0, sizeof(m_abVidOpen));
		memset(m_abSmallOpen, 0, sizeof(m_abSmallOpen));
		memset(m_abAudOpen, 0, sizeof(m_abVidOpen));

		m_bMixAudOpen = FALSE;
	}
	
}TPACascadeOpenChanCmd;

typedef struct tagTPACascadeOpenChanAck
{
	u16 m_wEpID;
	
	TPaMediaTransAddr m_atVidAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_atSmallAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TPaMediaTransAddr m_tMixAudAddr;

	BOOL32		 m_abVidOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abSmallOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abAudOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_bMixAudOpen;

	tagTPACascadeOpenChanAck()
	{
		m_wEpID = TP_INVALID_INDEX;
		
		memset(m_abVidOpen, 0, sizeof(m_abVidOpen));
		memset(m_abSmallOpen, 0, sizeof(m_abSmallOpen));
		memset(m_abAudOpen, 0, sizeof(m_abVidOpen));

		m_bMixAudOpen = FALSE;
	}
	
}TPACascadeOpenChanAck;


typedef struct tagTPAUmsReasonInd
{
    u16	m_wConfID;     //����
    u16 m_wEpID;       //���� ʵ�� ���ʹ��
    u32 m_dwReason;    //���� tperror.h�е�ԭ��
    
    u32 m_dwReserve1;  //����
    u32 m_dwReserve2;
    u32 m_dwReserve3;
    
    tagTPAUmsReasonInd()
    {
        m_wConfID = TP_INVALID_INDEX;
        m_wEpID   = TP_INVALID_INDEX;
        
        m_dwReason = 0;
        
        m_dwReserve1 = 0;
        m_dwReserve2 = 0;
        m_dwReserve3 = 0;
    }
}TPAUmsReasonInd;



#define PA_TP_REC_FILE_LEN  192  //¼���ļ�����󳤶�

typedef struct tagTPAUmsUpRecPlayState
{
    BOOL32		m_bIsPlayIng;	//�Ƿ��ڷ���
    BOOL32		m_bIsDualPlayIng;	//�Ƿ��˫��
    s8			m_achFileName[PA_TP_REC_FILE_LEN];	//�ļ���
    
    tagTPAUmsUpRecPlayState()
    {
        Clear();
    }
    
    void Clear()
    {
        m_bIsPlayIng = FALSE;
        m_bIsDualPlayIng = FALSE;
        memset(m_achFileName, 0, PA_TP_REC_FILE_LEN);
    }
}TPAUmsUpRecPlayState;

typedef struct tagTPAFlowControl
{
	TPAEpKey	m_tEpKey;
	u16	m_wEncNo;	//-1���������
	u16	m_wBand;
	u32 m_dwEnOpr;
	tagTPAFlowControl()
	{
		m_tEpKey.Clear();
		m_wEncNo = -1;
		m_wBand = 0;
		m_dwEnOpr = 0;
	}
}TPAFlowControl;

typedef struct tagTPAAudChanCmd
{
	TPAEpKey		m_tEpKey;
	TPAIPAddress	m_atRtpAddr[TP_MAX_STREAMNUM];
	TPAIPAddress	m_tMixRtpAddr;
	tagTPAAudChanCmd()
	{
		m_tEpKey.Clear();
		memset(m_atRtpAddr, 0, sizeof(m_atRtpAddr));
		memset(&m_tMixRtpAddr, 0, sizeof(m_tMixRtpAddr) );
	}
	
}TPAAudChanCmd;

typedef struct tagTPAAudChanAck
{
	u16		  	    m_wReason;					//ԭ��
	TPAEpKey		m_tEpKey;
	TPAIPAddress    m_atBackRtcpAddr[TP_MAX_STREAMNUM];
	TPAIPAddress    m_tMixBackRtcpAddr;
	tagTPAAudChanAck()
	{
		m_tEpKey.Clear();
		m_wReason = TP_RET_OK;
		
		memset( m_atBackRtcpAddr, 0, sizeof(m_atBackRtcpAddr) );
		memset( &m_tMixBackRtcpAddr, 0, sizeof(m_tMixBackRtcpAddr) );
	}
	
}TPAAudChanAck;


typedef struct tagTPAVidUpAddr
{
	TPAIPAddress		m_tAddr;
	TPAIPAddress		m_tSmallAddr;
	tagTPAVidUpAddr()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tAddr.Clear();
		m_tSmallAddr.Clear();
	}
}TPAVidUpAddr;

typedef struct tagTPAVidDownAddr
{
	TPAIPAddress	m_tAddr;
	TPAIPAddress	m_tSmallAddrL;
	TPAIPAddress	m_tSmallAddrR;
	tagTPAVidDownAddr()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tAddr.Clear();
		m_tSmallAddrL.Clear();
		m_tSmallAddrR.Clear();
	}
}TPAVidDownAddr;

typedef struct tagTPAVidChanCmd
{
	TPAEpKey			m_tEpKey;
	TPAVidUpAddr		m_atUpRtp[TP_MAX_STREAMNUM];		//�ϴ���Rtp�˿�
	TPAVidDownAddr		m_atDownBackRtcp[TP_MAX_STREAMNUM]; //�´���BackRtcp�˿�
	TPAIPAddress		m_atAudBackRtcp[TP_MAX_STREAMNUM];
	
	tagTPAVidChanCmd()
	{
		m_tEpKey.Clear();
		memset(m_atUpRtp, 0, sizeof(m_atUpRtp));
		memset(m_atDownBackRtcp, 0, sizeof(m_atDownBackRtcp) );
		memset(m_atAudBackRtcp, 0, sizeof(m_atAudBackRtcp) );
	}
}TPAVidChanCmd;

typedef struct tagTPAVidChanAck
{
	u16					m_wReason;	//ԭ��
	TPAEpKey			m_tEpKey;
	TPAVidUpAddr		m_atUpBackRtcp[TP_MAX_STREAMNUM];		//�ϴ���BackRtcp�˿�
	TPAVidDownAddr		m_atDownRtp[TP_MAX_STREAMNUM];		    //�´���Rtp�˿�
	TPAIPAddress		m_atAudRtp[TP_MAX_STREAMNUM];

	tagTPAVidChanAck()
	{
		m_wReason = TP_RET_OK;
		m_tEpKey.Clear();
		memset(m_atUpBackRtcp, 0, sizeof(m_atUpBackRtcp));
		memset(m_atDownRtp, 0, sizeof(m_atDownRtp));
		memset( m_atAudRtp, 0, sizeof(m_atAudRtp) );
	}
}TPAVidChanAck;


#define PA_CONF_MAX_AUDMIXNUM	27			//��������������
typedef struct tagTPAAuxMixList
{
	u16 m_wSpeakerIndex;					//�������������
	u16	m_awList[PA_CONF_MAX_AUDMIXNUM];	//����ID
	tagTPAAuxMixList()
	{
		memset(this, 0, sizeof(tagTPAAuxMixList) );
	}
}TPAAuxMixList;

typedef struct tagTPAConfAuxMixInfo
{
	u16			m_wConfID;
	BOOL32		m_bStart;
	BOOL32      m_bVacOn;
	TPAAuxMixList	m_atAuxMixList;
	u32 m_dwRet;  // �������۵Ľ��������ind��Ϣ
	tagTPAConfAuxMixInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart = FALSE;
		m_bVacOn = FALSE;
		m_dwRet = TP_INVALID_INDEX;
	}
}TPAConfAuxMixInfo;

typedef struct tagTPAConfEpID
{
	u16	m_wConfID;
	u16	m_wEpID;
	tagTPAConfEpID()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
	}
}TPAConfEpID;


typedef struct tagTPAConfTurnList
{
	BOOL32 m_bPollOn;
	u16 m_wInterval;						//��ѯ�������λ��
	u16	m_wNum;								//������ѯ����
	u16	m_awList[PA_CONF_MAX_TURNNUM];
	tagTPAConfTurnList()
	{
		Clear();
	}
	void Clear()
	{
		m_wInterval = 20;
		m_wNum = 0;
	}
}TPAConfTurnList;

typedef struct tagTPAConfTurnInfo
{
	u16				m_wConfID;
	TPAConfTurnList	m_tTurnList;
	tagTPAConfTurnInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TPAConfTurnInfo;


typedef struct tagTPAConfCallEpAddr
{
	u16	m_wConfID;
	TPAAlias	m_tAlias;
	tagTPAConfCallEpAddr()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TPAConfCallEpAddr;

typedef struct tagTPAChairConfInfo
{
	u16			m_wConfID;
	time_t		m_tBeginTime;		//���鿪ʼʱ��
	TPAAlias	m_tConfName;		//��������
	TPAAlias	m_tChairName;		//��ϯ����
	tagTPAChairConfInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tBeginTime = 0;
	}
}TPAChairConfInfo;


typedef struct tagTPAAudMixStat
{
	u16		m_wConfID;
	u16		m_wEpID;
	BOOL32	m_bIsStart;
	EmPATpMixStatus	m_emMixStatus;
	tagTPAAudMixStat()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_bIsStart = FALSE;
		m_emMixStatus = emPAAudMixIdle;
	}
}TPAAudMixStat;

// typedef struct tagTPADisScreenStat
// {
// 	BOOL32 m_bInDiscard;//�û᳡�Ƿ���������
// 	u16 m_wEpIDDst;//UMS������
// 	
// 	u16 m_awScreenNum[TP_MAX_STREAMNUM]; //��������Ӧ�᳡������
// 	u16 m_awSpeakerIndx[TP_MAX_STREAMNUM];//��������Ӧ�᳡�Ķ�Ӧ�ķ�����ϯ����
// 	TPAAlias m_atAlias[TP_MAX_STREAMNUM];//��������Ӧ�Ļ᳡��������Чֵ����˴��᳡Ϊ���迴��̬ͼƬ������Ϊ�м�
// 	u32 m_dwOprType;//��������
// 
// 	tagTPADisScreenStat(){Clear();}
// 	
// 	void Clear()
// 	{
// 		m_bInDiscard = FALSE;
// 		m_wEpIDDst = TP_INVALID_INDEX;
// 		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
// 		{
// 			m_atAlias[wIndex].Clear();
// 			m_awScreenNum[wIndex] = TP_INVALID_INDEX;
// 			m_awSpeakerIndx[wIndex] = TP_INVALID_INDEX;
// 		}
// 		m_dwOprType = 0;
// 	}
// 	
// 	void SetByScreenID( u16 wScreenID, TPAAlias tAlias, u16 wScreenNum, u16 wSpeakerIndex )
// 	{
// 		if ( wScreenID >= TP_MAX_STREAMNUM )
// 		{
// 			return ;
// 		}
// 		
// 		m_atAlias[wScreenID].SetAlias( tAlias.m_byType, tAlias.m_abyAlias);
// 		m_awSpeakerIndx[wScreenID] = wSpeakerIndex;
// 		m_awScreenNum[wScreenID] = wScreenNum;
// 		
// 		return ;
// 	}
// 	
// }TPADisScreenStat;



typedef struct tagTPADisAskKeyFrame
{
	u16 m_wEpID;//�ؼ�֡�����Դ�᳡ID
	u16 m_wScreenNo;//Դ�᳡���ĸ�������
	BOOL32 m_bReqBySys;
	tagTPADisAskKeyFrame(){Clear();}
	
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNo = TP_INVALID_INDEX;
		m_bReqBySys = FALSE;
	}
	
}TPADisAskKeyFrame; 


typedef struct tagTPADisListOpr
{

	u16 m_wConfId;
	u16 m_wNum;	                            // ��ӻ�ɾ��������
	u16 m_awEpId[PA_CONF_MAX_AUDMIXNUM];    // ���orɾ���Ļ᳡��Ա
	u32  m_dwOprType;        // ���orɾ��
	
	u32 m_adwRet[PA_CONF_MAX_AUDMIXNUM];    // ��������᳡���ظ�ÿ���᳡�Ĳ����������m_awEpId[TP_CONF_MAX_AUDMIXNUM]һһ��Ӧ������ind��Ϣ
	
	tagTPADisListOpr()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTPADisListOpr));
	}
}TPADisListOpr;

// added by ganxiebin 20120814 >>> 

// ����ն�����, ��ӦMAX_CONFMT_NUM
#define PA_MAX_CONFMT_NUM		192	

// �ն˱�Ų���
// ��Ӧmodulcallstruct.h�е�TMDLTERLABEL�ṹ��
typedef struct tagTPATerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	
	tagTPATerminalLabel()
	{
		Clear();		
	}
	
	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	BOOL32 isValid()
	{
		if( m_byTerNo <= PA_MAX_CONFMT_NUM && m_byMcuNo != 0xff )
			return TRUE;

		return FALSE;
	}

	BOOL32 operator == (const tagTPATerminalLabel& tTerLabel)
	{
      if(memcmp(this, (void*)&tTerLabel, sizeof(tTerLabel)) == 0)
			  return TRUE;
		
		  return FALSE;
	}

}TPATerminalLabel,*PTPATerminalLabel;
			

// �ն˱���б�
// ��Ӧmodulcallstruct.h�е�TMDLTERLABELLIST�ṹ��
typedef struct tagTPATerLabelList
{
	u8 m_byNum;
	TPATerminalLabel m_atTerLabelList[PA_MAX_CONFMT_NUM];
	
	tagTPATerLabelList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byNum = 0;
		memset( m_atTerLabelList, 0, sizeof(m_atTerLabelList) );
	}
}TPATerLabelList;

// �ն˱�������, ��ӦMAX_TERMINALID_LEN
#define PA_MAX_TERMINALID_LEN		128	

//�ն���Ϣ(�����), ��ӦTMDLTERMINALINFO
typedef struct tagTPATerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   //�������
	s8 m_achTerminalId[PA_MAX_TERMINALID_LEN+1];    //TerminalID
	BOOL32 m_bIsChair;   //�Ƿ�����ϯ
	BOOL32 m_bIsFloor;   //�Ƿ��Ƿ�����
	
	BOOL32 m_bLastPack;  // �Ƿ������һ��
	BOOL32 m_bOnline;    // �Ƿ�����
	
	TPATerminalLabel m_tTerYouAreView;    //����ѡ��˭
	u32 m_anSeenByOtherListMask[6];   //6��int��ʾ192��λ������ʾ192���նˣ�˭ѡ��������ն�

	tagTPATerminalInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byConfNo = 0xff;
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
		memset( m_achTerminalId, 0, sizeof(m_achTerminalId) );
		m_bIsChair = FALSE;
		m_bIsFloor = FALSE;
		
		m_bLastPack = FALSE;
		m_bOnline   = FALSE;
		m_tTerYouAreView.Clear();
		
		memset( m_anSeenByOtherListMask, 0, sizeof(m_anSeenByOtherListMask) );
	}
	
	void AddSeenByOtherList( u8 byTerNo )
	{
		if( byTerNo >= 192 )
			return;

		u8 i = byTerNo/(sizeof(u32)*8);
		u8 j = byTerNo%(sizeof(u32)*8);
		
		u32 mask = 0x00000001;
		mask <<= j;
		
		m_anSeenByOtherListMask[i] |= mask;
	}

	void DelSeenByOtherList( u8 byTerNo )
	{
		if( byTerNo >= 192 )
			return;

		u8 i = byTerNo/(sizeof(u32)*8);
		u8 j = byTerNo%(sizeof(u32)*8);

		u32 mask = 0x00000001;
		mask <<= j;

		m_anSeenByOtherListMask[i] &= ~mask;
	}

	BOOL32 IsSeenByOtherListEmpty( )
	{
		u32 temp[6];
		memset( temp, 0, sizeof(temp) );
		return !memcmp( temp, m_anSeenByOtherListMask, sizeof(temp) );
	}

	void ResetSeenByOtherList( )
	{
		memset( m_anSeenByOtherListMask, 0, sizeof(m_anSeenByOtherListMask) );
	}

	u8 GetSeenByOtherList( u8* pbyList )  //�������������192��u8
	{ 
		u8 count = 0;

		for( u8 i = 0; i < 6; i++ )
		{
			if( m_anSeenByOtherListMask[i] != 0 )
			{
				for( u8 j = 0; j < sizeof(u32)*8; j++ )
				{
					u32 mask = 0x00000001;
					mask <<= j;

					if( m_anSeenByOtherListMask[i] & mask )
					{
						pbyList[count++] = (u8)(sizeof(u32)*8*i + j);
					}
				}
			}
		}
		return count;
	}
	
}TPATerminalInfo, *PTPATerminalInfo;

typedef struct tagTPATPVMPChanInfo
{
	u16 m_wChanID;
	s8  m_achRoomName[PA_MAX_ALIAS_LEN+1];
	EmPATPVMPType m_emTPVMPType;
	BOOL32 m_bClosed;
	tagTPATPVMPChanInfo()
	{
		memset(this, 0, sizeof(tagTPATPVMPChanInfo));
	}
}TPATPVMPChanInfo;

typedef struct tagTPATPVMPInfo
{
	EmPATPVMPStyle m_emTPVMPStyle;
	TPATPVMPChanInfo m_atTPVMPChanInfo[TP_PA_MAX_VMP_CHANNEL_NUM]; //const u8 TP_MAX_VMP_CHANNEL_NUM = 25
	BOOL32 m_bOpen;
	tagTPATPVMPInfo()
	{
		memset(this, 0, sizeof(tagTPATPVMPInfo));
	}
}TPATPVMPInfo;

typedef struct tagTPATPSelViewReq
{
	EmPAUIType m_emUIType;
	
	BOOL32	 m_bSel;
	u16		 m_wConfID;
	u16		 m_wEpID;
	u16		 m_wScreenIndx;
	
	EmPAViewEpType	m_emType;
	u16				m_wDstID;
	u16				m_wDstScrIndx;
	tagTPATPSelViewReq()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPATPSelViewReq));
		m_emUIType = EmPAUI_UMC;
		m_bSel = TRUE;
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenIndx = TP_MAX_STREAMNUM;
		m_wDstID = 0;
		m_emType = EmPAEpType_Ter;
		m_wDstScrIndx = TP_MAX_STREAMNUM;  
	}

}TPATPSelViewReq;

typedef struct tagTPATPSelViewInd
{
	TPATPSelViewReq m_tSelView;
	u32 m_emRet;
	
	tagTPATPSelViewInd()
	{
		Clear();
	}
	void Clear()
	{
		m_tSelView.Clear();
		m_emRet = 0;
	}
	void SetView(TPATPSelViewReq& tView)
	{
		memcpy(&m_tSelView, &tView, sizeof(m_tSelView));
	}
}TPATPSelViewInd;
typedef struct tagTPATPSelViewNtfy
{
	TPATPSelViewReq	m_tSelView;
	EmPAOprType		m_emOpr;
	
	tagTPATPSelViewNtfy()
	{
		Clear();
	}
	void Clear()
	{
		m_tSelView.Clear();
		m_emOpr = PA_OprType_Add;
	}
	void SetView(TPATPSelViewReq& tView)
	{
		memcpy(&m_tSelView, &tView, sizeof(m_tSelView));
	}
}TPATPSelViewNtfy;

typedef struct tagTPASelViewNtfy
{
	u16				m_wEpID;
	TPATPSelViewReq	m_atSelView[TP_MAX_STREAMNUM];
}TPASelViewNtfy;

typedef struct tagTPAGetVidBaseInfo
{
	u16				m_wHandle;
	u16				m_wEpID;
	u16				m_wScreenIndex;
	EmPAGetVidType	m_emType;
	
	tagTPAGetVidBaseInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wHandle = 0;
		m_wEpID = 0;
		m_wScreenIndex = TP_MAX_STREAMNUM;
		m_emType = em_PAGetVid_Invalid;
	}
	
}TPAGetVidBaseInfo;

typedef struct tagTPAGetVidInfo
{
	TPAGetVidBaseInfo	m_tBaseInfo;
	BOOL32				m_bSamll;
	TPaMediaTransAddr	m_atVidAddr[TP_MAX_STREAMNUM];
	TPaMediaTransAddr	m_atAudAddr[TP_MAX_STREAMNUM];
	TPaMediaTransAddr	m_atSmallVid[TP_MAX_STREAMNUM];
	TPaMediaTransAddr	m_tMixAddr;
	
	tagTPAGetVidInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atVidAddr[wIndex].Clear();
			m_atAudAddr[wIndex].Clear();
			m_atSmallVid[wIndex].Clear();
		}
		
		m_tMixAddr.Clear();
		m_tBaseInfo.Clear();
		m_bSamll = FALSE;
	}
	
}TPAGetVidInfo;

typedef struct tagTPAGetVidInfoRes
{
	EmPAGetVidRes		m_emRes;
	TPAGetVidInfo		m_tInfo;
	
	tagTPAGetVidInfoRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emRes = em_PAGetVid_Success;
		m_tInfo.Clear();
	}
}TPAGetVidInfoRes;

typedef struct tagTPAStopGetVid
{
	TPAGetVidBaseInfo	m_tInfo;
	EmPAGetVidRes		m_emRes;
	
	tagTPAStopGetVid()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tInfo.Clear();
		m_emRes = em_PAGetVid_Success;
	}
}TPAStopGetVid;

typedef struct tagTPACasecadePollEpReq
{
	BOOL32				m_bCreate;
	u16					m_wEpID;
	TPAIPAddress		m_atPollAddr[TP_MAX_STREAMNUM];
	TPAIPAddress		m_atPollSmallAddr[TP_MAX_STREAMNUM];
	tagTPACasecadePollEpReq()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bCreate = TRUE;
		m_wEpID = TP_INVALID_INDEX;
		
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atPollAddr[wIndex].Clear();
			m_atPollSmallAddr[wIndex].Clear();
		}
	}
	
}TPACasecadePollEpReq;

typedef struct tagTPACasecadePollEpRsp
{
	TPACasecadePollEpReq	m_tReq;
	u32		        m_emRes;
	
	tagTPACasecadePollEpRsp()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tReq.Clear();
		m_emRes = 0;
	}
	
}TPACasecadePollEpRsp;


typedef struct tagTPAPollListNtfy
{
	u16		m_wConfID;
	u16		m_wInterval;				//��ѯ�������λ��
	s32		m_nFlag;                    //��ѯ���濪��״̬
	u16		m_wTotalNum;				//������
	u16		m_wCurNum;					//����Я������
	u16		m_awList[PA_CONF_MAX_TURNNUM];
	tagTPAPollListNtfy()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wInterval = 0;
		m_nFlag = 0;
		m_wTotalNum = 0;
		m_wCurNum = 0;
		memset(m_awList, 0, sizeof(m_awList));
	}
}TPAPollListNtfy;

typedef struct tagTPAPollListInd
{
	u16		m_wConfID;
	s32		m_nFlag;					//���±�ʶ
	u16		m_wRet;
    u16     m_wCurRcvNum;   // ��ǰ�Ѿ�������ɵ�����
	tagTPAPollListInd()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_nFlag = 0;
		m_wRet = TP_RET_OK;
	}
}TPAPollListInd;

typedef struct tagTPAPollStat
{
	u16			m_wConfID;
	EmPAPollStat	m_emStat;
	tagTPAPollStat()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_emStat = emPAPollStat_Stop;
	}
}TPAPollStat;

typedef struct tagTPADiscussObjInfo
{
	u16 wReserve; // 0 speakerobj, 1 ThreeObj, 2 SingleObj,
	
	BOOL32   m_abIsVaild[TP_MAX_STREAMNUM];
	TPAAlias m_atEpAlias[TP_MAX_STREAMNUM];
	
	tagTPADiscussObjInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTPADiscussObjInfo));
	}
	
}TPADiscussObjInfo;

typedef struct tagTPADiscussCasecadeNtfy
{
	BOOL32 m_bIsDiscussModle;
	
	TPADiscussObjInfo m_atDiscussObj[PADiscussObjEnd];

	//u16       m_awDiscussEpId[PA_CONF_MAX_AUDMIXNUM];
	//BOOL32    m_bIsRcvNModeAud[PA_CONF_MAX_AUDMIXNUM];

	u16       m_awDiscussEpId[PA_CONF_MAX_AUDMIXNUM];
	u8        m_abyIsRcvNModeAud[PA_CONF_MAX_AUDMIXNUM][TP_MAX_STREAMNUM];

	tagTPADiscussCasecadeNtfy()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTPADiscussCasecadeNtfy));
	}
	
}TPADiscussCasecadeNtfy;

typedef struct tagTPAEqpInfo
{
	u8			m_byEqpID;			//EqpID
	u32			m_emEqpType;		// ��������
	
	s8			m_szEqpAlias[PA_MAXLEN_EQP_ALIAS];//�������
	tagTPAEqpInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_byEqpID = 0;
		m_emEqpType = 0;
		memset(m_szEqpAlias, 0, sizeof(m_szEqpAlias));
	}
}TPAEqpInfo;

typedef struct tagTPARersvesEqpReq
{
	u16			m_wConfID;
	BOOL32		m_bRersves;
	TPAEqpInfo	m_tEqp;
	tagTPARersvesEqpReq()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bRersves = FALSE;
		m_tEqp.Clear();
	}
}TPARersvesEqpReq;

typedef struct tagTPARersvesEqpRsp
{
	u16				m_wConfID;
	u32				m_emRet;
	TPARersvesEqpReq	m_tRersvesReq;
	tagTPARersvesEqpRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_emRet = 0;
		m_tRersvesReq.Clear();
	}
}TPARersvesEqpRsp;

typedef struct tagTPABrdVmpChnl
{
	u16 m_wEpID;
	u16 m_wScrIndx;
	tagTPABrdVmpChnl()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScrIndx = 0;
	}
	
	BOOL32 IsValid()
	{
		return m_wEpID;
	}
}TPABrdVmpChnl;

typedef struct tagTPABrdVmpStyle
{
	EmPATPVMPStyle	m_emVmpStyle;	//������
	u16			m_wSpeakerIndx;//�����˸�������
	u16			m_wChairIndx;//��ϯ��������
	u16			m_wChnlNum;
	TPABrdVmpChnl m_atVmpChnl[TP_PA_MAX_VMP_CHANNEL_NUM];
	tagTPABrdVmpStyle()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wSpeakerIndx = TP_INVALID_INDEX;
		m_wChairIndx = TP_INVALID_INDEX;
		m_wChnlNum = 0;
		for ( u16 wIndex = 0; wIndex < TP_PA_MAX_VMP_CHANNEL_NUM; wIndex ++ )
		{
			m_atVmpChnl[wIndex].Clear();
		}
	}
	
}TPABrdVmpStyle;

typedef struct tagTPASetVmpInfoReq
{
	u16				m_wConfID;
	TPAEqpInfo		m_tEqp;
	TPABrdVmpStyle	m_tStyle;
	tagTPASetVmpInfoReq()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tEqp.Clear();
		m_tStyle.Clear();
	}
}TPASetVmpInfoReq;

typedef struct tagTPASetVmpInfoRsp
{
	u16				m_wConfID;
	TPASetVmpInfoReq	m_tReq;
	u32		m_emRet;
	tagTPASetVmpInfoRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tReq.Clear();
		m_emRet = 0;
	}
}TPASetVmpInfoRsp;

typedef struct tagTPABrdVmpReq
{
	u16			m_wConfID;
	BOOL32		m_bBrd;
	TPAEqpInfo	m_tEqp;
	tagTPABrdVmpReq()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bBrd = FALSE;
		m_tEqp.Clear();
	}
}TPABrdVmpReq;

typedef struct tagTPABrdVmpRsp
{
	u16			m_wConfID;
	TPABrdVmpReq	m_tReq;
	u32 m_emRet;
	tagTPABrdVmpRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tReq.Clear();
		m_emRet = 0;
	}
}TPABrdVmpRsp;

typedef struct tagTPAVmpCasecadeNtfy
{
	BOOL32	m_bBrdVmp;
	BOOL32	m_bSpeakerVmp;
	s8		m_szBrdVmpAlias[PA_MAXLEN_EQP_ALIAS];
	tagTPAVmpCasecadeNtfy()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPAVmpCasecadeNtfy));
	}
}TPAVmpCasecadeNtfy;


typedef struct tagTPABrdVmpResNtfy
{
	u16				m_wConfID;
	BOOL32			m_bVmpAuto;
	u32				m_dwStat;
	TPAEqpInfo		m_tEqpInfo;
	TPABrdVmpStyle	m_tVmpStyle;
	EmPAOprType		m_emOpr;
	
	tagTPABrdVmpResNtfy()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emOpr = PA_OprType_Add;
		m_bVmpAuto = FALSE;
		m_wConfID = TP_INVALID_INDEX;
		m_tVmpStyle.Clear();
		m_tEqpInfo.Clear();
		m_dwStat = 0;
	}	
}TPABrdVmpResNtfy;

typedef struct tagTPABrdVmpResArray
{
	u16					m_wNum;
	TPABrdVmpResNtfy	m_atVmpNtfy[PA_REFRESH_LIST_EIGHT];
	tagTPABrdVmpResArray()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wNum = 0;
		for(u16 wIndex = 0; wIndex < PA_REFRESH_LIST_EIGHT; wIndex ++)
		{
			m_atVmpNtfy[wIndex].Clear();
		}
	}
}TPABrdVmpResArray;

typedef struct tagTPAConfAuxMixVacOpr
{
	u16			m_wConfID;
	BOOL32      m_bVacOn;
	u16         m_wOprRet; 
	
	tagTPAConfAuxMixVacOpr()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bVacOn = FALSE;
		m_wOprRet = 0;
	}
}TPAConfAuxMixVacOpr;

typedef struct tagTPAVmpCfgChnl
{
	u16         m_wScrIndx;
	TPAAlias    m_tEpAlias;
	tagTPAVmpCfgChnl()
	{
		Clear();
	}

	void Clear()
	{
		m_wScrIndx = 0;
		m_tEpAlias.Clear();
	}
}TPAVmpCfgChnl;

typedef struct tagTPAVmpMemberCfg
{
	u16			m_wConfID;
	EmPATPVMPStyle	m_emStyle;
	u16			m_wFlag;
	u16			m_wTotalNum;
	u16			m_wEpNum;
	u16			m_wSpeakerIndx;		   
	u16			m_wDualIndx;		   
	BOOL32              m_bFirst;              
	TPAVmpCfgChnl       m_atEpList[PA_VMP_MAX_IN_CHN_NUM]; 
	tagTPAVmpMemberCfg()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_emStyle = emPAVmpStyle_DYNAMIC;
		m_wFlag = 0; 
		m_wEpNum = 0;
		m_wTotalNum = 0;
		m_bFirst = FALSE;
		m_wSpeakerIndx = TP_INVALID_INDEX;
		m_wDualIndx = TP_INVALID_INDEX;		

		for ( u16 wIndex = 0; wIndex < PA_VMP_MAX_IN_CHN_NUM; wIndex ++ )
		{
			m_atEpList[wIndex].Clear();
		}
	}
}TPAVmpMemberCfg;

typedef struct tagTPAVmpMemberCfgInd
{
	u16			m_wConfID;
	BOOL32		m_bRet;
	u16			m_wFlag;
	tagTPAVmpMemberCfgInd()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bRet = TRUE;
		m_wFlag = 0;
	}
}TPAVmpMemberCfgInd;

typedef struct tagTPAObj
{
	u16			m_wVidNum;
	u16			m_wAudNum;
	u16			m_wScrIndx;
	EMPAScreenObj m_emObj;
	TPAAlias	m_tAlias;

	tagTPAObj()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wVidNum = 0;
		m_wAudNum = 0;
		m_wScrIndx = 0;
		m_emObj = emPAObjSelf;
		m_tAlias.Clear();
	}
}TPAObj;

typedef struct tagTPAYouAreSeeing
{
	BOOL32		m_bSpeaker;
	u16			m_wVidNum;
	u16			m_wAudNum;
	TPAObj		m_atObj[TP_MAX_STREAMNUM];
	
	tagTPAYouAreSeeing()
	{
		m_wVidNum = 0;
		m_wAudNum = 0;
		m_bSpeaker = TRUE;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atObj[wIndex].Clear();
		}
	}
}TPAYouAreSeeing;
typedef struct tagTPACallAddr
{
	TPAAlias	    m_tAlias;
	TPAAlias    	m_tE164;
	u32_ip		    m_dwIP;
	BOOL32          m_bAliasIP;
	EmPAAliasType	m_byCallType;
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTPACallAddr));
	}
	tagTPACallAddr()
	{
		Clear();
	}

}TPACallAddr;

typedef struct tagTPAConfEpInfo
{
	u16 m_wConfID; 
	TPACallAddr m_tCallAddr;
	
	u16 m_Index;
	BOOL32 m_bPermit;
	
	tagTPAConfEpInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tCallAddr.Clear();
		m_Index = TP_INVALID_INDEX;
		m_bPermit = FALSE;
	}
	
}TPAConfEpInfo;

typedef struct tagTPAHduUnitPlayInfo
{
	u16		m_wConfID;		//����ID
	u16		m_wDstID;
	s8      m_achAlias[TP_MAX_EPID_LEN+1];
	u16		m_wScreenNum;	//����
	EmPAViewEpType		m_emType;
	EmPAHduRunStatus	m_emStatus;
	tagTPAHduUnitPlayInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_emStatus = emPAHdu_Idle;
	}
	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_EPID_LEN);
		m_achAlias[TP_MAX_EPID_LEN] = '\0';
	}
}TPAHduUnitPlayInfo;
typedef struct tagTPAHduPlanUnit
{	
	u8  	m_byReged;	//����״̬
	u8      m_byValid;
	u16		m_wIndex;	//����
	TPAName	m_tHduName;	//HDU ������
	u8   	m_byVmp;
	u8		m_byVol;
	u8  	m_byMute;
	u8		m_byChanIndex;	//ͨ���� 0 �� 1
	TPAHduUnitPlayInfo	m_atPlayInfo[PA_MAX_VMP_SUBCHAN];
	tagTPAHduPlanUnit()
	{
		Clear();
	}
	void Clear()
	{
		m_byReged = 0;
		m_byValid = 0;
		m_wIndex = TP_INVALID_INDEX;
		m_tHduName.Clear();
		m_byVmp = 0;
		m_byVol = 0;
		m_byMute = 0;
		m_byChanIndex = 0;
		for (u16 wIndex = 0 ; wIndex < PA_MAX_VMP_SUBCHAN; wIndex++)
		{
			m_atPlayInfo[wIndex].Clear();
		}
	}
}TPAHduPlanUnit;
typedef struct tagTPAHduPlanPackData
{
	u8		m_byRow;
	u8		m_byCol;
	u16		m_wNum; // ����
	u8      m_byFirst; // �Ƿ��ǵ�һ��
	u8		m_CurentNum;  // ��ǰ�������������Ч����
	TPAHduPlanUnit m_atUnits[PA_STYLE_DATA_PACK_NUM];  
	tagTPAHduPlanPackData()
	{
		Clear();
	}
	void Clear()
	{
		m_byRow = 0;
		m_byCol = 0;
		m_wNum = 0;
		m_byFirst = 0;
		m_CurentNum = 0;
		for (u16 wIndex = 0; wIndex < PA_STYLE_DATA_PACK_NUM; wIndex++)
		{
			m_atUnits[wIndex].Clear();
		}
	}
}TPAHduPlanPackData;
typedef struct tagTPAHduPlayReq
{
	EmPAViewEpType	m_emType;
	u16		m_wConfID;
	u16		m_wDstID;   // ����ǻ᳡�����ǻ᳡id������Ǻϳ�������������id
	s8      m_achAlias[PA_MAX_ALIAS_LEN + 1];  // �᳡���ƻ�����������
	u16		m_wScreenNum;  // 
	u16		m_wIndex;		//����
	u8		m_bySubIndex;	//������
	BOOL32	m_bVmp; //�Ƿ��Ǻϳ�ͨ��
	tagTPAHduPlayReq()
	{
		m_emType = EmPAEpType_Ter;
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX;
		m_bySubIndex = PA_MAX_VMP_SUBCHAN;
		m_bVmp = FALSE;
	}
	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, PA_MAX_ALIAS_LEN);
		m_achAlias[PA_MAX_ALIAS_LEN] = '\0';
	}
	tagTPAHduPlayReq& operator = (const tagTPAHduPlayReq& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tRhs));
		return *this;
	}
}TPAHduPlayReq;

typedef struct tagTPAHduBaseInfo
{
	u16		m_wIndex;
	u8		m_bySubIndex;
	tagTPAHduBaseInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_bySubIndex = 0;
	}
}TPAHduBaseInfo;

typedef struct tagTPAHduSetVolInfo
{
	TPAHduBaseInfo	m_tInfo;
	u8		m_byVol;
	BOOL32	m_bMute;
	tagTPAHduSetVolInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tInfo.Clear();
		m_byVol = 0;
		m_bMute = FALSE;
	}
}TPAHduSetVolInfo;

typedef struct tagTPAHduChanModeSetInfo
{
	u16 m_wIndex;  // ͨ������
	u8  m_byMode;  // 0 Ϊһ���棬1Ϊ4����
	tagTPAHduChanModeSetInfo()
	{
		Clear();
	}
	BOOL32 IsValidMode()
	{
		return (0 == m_byMode || 1 == m_byMode);
	}
	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_byMode = 0;
	}
}TPAHduChanModeSetInfo;

typedef struct tagTPAUmsAudMixList
{
	u16	m_wNum;
	u16	m_awMixEp[PA_APU2_MAX_CHAN_NUM];

	tagTPAUmsAudMixList()
	{
		Clear();
	}

	void Clear()
	{
		m_wNum = 0;
		for (u16 wIndex = 0; wIndex < PA_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_awMixEp[wIndex] = TP_INVALID_INDEX;
		}
	}

}TPAUmsAudMixList;

typedef struct tagTPAUmsAudMixInfo
{
	u16			m_wConfId;
	TPAUmsAudMixList		m_tMixList;
	u32		m_dwMode;  // ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��

	tagTPAUmsAudMixInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tMixList.Clear();
		m_dwMode = 0;
	}

}TPAUmsAudMixInfo;

typedef struct tagTPAUmsAudMixModeCmdRes
{
	u16		m_wConfId;
	u32		m_dwCmdMode;    // ö��Э�����u32����
	u32		m_dwRes;        // ö��Э�����u32����

	tagTPAUmsAudMixModeCmdRes()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_dwCmdMode = 0;
		m_dwRes = 0;
	}

}TPAUmsAudMixModeCmdRes;

typedef struct tagTPAUmsAudMixListCmd
{
	u16			m_wConfId;   
	TPAUmsAudMixList		m_tList;     //����Ϣ1
	u32	m_dwOpr;     // ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��

	tagTPAUmsAudMixListCmd()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tList.Clear();
		m_dwOpr = 0;
	}

}TPAUmsAudMixListCmd;

typedef struct tagTPAUmsAudMixListCmdRes
{
	u16			m_wConfId;
	TPAUmsAudMixList		m_tList;    //����Ϣ1
	u32		m_aRes[PA_APU2_MAX_CHAN_NUM];   // ö��Э�����u32����

	tagTPAUmsAudMixListCmdRes()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tList.Clear();
		for (u16 wIndex = 0; wIndex < PA_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_aRes[wIndex] = 0;
		}
	}

}TPAUmsAudMixListCmdRes;

typedef struct tagTPAUmsAudMixCasecadeInfo
{
	u32		    m_dwMode;    // ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��
	u32			m_dwReserve; // �����ֶ�
	u32			m_dwReserve1; 

	tagTPAUmsAudMixCasecadeInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_dwMode = 0;
		m_dwReserve = 0;
		m_dwReserve1 = 0;
	}


}TPAUmsAudMixCasecadeInfo;


typedef struct tagTPARollCallList
{
	u16	m_wNum;
	u16	m_awList[PA_MAX_ROLLCALL_NUM];	     //�����б�,���б�������
	u16 m_wRollCaller;                           //������
	u16 m_wCallTarget;                           //��������
	tagTPARollCallList()
	{
		Clear();
	}

	void Clear()
	{
		for (u16 wIndex = 0; wIndex < PA_MAX_ROLLCALL_NUM; ++wIndex)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}

		m_wNum = 0;
		m_wRollCaller = TP_INVALID_INDEX;
		m_wCallTarget = TP_INVALID_INDEX;
	}
	
}TPARollCallList, *PTPARollCallList;

typedef struct tagTPAConfRollCallInfo
{
	u16			m_wConfID;            //����ID
	BOOL32			m_bStart;             //�����رյ���
	TPARollCallList		m_atRollCallMemList;  //�����б�
	u32	        m_dwRet;              // ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��

	tagTPAConfRollCallInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart  = FALSE;

		m_atRollCallMemList.Clear();
		m_dwRet = 0;
	}

}TPAConfRollCallInfo;

typedef struct tagTPARollCallNextEpInfo
{
	u16 m_wConfID;                  //����ID
	u16 m_wRollCaller;              //������
	u16 m_wCallTarget;              //��������
	u32 m_dwRet;       // ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��              

	tagTPARollCallNextEpInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wRollCaller = TP_INVALID_INDEX;
		m_wCallTarget = TP_INVALID_INDEX;
		m_dwRet = 0;
	}

}TPARollCallNextEpInfo;

typedef struct tagTPARollCallEpNodeInfo
{
	u16 m_wEpId;           //�����˱��������ڱ���UMS �е�EPID ������ڱ�����ΪInvalid

	u16 m_wVidSndNum;     
	u16 m_wVidRcvNum;

	u16 m_wAudSndNum;
	u16 m_wAudRcvNum;

	u16 m_wSpeakerSeat;   //��ϯ

	TPAAlias  m_Alias;

	tagTPARollCallEpNodeInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wEpId = TP_INVALID_INDEX;     

		m_wVidSndNum = 0;     
		m_wVidRcvNum = 0;

		m_wAudSndNum = 0;
		m_wAudRcvNum = 0;

		m_wSpeakerSeat = 0; 

		m_Alias.Clear(); 
	}

	tagTPARollCallEpNodeInfo& operator = (const tagTPARollCallEpNodeInfo& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}

		m_wEpId      = tRhs.m_wEpId;     
		m_wVidSndNum = tRhs.m_wVidSndNum;     
		m_wVidRcvNum = tRhs.m_wVidRcvNum;
		m_wAudSndNum = tRhs.m_wAudSndNum;
		m_wAudRcvNum = tRhs.m_wAudRcvNum;
		m_wSpeakerSeat = tRhs.m_wSpeakerSeat; 
		m_Alias        = tRhs.m_Alias; 

		return *this;
	}

	BOOL32 IsVidSndValid() const	{ return m_wVidSndNum > 0 && m_wVidSndNum % 2 != 0; }
	BOOL32 IsVidRcvValid() const	{ return m_wVidRcvNum > 0 && m_wVidRcvNum % 2 != 0; }
	BOOL32 IsAudSndValid() const	{ return (m_wAudSndNum > 0 && m_wAudSndNum % 2 != 0); }
	BOOL32 IsAudRcvValid() const	{ return (m_wAudRcvNum > 0 && m_wAudRcvNum % 2 != 0); }
	//u16 GetSpeaker()const	{ return m_wSpeakerSeat < TP_MAX_STREAMNUM ? m_wSpeakerSeat :  (u16)(MIDSCREENINDEX);}

}TPARollCallEpNodeInfo;

typedef struct tagTPARollCallCasecadeNtfy

{
	u32  m_dwNotyType;         //ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��
	BOOL32                      m_bIsRollCallModle;  
	TPARollCallEpNodeInfo         m_NodeInfo[PA_NUM_OF_CALLER_AND_TARGET];

	tagTPARollCallCasecadeNtfy()
	{
		Clear();
	}

	void Clear()
	{
		m_dwNotyType         = 0;
		m_bIsRollCallModle = FALSE;

		for(u16 wIndex = 0; wIndex < PA_NUM_OF_CALLER_AND_TARGET; wIndex++)
		{
			m_NodeInfo[wIndex].Clear();
		}
	}

	tagTPARollCallCasecadeNtfy& operator = (const tagTPARollCallCasecadeNtfy& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}

		m_dwNotyType            = tRhs.m_dwNotyType;
		m_bIsRollCallModle    = tRhs.m_bIsRollCallModle;


		for(u16 wIndex = 0; wIndex < PA_NUM_OF_CALLER_AND_TARGET; wIndex++)
		{
			m_NodeInfo[wIndex] = tRhs.m_NodeInfo[wIndex];
		}

		return *this;
	}

}TPARollCallCasecadeNtfy;

typedef struct tagTPAUpdataRollCallList
{
	u16			m_wConfID;            //����ID
	BOOL32			m_bAdd;               //���ɾ��
	TPARollCallList		m_atRollCallMemList;  //�˽ṹ ��ӦЭ��ջ��ϢTPARollCallList

	tagTPAUpdataRollCallList()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bAdd    = FALSE;

		m_atRollCallMemList.Clear();
	}

}TPAUpdataRollCallList;

typedef struct tagTPAUpdataRollCallListRes
{
	u16		    m_wConfID;                      //����ID
	BOOL32		    m_bAdd;                         //���ɾ��
	TPARollCallList	    m_atRollCallMemList;            //�˽ṹ ��ӦЭ��ջ��ϢTPARollCallList 
	u32    m_emRet[PA_MAX_ROLLCALL_NUM];   //ö��Э�����u32���ݣ�ҵ��ౣ��ͳһ���弴��  TP_MAX_ROLLCALL_NUM ��ӦЭ��ջ PA_MAX_ROLLCALL_NUM 

	tagTPAUpdataRollCallListRes()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bAdd    = FALSE;

		m_atRollCallMemList.Clear();

		for(u16 wIndex = 0; wIndex < PA_MAX_ROLLCALL_NUM; wIndex++)   
		{
			m_emRet[wIndex] = 0;
		}
	}

}TPAUpdataRollCallListRes;

typedef struct tagTPARollCallPresentStateEpInfo
{
	u16 m_wEpID;                  //����ID
	u16 m_wEpState;               

	tagTPARollCallPresentStateEpInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wEpState = 0;
	}

}TPARollCallPresentStateEpInfo;


typedef struct tagTPARollCallPresentStateMsg
{
	u16 m_wConfID;

	u16 m_wValidNum;              //  ״̬��������Ч��
	TPARollCallPresentStateEpInfo  m_atEpState[PA_MAX_ROLLCALL_NUM];  //��������״̬  //TP_MAX_ROLLCALL_NUM ��ӦЭ��ջ PA_MAX_ROLLCALL_NUM 

	tagTPARollCallPresentStateMsg()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID      = TP_INVALID_INDEX;
		m_wValidNum    = 0;

		for(u16 wIndex = 0; wIndex < PA_MAX_ROLLCALL_NUM; wIndex++)   //TP_MAX_ROLLCALL_NUM ��ӦЭ��ջ PA_MAX_ROLLCALL_NUM 
		{
			m_atEpState[wIndex].Clear();
		}
	}
}TPARollCallPresentStateMsg;

#define UMS_PA_MAX_VID_SOURCE_NUM                  10			  // ��ƵԴ������
#define UMS_PA_MAX_VID_ALIAS_LEN					16            // ��ƵԴ������󳤶�
typedef struct tagTPAVidAliasInfo
{
	u8	m_byIndex;							// ��ƵԴ����
	s8  m_abyAlias[UMS_PA_MAX_VID_ALIAS_LEN];	// ��ƵԴ���� [16]H.323�᳡�����ƵԴ��������
	tagTPAVidAliasInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPAVidAliasInfo));
	}

}TPAVidAliasInfo;

typedef struct tagTPAVidSourceInfo
{
	u8	m_byNum;
	TPAVidAliasInfo m_atVidInfo[UMS_PA_MAX_VID_SOURCE_NUM]; // ��ƵԴ��Ϣ [10]H.323�᳡�����ƵԴ��
	tagTPAVidSourceInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPAVidSourceInfo));
	}

	tagTPAVidSourceInfo& operator = (tagTPAVidSourceInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_byNum = tInfo.m_byNum;
			for (u16 wIndex = 0; wIndex < m_byNum; ++wIndex)
			{
				m_atVidInfo[wIndex].m_byIndex = tInfo.m_atVidInfo[wIndex].m_byIndex;
				memcpy(m_atVidInfo[wIndex].m_abyAlias, tInfo.m_atVidInfo[wIndex].m_abyAlias,
					sizeof(tInfo.m_atVidInfo[wIndex].m_abyAlias));
			}
		}

		return *this;
	}

}TPAVidSourceInfo;

typedef struct tagTPAVidFeccInfo
{
	u16	m_wEpID;	// �᳡id

	BOOL32 m_bAllowFecc; // �Ƿ�����Զң
	u8 m_byVidno;		 // ��ǰԴ����
	TPAVidSourceInfo m_tVidSourceInfo;

	tagTPAVidFeccInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_bAllowFecc = FALSE;
		m_byVidno	 = 0;
		m_tVidSourceInfo.Clear();
	}

}TPAVidFeccInfo;

typedef struct tagTPAEpVidFeccInfo
{
	TPAEpPathKey m_tID;						// �Ѵ��ڣ���Ӧ��Э��� (TPAEpKeyID��  ��״��ums��������ʹ�ã�
	TPAVidFeccInfo m_tVidFeccInfo;			// Զң��Ϣ
	tagTPAEpVidFeccInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tID.Clear();
		m_tVidFeccInfo.Clear();
	}

}TPAEpVidFeccInfo;

typedef struct tagTPAConfEpVidFeccList
{
	u16		m_wNum;
	TPAEpVidFeccInfo m_atList[PA_REFRESH_LIST_THREE]; // �Ѵ��� ��Ӧ��Э���(PA_REFRESH_LIST_THREE) �᳡Զң��Ϣ [3]һ�����3��
	tagTPAConfEpVidFeccList()
	{
		Clear();
	}
	void Clear()
	{
		m_wNum = 0;
		for (u16 wIndex = 0; wIndex < PA_REFRESH_LIST_THREE; ++wIndex)
		{
			m_atList[wIndex].Clear();
		}
	}

}TPAConfEpVidFeccList;


typedef struct tagTPAConfVidFeccInfo
{
	EmPAModuleOperateType		m_emOpr;		//  �Ѵ��ڣ���Ӧ��Э���(EmModuleOperateType)�������
	BOOL32			m_bLastPack; 	// �Ƿ����һ��
	u16				m_wConfID;		// ����ID

	u16				m_wNum;		
	TPAVidFeccInfo	m_atVidFeccList[PA_REFRESH_LIST_THREE];
	tagTPAConfVidFeccInfo()
	{
		m_emOpr = emPAModuleOperateType_Add;
		m_wConfID = TP_INVALID_INDEX;
		m_wNum = 0;
		m_bLastPack = TRUE;
		memset(m_atVidFeccList, 0, sizeof(m_atVidFeccList));
	}
	tagTPAConfVidFeccInfo& operator = (tagTPAConfVidFeccInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_emOpr = tInfo.m_emOpr;
			m_bLastPack = tInfo.m_bLastPack;
			m_wConfID = tInfo.m_wConfID;
			m_wNum = tInfo.m_wNum;

			for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
			{
				m_atVidFeccList[wIndex].m_wEpID = tInfo.m_atVidFeccList[wIndex].m_wEpID;
				m_atVidFeccList[wIndex].m_bAllowFecc = tInfo.m_atVidFeccList[wIndex].m_bAllowFecc;
				m_atVidFeccList[wIndex].m_byVidno = tInfo.m_atVidFeccList[wIndex].m_byVidno;
				m_atVidFeccList[wIndex].m_tVidSourceInfo = tInfo.m_atVidFeccList[wIndex].m_tVidSourceInfo;
			}
		}
		return *this;
	}

}TPAConfVidFeccInfo;

#ifdef _ENABLE_QUANTUM_PROJECT_

#define PA_INVALID_HANDLE -1
#define	PA_MAX_MEDIAKEY_LEN 1024

typedef struct tagTPAQTMediaKeyInfo
{
	u32		m_dwHandle;
	u16		m_wIndex;
	//s8		m_szMediaKey[PA_MAX_MEDIAKEY_LEN+1];
	u8      m_szMediaKey1[PA_MAX_MEDIAKEY_LEN/4+1];
	u8      m_szMediaKey2[PA_MAX_MEDIAKEY_LEN/4+1];
	u8      m_szMediaKey3[PA_MAX_MEDIAKEY_LEN/4+1];
	u8      m_szMediaKey4[PA_MAX_MEDIAKEY_LEN/4+1];
	u32     m_dwKeyLen;			//������Կʵ�ʳ��� ����������Կ�����ص���Կ�д���'\0'
	EmPAConfEncFrequency m_emKeyFrequency;
	u32		m_dwQtFlag;

	tagTPAQTMediaKeyInfo()
	{
		memset(this, 0, sizeof(this));
	}

	void clear()
	{
		memset(this, 0, sizeof(struct tagTPAQTMediaKeyInfo));
		m_dwHandle = PA_INVALID_HANDLE;
		m_wIndex = PA_INVALID_HANDLE;
		m_emKeyFrequency = emPAConfEncFrequencyEveryConf;
		m_dwQtFlag = 0;
		m_dwKeyLen = 0;
	}

}TPAQTMediaKeyInfo;

#endif

#endif



