#ifndef _h_handlecallservice_h__
#define _h_handlecallservice_h__

#include "tpsys.h"
#include "tphandle.h"
#include "tpstruct.h"
#include "umsinnerstruct.h"

//CallMgr : 
typedef struct tagTCallMgr
{
	TLogUser m_tUmcUser;
	BOOL32	 m_bIsRunning;
	s8       m_achConfName[TP_MAX_ALIAS_LEN+1];	//会议名称
	s8       m_achConfE164[TP_MAX_ALIAS_LEN+1];	//会议e164
	time_t   m_tEndConfTime;                     //结束会议时间
	BOOL32	 m_bCallByTimer;	//是否是预约呼叫

	tagTCallMgr()
	{
		Clear();
	}

	void Clear()
	{
		m_bIsRunning = FALSE;
		m_achConfName[0] = '\0';
		m_achConfE164[0] = '\0';
		m_tEndConfTime = 0;
		m_tUmcUser.Clear();
		m_bCallByTimer = FALSE;
	}
    
	void HungUp()
	{
		Clear();
		time_t CurTime;
		time(&CurTime);
		m_tEndConfTime = CurTime;    //挂断会议时
		m_bCallByTimer = FALSE;
	}

}TCallMgr, *PTCallMgr;

class CUmsCallHandleService : public CTpHandler
{
public:
	CUmsCallHandleService(CTpObject* pcObjec);
	~CUmsCallHandleService();
	
public:
	virtual BOOL32 Handler( CTpMsg *const ptMsg );

	u16			GetIdleConf(TTPConfTemplate* tTemplate, TLogUser* ptUmcUsr = NULL);
	TCallMgr*	GetCallMgr(u16 wIndex);
	u16			GetConf(TTPConfTemplate* tTemplate);
	u16			GetConfByDstAddr(TTpCallAddr* pCallDstAddr);
	BOOL32		IsConfIdle();

	void        ShowAllConf();

public:
	//获取正在开会的数量
	u32		GetRunningConf();
	void UpdateRunningConfCount();
protected:
	//呼叫到来
	void EventCallIncoming(u8* pDataBuf, u16 wDataSize);
	void EventCallCreateMeeting(u8* pDataBuf, u16 wDataSize);
	void EventStartConfTemplateFailed(u8* pDataBuf, u16 wDataSize);
	void EventUpdateConfTurnList(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventHungUpConfResult(CTpMsg *const ptMsg);
	void EventDelConfNotify(CTpMsg *const ptMsg);
	void EventAuxMixInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventCallEpResult(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 邀请会场的回应
	void EventApplySpeakerResult(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 指定发言人的回应
	void EventStartDualInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 开启双流的回应
	void EventChairConfInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventUpdateConfCnsListNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventFeccVidListNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventAddConfListNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventDualEpNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventSpeakerChangeNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventMuteEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 哑音回应
	void EventQuietEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 静音回应

	void EventAllEpQuietMuteStatusNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);//通知界面全局静音哑音状态
	void EventAudMixStatNotify( u16 wEvent, u8* pData, u16 wDataSize );
	void EventHungUpConfReasonToUI(u16 wEvent, u8* pData, u16 wDataSize);
	void EventStartConfRet(u8* pDataBuf, u16 wDataSize);
	void EventCommReasonUIInd(u16 wEvent, u8* pData, u16 wDataSize);

	// add by gaoyong
	void EventDropEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 挂断一个会场的回应
	void EventCallExistEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 呼叫一个会场的回应
	void EventStopDualInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 停止双流的回应
	void EventSetTurnListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); //
	void EventOprDiscussEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 
	void EventUptateDiscussInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 讨论操作的回应
	void EventStartPollInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 开轮询的回应
	void EventSuspendPollInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 开轮询的回应
	void EventStopPollInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 关轮询的回应
	void EventViewObjInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 选看会场的回应
	void EventUnViewObjInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 取消选看的回应

	void EventAudMixVacInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);

	void EventPollStatNtfy( u16 wEvent, u8* pDataBuf, u16 wDataSize );

	void EventChairStreenInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);

	void EventSelViewInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventSelViewNtfy(u16 wEvent, u8* pDataBuf, u16 wDataSize);

	void EventRervesBrdVmpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventSetBrdVmpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventBrdVmpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventBrdVmpNtfy(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventSaveBrdVmpCfgInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
    void EventUmsJoinConfReq(u16 wEvent,u8* pData, u16 wDataSize);
	void EventUmsJoinConfNtfy(u16 wEvent, u8* pData,u16 wDataSize);

	//从UI过来的消息
	void EventLogin(CTpMsg *const ptMsg);
	void EventStartConfReq(CTpMsg *const ptMsg);
	void EventStartMeetingReq(CTpMsg *const ptMsg);
	void EventHungUpConf(CTpMsg *const ptMsg);
	void EventCallEp(CTpMsg *const ptMsg);   // 邀请一个会场
	void EventCallExistEp(CTpMsg *const ptMsg);  // 呼叫一个会场
	void EventDropEp(CTpMsg *const ptMsg);   // 挂断一个会场
/*	void EventDeleteEp(CTpMsg *const ptMsg);*/
	void EventChangeSpeaker(CTpMsg* const ptMsg);  // 指定发言人
	void EventMuteEp(CTpMsg* const ptMsg);   // 哑音
	void EventQuietEp(CTpMsg* const ptMsg); // 静音
	void EventSetTurnList(CTpMsg* const ptMsg);  // umc更新轮询列表
	void EventOprDiscussEpCmd(CTpMsg* const ptMsg);  // 
	void EventUptateDiscussCmd(CTpMsg* const ptMsg); // 
	void EventStartDual(CTpMsg* const ptMsg);  // 开启双流
	void EventStopDual(CTpMsg* const ptMsg);  // 关闭双流

	void EventAudMixVacCmd(CTpMsg* const ptMsg);
	void EventFeccCameraReq(CTpMsg *const ptMsg);
	void EventFeccPrePosReq(CTpMsg *const ptMsg);
	void EventFeccSelVidReq(CTpMsg *const ptMsg);

	// add by gaoyong
	void EventStartPoll(CTpMsg* const ptMsg);   // 开轮询
	void EventStopPoll(CTpMsg* const ptMsg);   // 关轮询
	void EventSupendPoll(CTpMsg* const ptMsg);

	void EventViewObj(CTpMsg* const ptMsg);  // 选看会场
	void EventUnViewObj(CTpMsg* const ptMsg);  // 取消选看
	
	void EventSelViewReq(CTpMsg* const ptMsg);  //自由选看
	void EventRervesBrdVmpReq(CTpMsg* const ptMsg);  //占用合成
	void EventSetBrdVmpReq(CTpMsg* const ptMsg);  //配置合成
	void EventBrdVmpReq(CTpMsg* const ptMsg);  //开启广播
	void EventSaveBrdVmpCfg( CTpMsg *const ptMsg );//保存合成配置
	void EventUmsJoinConfAck( CTpMsg *const ptMsg);


	//点名
	void EventUptateRollCallCmd(CTpMsg* const ptMsg);
	void EventUptateRollCallInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 操作的回应
	void EventUptateRollCallNextEpCmd(CTpMsg* const ptMsg);
	void EventUptateRollCallNextEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 操作的回应
    void EventUptateRollCallListCmd(CTpMsg* const ptMsg);
	void EventUptateRollCallListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 操作的回应
    void EventRollCallPresentStateCmd(CTpMsg* const ptMsg);
    void EventRollCallPresentStateNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
    void EventRollCallInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);


	// 会议混音
	void EventAudMixModeCmd(CTpMsg* const ptMsg);
	void EventAudMixModeInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventAudMixListCmd(CTpMsg* const ptMsg);
	void EventAudMixListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
    void EventAudMixNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);


	//getconfvidaud
    void EventGetConfBrdVidAudCmd(CTpMsg* const ptMsg);
	void EventGetConfBrdVidAudInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); 
	void EventReleaseGetConfBrdVidAudCmd(CTpMsg* const ptMsg);
	void EventReleaseGetConfBrdVidAudInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventGetConfBrdVidAudaskKey(CTpMsg* const ptMsg);

	// 不入会请求画面合成evtp_GetConfVmpVidAskKey_cmd
	void EventGetConfVmpVidCmd(CTpMsg* const ptMsg);
	void EventGetConfVmpVidInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); 
	void EventReleaseConfVmpVidCmd(CTpMsg* const ptMsg);
	void EventReleaseConfVmpVidInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventGetConfVmpVidAskKey(CTpMsg* const ptMsg);
	void EventConfVmpVidNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);

	void EventGetEpScreenInfoCmd(CTpMsg* const ptMsg);
	void EventGetEpScreenInfoInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); 
	void EventReleaseEpScreenInfoCmd(CTpMsg* const ptMsg);
	void EventReleaseEpScreenInfoInd(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventGetConfEpScreenAskKey(CTpMsg* const ptMsg);
	
//	临时会议处理
	void GetValue(TConfTemplateLocal&tRes,const TTPConfMeet&tRhs);


	//更新临时会议名
	void EventUpdateTempConfName(CTpMsg* const ptMsg);

protected:

	TCallMgr m_atCall[TP_UMS_MAX_CONFNUM+1];
	
private:
};




#endif // _h_handlecallservice_h__