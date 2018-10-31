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
		
	//���������е�netbuf
	static void CreateNetBuf(CUmsConfInst* pInst);
	static void DestoryNetBuf(CUmsConfInst* pInst);

//��ʱû�� ��������ϯ
	static u16 CreateChairToVirChair(CUmsConfInst* pInst, TCapNode* ptChair);

/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//���ⷢ���˽���
	//�����Ի᳡����ת�����ⷢ�Ի᳡
	static u16 CreateSpeakerToVirSpeaker(CUmsConfInst* pInst);


	static u16 GetSpeakerToVirSpeaker(BOOL32 bIsCreate, CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);
	static u16 GetNonSpeakerToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs); // �����˲����ߵ�ʱ�򣬹㲥�ϳɵ�����Ҳ��Ҫ��virSpeaker

	//����������ϯ�������Ľ���
	static void CreateVirChairToBas(CUmsConfInst* pInst);
	//�������ⷢ���˵������Ľ���
	static void CreateVirSpeakerToBas(CUmsConfInst* pInst);
	//���ⷢ���˵�netbuf����
	static u16 CreateVirSpeakerTrans(CUmsConfInst* pInst);

	static void CreateMediaToSingleMixer( CUmsConfInst* pInst );

//////////////////////////////////////////////////////////////////////////
//ƽ��
	//������ƽ��
	static BOOL32 CreateSpeakerToVirSpeakerForIframeCheck(CUmsConfInst* pInst, TCallNode* ptCurSpeaker, TCallNode* ptNewSpeaker, u16 wChanIndex);
	static u16 DestroySpeakerToVirSpeakerForIframeCheck(CUmsConfInst* pInst, u16 wChanIndex);
	static BOOL32 CreateSpeakerToSingleVirSpeakerForIframeCheck(CUmsConfInst* pInst, TCallNode* ptCurSpeaker, u16 wCurIndex, TCallNode* ptNewSpeaker, u16 wNewIndex);
	static u16 DestroySpeakerToSingleVirSpeakerForIframeCheck(CUmsConfInst* pInst);

	//��ѯƽ��
	static BOOL32 CreatePollForIframeCheck(CUmsConfInst* pInst, TTPTransAddr* ptCurAddr, TTPTransAddr* ptOldAddr, u16 wChanIndex, u16 wNewPollID);
	static BOOL32 DestroyPollForIframeCheck(CUmsConfInst* pInst, TTPTransAddr* ptCurAddr, TTPTransAddr* ptOldAddr);

//�ϳɰ�
	static void CreatVidToSingleVmpTp(CUmsConfInst* pInst);
	//�������ϳɰ�Ľ���
	static void CreateMeidaToVmp(CUmsConfInst* pInst, TCapNode* ptFarterNode, TCallNode* ptNode);


//////////////////////////////////////////////////////////////////////////
//��ѯ

	//B4����ѯ
	static void	AdjustPollTransToUms(CUmsConfInst* pInst);

//////////////////////////////////////////////////////////////////////////
//˫��
	static void CreateDualFromDownToUp(CUmsConfInst* pInst);
	static void DestroyDualFromDownToUp(CUmsConfInst* pInst);
	static u16 FindDualFromDownToUp(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);

	static void AjustDualFromNodeToUms(CUmsConfInst* pInst);
	static void DestroyDualFromNodeToUms(CUmsConfInst* pInst);
	static u16 FindDualFromNodeToUms(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);



//////////////////////////////////////////////////////////////////////////
//����ǽ
	static u16 CreateTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo);
	static u16 DestroyTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo);
	static u16 FindTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo, TUmsDsData atDsData[], u16 wMaxDs);

//////////////////////////////////////////////////////////////////////////
// B4��������

	// ����Ŀ��
	static u16 AdjustSingleDiscussObjToMix(CUmsConfInst* pInst, BOOL32 bIsAddDualAud);
	static u16 AdjustSingleDiscussObjToVmpTp(CUmsConfInst* pInst, TDiscussScreenInfo* ptDstInfo);

	// ����Ŀ������ⷢ����
	static u16 GetDiscussObjToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);  // vmp and N Mix to virspeaker
	static u16 GetDisCussObjToVirSpeakerForDown(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);

	// For ALL ����������Ŀ��
	static u16 AdjustDiscussObjToVmpTp(CUmsConfInst* pInst, TDiscussVmpTpRes* pVmpTpRes, TDiscussScreenInfo* ptDstInfo);  // ����Ŀ�겻����
	static u16 AdjustDiscussObjToMix(CUmsConfInst* pInst, TDiscussMixRes* pMixRes, TAudMixMemberInfo* ptMemberInfo); // ����Ŀ�겻����

	static u16 PutAudDownToDiscussEp(CUmsConfInst* pInst, TCallNode* ptNode, TDiscussEpAudInfo* ptEpAudInfo);   //  ���¼��Ƿ������ۻ᳡����Ƶ����
	static u16 AdjustDiscussEpToBas(CUmsConfInst* pInst, TDiscussEpInfo* pEpInfo);  // ��С�����᳡����bas

	static u16 CreatPutAudRtpToDown(CUmsConfInst* pInst, TPutAudChnl* ptAudChnl);
	static u16 CreatPutAudBackRtpToUp(CUmsConfInst* pInst, TPutAudChnl* ptAudChnl);

//////////////////////////////////////////////////////////////////////////

	//����������ת����
	static u16 AdjustBasDsEqpToConfDsEqp(CUmsConfInst* pInst);
	static u16 FindBasDsEqpToConfDsEqp(CUmsConfInst* pInst, 
				TBasChnInfo& tChnInfo, u16 wOutChanNum, TUmsDsData atDsData[], BOOL32 bIsBrd = FALSE);

	//�᳡���ϳɵĽ���
	static u16 CreateAllMemberToBrdVmp(CUmsConfInst* pInst, TBrdVmpRes* ptVmpRes);

/////////////////////////////////B5////////////////////////////////////////
// B5 ����

    static u16 GetRollCallObjToVirSpeakerForDown(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);  

	//��������ߣ��������� ���¼������´�N-1��Ƶ
	static u16 GetRollCallObjToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs);  // vmp and N Mix to virspeaker

	static u16 PutAudDownToRollCallEp(CUmsConfInst* pInst,  TCallNode* ptNode);   //  ���¼��Ƿ������ۻ᳡����Ƶ����

	static u16 AdjustRollCallObjToMix(CUmsConfInst* pInst, TRollCallMixRes* ptRollCallMixRes, TAudMixMemberInfo* ptMemberInfo);

	static void AdjustRollCallerToBas(CUmsConfInst* pInst);
    static u16 AdjustRollCallerToVirRollCaller(CUmsConfInst* pInst, u16 wCallEpId);
	static void CreateRollCallEpToVmp(CUmsConfInst* pInst, TCapNode* ptFarterNode, TCallNode* ptNode);


    static void CreateRollCallMediaToDulMixer( CUmsConfInst* pInst );

/////////////////////////////////B5////////////////////////////////////////
// B5 �������
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
//����
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

