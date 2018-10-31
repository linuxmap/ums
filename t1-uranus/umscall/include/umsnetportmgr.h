#ifndef _h_umsnetportmgr_h__
#define _h_umsnetportmgr_h__
#include "umsobject.h"
#include "callinnerstruct.h"
#include "tphandle.h"
#include "umsinnerrecstruct.h"
#include "umsdiscussnew.h"
#include "umsvmp.h"
#include "tvwallmgr.h"
#include "umsrollcall.h"
#include "umsaudmix.h"

#define IFRAME_CHECK_TIMEOUT	4

class TCapNode;
class CUmsConfInst;
struct tagTVidChan;
struct tagTPollAddr;
class CNetPortMgr
{
public:
	CNetPortMgr();
	~CNetPortMgr();
	
	static BOOL32 CreateMediaTrans(CUmsConfInst* pInst, TUmsDsData* ptDs, u16 wDsNum);
	static BOOL32 DestroyMediaTrans(CUmsConfInst* pInst, TUmsDsData* ptDs, u16 wDsNum);
		
	//创建会议中的netbuf
	static void CreateNetBuf(CUmsConfInst* pInst);
	static void DestoryNetBuf(CUmsConfInst* pInst);

//暂时没用 到虚拟主席
	static u16 CreateChairToVirChair(CUmsConfInst* pInst, TCapNode* ptChair);

/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//虚拟发言人交换
	//将发言会场码流转到虚拟发言会场
	static u16 CreateSpeakerToVirSpeaker(CUmsConfInst* pInst);


	static u16 GetSpeakerToVirSpeaker(BOOL32 bIsCreate, CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);
	static u16 GetNonSpeakerToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs); // 发言人不在线的时候，广播合成的码流也需要进virSpeaker

	//创建虚拟主席到适配板的交换
	static void CreateVirChairToBas(CUmsConfInst* pInst);
	//创建虚拟发言人到适配板的交换
	static void CreateVirSpeakerToBas(CUmsConfInst* pInst);
	//虚拟发言人到netbuf交换
	static u16 CreateVirSpeakerTrans(CUmsConfInst* pInst);

	static void CreateMediaToSingleMixer( CUmsConfInst* pInst );

//////////////////////////////////////////////////////////////////////////
//平滑
	//发言人平滑
	static BOOL32 CreateSpeakerToVirSpeakerForIframeCheck(CUmsConfInst* pInst, TCallNode* ptCurSpeaker, TCallNode* ptNewSpeaker, u16 wChanIndex);
	static u16 DestroySpeakerToVirSpeakerForIframeCheck(CUmsConfInst* pInst, u16 wChanIndex);
	static BOOL32 CreateSpeakerToSingleVirSpeakerForIframeCheck(CUmsConfInst* pInst, TCallNode* ptCurSpeaker, u16 wCurIndex, TCallNode* ptNewSpeaker, u16 wNewIndex);
	static u16 DestroySpeakerToSingleVirSpeakerForIframeCheck(CUmsConfInst* pInst);

	//轮询平滑
	static BOOL32 CreatePollForIframeCheck(CUmsConfInst* pInst, TTPTransAddr* ptCurAddr, TTPTransAddr* ptOldAddr, u16 wChanIndex, u16 wNewPollID);
	static BOOL32 DestroyPollForIframeCheck(CUmsConfInst* pInst, TTPTransAddr* ptCurAddr, TTPTransAddr* ptOldAddr);

//合成板
	static void CreatVidToSingleVmpTp(CUmsConfInst* pInst);
	//创建到合成板的交换
	static void CreateMeidaToVmp(CUmsConfInst* pInst, TCapNode* ptFarterNode, TCallNode* ptNode);


//////////////////////////////////////////////////////////////////////////
//轮询

	//B4用轮询
	static void	AdjustPollTransToUms(CUmsConfInst* pInst);

//////////////////////////////////////////////////////////////////////////
//双流
	static void CreateDualFromDownToUp(CUmsConfInst* pInst);
	static void DestroyDualFromDownToUp(CUmsConfInst* pInst);
	static u16 FindDualFromDownToUp(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);

	static void AjustDualFromNodeToUms(CUmsConfInst* pInst);
	static void DestroyDualFromNodeToUms(CUmsConfInst* pInst);
	static u16 FindDualFromNodeToUms(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);



//////////////////////////////////////////////////////////////////////////
//电视墙
	static u16 CreateTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo);
	static u16 DestroyTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo);
	static u16 FindTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo, TUmsDsData atDsData[], u16 wMaxDs);

//////////////////////////////////////////////////////////////////////////
// B4会议讨论

	// 单屏目标
	static u16 AdjustSingleDiscussObjToMix(CUmsConfInst* pInst, BOOL32 bIsAddDualAud);
	static u16 AdjustSingleDiscussObjToVmpTp(CUmsConfInst* pInst, TDiscussScreenInfo* ptDstInfo);

	// 讨论目标进虚拟发言人
	static u16 GetDiscussObjToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);  // vmp and N Mix to virspeaker
	static u16 GetDisCussObjToVirSpeakerForDown(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);

	// For ALL 不包括单屏目标
	static u16 AdjustDiscussObjToVmpTp(CUmsConfInst* pInst, TDiscussVmpTpRes* pVmpTpRes, TDiscussScreenInfo* ptDstInfo);  // 单屏目标不适用
	static u16 AdjustDiscussObjToMix(CUmsConfInst* pInst, TDiscussMixRes* pMixRes, TAudMixMemberInfo* ptMemberInfo); // 单屏目标不适用

	static u16 PutAudDownToDiscussEp(CUmsConfInst* pInst, TCallNode* ptNode, TDiscussEpAudInfo* ptEpAudInfo);   //  到下级非发言讨论会场的音频码流
	static u16 AdjustDiscussEpToBas(CUmsConfInst* pInst, TDiscussEpInfo* pEpInfo);  // 无小码流会场，进bas

	static u16 CreatPutAudRtpToDown(CUmsConfInst* pInst, TPutAudChnl* ptAudChnl);
	static u16 CreatPutAudBackRtpToUp(CUmsConfInst* pInst, TPutAudChnl* ptAudChnl);

//////////////////////////////////////////////////////////////////////////

	//适配板向会议转发板
	static u16 AdjustBasDsEqpToConfDsEqp(CUmsConfInst* pInst);
	static u16 FindBasDsEqpToConfDsEqp(CUmsConfInst* pInst, 
				TBasChnInfo& tChnInfo, u16 wOutChanNum, TUmsDsData atDsData[], BOOL32 bIsBrd = FALSE);

	//会场进合成的交换
	static u16 CreateAllMemberToBrdVmp(CUmsConfInst* pInst, TBrdVmpRes* ptVmpRes);

/////////////////////////////////B5////////////////////////////////////////
// B5 点名

    static u16 GetRollCallObjToVirSpeakerForDown(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);  

	//如果点名者，被点名者 在下级，向下打N-1音频
	static u16 GetRollCallObjToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);  // vmp and N Mix to virspeaker

	static u16 PutAudDownToRollCallEp(CUmsConfInst* pInst,  TCallNode* ptNode);   //  到下级非发言讨论会场的音频码流

	static u16 AdjustRollCallObjToMix(CUmsConfInst* pInst, TRollCallMixRes* ptRollCallMixRes, TAudMixMemberInfo* ptMemberInfo);

	static void AdjustRollCallerToBas(CUmsConfInst* pInst);
    static u16 AdjustRollCallerToVirRollCaller(CUmsConfInst* pInst, u16 wCallEpId);
	static void CreateRollCallEpToVmp(CUmsConfInst* pInst, TCapNode* ptFarterNode, TCallNode* ptNode);


    static void CreateRollCallMediaToDulMixer( CUmsConfInst* pInst );

/////////////////////////////////B5////////////////////////////////////////
// B5 会议混音
	static u16 AdjustEpAudToMixDs(CUmsConfInst* pInst, TUmsAudMixEqp* pMixRes, TAudMixMemberInfo* ptMemberInfo);
	static u16 PutMixAudToLowUmsEp(CUmsConfInst* pInst, TUmsAudMixEpInfo* ptInfo);


	static u16 AdjustConfMixToDulMixer(CUmsConfInst* pInst, TAudMixMemberInfo* ptMemberInfo);

//////////////////////////////////////////////////////////////////////////

	static u16 AdjustConfVidAudToTarget(CUmsConfInst* pInst, CDsListInfo& DsInfo, const TUmsGetConfBrdVidAudInfo& tVidAudmsgInfo);
	
//////////////////////////////////////////////////////////////////////////
	static u16 AdjustConfVmpVidToTarget(CUmsConfInst* pInst, CDsListInfo& DsInfo, TTPDsFrom& tVmp, TUmsGetVmpVidInfo& tInfo );
//////////////////////////////////////////////////////////////////////////
	static u16 AdjustEpScreenStreamToTarget(CUmsConfInst* pInst, CDsListInfo& cDsInfo, TGetEpScreenInfo& tInfo, TGetVidAddr& tAddr, BOOL32 bAudMix);
///////////////////////////////////////////////////////////////////////
//其他
	static u16 CreateMediaForVRS2S(CUmsConfInst* pInst, TCapNode* ptVRS, TCapNode* ptNodeSrc);
	static u16 DestroyUmsToNode(CUmsConfInst* pInst, TCapNode* ptRmt);
	static void FreeMediaTrans(CUmsConfInst* pInst, CDsListInfo& tListInfo);

	// Xmpu Mix
	static u16 AdjustXmpuMiddleAddrToMix(CUmsConfInst* pInst, TAudMixInfo* ptMixInfo); 

	static u16 AdjustXmpuMiddleAddrToMpu2(CUmsConfInst* pInst, CServiceInfo* pcService); 
	static u16 AdjustXmpuMiddleAddrToVmp(CUmsConfInst* pInst, TBrdVmpRes* ptVmp); 

	//vid aud xmpu bas
#ifdef _USE_XMPUEQP_
	static u16 AdjustXmpuMiddleAddrToVidBas(CUmsConfInst* pInst, tXmpuVidBasRes* pVidBasInfo); 
	static u16 AdjustXmpuMiddleAddrToAudBas(CUmsConfInst* pInst, tXmpuAuddBasRes* pAudBasInfo); 
#endif


//protected:

	static void MergerDsList(CUmsConfInst* pInst, CDsListInfo& cDsList, TUmsDsData aNewDsData[MAX_CHANNEL_DS_NUM], u16 wDsNumm, s8* pszDstDes);

};




BOOL32 InitMediaTransLib();
void QuitMediaTransLib();




void MediaCreateNetBuf(CUmsConfInst* pInst, TUmsNetBuf& tNetPara);
void MediaDestroyNetBuf(CUmsConfInst* pInst, TUmsNetBuf& tNetPara);


#endif // _h_umsnetportmgr_h__

