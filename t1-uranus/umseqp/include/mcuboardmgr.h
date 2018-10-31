#ifndef _MCUBOARDMGR_H_
#define _MCUBOARDMGR_H_

#include "umsobject.h"
#include "mcudef.h"
#include "tpsys.h"
#include "servicehandler.h"

//响应mcu那边的单板 板子类消息
class CTPMcuBrdReg : public CUmsObject
{
public:
	CTPMcuBrdReg() {  }
	~CTPMcuBrdReg() {  }
protected:

	virtual BOOL PreDaemonMessageProc( CMessage *const ptMsg );

	virtual BOOL PreMessageProc( CMessage *const ptMsg );
	virtual void MessageProc(CTpMsg *const ptMsg);
	
	virtual BOOL32 DaemonObjectInit(u32 wParam, u32 lParam);
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam) { SetLogTitle("[McuBrdReg]"); return TRUE; }
private:

	void SendMsgToUmsEqp( u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );
	void SendMsgToBrd( u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );

	void OnDaemonBrdReg(CMessage *const ptMsg, CApp* pcApp);
	void OnBrdReg(CMessage *const ptMsg);
	void OnBrdRegAck(CTpMsg *const ptMsg);
	void OnBrdGetCfgReq(CMessage *const ptMsg);
	void OnBrdGetCfgAck(CTpMsg *const ptMsg);
	void OnDisconnect( CMessage *const ptMsg );

	void OnBrdSwitchNty( CMessage *const ptMsg );
	
	void OnBrdHDVersionRsp(CMessage *const ptMsg);
	void OnMpuUpdate(CTpMsg* const ptMsg);
	void OnBrdSoftWareUpdateNtfy(CMessage *const ptMsg);


	void OnSwitchTelnetFtpCmd( CTpMsg *const ptMsg );

private:
	void OnMpuGetCfgAck(u8* pData, u16 wDataSize);
	void OnHduGetCfgAck(u8* pData, u16 wDataSize);
	void OnApu2GetCfgAck(u8* pData, u16 wDataSize);

	u16	 FindBrdArrayIndex(u8 byLate, u8 bySlot);	//根据注册带来的信息找出所存数组中的索引

public:
	void InstClear();
private:
	u32		m_dwBrdNode;//该外设的node
	u32		m_dwBrdIID;//该外设的IID
};
typedef zTemplate<CTPMcuBrdReg, TP_BOARD_MAX_NUM + HDU_MAX_NUM> CTPMcuBrdRegApp;

//响应mcu那边的单板 业务类消息
class CTPMcuBrdSsn : public CUmsObject
{
public:
	CTPMcuBrdSsn() { m_dwBrdNode = INVALID_NODE; };
	~CTPMcuBrdSsn() { m_dwBrdNode = INVALID_NODE; };
	
protected:
	virtual BOOL PreDaemonMessageProc( CMessage *const ptMsg );

	virtual BOOL PreMessageProc( CMessage *const ptMsg );
	virtual void MessageProc(CTpMsg *const ptMsg);
	
	virtual BOOL32 DaemonObjectInit(u32 wParam, u32 lParam);
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit(void);

	void OnDisconnect(CMessage *const ptMsg);
public:
	void InstClear();

private:
	/*Eqp 通用消息*/
	void OnEqpChangeSndAddr(CTpMsg *const ptMsg);

private:
	/* Vmp */
	BOOL32	VmpMsgFromUmsEqpHandle(CTpMsg *const ptMsg);
	BOOL32	VmpMsgFromMcuBrdHandle(CMessage* const ptMsg);

	void OnVmpReg(CMessage *const ptMsg);
	void OnVmpRegAck(CTpMsg *const ptMsg);
	void OnVmpRegNAck(CTpMsg *const ptMsg);

	void OnVmpStateNtfy(CMessage *const ptMsg);

	void OnVmpMixRetInfo(CMessage *const ptMsg);

	void OnVmpStartReq(CTpMsg *const ptMsg);
	void OnVmpStopReq(CTpMsg *const ptMsg);
	
	void OnStartStopChnReq(CTpMsg *const ptMsg);
	void OnAskFrameVmpToEqp(CMessage *const ptMsg);
	void OnAskFrameEqpToVmp(CTpMsg *const ptMsg);

	void SendMsgToUmsEqp( u16 wEvent, u8 * const pbyMsg, u16 wLen );
	void SendMsgToBrd( u16 wEvent, u8 * const pbyMsg, u16 wLen );

	void	OnVmpQtSetMediaKey(CTpMsg *const ptMsg);

private:
	/* Bas */
	BOOL32	BasMsgFromUmsEqpHandle(CTpMsg *const ptMsg);
	BOOL32	BasMsgFromMcuBrdHandle(CMessage* const ptMsg);
	
	void	OnBasReg(CMessage* const ptMsg);
	void	OnBasRegAck(CTpMsg *const ptMsg);
	void	OnBasRegNAck(CTpMsg *const ptMsg);

	void	OnBasStartReq(CTpMsg *const ptMsg);
	void	OnBasStopReq(CTpMsg *const ptMsg);

	void	OnBasStateNtfy(CMessage *const ptMsg);
	void	OnBasChnStateNtfy(CMessage *const ptMsg);
	
	void	OnBasRetInfo(CMessage *const ptMsg);

	void	OnAskFrameBasToEqp(CMessage *const ptMsg);
	void	OnAskFrameEqpToBas(CTpMsg *const ptMsg);

    void	OnBasQtSetMediaKey(CTpMsg *const ptMsg);
private:
	enum EmEqpHandler
	{
		em_hdu_handler,	//电视墙处理接口
		em_audmix_handler,//混音和语音激励板
		em_audbas_handler,//音频适配
		em_eqp_handler_end,
	};

private:
	static IServiceHandler*	m_apServiceHandler[em_eqp_handler_end];	//业务处理接口

public:
	void	SetBrdNode(u32 dwBrdNode) { m_dwBrdNode = dwBrdNode; }
	u32		GetBrdNode() { return m_dwBrdNode; }
	void	SetBrdIID(u32 dwIID) { m_dwBrdIID = dwIID; }
	u32		GetBrdIID() { return m_dwBrdIID; }

private:
	
	u32		m_dwBrdNode;
	u32		m_dwBrdIID;
};
typedef zTemplate<CTPMcuBrdSsn, EQP_ID_TOTAL_END> CTPMcuBrdSsnApp;

#endif