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
	s8       m_achConfName[TP_MAX_ALIAS_LEN+1];	//��������
	s8       m_achConfE164[TP_MAX_ALIAS_LEN+1];	//����e164
	time_t   m_tEndConfTime;                     //��������ʱ��
	BOOL32	 m_bCallByTimer;	//�Ƿ���ԤԼ����

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
		m_tEndConfTime = CurTime;    //�Ҷϻ���ʱ
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
	//��ȡ���ڿ��������
	u32		GetRunningConf();
	void UpdateRunningConfCount();
protected:
	//���е���
	void EventCallIncoming(u8* pDataBuf, u16 wDataSize);
	void EventCallCreateMeeting(u8* pDataBuf, u16 wDataSize);
	void EventStartConfTemplateFailed(u8* pDataBuf, u16 wDataSize);
	void EventUpdateConfTurnList(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventHungUpConfResult(CTpMsg *const ptMsg);
	void EventDelConfNotify(CTpMsg *const ptMsg);
	void EventAuxMixInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventCallEpResult(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ����᳡�Ļ�Ӧ
	void EventApplySpeakerResult(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ָ�������˵Ļ�Ӧ
	void EventStartDualInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ����˫���Ļ�Ӧ
	void EventChairConfInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventUpdateConfCnsListNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventFeccVidListNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventAddConfListNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventDualEpNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventSpeakerChangeNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
	void EventMuteEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ������Ӧ
	void EventQuietEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ������Ӧ

	void EventAllEpQuietMuteStatusNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);//֪ͨ����ȫ�־�������״̬
	void EventAudMixStatNotify( u16 wEvent, u8* pData, u16 wDataSize );
	void EventHungUpConfReasonToUI(u16 wEvent, u8* pData, u16 wDataSize);
	void EventStartConfRet(u8* pDataBuf, u16 wDataSize);
	void EventCommReasonUIInd(u16 wEvent, u8* pData, u16 wDataSize);

	// add by gaoyong
	void EventDropEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // �Ҷ�һ���᳡�Ļ�Ӧ
	void EventCallExistEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ����һ���᳡�Ļ�Ӧ
	void EventStopDualInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ֹͣ˫���Ļ�Ӧ
	void EventSetTurnListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); //
	void EventOprDiscussEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // 
	void EventUptateDiscussInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ���۲����Ļ�Ӧ
	void EventStartPollInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ����ѯ�Ļ�Ӧ
	void EventSuspendPollInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ����ѯ�Ļ�Ӧ
	void EventStopPollInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ����ѯ�Ļ�Ӧ
	void EventViewObjInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ѡ���᳡�Ļ�Ӧ
	void EventUnViewObjInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // ȡ��ѡ���Ļ�Ӧ

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

	//��UI��������Ϣ
	void EventLogin(CTpMsg *const ptMsg);
	void EventStartConfReq(CTpMsg *const ptMsg);
	void EventStartMeetingReq(CTpMsg *const ptMsg);
	void EventHungUpConf(CTpMsg *const ptMsg);
	void EventCallEp(CTpMsg *const ptMsg);   // ����һ���᳡
	void EventCallExistEp(CTpMsg *const ptMsg);  // ����һ���᳡
	void EventDropEp(CTpMsg *const ptMsg);   // �Ҷ�һ���᳡
/*	void EventDeleteEp(CTpMsg *const ptMsg);*/
	void EventChangeSpeaker(CTpMsg* const ptMsg);  // ָ��������
	void EventMuteEp(CTpMsg* const ptMsg);   // ����
	void EventQuietEp(CTpMsg* const ptMsg); // ����
	void EventSetTurnList(CTpMsg* const ptMsg);  // umc������ѯ�б�
	void EventOprDiscussEpCmd(CTpMsg* const ptMsg);  // 
	void EventUptateDiscussCmd(CTpMsg* const ptMsg); // 
	void EventStartDual(CTpMsg* const ptMsg);  // ����˫��
	void EventStopDual(CTpMsg* const ptMsg);  // �ر�˫��

	void EventAudMixVacCmd(CTpMsg* const ptMsg);
	void EventFeccCameraReq(CTpMsg *const ptMsg);
	void EventFeccPrePosReq(CTpMsg *const ptMsg);
	void EventFeccSelVidReq(CTpMsg *const ptMsg);

	// add by gaoyong
	void EventStartPoll(CTpMsg* const ptMsg);   // ����ѯ
	void EventStopPoll(CTpMsg* const ptMsg);   // ����ѯ
	void EventSupendPoll(CTpMsg* const ptMsg);

	void EventViewObj(CTpMsg* const ptMsg);  // ѡ���᳡
	void EventUnViewObj(CTpMsg* const ptMsg);  // ȡ��ѡ��
	
	void EventSelViewReq(CTpMsg* const ptMsg);  //����ѡ��
	void EventRervesBrdVmpReq(CTpMsg* const ptMsg);  //ռ�úϳ�
	void EventSetBrdVmpReq(CTpMsg* const ptMsg);  //���úϳ�
	void EventBrdVmpReq(CTpMsg* const ptMsg);  //�����㲥
	void EventSaveBrdVmpCfg( CTpMsg *const ptMsg );//����ϳ�����
	void EventUmsJoinConfAck( CTpMsg *const ptMsg);


	//����
	void EventUptateRollCallCmd(CTpMsg* const ptMsg);
	void EventUptateRollCallInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // �����Ļ�Ӧ
	void EventUptateRollCallNextEpCmd(CTpMsg* const ptMsg);
	void EventUptateRollCallNextEpInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // �����Ļ�Ӧ
    void EventUptateRollCallListCmd(CTpMsg* const ptMsg);
	void EventUptateRollCallListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize); // �����Ļ�Ӧ
    void EventRollCallPresentStateCmd(CTpMsg* const ptMsg);
    void EventRollCallPresentStateNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);
    void EventRollCallInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize);


	// �������
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

	// �����������ϳ�evtp_GetConfVmpVidAskKey_cmd
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
	
//	��ʱ���鴦��
	void GetValue(TConfTemplateLocal&tRes,const TTPConfMeet&tRhs);


	//������ʱ������
	void EventUpdateTempConfName(CTpMsg* const ptMsg);

protected:

	TCallMgr m_atCall[TP_UMS_MAX_CONFNUM+1];
	
private:
};




#endif // _h_handlecallservice_h__