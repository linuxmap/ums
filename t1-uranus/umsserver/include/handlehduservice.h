#ifndef _handlehduservice_h__
#define _handlehduservice_h__

#include "tphandle.h"
#include "tpstruct.h"
#include "umsinnerstruct.h"
#include "umshdu.h"


//�������ǽ�����Ϣ
class CUmsHduHandleService : public CTpHandler
{
public:
	CUmsHduHandleService(CTpObject* pcObjec);
	~CUmsHduHandleService();
	
public:
	virtual BOOL32	Handler(CTpMsg *const ptMsg);
	void			ShowHdu();
	void			ShowHduStyle();

	//��ȡ����ǽ��ʹ����Ϣ
	void			GetHduUesInfo(TTPBrdUsedInfo& tUseInfo);

private:
	//�޸�HDU
	void			EventHduBrdModify(u8* pData, u16 wDataSize);
	//���HDU
	void			EventHduBrdAdd(u8* pData, u16 wDataSize);
	//����HDU
	void			EventHduUpdate(u8* pData, u16 wDataSize);
	//�������
	void			EventHduUpdateNty(u8* pData, u16 wDataSize);
	//����
	void			EventHduReboot(u8* pData, u16 wDataSize);
	//�޸�ͨ��
	void			EventHduChanModify(u8* pData, u16 wDataSize);
	//ɾ��ͨ������
	void			EventHduDelChan(u8* pData, u16 wDataSize);
	//ɾ��HDU
	void			EventHduDel(u8* pData, u16 wDataSize);
	//��ӵ���ǽ���
	void			EventHduStyleAdd(u8* pData, u16 wDataSize);
	//ɾ������ǽ���
	void			EventHduStyleDel(u8* pData, u16 wDataSize);
	//���µ���ǽ���
	void			EventHduStyleUpdate(u8* pData, u16 wDataSize);
	//�û���¼
	void			EventHduUserLogin(u8* pData, u16 wDataSize);
	
	//���󲥷�
	void			EventHduPlayReq(u8* pData, u16 wDataSize);
	void			EventHduPlayAckFromCall(u8* pData, u16 wDataSize);
	void			EventHduDelMonitorFromCall(u8* pData, u16 wDataSize);
	void			EventHduPlayAckFromEqp(u8* pData, u16 wDataSize);
	void			EventHduPlayNackFromEqp(u8* pData, u16 wDataSize);
	//ֹͣ����
	void			EventHduStopPlay(u8* pData, u16 wDataSize);
	void			EventHduAllStopPlay(u8* pData, u16 wDataSize);
	void			EventHduStopAckFromEqp(u8* pData, u16 wDataSize);
	void			EventHduStopNackFromEqp(u8* pData, u16 wDataSize);
	
	void			EventBrdRegRes(u8* pData, u16 wDataSize);   // hdu�忨ע��
	void			EventServiceRegRes(u8* pData, u16 wDataSize); // ����ǽͨ��ע��	
	void			EventUpdateChanStatus(u8* pData, u16 wDataSize);  // ����ǽͨ��״̬����
	void			EventUpdateStatus(u8* pData, u16 wDataSize);  // ֻ֪ͨ��serverδ����
	
	// hdu����ؼ�֡
	void			EventReqIFrame(u8* pData, u16 wDataSize);
	
	void			EventHungUpHdu(u8* pData, u16 wDataSize); // �Ҷϻ᳡����
	void			EventHungUpConfHdu(u8* pData, u16 wDataSize); // ��ᴦ��
	
	// �޸�����
	void			EventSetVolInfo(u8* pData, u16 wDataSize);
	void			EventSetVolRes(u8* pData, u16 wDataSize);
	
	// �޸�hduͨ��ģʽ��vmpģʽ����ͨģʽ��
	void            EventChangeChanModeReq(u8* pData, u16 wDataSize);
	void            EventChangeChanModeRsp(u8* pData, u16 wDataSize);

	////////////////////////////////////////
	//// �����ն˲�������ǽ���
	
	// �������ǽĳ��ͨ��
	void			EventFromCnsHduPlayReq(u8* pData, u16 wDataSize);
	
	// ֹͣ����ĳ��ͨ��
	void			EventFromCnsHduStopPlay(u8* pData, u16 wDataSize);

	// ֹͣ��������ͨ��
	void			EventFromCnsHduAllStopPlay(u8* pData, u16 wDataSize);

	// �޸�����
	void			EventFromCnsSetVolInfo(u8* pData, u16 wDataSize);

	// �޸�ͨ��ģʽ
	void            EventFromCnsChangeChanModeReq(u8* pData, u16 wDataSize);
	
	// ���µ���ǽ��Ϣ��CNS
	void			SendToCnsHduPlanInfo(u16 wConfID = 0, u16 wEpID = 0);

	void			EventMediaKeyNty(u8* pData, u16 wDataSize);
private:
	//��ȡHDU ��Ϣ
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

	// ��ȡ���еĵ���ǽ��Ϣ
	void            GetALLHduPalnInfo(THduPlanData& tData);

	// ���󲥷ŵ���ǽ����У��
	void            HduPlayReqStateFromUmcCns(TTPHduPlayReq& tReq, EmTpHduPlayNackReason& emReason);

	// ����ֹͣ���ŵ���ǽĳ��ͨ������У��
	void            HduStopReqStateFromUmcCns(TTPHduPlayReq& tReq, BOOL32& bRes);
	
	// ����ֹͣ���ŵ���ǽ����ͨ������У��
	void            HduStopAllReqStateFromUmcCns(u8* pData, u16 wDataSize);

	// ����ǽ����������Ϣ����У��
	void            HduSetVolReqStateFromUmcCns( THduPlayUnit* ptInfo, EmTpHduSetVolRes& emRes);

	// �޸ĵ���ǽͨ��״̬����У��
	void            HduChangeChanModeStateFromUmcCns(THduChanModeSetInfo& tInfo, EmTpHduChangeChanModeRes& emRes);


private:
	CHduEx		m_acHdu[HDU_MAX_NUM];
	CHduPlan	m_cHduPlanEx;
};

#endif