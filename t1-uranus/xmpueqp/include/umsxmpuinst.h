#ifndef _xmpu_inst_ 
#define _xmpu_inst_ 

#include "eqpinterface.h"
#include "umsobject.h"
#include "xmpuinnerstruct.h"

typedef struct tagTEqpHandle
{
	CEqpBaseHandle* m_pcHandle;
	EMXmpuEqpType	m_emEqpType;
	
	tagTEqpHandle() { Clear(); }
	void Clear()
	{
		m_pcHandle = NULL;
		m_emEqpType = em_Xmpu_unknow;
	}
}TEqpHandle;

typedef struct tagTXmpuSynInfo
{
	u32					m_dwSynID;
	TXmpuSynChn m_atSynChn[TP_MAX_STREAMNUM];
	tagTXmpuSynInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_dwSynID = 0;
		memset(m_atSynChn, 0, sizeof(m_atSynChn));
	}
	BOOL32 IsUsing()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (m_atSynChn[wIndex].m_dwHandle !=0)
			{
				return TRUE;
			}
		}
		return FALSE;
	}

}TXmpuSynInfo;

typedef struct tagTXmpuSynMsg
{
	u16					m_wConfID;
	s8						m_achConfE164[TP_MAX_ALIAS_LEN+1];	//会议e164
	s8						m_achConfName[TP_MAX_ALIAS_LEN+1];	//会议名称
	u8					m_bySynNum;
	TXmpuSynInfo	m_abySynInfo[XMPU_MAX_SYN_NUM];

	tagTXmpuSynMsg()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = 0;
		m_bySynNum = 0;
		memset(m_achConfE164, 0, sizeof(m_achConfE164));
		memset(m_achConfName, 0, sizeof(m_achConfName));
		memset(m_abySynInfo, 0, sizeof(m_abySynInfo));
	}

	BOOL32 IsValidConfID()
	{
		if (m_wConfID > 0 && m_wConfID <= TP_UMS_MAX_CONFNUM)
		{
			return TRUE;
		}

		return FALSE;
	}
}TXmpuSynMsg;

class CXmpuSem
{
public:
	CXmpuSem(s8* pszPos, u32 dwLine);
	~CXmpuSem();
};
#define CHECK_XMPU_SEM CXmpuSem cCheckXmpuSem(__FILE__, __LINE__);

class CUmsXmpuInst :  public CUmsObject
{
public:
    CUmsXmpuInst();
	~CUmsXmpuInst();

	enum EmXmpuHandle
	{
		_CVmpEqpHandle,
		_CVidBasEqpHandle,
		_CAudioBasEqpHandle,
		_CAudioMixEqpHandle,

		_CEqpHandleEnd,
	};

	enum xmpu_dump
	{
		dump_showxmpu,
		dump_showsyn,
		dump_showxmpuall,
	};
	
public:
	BOOL32 AssignEqpEx(TXmpuEqpParam* ptEqpParam);
	BOOL32 ReleaseEqpEx(TXmpuEqpParam* ptEqpParam);

	BOOL32 InitMeeting(TXmpuMettingInfo tInfo);
	BOOL32 ReleaseMeeting(u16 wConfID);
	BOOL32 InitMediaClient();
	void SetSynID(u16 wConfID, EMXmpuSynType emSynIndex, TXmpuSynChn* ptSynChn);
	
	void OnGetUsedXmpu();
	u32 GetVmpCnt() {return m_tEqpMgr.m_dw264VmpCnt;}
	void XmpuTime(BOOL32 bStart);
protected:
	virtual BOOL PreMessageProc ( CMessage *const ptMsg ); 
	virtual void MessageProc( CTpMsg *const ptMsg);
	
	BOOL32 ObjectInit(u32 wParam, u32 lParam);
	void ObjectExit();
	
protected:
	
	virtual void InstanceDump(u32=0);

private:
	void OnInitMettingRsp(CTpMsg *const ptMsg);
	TXmpuSynMsg* FindSynMsg(u16 wConfID);
	TXmpuSynMsg* FindIdleSynMsg();
	CEqpBaseHandle* GetHandle(EMXmpuEqpType emEqp);

	void SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen );

	void  OnGetXmpuIdleResReq(CTpMsg *const ptMsg);
	void OnGetXmpuResourceTime();
	void OnRefreshXmpuResourceTime();

	void ShowEqp();
	void ShowSynInfo();
	void ShowEqpAll();

private:
	TEqpHandle	m_atEqpHandle[_CEqpHandleEnd];
	TMediaEqpMgr m_tEqpMgr;
	TXmpuSynMsg	m_atSynMsg[TP_UMS_MAX_CONFNUM];
};

typedef zTemplate<CUmsXmpuInst, 1> CUmsXmpuApp;


#endif // _xmpu_inst_