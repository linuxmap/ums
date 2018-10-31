#ifndef __audbas_handler_h_
#define __audbas_handler_h_

#include "servicehandler.h"
#include "umsinnertype.h"

//apu2 “Ù∆µ  ≈‰∆˜
class CAudBasHandler : public IServiceHandler
{
public:
	CAudBasHandler();
	~CAudBasHandler();

public:
	virtual BOOL32		MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	virtual BOOL32		MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

private:
	//∂œ¡¥
	void				EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//◊¢≤·
	void				EventReg(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegAck(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventRegNack(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);

	//  ≈‰∆˜µƒ◊¥Ã¨Õ®÷™
	void				EventEqpStatNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	//  ≈‰∆˜Õ®µ¿µƒ◊¥Ã¨Õ®÷™
	void				EventChnlStatNtfy(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//ø™∆Ù  ≈‰
	void				EventStartAdapter(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStartAdapterAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStartAdapterNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//µ˜’˚  ≈‰
//	void				EventChangeAdapter(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventChangeAdapterAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventChangeAdapterNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);

	//Õ£÷π  ≈‰
	void				EventStopAdapter(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopAdapterAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventStopAdapterNAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst);
	void				EventSetSync( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst );

	void				EventSetMediaKey( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst );
};

#endif