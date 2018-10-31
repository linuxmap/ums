
#ifndef _h_umscommonstruct_h__
#define _h_umscommonstruct_h__

#include "tpstruct.h"
#include "umsinnertype.h"
//#include "umsinnerstruct.h"
 
//0�Žڵ㱣�������л᳡�ڵ��1��ʼ���
#define UMS_CONF_EP_NUM TP_CONF_MAX_EPNUM + 1


#define CALLER_EP_INDEX		UMS_CONF_EP_NUM			//�ϼ�MCU�����������̶�	
#define MAX_CAPSET_NODE_NUM	(UMS_CONF_EP_NUM + 1) //���EP���� + �ϼ�UMS 

#define VALID_ALL_EPID(epid)	((epid) < TP_CONF_MAX_CNSNUM && (epid) >= 0)		//���еĻ᳡
#define VALID_CAPSET_EPID(epid)	((epid) < MAX_CAPSET_NODE_NUM && (epid) > 0)	//�����������Ľ�㣺�����᳡+�ϼ�UMS
#define VALID_LOCAL_EPID(epid)	((epid) < UMS_CONF_EP_NUM && (epid) > 0)		//�����᳡����

#define Is_Caller_Node(epid) ((epid) == CALLER_EP_INDEX)
#define Is_Local_Node(epid)	 ((epid) < UMS_CONF_EP_NUM && (epid) > 0)

#define MIDSCREENINDEX ((TP_MAX_STREAMNUM >> 2) + 1)

#define VALID_AUDMIX_INDEX(INDEX)  (INDEX < TP_CONF_MAX_AUDMIXNUM)
#define AUD_MIX_SND_TIMESAN	2000	//�����ش����ʱ��


#define MAX_CHANNEL_DS_NUM 128 
#define SEPCHAR '.'

#define FLOW_CTROL_ALL_ENC 0XFF
#define TP_MAX_CHAN_NUM    16

#define NUM_OF_CALLER_AND_TARGET  2

#define UMS_MCU_ROSTER_PARTLIST_NUM		32

#define UMS_MCU_PART_MAX_NUM		192

#define UMS_MCU_PART_NAME                  (s32)50
#define UMS_MCU_MAX_MIXERS_CONF				   (s32)16
#define UMS_MCU_MAX_VIEWS_CONF               (s32)4
#define UMS_MCU_MAX_GEOMETRYS_PER_VIEW           (s32)5
#define UMS_MCU_MAX_SUBFRAMES_PER_GEOMETRY       (s32)16
#define UMS_MCU_MAX_VIDEOSCHEMES_PER_VIEW        (s32)4


// mediatype
// ������Ƶ��·����������նˣ��������ն���Ƶ���м䣩
#define UMSDS_MEDIATYPE_VIDEO_LEFT			0x00000001
#define UMSDS_MEDIATYPE_VIDEO_MIDDLE		0x00000002
#define UMSDS_MEDIATYPE_VIDEO_RIGHT			0x00000003
// ������ƵС������·����������նˣ�
#define UMSDS_MEDIATYPE_VIDEO_SLEFT			0x00000004
#define UMSDS_MEDIATYPE_VIDEO_SMIDDLE		0x00000005
#define UMSDS_MEDIATYPE_VIDEO_SRIGHT		0x00000006
// ˫����Ƶһ·
#define UMSDS_MEDIATYPE_VIDEO_DUAL			0x00000007
// �ϳɳ�������Ƶ����
#define UMSDS_MEDIATYPE_VIDEO_VMP			0x00000008
// �����������Ƶ����
#define UMSDS_MEDIATYPE_VIDEO_BAS			0x00000009

#define UMSDS_MEDIATYPE_VIDEO_UNKNOW		0x000000FF


// ������Ƶ��·����������նˣ��������ն���Ƶ���м䣩
#define UMSDS_MEDIATYPE_AUDIO_LEFT			0x00000100
#define UMSDS_MEDIATYPE_AUDIO_MIDDLE		0x00000200
#define UMSDS_MEDIATYPE_AUDIO_RIGHT			0x00000300
// ��������Ƶһ·����������ն˵Ļ�����
#define UMSDS_MEDIATYPE_AUDIO_EPMIX			0x00000400
// ˫����Ƶһ·
#define UMSDS_MEDIATYPE_AUDIO_DUAL			0x00000500
// ����������Nģʽ
#define UMSDS_MEDIATYPE_AUDIO_EQPMIXN		0x00000600
// ����������N-1ģʽ
#define UMSDS_MEDIATYPE_AUDIO_EQPMIXN1		0x00000700
// �����������Ƶ����
#define UMSDS_MEDIATYPE_AUDIO_BAS			0x00000800

#define UMSDS_MEDIATYPE_AUDIO_UNKOWN		0x0000FF00


typedef struct tagTUmsHandle
{
	u32	handPaCall;
	u32 handAppCall;
	s32 handPaChan;
	u32 m_dwAdapteID;
	EmTpConfProtocol m_emProtocol;
	
	tagTUmsHandle()
	{
		Clear();
	}
	
	void Clear()
	{
		handPaCall = 0;
		handAppCall = 0;
		handPaChan = 0;
		m_dwAdapteID = 0;
		m_emProtocol = emTpSIP;
	}	
	
	void MakeAppHandle(u16 wConfID, u16 wEpID)
	{
		handAppCall = wConfID;
		handAppCall = handAppCall << 16;
		handAppCall |= wEpID;
	}
	
	u16 GetConfID() const	{ return u16(handAppCall >> 16); }
	u16 GetEpID()   const	{ return u16(handAppCall << 16 >> 16); }
	
}TUmsHandle;

typedef struct tagTRegCfg
{
	BOOL m_bUsed;
	TTPAlias	m_tAlias[TP_CONFTEMPGROUP_MAXNUM+1];	
	s8	m_achEPID[TP_CONFTEMPGROUP_MAXNUM + 1];
	s32	m_nTimeToLive;
	TTPTransAddr m_tLocalAddress; 
	TTPTransAddr m_tGKAddress;
    u32     m_dwQTId;

	tagTRegCfg()
	{
		Clear();
	}
	void Clear()
	{
		memset( m_tAlias , 0 , sizeof(m_tAlias) );
		memset( m_achEPID, 0, sizeof( m_achEPID) );
		m_tLocalAddress.Clear();
		m_tGKAddress.Clear();
		m_nTimeToLive = 60;
		m_bUsed = FALSE;
		m_dwQTId = 0;
	}

}TRegCfg;

//SIP Register����
typedef struct tagTUmsSipRegCfg
{
	BOOL   bUsed;   //�Ƿ�ע��
	u32_ip dwRegIP; //ע�������IP��ַ
	u16    wRegPort;//ע��������˿�
	s8     achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;
	
	s8		achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//��������

	TTPTransAddr	m_atAdaptAddr[TP_MAX_NUM_CONTACT_ADDR];
	s8		achCompileTm[TP_MAX_VERSION_LEN + 1];
	u32     m_dwQTId;
public:
	tagTUmsSipRegCfg(){ memset( this, 0, sizeof(struct tagTUmsSipRegCfg) ); }
}TUmsSipRegCfg;

//ע����
typedef struct tagTCnsRegRetResult
{
	EmTpCnsRegUms m_emReson;
	EmTpRegType	  m_emRegType;
	tagTCnsRegRetResult()
	{
		m_emRegType = em_sip_reg;
		m_emReson = tp_CnsRegRet_Unknow;
	}
}TCnsRegRetResult;



typedef struct tagTPollInfoNtf
{
	TTPAlias		m_tAlias;
	u32             m_nScreenNum;
	tagTPollInfoNtf()
	{
		memset( this, 0, sizeof(tagTPollInfoNtf) );
	}
}TPollInfoNtf;





//�������ڼ�������
//ID��ʽ 1.1.1.
typedef struct tagTEpPathKey
{
	s8	m_szEpID[TP_MAX_EPID_LEN+1];
	tagTEpPathKey()
	{
		Clear();
	}
	void Clear()
	{
		m_szEpID[0] = '\0';
	}
	
	BOOL32 IsRoot() const
	{
		if (0 == memcmp(m_szEpID, "root", 4))
		{
			return TRUE;
		}
		return FALSE;
	}

	void SetKey(const s8* pszKey)
	{
		strncpy(m_szEpID, pszKey, TP_MAX_EPID_LEN);
		m_szEpID[TP_MAX_EPID_LEN] = '\0';
	}
	
	BOOL32 IsValid() const
	{
		u8 byLast = SEPCHAR;
		u16 wIndex = 0;
		
		if (IsRoot())
		{
			return TRUE;
		}
		while (m_szEpID[wIndex] != '\0')
		{
			if (m_szEpID[wIndex] != SEPCHAR && (m_szEpID[wIndex] < '0' || m_szEpID[wIndex] > '9'))
			{
				return FALSE;
			}
			
			if (m_szEpID[wIndex] == SEPCHAR && m_szEpID[wIndex] == byLast)
			{
				return FALSE;
			}
			
			byLast = m_szEpID[wIndex];
			
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
		s8	szEpID[TP_MAX_EPID_LEN+1];
		memcpy(szEpID, m_szEpID, TP_MAX_EPID_LEN+1);
		
		s8* pChar = szEpID;
		u16 wIndex = 0;
		while (*(pChar+wIndex) != '\0')
		{
			if (*(pChar+wIndex) == SEPCHAR)
			{
				if (wIndex == 0)
				{
					return FALSE;
				}
				*(pChar+wIndex) = '\0';
				awEpID[wRealNum] = atoi(pChar);
				++wRealNum;
				if (wRealNum >= wMaxNum)
				{
					return FALSE;
				}
				pChar = pChar+wIndex+1;
				wIndex = 0;
				continue;
			}
			wIndex++;
		}
		return TRUE;
	}
}TEpPathKey;

typedef struct tagTEpKey
{
	u16 m_wEpID;			//�ϼ�֪ͨ�¼�ʱΪ�¼�ID
							//�¼�֪ͨ�ϼ�ʱΪ����ID���¼�ID
//	TEpPathKey m_tKey;
	tagTEpKey()
	{
		m_wEpID = TP_INVALID_INDEX;
//		m_tKey.Clear();
	}
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
//		m_tKey.Clear();
	}

}TEpKey;

typedef struct tagTEpKeyEx
{
	u16 m_wEpID;			//�ϼ�֪ͨ�¼�ʱΪ�¼�ID, �¼�֪ͨ�ϼ�ʱΪ����ID���¼�ID
	s8  m_achReserve[TP_MAX_EPID_LEN+1];

	tagTEpKeyEx()
	{
		Clear();
	}

	void AddKey(s8 ch)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_EPID_LEN+1; wIndex++)
		{
			if (m_achReserve[wIndex] == '\0')
			{
				m_achReserve[wIndex] = ch;
				m_achReserve[wIndex+1] = '\0';
				return;
			}
		}
		return;
	}

	BOOL32 IsKeyExist(s8 ch)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_EPID_LEN+1; wIndex++)
		{
			if (m_achReserve[wIndex] == '\0')
			{
				break;
			}
			else
			{
				if (m_achReserve[wIndex] == ch)
				{
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_achReserve[0] = '\0';
	}
	
}TEpKeyEx;


typedef struct tagTCheckIFrameBase
{
	u16 m_wConfID;
	u16 m_wExpires;					//��ʱʱ��
	EmTpIFrameCheckType m_emType;	//��������
	u32_ip m_dwIP;				//����IP
	u16 m_wPort;				//�����˿�

	tagTCheckIFrameBase()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = 0;
		m_wExpires = 0;
		
		m_emType = TP_IFrameCheck_Speaker;

		m_dwIP = 0;
		m_wPort = 0;
	}
	
}TCheckIFrameBase;


typedef struct tagTIFrameBySrc
{
	u16	m_wChanIndex;					//����
	u16	m_wNewSpeakerID;				//�µķ�����EpID

	u32_ip	m_dwOldIP;		//m_wListenPort��m_wOldPort��m_wNewPort�հ�
	u32_ip	m_dwNewIP;		//��ǰһֱ��m_wOldPort�յ��İ�Ϊ��Ч����
	u16	m_wOldPort;			//��ĳһʱ�̣���m_wNewPort�����İ�Ϊ�ؼ�֡ʱ
	u16	m_wNewPort;			//��ȡm_wNewPortΪ��Ч�������ϳ�m_wOldPort�����İ�

	BOOL32 m_bUsedNew;
	

	void Clear()
	{
		m_wChanIndex = 0;
		m_wNewSpeakerID = 0;

		m_dwOldIP = 0;
		m_dwNewIP = 0;
		m_wOldPort = 0;
		m_wNewPort = 0;
		m_bUsedNew = FALSE;
	}
	
}TIFrameBySrc;

typedef struct tagTIFrameTwoRcvPort //NewPort��OldPortͬʱ�����������ʼʱNewPort�յ���������Ч
{									//��NewPort��⵽�ؼ�֡ʱ����Ч����ʱ��OldPort��Ϊ��Ч
									//����ʱ����NewPort���ؼ�֡�����ó�ʱʱ�䣬OldPort���ü��

	u16 m_wNewPort;					//�����˿�
	u16 m_wOldPort;					//�����˿�

	BOOL32 m_bTrans;					//�Ƿ�ת��
	
	u16	m_wChanIndex;					//����
	u16	m_wPollEp;						//��ѯĿ��
	

	void Clear()
	{
		m_wNewPort= 0;
		m_wOldPort= 0;

		m_wChanIndex = 0;
		m_wPollEp = 0;
		
		m_bTrans = FALSE;;
	}	
}TIFrameTwoRcvPort;

typedef struct tagTIFrameSndBySrc
{								
							//��m_wPort����m_wDstPort��������������m_wCheckPort�յ��ؼ�֡�󣬲�ת����ȥ
	u32_ip m_dwCheckIp;		//m_wCheckPort = TIFrameBySrc.m_wNewPort�� ��TIFrameBySrc���ʹ��
	u16 m_wCheckPort;

	u32_ip m_dwDstIp;
	u16 m_wDstPort;

	u16 m_wRcvPort;		//ȡ�ý��ռ��Ķ�
	

	void Clear()
	{
		m_dwCheckIp= 0;
		m_wCheckPort = 0;

		m_dwDstIp = 0;
		m_wDstPort = 0;;
	}	
}TIFrameSndBySrc;

typedef struct tagTUmsDsData
{
	u32				m_dwEqpNode;

	TTPTransAddr m_tRcvFromAddr;
	TTPTransAddr m_tSndToAddr;
	TTPTransAddr m_tMapedAddr;

	BOOL32		m_bNeedModifySrc;

	EmSwitchType    m_emSwitchType;

	u32			m_dwSrcMediaType; // �������ó�Ա���������ã��������������ͣ�����src��ȷ������m_tRcvFromAddr�����յ��������ͣ�
	
	tagTUmsDsData()
	{
		memset(this, 0, sizeof(tagTUmsDsData));
	}

	void SetVideo(u16 wSreen)
	{
		if (0 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_LEFT;
		}
		else if (1 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_MIDDLE;
		}
		else if (2 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_RIGHT;
		}
		else
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_UNKNOW;
		}
	}

	void SetSmallVideo(u16 wSreen)
	{
		if (0 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_SLEFT;
		}
		else if (1 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_SMIDDLE;
		}
		else if (2 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_SRIGHT;
		}
		else
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_UNKNOW;
		}
	}

	void SetSingleVideo()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_MIDDLE;
	}

	void SetDualVideo()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_DUAL;
	}

	void SetVmpVideo()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_VMP;
	}
	
	void SetBasVideo()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_BAS;
	}

	void SetUnknowVideo()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_VIDEO_UNKNOW;
	}

	void SetAudio(u16 wSreen)
	{
		if (0 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_LEFT;
		}
		else if (1 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_MIDDLE;
		}
		else if (2 == wSreen)
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_RIGHT;
		}
		else
		{
			m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_UNKOWN;
		}
	}

	void SetEPMixAudio()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_EPMIX;
	}

	void SetSingleAudio()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_MIDDLE;
	}

	void SetDualAudio()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_DUAL;
	}

	void SetEQPMixNVideo()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_EQPMIXN;
	}

	void SetEQPMixN1Video()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_EQPMIXN1;
	}

	void SetBasAudio()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_BAS;
	}
	void SetUnknowAudio()
	{
		m_dwSrcMediaType = UMSDS_MEDIATYPE_AUDIO_UNKOWN;
	}
	tagTUmsDsData& operator = (const tagTUmsDsData& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dwEqpNode = tRhs.m_dwEqpNode;
		this->m_tRcvFromAddr = tRhs.m_tRcvFromAddr;
		this->m_tSndToAddr = tRhs.m_tSndToAddr;
		this->m_tMapedAddr = tRhs.m_tMapedAddr;
		this->m_bNeedModifySrc = tRhs.m_bNeedModifySrc;
		this->m_emSwitchType = tRhs.m_emSwitchType;
		this->m_dwSrcMediaType = tRhs.m_dwSrcMediaType;
		return *this;
	}

	BOOL32 operator == (tagTUmsDsData& tRsData)
	{
		return (m_tRcvFromAddr == tRsData.m_tRcvFromAddr) && (m_tSndToAddr == tRsData.m_tSndToAddr)
			&& (m_emSwitchType == tRsData.m_emSwitchType);
	}
	BOOL32 operator < (tagTUmsDsData& tRsData)
	{
		if (m_tRcvFromAddr.m_dwIP > tRsData.m_tRcvFromAddr.m_dwIP)
		{
			return FALSE;
		}
		else if (m_tRcvFromAddr.m_dwIP == tRsData.m_tRcvFromAddr.m_dwIP)
		{
			if (m_tRcvFromAddr.m_wPort > tRsData.m_tRcvFromAddr.m_wPort)
			{
				return FALSE;
			}
			else if (m_tRcvFromAddr.m_wPort == tRsData.m_tRcvFromAddr.m_wPort)
			{
				if (m_tSndToAddr.m_dwIP > tRsData.m_tSndToAddr.m_dwIP)
				{
					return FALSE;
				}
				else if (m_tSndToAddr.m_dwIP == tRsData.m_tSndToAddr.m_dwIP)
				{
					if (m_tSndToAddr.m_wPort > tRsData.m_tSndToAddr.m_wPort)
					{
						return FALSE;
					}
					else if (m_tSndToAddr.m_wPort == tRsData.m_tSndToAddr.m_wPort)
					{
						return FALSE;
					}
				}
			}
		}
		return TRUE;
	}
	BOOL32 operator > (tagTUmsDsData& tRsData)
	{
		if (m_tRcvFromAddr.m_dwIP < tRsData.m_tRcvFromAddr.m_dwIP)
		{
			return FALSE;
		}
		else if (m_tRcvFromAddr.m_dwIP == tRsData.m_tRcvFromAddr.m_dwIP)
		{
			if (m_tRcvFromAddr.m_wPort < tRsData.m_tRcvFromAddr.m_wPort)
			{
				return FALSE;
			}
			else if (m_tRcvFromAddr.m_wPort == tRsData.m_tRcvFromAddr.m_wPort)
			{
				if (m_tSndToAddr.m_dwIP < tRsData.m_tSndToAddr.m_dwIP)
				{
					return FALSE;
				}
				else if (m_tSndToAddr.m_dwIP == tRsData.m_tSndToAddr.m_dwIP)
				{
					if (m_tSndToAddr.m_wPort < tRsData.m_tSndToAddr.m_wPort)
					{
						return FALSE;
					}
					else if (m_tSndToAddr.m_wPort == tRsData.m_tSndToAddr.m_wPort)
					{
						return FALSE;
					}
				}
			}
		}
		return TRUE;
	}
}TUmsDsData;


typedef struct tagTUmsNetBuf
{
	TTPTransAddr m_wSndAddr;			//����RTP�����ն˺ͷ���RTCP�����Ͷ˵ķ��Ͷ˿�
	TTPTransAddr m_tRcvRtpAddr;			//netbuf����RTP�Ķ˿�
	TTPTransAddr m_tRcvRtcpAddr;		//netbuf����RTCP�Ķ˿�
	TTPTransAddr m_tRmtRtcpAddr;		//netbuf����RTCP��Զ�˶˿�
	
	tagTUmsNetBuf()
	{
		memset(this, 0, sizeof(tagTUmsNetBuf));
	}
	void Clear() {	memset(this, 0, sizeof(tagTUmsNetBuf));	}
}TUmsNetBuf;

//�¼����ϼ����½����Ϣ
typedef struct tagTConfNodeCallUpdateTr
{
	TEpPathKey m_tID;						//��״��
	u16		 m_wEpID;						//���¼��е�ID
	
	EmTPEndpointType	m_emEpType;			//�������
	EmTpVendorID		m_emVendorID;		//����ID
	
	EmUmsConfNodeState	m_emCallState;		//����״̬
	EmCnsCallReason		m_emCallReason; 
	
	TTpCallAddr m_tCalledAddr;				//���д˽��ʱ�ĵ�ַ
	TTPAlias m_tConfName;					//�᳡��
	
	EmTPSipLevel	m_emLevel;				//�᳡�ȼ�	����
	
	EmTPRcvAlignType m_enRcvAlignType;

	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	//�����������ͨ�� 0,1,2,3,4���򣬲��ܱ��᳡��ʵ�Ǽ���������
	u16 m_wSpearkIndex;			//������ͨ������
	u16 m_wDualIndex;			//����˫��ͨ������

	tagTConfNodeCallUpdateTr()
	{	
		Clear();
	}
	
	void Clear()
	{
		m_tID.Clear();
		
		m_emEpType = emTPEndpointTypeCNS;
		m_emVendorID = EmTp_vendor_KEDA;
		
		m_emCallState = ums_UmsConfNodeState_unused;
		m_emCallReason = EmCnsCallReason_Local;
		
		m_tCalledAddr.Clear();
		m_tConfName.Clear();
		m_emLevel = emTPSipProvince;
		m_enRcvAlignType = emTPRcvAlignTypeMidAlign;
		
		m_bMute = FALSE;
		m_bQuiet = FALSE;

		m_wSpearkIndex = TP_INVALID_INDEX;
		m_wDualIndex = TP_INVALID_INDEX;
	}
}TConfNodeCallUpdateTr;

typedef struct tagTConfNodeCallUpdateTrList
{
	u16		m_wNum;
	TConfNodeCallUpdateTr m_atList[TP_REFRESH_LIST_THREE];
	tagTConfNodeCallUpdateTrList()
	{
		m_wNum = 0;
	}
}TConfNodeCallUpdateTrList;

//�¼����ϼ����½����Ϣ
typedef struct tagTConfNodeChanUpdateTr
{
	TEpKey	tID;						//��״��
	u16			wEpID;					//���¼��е�ID
	BOOL32		bChanOpen;				//ͨ���Ƿ��
	BOOL32		bSmallOpenEnc;			//С����
	BOOL32		bSmallOpenDec;			//С����
	//B2����
	u16	wVidSnd;		
	u16	wVidRcv;	
	u16	wAudSnd;	
	u16	wAudRcv;
	
	TUmsVidFormat	tVidRcv;
	TUmsAudFormat	tAudRcv;
	
	TUmsVidFormat	tVidSnd;
	TUmsAudFormat	tAudSnd;

	TUmsVidFormat	tDualVidRcv;		//��������
	TUmsAudFormat	tDualAudRcv;
	
	TUmsVidFormat	tDualVidSnd;
	TUmsAudFormat	tDualAudSnd;

	//�غ�������������˳������Ƶ���� ��Ƶ���� ˫����Ƶ���� ˫����Ƶ���� ��Ƶ���� ��Ƶ���� ˫����Ƶ���� ˫����Ƶ����
	u16 awPd[TP_MAX_CHAN_NUM]; 

	BOOL32		bInPoll;					//�Ƿ�����ѯ�б���

	tagTConfNodeChanUpdateTr()
	{	
		Clear();
	}
	
	void Clear()
	{
		tID.Clear();
		bChanOpen = FALSE;
		bSmallOpenEnc = FALSE;
		bSmallOpenDec = FALSE;
		bInPoll = FALSE;

		wVidRcv = 0;
		wVidSnd = 0;
		wAudRcv = 0;
		wAudSnd = 0;
		
		tVidRcv.Clear();
		tVidSnd.Clear();
		tAudRcv.Clear();
		tAudSnd.Clear();
		
		tDualVidRcv.Clear();
		tDualVidSnd.Clear();
		tDualAudRcv.Clear();
		tDualAudSnd.Clear();

		u16 wIndex = 0;
		for (wIndex = 0; wIndex < (TP_MAX_CHAN_NUM / 2); wIndex++)
		{
			awPd[wIndex] = MEDIA_TYPE_H264;
		}
		for (wIndex; wIndex < TP_MAX_CHAN_NUM; wIndex++)
		{
			awPd[wIndex] = MEDIA_TYPE_AACLD;
		}
	}
	void SetVidSndNum(u16 wNum)
	{
		if (wNum > TP_MAX_STREAMNUM)		
			return;
		wVidSnd = wNum;
	}
	void SetVidRcvNum(u16 wNum)
	{
		if (wNum > TP_MAX_STREAMNUM)		
			return;
		wVidRcv = wNum;
	}
	void SetAudSndNum(u16 wNum)
	{
		if (wNum > TP_MAX_STREAMNUM)		
			return;
		wAudSnd = wNum;
	}
	void SetAudRcvNum(u16 wNum)
	{
		if (wNum > TP_MAX_STREAMNUM)		
			return;
		wAudRcv = wNum;
	}
	
}TConfNodeChanUpdateTr;

typedef struct tagTConfNodeChanUpdateTrList
{
	u16		m_wNum;
	TConfNodeChanUpdateTr m_atList[TP_REFRESH_LIST_THREE];
	tagTConfNodeChanUpdateTrList()
	{
		m_wNum = 0;
	}
}TConfNodeChanUpdateTrList;



typedef struct tagTConfNodeDelTrList
{
	u16		m_wNum;
	TEpKey  m_atList[TP_REFRESH_LIST_THREE];
	tagTConfNodeDelTrList()
	{
		m_wNum = 0;
	}
}TConfNodeDelTrList;

typedef struct tagTSpeakerCapTr
{
	BOOL32 m_bIsSpeaker;	//�Զ��Ƿ�Ϊ�����ˣ������UMS���ʾ�������Ƿ��ڶԶ���
	u16 m_wSpeakerID;		//�ڶԶ��е�EpID
	u16	m_wVidSnd;
	u16 m_wAudSnd;
	TTPAlias m_tEpAlias;	//���Ի᳡����
	u16 m_wSpeakerIndex;	//�᳡�ڵķ���������
	tagTSpeakerCapTr()
	{
		m_bIsSpeaker = FALSE;
		m_wSpeakerID = TP_INVALID_INDEX;
		m_wVidSnd = 0;
		m_wAudSnd = 0;
		m_wSpeakerIndex = 0;
	}
}TSpeakerCapTr;

typedef struct tagTPollCmdTr
{
	TTPMediaTransAddr m_tAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	u16 m_wBitrate;				//��ѯ����
	u16	m_wInterval;			//��ѯʱ����
	tagTPollCmdTr()
	{
		m_wBitrate = 0;
		m_wInterval = 0;
	}
}TPollCmdTr;

typedef struct tagTPollAckTr
{
	u16 m_wReason;
	TTPMediaTransAddr m_tAddr[TP_MAX_STREAMNUM];
	tagTPollAckTr()
	{
		m_wReason = TP_RET_OK;
	}
}TPollAckTr;

//m_abOpen��ʾ�Ƿ���Ҫ�ص�����Ļ��Դ
//1. ����Ҫ�ص���߻��ұ���ʱ��ֱ�ӽ���߻��ұߵ�����Ƶ����ص�����
//2. ����Ҫ�ص��м���ʱ������Ҫ���������жϣ�
//      ���m_bViewSpeakerΪ�棬�򽫷�����ϯ���м�ͨ���ص����������������м�ͨ���ص�
//      ����m_bViewSpeakerΪ��, ��ص��м�����������ͼ��
//3. ��������ȫ���ص�ʱ��
//		����ǵ������򽫵���������ͼ�����м�ͨ���ص�
//		�������������������������Ƶ�Լ�����ȫ���ص�
typedef struct tagTViewCmdTr
{
	u16 m_wEpID;					//Ŀ��ID
	u16 m_wIndex;					//λ������
	u32 m_dwType;					//ҵ������	//��Ӧpa��m_dwType�ֶΣ����ֶ�B1��û��ʹ��
	u16	m_wSrcScreenIndex;			//Դ���ţ�B1û��ʹ�ã�����Э��ջ����Ӵ��ֶ�
	

	TTPMediaTransAddr m_atAddr[TP_MAX_STREAMNUM];	//���յ�ַ	
	BOOL32			  m_abOpen[TP_MAX_STREAMNUM];	

	//����B2����
	TTPMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//��Ƶ���յ�ַ	
	TTPMediaTransAddr m_tMixAddr;						//�������յ�ַ

	BOOL32			  m_bViewSpeaker;					//�Ƿ��ǽ���������ϯ	
	BOOL32			  m_bNeedBas;						//�Ƿ���Ҫ����
	tagTViewCmdTr()
	{
		memset(m_abOpen, 0, sizeof(m_abOpen));
		m_wEpID = TP_INVALID_INDEX;
		m_wSrcScreenIndex = TP_INVALID_INDEX;
		m_bViewSpeaker = FALSE;
		m_bNeedBas = FALSE;
	}

	BOOL32& MidOpen()			{ return m_abOpen[MIDSCREENINDEX]; }
}TViewCmdTr;


typedef struct tagTViewAckTr
{
	EmTPViewResult m_emRes;
	u16 m_wIndex;

	TTPMediaTransAddr m_atAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	BOOL32		 m_abOpen[TP_MAX_STREAMNUM];
	
	//����B2����
	TTPMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//��Ƶ���յ�ַ	
	TTPMediaTransAddr m_tMixAddr;						//�������յ�ַ
	tagTViewAckTr()
	{
		m_emRes = emViewSucceed;
		
		memset(m_abOpen, 0, sizeof(m_abOpen));
	}
	TTPMediaTransAddr& MidAddr() { return m_atAddr[MIDSCREENINDEX]; }
	BOOL32& MidOpen()			{ return m_abOpen[MIDSCREENINDEX]; }
}TViewAckTr;


typedef struct tagTCascadeOpenChanCmd
{
	u16 m_wEpID;
	
	TTPMediaTransAddr m_atVidAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TTPMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//���յ�ַ
//	TTPMediaTransAddr m_atSmallAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TTPMediaTransAddr m_tMixAudAddr;
//	TTPMediaTransAddr m_tSpeakerVmpVid;
	TTPMediaTransAddr m_tDisSingleVid;
	TTPMediaTransAddr m_tDisSingleAud;

	BOOL32		 m_abVidOpen[TP_MAX_STREAMNUM];
//	BOOL32		 m_abSmallOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abAudOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_bMixAudOpen;
//	BOOL32		 m_bSpeakerVmpVid;
	BOOL32		 m_bDisSingleVid;
	BOOL32		 m_bDisSingleAud;
	
	tagTCascadeOpenChanCmd()
	{
		m_wEpID = TP_INVALID_INDEX;

		memset(m_abVidOpen, FALSE, sizeof(m_abVidOpen));
//		memset(m_abSmallOpen, FALSE, sizeof(m_abSmallOpen));
		memset(m_abAudOpen, FALSE, sizeof(m_abVidOpen));
		m_bMixAudOpen = FALSE;
//		m_bSpeakerVmpVid = FALSE;
		m_bDisSingleVid = FALSE;
		m_bDisSingleAud = FALSE;
	}
	
}TCascadeOpenChanCmd;

typedef struct tagTCascadeOpenChanAck
{
	u16 m_wEpID;
	
	TTPMediaTransAddr m_atVidAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TTPMediaTransAddr m_atAudAddr[TP_MAX_STREAMNUM];	//���յ�ַ
//	TTPMediaTransAddr m_atSmallAddr[TP_MAX_STREAMNUM];	//���յ�ַ
	TTPMediaTransAddr m_tMixAudAddr;
//	TTPMediaTransAddr m_tSpeakerVmpVid;
	TTPMediaTransAddr m_tDisSingleVid;
	TTPMediaTransAddr m_tDisSingleAud;

	BOOL32		 m_abVidOpen[TP_MAX_STREAMNUM];
//	BOOL32		 m_abSmallOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_abAudOpen[TP_MAX_STREAMNUM];
	BOOL32		 m_bMixAudOpen;
//	BOOL32		 m_bSpeakerVmpVid;
	BOOL32		 m_bDisSingleVid;
	BOOL32		 m_bDisSingleAud;
	
	tagTCascadeOpenChanAck()
	{
		m_wEpID = TP_INVALID_INDEX;

		memset(m_abVidOpen, FALSE, sizeof(m_abVidOpen));
//		memset(m_abSmallOpen, FALSE, sizeof(m_abSmallOpen));
		memset(m_abAudOpen, FALSE, sizeof(m_abVidOpen));
		m_bMixAudOpen = FALSE;
//		m_bSpeakerVmpVid = FALSE;
		m_bDisSingleVid = FALSE;
		m_bDisSingleAud = FALSE;
	}
	
}TCascadeOpenChanAck;


typedef struct tagTAudMixEpCmdTr
{
	u16	m_wEpID;
	u16 m_wLocalID;					//�ϼ�����������
	TTPTransAddr m_tRtpAddr;		//�ϼ�����EP����
	TTPTransAddr m_tBackRtpAddr;	//������������BACKRTP��ַ
	tagTAudMixEpCmdTr()
	{
		m_tRtpAddr.Clear();
		m_tBackRtpAddr.Clear();
		m_wEpID = TP_INVALID_INDEX;
		m_wLocalID = TP_INVALID_INDEX;
	}
}TAudMixEpCmdTr;

typedef struct tagTAudMixEpAckTr
{
	u16 m_wReason;				//ԭ��
	u16 m_wLocalID;
	TTPTransAddr m_tRtpAddr;		//�����ϼ������������
	TTPTransAddr m_tBackRtpAddr;	//EP������backrtp��ַ
	tagTAudMixEpAckTr()
	{
		m_wReason = TP_RET_OK;
		m_tRtpAddr.Clear();
		m_tBackRtpAddr.Clear();
		m_wLocalID = TP_INVALID_INDEX;
	}
}TAudMixEpAckTr;



typedef struct tagTChairInfoTr
{	
	u16 m_wSpeakerIndex;
	tagTChairInfoTr()
	{
		Clear();
	}
	void Clear()	{ m_wSpeakerIndex = TP_INVALID_INDEX; }
	u16 GetSpeaker(){ return u16(m_wSpeakerIndex < TP_MAX_STREAMNUM ? m_wSpeakerIndex : (MIDSCREENINDEX));	}
}TChairInfoTr;


typedef struct tagTMuteRmtEpCmd
{
	BOOL32 m_bMute;
	u16	   m_wEpID;
	tagTMuteRmtEpCmd()
	{
		m_bMute = FALSE;
		m_wEpID = TP_INVALID_INDEX;
	}
}TMuteRmtEpCmd;

typedef struct tagTMuteRmtEpInd
{
	BOOL32 m_bMute;
	TEpKey m_tKeyID;
	tagTMuteRmtEpInd()
	{
		Clear();
	}

	void Clear()
	{
		m_bMute = FALSE;
	}
}TMuteRmtEpInd;


typedef struct tagTQuietRmtEpCmd
{
	BOOL32 m_bQuiet;
	u16	   m_wEpID;
	tagTQuietRmtEpCmd()
	{
		Clear();
	}
	void Clear()
	{
		m_bQuiet = FALSE;
		m_wEpID = TP_INVALID_INDEX;
	}

}TQuietRmtEpCmd;

typedef struct tagTQuietRmtEpInd
{
	BOOL32 m_bQuiet;
	TEpKey m_tKeyID;
	tagTQuietRmtEpInd()
	{
		Clear();
	}
	void Clear()
	{
		m_bQuiet = FALSE;
	}
}TQuietRmtEpInd;


typedef struct tagTDropEpCmd
{
	u16 m_wEpID;
	BOOL32 m_bDel;
	tagTDropEpCmd()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_bDel = FALSE;
	}
}TDropEpCmd;



typedef struct tagTTvMonitorCmdTr
{
	u16					m_wIndex;
//	TEpPathKey			m_tKey;
	u16					m_wEpID;
	u16                 m_wScreenNum;
	TTPMediaTransAddr	m_tVidAddr;
	TTPMediaTransAddr	m_tAudAddr;
	tagTTvMonitorCmdTr()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNum = TP_INVALID_INDEX;
//		m_tKey.Clear();
		m_tVidAddr.Clear();
		m_tAudAddr.Clear();
	}
}TTvMonitorCmdTr;

typedef struct tagTTvMonitorIndTr
{
	BOOL32				m_bAccept;
	u16					m_wIndex;
//	TEpPathKey			m_tKey;
	u16					m_wEpID;
	u16                 m_wScreenNum;
	TTPMediaTransAddr	m_tVidAddr;
	TTPMediaTransAddr	m_tAudAddr;
	tagTTvMonitorIndTr()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNum = TP_INVALID_INDEX;
//		m_tKey.Clear();
		m_tVidAddr.Clear();
		m_tAudAddr.Clear();
	}
}TTvMonitorIndTr;


typedef struct tagTAskKeyByScreenTr
{
	u16		m_wEpID;
	u16		m_wScreenIndex;
	BOOL32	m_bReqBySys;			//�Ƿ���ϵͳ����

	u32		m_dwAskType;            //��������  �����ˡ���ϯ��ѡ����ѯ�����ۡ�¼��������ǽ
	u32		m_dwRervse1;            //����
	u32		m_dwRervse2;            //����

	tagTAskKeyByScreenTr()
	{
		memset(this, 0, sizeof(tagTAskKeyByScreenTr));
	}
}TAskKeyByScreenTr;


//flowcontrol
typedef struct tagTFlowControl
{
	TEpKey	m_tEpKey;
	u16	m_wEncNo;	//-1���������
	u16	m_wBand;
	u32 m_dwOpr;
	tagTFlowControl()
	{
		m_tEpKey.Clear();
		m_wEncNo = FLOW_CTROL_ALL_ENC;
		m_wBand = 0;
		m_dwOpr = 0;
	}
}TFlowControl;

//�������ڼ�������

//CallInfo : ����Ŀ����Ϣ
typedef struct tagTUmsCallInfo
{
	EmTPEndpointType	m_emSrcEpType;			//���ж˵�����
	EmTpCallMode		m_emTpCallType;			// ��������:JOIN|CREATE|INVITE
	EmTpConfProtocol	m_emTpProtocol;         // ͨ��Э��Э��
	EmTpVendorID		m_emVendorID;			//����ID
	
	u16					m_wBitRate;				//��������
	EmTPSipLevel		m_emLevel;				//�᳡�ȼ�

	TTpCallAddr			m_tDestAddr;			//Ŀ���ַ
	TTpCallAddr			m_tSrcAddr;				//Դ��ַ
	u8					m_byVer;				//EP�汾��

	BOOL32              m_bIsCreatConf;

	s8					m_acPrdutID[TP_UMS_PRDUT_ID];

	TTPEncrypt          m_tEncrypt; // ��������

	BOOL32				m_bIsCasecadeMcuOn; // �Ƿ�Я������mcu����

	tagTUmsCallInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_emSrcEpType = emTPEndpointTypeUMS;
		m_emTpCallType = emTpJoin;
		m_emTpProtocol = emTpSIP;
		m_emVendorID = EmTp_vendor_KEDA;
		m_wBitRate = TP_UMS_CHAN_BITRATE;	
		m_emLevel = emTPSipCounty;
		m_tDestAddr.Clear();
		m_tSrcAddr.Clear();
		m_byVer = 0;
		m_bIsCreatConf = FALSE;
		memset(m_acPrdutID, 0, sizeof(m_acPrdutID));
		m_tEncrypt.Clear();
		m_bIsCasecadeMcuOn = FALSE;
	}
}TUmsCallInfo;

//ͨ������
typedef struct tagTChanNetPara
{
//	u16					m_wRealBitRate;	//UMS����֮�������
	BOOL32				m_bIsChanOn;	//�Ƿ��
	TTPMediaTransAddr	m_tChanAddr;	//��ַ
	s32					m_tPAHandle;
	
	tagTChanNetPara()
	{
		m_tPAHandle = TP_INVALID_INDEX;
		m_bIsChanOn = FALSE;
//		m_wRealBitRate = 0;
	}
	
	void Clear()
	{
		m_tPAHandle = TP_INVALID_INDEX;
//		m_wRealBitRate = 0;
		m_bIsChanOn = FALSE;
		m_tChanAddr.Clear();
	}	
}TChanNetPara;


typedef struct tagTUmsVidCapParam
{
	TUmsVidFormat m_tHp;
	TUmsVidFormat m_tBp;
	
	u16     m_wDynamicPayload;
	tagTUmsVidCapParam()
	{
		Clear();
	}
	void Clear()
	{
		m_tHp.m_emQualityLvl = emTPH264HP;
		m_tHp.m_emFormat = emTPVH264;
		m_tHp.m_emRes = emTPVResEnd;
		m_tHp.m_wFrameRate = 0;
		
		m_tBp.m_emQualityLvl = emTPH264BP;
		m_tBp.m_emFormat = emTPVH264;
		m_tBp.m_emRes = emTPVResEnd;
		m_tBp.m_wFrameRate = 0;

		m_wDynamicPayload = MEDIA_TYPE_H264;
	}

	BOOL32 IsMulCap()	const { return m_tHp.IsValid() && m_tBp.IsValid(); }
	BOOL32 IsValidCap()	const { return m_tHp.IsValid() || m_tBp.IsValid(); }
}TUmsVidCapParam;

typedef struct tagTUmsAudCap
{
	u16					m_wAudFmtNum;	//��Ƶ��ʽ����
	TUmsAudFormat		m_atAudFmt[TP_CONF_MAX_AUD_FMT_NUM];
	u16					m_wBitrate;

	tagTUmsAudCap()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(m_atAudFmt, 0, sizeof(m_atAudFmt));
		for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUD_FMT_NUM; wIndex ++)
		{
			m_atAudFmt[wIndex].m_emFormat = emTPAEnd;
		}
		m_wBitrate = 0;
	}
}TUmsAudCap;

//�᳡���������
typedef struct tagTUmsNodeCapset 
{	
	u16	m_wVidEncNum;	
	u16	m_wVidDecNum;	
	u16	m_wAudEncNum;	
	u16	m_wAudDecNum;
	TChanNetPara m_atVidEnc[TP_MAX_STREAMNUM];	//Զ����Ƶ����ͨ��
	TChanNetPara m_atVidDec[TP_MAX_STREAMNUM];	//Զ����Ƶ����ͨ��
	TChanNetPara m_atAudEnc[TP_MAX_STREAMNUM];	//Զ����Ƶ����ͨ��
	TChanNetPara m_atAudDec[TP_MAX_STREAMNUM];	//Զ����Ƶ����ͨ��
		
	TChanNetPara m_atSmallVidEnc[TP_MAX_STREAMNUM];	//Զ��С��������ͨ��
	TChanNetPara m_atSmallVidDec[TP_MAX_STREAMNUM];	//Զ��С��������ͨ��

	TChanNetPara m_tAudMixEnc;
	TChanNetPara m_tAudMixDec;
		
// 	EmTPEncryptType  m_byEncryptBits;			//��������
// 	TTpEncryptKey	 m_tEnc;
// 	u16  m_byFECBits;							//FEC����

	TTPEncrypt  m_tEncrypt;  // ��������

//	u16 m_wMaxBitRate;							//kbps�� Node֧�ֵ��ܴ���
	
	TUmsVidCapParam	m_tVidRcvCap;
	TUmsVidCapParam	m_tVidSndCap;

	TUmsAudCap m_tAudRcvCap;					//��Ƶ����
	TUmsAudCap m_tAudSndCap;
	
	tagTUmsNodeCapset()
	{
		Clear();
	}
	
	//������ƥ���������룬����û����������
	BOOL32 InValid() const	{ return TRUE; }
	void Clear()
	{
		
		m_wVidEncNum = 0;
		m_wVidDecNum = 0;
		m_wAudEncNum = 0;
		m_wAudDecNum = 0;
		
		u16 wIndex;
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atVidEnc[wIndex].m_tChanAddr.Clear();
			m_atVidDec[wIndex].m_tChanAddr.Clear();
			m_atAudEnc[wIndex].m_tChanAddr.Clear();
			m_atAudDec[wIndex].m_tChanAddr.Clear();

			m_atSmallVidEnc[wIndex].Clear();
			m_atSmallVidDec[wIndex].Clear();
		}

// 		m_byEncryptBits = emTPEncryptTypeNone;
// 		memset(&m_tEnc, 0, sizeof(m_tEnc));
// 		m_byFECBits = 0;
//		m_wMaxBitRate = 0;
		
		m_tEncrypt.Clear();

		m_tVidRcvCap.Clear();
		m_tVidSndCap.Clear();
		m_tAudRcvCap.Clear();
		m_tAudSndCap.Clear();
	}
	
	tagTUmsNodeCapset & operator = (const tagTUmsNodeCapset& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tagTUmsNodeCapset));
		return *this;
	}
}TUmsNodeCapset;


//�᳡˫������
typedef struct tagTUmsDualCapset 
{	
	TChanNetPara m_tVid;
	TChanNetPara m_tAud;
	
	EmTPEncryptType  m_byEncryptBits;			//��������
	TTpEncryptKey	 m_tEnc;

	u16  m_byFECBits;							//FEC����
	u16 m_wMaxBitRate;							//kbps�� Node֧�ֵ��ܴ���
	
	TTPVideoCap m_tVidCap;						//��Ƶ����
	TTPAudCap m_tAudCap;						//��Ƶ����
	
	tagTUmsDualCapset()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tVid.m_tChanAddr.Clear();
		m_tAud.m_tChanAddr.Clear();
		
		m_byEncryptBits = emTPEncryptTypeNone;
		memset(&m_tEnc, 0, sizeof(m_tEnc));
		m_byFECBits = 0;
		m_wMaxBitRate = 0;
		
		m_tVidCap.m_emFormat =  emTPVH264;
		m_tVidCap.m_emRes = emTPVGA1280x1024;
		m_tVidCap.m_byMaxFrameRate = 10;
		
		m_tVidCap.Clear();
		m_tAudCap.Clear();
	}
}TUmsDualCapset;

//�᳡˫������
typedef struct tagTUmsDualCapsetMc
{	
	TChanNetPara m_tVidEnc;
	TChanNetPara m_tVidDec;
	TChanNetPara m_tAudEnc;
	TChanNetPara m_tAudDec;
	
	u16 m_wMaxBitRate;							//kbps�� Node֧�ֵ��ܴ���
	
	//add
	TUmsVidCapParam	m_tVidRcvCap;
	TUmsVidCapParam	m_tVidSndCap;

	TUmsAudCap m_tAudCap;						//��Ƶ����
	
	tagTUmsDualCapsetMc()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tVidEnc.m_tChanAddr.Clear();
		m_tVidDec.m_tChanAddr.Clear();
		m_tAudEnc.m_tChanAddr.Clear();
		m_tAudDec.m_tChanAddr.Clear();
		
		m_wMaxBitRate = 0;
		
		m_tVidRcvCap.Clear();
		m_tVidSndCap.Clear();

		m_tAudCap.Clear();
	}
}TUmsDualCapsetMc;

//MakeCallPara : ���в���
typedef struct tagTMakeCallPara
{
	TUmsCallInfo	m_tCallInfo;
	TUmsNodeCapset	m_tCapSet;
	TUmsDualCapsetMc	m_tDualCapSet;
	tagTMakeCallPara()
	{
		
	}
	void Clear()
	{
		m_tCallInfo.Clear();
		m_tCapSet.Clear();
		m_tDualCapSet.Clear();
	}
}TMakeCallPara, *PTMakeCallPara;


//UMS����֪ͨ������Ϣ
typedef struct tagTTPConfInfoNtfy
{
	u16 m_wConfID;
	u16 m_wEpID;
	time_t m_tBeginTime;
	TTPName	m_tConf;			//��������
	TTPName	m_tChair;			//��ϯ����
	TTPName	m_tSpeak;			//����������
	u16	m_wChairVidSndCap;
	u16 m_wChairAudSndCap;
	BOOL32 m_bMixMotive; //�Ƿ�������������
	BOOL32 m_bSpeakOnline;	//�������Ƿ�����
		
	tagTTPConfInfoNtfy()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_tBeginTime = 0;
		m_tConf.Clear();
		m_tChair.Clear();
		m_tSpeak.Clear();
		m_wChairVidSndCap = 0;
		m_wChairAudSndCap = 0;
		m_bMixMotive = TRUE;
		m_bSpeakOnline = FALSE;
	}

	u16 IsChairThreeVidSnd()		{	return m_wChairVidSndCap == 3; }
	u16 IsChairSingleVidSnd()		{	return m_wChairVidSndCap == 1; }
	
	u16 IsChairThreeAudSnd()		{	return m_wChairAudSndCap == 3; }
	u16 IsChairSingleAudSnd()		{	return m_wChairAudSndCap == 1; }
}TTPConfInfoNtfy;

typedef struct tagTCnsSpeakerAdjust
{
	TEpKey	m_tKey;
	u16 m_wEpID;
	u16 m_wSpeakerIndex;
	tagTCnsSpeakerAdjust()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wSpeakerIndex = TP_INVALID_INDEX;
		m_tKey.Clear();
	}
}TCnsSpeakerAdjust;

typedef struct tagTEqpRes
{
	u32 m_dwEqpNode;
	u32 m_dwEqpInst;
	u32 m_dwEqpIp;			//������
	u16 m_wEqpIndex;
	
	tagTEqpRes()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpNode = 0;
		m_dwEqpInst = 0;
		m_dwEqpIp = 0;
		m_wEqpIndex = TP_INVALID_INDEX;
	}
	BOOL32 IsValid() const	{	return m_dwEqpNode != 0; }
}TEqpRes;


typedef struct tagTModelProp
{
	EMEqpType m_wEqpType;	//ģ������
	s8 m_achAlias[TP_MAXLEN_EQP_ALIAS];  //�������
	u32 m_dwCapSet;
	u32_ip m_dwEqpIP;   //����IP��ַ
	u16 m_wVersion;     //����汾��Ϣ

	tagTModelProp()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wEqpType = em_unknow_mdl;
		m_dwCapSet = 0;
		m_dwEqpIP = 0;
		m_wVersion = 0;
		m_achAlias[0] = '\0';
	}
	void SetEqpAlias(char* szAlias)
	{
		strncpy( m_achAlias ,szAlias ,sizeof(m_achAlias) );
		m_achAlias[TP_MAXLEN_EQP_ALIAS-1] ='\0';
	}
	
	const s8* GetEqpAlias() const	{ return m_achAlias;	}
	void SetVersion(u16 wVersion)	{ m_wVersion = htons(wVersion);}
	u16 GetVersion() const			{ return ntohs(m_wVersion);	}
}TModelProp;


//stack cfg 
typedef struct tagTUmsStackCallCfg
{
	u32  m_dwUmsNode;	//UMS���������
	u16	 m_wUmsIndex;	//UMS���������	
	u16  m_wCallingPort; //���ж˿�
	u16  m_wMaxCallNum;//��������
	u32  m_dwKeepAliveTime;//second
	
	u32_ip	 m_dwRegIP;
	u16	 m_wRegPort;
	
	s32	 m_nProductIdSize;
	s8	 m_abyProductId[TP_NAME_LEN_256+1];				//��Ʒ��
	s32	 m_nVerIdSize;
	s8	 m_abyVersionId[TP_NAME_LEN_256+1];				//�汾��

	tagTUmsStackCallCfg()
		:m_dwUmsNode(0)
		,m_wUmsIndex(TP_INVALID_INDEX)
		,m_wCallingPort(TP_UMS_SIP_LISTIEN_PORT)
		,m_wMaxCallNum(TP_UMS_MAX_CALLNUM)
		,m_dwKeepAliveTime(TP_ROUNDTRIP_TIME)
		,m_nProductIdSize(0)
		,m_nVerIdSize(0)
		,m_dwRegIP(0)
		,m_wRegPort(0)
	{
	}
	
	void SetProductID(s8* pszID)
	{
		strncpy(m_abyProductId, UMS_ProductID, TP_NAME_LEN_256);
		m_nProductIdSize = strlen(m_abyProductId);
	}
	void SetVerID(s8* pszID)
	{
		strncpy(m_abyVersionId, UMS_VerID, TP_NAME_LEN_256-1);
		m_nVerIdSize = strlen(m_abyVersionId);
	}
}TUmsStackCallCfg;


//mediatrans
typedef struct tagTUmsMediatransCfg
{
	u32  m_dwUmsNode;	//UMS���������
	u16	 m_wUmsIndex;	//UMS���������	
	tagTUmsMediatransCfg()
		:m_dwUmsNode(0)
		,m_wUmsIndex(TP_INVALID_INDEX)
	{
	}
}TUmsMediatransCfg;

//netbuf
typedef struct tagTUmsNetbufCfg
{
	u32  m_dwUmsNode;	//UMS���������
	u16	 m_wUmsIndex;	//UMS���������	
	tagTUmsNetbufCfg()
		:m_dwUmsNode(0)
		,m_wUmsIndex(TP_INVALID_INDEX)
	{
	}
}TUmsNetbufCfg;


typedef struct tagTDualInfoTr
{
	s32 m_nScreenNo;
	TEpKey m_tKey;
	
	TUmsDualCapset m_tDualCap;
	
	tagTDualInfoTr()
	{
		m_nScreenNo = TP_INVALID_INDEX;
		m_tKey.Clear();
		m_tDualCap.Clear();
	}
	
}TDualInfoTr;

typedef struct tagTDualInfoAckTr
{
	BOOL32    m_bAccept;
	TDualInfoTr m_tDualInfo;
	tagTDualInfoAckTr()
	{
		m_bAccept = FALSE;
	}
}TDualInfoAckTr;

typedef struct tagTDualRequestAckTr
{
	BOOL32 m_bAccept;
	EmTPDualReason	m_dwReason;
	TEpKey m_tEpKey;
	tagTDualRequestAckTr()
	{
		m_bAccept = FALSE;
		m_dwReason = emTpDualAccept;
		m_tEpKey.Clear();
	}
}TDualRequestAckTr;

typedef struct tagTAudChanAck
{
	u16			m_wReason;					//ԭ��
	TEpKey		m_tEpKey;
	TTPTransAddr m_atBackRtcpAddr[TP_MAX_STREAMNUM];
	TTPTransAddr m_tMixBackRtcpAddr;
	tagTAudChanAck()
	{
		m_tEpKey.Clear();
		m_wReason = TP_RET_OK;
		
		memset(m_atBackRtcpAddr, 0, sizeof(m_atBackRtcpAddr));
		m_tMixBackRtcpAddr.Clear();
	}
	
}TAudChanAck;

typedef struct tagTAudChanCmd
{
	TEpKey			m_tEpKey;
	TTPTransAddr	m_atRtpAddr[TP_MAX_STREAMNUM];
	TTPTransAddr	m_tMixRtpAddr;
	
	tagTAudChanCmd()
	{
		m_tEpKey.Clear();
		memset(m_atRtpAddr, 0, sizeof(m_atRtpAddr));
		m_tMixRtpAddr.Clear();
	}
	
}TAudChanCmd;

typedef struct tagTVidUpAddr
{
	TTPTransAddr		m_tAddr;
	TTPTransAddr		m_tSmallAddr;
	tagTVidUpAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_tAddr.Clear();
		m_tSmallAddr.Clear();
	}
}TVidUpAddr;

typedef struct tagTVidDownAddr
{
	TTPTransAddr	m_tAddr;
	TTPTransAddr	m_tSmallAddrL;
	TTPTransAddr	m_tSmallAddrR;
	tagTVidDownAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_tAddr.Clear();
		m_tSmallAddrL.Clear();
		m_tSmallAddrR.Clear();
	}
}TVidDownAddr;

typedef struct tagTVidChanCmd
{
	TEpKey				m_tEpKey;
	TVidUpAddr			m_atUpRtp[TP_MAX_STREAMNUM];	//�ϴ���Rtp�˿�
	TVidDownAddr		m_atDownBackRtcp[TP_MAX_STREAMNUM]; //�´���BackRtcp�˿�

	TTPTransAddr		m_atAudBackRtcp[TP_MAX_STREAMNUM];

	tagTVidChanCmd()
	{
		m_tEpKey.Clear();
		memset(m_atUpRtp, 0, sizeof(m_atUpRtp));
		memset(m_atDownBackRtcp, 0, sizeof(m_atDownBackRtcp));
		memset(m_atAudBackRtcp, 0, sizeof(m_atAudBackRtcp));
	}
}TVidChanCmd;

typedef struct tagTVidChanAck
{
	u16					m_wReason;	//ԭ��
	TEpKey				m_tEpKey;
	TVidUpAddr			m_atUpBackRtcp[TP_MAX_STREAMNUM];	//�ϴ���BackRtcp�˿�
	TVidDownAddr		m_atDownRtp[TP_MAX_STREAMNUM];		//�´���Rtp�˿�

	TTPTransAddr		m_atAudRtp[TP_MAX_STREAMNUM];

	tagTVidChanAck()
	{
		m_wReason = TP_RET_OK;
		m_tEpKey.Clear();
		memset(m_atUpBackRtcp, 0, sizeof(m_atUpBackRtcp));
		memset(m_atDownRtp, 0, sizeof(m_atDownRtp));
		memset(m_atAudRtp, 0, sizeof(m_atAudRtp));
	}
}TVidChanAck;

typedef struct tagTDiscussObjInfo
{
	u16      m_wReserve; // ����

	BOOL32   m_abIsVaild[TP_MAX_STREAMNUM];
	TTPAlias m_atEpAlias[TP_MAX_STREAMNUM];

	tagTDiscussObjInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussObjInfo));
	}

	BOOL32 IsVaildObj()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (m_abIsVaild[wIndex])
			{
				return TRUE;
			}
		}
		return FALSE;
	}
	
}TDiscussObjInfo;

typedef struct tagTDiscussEpAudInfo
{
	u16       m_awDiscussEpId[TP_CONF_MAX_AUDMIXNUM];
	u8        m_abyIsRcvNModeAud[TP_CONF_MAX_AUDMIXNUM][TP_MAX_STREAMNUM];

	tagTDiscussEpAudInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussEpAudInfo));
	}

	void AddEp(u16 wEpId, u16 wScreenIndex)
	{
		if (0 != wEpId && wScreenIndex < TP_MAX_STREAMNUM)
		{
			u16 wIndex = 0;
			for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
			{
				if (0 == m_awDiscussEpId[wIndex] || m_awDiscussEpId[wIndex] == wEpId)
				{
					m_awDiscussEpId[wIndex] = wEpId;
					m_abyIsRcvNModeAud[wIndex][wScreenIndex] = 1;
					return;
				}
			}
		}
		
		return;
	}

	BOOL32 IsRcvNNmodeAud(u16 wEpId, u16 wScreenIndex)
	{
		if (0 != wEpId && wScreenIndex < TP_MAX_STREAMNUM)
		{
			u16 wIndex = 0;
			for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
			{
				if (m_awDiscussEpId[wIndex] == wEpId)
				{
					return (1 == m_abyIsRcvNModeAud[wIndex][wScreenIndex]);
				}
			}
		}
		return FALSE;
	}

}TDiscussEpAudInfo;

typedef struct tagTDiscussCasecadeNtfy
{
	BOOL32 m_bIsDiscussModle;
	
	TDiscussObjInfo m_atDiscussObj[emDiscussObjEnd];

	TDiscussEpAudInfo m_tEpAudInfo;

	tagTDiscussCasecadeNtfy()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussCasecadeNtfy));
	}

}TDiscussCasecadeNtfy;

typedef struct tagTDisScreenStat
{
	BOOL32 m_bInDiscard;//�û᳡�Ƿ���������
	u16 m_wEpIDDst;//UMS������

	EmTPDisOprType	m_emOprType;					//��������

	u16 m_awScreenNum[TP_MAX_STREAMNUM]; //��������Ӧ�᳡������
	u16 m_awSpeakerIndx[TP_MAX_STREAMNUM];//��������Ӧ�᳡�Ķ�Ӧ�ķ�����ϯ����
	TTPAlias m_atAlias[TP_MAX_STREAMNUM];//��������Ӧ�Ļ᳡��������Чֵ����˴��᳡Ϊ���迴��̬ͼƬ������Ϊ�м�
	
	tagTDisScreenStat(){Clear();}
	
	void Clear()
	{
		m_bInDiscard = FALSE;
		m_wEpIDDst = TP_INVALID_INDEX;
		m_emOprType = emDisOprType_Idle;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atAlias[wIndex].Clear();
			m_awScreenNum[wIndex] = TP_INVALID_INDEX;
			m_awSpeakerIndx[wIndex] = TP_INVALID_INDEX;
		}
	}
	
	void SetByScreenID( u16 wScreenID, TTPAlias tAlias, u16 wScreenNum, u16 wSpeakerIndex )
	{
		m_atAlias[wScreenID].SetAlias( tAlias.m_byType, tAlias.m_abyAlias);
		m_awSpeakerIndx[wScreenID] = wSpeakerIndex;
		m_awScreenNum[wScreenID] = wScreenNum;
		return ;
	}

	void ReSetByScreenID(u16 wScreenID)
	{
		m_atAlias[wScreenID].Clear();
		m_awSpeakerIndx[wScreenID] = TP_INVALID_INDEX;
		m_awScreenNum[wScreenID] = TP_INVALID_INDEX;
		return;
	}

	TTPAlias* GetAliasByIndx( u16 wIndex )	{return &m_atAlias[wIndex];}
	
}TDisScreenStat;

typedef struct tagTDisAskKeyFrame
{
	u16 m_wEpID;
	u16 m_wScreenNo;
	BOOL32 m_bReqBySys;
	tagTDisAskKeyFrame(){Clear();}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNo = TP_INVALID_INDEX;
		m_bReqBySys = FALSE;
	}

}TDisAskKeyFrame; 

typedef struct tagTTPBrdRegInfo
{
	TTPBrdPos	m_tBrdPos;				/*��������*/
	u8			m_byNetIndx;			/* ����ʹ�õ����ڣ�ǰ�� */
	EMOsType	m_emOsType;				/* ����ϵͳ */	

	tagTTPBrdRegInfo(){Clear();}
	
	void Clear()	{	memset(this, 0, sizeof(tagTTPBrdRegInfo));	}
	
}TTPBrdRegInfo;

typedef struct tagTTPMpu2CfgAck
{
	EMEqpModleType   m_byEqpMdlType;
	u8			m_byEqpId;
    u8			m_byEqpId2;
    u16			m_wEqpRcvStartPort;
    u16			m_wEqpRcvStartPort2;
	
	tagTTPMpu2CfgAck(){Clear();}
	
	void Clear()	{	memset(this, 0, sizeof(tagTTPMpu2CfgAck));	}
	
}TTPMpu2CfgAck;
typedef struct tagTHduCfgAck
{
	u8				m_byStartMode;
	u8				m_byEqpID;	
	tagTHduCfgAck()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTHduCfgAck));
	}

	void SetStartMoe(u8 byMode)
	{
		m_byStartMode = byMode;
	}

	u8 GetStartMode()
	{
		return m_byStartMode;
	}
}THduCfgAck;

typedef struct tagTTPVmpReg
{
	u8			m_byEqpID;
	EMEqpModleType	m_emEqpMdlType;
	u32			m_dwEqpIPAddr;
	u32			m_dwEqpPort;
	u32			m_dwEqpVer;
	
	tagTTPVmpReg()  {Clear();}
	
	void Clear()	{memset(this, 0, sizeof(tagTTPVmpReg));	}
	
}TTPVmpReg;

typedef struct tagTTPBasReg
{
	u8			m_byEqpID;
	EMEqpModleType	m_emEqpMdlType;
	u32			m_dwEqpIPAddr;
	u32			m_dwEqpPort;
	u32			m_dwEqpVer;

	tagTTPBasReg(){Clear();}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBasReg));
	}
	
}TTPBasReg;

typedef struct tagTTPBasRegAck
{
	u32   			m_dwIpAddr;			//UMS���յ�ַ
	u16 			m_wStartPort;		//UMS������ʼ�˿ں�

	s8				m_szAlias[TP_MAXLEN_EQP_ALIAS];		//����
	u16				m_wEqpStartPort;					//���������ʼ�˿ں�    
	u8				m_byEqpId;							//�豸ID
	
	tagTTPBasRegAck() {Clear();}
	
	void Clear()	  {memset(this, 0, sizeof(tagTTPBasRegAck));}

	void SetAlias(const s8* pszAlias)
	{
		strncpy(m_szAlias, pszAlias, sizeof(m_szAlias));
        m_szAlias[sizeof(m_szAlias) - 1] = '\0';
	}

}TTPBasRegAck;

typedef struct tagTTPBasStatNtfy
{
	u8		m_byEqpID;
	s8		m_szAlias[TP_MAXLEN_EQP_ALIAS];		//����

	tagTTPBasStatNtfy()	{	Clear();}
	
	void Clear()		{	memset(this, 0, sizeof(tagTTPBasStatNtfy));	}
	void SetAlias(const s8* pszAlias)
	{
		strncpy(m_szAlias, pszAlias, sizeof(m_szAlias));
        m_szAlias[sizeof(m_szAlias) - 1] = '\0';
	}
}TTPBasStatNtfy;

typedef struct tagTTPBasChnStatNtfy
{
	u8		m_byEqpID;
	u8		m_byChnIndx;
	u8		m_byStat;  // 0 ���� 1 ׼�� 2 ����
	
	tagTTPBasChnStatNtfy()	{ Clear();}
	
	void Clear()	{ memset(this, 0, sizeof(tagTTPBasChnStatNtfy));	}
}TTPBasChnStatNtfy;

typedef struct tagTTPBasRetInfo
{
	u8		m_byEqpID;
	u8		m_byChnID;
	
	tagTTPBasRetInfo(){Clear();}
	
	void Clear()	{memset(this, 0, sizeof(tagTTPBasRetInfo));	}
}TTPBasRetInfo;

typedef struct tagTTPBasNAck
{
	u8		m_byEqpID;
	u16		m_wChnIndx; //ͨ���������е�����
	
	tagTTPBasNAck(){Clear();}
	
	void Clear()	{memset(this, 0, sizeof(tagTTPBasNAck));	}
}TTPBasNAck;

typedef struct tagTHduRegInfo		
{
	u8			m_byLayer;
	u8			m_bySlot;
	u32   		m_dwIpAddr;		//����IP��ַ
	u16 		m_wStartPort;	//������ʼ���ն˿�
	u8  		m_byChannlNum;	//��������ŵ���
	s8          m_achAlias[TP_MAXLEN_EQP_ALIAS];
    u16         m_wVersion;     //�汾��Ϣ
    BOOL        m_bHDEqp;       //�Ƿ��������

	tagTHduRegInfo()	{Clear();}

	void Clear()	{memset(this, 0, sizeof(tagTHduRegInfo));}
}THduRegInfo;

typedef struct tagTHduRegCfgAck
{
	u16				m_wStartPort;	//������ʼ���յ�ַ
	s8				m_szAlias[TP_MAXLEN_EQP_ALIAS];	//����
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];

	tagTHduRegCfgAck()	{Clear();}

	void Clear()
	{
		memset(this, 0, sizeof(tagTHduRegCfgAck));

		for (u16 wIndex = 0; wIndex < HDU_MAX_CHANNEL_NUM; ++wIndex)
		{
			m_atChanInfo[wIndex].Clear();
		}
	}
}THduRegCfgAck;

//����汾��
typedef struct tagTBrdVersion
{
	u16		m_wBrdIndex;
	u8		m_achBrdVer[TP_BOARD_VERSION_LEN];
	u8		m_achSoftVer[TP_BOARD_VERSION_LEN];
	tagTBrdVersion(){Clear();}
	void Clear()
	{
		m_wBrdIndex = TP_INVALID_INDEX;
		memset(m_achBrdVer, 0, sizeof(m_achBrdVer));
		memset(m_achSoftVer, 0, sizeof(m_achSoftVer));
	}
}TBrdVersion;
//��������
typedef struct tagTBrdUpInfo
{
	u8		m_byIndex;		//��������
	u8		m_byNum;		//Դ�ļ�������
	u8		m_byNameLen;	//�ļ�������
	s8		m_szFileName[TP_UPGRADE_FILENAME_LENGTH];
	tagTBrdUpInfo(){Clear();}
	void Clear()
	{
		m_byIndex = (u8)TP_INVALID_INDEX;
		m_byNum = 0;
		m_byNameLen = 0;
		memset(m_szFileName, 0, sizeof(m_szFileName));
	}
}TBrdUpInfo;

//�ϼ�����״̬
typedef struct tagTUpRecPlayState
{
	BOOL32		m_bIsPlayIng;	//�Ƿ��ڷ���
	BOOL32		m_bIsDualPlayIng;	//�Ƿ��˫��
	s8			m_achFileName[TP_REC_FILE_LEN];	//�ļ���

	tagTUpRecPlayState()
	{
		Clear();
	}

	void Clear()
	{
		m_bIsPlayIng = FALSE;
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
	}
}TUpRecPlayState;

typedef struct tagTReqAddrInfo
{
	u32		m_dwSipHandle;	//SIPע����
	u32		m_dwGkHandle;	//GKע����

	tagTReqAddrInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_dwSipHandle = 0;
		m_dwGkHandle = 0;
	}
}TReqAddrInfo;

typedef struct tagTGetVidBaseInfo
{
	u16				m_wHandle;
	u16				m_wEpID;
	u16				m_wScreenIndex;
	EmGetVidType	m_emType;

	tagTGetVidBaseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wHandle = 0;
		m_wEpID = 0;
		m_emType = em_GetVid_Invalid;
		m_wScreenIndex = TP_MAX_STREAMNUM;
	}

}TGetVidBaseInfo;

typedef struct tagTGetVidInfo
{
	TGetVidBaseInfo		m_tBaseInfo;
	BOOL32				m_bSamll;
	TTPMediaTransAddr	m_atVidAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_atAudAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_atSmallVid[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_tMixAddr;

	tagTGetVidInfo()
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

}TGetVidInfo;

typedef struct tagTGetVidInfoRes
{
	EmGetVidRes		m_emRes;
	TGetVidInfo		m_tInfo;

	tagTGetVidInfoRes()
	{
		Clear();
	}

	void Clear()
	{
		m_emRes = em_GetVid_Success;
		m_tInfo.Clear();
	}
}TGetVidInfoRes;

typedef struct tagTStopGetVid
{
	TGetVidBaseInfo	m_tInfo;
	EmGetVidRes		m_emRes;
	
	tagTStopGetVid()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tInfo.Clear();
		m_emRes = em_GetVid_Success;
	}
}TStopGetVid;


//�������� ��Ϊ��������Դ�˿�
typedef struct tagTIFrameSndDis
{
	//�Ƿ��������ؼ�֡ FALSEΪ�����ȴ�
	BOOL32 m_bCheck;
	
	//��Ҫ���˵�Ŀ�Ķ˿�
	u32_ip m_dwDstIp;
	u16 m_wDstPort;
	
	//��������ʹ�� �������汻���ȴ���base �е� port
	u16 m_wOldPort;
	
	void Clear()
	{
		m_bCheck= 0;
		m_wOldPort = 0;
		
		m_dwDstIp = 0;
		m_wDstPort = 0;
	}	
}TIFrameSndDis;

typedef struct tagTIpmaskinfo
{
	u32_ip m_dwIpa;
	u32_ip m_dwMaska;
	u32_ip m_dwIpb;
	u32_ip m_dwMaskb;
	u32_ip m_dwOutIp;

	tagTIpmaskinfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTIpmaskinfo));
	}

	BOOL32 IsSameNetwork()
	{
		if (0 == m_dwIpa || 0 == m_dwIpb || 0 == m_dwMaska || 0 == m_dwMaskb)
		{
			return TRUE;
		}

		return (m_dwIpa&m_dwMaska) == (m_dwIpb&m_dwMaskb);
	}

	u32 GetSameNetWork(u32 dwDstIp)
	{
		if ((dwDstIp&m_dwMaska) == (m_dwIpa&m_dwMaska))
		{
			return m_dwIpa;
		}
		if ((dwDstIp&m_dwMaskb) == (m_dwIpb&m_dwMaskb))
		{
			return m_dwIpb;
		}
		return 0;
	}

	BOOL32 IsValid()
	{
        if(m_dwIpa && m_dwMaska && m_dwIpb && m_dwMaskb)
		{
            return TRUE;
		}
		
		return FALSE;
	}

}TIpmaskinfo;

////////////////////////

typedef struct tagTRollCallEpNodeInfo
{
    u16 m_wEpId;           //�����˱��������ڱ���UMS �е�EPID ������ڱ�����ΪInvalid

	u16 m_wVidSndNum;     
	u16 m_wVidRcvNum;

	u16 m_wAudSndNum;
	u16 m_wAudRcvNum;

	u16 m_wSpeakerSeat;   //��ϯ
    
	TTPAlias  m_Alias;

    tagTRollCallEpNodeInfo()
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
		
		m_wSpeakerSeat = TP_INVALID_INDEX; 
		
		
        m_Alias.Clear(); 
	}

	tagTRollCallEpNodeInfo& operator = (const tagTRollCallEpNodeInfo& tRhs)
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
	u16 GetSpeaker()const	{ return m_wSpeakerSeat < TP_MAX_STREAMNUM ? m_wSpeakerSeat :  (u16)(MIDSCREENINDEX);}

}TRollCallEpNodeInfo;



typedef struct tagTRollCallCasecadeNtfy
{
	EMRollCallNotyToLowUmsType  m_NotyType;
    BOOL32 m_bIsRollCallModle;
    TRollCallEpNodeInfo m_NodeInfo[NUM_OF_CALLER_AND_TARGET];
	
	tagTRollCallCasecadeNtfy()
	{
		Clear();
	}
	
	void Clear()
	{
        m_NotyType         = em_RollCallNotyUpNodeInfo;
		m_bIsRollCallModle = FALSE;

        for(u16 wIndex = 0; wIndex < NUM_OF_CALLER_AND_TARGET; wIndex++)
		{
            m_NodeInfo[wIndex].Clear();
		}
	}
	
	tagTRollCallCasecadeNtfy& operator = (const tagTRollCallCasecadeNtfy& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}

		m_NotyType            = tRhs.m_NotyType;
		m_bIsRollCallModle    = tRhs.m_bIsRollCallModle;


		for(u16 wIndex = 0; wIndex < NUM_OF_CALLER_AND_TARGET; wIndex++)
		{
            m_NodeInfo[wIndex] = tRhs.m_NodeInfo[wIndex];
		}
		
		return *this;
	}
	
}TRollCallCasecadeNtfy;

// ����mcu���
typedef struct tagTUmsMcuChan
{
	s32		m_hMcuChan;
	s32		m_hMcuAppChan;

	tagTUmsMcuChan()
	{
		Clear();
	}

	void Clear()
	{
		
		m_hMcuChan = 0;
		m_hMcuAppChan = 0;
	}
}TUmsMcuChan;

typedef struct tagTUmsMcuRegUnReg
{
	BOOL32			m_bReg;
	s32 			m_nReqID;
	EmUmsMcuRet		m_emRet;

	tagTUmsMcuRegUnReg()
	{
		Clear();
	}

	void Clear()
	{
		m_bReg = FALSE;
		m_nReqID = 0;
		m_emRet = em_umsmcuret_Ok;
	}

}TUmsMcuRegUnReg;

typedef struct tagTUmsMcuRosterItem
{
	u8			m_byState; // 0 unkown 1 connected 2 disconnected 3 connecting
	u32			m_dwPID;   // mcuid+mtid

	tagTUmsMcuRosterItem()
	{
		Clear();
	}

	void Clear()
	{
		m_byState = 0;
		m_dwPID = 0xffffffff;
	}

	
}TUmsMcuRosterItem;

typedef struct tagTUmsMcuRosterList
{
	u16					m_wNum;
	TUmsMcuRosterItem	m_atRoster[UMS_MCU_ROSTER_PARTLIST_NUM];

	tagTUmsMcuRosterList()
	{
		Clear();
	}

	void Clear()
	{
		m_wNum = 0;
		for(u16 wIndex = 0; wIndex < UMS_MCU_ROSTER_PARTLIST_NUM; wIndex++)
		{
			m_atRoster[wIndex].Clear();
		}
	}


}TUmsMcuRosterList;

typedef struct tagTUmcMcuPart
{
	u32         m_dwPID;          // part id
    s8			m_aszEpName[UMS_MCU_PART_NAME];     //part name (����:16Byte) 
    u32			m_dwIP;            //part ip
    //EmTPEndpointType	m_emEPType;        //part type
    u8			m_byState; // 0 unkown 1 connected 2 disconnected 3 connecting
	BOOL32      m_bMute;   // ����
	BOOL32		m_bQuiet;  // ����
	
    tagTUmcMcuPart()
    {
        memset(this, 0, sizeof(*this));
    }
   
}TUmcMcuPart;

typedef struct tagTMcuEpCmd
{
	u32		m_dwPID;
	BOOL32	m_bCall; // true:���л᳡����  false:�Ҷϻ᳡
	tagTMcuEpCmd()
	{
		m_dwPID	= (u32)(0xffffffff);
		m_bCall = FALSE;
	}
}TMcuEpCmd;

typedef struct tagTUmsMcuPartList
{
	s32			m_nReqID;
	EmUmsMcuRet	m_emRet;
    s32			m_dwPartCount;      // part count
	BOOL32		m_bLastPack;		// �Ƿ����һ��
    //s32    m_nSnapShot;         //����Ŀ���ֵ ��Чֵ��

	tagTUmsMcuPartList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_nReqID		= 0;
		m_emRet			= em_umsmcuret_Ok;
		m_dwPartCount	= 0;
		m_bLastPack		= FALSE;
	}
} TUmsMcuPartList;

typedef struct tagTMcuSpeakerStausNty
{
	u32		m_dwPID;
	u32		m_dwStatus; // 0 invalid 1 �ն��ڷ������� �� ��Ϊ������֪ͨ �� ֮ǰ���Զ������״̬ 2 ������ 3 ���뱻�� 4 ��ȡ�������� 
	tagTMcuSpeakerStausNty()
	{
		Clear();
	}
	void Clear()
	{
		m_dwPID		= (u32)(0xffffffff);
		m_dwStatus	= 0;
	}

}TMcuSpeakerStausNty;

typedef struct tagTMcuSpyReq
{
	u32		m_dwPID;
	EmTpVideoResolution		m_emRes; 
	tagTMcuSpyReq()
	{
		Clear();
	}

	void Clear()
	{
		m_dwPID	= (u32)(0xffffffff);
		m_emRes	= emTPVResolutionAuto;
	}
}TMcuSpyReq;

typedef struct tagTFeccMtInfo
{
	u8		m_bySrcMcuId;
	u8		m_bySrcMtId; 

	u8		m_byDstMcuId;
	u8		m_byDstMtId;
	tagTFeccMtInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_bySrcMcuId = 0xff;
		m_bySrcMtId  = 0xff;
		m_byDstMcuId = 0xff;
		m_byDstMtId  = 0xff;
	}

}TFeccMtInfo;

typedef struct tagTEpVidFeccInfo
{
	TEpPathKey m_tID;						//��״��
	TVidFeccInfo m_tVidFeccInfo;
	tagTEpVidFeccInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tID.Clear();
		m_tVidFeccInfo.Clear();
	}

}TEpVidFeccInfo;

typedef struct tagTConfEpVidFeccList
{
	u16		m_wNum;
	TEpVidFeccInfo m_atList[TP_REFRESH_LIST_THREE];
	tagTConfEpVidFeccList()
	{
		Clear();
	}
	void Clear()
	{
		m_wNum = 0;
		for (u16 wIndex = 0; wIndex < TP_REFRESH_LIST_THREE; ++wIndex)
		{
			m_atList[wIndex].Clear();
		}
	}

}TConfEpVidFeccList;

typedef struct tagTEpStatusInfo
{
	TQuietRmtEpInd	m_tQuietInd;	// ����
	TMuteRmtEpInd	m_tMuteInd;		// ����

	u8				m_byCurVidNo;	// ��ǰԴ
	BOOL32			m_bAllowFecc;	// Զңͨ���Ƿ��
	tagTEpStatusInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tQuietInd.Clear();
		m_tMuteInd.Clear();
		m_bAllowFecc = FALSE;
		m_byCurVidNo = 0;
	}
	
}TEpStatusInfo;

//telnet ftp״̬
typedef struct tagTTelnetFtpStatus
{
    BOOL32 m_bTelnetStatus;
	BOOL32 m_bFtpStatus;
	tagTTelnetFtpStatus()
	{
		Clear();
	}
	void Clear()
	{
		// Ĭ��ֵȡ�����������ã��忨��ftp��telnetĬ�϶��ǿ���
		m_bTelnetStatus = TRUE;
		m_bFtpStatus    = TRUE;
	}
	
}TTelnetFtpStatus;

//telnet ftp״̬
typedef struct tagTBrdSwitchInfo
{
    u16    m_wBrdIndex;
	BOOL32 m_bSwitch;
	EmBoardSwitchType m_emType;
	tagTBrdSwitchInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wBrdIndex  = 0xFFFF;
		m_bSwitch    = FALSE;
		m_emType     = em_BoardSwitch_end;
	}
	
}TBrdSwitchInfo;

////////////////////////

/*******************����µĽṹ�嶨���������Professional_VOB\t0-luna\localxmlparse\umslocalxmlparse.bat�ű�****/


#endif // _h_umscommonstruct_h__


