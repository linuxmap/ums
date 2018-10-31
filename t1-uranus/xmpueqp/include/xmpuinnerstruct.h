#ifndef _ums_inner_struct_
#define _ums_inner_struct_
#include "umsobject.h"
#include "eqpinterface.h"
#include "tpsys.h"
#include "tpcommontype.h"
#include "umsxmpinterface.h"


//Hdu/Vmp/Mix的用户数据类型声明
typedef    u32	APPHANDLE;     //上层业务APP句柄    
// 句柄定义
typedef    u32	HMEDIARES;     // 媒体句柄

#define  XMPU_USERDATE_BEGIN  1500


enum EmXmpuEqpStat
{
	XmpuEqpStat_Idle,   //
	XmpuEqpStat_Starting, //正在开启，中间状态
	XmpuEqpStat_Running, //正在工作
	XmpuEqpStat_Error,  //异常
};

// 一块xmpu2上有 12个Netro芯片 一个6678芯片
//Netro芯片3个作为一组能抽象出 4个画面合成器（每个画面合成器最大支持25风格）或4*4个视频适配通道（4个里 2大 2小）
//一个6678芯片支持6个大混音器（每个最大192路，大混音器可再拆分成两个小混音器）或是12个小混音器（可支持10路），
//一个6678芯片支持7个音频适配器（1进4出）混音和音频视频同时存在
typedef struct tagTMediaEqpMgr
{
	//总数量
	u32   m_dw264VmpCnt;           //仅支持264的vmp数量
	u32   m_dw265_264VmpCnt;       //支持264或265的vmp数量
	u32   m_dw264BasCnt;           //仅支持264的vbas数量
	u32   m_dw265_264BasCnt;       //仅支持264或265的vmp数量
	u32   m_dwABasCnt;             //aud bas数量
	u32   m_dwMixer8Cnt;           //仅支持8方的mixer数量
	u32   m_dwMixer192Cnt;         //仅支持192方的mixer数量
	u32   m_dw264Port;             //仅支持264的端口资源数量
	u32   m_dw265Port;             //仅支持265的端口资源数量

	//已用数量
	u32   m_dw264VmpUsedCnt;           //仅支持264的vmp数量
	u32   m_dw265_264VmpUsedCnt;       //支持264或265的vmp数量
	u32   m_dw264BasUsedCnt;           //仅支持264的vbas数量
	u32   m_dw265_264BasUsedCnt;       //仅支持264或265的vmp数量
	u32   m_dwABasUsedCnt;             //aud bas数量
	u32   m_dwMixer8UsedCnt;           //仅支持8方的mixer数量
	u32   m_dwMixer192UsedCnt;         //仅支持192方的mixer数量
	u32   m_dw264UsedPort;             //仅支持264的端口资源数量
	u32   m_dw265UsedPort;             //仅支持265的端口资源数量
	
	//初始化数量
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
	u32					m_dwEqpID; //业务句柄
	HMEDIARES		m_dwHandle; //业务句柄
	u8					m_bySynChn;  //同步的通道号，从0开始

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