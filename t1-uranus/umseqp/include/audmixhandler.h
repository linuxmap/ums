#ifndef __audmixer_handler_h_
#define __audmixer_handler_h_

#include "servicehandler.h"
#include "umsinnertype.h"

//apu2 �������� ����
class CAudMixHandler : public IServiceHandler
{
public:
	CAudMixHandler();
	~CAudMixHandler();

public:
	virtual BOOL32		MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	virtual BOOL32		MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

private:
	//����
	void				EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//ע��
	void				EventReg(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegAck(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegNack(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//��������״̬֪ͨ
	void				EventMixerStatNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
// 	//�������״̬֪ͨ
// 	void				EventMixGrpStatNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//��������
	void				EventStartMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStartMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStartMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//ֹͣ����
	void				EventStopMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//������������
	void				EventStartVac(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//ֹͣ��������
	void				EventStopVac(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//�����Ա
	void				EventAddMixMember(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventAddMixMemberAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventAddMixMemberNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	//ɾ����Ա
	void				EventDelMixMember(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventDelMixMemberAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventDelMixMemberNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

//ǿ�Ƴ�Ա����
 	void				EventForceMemberMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventForceMemberMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventForceMemberMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
//ȡ��ǿ�Ƴ�Ա����
 	void				EventCancelForceMemberMix(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventCancelForceMemberMixAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
 	void				EventCancelForceMemberMixNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//���û������
	void				EventSetMixDepth(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetMixDepthAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetMixDepthNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//�Ƿ�������  �����Ƿ�������
	void				EventSendAudNtfy(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//����������������ʱ��
	void				EventSetVacKeepTime(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//�������֪ͨ
	void				EventVacResultNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);


	void				EventSyncChnlCmd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//����������Կ ����
	void				EventSetMediaKeyNtfy(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

};

#endif