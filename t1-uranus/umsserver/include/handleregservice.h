#ifndef _h_handleregservice_h__
#define _h_handleregservice_h__
#include "tpstruct.h"
#include "tpsys.h"
#include "tphandle.h"
#include "umsinnertype.h"
#include "umsconfig.h"
#include "umsinnerstruct.h"


class CUmsRegHandleService : public CTpHandler
{
public:
	CUmsRegHandleService(CTpObject* pcObjec);
	~CUmsRegHandleService();
	
public:
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	virtual BOOL32 Create();

public:
	void ShowRegState();
	
protected:
	void EventLogin(void* pDataBuf, u16 wDataSize);
	void EventLogout(u8* pDataBuf, u16 wDataSize);
	void EventSetRegCfg(u8* pDataBuf, u16 wDataSize);
	void EventSetGkRegCfg(u8* pDataBuf, u16 wDataSize);
	void EventRegReq(u8* pDataBuf, u16 wDataSize);
	
	void EventRegRet(u8* pData, u16 wDataSize);
	void EventUnRegRet(u8* pData, u16 wDataSize);
	void EventReqRegInfo(CTpMsg *const ptMsg);
	void EventReqRegInfoRet(CTpMsg* const ptMsg);
	void EventUmsRegInfoRet(CTpMsg* const ptMsg);
	void EventCnsRegInfoRet(CTpMsg* const ptMsg);
	void EventMtRegInfoRet(CTpMsg* const ptMsg);
	void EventMcuRegInfoRet(CTpMsg* const ptMsg);
	void EventUpdateReg(const EmRegGroupNum& emGroupNum,BOOL32 bUpdateQtID = FALSE);
	void EventAdapterRegOut(u8* pData, u16 wDataSize);
protected:
	void Register( EmRegGroupNum emRegGroupNum, EmRegType emRegType);
	void UnRegister(EmRegType emRegType, EmRegGroupNum emGroupNum = em_AllGroup, BOOL32 bForce = FALSE);

private:
	//发送B2的全局地址薄给用户
	void PostRegInfoToUserEx();
	//发送指定类型的注册信息给指定的用户
	void PostRegInfoToUser(TLogUser& tUser, const EmGetRegInfoType& tType);
	//通知维护工具UMS的SIP和GK的注册信息
	void NotifyRegInfoToTpTool();

public:
	//清除SIP的注册结果
	void ClearRegRet(const EmRegType& emRegType, const EmRegGroupNum& emGroupNums = em_AllGroup);
	//将某个数据包的状态切换为正在注册状态
	void SetGroupReging(const EmRegType& emRegType, const EmRegGroupNum& emGroupNums = em_AllGroup);
	//对应的注册类型是否成功注册一包
	BOOL32 IsRegOneGroup(const EmRegType& emRegType) const;
	//检查对应注册类型的每包的注册状态，有一包为成功或者正在注册则返回TRUE
	BOOL32 IsReg(const EmRegType& emRegType);

public:
	void  UpdateReg(const EmRegGroupNum emGroupNum);
    void  UpdateQtId(const u32 dwQtid);
public:

	//注册结果以及失败原因
	typedef struct tagRegRet
	{
		EmUmsRegState	m_emRegState;	//注册状态
		EmTpCnsRegUms	m_emReason;		//注册失败的原因

		tagRegRet()
		{
			Clear();
		}

		void Clear()
		{
			m_emRegState = em_un_reg;
			m_emReason   = tp_CnsRegRet_Unknow;
		}
	}TRegRet;

protected:
	u16					m_wTempGroupNum;//注册分组的实际个数
	TTPSipRegistrarCfg  m_tSipRegCfg;	//目前只用到CFG中的信息，不包括别名等，别名数据另外发
	TTPGKCfg			m_tGKRegCfg;	//GK注册信息
	BOOL32				m_bReqRegInfo;	//是否查询过注册信息

	TRegRet				m_atRegRet[TP_TEMPGROUP_MAXNUM][em_reg_type_end];	//每包的注册结果
};

#endif // _h_handleregservice_h__
