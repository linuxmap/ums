#ifndef __hdu_handler_h_
#define __hdu_handler_h_

#include "servicehandler.h"
#include "tphdu2.h"
#include "umsinnertype.h"

//����ǽ��Ϣ����ӿ�
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
	//ע��
	void				EventReg(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegAck(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegNack(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//����
	void				EventPlayReq(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventPlayAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventPlayNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//ֹͣ����
	void				EventStopPlayReq(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopPlayAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopPlayNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	
	//����ͨ��״̬
	void				EventUpdateChanStatus(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventReqIFrame(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//��������
	void				EventUpdateBrd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventUpdateNotify(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	//�޸�ͨ������
	void				EventNotifyChan(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//
	void				EventDelBrd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventDelChan(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	//HDU ����״̬
	void				EventUpdateStatus(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetVol(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	// �л�ͨ������ģʽ��1�������4���棩
	void                EventChangeHduChanMode(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventChangeHduChanModeAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventChangeHduChanModeNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	void                EventMediaKeyNty(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
private:
	//��
	u8					Layer(CTPMcuBrdSsn* pInst);
	//��
	u8					Slot(CTPMcuBrdSsn* pInst);
};


#endif