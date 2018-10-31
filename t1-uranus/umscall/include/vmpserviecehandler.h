#ifndef _vmp_service_handler_h_
#define _vmp_service_handler_h_
#include "umseqpservice.h"

//////////////////////////////////////////////////////////////////////////
//许成	不同业务的处理接口

class CUmsConfInst;
class CServiceHandler
{
public:
	CServiceHandler() {}
	virtual ~CServiceHandler() {}

public:
	virtual BOOL32	Handler(CTpMsg* const pcMsg) = 0;

public:
	virtual const CBaseService*		Assign(ServiceCB cbFun, CUmsConfInst* pcInst) const = 0;
	virtual void					Release(const CBaseService* pcService) = 0;
	virtual BOOL32                  Start(const CBaseService* pcBaseService, void* useParam) = 0;
	virtual BOOL32					ChangeMode(const CBaseService* pcBaseService, void* useParam) = 0;
	virtual void					Stop(const CBaseService* pcBaseService) const = 0;
	virtual void					GetRcvChanAddr(TServiceAddr& tRes, const CBaseService* pcBaseService, u16 wChanIndex) = 0;
	virtual void					GetSndChanAddr(TServiceAddr& tRes, const CBaseService* pcBaseService) = 0;
	virtual void                    AskFrameToBaseService(const CBaseService* pcBaseService) = 0;

	virtual void					Show(const CBaseService* pcBaseService) = 0;

protected:
	void	PostMsgToEqpModule(u16 wEvent, void* param, u16 wLength) const;
	void PostMsgToXmpuEqp(u16 wEvent, void* param, u16 wLength) const;
};

class CVmpServiceHandler : public CServiceHandler
{
public:
	CVmpServiceHandler();
	~CVmpServiceHandler();

public:
	virtual BOOL32	Handler(CTpMsg* const pcMsg);

public:
	virtual const CBaseService*		Assign(ServiceCB cbFun, CUmsConfInst* pcInst) const;
	virtual void					Release(const CBaseService* pcService);
	virtual BOOL32                  Start(const CBaseService* pcBaseService, void* useParam);
	virtual BOOL32					ChangeMode(const CBaseService* pcBaseService, void* useParam);
	virtual void					Stop(const CBaseService* pcBaseService) const;
	virtual void					GetRcvChanAddr(TServiceAddr& tRes, const CBaseService* pcBaseService, u16 wChanIndex);
	virtual void					GetSndChanAddr(TServiceAddr& tRes, const CBaseService* pcBaseService);
	virtual void                    AskFrameToBaseService(const CBaseService* pcBaseService);
	static	void					SetMediaKey(const CBaseService* pcBaseService, const TTPQTMediaKeyInfo& tInfo, void* pcInst = NULL);
	virtual void					Show(const CBaseService* pcBaseService);

	void	UpdateSpeakerSideLine(const CBaseService* pcBaseService, u8 byFlag[], u8 byNum);

	void		UpdateXmpuSpeakerSideLine(const CBaseService* pcBaseService, u8 byFlag[], u8 byNum);
	void		XmpuAskFrame(CTpMsg* const pcMsg);
private:
	void    EventAssginRes(CTpMsg* const pcMsg);
	void	EventStartRes(CTpMsg* const pcMsg);
	void	EventStopRes(CTpMsg* const pcMsg);
	void	EventMdyRes(CTpMsg* const pcMsg);
	void	EventAskFrame(CTpMsg* const pcMsg);

	//Xmpu msg
	const CBaseService*		AssignXmpuEqp(ServiceCB cbFun, CUmsConfInst* pcInst) const;
	virtual void					ReleaseXmpuMpu2(const CBaseService* pcService);
};

#endif