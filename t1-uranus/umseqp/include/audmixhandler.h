#ifndef __audmixer_handler_h_
#define __audmixer_handler_h_

#include "servicehandler.h"
#include "umsinnertype.h"

//apu2 语音激励 混音
class CAudMixHandler : public IServiceHandler
{
public:
	CAudMixHandler();
	~CAudMixHandler();

public:
	virtual BOOL32		MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	virtual BOOL32		MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

private:
	//断链
	void				EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//注册
	void				EventReg(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegAck(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegNack(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//混音器的状态通知
	void				EventMixerStatNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
// 	//混音组的状态通知
// 	void				EventMixGrpStatNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//开启混音
	void				EventStartMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStartMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStartMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//停止混音
	void				EventStopMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//开启语音激励
	void				EventStartVac(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//停止语音激励
	void				EventStopVac(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//加入成员
	void				EventAddMixMember(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventAddMixMemberAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventAddMixMemberNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	//删除成员
	void				EventDelMixMember(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventDelMixMemberAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventDelMixMemberNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

//强制成员混音
 	void				EventForceMemberMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventForceMemberMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventForceMemberMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
//取消强制成员混音
 	void				EventCancelForceMemberMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventCancelForceMemberMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventCancelForceMemberMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//设置混音深度
	void				EventSetMixDepth(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetMixDepthAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetMixDepthNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//是否发送码流  即：是否开启混音
	void				EventSendAudNtfy(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//设置语音激励保护时间
	void				EventSetVacKeepTime(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//激励结果通知
	void				EventVacResultNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);


	void				EventSyncChnlCmd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//更新码流秘钥 量子
	void				EventSetMediaKeyNtfy(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

};

#endif