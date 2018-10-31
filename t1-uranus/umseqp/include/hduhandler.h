#ifndef __hdu_handler_h_
#define __hdu_handler_h_

#include "servicehandler.h"
#include "tphdu2.h"
#include "umsinnertype.h"

//电视墙消息处理接口
class CHduHandler : public IServiceHandler
{
public:
	CHduHandler();
	~CHduHandler();

public:
public:
	virtual BOOL32		MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	virtual BOOL32		MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

private:
	//
	void				EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	//注册
	void				EventReg(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegAck(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegNack(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//播放
	void				EventPlayReq(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventPlayAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventPlayNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//停止播放
	void				EventStopPlayReq(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopPlayAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopPlayNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	
	//更新通道状态
	void				EventUpdateChanStatus(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventReqIFrame(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//升级板子
	void				EventUpdateBrd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventUpdateNotify(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	//修改通道参数
	void				EventNotifyChan(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//
	void				EventDelBrd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventDelChan(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//HDU 更新状态
	void				EventUpdateStatus(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetVol(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	// 切换通道画面模式（1画面或者4画面）
	void                EventChangeHduChanMode(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventChangeHduChanModeAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventChangeHduChanModeNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	void                EventMediaKeyNty(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
private:
	//层
	u8					Layer(CTPMcuBrdSsn* pInst);
	//槽
	u8					Slot(CTPMcuBrdSsn* pInst);
};


#endif