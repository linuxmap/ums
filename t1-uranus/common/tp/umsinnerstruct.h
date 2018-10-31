#ifndef _h_umsinnerstruct_h__
#define _h_umsinnerstruct_h__

#include "umconst.h"
#include "tpsys.h"
#include "tpstruct.h"
#include "umsinnertype.h"
#include "umscommonstruct.h"

typedef struct tagTServiceAddr
{
	u32					m_dwMediaNode;
	TTPMediaTransAddr	m_tAddr;

	tagTServiceAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_dwMediaNode = 0;
		m_tAddr.Clear();
	}

	BOOL32 IsValidAddr()
	{
		return 0 != m_dwMediaNode;
	}

}TServiceAddr;

typedef struct tagTServiceBaseInfo
{
	EmServiceType	m_emType;
	u16				m_wServiceID;
	
	tagTServiceBaseInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emType = em_unknow_service;
		m_wServiceID = 0;
	}

	BOOL32 Invalid()
	{
		return em_unknow_service == m_emType || 0 == m_wServiceID;
	}

	tagTServiceBaseInfo& operator=(const tagTServiceBaseInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_emType = tInfo.m_emType;
			m_wServiceID = tInfo.m_wServiceID;
		}

		return *this;
	}

}TServiceBaseInfo;

typedef struct tagTServiceReg
{
	TServiceBaseInfo	m_tBaseInfo;
	u16					m_wEqpStartPort;
	u32					m_dwEqpIP;
	u16					m_wUmsStartPort;
	u32					m_dwLocalIP;
	u32					m_dwMediaNode;

	tagTServiceReg()
	{
		Clear();
	}

	void Clear()
	{
		m_tBaseInfo.Clear();
		m_wEqpStartPort = 0;
		m_dwEqpIP = 0;
		m_wUmsStartPort = 0;
		m_dwLocalIP = 0;
		m_dwMediaNode = 0;
	}

}TServiceReg;

typedef struct tagTVmpUseParam
{
	TTPEncrypt		m_tEncrypt;
	TVmpStyleInfo	m_tStyleInfo;
	TVmpEncParam	m_tEncParam;

	
	tagTVmpUseParam()
	{
		Clear();
	}

	tagTVmpUseParam& operator=(const tagTVmpUseParam& tInfo)
	{
		if (this != &tInfo)
		{
			m_tEncrypt = tInfo.m_tEncrypt;
			m_tStyleInfo = tInfo.m_tStyleInfo;
			m_tEncParam = tInfo.m_tEncParam;
		}
		
		return *this;
	}
	
	void Clear()
	{
		m_tEncrypt.Clear();
		m_tStyleInfo.Clear();
		m_tEncrypt.Clear();
	}

}TVmpUseParam;

typedef struct tagTVmpStartInfo
{
	u16				m_wServiceID;
	TVmpUseParam	m_tVmpParam;

	tagTVmpStartInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wServiceID = 0;
		m_tVmpParam.Clear();
	}

}TVmpStartInfo;

typedef struct tagTVmpStartResult
{
	TServiceBaseInfo	m_tBaseInfo;
	EmServiceRes		m_emRes;

	tagTVmpStartResult()
	{
		Clear();
	}

	void Clear()
	{
		m_tBaseInfo.Clear();
		m_emRes = em_Start_Failed;
	}

}TVmpStartResult;

typedef struct tagTVmpMdyResult
{
	TServiceBaseInfo	m_tBaseInfo;
	EmServiceRes		m_emRes;
	
	tagTVmpMdyResult()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tBaseInfo.Clear();
		m_emRes = em_Start_Failed;
	}
	
}TVmpMdyResult;

typedef struct tagTUmsCallCfg
{
	u16 m_wStartPort;
	u16 m_wMaxOnceCall;
	tagTUmsCallCfg()
		:m_wStartPort(0)
		,m_wMaxOnceCall(8)
	{
	}
}TUmsCallCfg;


typedef struct tagTLogUser 
{
	u32 m_dwUserID;
	u32 m_dwUserNode;
	u32 m_dwUserInst;
	u32 m_dwUserIP;
	char m_achName[MAX_CHARLENGTH]; //�û���	
	
	tagTLogUser()
	{
		Clear();
	}
	
	void Clear()
	{
		m_dwUserID = TP_INVALID_INDEX;
		m_dwUserNode = 0;
		m_dwUserInst = 0;
		m_dwUserIP = 0;
		m_achName[0] = '\0';
	}
	BOOL32 Invalid()const	
	{	
		return 0 == m_dwUserNode; 
	} 
	

	BOOL32 operator == (const tagTLogUser& tRhs)
	{
		return m_dwUserNode == tRhs.m_dwUserNode;
	}

	tagTLogUser& operator = (const tagTLogUser& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		
		m_dwUserNode = tRhs.m_dwUserNode;
		m_dwUserInst = tRhs.m_dwUserInst;
		m_dwUserIP = tRhs.m_dwUserIP;
		memcpy(m_achName, tRhs.m_achName, MAX_CHARLENGTH);
		return *this;
	}
	
}TLogUser ;

typedef struct tagTAddTvMonitor
{
	TTPHduPlayReq		m_tReq;
	TTPMediaTransAddr	m_tVidAddr;
	TTPMediaTransAddr	m_tAudAddr;
}TAddTvMonitor;

typedef struct tagTAddTvMonitorAck
{
	BOOL32 m_bAccept;

	TTPHduPlayReq		m_tReq;
	TTPMediaTransAddr	m_tVidAddr;
	TTPMediaTransAddr	m_tAudAddr;

	// ���ܲ���
	TTPEncrypt      m_tEncrypt;

	u8	m_byVidPayload;
	u8	m_byAudPayload;
}TAddTvMonitorAck;


//CnsNodeInfo : CNS�Ļ�����Ϣ
typedef struct tagTCnsRegNode
{
	u16				m_wAliasNum;
	TTPAlias		m_atAlias[TP_MAX_ALIAS_NUM];
	TTPTransAddr	m_atCalledAddr[TP_MAX_NUM_CONTACT_ADDR];	//���е�ַ
	
	u32				m_dwExpires;//��ʱʱ��
	s8				m_aCallId[TP_MAX_NUM_CALLID];//����ID
	s32				m_nCSqence;//���к� //m_tRegistrar m_dwExpires m_aCallId m_nCSqence ��Ҫҵ��㱣�棬�Ա��ѯ

	EmTPEndpointType	m_emSelfType;//ע�᷽ ��ϵͳ����(UMS��CNS)				
	s8					m_aSelfVer[TP_MAX_VERSION_LEN +1];//ע�᷽ �İ汾��
	u32_ip				m_dwSelfAddr;//ע�᷽ �ĵ�ַ
	s8					m_aCompileTm[TP_MAX_VERSION_LEN +1];//ע�᷽�ı���ʱ��
	

	u32					m_dwSelfQtID;//ע�᷽ �ı��������ն�ID

	tagTCnsRegNode()
	{
		Clear();
	}
	void Clear()
	{
		m_wAliasNum = 0;
		for (u32 dwIndex = 0; dwIndex < TP_MAX_NUM_CONTACT_ADDR; dwIndex++)
		{
			m_atCalledAddr[dwIndex].Clear();
		}
		m_dwExpires = 0;
		m_nCSqence = 0;
		m_aCallId[0] = '\0';

		m_emSelfType = emTPEndpointTypeUnknown;
		memset( m_aSelfVer, 0, sizeof(m_aSelfVer));
		m_dwSelfAddr = 0;
		memset(m_aCompileTm, 0, sizeof(m_aCompileTm));
	}
}TCnsRegNode;


//CNS��Ϣ����
typedef struct tagTCnsRegInfo
{
	u32				m_dwTryTimes;
	u32				m_dwTimerID;
	TCnsRegNode	m_tCsnNodeInfo;

	u32				m_dwCallType;		//�������� TCP���л���UDP���У�ע������������������
		
	tagTCnsRegInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_dwTryTimes = 0;
		m_dwTimerID = 0;
		m_dwCallType = 0;

		m_tCsnNodeInfo.Clear();
	}

	tagTCnsRegInfo& operator = (const tagTCnsRegInfo& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tRhs));
		return *this;
	}
}TCnsRegInfo, *PTCnsRegInfo;


typedef struct tagTRegAdapter
{
	TEqpRes m_tEqp;
	TTPTransAddr m_tAddr;
	
	tagTRegAdapter()
	{
		Clear();
	}
	void Clear()
	{
		m_tEqp.Clear();
		m_tAddr.Clear();
	}
}TRegAdapter;

//��������Ϣ֪ͨ��eqp
typedef struct tagTHduCfgInfo
{
	u8		m_byLayer;	//���
	u8		m_bySlot;	//�ۺ�
	u32		m_dwIP;		//IP
	u8		m_byStartMode;	//����ģʽ
	u16		m_wStartPort;	//�����˿�
	
	u8		m_byChanNum;	//���õ�ͨ����
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];	//ͨ����Ϣ
	TTPName	m_tName;
	BOOL32	m_bQtHdu;
	tagTHduCfgInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byLayer = 0;
		m_bySlot = 0;
		m_dwIP = 0;
		m_byStartMode = 0;
		m_wStartPort = 0;
		m_byChanNum = HDU_MAX_CHANNEL_NUM;
		m_bQtHdu = 0;

		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			m_atChanInfo[byIndex].Clear();
		}
		m_tName.Clear();
	}
}THduCfgInfo;

typedef struct tagTHduRegStatus
{
	u8		m_byLayer;	
	u8		m_bySlot;
	BOOL32	m_bRegRes;

	tagTHduRegStatus()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTHduRegStatus));
	}
}THduRegStatus;

typedef struct tagTHduPlayInfo
{
	u8		m_byLayer;
	u8		m_bySlot;
	u8		m_byChanIndex;
	u8		m_bySubChan;
	BOOL32	m_bVmp;

	tagTHduPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = 0;
		m_bySlot = 0;
		m_byChanIndex = 0;
		m_bySubChan = 0;
		m_bVmp = FALSE;
	}
}THduPlayInfo;

typedef struct tagTVolInfo
{
	u8		m_byVol;
	BOOL32	m_bMute;
	
	tagTVolInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byVol = 0;
		m_bMute = FALSE;
	}
}TVolInfo;

typedef struct tagTHduChanModeInfo
{
	u8		m_byLayer;
	u8		m_bySlot;
	u8		m_byChanIndex;
	u8	    m_byChanMode; // 0 Ϊһ���棬1Ϊ4����

	tagTHduChanModeInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = 0;
		m_bySlot = 0;
		m_byChanIndex = 0;
		m_byChanMode = 0;
	}

}THduChanModeInfo;

typedef struct tagTHduChanStatus
{
	u8		    m_byStatus;  // 0:emIDLE, 1:emINIT, 2:emREADY 3:emRUNNING  ��ӦHdu��ͨ��״̬
	u8			m_byChanIndex;
	u8			m_bySubChan;
	u16			m_wEqpID;
	u8			m_byLayer;
	u8			m_bySlot;

	TVolInfo	m_tChanVol;

	tagTHduChanStatus()
	{
		Clear();
	}

	void Clear()
	{
		m_byStatus = 0;
		m_byChanIndex = HDU_MAX_CHANNEL_NUM;
		m_bySubChan = 0;
		m_wEqpID = 0;
		m_byLayer = 0;
		m_bySlot = 0;
		m_tChanVol.Clear();
	}

	BOOL32 IsVaildStatus()
	{
		return m_byStatus >= 2;
	}

}THduChanStatus;

typedef struct tagTHduUpdateInfo
{
	BOOL32		m_bOnLine;
	u16			m_wEqpID;
	u8			m_byLayer;
	u8			m_bySlot;
	TTPName		m_tName; 

	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];

	tagTHduUpdateInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTHduUpdateInfo));
	}
}THduUpdateInfo;

typedef struct tagTHduVolInfo
{
	u8	m_byLayer;
	u8	m_bySlot;
	u8  m_byChanlIdx;    // ͨ��������
	u8  m_byVolume;     // ������С
	u8  m_byIsMute;		// �Ƿ���

	tagTHduVolInfo()
	{
		m_byLayer = 0;
		m_bySlot = 0;
		m_byChanlIdx = 0;
		m_byVolume = 0;
		m_byIsMute = 0;
	}
}THduVolInfo;

typedef struct tagTHduIFrameInfo
{
	u16			m_wEqpID;
	u8			m_byLayer;
	u8			m_bySlot;
	u8			m_byChanIndex;
	u8			m_bySubChan;

	tagTHduIFrameInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wEqpID = 0;
		m_byLayer = 0;
		m_bySlot = 0;
		m_byChanIndex = 0;
		m_bySubChan = 0;
	}
}THduIFrameInfo;

typedef struct tagTHduUpdateFileInfo
{
	u8		m_byFileLength;
	s8		m_achFileName[256];

	tagTHduUpdateFileInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTHduUpdateFileInfo));
	}

}THduUpdateFileInfo;

typedef struct tagTHduUpdateRes
{
	u8	m_byLayer;
	u8	m_bySlot;
	u8	m_byFileNum;
	u8	m_abyRes[HDU_MAX_UPDATE_FILE_NUM];
	THduUpdateFileInfo	m_atFileInfo[HDU_MAX_UPDATE_FILE_NUM];

	tagTHduUpdateRes()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = 0;
		m_bySlot  = 0;
		m_byFileNum = 0;
		memset(m_abyRes, 0, sizeof(m_abyRes));
	
		for (u16 wIndex = 0; wIndex < HDU_MAX_UPDATE_FILE_NUM; ++wIndex)
		{
			m_atFileInfo[wIndex].Clear();
		}
	}
}THduUpdateRes;

typedef struct tagTHduStyleUnitCfg
{
	u8		m_byLayer;
	u8		m_bySlot;
	u8		m_byChanIndex;
	BOOL32	m_bVmp;

	TTPName		m_tName;

	tagTHduStyleUnitCfg()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byLayer = HDU_MAX_LAYER;
		m_bySlot  = HDU_MAX_SLOT;
		m_byChanIndex = HDU_MAX_CHANNEL_NUM;
		m_bVmp = FALSE;
		m_tName.Clear();
	}
}THduStyleUnitCfg;

//����ǽ���������Ϣ
typedef struct tagTHduStyleCfgInfo
{
	u8				m_byRow; //����
	u8				m_byCol; //����
	THduStyleUnitCfg	m_atHduStyle[HDU_STYLE_MAX_NUM];
	
	tagTHduStyleCfgInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byRow = 0;
		m_byCol = 0;

		for (u16 wIndex = 0; wIndex < HDU_STYLE_MAX_NUM; ++wIndex)
		{
			m_atHduStyle[wIndex].Clear();
		}
	}
}THduStyleCfgInfo;
//����״̬
typedef struct tagTBrdStateInfo
{
	u16		m_wIndex;
	BOOL32  m_bUsed;  //�����Ƿ�ʹ��
	BOOL32  m_bReg;   //�����Ƿ�ע��
	BOOL32  m_abEqpReg[TP_UMS_BRD_MAXNUM_EQP]; //����ע�����

	tagTBrdStateInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_bUsed = FALSE;
		m_bReg = FALSE;
		for (u16 wIndex = 0; wIndex < TP_UMS_BRD_MAXNUM_EQP; wIndex++)
		{
			m_abEqpReg[wIndex] = FALSE;
		}
	}
}TBrdStateInfo;

typedef struct tagUmsNMServerCfg
{
	BOOL32  m_bIsServerOn;
	u32_ip	m_dwIP;   
	u16		m_wGetSetPort;  
	u16		m_wTrapPort;    
	s8		m_szReadCom[MAX_COMMUNITY_LENGTH];  
	s8		m_szWriteCom[MAX_COMMUNITY_LENGTH];
	u16		m_wHandle;	//����ľ��

	BOOL32	m_bValid;	//�Ƿ�Ϊ��Чֵ

	tagUmsNMServerCfg()
	{
		Clear();
	}

	tagUmsNMServerCfg& operator=(const tagUmsNMServerCfg& tCfg)
	{
		if (&tCfg == this)
		{
			return *this;
		}

		m_dwIP = tCfg.m_dwIP;
		m_wGetSetPort = tCfg.m_wGetSetPort;
		m_wTrapPort = tCfg.m_wTrapPort;
		memcpy(m_szReadCom, tCfg.m_szReadCom, MAX_COMMUNITY_LENGTH);
		memcpy(m_szWriteCom, tCfg.m_szWriteCom, MAX_COMMUNITY_LENGTH);
		m_wHandle = tCfg.m_wHandle;
		m_bValid = tCfg.m_bValid;

		return *this;
	}

	void Clear()
	{
		m_bIsServerOn = FALSE;
		m_dwIP = 0;
		m_wGetSetPort = 0;
		m_wTrapPort = 0;
		memset(m_szReadCom, 0, MAX_COMMUNITY_LENGTH);
		memset(m_szWriteCom, 0, MAX_COMMUNITY_LENGTH);
		m_bValid = FALSE;
	}

	void SetInfo(const TTPNMServerCfg& tCfg)
	{
		m_bIsServerOn = tCfg.bIsServerOn;
		m_dwIP = tCfg.dwNMServerIP;
		m_wGetSetPort = tCfg.wNMGetSetPort;
		m_wTrapPort = tCfg.WNMTrapPort;
		memcpy(m_szReadCom, tCfg.achNMReadCommunity, MAX_COMMUNITY_LENGTH);
		memcpy(m_szWriteCom, tCfg.achNMWriteCommunity, MAX_COMMUNITY_LENGTH);
		m_wHandle = tCfg.wNMServerNO;

		m_bValid = TRUE;
	}
	
	void GetInfo(TTPNMServerCfg& tCfg)
	{
		memcpy(tCfg.achNMReadCommunity, m_szReadCom, MAX_COMMUNITY_LENGTH);
		memcpy(tCfg.achNMWriteCommunity, m_szWriteCom, MAX_COMMUNITY_LENGTH);
		tCfg.bIsServerOn = m_bIsServerOn;
		tCfg.dwNMServerIP = m_dwIP;
		tCfg.wNMGetSetPort = m_wGetSetPort;
		tCfg.wNMServerNO = m_wHandle;
		tCfg.WNMTrapPort = m_wTrapPort;
	}
		
}UmsNMServerCfg;


typedef struct tagTTPVmpRegAck
{
	u32   		m_dwIpAddr;			//UMS���յ�ַ
	u16 		m_wStartPort;		//UMS������ʼ�˿ں�
	
	tagTTPVmpRegAck(){Clear();}
	
	void Clear()	{memset(this, 0, sizeof(tagTTPVmpRegAck));	}
}TTPVmpRegAck;

typedef struct tagTTPVmpStatNtfy
{
	u8		m_byEqpID;
	u8      m_byDecodeNum;    //����ϳ������Խ��뼸·
	u8		m_byEncodeNum;	  //����ϳ������Ա��뼸·
	u8      m_byVMPStyle;	  //����ϳɷ��
	u8		m_byStat;		  //ʹ��״̬ 0-�������� 3-����ʹ��
	tagTTPVmpStatNtfy(){Clear();}
	
	void Clear()	{memset(this, 0, sizeof(tagTTPVmpStatNtfy));}
}TTPVmpStatNtfy;

//�ýṹ�����������滭��ϳɷ����ز���
//�����ɽ���Ԥ���������5�׷��� �洢�������ļ��У��ڿ����ϳ��У����ݷ���ID����ʹ��
typedef struct tagTTPVmpStyleCfgInfo
{
    u8  m_bySchemeId;                   //����id��1��5
	u8	m_byRimEnabled;					//�Ƿ�ʹ�ñ߿�: 0-��ʹ��(Ĭ��) 1-ʹ��;
    u32 m_dwBackgroundColor;            //ͼ�񱳾�ɫ
    u32 m_dwFrameColor;                 //ͼ��߿�ɫ
    u32 m_dwSpeakerFrameColor;          //�����˱߿�ɫ
    u32 m_dwChairFrameColor;            //��ϯ�߿�ɫ 
	u8  m_byFontType;                   // �ϳ���������
	u8  m_byFontSize;					// �ϳ������ֺ�
	u8  m_byAlignment;                  // ���뷽ʽ
	u32 m_dwTextColor;                  // �ϳ�����������ɫ
	u32 m_dwTopicBkColor;               // �ϳ����ⱳ��ɫ
	u32 m_dwDiaphaneity;                // �ϳ�����͸����
	
	//��չ����
	u8 m_byIdleChlShowMode;				// ����ͨ����ʾģʽ VMP_SHOW_GRAY_MODE
	u8 m_byIsDisplayMmbAlias;			// �Ƿ���ʾ������1 Ϊ��ʾ��0Ϊ����ʾ��
	
    s8  m_achSchemeAlias[TP_VMP_SCHEME_CFG_ALIAS];  // ����ϳɷ�������
	
	tagTTPVmpStyleCfgInfo()	{	memset(this, 0, sizeof(tagTTPVmpStyleCfgInfo));	}
}TTPVmpStyleCfgInfo;

typedef struct tagTTPVidParam
{
	EmTpVideoFormat				m_emEncType;		//ͼ��������� h264
	EmTpVideoQualityLevel    	m_emProfileType;	//BP/HP
	u8							m_byFrameRate;		//֡��
	u16							m_wBitRate;			//���������(Kbps)
	u16   						m_wVideoWidth;		//ͼ����(default:1080)
	u16   						m_wVideoHeight;		//ͼ��߶�(default:720)
	tagTTPVidParam()
	{
		memset(this, 0, sizeof(tagTTPVidParam));
		m_emEncType = emTPVH264;
	}
}TTPVidParam;

typedef struct tagTTPVMPMember
{
	u16	m_wEpID;		//ums��᳡ID
	u16 m_wScreenIndx;	//ums��᳡��ϯ����
	u8	m_byStat;		// 0 Ϊ���� 1 Ϊ˫�� 2 Ϊ������
	
	//����
	TTPEncrypt      m_tEncrypt;

	//�غ�
	u16	m_wStaticPayload;				
	u16	m_wDynamicPayload;
	TTPAlias m_tAlias;
	tagTTPVMPMember()
	{
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX; //Ĭ����Чֵ
		m_wScreenIndx = TP_INVALID_INDEX;//Ĭ����Чֵ
		m_byStat = 0; //Ĭ��Ϊ����
	
		m_tEncrypt.Clear();
		
		m_wStaticPayload = MEDIA_TYPE_H264;
		m_wDynamicPayload = MEDIA_TYPE_H264;
	
		m_tAlias.Clear();
	}

	BOOL32 IsDual()
	{
		return 1 == m_byStat;
	}

	tagTTPVMPMember& operator=(const tagTTPVMPMember& tInfo)
	{
		if (&tInfo != this)
		{
			memcpy(this, &tInfo, sizeof(tagTTPVMPMember));
		}
		
		return *this;
	}

}TTPVMPMember;

//
typedef struct tagTTVmpStartParam
{
	EMVmpStyle		m_emVmpStyle;	  //����ϳɷ��
	
	u8				m_byVMPMemberNum;	  //��ǰ�ϳɳ�Ա��Ŀ
	TTPVMPMember	m_atVMPMember[TP_VMP_MAX_IN_CHN_NUM]; //����ϳɳ�Ա
	
	tagTTVmpStartParam()
	{
		memset(this, 0, sizeof(tagTTVmpStartParam));
	}
	
}TTVmpStartParam;

typedef struct tagTTPVMPParam
{
	EMVmpStyle		m_emVmpStyle;	  //����ϳɷ��
	u8				m_byDecodeNum;    //����ϳ������Խ��뼸·
	u8				m_byEncodeNum;	  //����ϳ������Ա��뼸·	

	u8				m_byVMPMemberNum;	  //��ǰ�ϳɳ�Ա��Ŀ
	TTPVMPMember	m_atVMPMember[TP_VMP_MAX_IN_CHN_NUM]; //����ϳɳ�Ա
	
	u8				m_byVmpOutMemberNum;//�ϳɺ�����ͨ������
	TUmsVidFormat	m_atVMPOutMember[TP_VMP_MAX_OUT_CHN_NUM]; //�ϳɺ�����ͨ������
	tagTTPVMPParam()
	{
		m_emVmpStyle = tp_VmpStyle_MidBig;
		m_byDecodeNum = TP_VMP_MAX_IN_CHN_NUM;
		m_byEncodeNum = TP_VMP_MAX_OUT_CHN_NUM;
		
		m_byVMPMemberNum = TP_VMP_MAX_IN_CHN_NUM;
		m_byVmpOutMemberNum = TP_VMP_MAX_OUT_CHN_NUM;

		memset(m_atVMPMember, 0, sizeof(m_atVMPMember));
		memset(m_atVMPOutMember, 0, sizeof(m_atVMPOutMember));
	}
	
	void ClearInOutParam()
	{
		m_emVmpStyle = tp_VmpStyle_MidBig;
		m_byVMPMemberNum = TP_VMP_MAX_IN_CHN_NUM;
		m_byVmpOutMemberNum = TP_VMP_MAX_OUT_CHN_NUM;
		memset(m_atVMPMember, 0, sizeof(m_atVMPMember));
		memset(m_atVMPOutMember, 0, sizeof(m_atVMPOutMember));
	}
}TTPVMPParam;

typedef struct tagTTPVmpRetInfo
{
	u8	m_byEqpID;
	u16	m_wErrCode;
	tagTTPVmpRetInfo()
	{
		memset(this, 0, sizeof(tagTTPVmpRetInfo));
	}
}TTPVmpRetInfo;

typedef struct tagTTPVmpAskFrame
{
	u8	m_byEqpID;
	u8	m_byChanIndx;  //vmp��Ϊ������ͨ��ID
	tagTTPVmpAskFrame()
	{
		memset(this, 0, sizeof(tagTTPVmpAskFrame));
	}
}TTPVmpAskFrame;

typedef struct tagTTPBasVidParam
{
	u8				m_byParamNum;   //��ֵ��eqp��umscall���涼�������������Ч���� ����mcubordmgr����Ϊ��ͨ������������·��
	TUmsVidFormat	m_atVidParam[TP_CONF_MAX_MINOR_VIDEO_RES_NUM];
	tagTTPBasVidParam()
	{
		memset(this, 0, sizeof(tagTTPBasVidParam));
	}

	tagTTPBasVidParam& operator=(const tagTTPBasVidParam& tInfo)
	{
		if (&tInfo != this)
		{
			memcpy(this, &tInfo, sizeof(tagTTPBasVidParam));
		}
		
		return *this;
	}

}TTPBasVidParam;

typedef struct tagTTPBasAskFrame
{
	u8	m_byEqpID;
	u8	m_byChanID;//mcumgr->eqpΪchnID
	tagTTPBasAskFrame()
	{
		memset(this, 0, sizeof(tagTTPBasAskFrame));
	}
}TTPBasAskFrame;

typedef struct tagTBasSndAddr
{
	u8  m_byEqpID;
	u32 m_dwNewDsIP;
	tagTBasSndAddr(){Clear();}
	void Clear()
	{
		m_byEqpID = 0;
		m_dwNewDsIP = INVALID_NODE;
	}
}TBasSndAddr;

typedef struct tagTBasMediaInfo
{
	u8  m_byEqpID;
	u32 m_dwNewDsNode;
	u32 m_dwNewDsIP;
	tagTBasMediaInfo(){Clear();}
	void Clear()
	{
		m_byEqpID = 0;
		m_dwNewDsNode = INVALID_NODE;
		m_dwNewDsIP = 0;
	}
}TBasMediaInfo;


typedef struct tagTCallVidFormat
{
	TUmsVidFormat m_tFormat;
	
	u16     m_wStaticPayload;				
	u16     m_wDynamicPayload;
	tagTCallVidFormat()
	{
		Clear();
	}
	void Clear()
	{
		m_tFormat.Clear();
		
		m_wStaticPayload = MEDIA_TYPE_H264;
		m_wDynamicPayload = MEDIA_TYPE_H264;
	}
	
	tagTCallVidFormat& operator=(const tagTCallVidFormat& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		m_tFormat = tInfo.m_tFormat;
		m_wStaticPayload = tInfo.m_wStaticPayload;
		m_wDynamicPayload = tInfo.m_wDynamicPayload;
		
		return *this;
	}
	BOOL32 IsValid() const	{ return emTPVResEnd != m_tFormat.m_emRes; }
}TCallVidFormat;

typedef struct tagTCallAudFormat
{
	TUmsAudFormat		m_tFormat;
	
	u16     m_wStaticPayload;				
	u16     m_wDynamicPayload;
	
	tagTCallAudFormat()
	{
		Clear();
	}
	void Clear()	
	{ 
		m_tFormat.Clear();
		m_wStaticPayload = MEDIA_TYPE_AACLD;
		m_wDynamicPayload = MEDIA_TYPE_AACLD;
	}
	BOOL32 IsValid() const { return emTPAEnd != m_tFormat.m_emFormat;}
}TCallAudFormat;



//¼��������������Ϣ
typedef struct tagTRecorderCfg
{
	s8		m_achName[MAX_VTR_NAME_LENGTH];  //����
	u8		m_byEqpID;	//�豸ID
	u32_ip	m_dwIP;		//IP

	tagTRecorderCfg()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_dwIP = 0;
		memset(m_achName, 0, MAX_VTR_NAME_LENGTH);
	}

	void SetCfgInfo(const TVcrCfg& tCfg)
	{
		m_dwIP = tCfg.m_dwIP;
		m_byEqpID = tCfg.m_byEqpID;
		memcpy(m_achName, tCfg.m_achName, MAX_VTR_NAME_LENGTH);
	}

	void GetCfgInfo(TVcrCfg& tCfg)
	{
		tCfg.m_dwIP = m_dwIP;
		tCfg.m_byEqpID = m_byEqpID;
		memcpy(tCfg.m_achName, m_achName, MAX_VTR_NAME_LENGTH);
	}

	tagTRecorderCfg& operator=(const tagTRecorderCfg& tCfg)
	{
		if (this == &tCfg)
		{
			return *this;
		}

		m_dwIP = tCfg.m_dwIP;
		m_byEqpID = tCfg.m_byEqpID;
		memcpy(m_achName, tCfg.m_achName, MAX_VTR_NAME_LENGTH);

		return *this;
	}

}TRecorderCfg;

//¼��ע����Ϣ
typedef struct tagTRecRegInfo
{
	u32   		m_dwIpAddr;		//����IP��ַ
	u16 		m_wStartPort;	//������ʼ���ն˿�
	u8  		m_byChannlNum;	//��������ŵ���
	u8			m_byEqpID;

	tagTRecRegInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecRegInfo));
	}

}TRecRegInfo;

typedef struct tagTRecRegAck
{
	u32		m_dwIP;	//ums��ַ
	u16		m_wRcvStartPort;	//��ʼ���ն˿�

	tagTRecRegAck()
	{
		Clear();
	}

	void Clear()
	{
		m_dwIP = 0;
		m_wRcvStartPort = 0;
	}
}TRecRegAck;

typedef struct tagTRecRegStatus
{
	u8		m_byEqpID;		//�豸ID
	BOOL32	m_bRegisted;	//ע��״̬
	u16		m_wStartPort;	//��ʼ�˿�
	u32		m_dwIP;			//�豸IP

	u32		m_dwMediaIP;	//ת����IP
	u32		m_dwMediaNode;	//ת����NODE

	tagTRecRegStatus()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_bRegisted = FALSE;
		m_wStartPort = 0;
		m_dwIP = 0;
		m_dwMediaIP = 0;
		m_dwMediaNode = 0;
	}
}TRecRegStatus;

typedef struct tagTRecUseMedia
{
	u8		m_byEqpID;
	u32		m_dwNode;
	u32		m_dwIP;

	tagTRecUseMedia()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecUseMedia));
	}
}TRecUseMedia;

typedef struct tagTRecStatusNty
{
	u8  	m_byRcvChnnlNum;		//¼���ŵ�������
	u8  	m_byPlayChnnlNum;		//�����ŵ�������
	u8      m_bSupportPublic;       // �Ƿ�֧�ַ���(TRUE: ֧��, FALSE:��֧��)
	u32   	m_dwFreeSpace;        //¼���ʣ����̿ռ�(��λΪMB)
	u32   	m_dwTotalSpace;		//¼����ܴ��̿ռ�(��λΪMB)
	u8		m_byEqpID;

	tagTRecStatusNty()
	{
		Clear();
	}

	void Clear()
	{
		m_byRcvChnnlNum = 0;
		m_byPlayChnnlNum = 0;
		m_bSupportPublic = FALSE;
		m_dwFreeSpace = 0;
		m_dwTotalSpace = 0;
		m_byEqpID = 0;
	}
}TRecStatusNty;

typedef struct tagTRecFileList
{
	u8	m_byEqpID;		//�豸ID
	u16 m_wTotalSize;	//����
	u16	m_wCurSize;	//��ǰ������
	s8	m_achFileName[TP_MAX_RECORDER_PACK_NUM][TP_REC_FILE_LEN];

	tagTRecFileList()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecFileList));
	}
}TRecFileList;

typedef struct tagTRecMdyFileInfo
{
	u8	m_byEqpID;	//�豸ID
	s8	m_szFilelName[TP_REC_FILE_LEN];	//�ļ���

	tagTRecMdyFileInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecMdyFileInfo));
	}

	tagTRecMdyFileInfo& operator=(const tagTRecMdyFileInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_byEqpID = tInfo.m_byEqpID;
		memcpy(m_szFilelName, tInfo.m_szFilelName, TP_REC_FILE_LEN);

		return *this;
	}

}TRecMdyFileInfo;

//����¼����Ϣ
typedef struct tagTStartConfRecInfo
{
	TCallVidFormat	m_tConfFormat;	//�����ʽ
	TCallAudFormat	m_tAudFormat;	
	EmTPEncryptType	m_emEncryptModel;	//����ģʽ: none, aes, des

	TTPTransAddr	m_tConfVidRtcp;
	TTPTransAddr	m_tConfAudRtcp;

	tagTStartConfRecInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tConfFormat.Clear();
		m_tAudFormat.Clear();
		m_emEncryptModel = emTPEncryptTypeNone;
		m_tConfVidRtcp.Clear();
		m_tConfAudRtcp.Clear();
	}

	tagTStartConfRecInfo& operator=(const tagTStartConfRecInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		m_tConfFormat = tInfo.m_tConfFormat;
		m_emEncryptModel = tInfo.m_emEncryptModel;

		return *this;
	}

	void Set(const TRecorderConfInfo& tInfo)
	{
		m_tConfFormat.m_tFormat = tInfo.m_tConfFormat;
	}

}TStartConfRecInfo;

//�ն�¼����Ϣ
typedef struct tagTStartMTRecInfo
{
	u16				m_wMtID;	//
	TCallVidFormat	m_tConfFormat;	//�����ʽ
	TCallAudFormat	m_tAudFormat;
	EmTPEncryptType	m_emEncryptModel;	//����ģʽ: none, aes, des

	TTPTransAddr	m_tConfVidRtcp;
	TTPTransAddr	m_tConfAudRtcp;

	tagTStartMTRecInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wMtID = 0;
		m_tConfFormat.Clear();
		m_tAudFormat.Clear();
		m_emEncryptModel = emTPEncryptTypeNone;
		m_tConfVidRtcp.Clear();
		m_tConfAudRtcp.Clear();
	}

	tagTStartMTRecInfo& operator=(const tagTStartMTRecInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_wMtID = tInfo.m_wMtID;
		m_tConfFormat = tInfo.m_tConfFormat;
		m_tAudFormat = tInfo.m_tAudFormat;
		m_emEncryptModel = tInfo.m_emEncryptModel;

		return *this;
	}

	void Set(const TRecorderMTInfo& tInfo)
	{
		m_wMtID = tInfo.m_wMtID;
	}

}TStartMTRecInfo;

typedef struct tagTStartRecInfo
{
	u8				m_byEqpID;		//�豸ID
	u16				m_wConfID;		//����ID
	u8				m_byChanID;	//����ͨ������
	EmRecorderType	m_emType;
	s8				m_achFileName[TP_REC_FILE_LEN];
	BOOL32			m_bRecDual;		//�Ƿ�¼��˫��
	TCallVidFormat	m_tDualFormat;	//˫����ʽ
	TTPTransAddr	m_tDualRtcp;

	TStartConfRecInfo	m_tConfRecInfo;
	TStartMTRecInfo		m_tMtRecInfo;

	tagTStartRecInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_byChanID = INVALID_REC_CHANNEL;
		m_emType = em_rec_recorder_unknow;
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_bRecDual = FALSE;
		m_tDualFormat.Clear();
		m_tDualRtcp.Clear();
		m_tConfRecInfo.Clear();
		m_tMtRecInfo.Clear();
	}
}TStartRecInfo;

typedef struct tagTRecConfResult
{
	u8		m_byEqpID;		//�豸ID
	u8		m_byChanID;		//����ͨ������
	u8		m_byRecChan;	//¼��������ͨ������

	tagTRecConfResult()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = INVALID_REC_CHANNEL;
		m_byRecChan = 0;
	}
}TRecConfResult;

typedef struct tagTRecPauseInfo
{
	u8		m_byEqpID;
	u8		m_byRecChan;
	
	tagTRecPauseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byRecChan = 0;
	}
}TRecPauseInfo;

typedef struct tagTConfPlayInfo
{
	u8		m_byEqpID;
	u16		m_wConfID;
	BOOL32	m_bPlayInDual;
	s8		m_achFileName[TP_REC_FILE_LEN];
	u8		m_byChanID;

	TCallVidFormat	m_tConfFormat;	//�����ʽ
	TCallVidFormat	m_tDualFormat;	//˫����ʽ
	TCallAudFormat	m_tAudFormat;	
	EmTPEncryptType	m_emEncryptModel;	//����ģʽ: none, aes, des

	TUmsVidFormat	m_tConfInfo;	//�����ʽ
	TUmsVidFormat	m_tDualInfo;	//˫����ʽ


	tagTConfPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_bPlayInDual = FALSE;
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_byChanID = 0;
		m_tConfFormat.Clear();
		m_tDualFormat.Clear();
		m_tAudFormat.Clear();
		m_emEncryptModel = emTPEncryptTypeNone;
		m_tConfInfo.Clear();
		m_tDualInfo.Clear();
	}
}TConfPlayInfo;

typedef struct tagTConfPlayNack
{
	u8		m_byEqpID;
	u16		m_wConfID;
	u8		m_byChanID;
	BOOL32	m_bPlayInDual;
	s8		m_achFileName[TP_REC_FILE_LEN];

	tagTConfPlayNack()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_byChanID = 0;
		m_bPlayInDual = FALSE;
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
	}

}TConfPlayNack;

typedef struct tagTConfPlayAck
{
	u8		m_byEqpID;
	u8		m_byChanID;
	u8		m_byRecChan;
	EmRecFileType m_emFileType;

	EmTpAudioFormat m_emAudFormat;
	EmTpVideoFormat m_emVidFormat;
	EmTpVideoFormat	m_emDVidFormat;
	EmTpVideoResolution m_emVidRes;
	EmTpVideoResolution m_emDVidRes;

	tagTConfPlayAck()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = 0;
		m_byRecChan = 0;
		m_emFileType = em_recfile_unknow;
		m_emAudFormat = emTPAMpegAACLD;
		m_emVidFormat = emTPVH264;
		m_emDVidFormat = emTPVH264;
		m_emVidRes = emTPVResolutionAuto;
		m_emDVidRes = emTPVResolutionAuto;
	}

}TConfPlayAck;

typedef struct tagTMdyFilePlay
{
	u8		m_byEqpID;
	u8		m_byChanID;
	u8		m_byRecChan;
	u16		m_wConfID;

	tagTMdyFilePlay()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = 0;
		m_byRecChan = 0;
		m_wConfID = 0;
	}
}TMdyFilePlay;

typedef struct tagTConfTransInfo
{
	TTPTransAddr	m_tVidRcvAddr;
	TTPTransAddr	m_tAudRcvAddr;
	TUmsVidFormat	m_tConfFormat;

	tagTConfTransInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tVidRcvAddr.Clear();
		m_tAudRcvAddr.Clear();
		m_tConfFormat.Clear();
	}

	tagTConfTransInfo& operator=(const tagTConfTransInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_tVidRcvAddr = tInfo.m_tVidRcvAddr;
		m_tAudRcvAddr = tInfo.m_tAudRcvAddr;
		m_tConfFormat = tInfo.m_tConfFormat;

		return *this;
	}
}TConfTransInfo;

typedef struct tagTMtTransInfo
{
	u16				m_wMtID;
	TTPTransAddr	m_tVidRcvAddr;
	TTPTransAddr	m_tAudRcvAddr;
	TUmsVidFormat	m_tConfFormat;

	tagTMtTransInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wMtID = 0;
		m_tVidRcvAddr.Clear();
		m_tAudRcvAddr.Clear();
		m_tConfFormat.Clear();
	}

	tagTMtTransInfo& operator=(const tagTMtTransInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_wMtID = tInfo.m_wMtID;
		m_tVidRcvAddr = tInfo.m_tVidRcvAddr;
		m_tAudRcvAddr = tInfo.m_tAudRcvAddr;
		m_tConfFormat = tInfo.m_tConfFormat;

		return *this;
	}

}TMtTransInfo;

typedef struct tagTRecConfTrans
{
	u8		m_byEqpID;
	u8		m_byChanID;

	u32		m_dwMediaNode;
	u32		m_dwMediaIP;

	EmRecorderType	m_emRecType;
	BOOL32			m_bRecDual;
	TUmsVidFormat	m_tDualFormat;
	TTPTransAddr	m_tDVidRcvAddr;
	TTPTransAddr	m_tDAudRcvAddr;

	TConfTransInfo	m_tConfInfo;
	TMtTransInfo	m_tMtInfo;

	tagTRecConfTrans()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = INVALID_REC_CHANNEL;
		m_emRecType = em_rec_recorder_unknow;
		m_bRecDual = FALSE;
		m_dwMediaNode = 0;
		m_dwMediaIP = 0;
		m_tDualFormat.Clear();
		m_tDVidRcvAddr.Clear();
		m_tDAudRcvAddr.Clear();
		m_tConfInfo.Clear();
		m_tMtInfo.Clear();
	}

	tagTRecConfTrans& operator=(const tagTRecConfTrans& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_byEqpID = tInfo.m_byEqpID;
		m_byChanID = tInfo.m_byChanID;
		m_emRecType = tInfo.m_emRecType;
		m_bRecDual = tInfo.m_bRecDual;
		m_tDualFormat = tInfo.m_tDualFormat;
		m_tDVidRcvAddr = tInfo.m_tDVidRcvAddr;
		m_tDAudRcvAddr = tInfo.m_tDAudRcvAddr;
		m_tConfInfo = tInfo.m_tConfInfo;
		m_tMtInfo = tInfo.m_tMtInfo;

		return *this;
	}

}TRecConfTrans;

typedef struct tagTPlayTrans
{
	u8		m_byEqpID;
	u8		m_byChanID;
	BOOL32	m_bPlayInDual;

	u32		m_dwMediaIP;
	u32		m_dwMediaNode;

	TTPTransAddr	m_tVidPlayAddr;
	TTPTransAddr	m_tAudPlayAddr;
	TTPTransAddr	m_tDVidPlayAddr;
	s8				m_achFileName[TP_REC_FILE_LEN];

	TUmsVidFormat	m_tConfInfo;	//�����ʽ
	TUmsVidFormat	m_tDualInfo;	//˫����ʽ

	tagTPlayTrans()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = 0;
		m_bPlayInDual = FALSE;
		m_tVidPlayAddr.Clear();
		m_tAudPlayAddr.Clear();
		m_tDVidPlayAddr.Clear();
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_dwMediaIP = 0;
		m_dwMediaNode = 0;
		m_tConfInfo.Clear();
		m_tDualInfo.Clear();
	}

	tagTPlayTrans& operator=(const tagTPlayTrans& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		m_byEqpID = tInfo.m_byEqpID;
		m_byChanID = tInfo.m_byChanID;
		m_bPlayInDual = tInfo.m_bPlayInDual;
		m_tVidPlayAddr = tInfo.m_tVidPlayAddr;
		m_tAudPlayAddr= tInfo.m_tAudPlayAddr;
		m_tDVidPlayAddr = tInfo.m_tDVidPlayAddr;
		memcpy(m_achFileName, tInfo.m_achFileName, TP_REC_FILE_LEN);
		m_tConfInfo = tInfo.m_tConfInfo;
		m_tDualInfo = tInfo.m_tDualInfo;
		m_dwMediaIP = tInfo.m_dwMediaIP;
		m_dwMediaNode = tInfo.m_dwMediaNode;
		
		return *this;
	}

}TPlayTrans;

typedef struct tagTRecChanStatus
{
	u8	m_byEqpID;
	u8	m_byRecChan;
	EmRecChanType	m_emChanType;
	u8	m_byChanState;

	tagTRecChanStatus()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byRecChan = 0;
		m_emChanType = em_rec_unknow_chan;
		m_byChanState = em_state_idle;
	}
}TRecChanStatus;

typedef struct tagTReleaseChanInfo
{
	u8				m_byEqpID;
	EmRecChanType	m_emChanType;
	u16				m_wConfID;

	tagTReleaseChanInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_emChanType = em_rec_unknow_chan;
		m_wConfID = 0;
	}
}TReleaseChanInfo;


typedef struct tagTRecIFrameReq
{
	u8		m_byEqpID;
	u8		m_byRecChan;
	u8		m_abyIFrame[REC_MAX_STREAM_NUM];

	EmRecorderType	m_emRecType;
	u16		m_wConfID;
	u16		m_wMtID;

	tagTRecIFrameReq()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byRecChan = 0;
		memset(m_abyIFrame, 0, REC_MAX_STREAM_NUM);
		m_emRecType = em_rec_recorder_unknow;
		m_wConfID = 0;
		m_wMtID = 0;
	}

}TRecIFrameReq;

//����,��λ��
typedef struct tagTRecProgress
{
	u32		m_dwTotalTime;
	u32		m_dwCurTime;

	tagTRecProgress()
	{
		Clear();
	}

	void Clear()
	{
		m_dwTotalTime = 0;
		m_dwCurTime = 0;
	}
}TRecProgress;

//����ͨ��������Ϣ
typedef struct tagTRecChanProgInfo
{
	u8				m_byEqpID;
	u8				m_byRecChan;
	EmRecChanType	m_emChanType;
	TRecProgress	m_tProgress;

	tagTRecChanProgInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byRecChan = 0;
		m_emChanType = em_rec_unknow_chan;
		m_tProgress.Clear();
	}

}TRecChanProgInfo;

typedef struct tagTHungupRecInfo
{
	u8		m_byEqpID;
	u8		m_byChanID;

	tagTHungupRecInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = INVALID_REC_CHANNEL;
	}
}THungupRecInfo;

typedef struct tagTRecGetVidInfo
{
	u16		m_wConfID;	//����ID
	u16		m_wMtID;	//�᳡ID

	tagTRecGetVidInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = 0;
		m_wMtID = 0;
	}
}TRecGetVidInfo;

//////////////////////////////////////////////////////////////////////////
//apu2��ؽṹ��
typedef struct tagTMixerRegInfo
{
	u8 m_byEqpID;
	u32 m_dwEqpIP;
	u16 m_wStartPort;

	tagTMixerRegInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byEqpID = 0;
		m_dwEqpIP = 0;
		m_wStartPort = 0;

	}
}TMixerRegInfo;

typedef struct tagTMixRegAck
{
	u32   			m_dwIpAddr;			//UMS���յ�ַ
	u16 			m_wStartPort;		//UMS������ʼ�˿ں�
	TUmsRSParam		m_tRsParam;
	tagTMixRegAck() {Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTMixRegAck));
	}
}TMixRegAck;

typedef struct tagTMixerStatNtfy
{
	u8		m_byEqpID;
	s8		m_szAlias[TP_MAXLEN_EQP_ALIAS];		//����
	BOOL32	m_bOnLine;
	u8		m_byStat;
	u8		m_byMixChanNum;
	
	tagTMixerStatNtfy()	{	Clear();}
	void Clear()		{	memset(this, 0, sizeof(tagTMixerStatNtfy));	}
	void SetAlias(const s8* pszAlias)
	{
		strncpy(m_szAlias, pszAlias, sizeof(m_szAlias));
        m_szAlias[sizeof(m_szAlias) - 1] = '\0';
	}
}TMixerStatNtfy;

#define UMS_AUDMIX_N_OUT_NUM 4 
typedef struct tagTStartMix
{
	u8				m_byEqpID;
	u8				m_byMixDepth;
	u8				m_byNNum;
	TUmsAudFormat	m_atAudFmt[UMS_AUDMIX_N_OUT_NUM];

	TTPEncrypt      m_tEncrypt;

	tagTStartMix()	{	Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTStartMix));
	}
}TStartMix;

#define     MAXNUM_MIXER_DEPTH				10  //���������������

typedef struct tagTMixVacResInfo
{
	u8       m_byEqpId;
	u8       m_byVacChanId;  // ��������ͨ������
	u8       m_abyChanId[MAXNUM_MIXER_DEPTH];  // ��������ͨ����������

	tagTMixVacResInfo()
	{
		m_byEqpId = 0xFF;
		m_byVacChanId = 0xFF;
		for (u16 wIndex = 0; wIndex < MAXNUM_MIXER_DEPTH; wIndex++)
		{
			m_abyChanId[wIndex] = 0xFF;
		}
	}

}TMixVacResInfo;

typedef struct tagTTPMixMember
{
	u8				m_byEqpID;
	u8				m_byIndex;
	u16				m_wEpID;
	TTPTransAddr	m_tLocalRtpRcv;
	TTPTransAddr	m_tLocalRtcpRcv;
	
	EmTpAudioFormat     m_emAudFormat;
	EmTPAACSampleFreq	m_emPASampleFreq;
    EmTPAACChnlCfg		m_emPAChnlCfg;	
	u16				    m_wStaticPayload;				
	u16				    m_wDynamicPayload;

	//  n-1��������Ƶ��ʽ
	EmTpAudioFormat     m_emOutAudFormat;
	EmTPAACSampleFreq	m_emOutPASampleFreq;
    EmTPAACChnlCfg		m_emOutPAChnlCfg;	
	u16				    m_wOutStaticPayload;				
	u16				    m_wOutDynamicPayload;

	tagTTPMixMember()	{	Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMixMember));
		m_emAudFormat = emTPAMpegAACLD;
		m_emOutAudFormat = emTPAMpegAACLD;
	}
}TTPMixMember;

typedef struct tagTTPMixDepth
{
	u8	m_byEqpID;
	u8	m_byDepth;
	tagTTPMixDepth()	{	Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMixDepth));
	}
}TTPMixDepth;

typedef struct tagTApu2Cfg
{
	u8			m_byEqpId;
	EMEqpType	m_emEqpType;
	u8			m_byChanNum;
    u16			m_wEqpRcvStartPort;
	u16			m_wUmsRcvStartPort;

	tagTApu2Cfg()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTApu2Cfg));
	}	

}TApu2Cfg;

typedef struct tagTTPApu2CfgAck
{
	EMBrdType	m_emType;
	u8			m_byEqpNum;
	TApu2Cfg	m_atInfo[TP_UMS_BRD_MAXNUM_EQP];
	
	tagTTPApu2CfgAck(){Clear();}
	
	void Clear()	{	memset(this, 0, sizeof(tagTTPApu2CfgAck));	}
	
}TTPApu2CfgAck;



typedef struct tagTStartAudAdapter
{
	u8				m_byEqpID;
	u8				m_byChnlIndx;
	TUmsAudFormat	m_tAudDec;
	TUmsAudFormat	m_atAudEnc[AUD_BAS_MAX_OUT_CHNL_NUM];
	
	TTPEncrypt      m_tEncrypt;
	tagTStartAudAdapter()	{	Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTStartAudAdapter));
	}
}TStartAudAdapter;

typedef struct tagTStartBasAdapter
{
	u8	m_byChnID;  // ��call->eqpʱΪͨ���������е�����  ��eqp->mpu2ʱΪͨ��ID
	u16	m_wStaticPayload; // ��̬�غ�
	u16 m_wDynamicPayload; // ��̬�غ�
	TTPBasVidParam m_tBasParam;
	TTPBasVidParam m_tMaxBasParam;
	EmTpAudioFormat m_emAudForamt;//��Ƶ��ʽ
	TTPEncrypt m_tEncrypt;// ���ܲ���

	tagTStartBasAdapter()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTStartBasAdapter));
	}

}TStartBasAdapter;


typedef struct tagTSaveVmpPlanInfo
{
	u16			   m_wConfID;
	TSaveVmpCfg    m_tCfg;
	u16			   m_wCfgIndex;
	s8			   m_achConfname[TP_MAX_ALIAS_LEN + 1];
	tagTSaveVmpPlanInfo()
	{
		m_wConfID = 0;
		m_tCfg.Clear();
		m_wCfgIndex = 0;
		memset(m_achConfname,0,sizeof(m_achConfname));
	}
}TSaveVmpPlanInfo;

typedef struct tagTTPConfEpParam
{
	TUmsHandle m_tHandle;
	TUmsCallInfo m_tCallInfo;
	//TCallNode m_tCallNode;
	u32  m_dwTimerID;
	u16 m_wConfID ;
	BOOL32 m_bUsed ;
	u16	m_wIndex;
	tagTTPConfEpParam()
	{
		Clear();
	}
	void Clear()
	{
		m_tHandle.Clear();
		m_tCallInfo.Clear();
		m_dwTimerID = 0;
		m_wConfID = TP_INVALID_INDEX;
		m_bUsed = FALSE;
		m_wIndex = TP_INVALID_INDEX;
	}
	BOOL32 IsUsed() { return m_bUsed; }
}TTPConfEpParam;

typedef struct tagTTPConfEpParamArray
{
	TTPConfEpParam m_ConfEpParam[TP_CONF_MAX_EPNUM];
	tagTTPConfEpParamArray()
	{
		Clear();
	}
	void Clear()
	{
		for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_EPNUM; ++ wIndex )
		{
			m_ConfEpParam[wIndex].Clear();
			m_ConfEpParam[wIndex].m_wIndex = wIndex;
		}
	}	
	
}TTPConfEpParamArray;

typedef struct tagTMixSyncChnl
{
	u8       m_abyEqpId[TP_MAX_STREAMNUM];
	u8       m_abyChanId[TP_MAX_STREAMNUM];
	
	tagTMixSyncChnl()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++ wIndex )
		{
			m_abyEqpId[0] = 0xFF;
			m_abyChanId[0] = 0xFF;
		}
	}
}TMixSyncChnl;

typedef struct tagTAudBasSyncChnl
{
	BOOL32	 m_bSet;
	u8       m_byEqpID;
	u8       m_abyChanId[TP_MAX_STREAMNUM];
	
	tagTAudBasSyncChnl()
	{
		m_bSet = TRUE;
		m_byEqpID = 0xFF;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++ wIndex )
		{
			m_abyChanId[wIndex] = 0xFF;
		}
	}
}TAudBasSyncChnl;

#define MAX_CONF_MEDIA_NUM 16

typedef struct tagTMediaNetWorkManger
{
	BOOL32       m_abVaild[MAX_CONF_MEDIA_NUM];
	u32          m_adwMediaNode[MAX_CONF_MEDIA_NUM];
	TIpmaskinfo  m_atInfo[MAX_CONF_MEDIA_NUM];
	
	tagTMediaNetWorkManger()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTMediaNetWorkManger));
	}

	void Add(TIpmaskinfo* ptInfo, u32 wNode)
	{
		for (u16 wIndex = 0; wIndex<MAX_CONF_MEDIA_NUM; wIndex++)
		{
			if (!m_abVaild[wIndex])
			{
				m_abVaild[wIndex] = TRUE;
				memcpy(&m_atInfo[wIndex], ptInfo, sizeof(TIpmaskinfo));
				m_adwMediaNode[wIndex] = wNode;
				return;
			}
		}
		return;
	}

	void Del(u32 wNode)
	{
		for (u16 wIndex = 0; wIndex<MAX_CONF_MEDIA_NUM; wIndex++)
		{
			if (m_abVaild[wIndex] && wNode == m_adwMediaNode[wIndex])
			{
				m_abVaild[wIndex] = FALSE;
				m_adwMediaNode[wIndex] = 0;
				m_atInfo[wIndex].Clear();
			}
		}
		return;
	}

	TIpmaskinfo* Get(u32 wNode)
	{
		for (u16 wIndex = 0; wIndex<MAX_CONF_MEDIA_NUM; wIndex++)
		{
			if (m_abVaild[wIndex] && wNode == m_adwMediaNode[wIndex])
			{
				return &m_atInfo[wIndex];
			}
		}
		return NULL;
	}

}TMediaNetWorkManger;

s8* UmsNodeConfType(EmUmsConfNodeState emType);
s8* UmsNodeType(EmTPEndpointType emType);
s8* UmsCallProto(EmTpConfProtocol emType);

typedef struct tagTSndDsAddr
{
	u16 m_wServiceID;
	u32 m_dwMediaIP;
	u16 m_wStartPort;

	tagTSndDsAddr()
	{
		Clear();
	}
	void Clear()
	{
		m_wServiceID = 0;
		m_dwMediaIP = 0;
		m_wStartPort = 0;
	}
}TSndDsAddr;

enum emVmpMangerStat
{
	VmpManger_Idle,
	VmpManger_Normal,
	VmpManger_Vmp,
	VmpManger_Mpu2tp
};

#define MAX_VMP_NUM 32
typedef struct tagTXmpuVmpManger
{
	u32		m_adwVmpID[MAX_VMP_NUM];
	emVmpMangerStat		m_aemStat[MAX_VMP_NUM]; // 0:offline 1:Idle  2:Take by vmp  3 Take by mpu2-tp
	s8			m_aachEqpAlias[MAX_VMP_NUM][TP_MAXLEN_EQP_ALIAS+1];//�������
	tagTXmpuVmpManger()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuVmpManger));
	}

	u16 GetIndex(u32 dwEqpID)
	{
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < MAX_VMP_NUM; ++wIndex)
		{
			if (dwEqpID == m_adwVmpID[wIndex])
			{
				return wIndex;
			}
		}

		return wIndex;
	}

	BOOL32 CanTask(u32 dwEqpID)
	{
		u16 wIndex = GetIndex(dwEqpID);
		if (wIndex < MAX_VMP_NUM && m_aemStat[wIndex] == VmpManger_Normal)
		{
			return TRUE;
		}
		return FALSE;
	}

	//vmp:TRUE  mpu2-tp:FALSE
	void TaskVmp(u32 dwEqpID, BOOL32 bVmp)
	{
		u16 wIndex = GetIndex(dwEqpID);
		if (wIndex < MAX_VMP_NUM)
		{
			if (bVmp)
			{
				m_aemStat[wIndex] = VmpManger_Vmp;
			}
			else
			{
				m_aemStat[wIndex] = VmpManger_Mpu2tp;
			}
			
		}
	}

	void ReleaseVmp(u32 dwEqpID)
	{
		u16 wIndex = GetIndex(dwEqpID);
		if (wIndex < MAX_VMP_NUM)
		{
			m_aemStat[wIndex] = VmpManger_Normal;
		}
	}

}TXmpuVmpManger;

#endif // _h_tpinnerstruct_h__

