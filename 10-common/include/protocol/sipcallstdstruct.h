#ifndef _SIPCALLSTDSTRUCT_H
#define _SIPCALLSTDSTRUCT_H

#include "kdvcapset.h"
#include "kdvsipcommon.h"
#include "kdvdatanet.h"
#include "kdvsiphandle.h"
#include "sipconfnonstdmsg.h"
#define IsValidHostNameAddr( hostname ) \
	( ( hostname.m_emType == emUrlIpv4 && hostname.m_dwIpAddr ) \
	|| ( hostname.m_emType == emUrlDomain && strlen( hostname.m_achDomainName ) ) ) \
	?TRUE:FALSE \

#define KDV_PORTRANGE_DEFAULT_START		15000
#define KDV_PORTRANGE_DEFAULT_FINISH	65535
#define MAX_SIP_URI_OTHER_PARAM_NUM	10
#define SIP_NONSTD_PRE_HEAD "KdNstd-"

typedef struct tagSipTsxTimeout
{
	/** Transaction T1 timeout, in msec. Default value is PJSIP_T1_TIMEOUT */
	u32 m_dwTsxTimer1;
	/** Transaction T2 timeout, in msec. Default value is PJSIP_T2_TIMEOUT */
	u32 m_dwTsxTimer2;
	/** Transaction completed timer for non-INVITE, in msec. Default value is PJSIP_T4_TIMEOUT */
	u32 m_dwTsxTimer4;
	/** Transaction completed timer for INVITE, in msec. Default value is PJSIP_TD_TIMEOUT. */
	u32 m_dwTsxTimerTD;

	tagSipTsxTimeout()
	{
		Clear();
	}
	void Clear()
	{
		m_dwTsxTimer1 = 500;	//PJSIP_T1_TIMEOUT;
		m_dwTsxTimer2 = 4000;	//PJSIP_T2_TIMEOUT;
		m_dwTsxTimer4 = 5000;	//PJSIP_T4_TIMEOUT;
		m_dwTsxTimerTD= 32000;	//PJSIP_TD_TIMEOUT;
	}
}TSipTsxTimeout;

typedef struct tagTlsCfg
{
	s8      m_achCACertFile[MAX_FILE_PATH_LEN]; //�����CA֤���ļ����������У�飬CACertFile��CACertPath��һ�����ɡ�
	s8      m_achCACertPath[MAX_FILE_PATH_LEN]; //�����CA֤��Ŀ¼���������У�飬CACertFile��CACertPath��һ�����ɡ�
	s8      m_achCertFile[MAX_FILE_PATH_LEN];   //�����֤���ļ�������������ã��ͻ���ѡ�������á�
	s8      m_achKeyFile[MAX_FILE_PATH_LEN];    //private key������������ã��ͻ���ѡ�������á�
	u16     m_wLocalTlsPort;		            //����tls�����˿�,defult��5061

	//֤��Ȼص��ӿڣ������ϲ���֤�����Ϣ
	BOOL32 (PROTO_CALLBACK* cbCertForVerify)(BOOL32 bVerifyServer, s32 nVerifyStatus, const s8 *Cert, u32 dwCertLen);

	tagTlsCfg()
	{
		Clear();
	}

	void Clear()
	{
		memset(this , 0 , sizeof(tagTlsCfg) );
		cbCertForVerify = NULL;
		m_wLocalTlsPort = 5061;
	}
}TTlsCfg;

typedef struct tagSipAdapterCfg
{
	emEndpointType	m_emEndpointType;
	BOOL32  m_bIfRegister;
	u32     m_dwMaxCalls;			//��������
	u32     m_dwLocalIP;            //���˵�ַ.������
	u16     m_wLocalUdpPort;		//����udp������ַ
	u16     m_wLocalTcpPort;		//����tcp������ַ
	BOOL32  m_bManualAck;
	u16     m_wRegClientNum;
	u32     m_dwMaxSendReciveBufferSize;
	s8      m_achProduct[MAX_PRODUCTID_LEN];	//��Ʒ��Ϣ
	s8      m_achTerVer[MAX_PRODUCTID_LEN];		//�汾��Ϣ
	u16		m_wPortRangeStart;    //// tcp or tls port range must be assigned by business, or random allocation
	u16		m_wPortRangeEnd;
	BOOL32	m_bUseIPv6;
	BOOL32	m_bIsh460GW;			//Ĭ��ֵFALSE,5.0gkӦ���ô�ֵΪTRUE,��adapter�оͲ�����kdvdatanet�ĵ���
	BOOL32	m_bUseStdAlias;
	TSipTsxTimeout m_tTsxTimeout;
	ALL_LOG_CALlBACK m_fpAdaptLogCB;

	BOOL32	m_bUseTLS;              //�Ƿ�����TLS����
	TTlsCfg m_tTlsCfg; 

public:
	tagSipAdapterCfg()
	{
		Clear();
		m_wPortRangeStart	= KDV_PORTRANGE_DEFAULT_START;
		m_wPortRangeEnd	= KDV_PORTRANGE_DEFAULT_FINISH;
		m_tTsxTimeout.Clear();
	}
	void Clear()
	{
		memset(this , 0 , sizeof(tagSipAdapterCfg) );
		m_emEndpointType			= emEndpointTypeUnknown;
		m_wRegClientNum				= 2;
		m_dwMaxSendReciveBufferSize = 20480;
		m_bUseIPv6					= FALSE;
		m_bIsh460GW					= FALSE;
		m_bUseStdAlias				= FALSE;
		m_fpAdaptLogCB              = NULL;
		m_bUseTLS                   = TRUE;
		m_tTlsCfg.Clear();
	}
}TSipAdapterCfg;

typedef struct tagStackInitRes
{
	TSipAdapterCfg tSipAdapterCfg;
	BOOL32 bSuc;
	tagStackInitRes()
	{
		memset((void*)&tSipAdapterCfg, 0, sizeof(tSipAdapterCfg));
		bSuc = TRUE;
	}
}TStackInitRes;

extern TStackInitRes  g_tStackInitRes;

typedef struct tagSipAdapterCB
{
	//��ȡ�����²���
	/* pBuf = NULL��dwBufLen = 0 */
	s32 (PROTO_CALLBACK* cbNotifyNewCall)(s32 haCall, s32 hsCall, const void *pBuf, u32 dwBufLen);

	//���п���֪ͨ����
	/* 
	h_call_capsetnotify��CSipCapSet + u8(u8����û�У�����dwBufLen�ж�)
	h_call_connected��h_call_incoming��TSipCallParam
	h_call_disconnected�����йҶ�ԭ��(u8)
	h_call_callidnotify��sip��ͷCall-ID�ַ���
	*/
	s32 (PROTO_CALLBACK* cbNotifyCallCtrlMsg)(s32 haCall, s32 hsCall,u16 wMsgType, const void *pBuf,u32 dwBufLen);

	//�������������(uas)
	/* pBuf = sip��������(EmSipArbitraryMsgType) + �Ƿ���ڷǱ��ͷ(BOOL32) + �Ǳ��ͷ����(u8) 
	+ �Ǳ��ͷ��Чֵ(�Ǳ��ͷ���� * sizeof(TSipHead)) + ���峤��(u32) + �������� */
	s32 (PROTO_CALLBACK* cbNotifyConfCtrlReqMsg)(s32 haCall, s32 hsCall, TSipUasHandle pHandle, const void *pBuf, u32 dwBufLen);

	//�������Ӧ����(uac)
	/* pBuf = sip��������(EmSipArbitraryMsgType) + �Ƿ���ڷǱ��ͷ(BOOL32) + �Ǳ��ͷ����(u8) 
	+ �Ǳ��ͷ��Чֵ(�Ǳ��ͷ���� * sizeof(TSipHead)) + ���峤��(u32) + �������� + ��Ӧ��(s32) */
	s32 (PROTO_CALLBACK* cbNotifyConfCtrlRspMsg)(s32 haCall, s32 hsCall, TSipUacHandle pHandle, const void *pBuf, u32 dwBufLen);

	//ע�����֪ͨ����(uas)
	/*
	pBuf = TRegReqInfo
	*/
	s32 (PROTO_CALLBACK* cbNotifyRegCtrlReqMsg)(TSipUasHandle pHandle, const void *pBuf, u32 dwBufLen);

	//ע�����֪ͨ����(uac)
	/*
	h_sip_state2failed��������(s32)
	h_sip_state2registered:via��receive ip��u32��
	�������ΪNULL
	*/
	s32 (PROTO_CALLBACK* cbNotifyRegCtrlRspMsg)(s32 haReg, s32 hsReg, u16 wMsgType, const void *pBuf, u32 dwBufLen);

	//Զң����֪ͨ����
	s32 (PROTO_CALLBACK* cbNotifyFeccMsg)(s32 hsCall, TFeccStruct tFeccStruct, TTERLABEL tTerSrc, TTERLABEL tTerDst);

	tagSipAdapterCB()
	{
		memset(this, 0, sizeof(tagSipAdapterCB));
	}

} TSipAdapterCB;

enum EmSipChannelReason
{
	emSipChannelReasonBegin,
	emSipChannelDisconnectNormal,
	emSipDualOffLine, 
	emSipChannelDisconnectForce,	//����˫����˫�������ͳɹ������յ��Զ˷�200Ok������Ӧ��
	emSipDualNotSend,	//˫��δ��Э��ջ���ͳ�ȥ����ǰ״̬����ȷ������Э��ջδ���ͣ�
};

//���йҶ�ԭ��
enum EmSipCallDisconReason
{
	emSipDiscon_Busy			= 1,	//�Զ�æ
	emSipDiscon_Normal			,	//�����Ҷ�
	emSipDiscon_Rejected		,	//�Զ˾ܾ�
	emSipDiscon_Unreachable		,	//�Զ˲��ɴ�
	emSipDiscon_Local			,	//����ԭ��
	emSipDiscon_unknown			,	//δ֪ԭ��
	emSipDiscon_custom   ,//δ֪ԭ��

		//TP
	emSipDiscon_AlredayInDualStream ,		//����˫���У��޷���������˫��
	emSipDiscon_Normal_Peer			,        //�Է��Ҷ�
	emSipDiscon_Abnormal			,        //���˵��߹Ҷ�
	emSipDiscon_Abnormal_Peer		,       //�Զ˵��߹Ҷ�
	emSipDiscon_MultiConfOver		,       //���������
	emSipDiscon_ConfAlredayExit		,       //�����Ѿ�����
	emSipDiscon_InvalidDestAddr		,		//��Ч��Ŀ�ĵ�ַ
		
	emSipDiscon_CallFull			,		//���о������(���ܴ��ں��о��δ�ͷŵ�����)
	emSipDiscon_MaxMtNum            ,       //�����к����Ѵ�����

	//����ԭ��
	emSipDisconnect_StreamEncryptKeyNotEqual ,    //��������֧�ֵ��������ܣ���ʽ����Կ����һ��

#ifdef _ENABLE_QUANTUM_PROJECT_
	emSipDisconnect_RegSerUnreachable,			//ע����������ɴ�
	emSipDisconnect_AliasNotFound,				//����������
	emSipDisconnect_GetSignalEncryptKeyFailed,	//��ȡ����������Կʧ��
	emSipDisconnect_AutoGetRegSerAddrFailed,		//IP����ʱ��ȡע���������ַʧ��
	emSipDisconnect_QTDevConnectionBroken,		//���������ն˵���
	emSipDisconnect_QTDevConnectionBroken_peer,		//�Զ������ն˵���
#endif

	//mcu
	emSipDiscon_RmtReconnect = 100,   // ��������ȶԶ˵�  
	emSipDiscon_EncrypeErr,    
	emSipDiscon_AdaptBusy,     
	emSipDiscon_MccDrop,              // ��عҶ�     
	emSipDiscon_ChairDrop,            // ��ϯ�Ҷ�     
	emSipDiscon_MMcuDrop,             // �ϼ�����Ҷ�  
	emSipDiscon_ConfReleaseNoMt,      // ���ն��Զ����-1����   
	emSipDiscon_ConfReleaseNoJoinedMt,// �������ն��Զ����-5����    
	emSipDiscon_ConfReleaseOnlyOneMt, // ��һ�������ն��Զ����-10����  
	emSipDiscon_Exception,            // �쳣�Ҷ�   
	emSipDiscon_MpDisconnect,         //mp����   

	//�ն�
	emSipDiscon_DonotDisturb,         //�����
};

typedef struct tagRegOptionData		//regserver���͵Ĳ�ѯָ��
{
	u32 m_dwtime;						//ע����
	u32 m_ip;							//�ն˵�ip	
	u16 m_port;					    	//�ն˵�port
	tagRegOptionData()
	{
		memset(this, 0, sizeof(tagRegOptionData));
	}
}TRegOptionData;

enum EmRegState
{
	emRegIdle,
	emRegRegistering,
	emRegRegistered,
	emRegFailed,
	emUnReg,
};

enum EmSipCallType
{
	emDirect = 0,					//ֱ�Ӻ���
	emByRedirect,					//ͨ���ض������������
	emByPxy,						//ͨ���������������
};

//����������
enum EmHostNameType
{
	emUrlIpv4,
	emUrlIpv6,
	emUrlDomain,
	emUrlAlias,
	emUrlE164Num,
    emUrlNone,
};

enum EmRegisterReason
{
	emRegNone = 0,
	emRegSuc,          // ע��ɹ�
	emRegFail,         //ע��ʧ��
	emRegNotFound,
	emRegNameDup,      //ע�����������ʱ������������������Ϣ
	emRegTimeOut,      //ע����������ɴ��ʱ
};



enum EmSipConnection
{
	emSipConnectionType = 0,
	emSipTcpConnection,
	emSipUdpConnection,
	emSipSCTPConnection,
	emSipTLSConnection,
};

enum EmSipLevel
{
	emSipCounty,
	emSipCity,
	emSipProvince,
	emSipUnKnown = 255,
};

enum EmSipCapSign
{
	emSipCapBig,
	emSipCapLeft,
	emSipCapSmall = emSipCapLeft,
	emSipCapRight,
	emSipCapEnd = emSipCapRight,
};

enum EmSipMsgType
{
	emSipNone,
	emSipInvite,  
	emSip200OK,
	emSipAck,
};

//�ն���Ϣ����
typedef struct tagTerminalInformation 
{
	TTERLABEL	m_tTerLabel;
	s8			m_achTerID[LEN_TERID + 1];
	
	tagTerminalInformation()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tTerLabel.Clear();
        memset( m_achTerID, 0, sizeof(m_achTerID) );        
	}	
	
	//�����ն˱��
	void SetLabel(const PTTERLABEL ptLabel)
	{
		if (ptLabel != NULL)
		{
			memcpy( &m_tTerLabel, ptLabel, sizeof(m_tTerLabel) );
		}		
	}
	void SetLabel(u8 byMcuNo, u8 byTerNo)
	{
		if (byMcuNo <= LEN_MAXMT_NUM && byTerNo <= LEN_MAXMT_NUM)
		{
			m_tTerLabel.SetTerminalLabel(byMcuNo, byTerNo);
		}
	}
	//����ն˱��
	TTERLABEL& GetTerlabel()
	{
		return m_tTerLabel;
	}
	void GetLabel(u8& byMcuNo, u8& byTerNo)
	{
		m_tTerLabel.GetTerminalLabel( &byMcuNo, &byTerNo );
	}
	//���Mcu��
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}
	//����ն˺�
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}
	
	//�����ն�����
	BOOL32 SetName(const s8* pchName)
	{
		if (pchName != NULL)
		{
			strncpy( m_achTerID, pchName, LEN_TERID + 1 );
			m_achTerID[LEN_TERID] = '\0';
			return TRUE;
		}
		return FALSE;
	}
	//����ն�����
	s8* GetName()
	{
		return m_achTerID;
	}
	
	void operator = (tagTerminalInformation& tTerInfo)
	{
		m_tTerLabel.SetTerminalLabel( tTerInfo.m_tTerLabel.GetMcuNo(), 
			tTerInfo.m_tTerLabel.GetTerNo() );
		
		strncpy( m_achTerID,tTerInfo.GetName(), LEN_TERID + 1);
	}
	
	BOOL32 operator != (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return FALSE;
		}
		return TRUE;
	}
	
	BOOL32 operator == (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return TRUE;
		}
		return FALSE;
	}
}TTERINFO,*PTTERINFO;

//defined in rfc4796
enum EmSipContentAttr
{
	emSipContentNone = 0,
	emSipContentSlides,
	emSipContentSpeaker,
	emSipContentSl,
	emSipContentMain,
	emSipContentAlt,
};

//defined in rfc4145
enum EmSipSetupAttr
{
	emSipSetupBegin = 0,
	emSipActive = 1,
	emSipPassive = 2,
	emSipActpass = 3,
	emSipHoldconn = 4
};

//defined in rfc4145
enum EmSipConnectionAttr
{
	emSipConnectionBegin = 0,
	emSipNew = 1,
	emSipExisting = 2,
};

//defined in rfc4583
enum EmSipFloorcontrolAttr
{
	emSipFloorcontrolBegin = 0,
	emSipClientOnly = 1,
	emSipServerOnly = 2,
	emSipClientServer = 3
};

enum EmCapOrder
{
	emCapOrderBegin,
	emMainAudio,
	emMainVideo,
	emDualAudio, 
	emDualVideo,    
	emBfcp,
	emFecc,
	emCapOrderEnd
};

enum EmSipBfcpSdpAttr
{
	emSipBfcpSdpBegin = 0,
	emSipTcpBfcp,
	emSipTcpTlsBfcp,
	emSipUdpBfcp,
	emSipUdpTlsBfcp,
};

typedef struct PROTO_API tagBfcpFloorInfo
{
	u16 m_wFloorId;
	s32 m_nLabelNum;
	s32 m_anLabelList[MAX_MEDIA_NUM_PER_FLOOR];
	
	void Clear()
	{
		m_wFloorId = 0;
		m_nLabelNum = 0;
		for (s32 i = 0; i < MAX_MEDIA_NUM_PER_FLOOR; i++)
		{
			m_anLabelList[i] = 0;
		}
	}
	tagBfcpFloorInfo()
	{
		Clear();
	}
}TBfcpFloorInfo;

class  PROTO_API CBfcpMediaStream
{
public:
	CBfcpMediaStream();
	
	void Clear();

	void operator = (const CBfcpMediaStream& cCopyMedia);
	
	void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}

	EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}

	void SetBfcpMediaPort( u16 wPort )
	{
		m_wPort = wPort;
	}
	
	u16 GetBfcpMediaPort()
	{
		return m_wPort;
	}

	void SetBfcpFloorcontrolAttr( EmSipFloorcontrolAttr emFloorcontrolAttr )
	{
		m_emFloorcontrolAttr = emFloorcontrolAttr;
	}
	
	EmSipFloorcontrolAttr GetBfcpFloorcontrolAttr()
	{
		return m_emFloorcontrolAttr;
	}

	void SetBfcpSetupAttr( EmSipSetupAttr emSetupAttr )
	{
		m_emSetupAttr = emSetupAttr;
	}

	EmSipSetupAttr GetBfcpSetupAttr()
	{
		return m_emSetupAttr;
	}

	void SetBfcpConnectionAttr( EmSipConnectionAttr emConnectionAttr )
	{
		m_emConnectionAttr = emConnectionAttr;
	}
	
	EmSipConnectionAttr GetBfcpConnectionAttr()
	{
		return m_emConnectionAttr;
	}
	void SetBfcpSdpAttr( EmSipBfcpSdpAttr emBfcpSdpAttr )
	{
		m_emBfcpSdpAttr = emBfcpSdpAttr;
	}
	
	EmSipBfcpSdpAttr GetBfcpSdpAttr()
	{
		return m_emBfcpSdpAttr;
	}
	
	void SetConfId( u32 dwConfId )
	{
		m_dwConfId = dwConfId;
	}

	u32 GetConfId()
	{
		return m_dwConfId;
	}

	void SetUserId( u16 wUserId )
	{
		m_wUserId = wUserId;
	}

	u16 GetUserId()
	{
		return m_wUserId;
	}
	
	void SetFloorNum(s32 nNum)
	{
		m_nFloorNum = nNum;
	}
	
	s32 GetFloorNum()
	{
		return m_nFloorNum;
	}

	void SetFloorInfo(s32 nIndex, TBfcpFloorInfo *ptInfo)
	{
		memcpy(&m_atBfcpFloor[nIndex], ptInfo, sizeof(TBfcpFloorInfo));
	}

	TBfcpFloorInfo* GetFloorInfo(s32 nIndex)
	{
		return &m_atBfcpFloor[nIndex];
	}

	void SetFloorId(s32 nIndex, u16 wFloorId)
	{
		m_atBfcpFloor[nIndex].m_wFloorId = wFloorId;
	}

	//Independent Media IP settings for hole punching mechanism of SIP proxy
	void SetBfcpMediaIP(u32 dwIP)
	{
		m_dwBFCPMediaIP = dwIP;
	}
	
	u32 GetBfcpMediaIP()
	{
		return m_dwBFCPMediaIP;
	}

private:
	EmSipMediaType m_emMediaType;
		
	u16 m_wPort;
	EmSipFloorcontrolAttr m_emFloorcontrolAttr;
	EmSipSetupAttr m_emSetupAttr;
	EmSipConnectionAttr m_emConnectionAttr;
	EmSipBfcpSdpAttr m_emBfcpSdpAttr;

	u32 m_dwConfId;
	u16 m_wUserId;
	s32 m_nFloorNum;	//Floor Number
	TBfcpFloorInfo m_atBfcpFloor[MAX_FLOOR_NUM];	//Floor

	//Independent Media IP settings for hole punching mechanism of SIP proxy
	u32	m_dwBFCPMediaIP;
};

//�ŵ�����
class PROTO_API CSipMediaStream 
{       
public:
    enum { emAVCapNum = 20 };

	 CSipMediaStream();
	 CSipMediaStream( EmSipMediaType emMediaType );

	 void operator = (const CSipMediaStream& cCopyMedia);

	 void Clear();
	 void ClearCapset();

    //����RTP����
	 void SetLocalRtp( u16 wPort ) 
	{ 
		m_tLocalRtp.m_dwIP		= m_dwLocalIp;
		m_tLocalRtp.m_wPort		= wPort;
	}
    //�õ�RTP����
	 TIPTransAddress& GetLocalRtp() 
	{
		return m_tLocalRtp; 
	}

	 void SetRemoteRtp( u32 dwIp, u16 wPort ) 
	{ 
		m_tRemoteRtp.m_dwIP		= dwIp;
		m_tRemoteRtp.m_wPort	= wPort;
	}

	//�õ�RTP����
	 TIPTransAddress& GetRemoteRtp() 
	{
		return m_tRemoteRtp; 
	};

    //����RTCP����
	 void SetLocalRtcp( u16 wPort ) 
	{
		m_tLocalRtcp.m_dwIP		= m_dwLocalIp;
		m_tLocalRtcp.m_wPort	= wPort;
	}

	//����RTCP����
	 void SetLocalRtcp(u32 dwIP, u16 wPort) 
	{
		m_dwLocalIp				= dwIP;
		m_tLocalRtcp.m_dwIP		= m_dwLocalIp;
		m_tLocalRtcp.m_wPort	= wPort;
	}

    //�õ�RTCP����
	 TIPTransAddress& GetLocalRtcp() 
	{
		return m_tLocalRtcp; 
	}
	
	/*
	 //����RTCP����
	 void SetSendRtcp( u32 dwIp, u16 wPort ) 
	{
		m_tSendRtcp.m_dwIP = dwIp; 
        m_tSendRtcp.m_wPort = wPort;
	}
    //�õ�RTCP����
	 TIPTransAddress& GetSendRtcp() 
	{
		return m_tSendRtcp; 
	}
	*/

    //���ü�������
     void SetEncryptType(emEncryptType emType)
	{
		m_emEncryptType = emType; 
	}
    //�õ���������
	 emEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}

	 void SetActivePT( PayloadType  emActivePT )
	{
		m_emActivePT = emActivePT;
	}

	 PayloadType GetActivePT()
	{
		return m_emActivePT;
	}

	 void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}

	 EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}
	 //��������Ƶ������������
	 BOOL32 AddMedia( PayloadType emPayloadType, TKdvCapSet *ptCap );
	 //��������Ƶ������������
	 BOOL32 GetMedia( PayloadType emPayloadType, TKdvCapSet **ptCap, u8 byIndex = 0);
	 void RemoveAllMedia();
	 BOOL32 RemoveMedia(PayloadType emPayloadType, u8 byIndex = 0xFF);

	 BOOL32 IsSupport( PayloadType emPayloadType, TKdvCapSet *ptCap, s32 nIndex = -1, s32 *pnH26XOrder = NULL,BOOL32 bStrictMatch=FALSE);

	 PayloadType GetMediaPT( u8 byIndex )
	{
        if ( byIndex < m_byMediaCount )
			return m_aemMediaPT[byIndex];
		else
			return emPayloadTypeEnd;
	}

	u8 GetMediaCount() 
	{
		return m_byMediaCount;
	}
    //���ü���ͬ����Ϣ
	void SetEncryptSync( TEncryptSync &tSync)
	{ 
		m_tEncryptSync = tSync; 
	}
    //�õ�����ͬ����Ϣ
	TEncryptSync &GetEncryptSync() 
	{ 
		return m_tEncryptSync; 
	} 

	void SetBitRate( s32 nRate )
	{
		m_nBitRate = nRate;
		m_tH261Cap.SetBitRate( nRate );
		m_tH263Cap.SetBitRate( nRate );
		m_tH263plusCap.SetBitRate( nRate );
		m_tMpeg4Cap.SetBitRate( nRate );
		m_tH262Cap.SetBitRate( nRate ); 
		u8 i = 0;
		for (i = 0; i < MAX_H264CAP_NUM; i++)
		{
			if (m_atH264Cap[i].GetBitRate() == 0)
			{
				m_atH264Cap[i].SetBitRate(nRate);
			}
		}
		for (i = 0; i < MAX_H265CAP_NUM; i++)
		{
			if (m_atH265Cap[i].GetBitRate() == 0)
			{
				m_atH265Cap[i].SetBitRate(nRate);
			}
		}
	}

	s32 GetBitRate()
	{
		return m_nBitRate;
	}

	void SetLocalIp( u32 dwIp )
	{
		m_dwLocalIp = dwIp;
	}
	u32 GetLocalIp()
	{
		return m_dwLocalIp;
	}

	BOOL32 IsActive()
	{
        return m_bActive;
	}

	void SetActive( BOOL32 bActive )
	{
		m_bActive = bActive;
	}
	void SetMediaPTArray( s32 nPos, PayloadType emSipPT )
	{
		if ( nPos < m_byMediaCount )
		{
			BOOL32 bFind = FALSE;
			for ( s32 i = 0; i< emAVCapNum; ++i )
			{
				if( m_aemMediaPT[i] == emSipPT && emSipPT != emH264 )
				{
					bFind = TRUE;
				}
				else
					continue;
			}
			if ( !bFind )
			{
				m_aemMediaPT[nPos] = emSipPT;
			}
		}
	}
	void SetMediaCount( s32 nCount )
	{
		m_byMediaCount = nCount;
	}
	
	s32 GetScreenNo()
	{
		return m_nScreenNum;
	}
	void SetScreenNo( s32 nScreenNo )
	{
		m_nScreenNum = nScreenNo;
	}
	s32 GetCapSignNum()
	{
		return m_nCapSignNum;
	}
	void SetCapSignNum( s32 nCapSignNum )
	{
		m_nCapSignNum = nCapSignNum;
	}
	EmSipCapSign GetCapSign( s32 nIndex = 0 )
	{
		return m_aemSipCapSign[nIndex];
	}
	void SetCapSign( EmSipCapSign emCapSign, s32 nIndex = 0 )
	{
		m_aemSipCapSign[nIndex] = emCapSign;
	}
	void SetAudMix(BOOL32 bAudMix)
	{
		m_bAudMix = bAudMix;
	}
	BOOL32 IsAudMix()
	{
		return m_bAudMix;
	}
	void SetTpRtpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_atTpRtpAddr[nIndex].m_dwIP = dwIP;
		m_atTpRtpAddr[nIndex].m_wPort = wPort;
	}
	TIPTransAddress& GetTpRtpAddress( s32 nIndex ) 
	{
		return m_atTpRtpAddr[nIndex]; 
	}
	void SetTpRtcpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_atTpRtcpAddr[nIndex].m_dwIP = dwIP;
		m_atTpRtcpAddr[nIndex].m_wPort = wPort;
	}
	TIPTransAddress& GetTpRtcpAddress( s32 nIndex ) 
	{
		return m_atTpRtcpAddr[nIndex]; 
	}

	void SetSipContentAttr( EmSipContentAttr emSipContentAttr)
	{
		m_emSipContent = emSipContentAttr;
	}

	EmSipContentAttr GetSipContentAttr()
	{
		return m_emSipContent;
	}

	void SetSipMediaLabel( s32 nSipMediaLabel )
	{
		m_nSipMediaLabel = nSipMediaLabel;
	}

	s32 GetSipMediaLabel()
	{
		return m_nSipMediaLabel;
	}
	
	void SetH264CapsetNumber( u8 byNum )
	{
		m_byH264CapNum = byNum;
	}
	
	u8 GetH264CapsetNumber()
	{
		return m_byH264CapNum;
	}

	void AddH264CapsetNumber()
	{
		m_byH264CapNum++;
	}

	void SetH264CapsetOrder( s32 nIndex, u8 byOrder )
	{
		m_abyH264CapOrder[nIndex] = byOrder;
	}
	
	u8 GetH264CapsetOrder( s32 nIndex )
	{
		return m_abyH264CapOrder[nIndex+1];
	}

	void SetExtmapAudioLevel(emSendRecvAttr emDirect, u8 byId, BOOL32 bVadOn)
	{
		m_emAudLvlDirect = emDirect;
		m_byAudLvlId = byId;
		m_bAudLvlVadOn = bVadOn;
	}

	void GetExtmapAudioLevel(emSendRecvAttr &emDirect, u8 &byId, BOOL32 &bVadOn)
	{
		emDirect = m_emAudLvlDirect;
		byId = m_byAudLvlId;
		bVadOn = m_bAudLvlVadOn;
	}

	// H.265 video capabilities
	void	SetH265CapsetNumber(u8 byNum){ m_byH265CapNum = byNum;}
	u8		GetH265CapsetNumber(){return m_byH265CapNum;}
	void	AddH265CapsetNumber(){m_byH265CapNum++;}
	void	SetH265CapsetOrder(s32 nIndex, u8 byOrder){m_abyH265CapOrder[nIndex] = byOrder;}
	u8		GetH265CapsetOrder(s32 nIndex){return m_abyH265CapOrder[nIndex];}

	void SetBitratePercent(u8 byPercent){ m_byBitratePercent = byPercent; }
	u8 GetBitratePercent(){ return m_byBitratePercent; }

#ifdef _KDV_SRTP_SUPPORT_
	//srtp
	void SetSrtpMediaSetting(TSrtpMediaSetting *ptSetting)
	{
		m_tSrtpSetting = *ptSetting;
	}
	TSrtpMediaSetting *GetSrtpMediaSetting()
	{
		return &m_tSrtpSetting;
	}
#endif
	
private:
	BOOL32				m_bActive;
	EmSipMediaType		m_emMediaType;
  
	TIPTransAddress		m_tLocalRtp;
	TIPTransAddress		m_tLocalRtcp;		//combine m_tSendRtcp with m_tRecvRtcp into a new TTransAddress m_tLocalRtcp, double checked with Lijing
	TIPTransAddress		m_tRemoteRtp;

	PayloadType			m_aemMediaPT[emAVCapNum];
	u8					m_byMediaCount;

	TKdvVideoCap		m_tH261Cap;
	TKdvVideoCap		m_tH263Cap;
	TKdvVideoCap		m_tH263plusCap;
	TKdvVideoCap		m_tMpeg4Cap;
	TKdvVideoCap		m_tH262Cap;    
	u8					m_byH264CapNum;	
	u8					m_abyH264CapOrder[MAX_H264CAP_NUM];
	TKdvH264VideoCap	m_atH264Cap[MAX_H264CAP_NUM];

	TKdvAudioCap		m_tG711u;
	TKdvAudioCap		m_tG711a;
	TKdvAudioCap		m_tG722;
	TKdvAudioCap		m_tG728;
	TKdvAudioCap		m_tG729;
	TKdvAudioCap		m_tMP3;
	TKdvAudioCap		m_tG723;
	TKdvAudioCap		m_tG719;
	TKdvTelephoneEventCap		m_tTelephoneEvent;
	TKdvG7231Cap		m_tG7231;
	 
	TKdvG7221Cap		m_atG7221[MAX_G7221CAP_NUM];
	u8					m_abyG7221MediaToCap[emAVCapNum];
	u8					m_byG7221CapNum;

	TKdvOpusCap			m_tOpus;

	TKdvAACCap			m_atAaclc[MAX_AAC_CAP_NUM];		//aaclc����
	u8					m_bylcNum;							//�����С
	u8					m_abylcMediaToCap[emAVCapNum];		//�ǵ�ǰm_byMediaCount������ ��Ӧ��aaclc���������
	TKdvAACCap			m_atAacld[MAX_AAC_CAP_NUM];
	u8					m_byldNum;
	u8					m_abyldMediaToCap[emAVCapNum];

	// H.265 video capabilties
	TKdvH265VideoCap	m_atH265Cap[MAX_H265CAP_NUM];
	u8					m_byH265CapNum;
	u8					m_abyH265CapOrder[MAX_H265CAP_NUM];

	PayloadType			m_emActivePT;
	emEncryptType		m_emEncryptType;	//��������
	TEncryptSync		m_tEncryptSync;		//master�����ô˽ṹ
	s32					m_nBitRate;
	u32					m_dwLocalIp;
	
	//��������
	s32					m_nScreenNum;
	s32					m_nCapSignNum;
	BOOL32				m_bAudMix;			//�Ƿ����
	EmSipCapSign		m_aemSipCapSign[emSipCapEnd];
	TIPTransAddress		m_atTpRtpAddr[emSipCapEnd];
	TIPTransAddress		m_atTpRtcpAddr[emSipCapEnd];

	//����BFCP�����content��label����
	EmSipContentAttr    m_emSipContent;
	s32                 m_nSipMediaLabel;

	//extmap��չ��audio-level��
	emSendRecvAttr m_emAudLvlDirect;
	u8 m_byAudLvlId;
	BOOL32 m_bAudLvlVadOn;
	
	//�ն�ƽ̨��ͨ�Ǳ꣨������ʣ�
	u8 m_byBitratePercent;
#ifdef _KDV_SRTP_SUPPORT_
	//srtp
	TSrtpMediaSetting	m_tSrtpSetting;
#endif
};

typedef struct PROTO_API tagMediaLine
{
	emSendRecvAttr	m_emAttr;
	u8				m_bySndPos;
	u8				m_byRcvPos;
	tagMediaLine()
	{
		m_emAttr	= emSendRecvBegin;
		m_byRcvPos	= 0;
		m_bySndPos	= 0;
	}
}tMediaLine; 

/************************************
* �������ṹ
* Ŀǰ����Ƶ֧��:G711u(64k),G711a(64k),G722(64k),G7231,G728,G729.
* Ŀǰ����Ƶ��һ·֧��:h261,h263,h264,mpeg4,h262
* ��һ·֧��:,h264,h263+  
* 
 *************************************/
#define SIP_MAX_AUDIO_STREAM_COUNT 4
#define SIP_MAX_VIDEO_STREAM_COUNT 4
//Jacky: Max Media Num
//		SIP_MAX_VIDEO_STREAM_COUNT + SIP_MAX_AUDIO_STREAM_COUNT + BFCP(1) + FECC(1) + DUAL AUDIO(1) + DUAL VIDEO(1)
#define SIP_MAX_MEDIA_NUM (SIP_MAX_VIDEO_STREAM_COUNT*4 + SIP_MAX_AUDIO_STREAM_COUNT*4 +2)  

class PROTO_API CAudVidCapSet
{
public:
	CAudVidCapSet();

public:
	void Clear( BOOL32 bOnlyComCap = FALSE );

	/*whether media support some format*/
	BOOL32 IsSupportCapset( PayloadType emPayloadType, TKdvCapSet *ptSupportCapset, BOOL32 bRecv, s32 nVideoSequence=0 );
	/*add one format to a media*/
	void AddCapSetToMedia( PayloadType emPayloadType, TKdvCapSet *ptCap, BOOL32 bRecv, int nVideoSequence = 0 );
	/*determine which payload to be transmitted*/
	void SetMediaActivePT( PayloadType emPayloadType, BOOL32 bRecv, int nVideoSequence = 0  );

	s32 GetVideoSendStreamCount(){ return m_nVideoSendStreamCount;	}
	s32 GetVideoRecvStreamCount(){ return m_nVideoRecvStreamCount;	}

	void SetVideoRecvStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoRecvStreamCount = SIP_MAX_VIDEO_STREAM_COUNT;
			return;
		}
		m_nVideoRecvStreamCount = nCount;
	}

	void SetVideoSendStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoSendStreamCount = SIP_MAX_VIDEO_STREAM_COUNT;
			return;
		}
		m_nVideoSendStreamCount = nCount;
	}

	void IncreasingSendVideoStream()
	{ 
		if ( m_nVideoSendStreamCount + 1 <= SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoSendStreamCount++; 
		}
	}

	void IncreasingRecvVideoStream()
	{ 
		if ( m_nVideoRecvStreamCount + 1 <= SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoRecvStreamCount++; 
		}
	}

	s32 GetAudioSendStreamCount(){ return m_nAudioSendStreamCount;}
	s32 GetAudioRecvStreamCount(){ return m_nAudioRecvStreamCount;}

	void SetAudioRecvStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioRecvStreamCount = SIP_MAX_AUDIO_STREAM_COUNT;
			return;
		}
		m_nAudioRecvStreamCount = nCount;
	}

	void SetAudioSendStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioSendStreamCount = SIP_MAX_AUDIO_STREAM_COUNT;
			return;
		}
		m_nAudioSendStreamCount = nCount;
	}

	void IncreasingSendAudioStream()
	{ 
		if ( m_nAudioSendStreamCount + 1 <= SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioSendStreamCount++; 
		}
	}

	void IncreasingRecvAudioStream()
	{ 
		if ( m_nAudioRecvStreamCount + 1 <= SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioRecvStreamCount++; 
		}
	}

	u32 GetMediaLinePosbySendPos(u8 bySndPos, BOOL32 bVideo = TRUE)
	{
		if(bVideo)
		{
			for(u32 dwIndex = 0; dwIndex< m_dwVideoNum; dwIndex++)
			{
				if(m_atVidSndRcv[dwIndex].m_emAttr == emSendOnly || m_atVidSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(bySndPos == m_atVidSndRcv[dwIndex].m_bySndPos )
						return dwIndex;	
				}
			}
		}
		else
		{
			for(u32 dwIndex = 0; dwIndex< m_dwAudioNum; dwIndex++)
			{
				if(m_atAudSndRcv[dwIndex].m_emAttr == emSendOnly || m_atAudSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(bySndPos == m_atAudSndRcv[dwIndex].m_bySndPos )
						return dwIndex;	
				}
			}
		}

		return -1;
	}

	u32 GetMediaLinePosbyRecvPos(u8 byRecvPos, BOOL32 bVideo = TRUE)
	{
		if(bVideo)
		{
			for(u32 dwIndex = 0; dwIndex < m_dwVideoNum; dwIndex++)
			{
				if(m_atVidSndRcv[dwIndex].m_emAttr == emRecvOnly || m_atVidSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(byRecvPos == m_atVidSndRcv[dwIndex].m_byRcvPos )
						return dwIndex;	
				}
			}
		}
		else 
		{
			for(u32 dwIndex = 0; dwIndex< m_dwAudioNum; dwIndex++)
			{
				if(m_atAudSndRcv[dwIndex].m_emAttr == emRecvOnly || m_atAudSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(byRecvPos == m_atAudSndRcv[dwIndex].m_byRcvPos )
						return dwIndex;	
				}
			}
		}

		return -1;
	}

	tMediaLine* GetMediaLine( u32 dwCount, BOOL32 bIfVideo = FALSE )
	{
		if ( bIfVideo)
		{
			if ( dwCount >= SIP_MAX_VIDEO_STREAM_COUNT * 2 )
				return NULL;
			else
				return &(m_atVidSndRcv[dwCount]);
		}
		else
		{
			if ( dwCount >= SIP_MAX_AUDIO_STREAM_COUNT * 2 )
				return NULL;
			else
				return &(m_atAudSndRcv[dwCount]);
		}
	}

	BOOL32 SetMediaLine( u32 dwCount, emSendRecvAttr emAttr, u8 bySndPos, u8 byRcvPos, BOOL32 bIfVideo = FALSE )
	{
		if ( bIfVideo)
		{
			if ( dwCount >= SIP_MAX_VIDEO_STREAM_COUNT * 2 )
				return FALSE;
			else
			{
				m_atVidSndRcv[dwCount].m_emAttr = emAttr;
				m_atVidSndRcv[dwCount].m_bySndPos = bySndPos;
				m_atVidSndRcv[dwCount].m_byRcvPos = byRcvPos;
			}
		}
		else
		{
			if ( dwCount >= SIP_MAX_AUDIO_STREAM_COUNT*2 )
				return FALSE;
			else
			{
				m_atAudSndRcv[dwCount].m_emAttr = emAttr;
				m_atAudSndRcv[dwCount].m_bySndPos = bySndPos;
				m_atAudSndRcv[dwCount].m_byRcvPos = byRcvPos;
			}
		}

		return TRUE;
	}

	BOOL32 SetAudioNum(u32 AudioNum)
	{
		if ( AudioNum > SIP_MAX_AUDIO_STREAM_COUNT * 2 )
			return FALSE;
		m_dwAudioNum = AudioNum;

		return TRUE;
	}

	u32 GetAudioNum()
	{
		return m_dwAudioNum;
	}

	BOOL32 SetVideoNum(u32 VideoNum)
	{
		if ( VideoNum > SIP_MAX_VIDEO_STREAM_COUNT * 2 )
			return FALSE;
		m_dwVideoNum = VideoNum;
			return TRUE;
	}

	u32 GetVideoNum()
	{
		return m_dwVideoNum;
	}

	/*get some media stream of a dialog*/
	CSipMediaStream* GetSendMediaStream( EmSipMediaType emMediaType, s32 nSequence = 0);
	CSipMediaStream* GetRecvMediaStream( EmSipMediaType emMediaType, s32 nSequence = 0);
	BOOL32 SetLocalVedioIP( u32 dwIp, s32 nSequence );
	BOOL32 SetLocalAudioIP( u32 dwIp, s32 nSequence );

private:
	//Audio Stream
	CSipMediaStream		m_acAudioSendStream[SIP_MAX_AUDIO_STREAM_COUNT];
	s32					m_nAudioSendStreamCount;
	CSipMediaStream		m_acAudioRecvStream[SIP_MAX_AUDIO_STREAM_COUNT];
	s32					m_nAudioRecvStreamCount;
	tMediaLine			m_atAudSndRcv[SIP_MAX_AUDIO_STREAM_COUNT * 2];
	u32					m_dwAudioNum;

	//Video Stream
	CSipMediaStream		m_acVideoSendStream[SIP_MAX_VIDEO_STREAM_COUNT];
	s32					m_nVideoSendStreamCount;
	CSipMediaStream		m_acVideoRecvStream[SIP_MAX_VIDEO_STREAM_COUNT];
	s32					m_nVideoRecvStreamCount;
	tMediaLine			m_atVidSndRcv[SIP_MAX_VIDEO_STREAM_COUNT * 2];
	u32					m_dwVideoNum;
};

class PROTO_API CSipCapSet
{
public:
	CSipCapSet();

public:
	void Clear();

	void SetMainCapset(CAudVidCapSet *ptCap);
	CAudVidCapSet *GetMainCapset();

	void SetDualCapset(CAudVidCapSet *ptCap);
	CAudVidCapSet *GetDualCapset();

	void SetBfcpMedia(CBfcpMediaStream *ptBfcpMedia);
	CBfcpMediaStream* GetBfcpMedia	();

	void SetFeccMedia(CFeccMediaStream *ptFeccMedia);
	CFeccMediaStream* GetFeccMedia();

	void SetSipMsgType( EmSipMsgType emType );
	EmSipMsgType GetSipMsgType();

	/*set dialog bandwidth*/
	void SetBandwidth( s32 nBandWidth );
	s32  GetBandwidth();

	void SetLocalIp( u32 dwIp );
	u32  GetLocalIp();
	
	void SetCapOrder(s32 nIndex, EmCapOrder emOrder);
	EmCapOrder GetCapOrder(s32 nIndex);

	void SetNatType(s32 nNatType);

	s32 GetNatType();

	void SetPeerVendorId(EmVendorProductId emVendorId);

	EmVendorProductId GetPeerVendorId();

private:
	//Main Stream
	CAudVidCapSet		m_cMainCapset;
	//Slide Stream
	CAudVidCapSet		m_cDualCapset;
	//BFCP Stream
	CBfcpMediaStream	m_cBfcpStream;
	//FECC Stream
	CFeccMediaStream	m_cFeccStream;
	//SIP Message type(invite/200OK/ack)
	EmSipMsgType		m_emSipType;

	s32					m_nBandWidth;
	u32					m_dwLocalIp;
	s32					m_nNatType;
	EmCapOrder			m_aemOrders[SIP_MAX_MEDIA_NUM];
	EmVendorProductId   m_emPeerVendorId;
};

typedef struct PROTO_API tagHostName
{
	EmHostNameType   m_emType;                   //����������
	s8				 m_achDomainName[LEN_DOMAINNAME + 1];//����
	u32              m_dwIpAddr;                   //IP��ַ

	void Clear()
	{
		memset(this, 0, sizeof(tagHostName));
	}
	tagHostName()
	{
		Clear();
	}
}THostName;

typedef struct PROTO_API tagSipAttr
{
	s8	m_achName[MAX_SDP_ATTR_NAME_LEN];	/**< Param/header name.	    */
	s8	m_achValue[MAX_SDP_ATTR_VALUE_LEN];	/**< Param/header value.    */

	void Clear()
	{
		memset(m_achName, 0, sizeof(m_achName));
		memset(m_achValue, 0, sizeof(m_achValue));
	}
	tagSipAttr()
	{
		Clear();
	}
} TSipAttr;

typedef TSipAttr TSipHead;
typedef TSipAttr TSdpAttr;

typedef struct PROTO_API tagSipUrl
{
	s8			m_achDisplayName[LEN_USERNAME + 1]; 
	s8			m_achUserName[LEN_USERNAME + 1];	//����   
	s8			m_achPassword[LEN_PASSWORD + 1];	//����
	s8  		m_achAuthUser[LEN_USERNAME+1];		//Username for digest authorization process
    THostName	m_tHostName;						//������
	u16			m_wPort;							//�˿� 
	u8			m_byParamNum;
	TSipAttr	m_atParam[MAX_SIP_URI_OTHER_PARAM_NUM];

public:
	tagSipUrl()
	{
		memset( this, 0, sizeof(tagSipUrl) );
	}
}TSipUrl;

/*
// ���е�ַ����
enum CallAddrType
{
	emcat_err	= -1,
	emcat_ip	= 1,	//IP����
	emcat_alias	= 2,	//��������
	emcat_e164	= 3,	//E164����
};
*/

//������ַ
typedef struct PROTO_API tagAliasTransAddress
{
	s8  m_achAlias[LEN_ALIAS + 1];			//h323-Id ��������λΪ��
	
	tagAliasTransAddress()
	{
		Clear();
	}
	
	void Clear()
	{
		memset( m_achAlias, 0, sizeof(m_achAlias) );
	}
	
	//���ñ���
	BOOL32 SetAliasAddr( const s8* pAlias )
	{
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		s32 nLen = Minimum( (s32)strlen(pAlias), (s32)LEN_ALIAS );
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		return TRUE;
	}	
	
	//��ñ���
	s8* GetAliasName()  
	{
		return m_achAlias;	
	}
}TAliasTransAddress, *PTAliasTransAddress;

//����ʱ�ı�����ַ
typedef struct PROTO_API tagSipTransAddress
{
	CallAddrType       m_emType;		//��������
	TIPTransAddress	    	m_tNetAddr;		//IP����ʱʹ��		
	TAliasTransAddress		m_tAlias;		//��������ʹ��
	
	tagSipTransAddress()
	{
		Clear();
	}
	void Clear()
	{
		m_emType = emcat_err;
		m_tNetAddr.Clear();
		m_tAlias.Clear();
	}
	
}TSipTransAddress, *PTSipTransAddress;

typedef enum
{
    emCreate,
	emJoin,
	emInvite,
	emCapabilityNegotiation,
	emCallIndependentSupplementaryService,
	emLastCG
} EmConfGoalType;


typedef struct PROTO_API tagTSipEncryptKey
{
	emEncryptType m_emEncryptType;
	u8 m_byLen;   //��Կ����
	u8 m_abyKey[MAX_SIP_ENCRYPT_KEY_LEN]; //��Կ����
	
public:
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipEncryptKey) );
		m_emEncryptType = emEncryptTypeNone;
	}
	tagTSipEncryptKey()
	{
		Clear();
	}
	void Print()
	{
		OspPrintf(TRUE, FALSE, "TSipEncryptKey:EncryptType=%d, m_byLen=%d, key:", m_emEncryptType, m_byLen);
		s32 nLen = Minimum(m_byLen, LEN_AES_KEY);
		if ( emEncryptTypeNone != m_emEncryptType )
		{
			for (int i = 0; i < nLen; i++)
			{
				OspPrintf(TRUE, FALSE, "%c", m_abyKey[i]);
				if ( i == (nLen - 1))
				{
					OspPrintf(TRUE, FALSE, "\n");
				}
			}
		}		
	}
}TSipEncryptKey;

//������в���
typedef struct PROTO_API tagSipCallParam 
{
	BOOL32				m_bCreateConf;
	EmConfGoalType		m_emConfGoalType;  						//�����Ŀ������
	u32					m_dwCallRate;							//��������	(kbps)
	TSipUrl				m_tCalledAddress;						//���е�ַ
	TSipUrl				m_tCallingAddress;						//���е�ַ
	EmSipCallType		m_emCallType;							//�������� (direct|by pxy|by redirect)
    THostName			m_tServerAddr;							//pxy server| redirect server    
	u16					m_wServerPort;
	EmSipConnection		m_emSipConnection;						//������������ tcp udp tls default udp
	s32					m_nProductIdSize;
	u8					m_abyProductId[MAX_PRODUCTID_LEN];		//��Ʒ��
	s32					m_nVerIdSize;
	u8					m_abyVersionId[MAX_PRODUCTID_LEN];		//�汾��
	emEndpointType		m_emSipTerType;
	
	//��������
	EmSipLevel			m_emSipLevel;							//����
	s32					m_nScreenNum;                           //����
	u8					m_abyConfId[LEN_GUID];		            //�����,����16 octet
	u16					m_wConfId;
	u8					m_byTerNum;								//�����ն˸���
	TSipTransAddress	m_atList[MAX_TERMINAL_NUM];				//�����ն��б�
	TSipConfInfo		m_tConfInfo;							//������Ϣ
	
	BOOL32				m_bNatCall;								//�����Ƿ��nat
	BOOL32				m_bAddTpAttr;							//�Ƿ����TP���ԣ�sip��ͷ��sdp��������TP�Ǳ����ԣ�
	BOOL32				m_bSupportMmcu;							//�Ƿ�֧�ֺϲ�����
	
	s8 m_achCallId[MAX_NUM_CALLID];								//CALL-ID	
	TSipEncryptKey	    m_tStreamKey;								//��m_tStreamKey.m_emEncryptType=emEncryptTypeNone ��ʾ����������

    EmVendorProductId   m_emVendorId;
	EmVendorProductId   m_emPeerVendorId;

	u8 m_byNonStdHdrNum;	//�Ǳ�sip��ͷ����
	TSipHead m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	 //�Ǳ�sip��ͷ

#ifdef _KDV_SRTP_SUPPORT_
	//srtp params
	EmSrtpMode			m_emSrtpMode;	//None��Optional��Mandatory
#endif
	TSipUrl				m_tReqUri;
#ifdef _ENABLE_QUANTUM_PROJECT_
	BOOL32 m_bSignalEncrypt;	//���������Ƿ����
	EmQtRetReason	m_emQtRetReason;
	TQtCallParam	m_tQtCallParam;
#endif
	s8 m_achPassword[LEN_PASSWORD+1]; //��֤����
	s8 m_achUsername[LEN_USERNAME+1];	//��֤�û���
	s8 m_achDomainName[LEN_DOMAINNAME+1];	//����

public:
	tagSipCallParam()
	{
		memset(this, 0, sizeof(tagSipCallParam));
		m_tStreamKey.Clear();
		m_emSipConnection = emSipTcpConnection;
		m_emVendorId = emKeda;
		m_emPeerVendorId = emKeda;
#ifdef _KDV_SRTP_SUPPORT_
		m_emSrtpMode = emSrtpModeNone;
#endif
#ifdef _ENABLE_QUANTUM_PROJECT_
		m_tQtCallParam.m_emKeyFrequency = EmQtFrequencyEveryConf;
#endif
	}
	
	//���û����
	void SetConfId(const u8* pchConfId, u8 byLen)
	{
		if (pchConfId == NULL || (s32)byLen <= 0)
		{
			return;
		}
		
		s32 nReal = Minimum(Maximum((s32)LEN_1, (s32)byLen), (s32)LEN_GUID);
		memcpy(m_abyConfId, pchConfId, nReal);
	}
	
}TSipCallParam;

typedef struct tagSipNodeInfo
{
    EmVendorProductId 	m_emVendorId;
	BOOL32     			m_bMt;
	s8       			m_achProductId[MAX_PRODUCTID_LEN + 1];
	s8       			m_achVersion[MAX_PRODUCTID_LEN + 1];
	
	public:	    
		tagSipNodeInfo()
		{ 
			Clear();
		}
		
		void Clear()
		{
			memset(this, 0, sizeof(tagSipNodeInfo));
		}
}TSipNodeInfo;

typedef struct tagSdpSessionInfo
{
    s8      m_achSessionName[SESSION_NAME_LEN + 1];
    //origin
    s8      m_achOriginSID[SESSION_ID_LEN + 1];         //SessionId
    s8      m_achOriginUserName[MAX_PRODUCTID_LEN + 1];    //User name
    //s8      m_achOriginVer[SESSION_VERSION_LEN+1];          //session Version
	s32     m_nOriginVer;
    s8      m_achOriginAddress[128];    //Address-url
    s8      m_achTerVer[SESSION_INFO_LEN + 1];
    
    u32     m_dwBandWidth;
    u32     m_dwStartTime;
    u32     m_dwEndTime;
    u32     m_dwIP;
public:	    
	tagSdpSessionInfo(){ memset(this, 0, sizeof(tagSdpSessionInfo));}
} TSdpSessionInfo;

enum EmSipEndpointType
{
	emSipEndpointTypeUnknown  = 0, 
	emSipEndpointTypeCNS	  = 0x01,
	emSipEndpointTypeUMS	  = 0x02,
	emSipEndpointTypeRegister = 0x04
};

typedef struct tagSipRegistLocalInfo
{
	EmSipEndpointType  m_emEndpointType;   //������ums��cns
	u32 m_dwLocalIP;                         //����IP��ַ
	s8  m_achSoftVersion[LEN_USERNAME + 1];     //����汾��
	s8  m_achCompileTime[LEN_USERNAME + 1];     //����ʱ�� 
public:
    tagSipRegistLocalInfo() 
    {memset(this, 0, sizeof(tagSipRegistLocalInfo));}
}TSipRegistLocalInfo, *PTSipRegistLocalInfo;

typedef struct tagRegisterInfo
{
	TSipUrl m_tFromUrl;			//From �ֶ�URL
	TSipUrl m_tToUrl;			//To �ֶ�URL
	THostName m_tLocalAddr;		//����������Ϣ
	THostName m_tRegistrar;		//ע��������Ϣ
	u32 m_dwRegPort;			//ע������������˿�
	u32 m_dwExpires;			//��ʱʱ��,��λ��
	TSipRegistLocalInfo			m_tSipRegLocalInfo;
	EmSipConnection	m_emConnection;	//ע���ַ����
	TIPTransAddress m_tNatAddress;
	BOOL32 m_bPortReused;	//�Ƿ�˿ڸ���
#ifdef _ENABLE_QUANTUM_PROJECT_
	u32	m_dwQtID;	//���Ӽ���ע���ʶ
#endif
    s8	m_achProductId[MAX_PRODUCTID_LEN + 1];
	s8	m_achVersionId[MAX_PRODUCTID_LEN + 1];
	emEndpointType	 m_emEndpointType;
	EmVendorProductId m_emVendorId;

public:	
	tagRegisterInfo()
	{ 
		memset(this, 0, sizeof(tagRegisterInfo));
		m_emConnection = emSipUdpConnection;
		m_emEndpointType = emEndpointTypeMT;
		m_emVendorId = emKeda;
	}
}TRegisterInfo;

typedef struct tagSipRegName
{
	EmHostNameType m_emSipAddrType;
	s8     m_achUserName[LEN_USERNAME + 1];     //ע����
	s8     m_achPassword[LEN_PASSWORD + 1];	  //ע������
	s8     m_achDisplayName[LEN_USERNAME + 1];  //��ʾ����
	
	tagSipRegName()
	{
		memset( this, 0, sizeof(tagSipRegName) );
	}
}TSipRegName, *PTSipRegName;

typedef struct tagRegisterRequest
{
	TSipRegName      m_atSipRegName[MAX_NUM_REGNAME_SIZE];
	s32				 m_nSipRegArraySize;
	
	TIPTransAddress  m_atContactAddr[MAX_NUM_CONTACT_ADDR];//ע���ַ
	
	u32 m_dwExpires;//��ʱʱ��,��λ��
	s8 m_achCallId[MAX_NUM_CALLID];//����ID
	s32 m_nCSqence;//���к� //m_tRegistrar m_dwExpires m_aCallId m_nCSqence ��Ҫҵ��㱣�棬�Ա��ѯ
	EmSipConnection m_emSipConnection;
    TSipRegistLocalInfo  m_tLocalInfo; 
#ifdef _ENABLE_QUANTUM_PROJECT_
	u32	m_dwQtID;	//���Ӽ���ע���ʶ
#endif	
public:
	tagRegisterRequest()
	{ 
		memset(this , 0 , sizeof(tagRegisterRequest));
		m_emSipConnection = emSipTcpConnection;
	}
}RegisterRequest;

typedef struct tagRegisterResponse
{
	TIPTransAddress  m_tContactAddr;
	EmSipConnection  m_emSipConnection;
	BOOL32 m_bSerchPrefix;        //�ж�regserver�Ƿ�����ǰ׺���ң������ǰ׺���ң��ظ���300�оͽ�achAliasд�뵽contact��ַ��
	s8 m_achAlias[LEN_USERNAME + 1];
#ifdef _ENABLE_QUANTUM_PROJECT_
	u32	m_dwQtID;	//���Ӽ���ע���ʶ
#endif
public:
	tagRegisterResponse()
	{
		memset(this, 0, sizeof(tagRegisterResponse));
		m_emSipConnection = emSipTcpConnection;
	}
}RegisterResponse;

enum EmSipAliasType
{
	sip_Alias_Unknow,
	sip_Alias_e164,
	sip_Alias_h323,
	sip_Alias_IP,
};

typedef struct tagTSipAlias
{
	EmSipAliasType	m_emType;
	s8				m_achAlias[LEN_USERNAME + 1];
    tagTSipAlias()
	{
		memset( this, 0, sizeof(tagTSipAlias) );
	}
}TSipAlias;

enum EmSIPRegNSMType
{
	emSipRegNSMType_CNS = 0,
	emSipRegNSMType_UMS,
	emSipRegNSMType_ALL,
	emSipRegNSMType_CONF = 10,
};

typedef struct tagSIPRegNSM
{
	EmSIPRegNSMType m_emType;
	u32    m_dwRegIP;         //ע�������IP��ַ
	u16    m_wRegPort;        //ע��������˿�
	u32    m_dwLocalIP;       //����ip��ַ  
	u16    m_wLocalPort;     //���ض˿�
	TSipRegName	m_tSipRegName;		//RegName: including user and display name for SIP header

	tagSIPRegNSM()
	{
		memset( this, 0, sizeof(tagSIPRegNSM) );
		m_tSipRegName.m_emSipAddrType = emUrlNone;
	}
}TSIPRegNSM;

typedef struct tagTSipRegPackInfo
{
	u16 m_wPackSeq;       //����ţ���1��ʼ��0Ϊ��Чֵ
	u16 m_wTotalPackNum;  //������
	tagTSipRegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	
}TSipRegPackInfo, *PTSipRegPackInfo;

typedef struct tagTSipRegInfo
{
	u16		   m_wAliasNum;
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	EmSipEndpointType m_emSelfType;                   //ע�᷽ ��ϵͳ����(UMS��CNS)    
	
	tagTSipRegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emSipEndpointTypeUnknown;
	}
	
}TSipRegInfo;

typedef struct tagTSipRegPackXml
{
	TSipRegPackInfo tPackInfo;
	EmSIPRegNSMType emType;
	TSipRegInfo  tRegInfo;
	
	tagTSipRegPackXml()
	{
		emType = emSipRegNSMType_ALL;
	}
}TSipRegPackXml;

typedef struct tagTSipRegInfoUms
{
	u16		   m_wAliasNum;
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TIPTransAddress  m_atContactAddr[MAX_NUM_CONTACT_ADDR];//ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmSipConnection emSipConnection;
	TSipRegistLocalInfo m_tSipRegistLocalInfo;
	
	tagTSipRegInfoUms()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTSipRegInfoUms));
	}
	
}TSipRegInfoUms;

typedef struct tagTSipRegInfoCns
{
	u16		   m_wAliasNum;
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE_CNS];       //��ʱ��Ϊ���ֵΪ64������Ϊһ������
	TIPTransAddress  m_atContactAddr[MAX_NUM_CONTACT_ADDR];//ע���ַ
	u32 m_dwExpires;//��ʱʱ��,��λ��
	EmSipConnection emSipConnection;
	TSipRegistLocalInfo m_tSipRegistLocalInfo;
	
	tagTSipRegInfoCns()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTSipRegInfoCns));
	}
}TSipRegInfoCns;

typedef struct tagTSipRegPackXmlB2
{
	TSipRegPackInfo m_tPackInfo;
	EmSIPRegNSMType m_emType;
	EmSipEndpointType  m_emEndpointType;
	u16	m_wTotalRegInfo;
	tagTSipRegPackXmlB2()
	{
		m_emType = emSipRegNSMType_ALL;
		m_wTotalRegInfo = 0;
	}
}TSipRegPackXmlB2;

typedef struct tagSipHostAddress
{
	s8 m_achHost[MAX_HOST_LEN];	//������
	u16 m_wPort;	//�˿�   

	void Clear()
	{
		memset(this, 0, sizeof(tagSipHostAddress));
	}
	tagSipHostAddress()
	{
		Clear();
	}
} TSipHostAddress;

typedef struct tagUriSip
{
	s8 m_achDisplayName[LEN_USERNAME + 1];	//����
	s8 m_achUserName[LEN_USERNAME + 1];	//E164 
	s8 m_achPassword[LEN_PASSWORD + 1];	//����
	TSipHostAddress m_tHostAddr;
	s32 m_nAttrNum;
	TSdpAttr m_atAttr[MAX_SIP_ATTR_NUM];

	void Clear()
	{
		memset(m_achDisplayName, 0, sizeof(m_achDisplayName));
		memset(m_achUserName, 0, sizeof(m_achUserName));
		memset(m_achPassword, 0, sizeof(m_achPassword));
		m_tHostAddr.Clear();
		m_nAttrNum = 0;
		for (u8 i = 0; i < MAX_SIP_ATTR_NUM; i++)
		{
			m_atAttr[i].Clear();
		}
	}
	tagUriSip()
	{
		Clear();
	}
} TUriSip;

typedef struct tagSipNonStdData
{
	EmSipConnection m_emConn;	//tcp or udp
	TSipUrl m_tLocalUrl;	//���˵�ַ
	TSipUrl m_tRemoteUrl;	//�Զ˵�ַ
	u8 m_byNonStdHdrNum;	//�Ǳ�sip��ͷ����
	TSipHead m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	 //�Ǳ�sip��ͷ

	void Clear()
	{
		memset(this, 0, sizeof(tagSipNonStdData));
	}
	tagSipNonStdData()
	{
		Clear();
	}
} TSipNonStdData;

typedef struct tagRegReqInfo
{
	TUriSip m_tLocalUri;	/* Currently point to Request-URI ip address */
	s8 m_achCallId[MAX_SDP_ATTR_VALUE_LEN];
	s8 m_achRegName[LEN_USERNAME + 1];	/* Register name */
	TUriSip m_tUaAddress;	/* Local ip address */
	TUriSip m_tUaNatAddress;	/* Local real address with nat */
	s32	m_nExpires;	/**< Expires parameter, otherwise -1 if not present. */
	BOOL32 m_bIsContactStar;	    /**< The contact contains only a '*' character */
	s8 m_achProductId[MAX_PRODUCTID_LEN];
	s8 m_achVersionId[MAX_PRODUCTID_LEN];
	u8 m_byNonStdHeadNum;
	TSipHead m_atNonStdHead[MAX_SIP_NONSTD_HEADER_NUM];
	u8 m_byOtherParamNum;
	TSipAttr m_atUriOtherParam[MAX_SIP_URI_OTHER_PARAM_NUM];

	tagRegReqInfo()
	{ 
		memset(this, 0, sizeof(tagRegReqInfo));
		m_nExpires = -1;
	}
} TRegReqInfo;

/*
emCtrlMsg: pbyInBuf��wInLen
h_chan_flowControl: stream_id(s32)+Bitrate(u16),sizeof(s32)+ sizeof(u16) 
h_chan_fastupdate:  stream_id(s32),sizeof(s32)
                    Null,0
pchOutBuf�� generate xml
wOutLen: the size of xml
*/
PROTO_API void GenerateChannelXml(u8* pbyInBuf, u16 wInLen, EmSipConfCtrlMsgType  emCtrlMsg , s8* pchOutBuf, u16 &wOutLen);

/*
this interface is just the opposite of what is described above for generate xml
*/
PROTO_API void ParseNonStdXml(s8* pchInBuf, u16 wInLen, EmSipConfCtrlMsgType  &emCtrlMsg , s8* pchOutBuf, u16 &wOutLen);

#endif
