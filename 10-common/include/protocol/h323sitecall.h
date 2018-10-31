/*****************************************************************************
   ģ����      : h323sitecall
   �ļ���      : h323sitecall.h
   ����ļ�    : h323sitecall
   �ļ�ʵ�ֹ���: ���ϲ���ⷽʽ���к�����API�����ͻص�����
   ����        : ZHHE
   �汾        : V4.0  Copyright(C) 2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
******************************************************************************/

#ifndef _H323SITECALL_H
#define _H323SITECALL_H


#include "osp.h"
#include "sitecall.h"


/*============================== ���ȶ��� ===================================*/
#define LEN_MEDIANAME		(u16)128			//��ý��������
#define SITECALL_MAXLEN_ALIAS		(u16)128	//�ն˱���
#define LEN_PWD				(u16)32				//���볤��
#define LEN_CONF			(u16)40				//����������
#define	LEN_CARD			(u16)32				//�ʺ�������
#define MAXROOMNUM			(u16)32				//���᳡����
#define LEN_ROOM			(u16)30				//�᳡���Ƴ���
#define LEN_E164			(u16)30				//E164���볤��
#define MAXMULTIPIC			(u8)32				//����ӻ������


/*============================ ��־������ =================================*/
#define SITECALL_LOG_EXP    (s32)0				//�쳣
#define SITECALL_LOG_IMT    (s32)1				//��Ҫ��־
#define SITECALL_LOG_DEBUG  (s32)2				//һ��������Ϣ
#define SITECALL_LOG_ALL    (s32)3				//���е�����Ϣ 


/*============================== ö�ٶ��� ===================================*/

/*����ֵ*/
enum SiteCallError
{
	sc_err = -1,
	sc_ok  = 0,
};

/*���к�������*/
enum
{
	sitecall_make = 0x02,						//[T-->G]: TSITECALLREQ
	sitecall_answer,							//[T<--G]: TSITECALLRES
	sitecall_drop								//[T-->G]: NULL
};


/*���к������*/
typedef enum
{
	scr_success	 = 0xff,					/*�̶�Ϊ0xff*/
	scr_invalidUser = 0x16,					/*�û��ʺŲ���ͨ����֤*/
	scr_outOfMoney	 = 0x17,				/*Ԥ�����û��ʻ�����*/
	scr_unkownReason= 0x19					/*��������*/
}SiteCallResult;


/*�ն�����*/
typedef enum
{
	TerminalType_isdnVideo = 0,					/*(0)ISDN��Ƶ�ն�*/
	TerminalType_v35,							/*(1)V.35�ն�*/
	TerminalType_e1,							/*(2)E1�ն�*/
	TerminalType_ip,							/*(3)IP�ն�*/
	TerminalType_phone							/*(4)Phone�ն�*/
}TerminalType;

/*������������(0x02)*/
typedef enum
{
	conf_immediateBegin = 0,					/*(0)������ʼ���飬������д����ʱ��*/
	conf_booking,								/*(1)ԤԼ����*/
	conf_bookingCancel,							/*(2)ȡ��ԤԼ����*/
	conf_p2pprepay								/*(3)��Ե��*/
}ConfCmdType;

/*�ټ��豸����(0x0F)*/
typedef enum
{
	unkownMT	 = 0,							/*(0)����*/
	meettingRoom = 0x01,						/*(1)�������ն�*/
	table,										/*(2)�����ն�*/
	otherMT										/*(3)�����ն�*/
}CallingTerminalType;


/*����ģʽ(0x10)*/
typedef enum
{
	CustomizeMode = 0,							/*(0)����:���᳡�Ľ������ʡ�����Ƶ�㷨�͸�ʽ��QOS �ȼ�����ȫ����ͳһ�Ļ���涨����*/
	AdaptMode									/*(1)����Ӧ:���᳡�ɲ�һ������MCU �������ƥ�䡣*/
}ConfMode;


/*�Ʒ�����(0x0E)*/
typedef enum
{
	payTypeCradPay = 0,							/*(0)�ʺŸ���*/
	payTypeOrganigerPay,						/*(1)�����ն˸���*/
	payTypeTerminalPay							/*(2)ÿ�ն˸���*/
}PayType;

/*��������(0x5A)*/
typedef enum
{
	rate_n64   = 0x20,							/*(0)64kbps*/
	rate_n2m64 = 0x21,							/*(1)2��64kbps*/
	rate_n3m64 = 0x22,							/*(2)3��64kbps*/
	rate_n4m64 = 0x23,							/*(3)4��64kbps*/
	rate_n5m64 = 0x24,							/*(4)5��64kbps*/
	rate_n6m64 = 0x25,							/*(5)6��64kbps*/
	rate_r384  = 0x26,							/*(6)384kbps*/
	rate_r1536 = 0x2B,							/*(7)1536kbps*/
	rate_r1920 = 0x2c,							/*(8)1920kbps*/
	rate_r128  = 0x2d,							/*(9)128kbps*/
	rate_r192  = 0x2e,							/*(10)192kbps*/
	rate_r256  = 0x2f,							/*(11)256kbps*/
	rate_r320  = 0x30,							/*(12)320kbps*/
	rate_r512  = 0x37,							/*(13)512kbps*/
	rate_r768  = 0x38,							/*(14)768kbps*/
	rate_r1152 = 0x3A,							/*(15)1152kbps*/
	rate_r1472 = 0x3D,							/*(16)1472kbps*/
	/*(ע��V2.0�汾������3M��4M��6M��8M����)*/
	rate_r3M   = 0x3E,							/*(17)3M(2880kbps)*/
	rate_r4M   = 0x3F,							/*(18)4M(3840kbps)*/
	rate_r6M   = 0x40,							/*(19)6M(5760kbps)*/
	rate_r8M   = 0x41							/*(20)8M(7680kbps)*/
}DataRate;


/*��Ƶ�㷨����Ϣ(0x5B)���ݱ���*/
enum SiteCallVideo
{
	sc_v_H261 = 0x41,							/*H.261*/
	sc_v_H263 = 0x42,							/*H.263*/
	sc_v_H264 = 0x43,							/*H.264*/
	sc_v_Real = 0x44,							/*Real��ʽ*/
	sc_v_WindowsMedia = 0x45,					/* WindowsMedia��ʽ*/
	sc_v_MPEG4 = 0x46							/* MPEG4��ʽ*/
		
};


/*��Ƶ��ʽ����Ϣ(0x5C)���ݱ���*/
enum SiteCallVideoFormat
{
	sc_vf_H263QCIF		   = 0x00,				/*H.263 QCIF*/
	sc_vf_H263CIF_H261QCIF = 0x01,				/*H.263 CIF/H.261 QCIF*/
	sc_vf_H261CIF		   = 0x02,				/* H.261 CIF*/
	sc_vf_H263_4CIF		   = 0x03,				/*H.263 4CIF*/
	sc_vf_VGA			   = 0x04,				/*����Э���Vga*/
	sc_vf_2CIF			   = 0x05,				/*����Э���2cif*/
	sc_vf_4CIF             = 0x06,				/*����Э���4CIF*/
	sc_vf_SVGA             = 0x07,				/*����Э���Svga*/
	sc_vf_SXVGA			   = 0x08,				/*����Э���sxvga*/
	sc_vf_16CIF			   = 0x09				/*����Э���16CIF*/
		
};

/*��Ƶ֡������Ϣ(0x5D)���ݱ���*/
enum SiteCallVideoFrame
{
    sc_v_frameauto = 0x0,
	sc_v_frame30 = 0x01,						/*30֡/��*/
	sc_v_frame15 = 0x02,						/*15֡/��*/
	sc_v_frame10 = 0x03,						/*10֡/��*/
	sc_v_frame75 = 0x04 						/*7.5֡/��*/
};

/*��Ƶ�㷨����Ϣ(0x5E)���ݱ���*/
enum SiteCallAudio
{
	sc_a_G7231	   = 0x0A,						/*G.723.1*/
	sc_a_G729	   = 0x0B,						/*G.729*/
	sc_a_G711A_56K = 0x12,						/*G.711A-56K*/
	sc_a_G711U_56K = 0x13,						/*G.711U-56K*/
	sc_a_G722_64K  = 0x17,						/*G.722-64K,(V2.0)*/
	sc_a_G722_56K  = 0x18,						/*G.722-56K*/
	sc_a_G722_48K  = 0x19,						/*G.722-48K*/
	sc_a_G728      = 0x1D,						/*G.728*/
	sc_a_G711A_64K = 0x1E,						/*G.711A-64K*/
	sc_a_G711U_64K = 0x1F,						/*G.711u-64K*/
	sc_a_Real	   = 0x20,						/*Real��ʽ,(V2.0)*/
	sc_a_WindowsMedia =	0x21,					/*WindowsMedia��ʽ,(V2.0)*/
	sc_a_MPEG4	   = 0x22						/*MPEG4��ʽ,(V2.0)*/
};

/*============================== �ṹ���� ===================================*/
typedef struct tagSiteCallAddress
{
	u32 m_dwIP;
	u16 m_wPort;

	tagSiteCallAddress()
	{
		Clear();
	}

	void Clear()
	{
		m_dwIP = 0;
		m_wPort = SITECALLPORT;
	}
	//����transport��ַ
	void SetNetAddress(u32 dwIPAddr, u16 wIPPort=SITECALLPORT)
	{
		m_dwIP   = dwIPAddr;
		m_wPort  = wIPPort;
	}
	//��ȡIP��ַ
	u32 GetIP()
	{
		return m_dwIP;
	}
	//��ȡ�˿�
	u16 GetPort()
	{
		return m_wPort;
	}
}SiteCallAddr;

typedef struct tagSiteCallNetConfig
{
	BOOL32 m_bIsGk;
	SiteCallAddr m_tLocalAddr;
	SiteCallAddr m_tGkAddr;
	
	tagSiteCallNetConfig()
	{
		Clear();
	}

	void Clear()
	{
		m_bIsGk = FALSE;
		m_tLocalAddr.Clear();
		m_tGkAddr.Clear();
	}

	void SetBeGk(BOOL32 bGk)
	{
		m_bIsGk = bGk;
	}
	BOOL32 IsGk()
	{
		return m_bIsGk;
	}

	void SetLocalAddr(u32 dwIp, u16 wPort = SITECALLPORT)
	{
		m_tLocalAddr.m_dwIP  = dwIp;
		m_tLocalAddr.m_wPort = wPort;
	}
	u32 GetLocalIP()
	{
		return m_tLocalAddr.GetIP();
	}
	u16 GetLocalPort()
	{
		return m_tLocalAddr.GetPort();
	}
	void SetGkAddr(u32 dwIp, u16 wPort = SITECALLPORT)
	{
		m_tGkAddr.m_dwIP = dwIp;
		m_tGkAddr.m_wPort = wPort;
	}
	u32 GetGkIP()
	{
		return m_tGkAddr.GetIP();
	}
	u16 GetGkPort()
	{
		return m_tGkAddr.GetPort();
	}
}TSCNetCfg, *PTSCNetCfg;

/*��������*/
typedef struct tagCommonInfo
{
	DataRate  m_emRate;							/*��������(u8),ע����ö���б���ѡ��!*/
	
	u8		  m_byVideoType;					//��Ƶ�㷨
	u8		  m_byVideoFormat;					//��Ƶ��ʽ
	u8		  m_byVideoFrame;					//��Ƶ֡��
	u8		  m_byAudioType;					//��Ƶ�㷨	
												/*
												ע����ǰ�汾�Ļ�Ϊ�նˣ����к�����Ҳֻ��
												H261QCIF,H261CIF,H263QCIF,H23CIF
												G711_64K,G722_64K,G728_16K	
												*/
	tagCommonInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emRate		= rate_r384;
		m_byVideoType	= sc_v_H261;
		m_byVideoFormat = sc_vf_H261CIF;
		m_byVideoFrame  = sc_v_frame30;
		m_byAudioType	= sc_a_G711A_64K;
	}
	
	/*���ô�������*/
	void SetRate(DataRate emRate)
	{
		m_emRate = emRate;
	}

	/*��ô�������*/
	DataRate GetRate()
	{
		return m_emRate;
	}
	
	void SetVideoType(u8 byType)
	{
		m_byVideoType = byType;
	}

	void SetVideoFormat(u8 byFormat)
	{
		m_byVideoFormat = byFormat;
	}

	void SetVideoFrame(u8 byFrame)
	{
		m_byVideoFrame = byFrame;
	}

	void SetAudioType(u8 byType)
	{
		m_byAudioType = byType;
	}

}TCOMMONINFO, *PTCOMMONINFO;

/*�ʺ�����*/
typedef struct tagCardInfo
{
	s8 m_achCardNumber[LEN_CARD];				/*�ʺ�*/
	s8 m_achCardPwd[LEN_PWD];					/*����*/
	
	tagCardInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(m_achCardNumber, 0, sizeof(m_achCardNumber));
		memset(m_achCardPwd, 0, sizeof(m_achCardPwd));
	}
	
	/*�����ʺ�*/
	void SetCardNumber(s8* pCardNumber, u16 wLen)
	{		
		if (pCardNumber != NULL && wLen < LEN_CARD+1) 
		{
			memset(m_achCardNumber, 0, sizeof(m_achCardNumber));
			memcpy(m_achCardNumber, pCardNumber, wLen);
			m_achCardNumber[wLen] = '\0';
		}	
	}
	/*��ȡ�ʺ�*/
	u16 GetCardNumber(s8 *pCardNumber, u16 &wLen)
	{
		if (pCardNumber != NULL) 
		{
			u16 realLen = min( wLen, LEN_CONF);
			memcpy(pCardNumber, m_achCardNumber, realLen);
			return realLen;
		}
	}
	
	/*��������*/
	void SetCardPwd(s8* pCardPwd, u16 wLen)
	{		
		if (pCardPwd != NULL && wLen < LEN_PWD+1) 
		{
			memset(m_achCardPwd, 0, sizeof(m_achCardPwd));
			memcpy(m_achCardPwd, pCardPwd, wLen);
			m_achCardPwd[wLen] = '\0';
		}	
	}
	/*��ȡ����*/
	u16 GetCardPwd(s8 *pCardPwd, u16 &wLen)
	{
		if (pCardPwd != NULL) 
		{
			u16 realLen = min( wLen, LEN_CONF);
			memcpy(pCardPwd, m_achCardPwd, realLen);
			return realLen;
		}
	}
	
}TCARDINFO, *PTCARDINFO;

/*�������*/
typedef struct tagConferenceParam
{
	s8 m_achConfName[LEN_CONF];					/*������*/
	s8 m_achConfPwd[LEN_PWD];					/*�����������,ע������Ϊ�����ַ���(HuaWei)*/
	ConfMode m_emConfMode;						/*����ģʽ*/
	
	tagConferenceParam()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emConfMode = AdaptMode;
		memset(m_achConfName, 0, sizeof(m_achConfName));
		memset(m_achConfPwd, 0, sizeof(m_achConfPwd));
	}

	/*���û�����*/
	s32 SetConfName(s8* pConfName)
	{
		if (pConfName == NULL)
		{
			return -1;
		}

		memset(m_achConfName, 0, sizeof(m_achConfName));
		u16 wLen = min(strlen(pConfName), LEN_CONF);
		strncpy(m_achConfName, pConfName, wLen);
		m_achConfName[wLen] = '\0';
		return wLen;
	}
	/*��ȡ������*/
	s8* GetConfName()
	{
		return m_achConfName;
	}

	/*��������*/
	void SetConfPwd(s8* pConfPwd, u16 wLen)
	{		
		if (pConfPwd != NULL && wLen < LEN_PWD+1) 
		{
			memset(m_achConfPwd, 0, sizeof(m_achConfPwd));
			memcpy(m_achConfPwd, pConfPwd, wLen);
			m_achConfPwd[wLen] = '\0';
		}	
	}
	/*��ȡ����*/
	u16 GetCardPwd(s8 *pConfPwd, u16 &wLen)
	{
		if (pConfPwd != NULL) 
		{
			u16 realLen = min( wLen, LEN_CONF);
			memcpy(pConfPwd, m_achConfPwd, realLen);
			return realLen;
		}
	}
	
	/*���û���ģʽ*/
	void SetConfMode(ConfMode emConfMode)
	{
		m_emConfMode = emConfMode;
	}
	/*��û���ģʽ*/
	ConfMode GetConfMode()
	{
		return m_emConfMode;
	}
	
}TConfParam, *PTConfParam;


/*�������*/
typedef struct tagSiteCallConferenceInfo
{
	TConfParam m_tConfParam;
	ConfCmdType m_emConfCmdType;				/*������������,��ֻȡconf_immediateBegin*/
	BOOL32 m_bDataConf;							/*���ݻ����־*/
	u8	 m_byMultiPic;							/*�໭����Դ,����ӻ��������0��ʾ��*/
	u16	 m_wRoomNum;							/*�᳡����,ע:����������СΪ2*/

	TCARDINFO m_tCardInfo;						/*�ʺ�����*/
	PayType m_emPayType;						/*�Ʒ�����*/

	CallingTerminalType m_emMtType;				/*�ټ��豸����*/
	TCOMMONINFO m_tCommInfo;					/*��������*/

	tagSiteCallConferenceInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byMultiPic = 0;
		m_wRoomNum   = 0;
		m_bDataConf  = FALSE;
		m_emPayType		 = payTypeCradPay;
		m_emConfCmdType	 = conf_immediateBegin;
		
		m_tCardInfo.Clear();		
		m_tConfParam.Clear();
		m_tCommInfo.Clear();
	}
	
	/*���û������*/
	void SetConfParam(TConfParam &tConfParam)
	{
		m_tConfParam = tConfParam;
	}
	/*��ȡ�������*/
	TConfParam* GetConfParam()
	{
		return &m_tConfParam;
	}
	
	/*���û�����������*/
	void SetConfCmdType(ConfCmdType emCmdType)
	{
		m_emConfCmdType = emCmdType;
	}
	/*��û�����������*/
	ConfCmdType GetConfCmdType()
	{
		return m_emConfCmdType;
	}


	/*��������ӻ������*/
	void SetMultiPicNum(u8 byNum)
	{
		m_byMultiPic = (byNum > MAXMULTIPIC ? MAXMULTIPIC : byNum);
	}
	/*��������ӻ������*/
	u8 GetMultiPicNum()
	{
		return m_byMultiPic;
	}

	/*���û᳡����*/
	void SetRoomNum(u16 wNum)
	{
		m_wRoomNum = wNum;
	}
	/*��û᳡����*/
	u16 GetRoomNum()
	{
		return m_wRoomNum;
	}

	/*�����ʺ�����*/
	void SetCardInfo(TCARDINFO &tCardInfo)
	{
		m_tCardInfo = tCardInfo;
	}
	/*����ʺ�����*/
	TCARDINFO* GetCardInfo()
	{
		return &m_tCardInfo;
	}

	/*���üƷ�����*/
	void SetPayType(PayType emPayType)
	{
		m_emPayType = emPayType;
	}
	/*��üƷ�����*/
	PayType GetPayType()
	{
		return m_emPayType;
	}

	/*�����ټ��豸����*/
	void SetMtType(CallingTerminalType emMtType)
	{
		m_emMtType = emMtType;
	}
	/*����ټ��豸����*/
	CallingTerminalType GetMtType()
	{
		return m_emMtType;
	}

	/*����᳡����������Ϣ*/
	void SetCommonInfo(TCOMMONINFO tCommonInfo)
	{
		m_tCommInfo = tCommonInfo;
	}
	TCOMMONINFO& GetCommonInfo()
	{
		return m_tCommInfo;
	}

}TSiteCallConfInfo, *PTSiteCallConfInfo;

/*�᳡��Ϣ*/
typedef struct tagRoomInfo
{
	s8 m_achRoomName[LEN_ROOM];					/*�᳡����*/
	s8 m_achAlias[LEN_E164];					/*�ն˺���*/

	TerminalType m_emMtType;					/*�ն�����*/
	TCOMMONINFO m_tCommInfo;					/*��������*/

	
	tagRoomInfo()
	{
		Clear();
	}

	void Clear()
	{

		m_emMtType   = TerminalType_ip;
		m_tCommInfo.Clear();
		memset(m_achRoomName, 0, sizeof(m_achRoomName));
		memset(m_achAlias, 0, sizeof(m_achAlias));
	}

	/*���û᳡����*/
	BOOL32 SetRoomName(s8 *pName)
	{
		if (pName == NULL)
		{
			return FALSE;
		}

		u16 wLen = (u16)min(strlen(pName), LEN_ROOM);
		memset(m_achRoomName, 0, sizeof(m_achRoomName));
		strncpy(m_achRoomName, pName, wLen);
		m_achRoomName[wLen] = '\0';
		return TRUE;
	}
	/*��û᳡����*/
	s8* GetRoomName()
	{
		return m_achRoomName;
	}

	/*���ñ���*/
	BOOL32 SetAlias(const s8* pAlias )
	{
		if (pAlias == NULL ) 
			return FALSE;
		
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		
		u16 nLen = (u16)min( strlen(pAlias), LEN_E164);
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		return TRUE;
	}	
	/*��ñ���*/
	s8* GetAlias()  
	{
		return m_achAlias;	
	}

	/*�����ն�����*/
	void SetMtType(TerminalType emType)
	{
		m_emMtType = emType;
	}
	/*����ն�����*/
	TerminalType GetMtType()
	{
		return m_emMtType;
	}

	/*����᳡����������Ϣ*/
	void SetCommonInfo(TCOMMONINFO tCommonInfo)
	{
		m_tCommInfo = tCommonInfo;
	}
	TCOMMONINFO& GetCommonInfo()
	{
		return m_tCommInfo;
	}
	
}TROOMINFO, *PTROOMINFO;

/*����������������*/
typedef struct tagConnectRequest
{
	u32			m_dwIPAddr;						/*�ն�IP��ַ*/
	s8			m_achAlias[SITECALL_MAXLEN_ALIAS];		/*�ն˱���(������128�ֽ�)E164*/


	tagConnectRequest()
	{
		Clear();
	}

	void Clear()
	{
		m_dwIPAddr = 0;
		memset(m_achAlias, 0, sizeof(m_achAlias));
	}

	/*�����ն�IP��ַ*/
    void SetIPAddr(u32 dwIPAddr)
    {
        m_dwIPAddr = dwIPAddr;
    }
    /*�õ����������ַ*/
    u32 GetCallAddr()
    {
        return m_dwIPAddr;
    }

	/*���ñ���*/
	BOOL32 SetAlias(const s8* pAlias )
	{
		if (pAlias == NULL ) 
			return FALSE;
		
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		
		u16 nLen = min( strlen(pAlias), SITECALL_MAXLEN_ALIAS);
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		return TRUE;
	}	
	/*��ñ���*/
	s8* GetAlias()  
	{
		return m_achAlias;	
	}
	
}TCONNECTREQ, *PTCONNECTREQ;

/*��������������Ӧ*/
typedef struct tagConnectResponse
{
	u8		  m_byResponse;					/*���к������ӽ��*/

	tagConnectResponse()
	{
		Clear();
	}

	void Clear()
	{
		m_byResponse = 0;
	}

	/*�������к������ӽ��*/
	void SetResponse(u8 byResponse)
	{
		m_byResponse = byResponse;
	}
	/*������к������ӽ��*/
	u8 GetResponse()
	{
		return m_byResponse;
	}

}TCONNECTRES, *PTCONNECTRES;

/*���к�������*/
typedef struct tagSiteCallRequest
{
	TSiteCallConfInfo	m_tConfInfo;					/*����������Ϣ*/
	TROOMINFO   m_atRoom[MAXROOMNUM];			/*�᳡������Ϣ,m_atRoom[0]Ϊ���᳡*/

	tagSiteCallRequest()
	{
		Clear();
	}

	void Clear()
	{
		m_tConfInfo.Clear();
		memset(m_atRoom, 0, sizeof(m_atRoom));
	}


	/*���û�����Ϣ*/
    void SetConfInfo(TSiteCallConfInfo &tConfInfo)
    {      
        m_tConfInfo = tConfInfo;
    }
    /*�õ�������Ϣ*/
    TSiteCallConfInfo& GetConfInfo()
    {
		return m_tConfInfo;
    }

	
    /*���û᳡��Ϣ*/
    void SetRoomInfo(TROOMINFO &tRoomInfo, u16 wRoomNo)
    {
        if (wRoomNo >= MAXROOMNUM )
            return;
        
        m_atRoom[wRoomNo] = tRoomInfo;
    }
    /*�õ��᳡��Ϣ*/
    TROOMINFO& GetRoomInfo(u16 wRoomNo)
    {
        if ( wRoomNo < MAXROOMNUM ) 
            return m_atRoom[wRoomNo];
        else
            return m_atRoom[0];
    }
	
}TSITECALLREQ, *PTSITECALLREQ;

/*���к�����Ӧ*/
typedef struct tagSiteCallResponse
{
	SiteCallResult m_emResult;					/*���к�����Ӧ*/
	s8		   m_achReason[SITECALL_MAXLEN_ALIAS];		/*�ɹ��������;ʧ�ܣ�����ԭ��*/

	tagSiteCallResponse()
	{
		Clear();
	}

	void Clear()
	{
		m_emResult = scr_unkownReason;
		memset(m_achReason, 0, sizeof(m_achReason));
	}

	void SetResult(SiteCallResult emResult)
	{
		m_emResult = emResult;
	}
	SiteCallResult GetResult()
	{
		return m_emResult;
	}

	/*�������к������*/
	BOOL32 SetReason(const s8* pReason)
	{
		if (pReason == NULL ) 
			return FALSE;
		
		memset( m_achReason, 0, sizeof(m_achReason) );
		
		u16 wLen = min( strlen(pReason), SITECALL_MAXLEN_ALIAS);
		strncpy( m_achReason, pReason, wLen );
		m_achReason[wLen] = '\0';
		return TRUE;
	}	
	/*������к������*/
	s8* GetReason()  
	{
		return m_achReason;	
	}
	
}TSITECALLRES, *PTSITECALLRES;


/*�Ͽ����к�����������*/
/*ע��V2.0�汾�У��ԡ��Ͽ����к����������������������չ*/
typedef struct tagDisConnectRequest
{
}TDISCONNECTREQ, *PTDISCONNECTREQ;

/*�Ͽ����к���������Ӧ*/
typedef struct tagDisConnectResponse
{
	u8	m_byReason;								/*�Ͽ����к������ӽ��*/		
	/*��չ��Ϣ......*/
	tagDisConnectResponse()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byReason = 0;
	}
	
	void SetResult(u8 byReason)
	{
		m_byReason = byReason;
	}
	u8 GetResult()
	{
		return m_byReason;
	}
}TDISCONNECTRES, *PTDISCONNECTRES;


/*================================= �ṹ���� ================================*/
typedef s32 (* NotifyNewSiteCallT)(HSITECALL hSiteCall);

typedef s32 (* NotifySiteCallMessageT)(HSITECALL hSiteCall, u16 msgType, const void* pBuf, u16 nBufLen);

typedef  struct
{
	NotifyNewSiteCallT					fpNotifyNewSiteCall;
	NotifySiteCallMessageT				fpNotifySiteCallMessage;
}SITECALLEVENTS, *LPSITECALLEVENTS;

/*====================================================================
    ������      : sitecalllog
    ����        : ���ô�ӡ����
    �㷨ʵ��    : ��
    ����ȫ�ֱ���: ��
    �������˵��: 
    ����ֵ˵��  : ��
====================================================================*/
API void setsitecalllog(u8 byLevel);

/*====================================================================
��	 ��   ��: SiteCallInit
��	      ��: ��ʼ�����к���ģ��
�� �� ʵ  ��: 
����ȫ�ֱ���: g_ptTrans
�������˵��: ��			  
��   ��   ֵ: �ɹ� - TRUE
			  ʧ�� - FALSE		
====================================================================*/
BOOL32 H323SiteCallInit(TSCNetCfg* ptConfig);

/*====================================================================
��	 ��   ��: SetCallBack
��	      ��: ע��Ӧ�ûص�����
�� �� ʵ  ��: 
����ȫ�ֱ���: g_ptTrans
�������˵��: lpEvent - �ص������ṹָ��
��   ��   ֵ: �ɹ� - sc_ok
ʧ�� - sc_err
====================================================================*/
s32 SCSetCallBack(LPSITECALLEVENTS lpEvent);

/*====================================================================
��	 ��   ��: SiteCallSetGkIp
��	      ��: 
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
API void SiteCallSetGkIp(u32 gkIp, u16 gkPort = SITECALLPORT);

/*====================================================================
��	 ��   ��: CreateNewSiteCall
��	      ��: �����µĺ��У������ȴ����ٺ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: haCall -   Ӧ�ó�����о��
�� �� ��  ��: lphsCall - Э��ջ���о��
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
s32 H323CreateNewSiteCall(LPHSITECALL lphSiteCall, bool bSync = true);

/*====================================================================
��	 ��   ��: SendSiteCallMsg
��	      ��: ���к���������Ϣ�ּ�
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: 
��   ��   ֵ: �ɹ� - sc_ok
			  ʧ�� - sc_err
====================================================================*/
s32 SendSiteCallCommand(HSITECALL hSiteCall, u16 wMsgType, void* pBuf,u16 wBufLen, bool bSync = true);

/*====================================================================
��	 ��   ��: SiteCallClose
��	      ��: �ر����к���
�� �� ʵ  ��: 
����ȫ�ֱ���: g_ptTrans
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
s32 SiteCallClose(HSITECALL hSiteCall, bool bSync);

/*====================================================================
��	 ��   ��: SiteCallEnd
��	      ��: �ر����к���ģ��
�� �� ʵ  ��: 
����ȫ�ֱ���: g_ptTrans
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
s32 SiteCallEnd(bool bSync = true);

//debug print
API void setsitecalllog(u8 byLevel);
API void printsitecall();

#endif //_H323SITECALL_H










































