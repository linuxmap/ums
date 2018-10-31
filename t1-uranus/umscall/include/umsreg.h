#ifndef _h_umsreg_h__
#define _h_umsreg_h__
#include "tpstruct.h"
#include "tphandle.h"
#include "umscommonstruct.h"
#include "umsinnerstruct.h"


#define UMS_MAX_TEMPCONF_NAME 2
#define INVALID_STACK_HANDLE 0
#define CONFTEMP_HANDLE_START 6000
#define UMS_REQ_Timer   5

class CUmsRegMgr : public CTpHandler
{
public:
	CUmsRegMgr(CTpObject* pcObject);
	virtual ~CUmsRegMgr();

	BOOL32 Handler( CTpMsg *const ptMsg );
	TUmsSipRegCfg& GetCfg()	{return m_tRegCfg;}
	virtual BOOL32  Create();
	void Show();
protected:
	void EventReg(u8* pData, u16 wDataSize);
	void EventUnReg(u8* pData, u16 wDataSize);

	void EventReqRegInfo(CTpMsg* const ptMsg);
	void EventReqRegInfoRet(u8* pData, u16 wDataSize);
	void EventUmsRegInfoRet(u8* pData, u16 wDataSize);
	void EventCnsRegInfoRet(u8* pData, u16 wDataSize);
	void EventMtRegInfoRet(u8* pData, u16 wDataSize);
	void EventMcuRegInfoRet(u8* pData, u16 wDataSize);

	void EventRegRet(u8* pData, u16 wDataSize);
	void EventUnRegRet(u8* pData, u16 wDataSize);
	void Event323UnRegRet(u8* pData, u16 wDataSize);

	void EventAdapterReg(u8* pData, u16 wDataSize);
	void EventAdapterUnReg(u8* pData, u16 wDataSize);
	void EventHandleInfo(u8* pData, u16 wDataSize);
	void EventSipRegTimer(u8* pData, u16 wDataSize);
	void EventGkRegTimer(u8* pData, u16 wDataSize);

	void EventUpdateSipCfg(u8* pData, u16 wDataSize);
	void EventUpdateGkCfg(u8* pData, u16 wDataSize);

protected:
	void Reg(u16 wCurIndex, EmRegType emRegType);
	void UnReg(EmRegType emRegType, const EmRegGroupNum& emGroupNum = em_AllGroup, BOOL32 bFromServer = FALSE);

	void MakeAdapterHandle(TUmsHandle& tHandle, u16 wIndex, EmRegType emRegType);

private:
	void ClearSipRegState();
	void ClearGkRegState();

	void ClearRegResultInfo(u16 wIndex)
	{
		if (wIndex < TP_TEMPGROUP_MAXNUM)
		{
			m_atRegResultInfo[wIndex].clear();
			m_adwResultPAHandle[wIndex] = 0;
			m_abRegResValid[wIndex] = FALSE;
		}
	}
	void ClearGkRegResultInfo(u16 wIndex)
	{
		if (wIndex < TP_TEMPGROUP_MAXNUM)
		{
			m_atGkRegResultInfo[wIndex].clear();
			m_adwGKResultPAHandle[wIndex] = 0;
			m_abGkRegResValid[wIndex] = FALSE;
		}
	}
public:
	void    GkResultFailProcess(u16 wAppId ,TUCSipRegResult* ptResult );
	void    SipResultFailProcess(u16 wAppId ,TUCSipRegResult* ptResult );
	void	StartTempReg(TUmsConfBase& tTemp, u16 wConfID);//������ʱģ��ע����Ϣ
	void	StopTempReg(u16 wConfID);
	void    UndoTempReg(u16 wConfID);
	void	TempReg(const EmRegType& emType, u16 wIndex);//��ʱģ��ע��
	void	TempReg(const EmRegType& emType);
	void	TempHandleInfo(u8* pData, u16 wDataSize);

	void	TempSipRegFailed(u8* pData, u16 wDataSize);
	void	Temp323RetFailed(u8* pData, u16 wDataSize);

	void	TempRegSuccess(u8* pData, u16 wDataSize);//��ʱģ��ע����

	void	TempRegRetHandle(u16 wIndex);

	BOOL32  IsRegSuccess(const EmRegType& emRegType) const;  // ��Ӧ����ע���Ƿ�ɹ�

protected:
	TUmsSipRegCfg m_tRegCfg;
	TRegCfg		  m_tGkRegCfg;

	TUCSipRegResult m_atRegResultInfo[TP_TEMPGROUP_MAXNUM];//ע��ʧ�ܽ����Ϣ
	u32				m_adwResultPAHandle[TP_TEMPGROUP_MAXNUM];
	BOOL32 m_abRegResValid[TP_TEMPGROUP_MAXNUM];//ע���Ƿ���Ч��ʶ��Ϊtrue������Ч

	TUCSipRegResult m_atGkRegResultInfo[TP_TEMPGROUP_MAXNUM];//ע��ʧ�ܽ����Ϣ
	u32				m_adwGKResultPAHandle[TP_TEMPGROUP_MAXNUM];
	BOOL32 m_abGkRegResValid[TP_TEMPGROUP_MAXNUM];//ע���Ƿ���Ч��ʶ��Ϊtrue������Ч

	u16 m_wSipAliasNum[TP_TEMPGROUP_MAXNUM];
	u16 m_wGKAliasNum[TP_TEMPGROUP_MAXNUM];
	TTPAlias m_atAlias[TP_TEMPGROUP_MAXNUM][TP_CONFTEMPGROUP_MAXNUM];
	
	u32	m_dwStackHandle[TP_TEMPGROUP_MAXNUM];		//Э��ջ���
	u32 m_dwGkRegHandle[TP_TEMPGROUP_MAXNUM];		//323ע��Э��ջ���
	
	BOOL32	m_bGkUnRegPack[TP_TEMPGROUP_MAXNUM];	//��ʶ323δע���ϵİ�
	BOOL32  m_bSipUnRegPack[TP_TEMPGROUP_MAXNUM];	//��ʶsipδע���ϵİ�

//add temp template reg
	TTPAlias m_atTempAlias[TP_UMS_MAX_CONFNUM][UMS_MAX_TEMPCONF_NAME];//���16����ʱģ�壬ÿ��ģ���������2������
	
	u32 m_adwTempGkRegHandle[TP_UMS_MAX_CONFNUM];
	u32	m_adwTempSipRegHandle[TP_UMS_MAX_CONFNUM];
// 
 	EmUmsRegState	m_aemTempGkRegState[TP_UMS_MAX_CONFNUM];
 	EmUmsRegState	m_aemTempSipRegState[TP_UMS_MAX_CONFNUM];
//end add
	
	TRegAdapter*	m_ptCurAdapt;
	TRegAdapter		m_atRegAdapt[TP_MAX_NUM_CONTACT_ADDR];

	BOOL32 m_bIsSipRegged[TP_TEMPGROUP_MAXNUM];
	BOOL32 m_bisGkRegged[TP_TEMPGROUP_MAXNUM];
	
};

#endif // _h_umsreg_h__
