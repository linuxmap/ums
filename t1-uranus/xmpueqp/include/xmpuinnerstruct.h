#ifndef _ums_inner_struct_
#define _ums_inner_struct_
#include "umsobject.h"
#include "eqpinterface.h"
#include "tpsys.h"
#include "tpcommontype.h"
#include "umsxmpinterface.h"


//Hdu/Vmp/Mix���û�������������
typedef    u32	APPHANDLE;     //�ϲ�ҵ��APP���    
// �������
typedef    u32	HMEDIARES;     // ý����

#define  XMPU_USERDATE_BEGIN  1500


enum EmXmpuEqpStat
{
	XmpuEqpStat_Idle,   //
	XmpuEqpStat_Starting, //���ڿ������м�״̬
	XmpuEqpStat_Running, //���ڹ���
	XmpuEqpStat_Error,  //�쳣
};

// һ��xmpu2���� 12��NetroоƬ һ��6678оƬ
//NetroоƬ3����Ϊһ���ܳ���� 4������ϳ�����ÿ������ϳ������֧��25��񣩻�4*4����Ƶ����ͨ����4���� 2�� 2С��
//һ��6678оƬ֧��6�����������ÿ�����192·������������ٲ�ֳ�����С������������12��С����������֧��10·����
//һ��6678оƬ֧��7����Ƶ��������1��4������������Ƶ��Ƶͬʱ����
typedef struct tagTMediaEqpMgr
{
	//������
	u32   m_dw264VmpCnt;           //��֧��264��vmp����
	u32   m_dw265_264VmpCnt;       //֧��264��265��vmp����
	u32   m_dw264BasCnt;           //��֧��264��vbas����
	u32   m_dw265_264BasCnt;       //��֧��264��265��vmp����
	u32   m_dwABasCnt;             //aud bas����
	u32   m_dwMixer8Cnt;           //��֧��8����mixer����
	u32   m_dwMixer192Cnt;         //��֧��192����mixer����
	u32   m_dw264Port;             //��֧��264�Ķ˿���Դ����
	u32   m_dw265Port;             //��֧��265�Ķ˿���Դ����

	//��������
	u32   m_dw264VmpUsedCnt;           //��֧��264��vmp����
	u32   m_dw265_264VmpUsedCnt;       //֧��264��265��vmp����
	u32   m_dw264BasUsedCnt;           //��֧��264��vbas����
	u32   m_dw265_264BasUsedCnt;       //��֧��264��265��vmp����
	u32   m_dwABasUsedCnt;             //aud bas����
	u32   m_dwMixer8UsedCnt;           //��֧��8����mixer����
	u32   m_dwMixer192UsedCnt;         //��֧��192����mixer����
	u32   m_dw264UsedPort;             //��֧��264�Ķ˿���Դ����
	u32   m_dw265UsedPort;             //��֧��265�Ķ˿���Դ����
	
	//��ʼ������
	u32 m_dwVmpInitCnt;


	tagTMediaEqpMgr()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTMediaEqpMgr));
	}

	BOOL32 operator == (const tagTMediaEqpMgr& cInfo) const
	{
		return ((this->m_dw264VmpCnt == cInfo.m_dw264VmpCnt) && (this->m_dw264BasCnt == cInfo.m_dw264BasCnt)
					&& (this->m_dwABasCnt == cInfo.m_dwABasCnt) && (this->m_dwMixer8Cnt == cInfo.m_dwMixer8Cnt) && (this->m_dwMixer192Cnt == cInfo.m_dwMixer192Cnt	)
					&&(this->m_dw265_264VmpCnt == cInfo.m_dw265_264VmpCnt) && (this->m_dw265_264BasCnt == cInfo.m_dw265_264BasCnt));
	}

	tagTMediaEqpMgr& operator = (const tagTMediaEqpMgr& tRsData)
	{
		if (this == &tRsData)
		{
			return *this;
		}
		memcpy(this, &tRsData, sizeof(tRsData));
		return *this;
	}
	void SetVmpInitCnt(u32 dwNum)
	{
		m_dwVmpInitCnt = dwNum;
	}
	u32 GetVmpInitCnt()
	{
		return m_dwVmpInitCnt;
	}
	

	BOOL32 IsNoIdleSource()
	{
		if (!(m_dw264VmpCnt || m_dw264BasCnt ||  m_dwABasCnt || m_dwMixer8Cnt || m_dwMixer192Cnt || m_dw265_264VmpCnt || m_dw265_264BasUsedCnt))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}


}TMediaEqpMgr;

typedef struct tagTXmpuFrameStatis
{
	u32 m_dwLastTime;
	u16	m_wIntrval;
	tagTXmpuFrameStatis()
	{
		Clear();
	}

	void Clear()
	{
		m_dwLastTime = 0;
		m_wIntrval = 1;
	}

	void SetIntrval(u16 wIntrval)
	{
		m_wIntrval = wIntrval;
	}

	BOOL32 CheckFrameStatis()
	{
		time_t t;
		time(&t);
		u32 dwNow = t;

		if ( dwNow - m_dwLastTime >= m_wIntrval  )
		{
			m_dwLastTime = dwNow;
			return TRUE;
		}
		return FALSE;
	}

}TXmpuFrameStatis;

#define XMPU_MAX_SYN_NUM 4
enum emInitMettingRsp
{
	InitMettingRsp_UnKnow,
	InitMettingRsp_Success,
	InitMettingRsp_FAILD,
};
typedef struct tagTXmpuInitMettingRsp
{
	APPHANDLE		m_dwConfID;
	u8					m_bySynNum;
	u32					m_adwSynID[XMPU_MAX_SYN_NUM];
	emInitMettingRsp m_emRes;
	tagTXmpuInitMettingRsp()
	{
		Clear();
	}

	void Clear()
	{
		m_dwConfID = 0;
		m_bySynNum  = 0;
		memset(m_adwSynID, 0, sizeof(m_adwSynID));
		m_emRes = InitMettingRsp_UnKnow;
	}
}TXmpuInitMettingRsp;

enum emStartVmpRsp
{
	StartVmpRsp_UnKnow,
	StartVmpRsp_Success,
	StartVmpRsp_FAILD,
};

typedef struct tagTXmpuStartVmpRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emStartVmpRsp m_emRes;
	tagTXmpuStartVmpRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = StartVmpRsp_UnKnow;
	}
}TXmpuStartVmpRsp;

enum emStartBasRsp
{
	StartBasRsp_UnKnow,
	StartBasRsp_Success,
	StartBasRsp_FAILD,
};

typedef struct tagTXmpuStartBasRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emStartBasRsp m_emRes;
	u8				m_byChnNum;
	BOOL32		m_abVaildChn[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	tagTXmpuStartBasRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = StartBasRsp_UnKnow;
		m_byChnNum = 0;
		memset(m_abVaildChn, 0, sizeof(m_abVaildChn));
	}
}TXmpuStartBasRsp;


enum emSetBasEncRsp
{
	SetBasEncRsp_UnKnow,
	SetBasEncRsp_Success,
	SetBasEncRsp_FAILD,
};

typedef struct tagTXmpuSetBasEncRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emSetBasEncRsp m_emRes;
	u8				m_byChnNum;
	BOOL32		m_abVaildChn[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	tagTXmpuSetBasEncRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = SetBasEncRsp_UnKnow;
		m_byChnNum = 0;
		memset(m_abVaildChn, 0, sizeof(m_abVaildChn));
	}

}TXmpuSetBasEncRsp;

enum emStartAudBasRsp
{
	StartAudBasRsp_UnKnow,
	StartAudBasRsp_Success,
	StartAudBasRsp_FAILD,
};

typedef struct tagTXmpuStartAudBasRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emStartAudBasRsp m_emRes;
	u8				m_byChnNum;
	BOOL32		m_abVaildChn[UMS_AUDBAS_ENC_NUM];
	tagTXmpuStartAudBasRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = StartAudBasRsp_UnKnow;
		m_byChnNum = 0;
		memset(m_abVaildChn, 0, sizeof(m_abVaildChn));
	}
}TXmpuStartAudBasRsp;

enum emSetAudBasEncRsp
{
	SetAudBasEncRsp_UnKnow,
	SetAudBasEncRsp_Success,
	SetAudBasEncRsp_FAILD,
};

typedef struct tagTXmpuSetAudBasRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emSetAudBasEncRsp m_emRes;
	u8				m_byChnNum;
	BOOL32		m_abVaildChn[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	tagTXmpuSetAudBasRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = SetAudBasEncRsp_UnKnow;
		m_byChnNum = 0;
		memset(m_abVaildChn, 0, sizeof(m_abVaildChn));
	}

}TXmpuSetAudBasRsp;

enum emStartMixRsp
{
	StartMixRsp_UnKnow,
	StartMixRsp_Success,
	StartMixRsp_FAILD,
};

typedef struct tagTXmpuStartMixRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emStartMixRsp m_emRes;
	tagTXmpuStartMixRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = StartMixRsp_UnKnow;
	}
}TXmpuStartMixRsp;

enum emAddMixMemRsp
{
	AddMixMemRsp_UnKnow,
	AddMixMemRsp_Success,
	AddMixMemRsp_FAILD,
};

typedef struct tagTXmpuAddMixMemRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emAddMixMemRsp m_emRes;
	u8				m_byNum;
	u8				m_abyChnID[XMPU_AUDMIX_N1_NUM];
	tagTXmpuAddMixMemRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = AddMixMemRsp_UnKnow;
		m_byNum = 0;
		memset(m_abyChnID, 0, sizeof(m_abyChnID));
	}
}TXmpuAddMixMemRsp;

typedef struct tagTXmpuStartBasCommonRsp
{
	HMEDIARES m_dwHandle;
	u16       m_wErrCode;
	u8				m_byNum;
	u8				m_abyID[TP_CONF_MAX_MINOR_VIDEO_RES_NUM];
	tagTXmpuStartBasCommonRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwHandle = 0;
		m_wErrCode = 0;
		m_byNum = 0;
		memset(m_abyID, 0, sizeof(m_abyID));
	}
}TXmpuStartBasCommonRsp;

enum emStartVacRsp
{
	StartVacRsp_UnKnow,
	StartVacRsp_Success,
	StartVacRsp_FAILD,
};

typedef struct tagTXmpuStartVacRsp
{
	APPHANDLE m_dwEqpID;
	HMEDIARES m_dwHandle;
	emStartVacRsp m_emRes;
	tagTXmpuStartVacRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_emRes = StartVacRsp_UnKnow;
	}
}TXmpuStartVacRsp;

typedef struct tagTXmpuSynChn
{
	u32					m_dwEqpID; //ҵ����
	HMEDIARES		m_dwHandle; //ҵ����
	u8					m_bySynChn;  //ͬ����ͨ���ţ���0��ʼ

	tagTXmpuSynChn()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID	= 0;
		m_dwHandle = 0;
		m_bySynChn = 0xff;
	}

}TXmpuSynChn;

class CUmsXmpuInst;
class CEqpBaseHandle
{
public:
	CEqpBaseHandle(CUmsXmpuInst* pInst);
	CEqpBaseHandle() {}
	virtual ~CEqpBaseHandle();
	
public:

	virtual void Init();	
	virtual BOOL32 AssignEqpEx(TXmpuEqpParam* ptEqpParam) = 0;
	virtual BOOL32 ReleaseEqpEx(TXmpuEqpParam* ptEqpParam) = 0;
 	virtual void Show();
	virtual void ShowAll();
	void NotifyMsgToEqp(u32 dwDstNode, u32 dwDstInst, u16 wEvent, void* body, u16 bodyLen);
	
public:
	virtual BOOL32 StopConf(u16 wConfID) = 0;
public:
	virtual BOOL32 Handle(CTpMsg *const ptMsg) = 0;

	virtual u16 OnGetUsedNum() = 0;
	
protected:
	CUmsXmpuInst* m_pcInst;
};

typedef BOOL32 (CEqpBaseHandle::*PCMsgFunc)(CMessage *const pcMsg);

s8* GetXmpuEqpStatBuf( EmXmpuEqpStat emStat );

s8* GetSynType( u16 wIndex );

#endif // _ums_inner_struct_