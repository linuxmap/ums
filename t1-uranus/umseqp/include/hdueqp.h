#ifndef HDU_EQP_H_
#define HDU_EQP_H_
#include "umseqp.h"
#include "hdudef.h"
#include "eqpmgr.h"
#include "tphdu2.h"

typedef struct tagTHduChanFrame
{
	u32 m_dwFrameP;
	tagTHduChanFrame()
	{
		Clear();
	}

	void Clear()
	{
		m_dwFrameP = 0;
	}

	BOOL32 CheckFrame()
	{
		time_t t;
		time(&t);
		u32 dwNow = t;
		
		if ( dwNow - m_dwFrameP >= 2  )
		{
			m_dwFrameP = dwNow;
			return TRUE;
		}
		return FALSE;
	}
}THduChanFrame;

class CHduModle : public CEqpModle
{
public:
	u32				m_dwBrdIns;		//����instance
	u8				m_byStartMode;	//����ģʽ(0: hdu_2, 1: hdu_1, 2: hdu_L)
	u16				m_wStartPort;
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];
	THduChanFrame	m_atSubChanAskKey[HDU_MAX_VMP_SUBCHAN];
	BOOL32			m_bServiceReged;	//ҵ���Ƿ��Ѿ�ע����

	u16				m_wEqpID;	//
	BOOL32			m_bQtVer;

public:
	CHduModle() :  CEqpModle()
	{
		Clear();
	}
	void Clear()
	{
		m_dwBrdIns = 0;
		m_byStartMode = 0;
		m_wStartPort  = 0;
		m_bServiceReged = FALSE;
		m_wEqpID = 0;
		m_bQtVer = FALSE;

		for (u16 wIndex = 0; wIndex < HDU_MAX_CHANNEL_NUM; ++wIndex)
		{
			m_atChanInfo[wIndex].Clear();
		}
		CEqpModle::Clear();
	}

	void SetBrdPos(const TTPBrdPos& tBrdPos)
	{
		m_tRegInfo.m_dwEqpIP = tBrdPos.m_dwBrdIP;
		if (tBrdPos.m_emBrdType == em_hdu2_qt_brd)
		{	
			m_bQtVer = TRUE;
		}
		else
		{
			m_bQtVer = FALSE;
		}
	}

	void SetChanInfo(const THduInfo& tHduInfo)
	{
		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			memcpy(&(m_atChanInfo[byIndex]), &(tHduInfo.m_atChanInfo[byIndex]), sizeof(THduChanInfo));
		}
	}

	void SetCfgInfo(const THduCfgInfo& tInfo)
	{
		m_byStartMode = tInfo.m_byStartMode;
		m_tRegInfo.m_dwEqpIP = tInfo.m_dwIP;
		m_bQtVer = tInfo.m_bQtHdu;
		for (u8 byIndex = 0; byIndex < tInfo.m_byChanNum; ++byIndex)
		{
			memcpy(&(m_atChanInfo[byIndex]), &(tInfo.m_atChanInfo[byIndex]), sizeof(THduChanInfo));
		}
	}
};

class CHduEqp : public CEqpBase
{
public:
	CHduEqp(CUmsEqpInst* pInst);
	virtual ~CHduEqp();

public:
	//��֤������Ϣ
	BOOL32		CheckBrdInfo(const TTPBrdRegInfo& tBrdInfo, u32 dwNode, u32 dwIns);
	//���ð��ӵ�EQPID
	void		SetBrdEqpID(u8 byLayer, u8 bySlot, u16 wEqpID);
	//���Ҷ�Ӧ�İ����Ƿ�ע��
	BOOL32		FindRegBrd(const TTPBrdPos& tBrdInfo);
	// ��ȡ����ǽ�İ汾
	BOOL32		GetHduVer(const TTPBrdPos& tBrdInfo, u8& byHduVer);

public:
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Init();
	virtual void Show();

	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 OnDisConnect(u32 dwNode);

private:
	//����
	void		EventDisconnect(CTpMsg* const ptMsg);
	//ע��
	void		EventRegReq(CTpMsg *const ptMsg);
	//��������
	void		EventReboot(CTpMsg *const ptMsg);
	//�޸İ�����Ϣ
	void		EventBrdModify(CTpMsg *const ptMsg);
	//��������
	void		EventUpdateBrd(CTpMsg *const ptMsg);
	//�������ӽ��
	void		EventBrdUpdateAck(CTpMsg *const ptMsg);
	//�޸�ͨ����Ϣ
	void		EventChanModify(CTpMsg *const ptMsg);
	//ɾ������
	void		EventDel(CTpMsg *const ptMsg);
	//������Ϣ
	void		EventCfgInfo(CTpMsg* const ptMsg);
	//��������
	void		EventPlayReq(CTpMsg* const ptMsg);
	//��������Ӧ��
	void		EventPlayAck(CTpMsg* const ptMsg);
	void		EventPlayNack(CTpMsg* const ptMsg);

	//ֹͣ����
	void		EventStopPlyaReg(CTpMsg* const ptMsg);
	void		EventStopPlayAck(CTpMsg* const ptMsg);
	void		EventStopPlayNack(CTpMsg* const ptMsg);
	
	//����ͨ��״̬
	void		EventUpdateChanStatus(CTpMsg* const ptMsg);
	//����ҵ��״̬
	void		EventUpdateStatus(CTpMsg* const ptMsg);
	//
	void		EventReqIFrame(CTpMsg* const ptMsg);
	void		EventSetVol(CTpMsg* const ptMsg);

	void        EventChangeHduChanMode(CTpMsg* const ptMsg);
	void        EventChangeHduChanModeRes(CTpMsg* const ptMsg);

	void		EventMediaKeyNty(CTpMsg* const ptMsg);
private:
	u8			GetLayer(u8 byIndex);
	u8			GetSlot(u8 byIndex);
	u16			GetIndex(u8 byLayer, u8 bySlot);

private:
	CHduModle*	FindModleByIP(u32 dwIP, u8& byVal);
	CHduModle*	FindModule(u16 wEqpID, u8& byVal);
	CHduModle*	FindModleByIns(u32 dwInsID, u8& byVal);
	void		NotifyHduInfoToServer(u16 wEvent, u8* pbyMsg = NULL, u16 wLen = 0);
	void		SendMsgToEqpSsn(u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg, u16 wLen);

private:
	CHduModle	m_acHduModle[HDU_MAX_NUM];		//�������е���ǽ����Ϣ

};

inline u8 CHduEqp::GetLayer(u8 byIndex)
{
	return byIndex / HDU_MAX_SLOT;
}

inline u8 CHduEqp::GetSlot(u8 byIndex)
{
	return byIndex % HDU_MAX_SLOT;
}

inline u16 CHduEqp::GetIndex(u8 byLayer, u8 bySlot)
{
	u16 wIndex = byLayer*HDU_MAX_SLOT+bySlot;
	return wIndex;
}

#endif