#ifndef _h_putaud_h__
#define _h_putaud_h__

#include "umsconfinst.h"
#include "callinnerstruct.h"

#define		EmPutAudUser			u16
#define		em_putauduser_none		u16(0)
#define		em_putauduser_discuss	u16(1)
#define		em_putauduser_rollcall	u16(2)
#define		em_putauduser_audmix	u16(3)


typedef struct tagTPutAudChnl
{
	u16	   m_wIndx;
	BOOL32 m_bUsed;
	u16	   m_wEpID;
	TTPMediaTransAddr* m_aptLocalAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr m_atRmtAddr[TP_MAX_STREAMNUM];

	u16		m_wUsedNum;

	u16		m_wCheck;

	EmPutAudUser		m_emUser;
	
	CDsListInfo	m_tDs;
	tagTPutAudChnl()
	{
		Clear();
	}

	void Clear()
	{
		m_bUsed = FALSE;
		m_wEpID = TP_INVALID_INDEX;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_aptLocalAddr[wIndex] = NULL;
			m_atRmtAddr[wIndex].Clear();
		}
		m_emUser = em_putauduser_none;
		m_wCheck = 0;
		m_wUsedNum = 0;
		m_tDs.Clear();
	}

	BOOL32 IsExist()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}
}TPutAudChnl;

class CPutAud
{
public:
	CPutAud(CUmsConfInst* pcInst);
	~CPutAud();
	
	BOOL32 Handler( CTpMsg *const ptMsg );
	void Show();

	BOOL32 AssignAudChnl(u16 wEpID, EmPutAudUser emUser, TTPMediaTransAddr atAddr[]);
	void ReleaseAudChnl(u16 wEpID, EmPutAudUser emUser);

	void ReleaseAll(EmPutAudUser emUser);

	void GetAudLocalAddr(u16 wEpId, EmPutAudUser emUser, TTPMediaTransAddr atAddr[]);  // 下级使用，取得上级下传的音频码流地址

protected:
	void OnAudChnlReq(CTpMsg *const ptMsg);
	void OnAudChnlRsp(CTpMsg *const ptMsg);
	void OnAudChnlClose(CTpMsg *const ptMsg);

	TPutAudChnl* FindIdle();
	TPutAudChnl* FindByEpID(u16 wEpID, EmPutAudUser emUser);
	void ReleaseRepeatdPutAudForDown(u16 wConfid, u16 wEpID, EmPutAudUser emUser);
private:
	CUmsConfInst* Inst()	{ return m_pcConf; }
	
protected:
	CUmsConfInst* m_pcConf;

	TPutAudChnl	m_atChanle[MAX_AUDMIX_MDL_NUM];
};


#endif // _h_putaud_h__