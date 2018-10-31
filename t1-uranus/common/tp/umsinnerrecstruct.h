#ifndef _umsinner_rec_struct_h_
#define _umsinner_rec_struct_h_
#include "tptype.h"
#include "tpsys.h"
#include "umsinnerstruct.h"

//¼��ͨ��������Ϣ
class CBaseRecChanInfo
{
public:
	CBaseRecChanInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_emRecType = em_rec_recorder_unknow;
		m_wConfID = 0;
		m_wMtID = 0;
	}

public:
	EmRecorderType	m_emRecType;	//¼������
	u16				m_wConfID;		//����ID
	u16				m_wMtID;		//�᳡ID
};

//¼��ͨ��ʹ����Ϣ
class CRecChanUseInfo : public CBaseRecChanInfo
{
public:
	CRecChanUseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byRecChan= 0;
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_emRecState = em_rec_unknow;
		m_dwRecTime = 0;
		m_bRecDual = FALSE;
		m_tDualFormat.Clear();
		m_tDVidRcvAddr.Clear();
		m_tDAudRcvAddr.Clear();
		m_tConfRecInfo.Clear();
		m_tMtRecInfo.Clear();
		
		CBaseRecChanInfo::Clear();
	}

public:
	u8					m_byRecChan;	//¼��ͨ����
	s8					m_achFileName[TP_REC_FILE_LEN];
	EmConfRecState		m_emRecState;	//¼��״̬
	u32					m_dwRecTime;	//¼��ʱ��
	BOOL32				m_bRecDual;		//¼��˫��
	TCallVidFormat		m_tDualFormat;
	TTPTransAddr		m_tDVidRcvAddr;
	TTPTransAddr		m_tDAudRcvAddr;

	TStartConfRecInfo	m_tConfRecInfo;
	TStartMTRecInfo		m_tMtRecInfo;
};

//����ͨ���Ļ�����Ϣ
class CBasePlayChanInfo
{
public:
	CBasePlayChanInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = 0;
	}

public:
	u16				m_wConfID;	//����ID
};


class CPlayChanUseInfo : public CBasePlayChanInfo
{
public:
	CPlayChanUseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_bPlayInDual = FALSE;
		m_byRecChan = 0;
		m_emRecState = em_rec_unknow;
		m_dwTotalTime = 0;
		m_dwCurTime = 0;
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_emVidFormat = emTPVH264;
		m_emDVidFormat = emTPVH264;
		m_emVidRes = emTPVResEnd;
		m_emDVidRes = emTPVResEnd;

		CBasePlayChanInfo::Clear();
	}

public:
	BOOL32				m_bPlayInDual;
	u8					m_byRecChan;
	EmConfRecState		m_emRecState;
	s8					m_achFileName[TP_REC_FILE_LEN];
	u32					m_dwTotalTime;
	u32					m_dwCurTime;

	EmTpVideoFormat		m_emVidFormat;
	EmTpVideoFormat		m_emDVidFormat;
	EmTpVideoResolution m_emVidRes;
	EmTpVideoResolution m_emDVidRes;
};

//���������Ϣ����
class CConfPlayMgr : public CNodeBase
{
public:
	CConfPlayMgr():CNodeBase(em_Node_Player) { Clear(); }

public:
	void				Clear()
	{
		m_bPlaying = FALSE;
		m_wPlayEpID = 0;
		m_tInfo.Clear();
	}

public:
	BOOL32				IsChairPlay() const { return m_wPlayEpID == CALLER_EP_INDEX; }
	u16					GetPlayEpID() const { return m_wPlayEpID; }
	void				SetPlayEpID(u16 wEpID) { m_wPlayEpID = wEpID; }
	BOOL32				IsPlaying() const { return m_bPlaying; }

public:
	BOOL32				m_bPlaying;		//�Ƿ��ڷ���
	u16					m_wPlayEpID;	//����UMS ID �ϼ�ʹ��
	TPlayTrans			m_tInfo;
};


class CConfRec : public CNodeBase
{
public:
	u8		m_byEqpID;
	u8		m_byChanID;
	
	EmRecorderType	m_emRecType;
	BOOL32			m_bRecDual;
	TUmsVidFormat	m_tDualFormat;
	TTPTransAddr	m_tDVidRcvAddr;
	TTPTransAddr	m_tDAudRcvAddr;
	
	TTPTransAddr	m_tVidRcvAddr;
	TTPTransAddr	m_tAudRcvAddr;
	TUmsVidFormat	m_tConfFormat;

	CDsListInfo		m_cDsList;

protected:
	CConfRec& operator = (const CConfRec&);
	CConfRec(CConfRec&);
public:	
	CConfRec()
		:CNodeBase(em_Node_RecConf)
	{
		Clear();
	}
	
	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = INVALID_REC_CHANNEL;
		m_emRecType = em_rec_recorder_unknow;
		m_bRecDual = FALSE;

		m_tDualFormat.Clear();
		m_tDVidRcvAddr.Clear();
		m_tDAudRcvAddr.Clear();

		m_tVidRcvAddr.Clear();
		m_tAudRcvAddr.Clear();
		m_tConfFormat.Clear();
	}
	void SetValue(TRecConfTrans& tInfo)
	{
		m_byEqpID = tInfo.m_byEqpID;
		m_byChanID = tInfo.m_byChanID;
		
		m_emRecType = tInfo.m_emRecType;
		m_bRecDual = tInfo.m_bRecDual;
		m_tDualFormat = tInfo.m_tDualFormat;
		m_tDVidRcvAddr = tInfo.m_tDVidRcvAddr;
		m_tDAudRcvAddr = tInfo.m_tDAudRcvAddr;

		if (em_rec_recorder_mt == m_emRecType)
		{
			m_tVidRcvAddr = tInfo.m_tMtInfo.m_tVidRcvAddr;
			m_tAudRcvAddr = tInfo.m_tMtInfo.m_tAudRcvAddr;
			m_tConfFormat = tInfo.m_tMtInfo.m_tConfFormat;
		}
		else if (em_rec_recorder_conf == m_emRecType)
		{
			m_tVidRcvAddr = tInfo.m_tConfInfo.m_tVidRcvAddr;
			m_tAudRcvAddr = tInfo.m_tConfInfo.m_tAudRcvAddr;
			m_tConfFormat = tInfo.m_tConfInfo.m_tConfFormat;
		}
	}
};


class CMtRec : public CNodeBase
{
public:
	u8		m_byEqpID;
	u8		m_byChanID;
	
	EmRecorderType	m_emRecType;
	BOOL32			m_bRecDual;
	TUmsVidFormat	m_tDualFormat;
	TTPTransAddr	m_tDVidRcvAddr;
	TTPTransAddr	m_tDAudRcvAddr;
	
	u16				m_wMtID;
	TTPTransAddr	m_tVidRcvAddr;
	TTPTransAddr	m_tAudRcvAddr;
	CDsListInfo		m_cDsList;

protected:
	CMtRec& operator = (const CMtRec&);
	CMtRec(CMtRec&);
	
public:	
	CMtRec()
		:CNodeBase(em_Node_RecMt)
	{
		Clear();
	}
	
	void Clear()
	{
		m_byEqpID = 0;
		m_byChanID = INVALID_REC_CHANNEL;
		m_emRecType = em_rec_recorder_unknow;
		m_bRecDual = FALSE;

		m_tDualFormat.Clear();
		m_tDVidRcvAddr.Clear();
		m_tDAudRcvAddr.Clear();

		m_wMtID = 0;
		m_tVidRcvAddr.Clear();
		m_tAudRcvAddr.Clear();		
	}	

	void SetValue(TRecConfTrans& tInfo)
	{
		m_byEqpID = tInfo.m_byEqpID;
		m_byChanID = tInfo.m_byChanID;
		
		m_emRecType = tInfo.m_emRecType;
		m_bRecDual = tInfo.m_bRecDual;
		m_tDualFormat = tInfo.m_tDualFormat;
		m_tDVidRcvAddr = tInfo.m_tDVidRcvAddr;
		m_tDAudRcvAddr = tInfo.m_tDAudRcvAddr;

		m_wMtID = tInfo.m_tMtInfo.m_wMtID;
		m_tVidRcvAddr = tInfo.m_tMtInfo.m_tVidRcvAddr;
	    m_tAudRcvAddr = tInfo.m_tMtInfo.m_tAudRcvAddr;
	}
};

#endif