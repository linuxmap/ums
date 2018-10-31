#include "tpmsg.h"
#include "umsobject.h"
#include "xmpuinnerstruct.h"
#include "innereventxmpuvmp.h"
#include "innereventxmpuaudbas.h"
#include "innereventxmpumix.h"
#include "innereventxmpubas.h"
#include "umsapi.h"
#include "umsxmltype.h"
#include "xmpudataconvert.h"
#include "mediabasapi.h"
#include "mediaclientapi.h"
#include "mediamixapi.h"
#include "mediavmpapi.h"
#include "mediaerrcode.h"
#include "mediaclientstruct.h"
#include "mediadefine.h"
#include "rabbitmqwrapper.h"
#include <map>

std::map<u32,u32> g_mapVmp; 
std::map<u32,u32> g_mapBas; 
std::map<u32,u32> g_mapMix; 

extern BOOL32	g_bXmpuInit;
extern BOOL32    g_bMediaInit;

u32 GetVmpEqpID(u32 dwHandle)
{
	u32 dwEqpID = 0;
	std::map<u32, u32>::iterator it = g_mapVmp.find(dwHandle);
	if (it != g_mapVmp.end())
	{
		dwEqpID = it->second;
	}
	return dwEqpID;
}

u32 GetBasEqpID(u32 dwHandle)
{
	u32 dwEqpID = 0;
	std::map<u32, u32>::iterator it = g_mapBas.find(dwHandle);
	if (it != g_mapBas.end())
	{
		dwEqpID = it->second;
	}
	return dwEqpID;
}

u32 GetMixEqpID(u32 dwHandle)
{
	u32 dwEqpID = 0;
	std::map<u32, u32>::iterator it = g_mapMix.find(dwHandle);
	if (it != g_mapMix.end())
	{
		dwEqpID = it->second;
	}
	return dwEqpID;
}

static void NotifyToXmpu(u16 wEvent, void* pBuf, u16 wSize)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if (NULL != pBuf)
	{
		cMsg.SetBody(pBuf, wSize);
	}
	cMsg.Post(UMS_XMPU_APP_INST);
}

void SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen )
{
	if ( wConfID == TP_INVALID_INDEX )
	{
		return ;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post( MAKEIID( AID_UMSCONFMGR, wConfID) );
	return ;
}

// MediaClient 回调
// typedef void (MEDIACLTCB* CBMediaCltRsp)(IN EmCBMediaCltId emCBFunId, IN u16 wErrCode, IN u8 *pbyBuf, IN u16 wBufLen);
// 
void MEDIACLTCB UmsCBMediaClient(IN MediaAPI::CMediaClt::EmCBMediaCltId emCBFunId, IN u16 wErrCode, IN u8 *pbyBuf, IN u16 wBufLen)
{
	u32 dwConfID = 0;
	TP_SAFE_CAST(dwConfID, pbyBuf);
	dwConfID = ntohl(dwConfID);
	MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaClient emCBFunId:%d dwConfID:%d, wErrcode:%d, wBufLen:%d !\n",
				emCBFunId, dwConfID, wErrCode, wBufLen));

// 	switch(wErrCode)
// 	{
// 	case ERR_CODE_NORMAL:
// 		{
// 			break;
// 		}
// 	default:
// 		{
// 			MdlLowHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaClient wErrcode faild! wErrCode:%d !\n", wErrCode));
// 			return;
// 		}
// 	}

// 	pbyBuf  = hUserData + abyLogicId[128] + bySynIdNum(N) + dwSynId* N
// 		byBufLen = sizeof(APPHANDLE) + u8*128 + u8 + u32*4
// 		abyLogicId(逻辑ID)，是为平台这边为了之后媒体和码流转发放在一起而服务的
// 		最后2个字段段给网呈用，同步ID数量+同步ID值，一个会议最多4组同步

	switch(emCBFunId)
	{
	case MediaAPI::CMediaClt::emTPConfReserveRsp:
		{
			u8 bySynNum = 0;
			TP_SAFE_CAST(bySynNum, pbyBuf+sizeof(u32));
			u32 adwSynID[4] = {0};
			memcpy(adwSynID, pbyBuf+sizeof(u32)+sizeof(u8), sizeof(u32)*bySynNum);

			for (u16 wIndex = 0; wIndex < bySynNum; ++wIndex)
			{
				adwSynID[wIndex] = ntohl(adwSynID[wIndex]);
			}

			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaClient emTPConfReserveRsp  dwMediaHandle:%d, wErrcode:%d adwSynID[wIndex]:%d,synId:(%d|%d|%d|%d)!\n", 
						 dwConfID, wErrCode, bySynNum,adwSynID[0],adwSynID[1], adwSynID[2], adwSynID[3]));

			TXmpuInitMettingRsp tRsp;
			tRsp.m_dwConfID = dwConfID;
			tRsp.m_bySynNum = bySynNum;
			memcpy(tRsp.m_adwSynID, adwSynID, sizeof(adwSynID));
			tRsp.m_emRes = (wErrCode==ERR_CODE_NORMAL?InitMettingRsp_Success:InitMettingRsp_FAILD);
			NotifyToXmpu(evXmpu_InitMetting_Rsp, &tRsp, sizeof(tRsp));

			BOOL32 bSuccess = (wErrCode==ERR_CODE_NORMAL?TRUE:FALSE);
			SendMsgToCall(dwConfID, evXmpu_InitMettingFaild_Nty, &bSuccess, sizeof(bSuccess));
			break;
		}
		
	default:
		{
			MdlLowHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaClient wErrcode faild! wErrCode:%d !\n", wErrCode));
			break;
		}
	}
}

// MediaBase 回调
// audbas: ERR_ABASINIT  vidbas:ERR_INITMULPIC   success: ERR_CODE_NORMAL(0)
void MEDIACLTCB UmsCBMediaBase(IN MediaAPI::CBasMgr::EmCBBasId emCBFunId, u16 wErrCode, u8 *pbyBuf, u16 wBufLen)
{
	HMEDIARES dwMediaHandle = 0;
	TP_SAFE_CAST(dwMediaHandle, pbyBuf);
	dwMediaHandle = ntohl(dwMediaHandle);
	u32 dwConfID = MediaAPI::CVmpMgr::GetUserData(dwMediaHandle);

	MdlLowDtl(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emCBFunId:%d, dwConfID:%d, dwMediaHandle:%d, , wErrcode:%d !\n", 
		emCBFunId, dwConfID,  dwMediaHandle,  wErrCode));

	switch(emCBFunId)
	{
	case MediaAPI::CBasMgr::emBasStartRsp:
		{

			TXmpuStartBasCommonRsp tRes;
			u8 abyBuf[TP_CONF_MAX_MINOR_VIDEO_RES_NUM] = {0};
			u8 byEncNum = 0;
			TP_SAFE_CAST(byEncNum, pbyBuf + sizeof(u32));
			memcpy(abyBuf, pbyBuf+sizeof(u8)+sizeof(u32), sizeof(u8)*byEncNum);
			memcpy(tRes.m_abyID, pbyBuf+sizeof(u8)+sizeof(u32), sizeof(u8)*byEncNum);
			tRes.m_byNum = byEncNum;
			tRes.m_dwHandle = dwMediaHandle;
			tRes.m_wErrCode = wErrCode;
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emBasStartRsp dwMediaHandle:%d, byEncNum:%d, ID:(%d|%d|%d|)!\n", 
				dwMediaHandle,byEncNum, abyBuf[0], abyBuf[1], abyBuf[2] ));

			NotifyToXmpu(evXmpu_StartBas_Rsp,&tRes,sizeof(tRes));
			break;
		}
	case MediaAPI::CBasMgr::emBasStopRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emBasStopRsp dwMediaHandle:%d ,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));
			break;
		}
	case MediaAPI::CBasMgr::emAddAdaptChnlRsp:
		{
			u8 byChn = 0;
			TP_SAFE_CAST(byChn, pbyBuf + sizeof(u32));
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emAddAdaptChnlRsp dwMediaHandle:%d,  ChnID:%d,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  byChn, wErrCode, emCBFunId));
			break;
		}
	case MediaAPI::CBasMgr::emSetEncChnParam:
		{

			TXmpuStartBasCommonRsp tRes;
			u8 abySucChn[TP_CONF_MAX_MINOR_VIDEO_RES_NUM] = {0};
			u8 bySucNum = 0;
			TP_SAFE_CAST(bySucNum, pbyBuf + sizeof(u32));
			memcpy(abySucChn, pbyBuf+sizeof(u8)+sizeof(u32), sizeof(u8)*bySucNum);
			memcpy(tRes.m_abyID, pbyBuf+sizeof(u8)+sizeof(u32), sizeof(u8)*bySucNum);
			tRes.m_byNum = bySucNum;
			tRes.m_dwHandle = dwMediaHandle;
			tRes.m_wErrCode = wErrCode;
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emSetEncChnParam dwMediaHandle:%d,  SuccNum:%d, SuccID:(%d|%d|%d|)!\n", 
				dwMediaHandle, 
				bySucNum, abySucChn[0], abySucChn[1], abySucChn[2] ));
			NotifyToXmpu(evXmpu_SetBasCommonEncParam_Rsp,&tRes,sizeof(tRes));
			break;
		}
	case MediaAPI::CBasMgr::emBasReqDecIFrame:
		{
			MdlLowDtl(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emBasReqDecIFrame dwMediaHandle:%d, dwEqpId:%d,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));

			NotifyToXmpu(evXmpu_AskBasKey_Req, &dwMediaHandle, sizeof(dwMediaHandle));
			break;
		}
	case MediaAPI::CBasMgr::emBasResDisconnect:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase emBasResDisconnect dwMediaHandle:%d, wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));
			
			NotifyToXmpu(evXmpu_BasCommonDisConnect_Nty, &dwMediaHandle, sizeof(dwMediaHandle));

			break;
		}
	default:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaBase default dwMediaHandle:%d, ,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));
			break;
		}
	}
}

// MediaMix 回调
// start: ERR_MIXINIT  success: ERR_CODE_NORMAL(0) 
void MEDIACLTCB UmsCBMediaMix(IN MediaAPI::CMixMgr::EmCBMixId emCBFunId, u16 wErrCode, u8 *pbyBuf, u16 wBufLen)
{
	HMEDIARES dwMediaHandle = 0;
	TP_SAFE_CAST(dwMediaHandle, pbyBuf);
	dwMediaHandle = ntohl(dwMediaHandle);
	u32 dwConfID = MediaAPI::CMixMgr::GetUserData(dwMediaHandle);
	MdlLowDtl(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emCBFunId:%d, dwConfID:%d,  dwMediaHandle:%d, , wErrcode:%d !\n", 
		emCBFunId,dwConfID,  dwMediaHandle,  wErrCode));

	switch(emCBFunId)
	{
	case MediaAPI::CMixMgr::emMixStartRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixStartRsp dwMediaHandle:%d,  ,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle, wErrCode, emCBFunId));
			TXmpuStartMixRsp tRes;
			tRes.m_dwHandle = dwMediaHandle;
			tRes.m_emRes = (wErrCode==ERR_CODE_NORMAL?StartMixRsp_Success:StartMixRsp_FAILD);
			NotifyToXmpu(evXmpu_UmsStartMix_Rsp, &tRes, sizeof(tRes));
			break;
		}
	case MediaAPI::CMixMgr::emMixStopRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixStopRsp dwMediaHandle:%d ,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));
			break;
		}
	case MediaAPI::CMixMgr::emMixStartVacRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixStartVacRsp dwMediaHandle:%d, wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle, wErrCode, emCBFunId));
			break;
		}
	case MediaAPI::CMixMgr::emMixStopVacRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixStopVacRsp dwMediaHandle:%d,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));
			break;
		}
	case MediaAPI::CMixMgr::emMixRemoveMemberRsp:
		{
			u8 byNum = 0;
			TP_SAFE_CAST(byNum, pbyBuf+sizeof(u32));
			u8 byID = 0;
			TP_SAFE_CAST(byID, pbyBuf+sizeof(u32)+sizeof(u8));
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixRemoveMemberRsp dwMediaHandle:%d, wErrcode:%d ,FuncID:%d byNum:%d, byID:%d!\n", 
				dwMediaHandle,wErrCode, emCBFunId, byNum, byID));
			break;
		}
	case MediaAPI::CMixMgr::emMixActiveChnIdNtf:
		{
			u8 byChnID = 0; 
			TP_SAFE_CAST(byChnID, pbyBuf+sizeof(u32));
			TXmpuVacActiveNty tNty;
			tNty.m_byChnID = byChnID;

			MdlLowDtl(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixActiveChnIdNtf dwMediaHandle:%d,wErrcode:%d, FuncID:%d, byChnID:%d!\n", 
				dwMediaHandle,  wErrCode, emCBFunId, byChnID));

			u8 abyBuf[sizeof(TXmpuVacActiveNty)+sizeof(u32)] ={0};
			memcpy(abyBuf,&tNty,sizeof(TXmpuVacActiveNty));
			memcpy(abyBuf +sizeof(TXmpuVacActiveNty),&dwMediaHandle,sizeof(u32));
			NotifyToXmpu(evXmpu_VacActive_Ntf, abyBuf, sizeof(abyBuf));
			break;
		}
	case MediaAPI::CMixMgr::emMixAddMemberRsp:
		{
			u8 bySuccNum = 0;
			TP_SAFE_CAST(bySuccNum, pbyBuf+sizeof(u32));
			TXmpuAddMixMemRsp tRes;
			tRes.m_dwHandle = dwMediaHandle;
			tRes.m_emRes = (wErrCode==ERR_CODE_NORMAL?AddMixMemRsp_Success:AddMixMemRsp_FAILD);
			tRes.m_byNum = bySuccNum;
			memcpy(tRes.m_abyChnID, pbyBuf+sizeof(u32)+sizeof(u8), sizeof(u8)*bySuccNum);

			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixAddMemberRsp dwMediaHandle:%d, wErrcode:%d, FuncID:%d, bySuccessNum:%d, byChnID(%d|%d|%d|%d|%d)!\n", 
				dwMediaHandle,  wErrCode, emCBFunId, bySuccNum, 
				tRes.m_abyChnID[0], tRes.m_abyChnID[1], tRes.m_abyChnID[2], tRes.m_abyChnID[3],tRes.m_abyChnID[4]));

			u8 abyBuf[sizeof(TXmpuAddMixMemRsp)+sizeof(u32)] ={0};
			memcpy(abyBuf,&tRes,sizeof(TXmpuAddMixMemRsp));
			memcpy(abyBuf +sizeof(TXmpuAddMixMemRsp),&dwMediaHandle,sizeof(u32));
			NotifyToXmpu(evUms_XmpuAddMixMember_Rsp, abyBuf, sizeof(abyBuf));
			break;
		}
	case MediaAPI::CMixMgr::emMixResDisconnect:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixResDisconnect dwMediaHandle:%d, wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));

			NotifyToXmpu(evXmpu_MixDisConnect_Nty, &dwMediaHandle, sizeof(dwMediaHandle));
			break;
		}
	// 语音检测不处理，多画面合成绿边框功能暂不做！
	case MediaAPI::CMixMgr::emMixVoiceDetection:
		{
			break;
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaMix emMixVoiceDetection dwMediaHandle:%d, wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle, wErrCode, emCBFunId));
			TVoiceDetectionNty tNty;
			TP_SAFE_CAST(tNty.m_byNum, pbyBuf+sizeof(u32));
			memcpy(tNty.m_abyChanId, pbyBuf+sizeof(u32)+sizeof(u8), sizeof(u8)*tNty.m_byNum);

			u8 abyBuf[sizeof(TVoiceDetectionNty)+sizeof(u32)] ={0};
			memcpy(abyBuf,&tNty,sizeof(TVoiceDetectionNty));
			memcpy(abyBuf +sizeof(TVoiceDetectionNty),&dwMediaHandle,sizeof(u32));
			NotifyToXmpu(evXmpu_MixVoiceDetection_Ntf, abyBuf, sizeof(abyBuf));
			break;
		}
	default:
		{
			break;
		}
	}
}

// MediaVmp 回调
// start: ERR_SETENCRYPTKEY  success: ERR_CODE_NORMAL(0)
void MEDIACLTCB UmsCBMediaVmp(IN MediaAPI::CVmpMgr::EmCBVmpMgrId emCBFunId, IN u16 wErrCode, 
		IN u8 *pbyBuf, IN u16 wBufLen)
{
	HMEDIARES dwMediaHandle = 0;
	TP_SAFE_CAST(dwMediaHandle, pbyBuf);
	dwMediaHandle = ntohl(dwMediaHandle);
	u32 dwConfID = MediaAPI::CVmpMgr::GetUserData(dwMediaHandle);
	MdlLowDtl(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaVmp emCBFunId:%d, dwConfID:%d, dwMediaHandle:%d,  wErrcode:%d !\n", 
		emCBFunId, dwConfID, dwMediaHandle,  wErrCode));

	switch(emCBFunId)
	{
	case MediaAPI::CVmpMgr::emVmpStartVmpRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaVmp emVmpStartVmpRsp dwMediaHandle:%d,  wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));

			TXmpuStartVmpRsp tRes;
			tRes.m_dwHandle = dwMediaHandle;
			tRes.m_emRes = (wErrCode==ERR_CODE_NORMAL?StartVmpRsp_Success:StartVmpRsp_FAILD);
			NotifyToXmpu(evXmpu_StartVmp_Rsp, &tRes, sizeof(tRes));
			break;
		}
	case MediaAPI::CVmpMgr::emVmpStopRsp:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaVmp emVmpStopRsp dwMediaHandle:%d,  wErrcode:%d ,FuncID:%d !\n", dwMediaHandle,
				 wErrCode, emCBFunId));
			break;
		}
	case MediaAPI::CVmpMgr::emVmpReqDecIFrame:
		{
			u8 byChnID = 0;
			TP_SAFE_CAST(byChnID, pbyBuf+sizeof(u32));

			MdlLowDtl(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaVmp emVmpReqDecIFrame dwMediaHandle:%d,  ChnID:%d,wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,   byChnID, wErrCode, emCBFunId));

			TTPVmpAskFrame tAsk;
			tAsk.m_byChanIndx = byChnID;

			u8 abyBuf[sizeof(TTPVmpAskFrame)+sizeof(u32)] ={0};
			memcpy(abyBuf,&tAsk,sizeof(TTPVmpAskFrame));
			memcpy(abyBuf +sizeof(TTPVmpAskFrame),&dwMediaHandle,sizeof(u32));
			NotifyToXmpu(evXmpu_AskVmpKey_Req, abyBuf, sizeof(abyBuf));
			break;
		}
	case MediaAPI::CVmpMgr::emVmpResDisconnect:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaVmp emVmpResDisconnect dwMediaHandle:%d, wErrcode:%d ,FuncID:%d !\n", 
				dwMediaHandle,  wErrCode, emCBFunId));

			 NotifyToXmpu(evXmpu_VmpDisConnect_Nty, &dwMediaHandle, sizeof(dwMediaHandle));
			break;
		}
	default:
		{
			MdlHint(Ums_Mdl_Xmpu, ("<<<< UmsCBMediaVmp default dwMediaHandle:%d,  wErrcode:%d ,FuncID:%d !\n", dwMediaHandle,
				 wErrCode, emCBFunId));
			break;
		}
	}
}

// 172.16.236.16 22223
// zk ip 和port 可以读取配置文件
BOOL32 XmpuInitMediaClient(s8* pchMqUrl, s8* pchMoid)
{

	MdlHint(Ums_Mdl_Xmpu, ("XmpuInitMediaClient begin..... MqUrl:%s, UmsMoid:%s\n", pchMqUrl, pchMoid));

	if (rabbitmqwrap::RT_OK != rabbitmqwrap::RabbitmqClntInitByUrl(pchMqUrl))
	{
		MdlError(Ums_Mdl_Xmpu, ("XmpuInitMediaClient RabbitmqClntInitByUrl error!\n"));
		return FALSE;
	}

	MediaAPI::TMediaInitParam tInitParam;
	tInitParam.SetHBNum(3);
	tInitParam.SetHBTimeOut(3);
	tInitParam.SetMcuMoId(pchMoid);
	if (!MediaAPI::CMediaClt::Init(tInitParam))
	{
		MdlError(Ums_Mdl_Xmpu, ("XmpuInitMediaClient CMediaClt::Init error!\n"));
		return FALSE;
	}

 	if (!MediaAPI::CMediaClt::SetCBFun(UmsCBMediaClient))
	{
		MdlError(Ums_Mdl_Xmpu, ("XmpuInitMediaClient CMediaClt::SetCBFun error!\n"));
		return FALSE;
	}
	if (!MediaAPI::CBasMgr::SetCBFun(UmsCBMediaBase))
	{
		MdlError(Ums_Mdl_Xmpu, ("XmpuInitMediaClient CBasMgr::SetCBFun error!\n"));
		return FALSE;
	}
	if (!MediaAPI::CMixMgr::SetCBFun(UmsCBMediaMix))
	{
		MdlError(Ums_Mdl_Xmpu, ("XmpuInitMediaClient CMixMgr::SetCBFun error!\n"));
		return FALSE;
	}
	if (!MediaAPI::CVmpMgr::SetCBFun(UmsCBMediaVmp))
	{
		MdlError(Ums_Mdl_Xmpu, ("XmpuInitMediaClient CVmpMgr::SetCBFun error!\n"));
		return FALSE;
	}

	return TRUE;
}

void GetMediaSource(s8* pszMqUrl, s8* pszMasterId, TMediaEqpMgr& tInfo)
{
	if (!g_bMediaInit)
	{
		return;
	}
// 	MediaAPI::CMediaClt::GetResBrdNum(byH264Num, byH265Num);
	MdlLowDtl(Ums_Mdl_Xmpu, ("GetMediaSource MqUrl:%s, UmsMoid:%s\n", pszMqUrl, pszMasterId));
	MediaAPI::TIdleTPResCount tRes;
	MediaAPI::CMediaClt::QueryMasterResCnt(pszMqUrl, pszMasterId, tRes);

	tInfo.m_dw264VmpCnt = tRes.Get264VmpCnt();
	tInfo.m_dw265_264VmpCnt = tRes.Get265VmpCnt();
	tInfo.m_dw264BasCnt = tRes.Get264VBasCnt();
	tInfo.m_dw265_264BasCnt = tRes.Get265VBasCnt();
	tInfo.m_dwABasCnt = tRes.GetABasCnt();
	tInfo.m_dwMixer8Cnt  = tRes.GetMixer8Cnt();
	tInfo.m_dwMixer192Cnt = tRes.GetMixer192Cnt();
	tInfo.m_dw264Port = tRes.Get264PortCnt();
	tInfo.m_dw265Port = tRes.Get265PortCnt();
}

BOOL32 MediaInitMeeting(IN TXmpuMettingInfo tInfo)
{
	MdlHint(Ums_Mdl_Xmpu, ("MediaInitMeeting wConfID:%d, E164:%s, maxMtNum:%d, bNeedAud:%d, bNeedVid:%d, MqUrl:%s, UmsMoid:%s\n", 
		tInfo.m_wConfID, tInfo.m_achConfE164, tInfo.m_dwMaxMtNum, tInfo.m_bNeedAudBas, tInfo.m_bNeedVidBas,
		tInfo.m_abyMqUrl, tInfo.m_abyMoid));

	MdlHint(Ums_Mdl_Xmpu, ("MediaInitMeeting vidFormatMsg mFormat:%d,emRes:%d, wFrameRate:%d, wBitrate:%d,emQualityLvl:%d\n", 
		tInfo.m_tFormat.m_emFormat,  tInfo.m_tFormat.m_emRes,  tInfo.m_tFormat.m_wFrameRate, 
		tInfo.m_tFormat.m_wBitrate, tInfo.m_tFormat.m_emQualityLvl));

	MediaAPI::TMediaVidStreamCap tCap;
	MediaAPI::TMediaConferenceInfo tConfInfo;
	if (strlen(tInfo.m_achConfE164))
	{
		tConfInfo.SetConfE164(tInfo.m_achConfE164, strlen(tInfo.m_achConfE164));		
	}
	else
	{
		tConfInfo.SetConfE164(tInfo.m_achConfName, strlen(tInfo.m_achConfName));
	}
	tConfInfo.SetMixMtNum(tInfo.m_dwMaxMtNum);
	tConfInfo.SetMqUrl(tInfo.m_abyMqUrl);
	tConfInfo.SetMasterId(tInfo.m_abyMoid);
	tConfInfo.SetSynIdNum(XMPU_MAX_SYN_NUM); //一个会议中最多使用4组同步ID
	ConvertVidForamtFromUmsToXmpu(tInfo.m_tFormat, tCap);
	tConfInfo.SetMaxConfCap(tCap);
	if (tInfo.m_bNeedAudBas && !tInfo.m_bNeedVidBas)
	{
		tConfInfo.SetConfType(MediaAPI::emTpABasConf);// 3:(7audbas)    4:(7vid)    5:(vid + aud)   6
	}
	else if (!tInfo.m_bNeedAudBas && tInfo.m_bNeedVidBas)
	{
		tConfInfo.SetConfType(MediaAPI::emTpVBasConf);// 3:(7audbas)    4:(7vid)    5:(vid + aud)   6
	}
	else if (tInfo.m_bNeedAudBas && tInfo.m_bNeedVidBas)
	{
		tConfInfo.SetConfType(MediaAPI::emTpAVBasConf);// 3:(7audbas)    4:(7vid)    5:(vid + aud)   6
	}
	else
	{
		tConfInfo.SetConfType(MediaAPI::emTpNoReserveConf);// 3:(7audbas)    4:(7vid)    5:(vid + aud)   6
	}

	return MediaAPI::CMediaClt::InitMeeting(tInfo.m_wConfID, tConfInfo);
}

BOOL32 MediaReleaseMeeting( OUT HMEDIARES dwUserDate )
{
	return MediaAPI::CMediaClt::ReleaseMeeting(dwUserDate);
}

//////////////////////////////////////////////////
///////////////****MediaVmp接口调用****///////////
//////////////////////////////////////////////////
BOOL32 MediaStartVmp(OUT HMEDIARES& dwVmpHandle, IN APPHANDLE dwEqpID, IN TXmpuVmpParam tInfo)
{
	MediaAPI::TVmpEncParam atEncParam[TP_VMP_MAX_OUT_CHN_NUM];
	MediaAPI::TMediaVidStreamCap tStreamCap;
	MediaAPI::TStreamCap tCap;
	MediaAPI::TMediaEncryptParam tEncrtpt;
	u8 byIndex = 0;
	TTPVMPMember* ptDec = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartVmp dwEqpID:%d, emStyle:%d, emTpStyle:%d, DecNum:%d.\n", dwEqpID, 
		tInfo.m_emVmpStyle, tInfo.m_emVmpTpStyle, tInfo.m_byVMPMemberNum);
	for (byIndex = 0; byIndex < tInfo.m_byVMPMemberNum; ++byIndex)
	{
		ptDec = &tInfo.m_atVMPMember[byIndex];
		if (ptDec->m_wEpID == 0)
		{
			continue;
		}
		tpLowHint(Ums_Mdl_Xmpu, "  wIndex:%d, EpId:%d,wScreen:%d, byStat:%d, EncryModle:%d, EncryKey:%s, DynLoad:%d, StaticLoad:%d, Alias:%s.\n", 
				byIndex, ptDec->m_wEpID, ptDec->m_wScreenIndx, ptDec->m_byStat, ptDec->m_tEncrypt.m_emEncryptModel, 
				ptDec->m_tEncrypt.m_achEncKey, ptDec->m_wDynamicPayload, ptDec->m_wStaticPayload, 
				ptDec->m_tAlias.m_abyAlias);
	}

	TUmsVidFormat* ptEnc = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartVmp EncNum:%d \n", tInfo.m_byOutMemBerNum);
	for (byIndex = 0; byIndex < tInfo.m_byOutMemBerNum; ++byIndex)
	{
		ptEnc = &tInfo.m_atVMPOutMember[byIndex];
		if (ptEnc->m_emFormat == 0)
		{
			continue;
		}
		tpLowHint(Ums_Mdl_Xmpu, "  wIndex:%d, emFormat:%d, emRes:%d, wFrameRate:%d, wBitrate:%d,emQualityLvl:%d.\n", 
			byIndex, ptEnc->m_emFormat, ptEnc->m_emRes, ptEnc->m_wFrameRate,
			ptEnc->m_wBitrate, ptEnc->m_emQualityLvl);
	}

	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tInfo.m_atVMPMember[0].m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
	tEncrtpt.SetEncryptKey(tInfo.m_atVMPMember[0].m_tEncrypt.m_byKeyLen, 
		(u8*)tInfo.m_atVMPMember[0].m_tEncrypt.m_achEncKey);
	// 编码参数
	MediaAPI::TVmpEncChnParam tEncChnParam[TP_VMP_MAX_OUT_CHN_NUM];
	for (byIndex = 0; byIndex < tInfo.m_byOutMemBerNum; ++byIndex)
	{
		ConvertVidForamtFromUmsToXmpu(tInfo.m_atVMPOutMember[byIndex], tStreamCap);

		atEncParam[byIndex].SetVidStreamCap(tStreamCap);
		atEncParam[byIndex].SetEncryptParam(tEncrtpt);

		tCap.SetVidCap(tStreamCap);
		tEncChnParam[byIndex].SetEncChnId(byIndex);
		tEncChnParam[byIndex].SetEncryptParam(tEncrtpt);
		tEncChnParam[byIndex].SetEncCap(tCap);
	}

	u16 wMaxIndex = 0;
	CTpTypeAdpt::GetMaxCap(&tInfo.m_atVMPOutMember[0], tInfo.m_byOutMemBerNum, wMaxIndex);
	ConvertVidForamtFromUmsToXmpu(tInfo.m_atVMPOutMember[wMaxIndex], tStreamCap);

	// create
	if (!MediaAPI::CVmpMgr::Create(tInfo.m_byOutMemBerNum, &atEncParam[0], dwVmpHandle, &tStreamCap))
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartVmp MediaAPI::CVmpMgr::Create failed!\n");
		return FALSE;
	}

	MediaAPI::CVmpMgr::SetUserData(dwVmpHandle, tInfo.m_wConfID);
	
	// 开启合成
	if (!MediaAPI::CVmpMgr::Start(dwVmpHandle))
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartVmp MediaAPI::CVmpMgr::Start failed!\n");
		return FALSE;
	}

	// 与create填的数据一样 覆盖先前配置
	for (byIndex = 0; byIndex < tInfo.m_byOutMemBerNum; ++byIndex)
	{
		MediaAPI::CVmpMgr::AddEncChnnl(dwVmpHandle, byIndex);
	}
  	MediaAPI::CVmpMgr::SetEncChnParam(dwVmpHandle, tInfo.m_byOutMemBerNum, &tEncChnParam[0]);

	// 解码参数
	MediaAPI::TVmpDecParam tParam;
	MediaAPI::TVidDecParam tVidParam;
	MediaAPI::TMediaPayload tload;
	MediaAPI::TChnProperty atChnPro[TP_VMP_MAX_IN_CHN_NUM];
	MediaAPI::TDisPlayParam atParam[TP_VMP_MAX_IN_CHN_NUM];
	MediaAPI::TShowMode atMode[TP_VMP_MAX_IN_CHN_NUM];
	for (byIndex = 0; byIndex < tInfo.m_byVMPMemberNum; ++byIndex)
	{
		tload.SetRealPayload((u8)tInfo.m_atVMPMember[byIndex].m_wStaticPayload);
		tload.SetActivPayload((u8)tInfo.m_atVMPMember[byIndex].m_wDynamicPayload);

		byEncType = ConvertEncKeyModeFromUmsToXmpu(tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_emEncryptModel);
		tEncrtpt.SetEncryptMode(byEncType);
		tEncrtpt.SetEncryptKey(tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_byKeyLen, 
			(u8*)tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_achEncKey);

		tVidParam.SetEncryptParam(tEncrtpt);
		tVidParam.SetMediaPayload(tload);
		tParam.SetDecMediaType(MEDIA_TYPE_H264);
		tParam.SetVidDecParam(tVidParam);

		u8 byPro = tInfo.m_atVMPMember[byIndex].m_byStat == 2?MediaAPI::emChairman:MediaAPI::emAudience;
		atChnPro[byIndex].SetChnProperty(byIndex, byPro);

		atParam[byIndex].SetChnId(byIndex);
		atParam[byIndex].SetChnAlias(tInfo.m_atVMPMember[byIndex].m_tAlias.m_abyAlias,TP_MAX_ALIAS_LEN);

 		atMode[byIndex].SetShowMode(byIndex, (u8)MEDIAVMP_SHOW_LASTFRAME_MODE);//

		MediaAPI::CVmpMgr::AddDecChnnl(dwVmpHandle, byIndex);
		MediaAPI::CVmpMgr::SetDecChnParam(dwVmpHandle, byIndex, tParam);
	}

	// 设置界面通道参数
	for (byIndex = 0; byIndex < TP_VMP_MAX_IN_CHN_NUM; ++byIndex)
	{
		atMode[byIndex].SetShowMode(byIndex, (u8)MEDIAVMP_SHOW_LASTFRAME_MODE);
	}
	MediaAPI::CVmpMgr::SetChnnlProperty(dwVmpHandle, tInfo.m_byVMPMemberNum, &atChnPro[0]);
  	MediaAPI::CVmpMgr::SetDecChnAlias(dwVmpHandle, tInfo.m_byVMPMemberNum, &atParam[0]);
	MediaAPI::CVmpMgr::SetNoStreamShowMode(dwVmpHandle, MEDIAVMP_SHOW_LASTFRAME_MODE, 
		TP_VMP_MAX_IN_CHN_NUM, &atMode[0]);
	//  	MediaAPI::CVmpMgr::SetChnColor();

	MediaAPI::TVmpCommCfg tcfg;
	tcfg.SetRimEnabled(0);// 默认不使用边框
 	tcfg.SetIdleChlShowMode((u8)MEDIAVMP_SHOW_LASTFRAME_MODE); // vmp通道显示最后一帧
	tcfg.SetIsDisplayAlias(0);//默认不显示屏的名字
	tcfg.SetEncodType(MEDIA_ENCODING_GBK); // gbk
	tcfg.SetBackgroundColor(MEDIADEFAULT_BACKGROUND_COLOR); //画面合成风格默认RGB值
	tcfg.SetVoiceHint(0); 
   	MediaAPI::CVmpMgr::SetCommCfg(dwVmpHandle, tcfg);	
	
	u8 byStyle = 0;
	if (em_ums_vmp_invalid != tInfo.m_emVmpTpStyle)
	{
		byStyle = ConvertMpu2StyleFromUmsToXmpu(tInfo.m_emVmpTpStyle);
	}
	else if (tp_VmpStyle_DYNAMIC != tInfo.m_emVmpStyle)
	{
		byStyle = ConvertVmpStyleFromUmsToXmpu(tInfo.m_emVmpStyle);
	}
	else
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartVmp Invalid Style!!!\n");
		return FALSE;
	}

	if (!MediaAPI::CVmpMgr::ChgStyle(dwVmpHandle, byStyle))
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartVmp MediaAPI::CVmpMgr::ChgStyle failed! vmpstyle:%d, vmptpstyle:%d, byStyle:%d.\n",
			tInfo.m_emVmpStyle, tInfo.m_emVmpTpStyle, byStyle);
		return FALSE;
	}

	g_mapVmp.insert(std::make_pair(dwVmpHandle, dwEqpID));
	return TRUE;
}

void MediaReleaseVmp(IN HMEDIARES dwVmpHandle)
{
	if (INVALID_HMEDIARES != dwVmpHandle)
	{
		g_mapVmp.erase(dwVmpHandle);
		// 结束合成
		MediaAPI::CVmpMgr::Stop(dwVmpHandle);
		MediaAPI::CVmpMgr::Destroy(dwVmpHandle);
	}
}

BOOL32 MediaChangeVmp( IN HMEDIARES& dwVmpHandle, IN TTVmpStartParam tInfo, IN u8 byOldDecNum)
{
	u8 byIndex = 0;
	TTPVMPMember* ptDec = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaChangeVmp emStyle:%d, DecNum:%d.\n",
			tInfo.m_emVmpStyle, tInfo.m_byVMPMemberNum);
	for (byIndex = 0; byIndex < tInfo.m_byVMPMemberNum; ++byIndex)
	{
		ptDec = &tInfo.m_atVMPMember[byIndex];
		tpLowHint(Ums_Mdl_Xmpu, "  wIndex:%d, EpId:%d, wScreen:%d, byStat:%d, EncryModle:%d, EncryKey:%s, DynLoad:%d, StaticLoad:%d, Alias:%s.\n", 
			byIndex, ptDec->m_wEpID, ptDec->m_wScreenIndx, ptDec->m_byStat, ptDec->m_tEncrypt.m_emEncryptModel, 
			ptDec->m_tEncrypt.m_achEncKey, ptDec->m_wDynamicPayload, ptDec->m_wStaticPayload, 
			ptDec->m_tAlias.m_abyAlias);
	}
	
	u8 byStyle = ConvertVmpStyleFromUmsToXmpu(tInfo.m_emVmpStyle);
	if (!MediaAPI::CVmpMgr::ChgStyle(dwVmpHandle, byStyle))
	{
		tpError(Ums_Mdl_Xmpu, "MediaChangeVmp MediaAPI::CVmpMgr::ChgStyle failed!, vmpstyle:%d, byStyle:%d.\n",
			tInfo.m_emVmpStyle, byStyle);
		return FALSE;
	}

	// 解码参数
	MediaAPI::TVmpDecParam tParam;
	MediaAPI::TVidDecParam tVidParam;
	MediaAPI::TMediaPayload tload;
	MediaAPI::TMediaEncryptParam tEncrtpt;
	MediaAPI::TShowMode atMode[TP_VMP_MAX_IN_CHN_NUM];
	u8 byEncType = ENCRYPT_NONE;
	for (byIndex = 0; byIndex < tInfo.m_byVMPMemberNum; ++byIndex)
	{
		tload.SetRealPayload((u8)tInfo.m_atVMPMember[byIndex].m_wStaticPayload);
		tload.SetActivPayload((u8)tInfo.m_atVMPMember[byIndex].m_wDynamicPayload);

		byEncType = ConvertEncKeyModeFromUmsToXmpu(tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_emEncryptModel);
		tEncrtpt.SetEncryptMode(byEncType);
		tEncrtpt.SetEncryptKey(tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_byKeyLen, 
			(u8*)tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_achEncKey);
		tVidParam.SetEncryptParam(tEncrtpt);
		
		tVidParam.SetMediaPayload(tload);
		tParam.SetDecMediaType(MEDIA_TYPE_H264);
		tParam.SetVidDecParam(tVidParam);

		tpLowHint(Ums_Mdl_Xmpu, "MediaChangeVmp Dec wIndex:%d, DynLoad:%d, StaticLoad:%d, key(%u-%u-%s).\n",
			byIndex, tVidParam.GetMediaPayload().GetActivPayload(), tVidParam.GetMediaPayload().GetRealPayload(),
			byEncType, tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_byKeyLen, 
			tInfo.m_atVMPMember[byIndex].m_tEncrypt.m_achEncKey);
		if (TP_INVALID_INDEX == tInfo.m_atVMPMember[byIndex].m_wEpID)
		{
			MediaAPI::CVmpMgr::RemoveDecChnnl(dwVmpHandle, byIndex);
		}
		MediaAPI::CVmpMgr::AddDecChnnl(dwVmpHandle, byIndex);
		MediaAPI::CVmpMgr::SetDecChnParam(dwVmpHandle, byIndex, tParam);
		atMode[byIndex].SetShowMode(byIndex, (u8)MEDIAVMP_SHOW_LASTFRAME_MODE);//界面参数
	}
	//设置界面参数，显示最后一帧
	MediaAPI::CVmpMgr::SetNoStreamShowMode(dwVmpHandle, MEDIAVMP_SHOW_LASTFRAME_MODE, 
		tInfo.m_byVMPMemberNum, &atMode[0]);
	return TRUE;
}

BOOL32 MediaChangeVmpTP( IN HMEDIARES& dwVmpHandle, IN TVmpStartInfo tInfo )
{
	u8 byIndex = 0;
	TVmpMemberInfo* ptDec = NULL;
	TDBPayload* ptLoad = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaChangeVmpTP dwVmpHandle:%d, DecNum:%d, byTpStyle:%d.\n", dwVmpHandle, 
		tInfo.m_tVmpParam.m_tStyleInfo.m_byMemberNum,
		tInfo.m_tVmpParam.m_tStyleInfo.m_emVmpStyle);

	for (byIndex = 0; byIndex < tInfo.m_tVmpParam.m_tStyleInfo.m_byMemberNum; ++byIndex)
	{
		ptDec = &tInfo.m_tVmpParam.m_tStyleInfo.m_atMemberInfo[byIndex];
		ptLoad = &tInfo.m_tVmpParam.m_tStyleInfo.m_atDoublePayload[byIndex];
		tpLowHint(Ums_Mdl_Xmpu, "  wIndex:%d, m_bMerged:%d, dwHandle:%d, realLoad:%d, activeLoad:%d.\n", 
			byIndex, ptDec->m_bMerged, ptDec->m_dwHandle, ptLoad->m_byRealPayload, ptLoad->m_byActivePayload);
	}

	TVmpEncParam* ptEnc = &tInfo.m_tVmpParam.m_tEncParam;
	tpLowHint(Ums_Mdl_Xmpu, "MediaChangeVmpTP m_byEncType:%d, m_byFrameRate:%d, m_byProfileType:%d, m_wBitRate:%d, m_wVideoWidth:%d, m_wVideoHeight:%d.\n", 
		ptEnc->m_byEncType, ptEnc->m_byFrameRate, 
		ptEnc->m_byProfileType, ptEnc->m_wBitRate, ptEnc->m_wVideoWidth, ptEnc->m_wVideoHeight);
	
	u8 byStyle = ConvertMpu2StyleFromUmsToXmpu(tInfo.m_tVmpParam.m_tStyleInfo.m_emVmpStyle);
	if (!MediaAPI::CVmpMgr::ChgStyle(dwVmpHandle, byStyle))
	{
		tpError(Ums_Mdl_Xmpu, "MediaChangeVmpTP MediaAPI::CVmpMgr::ChgStyle failed!, vmpstyle:%d, byStyle:%d.\n",
			tInfo.m_tVmpParam.m_tStyleInfo.m_emVmpStyle, byStyle);
		return FALSE;
	}

	// 解码参数
	MediaAPI::TVmpDecParam tParam;
	MediaAPI::TVidDecParam tVidParam;
	MediaAPI::TMediaPayload tload;
	MediaAPI::TMediaEncryptParam tEncrtpt;
	MediaAPI::TShowMode atMode[TP_VMP_MAX_IN_CHN_NUM];
	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tInfo.m_tVmpParam.m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
	tEncrtpt.SetEncryptKey(tInfo.m_tVmpParam.m_tEncrypt.m_byKeyLen, 
		(u8*)tInfo.m_tVmpParam.m_tEncrypt.m_achEncKey);

	for (byIndex = 0; byIndex < tInfo.m_tVmpParam.m_tStyleInfo.m_byMemberNum; ++byIndex)
	{
		tload.SetRealPayload(tInfo.m_tVmpParam.m_tStyleInfo.m_atDoublePayload[byIndex].m_byRealPayload);
		tload.SetActivPayload(tInfo.m_tVmpParam.m_tStyleInfo.m_atDoublePayload[byIndex].m_byActivePayload);
			
		tVidParam.SetEncryptParam(tEncrtpt);
		tVidParam.SetMediaPayload(tload);
		tParam.SetDecMediaType(MEDIA_TYPE_H264);
		tParam.SetVidDecParam(tVidParam);
		MediaAPI::CVmpMgr::AddDecChnnl(dwVmpHandle, byIndex);
		MediaAPI::CVmpMgr::SetDecChnParam(dwVmpHandle, byIndex, tParam);
		atMode[byIndex].SetShowMode(byIndex, (u8)MEDIAVMP_SHOW_LASTFRAME_MODE);//界面参数
	}

//设置界面参数，显示最后一帧
    MediaAPI::CVmpMgr::SetNoStreamShowMode(dwVmpHandle, MEDIAVMP_SHOW_LASTFRAME_MODE, 
	 tInfo.m_tVmpParam.m_tStyleInfo.m_byMemberNum, &atMode[0]);

	MediaAPI::TVmpEncChnParam tEncParam;
	MediaAPI::TMediaVidStreamCap tStream;
	tStream.SetVidType(tInfo.m_tVmpParam.m_tEncParam.m_byEncType);
	tStream.SetFrameRate(tInfo.m_tVmpParam.m_tEncParam.m_byFrameRate);
	tStream.SetBitRate(tInfo.m_tVmpParam.m_tEncParam.m_wBitRate);
	tStream.SetProfileType(tInfo.m_tVmpParam.m_tEncParam.m_byProfileType);
	tStream.SetHeight(tInfo.m_tVmpParam.m_tEncParam.m_wVideoHeight);
	tStream.SetWidth(tInfo.m_tVmpParam.m_tEncParam.m_wVideoWidth);
	tStream.SetRealPayload(tload.GetRealPayload());
	tStream.SetActivPayload(tload.GetActivPayload());
	tEncParam.SetVidCap(tStream);
	tEncParam.SetEncChnId(0);
	tEncParam.SetEncryptParam(tEncrtpt);

	// 擦除3屏右边框
	u8 abyBorder[UMS_VMP_MAX_RCV] = {0};
	u8 byNum = 0;
	for (u8 byIndex = 1; byIndex < tInfo.m_tVmpParam.m_tStyleInfo.m_byMemberNum; ++byIndex)
	{
		if (tInfo.m_tVmpParam.m_tStyleInfo.m_atMemberInfo[byIndex].m_bMerged)
		{
			abyBorder[byNum++] = byIndex;
		}
	}
	tpLowHint(Ums_Mdl_Xmpu, "MediaChangeVmpTP RemoveRightBorder byNum:%d, board:(%d|%d|%d|%d|%d|%d|%d|%d|%d|%d).\n", byNum, 
				abyBorder[0], abyBorder[1], abyBorder[2], abyBorder[3],
				abyBorder[4], abyBorder[5], abyBorder[6], abyBorder[7],
				abyBorder[8], abyBorder[9]);
	MediaAPI::CVmpMgr::RemoveRightBorder(dwVmpHandle, byNum, &abyBorder[0]);

	MediaAPI::CVmpMgr::AddEncChnnl(dwVmpHandle, 0);
	MediaAPI::CVmpMgr::SetEncChnParam(dwVmpHandle, 1, &tEncParam);

	return TRUE;
}

BOOL32 MediaUpdateLineSide( IN HMEDIARES& dwVmpHandle, IN TVmpSpeakerFlag tInfo )
{
	MediaAPI::TVmpChnColor atChnColor[UMS_VMP_MAX_RCV];
	for (u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		atChnColor[wIndex].SetChnId(tInfo.m_abyFlag[wIndex]);
		if (tInfo.m_abyFlag[wIndex] == 0)
		{//白色
			atChnColor[wIndex].SetFrameColor(0);
		}
		else
		{//绿色
			atChnColor[wIndex].SetFrameColor(MEDIADEFAULT_TEXT_COLOR);
		}
		
	}
	MediaAPI::CVmpMgr::SetChnColor(dwVmpHandle, UMS_VMP_MAX_RCV, &atChnColor[0]);
	return TRUE;
}

void MediaReqVmpIFrame(IN HMEDIARES dwVmpHandle, IN u32 dwChnId)
{
	MediaAPI::CVmpMgr::ReqEncIFrame(dwVmpHandle, dwChnId);
}

BOOL32 MediaSetVmpDecAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, IN TTPTransAddr tInAddr)
{
	MediaAPI::TAddrs tAddr;
	tAddr.SetIpAddr(ntohl(tInAddr.m_dwIP));
	tAddr.SetPort(tInAddr.m_wPort);
	return MediaAPI::CVmpMgr::SetSrcRtcpRcvAddrs(dwVmpHandle, dwChnId, tAddr);
}

BOOL32 MediaSetVmpEncAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, IN TTPTransAddr tInAddr)
{
	MediaAPI::TAddrs tAddr;
	tAddr.SetIpAddr(ntohl(tInAddr.m_dwIP));
	tAddr.SetPort(tInAddr.m_wPort);
	return MediaAPI::CVmpMgr::SetDstRtpRcvAddrs(dwVmpHandle, dwChnId, tAddr);
}

BOOL32 MediaGetVmpDecAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (!MediaAPI::CVmpMgr::GetLocalRtpRcvAddrs(dwVmpHandle, dwChnId, tAddr))
	{
		return FALSE;
	}
	tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
	tOutAddr.m_wPort = tAddr.GetPort();
	return TRUE;
}

BOOL32 MediaGetVmpEncAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (!MediaAPI::CVmpMgr::GetLocalRtcpRcvAddrs(dwVmpHandle, dwChnId, tAddr))
	{
		return FALSE;
	}
	tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
	tOutAddr.m_wPort = tAddr.GetPort();
	return TRUE;
}

// byMaxStyle:最大(4)几风格下全适配  byVipNum:风格超过(4), 可用适配通道数
BOOL32 MediaGetVmpVipNum( IN HMEDIARES dwVmpHandle, OUT u8& byMaxStyle,OUT u8& byVipNum)
{
	MediaAPI::TVmpHdChnInfo tInfo;
	MediaAPI::CVmpMgr::GetVmpHdChnnlNum(dwVmpHandle,  tInfo);
	byMaxStyle = tInfo.GetMaxStyle();
	byVipNum = tInfo.GetMaxHdChnCnt();
	return TRUE;
}

/****MediaBase接口调用****/
BOOL32 MediaStartBase(OUT HMEDIARES& dwBasHandle, IN APPHANDLE dwEqpID, IN TXmpuBasParam tParam)
{

	MediaAPI::TBasEncParam atEncParam[TP_CONF_MAX_MINOR_VIDEO_RES_NUM];
	MediaAPI::TStreamCap tCap;
	MediaAPI::TMediaVidStreamCap tStreamCap;
	MediaAPI::TMediaEncryptParam tEncrtpt;
	MediaAPI::TBasEncChnParam atEnc[TP_CONF_MAX_MINOR_VIDEO_RES_NUM];
	u16 wIndex = 0;
	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tParam.m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
	tEncrtpt.SetEncryptKey(tParam.m_tEncrypt.m_byKeyLen, 
		(u8*)tParam.m_tEncrypt.m_achEncKey);

	TUmsVidFormat* ptEnc = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartBase EntryModle:%d, EncKey:%s, DynaLoad:%d, StatLoad:%d, EncOutInfo EncNum:%d.\n",
		tParam.m_tEncrypt.m_emEncryptModel, tParam.m_tEncrypt.m_achEncKey, tParam.m_wDynamicPayload,
		tParam.m_wStaticPayload, tParam.m_tBasParam.m_byParamNum);
	for (wIndex = 0; wIndex < tParam.m_tBasParam.m_byParamNum; ++wIndex)
	{
		ptEnc = &tParam.m_tBasParam.m_atVidParam[wIndex];
		tpLowHint(Ums_Mdl_Xmpu, "  wIndex:%d, emFormat:%d, emRes:%d, wFrameRate:%d, wBitrate:%d, emQualityLvl:%d.\n", 
			wIndex, ptEnc->m_emFormat, ptEnc->m_emRes, ptEnc->m_wFrameRate,
			ptEnc->m_wBitrate, ptEnc->m_emQualityLvl);
	}
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartBase Dec emFormat:%d, emRes:%d, wFrameRate:%d, wBitrate:%d, emQualityLvl:%d.\n", 
		tParam.m_tMaxBasParam.m_emFormat, tParam.m_tMaxBasParam.m_emRes, tParam.m_tMaxBasParam.m_wFrameRate,
		tParam.m_tMaxBasParam.m_wBitrate, tParam.m_tMaxBasParam.m_emQualityLvl);

	for (wIndex = 0; wIndex < tParam.m_tBasParam.m_byParamNum; ++wIndex)
	{
		ConvertVidForamtFromUmsToXmpu(tParam.m_tBasParam.m_atVidParam[wIndex], tStreamCap);
		tCap.SetVidCap(tStreamCap);
		atEncParam[wIndex].SetBasVidEncCap(tStreamCap);
		atEncParam[wIndex].SetEncryptParam(tEncrtpt);   //编码加密参数

		atEnc[wIndex].SetChnId(wIndex);
		atEnc[wIndex].SetChnParam(atEncParam[wIndex]);
	}

	u16 wMaxIndex = 0;
	ConvertVidForamtFromUmsToXmpu(tParam.m_tMaxBasParam, tStreamCap); // max
	if (!MediaAPI::CBasMgr::Create(tParam.m_tBasParam.m_byParamNum, &atEncParam[0], dwBasHandle, TRUE, &tStreamCap))
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartBase MediaAPI::CBasMgr::Create failed!\n");
		return FALSE;
	}
	MediaAPI::CBasMgr::SetUserData(dwBasHandle, tParam.m_wConfID);

	MediaAPI::CBasMgr::SetEncChnParam(dwBasHandle, tParam.m_tBasParam.m_byParamNum, &atEnc[0]);
	MediaAPI::TBasDecParam tBasDecParam;
	MediaAPI::TVidDecParam tDecParam;
	MediaAPI::TMediaPayload tLoad;
	tLoad.SetActivPayload((u8)tParam.m_wDynamicPayload);
	tLoad.SetRealPayload((u8)tParam.m_wStaticPayload);
	tDecParam.SetEncryptParam(tEncrtpt);   //解码加密参数
	tDecParam.SetMediaPayload(tLoad);
	tBasDecParam.SetBasVidDecParam(tDecParam);
	MediaAPI::CBasMgr::SetDecParam(dwBasHandle, tBasDecParam);

// 	
// 	MediaAPI::CBasMgr::SetDecDependOnTS();
// 	MediaAPI::CBasMgr::SetEncChnParam();
	BOOL32 bRes = MediaAPI::CBasMgr::Start(dwBasHandle);
	if (bRes)
	{
		tpLowHint(Ums_Mdl_Xmpu, "MediaStartBase Start BasHandle:%d, EqpID:%d.\n",dwBasHandle,dwEqpID);
		g_mapBas.insert(std::make_pair(dwBasHandle, dwEqpID));
	}
	return bRes;
		
}

void MediaReleaseBase( IN HMEDIARES dwBasHandle )
{
	g_mapBas.erase(dwBasHandle);
	// 结束合成
	MediaAPI::CBasMgr::Stop(dwBasHandle);
	MediaAPI::CBasMgr::Destroy(dwBasHandle);
}

void MediaSetBasParam(IN HMEDIARES dwBasHandle, IN TXmpuChgBasInfo tInfo)
{
	MediaAPI::TBasEncChnParam atParam[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	MediaAPI::TMediaVidStreamCap tStreamCap;
	MediaAPI::TBasEncParam tEncParam;
	MediaAPI::TMediaEncryptParam  tEncrypt;
	
	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tInfo.m_tEncrypt.m_emEncryptModel);
	tEncrypt.SetEncryptMode(byEncType);
	tEncrypt.SetEncryptKey(tInfo.m_tEncrypt.m_byKeyLen, (u8*)tInfo.m_tEncrypt.m_achEncKey);

	u8 byIndex = 0;
	TUmsVidFormat* ptEnc = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaSetBasParam EntryModle:%d, EncKey:%s, DynaLoad:%d, StatLoad:%d, EncOutInfo EncNum:%d \n",
		tInfo.m_tEncrypt.m_emEncryptModel, tInfo.m_tEncrypt.m_achEncKey, tInfo.m_wDynamicPayload,
		tInfo.m_wStaticPayload, tInfo.m_tBasParam.m_byParamNum);
	for (byIndex = 0; byIndex < tInfo.m_tBasParam.m_byParamNum; ++byIndex)
	{
		ptEnc = &tInfo.m_tBasParam.m_atVidParam[byIndex];
		tpLowHint(Ums_Mdl_Xmpu, "  wIndex:%d, emFormat:%d, emRes:%d, wFrameRate:%d, wBitrate:%d, emQualityLvl:%d\n", 
			byIndex, ptEnc->m_emFormat, ptEnc->m_emRes, ptEnc->m_wFrameRate,
			ptEnc->m_wBitrate, ptEnc->m_emQualityLvl);
	}

	for (byIndex = 0; byIndex < tInfo.m_tBasParam.m_byParamNum; ++byIndex)
	{
		ConvertVidForamtFromUmsToXmpu(tInfo.m_tBasParam.m_atVidParam[byIndex], tStreamCap);
		tEncParam.SetBasVidEncCap(tStreamCap);
		tEncParam.SetEncryptParam(tEncrypt);      //编码加密参数
		atParam[byIndex].SetChnId(byIndex);
		atParam[byIndex].SetChnParam(tEncParam);
	}

	MediaAPI::CBasMgr::SetEncChnParam(dwBasHandle, tInfo.m_tBasParam.m_byParamNum, atParam);

	MediaAPI::TBasDecParam tBasDecParam;
	MediaAPI::TVidDecParam tDecParam;
	MediaAPI::TMediaPayload tLoad;
	tLoad.SetActivPayload((u8)tInfo.m_wDynamicPayload);
	tLoad.SetRealPayload((u8)tInfo.m_wStaticPayload);
	tDecParam.SetEncryptParam(tEncrypt);    //解码加密参数
	tDecParam.SetMediaPayload(tLoad);
	tBasDecParam.SetBasVidDecParam(tDecParam);
	MediaAPI::CBasMgr::SetDecParam(dwBasHandle, tBasDecParam);
}

void MediaReqBasIFrame(IN HMEDIARES dwBasHandle, IN u8 byChnId)
{
	MediaAPI::CBasMgr::ReqIFrame(dwBasHandle, byChnId);
}

BOOL32 MediaSetBasDecAddr(IN HMEDIARES dwBasHandle, IN TTPTransAddr tInAddr)
{
	MediaAPI::TAddrs tAddr;
	tAddr.SetIpAddr(ntohl(tInAddr.m_dwIP));
	tAddr.SetPort(tInAddr.m_wPort);
	return MediaAPI::CBasMgr::SetSrcRtcpRcvAddrs(dwBasHandle, tAddr);
}

BOOL32 MediaSetBasEncAddr(IN HMEDIARES dwBasHandle, IN u8 byChnId, IN TTPTransAddr tInAddr)
{
	MediaAPI::TAddrs tAddr;
	tAddr.SetIpAddr(ntohl(tInAddr.m_dwIP));
	tAddr.SetPort(tInAddr.m_wPort);
	return MediaAPI::CBasMgr::SetDstRtpRcvAddrs(dwBasHandle, byChnId, tAddr);
}

BOOL32 MediaGetBasDecAddr(IN HMEDIARES dwBasHandle, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (!MediaAPI::CBasMgr::GetLocalRtpRcvAddrs(dwBasHandle, tAddr))
	{
		return FALSE;
	}
	else
	{
		tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
		tOutAddr.m_wPort = tAddr.GetPort();
		return TRUE;
	}
}

BOOL32 MediaGetBasEncAddr(IN HMEDIARES dwBasHandle, IN u8 byChnId, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (!MediaAPI::CBasMgr::GetLocalRtcpRcvAddrs(dwBasHandle, byChnId, tAddr))
	{
		return FALSE;
	}
	else
	{
		tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
		tOutAddr.m_wPort = tAddr.GetPort();
		return TRUE;
	}
}

/****MediaMix接口调用****/
BOOL32 MediaStartMix(OUT HMEDIARES& dwMixHandle, IN APPHANDLE dwEqpID, IN TXmpuMixParam tParam)
{
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartMix dwEqpID:%d, ConfID:%d, DsIP:"TPIPFORMAT", byChnNum:%d, byDepth:%d.\n",
		dwEqpID, tParam.m_wConfID,Tpu32ToIP(tParam.m_dwMediaIp), tParam.m_byChanNum, tParam.m_byMixDepth);

	tpLowHint(Ums_Mdl_Xmpu, "MediaStartMix emEncry:%d, EncryKey:%s, byNNum:%d \n",
		tParam.m_tEncrypt.m_emEncryptModel, 
		tParam.m_tEncrypt.m_achEncKey, tParam.m_byNNum);

	TUmsAudFormat* ptFormat = NULL;
	for (u16 wNum = 0; wNum <  tParam.m_byNNum; ++wNum)
	{
		ptFormat = &tParam.m_atAudFmt[wNum];
		tpLowHint(Ums_Mdl_Xmpu, "  emFormat:%d, Freq:%d, ChnCfg:%d, DsIP:"TPIPFORMAT", wPort:%d.\n",
			ptFormat->m_emFormat, ptFormat->m_emSampleFreq, ptFormat->m_emChnlCfg,
			Tpu32ToIP(tParam.m_atNEncRtpAddr[wNum].m_dwIP), tParam.m_atNEncRtpAddr[wNum].m_wPort);
	}

	MediaAPI::TMixInitParam tInfo;
	MediaAPI::TMediaEncryptParam tEncrtpt;

	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tParam.m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
	tEncrtpt.SetEncryptKey(tParam.m_tEncrypt.m_byKeyLen, 
		(u8*)tParam.m_tEncrypt.m_achEncKey);
	tInfo.SetMixChnNum(tParam.m_byChanNum); // n-1通道
	tInfo.SetMixDepth(tParam.m_byMixDepth);
	tInfo.SetMixEncNNum(tParam.m_byNNum);
	tInfo.SetEncryptParam(tEncrtpt);        //加密参数

	MediaAPI::TMixEncParam tEnParam;
	MediaAPI::TMediaAudStreamCap tAudStream;
	MediaAPI::TAddrs tAddr;
	for (u8 byIndex  = 0; byIndex< tParam.m_byNNum; ++byIndex)
	{
// 		tAudStream.SetAudType(CTpTypeAdpt::GetAudPayloadValue(tParam.m_atAudFmt[byIndex].m_emFormat));
// 		tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
// 		tAudStream.SetTrackNum(1); // 单声道写死 1
// 		tAudStream.SetRealPayload((u8)tParam.m_wStaticPayload);
// 		tAudStream.SetActivPayload((u8)tParam.m_wDynamicPayload);
// 
// 		tAddr.SetIpAddr(ntohl(tParam.m_atNEncRtpAddr[byIndex].m_dwIP));
// 		tAddr.SetPort(tParam.m_atNEncRtpAddr[byIndex].m_wPort);
// 		tEnParam.SetRtpRcvAddrs(tAddr);
// 		tEnParam.SetEncryptParam(tEncrtpt);
// 		tEnParam.SetMixEncCap(tAudStream);

		tInfo.SetEncParam(byIndex, tEnParam);
	}
	if (!MediaAPI::CMixMgr::Create(tInfo, dwMixHandle))
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartMix MediaAPI::CBasMgr::Create failed!\n");
		return FALSE;
	}
	MediaAPI::CMixMgr::SetUserData(dwMixHandle, tParam.m_wConfID);

	u8 byNum = 0;
	u8 abyNID[4] = {0};
	MediaAPI::CMixMgr::GetEncNChnNum(dwMixHandle, byNum, abyNID);
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartMix Before EncNNum:%d, byNID(%d|%d|%d|%d).\n",
					byNum, abyNID[0], abyNID[1], abyNID[2], abyNID[3]);
	u8 byEncChnId = 0;
	for (u8 byIndex  = 0;  byIndex < tParam.m_byNNum; ++byIndex)
	{
		u8 byType = CTpTypeAdpt::GetAudPayloadValue(tParam.m_atAudFmt[byIndex].m_emFormat);
		tAudStream.SetAudType(byType);
		tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
		tAudStream.SetTrackNum(1); // 单声道写死 1
		tAudStream.SetRealPayload(byType);
		tAudStream.SetActivPayload(byType);

		tAddr.SetIpAddr(ntohl(tParam.m_atNEncRtpAddr[byIndex].m_dwIP));
		tAddr.SetPort(tParam.m_atNEncRtpAddr[byIndex].m_wPort);
		tEnParam.SetRtpRcvAddrs(tAddr);
		tEnParam.SetEncryptParam(tEncrtpt);   //加密参数            
		tEnParam.SetMixEncCap(tAudStream);

		tpLowHint(Ums_Mdl_Xmpu, "MediaStartMix AddEncNParam byIndex:%d, byNum:%d.\n",
			byIndex, tParam.m_byNNum);
		MediaAPI::CMixMgr::AddEncNParam(dwMixHandle, tEnParam, byEncChnId);
	}

	MediaAPI::CMixMgr::GetEncNChnNum(dwMixHandle, byNum, abyNID);
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartMix After EncNNum:%d, byNID(%d|%d|%d|%d)\n",
		byNum, abyNID[0], abyNID[1], abyNID[2], abyNID[3]);
	//	MediaAPI::TResendConf tInfo;
	//	MediaAPI::CMixMgr::SetAudioResend();
	//	MediaAPI::CMixMgr::AddMember(dwMixHandle);

	BOOL32 bRes = MediaAPI::CMixMgr::StartMix(dwMixHandle);
	if (bRes)
	{
		g_mapMix.insert(std::make_pair(dwMixHandle, dwEqpID));
	}
	return bRes;
}

BOOL32 MediaStartVac( IN HMEDIARES dwMixHandle )
{
	return MediaAPI::CMixMgr::StartVac(dwMixHandle);
}

void MediaStopVac( IN HMEDIARES dwMixHandle )
{
	MediaAPI::CMixMgr::StopVac(dwMixHandle);
}

void MediaReleaseMix( IN HMEDIARES dwMixHandle )
{
	g_mapMix.erase(dwMixHandle);
	MediaAPI::CMixMgr::StopMix(dwMixHandle);
	MediaAPI::CMixMgr::Destroy(dwMixHandle);
}


BOOL32 MediaAddMixMember( IN HMEDIARES& dwMixHandle, IN TXmpuMixMember tMember )
{
	tpLowHint(Ums_Mdl_Xmpu, "MediaAddMixMember  dwHandle:%d, dwEqpID:%d, EpID:%d-%d, MemIndex:%d, DsIP:"TPIPFORMAT", RtpPort:%d, RtcpPort:%d, emEncryModle:%d, EncryKey:%s.\n",
		dwMixHandle, tMember.m_dwEqpID, tMember.m_wEpID, tMember.m_wScreenIndex, 
		tMember.m_byIndex, Tpu32ToIP(tMember.m_tLocalRtpRcv.GetIP()),
		tMember.m_tLocalRtpRcv.GetPort(), tMember.m_tLocalRtcpRcv.GetPort(),
		tMember.m_tEncrypt.m_emEncryptModel, tMember.m_tEncrypt.m_achEncKey);

	tpLowHint(Ums_Mdl_Xmpu, "MediaAddMixMember emDecFormat:%d-%s, emEncFormat:%d-%s.\n",
		TpEnumIdString(EmTpAudioFormat, tMember.m_emAudFormat),
		TpEnumIdString(EmTpAudioFormat, tMember.m_emOutAudFormat));

	MediaAPI::TMixMemberParam tParam;
	MediaAPI::TAddrs tAddr;
	MediaAPI::TMediaEncryptParam tEncrtpt;

	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tMember.m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
 	tEncrtpt.SetEncryptKey(tMember.m_tEncrypt.m_byKeyLen, 
 		(u8*)tMember.m_tEncrypt.m_achEncKey);

	tParam.SetForceMix(0);
	tParam.SetVolume(31/2);//MAXVALUE_APU2_VOLUME apu2最大声音
	tParam.SetChnId((u8)tMember.m_byIndex);//通道ID如何计算 从0开始还是1开始 
	
	tAddr.SetIpAddr(ntohl(tMember.m_tLocalRtpRcv.GetIP()));
	tAddr.SetPort(tMember.m_tLocalRtpRcv.GetPort());
	tParam.SetRtpRcvAddrs(tAddr);
	tAddr.SetIpAddr(ntohl(tMember.m_tLocalRtcpRcv.GetIP()));
	tAddr.SetPort(tMember.m_tLocalRtcpRcv.GetPort());
	tParam.SetRtcpRcvAddrs(tAddr);

	tParam.SetEncryptParam(tEncrtpt);

	MediaAPI::TMediaAudStreamCap tAudStream;
	u8 byType = CTpTypeAdpt::GetAudPayloadValue(tMember.m_emAudFormat);
	tAudStream.SetAudType(byType);
	tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
	tAudStream.SetTrackNum(1); // 单声道写死 1
	tAudStream.SetRealPayload(byType);
	tAudStream.SetActivPayload(byType);

	tParam.SetMixDecCap(tAudStream);

	byType = CTpTypeAdpt::GetAudPayloadValue(tMember.m_emOutAudFormat);
	tAudStream.SetAudType(byType);
	tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
	tAudStream.SetTrackNum(1); // 单声道写死 1
	tAudStream.SetRealPayload(byType);
	tAudStream.SetActivPayload(byType);

	tParam.SetMixEncCap(tAudStream);


	u8 byNum = 0;
	u8 abyID[64] = {0};
	
	MediaAPI::CMixMgr::GetEncN_1ChnNum(dwMixHandle, byNum, abyID);
	tpLowHint(Ums_Mdl_Xmpu, "MediaAddMixMember before byNum:%d, ID(%d|%d|%d|%d)\n",
		byNum, abyID[0], abyID[1], abyID[2], abyID[3]);

	MediaAPI::CMixMgr::AddN_1Chnnl(dwMixHandle, (u8*)&tMember.m_byIndex, 1, TRUE);
	MediaAPI::CMixMgr::AddN_1Chnnl(dwMixHandle, (u8*)&tMember.m_byIndex, 1, FALSE);
	BOOL32 bRes = MediaAPI::CMixMgr::AddMember(dwMixHandle, &tParam, 1);
	
	MediaAPI::CMixMgr::GetEncN_1ChnNum(dwMixHandle, byNum, abyID);
	tpLowHint(Ums_Mdl_Xmpu, "MediaAddMixMember after byNum:%d, ID(%d|%d|%d|%d)\n",
		byNum, abyID[0], abyID[1], abyID[2], abyID[3]);


	return bRes;
}

void MediaDelMixMember( IN HMEDIARES& dwMixHandle, IN u8 byChnID )
{
	MediaAPI::CMixMgr::RemoveMember(dwMixHandle, &byChnID, 1);
}

BOOL32 MediaGetMixNChnID( IN HMEDIARES& dwMixHandle, OUT u8& byNChnNum, OUT u8* byNChnID )
{
	return MediaAPI::CMixMgr::GetEncNChnNum(dwMixHandle, byNChnNum, byNChnID);
}

BOOL32 MediaGetMixN1ChnID( IN HMEDIARES& dwMixHandle, OUT u8& byNChnNum, OUT u8* byNChnID )
{
	return MediaAPI::CMixMgr::GetEncN_1ChnNum(dwMixHandle, byNChnNum, byNChnID);
}

void MediaSetKeepTime(IN HMEDIARES dwMixHandle, IN u32 dwKeepTime)
{
	MediaAPI::CMixMgr::SetVacKeepTime(dwMixHandle, dwKeepTime);
}

void MediaSetForceMix( IN HMEDIARES dwMixHandle , IN u8 byChnID, IN BOOL32 bStart)
{
	MediaAPI::CMixMgr::SetForceMix(dwMixHandle, byChnID, bStart);
}

BOOL32 MediaGetMixDecAddr(IN HMEDIARES dwMixHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (MediaAPI::CMixMgr::GetLocalRtpRcvAddrs(dwMixHandle, dwChnId, tAddr))
	{
		tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
		tOutAddr.m_wPort = tAddr.GetPort();
		return TRUE;
	}
	return FALSE;
}
	

BOOL32 MediaGetMixEncAddr(IN HMEDIARES dwMixHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (MediaAPI::CMixMgr::GetLocalRtcpRcvAddrs(dwMixHandle, dwChnId, tAddr))
	{
		tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
		tOutAddr.m_wPort = tAddr.GetPort();
		return TRUE;
	}
	return FALSE;
}

void MediaMixSetSynId( IN u32 dwSynID,  IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE164)
{
 	MediaAPI::TAudioSynDecChn atAudSynChn[TP_MAX_STREAMNUM];
 	for (u16 wIndex = 0; wIndex < byNum; ++wIndex)
 	{
		atAudSynChn[wIndex].SetHMediares(ptSynChn[wIndex].m_dwHandle);
		atAudSynChn[wIndex].SetDecChn(ptSynChn[wIndex].m_bySynChn);
		atAudSynChn[wIndex].SetE164(pchE164);
		MdlHint(Ums_Mdl_Xmpu, ("MediaMixSetSynId SynId:%d, Index:%d, Handle:%x, Synchn:%d,  E164:%s\n",dwSynID,wIndex,
			ptSynChn[wIndex].m_dwHandle, ptSynChn[wIndex].m_bySynChn,pchE164));
 	}

 	MediaAPI::CMixMgr::SetSynId (dwSynID, byNum, atAudSynChn);
}

void MediaMixFreeSynId( IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE164 )
{
		MediaAPI::TAudioSynDecChn atAudSynChn[TP_MAX_STREAMNUM];
	 	for (u16 wIndex = 0; wIndex < byNum; ++wIndex)
	 	{
			atAudSynChn[wIndex].SetHMediares(ptSynChn[wIndex].m_dwHandle);
			atAudSynChn[wIndex].SetDecChn(ptSynChn[wIndex].m_bySynChn);
			atAudSynChn[wIndex].SetE164(pchE164);			
			tpLowHint(Ums_Mdl_Xmpu, "MediaMixFreeSynId Index:%d, Handle:%x, Synchn:%d,  E164:%s\n",wIndex,
				ptSynChn[wIndex].m_dwHandle, ptSynChn[wIndex].m_bySynChn,pchE164);
	 	}
	 	MediaAPI::CMixMgr::ClearSynId  (byNum, atAudSynChn);
}


/*media adu 接口*/
BOOL32 MediaStartAudBas(OUT HMEDIARES& dwAudHandle, IN APPHANDLE dwEqpID, IN TXmpuAudBasParam tParam)
{
	TUmsAudFormat* ptFormat = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartAudBas EqpID:%d, ConfID:%d, DsIP:"TPIPFORMAT", emModle:%d, Key:%s\n",
		dwEqpID, tParam.m_wConfID,Tpu32ToIP(tParam.m_dwMediaIP), 
		tParam.m_tEncrypt.m_emEncryptModel, tParam.m_tEncrypt.m_achEncKey);

	ptFormat = &tParam.m_tAudDec;
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartAudBas  DecParam:%d, Freq:%d, ChnCfg:%d\n",
		ptFormat->m_emFormat, ptFormat->m_emSampleFreq, ptFormat->m_emChnlCfg);

	u16 wIndex = 0;
	tpLowHint(Ums_Mdl_Xmpu, "MediaStartAudBas  EncInfo: \n" );
	for (wIndex = 0; wIndex < UMS_AUDBAS_ENC_NUM; ++wIndex)
	{
		ptFormat = &tParam.m_atAudEnc[wIndex];
		tpLowHint(Ums_Mdl_Xmpu, "  EncParam:%d, Freq:%d, ChnCfg:%d\n",
			ptFormat->m_emFormat, ptFormat->m_emSampleFreq, ptFormat->m_emChnlCfg);
	}

	MediaAPI::TBasEncParam atEncParam[AUD_BAS_MAX_OUT_CHNL_NUM];
	MediaAPI::TMediaAudStreamCap tAudStream;
	MediaAPI::TMediaEncryptParam tEncrtpt;

	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tParam.m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
	tEncrtpt.SetEncryptKey(tParam.m_tEncrypt.m_byKeyLen, 
		(u8*)tParam.m_tEncrypt.m_achEncKey);

	u8 byType = 0;
	u8 byNum = 0;
	for (wIndex = 0; wIndex < AUD_BAS_MAX_OUT_CHNL_NUM; ++wIndex)
	{
		if (tParam.m_atAudEnc[wIndex].m_emFormat == emTPAEnd)
		{
			continue;
		}
		byType = CTpTypeAdpt::GetAudPayloadValue(tParam.m_atAudEnc[wIndex].m_emFormat);
		tAudStream.SetAudType(byType);
		tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
		tAudStream.SetTrackNum(1); // 单声道写死 1
		tAudStream.SetRealPayload(byType);
 		tAudStream.SetActivPayload(byType);
	
		atEncParam[wIndex].SetBasAudEncCap(tAudStream);
		atEncParam[wIndex].SetEncryptParam(tEncrtpt);
		byNum++;
	}

	if (!MediaAPI::CBasMgr::Create(byNum, &atEncParam[0], dwAudHandle, FALSE, NULL))
	{
		tpError(Ums_Mdl_Xmpu, "MediaStartAudBas MediaAPI::CBasMgr::Create failed!\n");
		return FALSE;
	}
	MediaAPI::CBasMgr::SetUserData(dwAudHandle, tParam.m_wConfID);

	MediaAPI::TBasEncChnParam atEnc[AUD_BAS_MAX_OUT_CHNL_NUM];
	MediaAPI::TBasEncParam tEncParam;
	byNum = 0;
	for (u8 byIndex = 0; byIndex < AUD_BAS_MAX_OUT_CHNL_NUM; ++byIndex)
	{
		if (tParam.m_atAudEnc[byIndex].m_emFormat == emTPAEnd)
		{
			continue;
		}
		byType = CTpTypeAdpt::GetAudPayloadValue(tParam.m_atAudEnc[byIndex].m_emFormat);
		tAudStream.SetAudType(byType);
		tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
		tAudStream.SetTrackNum(1); // 单声道写死 1
		tAudStream.SetRealPayload(byType);
		tAudStream.SetActivPayload(byType);
		tEncParam.SetBasAudEncCap(tAudStream);
		tEncParam.SetEncryptParam(tEncrtpt); //编码加密参数
		atEnc[byIndex].SetChnParam(tEncParam);
		atEnc[byIndex].SetChnId(byIndex);
		byNum++;
	}
	MediaAPI::CBasMgr::SetEncChnParam(dwAudHandle, byNum, atEnc);

	MediaAPI::TBasDecParam tDecParam;
	MediaAPI::TAudDecParam tAudDec;
	MediaAPI::TMediaPayload tLoad;
	byType = CTpTypeAdpt::GetAudPayloadValue(tParam.m_tAudDec.m_emFormat);
	tLoad.SetRealPayload(byType);
	tLoad.SetActivPayload(byType);
	tAudDec.SetAudType(byType);
	tAudDec.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
	tAudDec.SetTrackNum(1); // 单声道写死 1
	tAudDec.SetMediaPayload(tLoad);
	tAudDec.SetEncryptParam(tEncrtpt); //解码加密参数
	tDecParam.SetBasAudDecParam(tAudDec);
	MediaAPI::CBasMgr::SetDecParam(dwAudHandle, tDecParam);
// 	MediaAPI::CBasMgr::SetAudioResend();
	BOOL32 bRes = MediaAPI::CBasMgr::Start(dwAudHandle);
	if (bRes)
	{
		g_mapBas.insert(std::make_pair(dwAudHandle, dwEqpID));
	}
	return bRes;
}

BOOL32 MediaSetAudBasDecAddr(IN HMEDIARES dwBasHandle, IN TTPTransAddr tInAddr)
{
	MediaAPI::TAddrs tAddr;
	tAddr.SetIpAddr(ntohl(tInAddr.m_dwIP));
	tAddr.SetPort(tInAddr.m_wPort);
	return MediaAPI::CBasMgr::SetSrcRtcpRcvAddrs(dwBasHandle, tAddr);
}

BOOL32 MediaSetAudBasEncAddr(IN HMEDIARES dwBasHandle, IN u32 dwChnId, IN TTPTransAddr tInAddr)
{
	MediaAPI::TAddrs tAddr;
	tAddr.SetIpAddr(ntohl(tInAddr.m_dwIP));
	tAddr.SetPort(tInAddr.m_wPort);
	return MediaAPI::CBasMgr::SetDstRtpRcvAddrs(dwBasHandle, dwChnId, tAddr);
}

BOOL32 MediaGetAudBasDecAddr(IN HMEDIARES dwBasHandle, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (MediaAPI::CBasMgr::GetLocalRtpRcvAddrs(dwBasHandle, tAddr))
	{
		tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
		tOutAddr.m_wPort = tAddr.GetPort();
		return TRUE;
	}
	return FALSE;
}

BOOL32 MediaGetAudBasEncAddr(IN HMEDIARES dwBasHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr)
{
	MediaAPI::TAddrs tAddr;
	if (MediaAPI::CBasMgr::GetLocalRtcpRcvAddrs(dwBasHandle, dwChnId, tAddr))
	{
		tOutAddr.m_dwIP = htonl(tAddr.GetIpAddr());
		tOutAddr.m_wPort = tAddr.GetPort();
		return TRUE;
	}
	return FALSE;
}

void MediaSetAudBasParam(IN HMEDIARES dwBasHandle, IN TXmpuChgAudParam tParam)
{
	TUmsAudFormat* ptFormat = NULL;
	tpLowHint(Ums_Mdl_Xmpu, "MediaSetAudBasParam dwEqpID:%d, emModle:%d, Key:%s\n",
		tParam.m_dwEqpID,
		tParam.m_tEncrypt.m_emEncryptModel, tParam.m_tEncrypt.m_achEncKey);

	ptFormat = &tParam.m_tAudDec;
	tpLowHint(Ums_Mdl_Xmpu, "MediaSetAudBasParam  DecParam:%d, Freq:%d, ChnCfg:%d\n",
		ptFormat->m_emFormat, ptFormat->m_emSampleFreq, ptFormat->m_emChnlCfg);


	tpLowHint(Ums_Mdl_Xmpu, "MediaSetAudBasParam  EncParam:(%d|%d|%d)\n",
		tParam.m_aemEncFormat[0], tParam.m_aemEncFormat[1],
		tParam.m_aemEncFormat[2]);

	MediaAPI::TBasEncChnParam atEncParam[AUD_BAS_MAX_OUT_CHNL_NUM];
	MediaAPI::TMediaAudStreamCap tAudStream;
	MediaAPI::TBasEncParam tEncParam;
	MediaAPI::TMediaEncryptParam tEncrtpt;

	u8 byEncType = ENCRYPT_NONE;
	byEncType = ConvertEncKeyModeFromUmsToXmpu(tParam.m_tEncrypt.m_emEncryptModel);
	tEncrtpt.SetEncryptMode(byEncType);
	tEncrtpt.SetEncryptKey(tParam.m_tEncrypt.m_byKeyLen, 
		(u8*)tParam.m_tEncrypt.m_achEncKey);

	u8 byType = 0 ;
	MediaAPI::TBasDecParam tDecParam;
	MediaAPI::TAudDecParam tAudDec;
	MediaAPI::TMediaPayload tLoad;
	byType = CTpTypeAdpt::GetAudPayloadValue(tParam.m_tAudDec.m_emFormat);
	tLoad.SetRealPayload(byType);
	tLoad.SetActivPayload(byType);
	tAudDec.SetAudType(byType);
	tAudDec.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
	tAudDec.SetTrackNum(1); // 单声道写死 1
	tAudDec.SetMediaPayload(tLoad);
	tAudDec.SetEncryptParam(tEncrtpt); //解码加密参数
	tDecParam.SetBasAudDecParam(tAudDec);
	MediaAPI::CBasMgr::SetDecParam(dwBasHandle, tDecParam);
	u8 byNum = 0;
	for (u8 byIndex = 0; byIndex < AUD_BAS_MAX_OUT_CHNL_NUM; ++byIndex)
	{
		if (tParam.m_aemEncFormat[byIndex] == emTPAEnd)
		{
			continue;
		}
		byType = CTpTypeAdpt::GetAudPayloadValue(tParam.m_aemEncFormat[byIndex]);
		tAudStream.SetAudType(byType);
		tAudStream.SetSampleRate(7);//AAC_SAMPLE_FRQ_32
		tAudStream.SetTrackNum(1); // 单声道写死 1
		tAudStream.SetRealPayload(byType);
		tAudStream.SetActivPayload(byType);
		tEncParam.SetBasAudEncCap(tAudStream);
		tEncParam.SetEncryptParam(tEncrtpt);   //编码加密参数
		atEncParam[byIndex].SetChnParam(tEncParam);
		atEncParam[byIndex].SetChnId(byIndex);
		byNum++;
	}
	
	MediaAPI::CBasMgr::SetEncChnParam(dwBasHandle, byNum, atEncParam);
}

void MediaAudBasSetSynId( IN u32 dwSynID,  IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE164 )
{
		MediaAPI::TAudioSynDecChn atAudSynChn[TP_MAX_STREAMNUM];
		for (u16 wIndex = 0; wIndex < byNum; ++wIndex)
		{
			atAudSynChn[wIndex].SetHMediares(ptSynChn[wIndex].m_dwHandle);
			atAudSynChn[wIndex].SetDecChn(0);
			atAudSynChn[wIndex].SetE164(pchE164);
		}
		MediaAPI::CBasMgr::SetSynId (dwSynID, byNum, atAudSynChn);
}

void MediaAudBasFreeSynId(  IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE164 )
{
	MediaAPI::TAudioSynDecChn atAudSynChn[TP_MAX_STREAMNUM];
	for (u16 wIndex = 0; wIndex < byNum; ++wIndex)
	{
		atAudSynChn[wIndex].SetHMediares(ptSynChn[wIndex].m_dwHandle);
		atAudSynChn[wIndex].SetDecChn(0);
		atAudSynChn[wIndex].SetE164(pchE164);
	}
	MediaAPI::CBasMgr::ClearSynId(byNum, atAudSynChn);
}

void ShowVmpMap()
{
	msgprintnotime("Xmpu Vmp Map -----------------------------------------------------------------------------\n");
	std::map<u32, u32>::iterator it = g_mapVmp.begin();
	while(it != g_mapVmp.end())
	{
		msgprintnotime("Xmpu Vmp Map Handle:(%u  0x%x), EqpID:%d\n",it->first, it->first, it->second);
		++it ;
	}
	msgprintnotime("\n");
}

void ShowBasMap()
{
	msgprintnotime("Xmpu Bas Map -----------------------------------------------------------------------------\n");
	std::map<u32, u32>::iterator it = g_mapBas.begin();
	while (it != g_mapBas.end())
	{
		msgprintnotime("Xmpu Bas Map Handle:(%u  0x%x), EqpID:%d\n",it->first, it->first, it->second);
		++it  ;
	}
	msgprintnotime("\n");
}

void ShowMixMap()
{
	msgprintnotime("Xmpu Mix Map -----------------------------------------------------------------------------\n");
	std::map<u32, u32>::iterator it = g_mapMix.begin();
	while (it != g_mapMix.end())
	{
		msgprintnotime("Xmpu Mix Map Handle:(%u 0x%x), EqpID:%d\n",it->first, it->first, it->second);
		++it;
	}
	msgprintnotime("\n");
}