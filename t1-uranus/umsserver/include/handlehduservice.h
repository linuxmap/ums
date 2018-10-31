#ifndef _handlehduservice_h__
#define _handlehduservice_h__

#include "tphandle.h"
#include "tpstruct.h"
#include "umsinnerstruct.h"
#include "umshdu.h"


//处理电视墙相关信息
class CUmsHduHandleService : public CTpHandler
{
public:
	CUmsHduHandleService(CTpObject* pcObjec);
	~CUmsHduHandleService();
	
public:
	virtual BOOL32	Handler(CTpMsg *const ptMsg);
	void			ShowHdu();
	void			ShowHduStyle();

	//获取电视墙的使用信息
	void			GetHduUesInfo(TTPBrdUsedInfo& tUseInfo);

private:
	//修改HDU
	void			EventHduBrdModify(u8* pData, u16 wDataSize);
	//添加HDU
	void			EventHduBrdAdd(u8* pData, u16 wDataSize);
	//升级HDU
	void			EventHduUpdate(u8* pData, u16 wDataSize);
	//升级结果
	void			EventHduUpdateNty(u8* pData, u16 wDataSize);
	//重启
	void			EventHduReboot(u8* pData, u16 wDataSize);
	//修改通道
	void			EventHduChanModify(u8* pData, u16 wDataSize);
	//删除通道配置
	void			EventHduDelChan(u8* pData, u16 wDataSize);
	//删除HDU
	void			EventHduDel(u8* pData, u16 wDataSize);
	//添加电视墙风格
	void			EventHduStyleAdd(u8* pData, u16 wDataSize);
	//删除电视墙风格
	void			EventHduStyleDel(u8* pData, u16 wDataSize);
	//更新电视墙风格
	void			EventHduStyleUpdate(u8* pData, u16 wDataSize);
	//用户登录
	void			EventHduUserLogin(u8* pData, u16 wDataSize);
	
	//请求播放
	void			EventHduPlayReq(u8* pData, u16 wDataSize);
	void			EventHduPlayAckFromCall(u8* pData, u16 wDataSize);
	void			EventHduDelMonitorFromCall(u8* pData, u16 wDataSize);
	void			EventHduPlayAckFromEqp(u8* pData, u16 wDataSize);
	void			EventHduPlayNackFromEqp(u8* pData, u16 wDataSize);
	//停止播放
	void			EventHduStopPlay(u8* pData, u16 wDataSize);
	void			EventHduAllStopPlay(u8* pData, u16 wDataSize);
	void			EventHduStopAckFromEqp(u8* pData, u16 wDataSize);
	void			EventHduStopNackFromEqp(u8* pData, u16 wDataSize);
	
	void			EventBrdRegRes(u8* pData, u16 wDataSize);   // hdu板卡注册
	void			EventServiceRegRes(u8* pData, u16 wDataSize); // 电视墙通道注册	
	void			EventUpdateChanStatus(u8* pData, u16 wDataSize);  // 电视墙通道状态更新
	void			EventUpdateStatus(u8* pData, u16 wDataSize);  // 只通知，server未处理
	
	// hdu请求关键帧
	void			EventReqIFrame(u8* pData, u16 wDataSize);
	
	void			EventHungUpHdu(u8* pData, u16 wDataSize); // 挂断会场处理
	void			EventHungUpConfHdu(u8* pData, u16 wDataSize); // 结会处理
	
	// 修改音量
	void			EventSetVolInfo(u8* pData, u16 wDataSize);
	void			EventSetVolRes(u8* pData, u16 wDataSize);
	
	// 修改hdu通道模式（vmp模式和普通模式）
	void            EventChangeChanModeReq(u8* pData, u16 wDataSize);
	void            EventChangeChanModeRsp(u8* pData, u16 wDataSize);

	////////////////////////////////////////
	//// 来自终端操作电视墙相关
	
	// 请求电视墙某个通道
	void			EventFromCnsHduPlayReq(u8* pData, u16 wDataSize);
	
	// 停止播放某个通道
	void			EventFromCnsHduStopPlay(u8* pData, u16 wDataSize);

	// 停止播放所有通道
	void			EventFromCnsHduAllStopPlay(u8* pData, u16 wDataSize);

	// 修改音量
	void			EventFromCnsSetVolInfo(u8* pData, u16 wDataSize);

	// 修改通道模式
	void            EventFromCnsChangeChanModeReq(u8* pData, u16 wDataSize);
	
	// 更新电视墙信息给CNS
	void			SendToCnsHduPlanInfo(u16 wConfID = 0, u16 wEpID = 0);

	void			EventMediaKeyNty(u8* pData, u16 wDataSize);
private:
	//获取HDU 信息
	void			LoadHduInfo();
	BOOL32			IsToolUser(const TLogUser& ptUser);

private:
	u16				GetHduIndex(u8 byLayer, u8 bySlot);
	void			InitHduToCall(THduPlayUnit* ptInfo, u8 bySubChanID, BOOL32 bChangeMode = FALSE);
	void            UptateHduToCall(THduPlayUnit* ptInfo, u8 bySubChanID);
	void			StopHduToCall(THduPlayUnit* ptInfo, u8 bySubChanID);
	void			StopHduPlay(THduPlayUnit* ptInfo, u8 bySubChanID);
	void			SaveHduBrdInfo();
	void			SaveHduBrdInfo(u16 wIndex);
	void			SaveHduPlanInfo();
	void			SendHduPlanInfo(BOOL32 bUmcReq = TRUE,  BOOL32 bCnsReq = TRUE);
	u16				GetIndex(u8 byLayer, u8 bySlot){ return byLayer *  HDU_MAX_SLOT + bySlot; }

	// 获取所有的电视墙消息
	void            GetALLHduPalnInfo(THduPlanData& tData);

	// 请求播放电视墙参数校验
	void            HduPlayReqStateFromUmcCns(TTPHduPlayReq& tReq, EmTpHduPlayNackReason& emReason);

	// 请求停止播放电视墙某个通道参数校验
	void            HduStopReqStateFromUmcCns(TTPHduPlayReq& tReq, BOOL32& bRes);
	
	// 请求停止播放电视墙所有通道参数校验
	void            HduStopAllReqStateFromUmcCns(u8* pData, u16 wDataSize);

	// 电视墙设置音量消息参数校验
	void            HduSetVolReqStateFromUmcCns( THduPlayUnit* ptInfo, EmTpHduSetVolRes& emRes);

	// 修改电视墙通道状态参数校验
	void            HduChangeChanModeStateFromUmcCns(THduChanModeSetInfo& tInfo, EmTpHduChangeChanModeRes& emRes);


private:
	CHduEx		m_acHdu[HDU_MAX_NUM];
	CHduPlan	m_cHduPlanEx;
};

#endif