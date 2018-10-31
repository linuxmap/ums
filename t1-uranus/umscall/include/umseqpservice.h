#ifndef _ums_eqp_service_h_
#define _ums_eqp_service_h_

#include "umsinnerstruct.h"
#include "tpmsg.h"
#include "umsxmpinterface.h"
#include "callinnerstruct.h"

using namespace UmsTpmsg;
//////////////////////////////////////////////////////////////////////////
//许成	外设业务管理

enum EmSerInfoStatus
{
	em_Idle = 0,
	em_Assigned,
	em_Working,
	em_Error,
};

class CUmsConfInst;
//外设信息
class CBaseService
{
public:
	CBaseService();
	virtual ~CBaseService();

public:
	void	Init(const TServiceReg& tInfo);
	void	Clear();

public:
	EmServiceType	GetType() const { return m_emType; }
	u16				GetEqpStartPort() const { return m_wEqpStartPort; }
	u32				GetEqpIP() const { return m_dwEqpIP; }
	u16				GetUmsStartPort() const { return m_wUmsStartPort; }
	u32				GetMediaIP() const { return m_dwMediaIP; }
	u32				GetMediaNode() const { return m_dwMediaNode; }
	void			SetMediaIP(u32 dwLocalIP) { m_dwMediaIP = dwLocalIP; }
	void			SetMediaNode(u32 dwMediaNode) { m_dwMediaNode = dwMediaNode; }

public:
	u16		GetServiceID() const { return m_wServiceID; }
	BOOL32	Invalid() const { return em_unknow_service == m_emType || 0 == m_wServiceID; }

public:
	BOOL32	operator==(const CBaseService& cInfo) const;

private:
	CBaseService(const CBaseService& );
	CBaseService& operator=(const CBaseService& );

private:
	EmServiceType	m_emType;
	u16				m_wServiceID;
	u16				m_wEqpStartPort;
	u32				m_dwEqpIP;
	u16				m_wUmsStartPort;
	u32				m_dwMediaIP;
	u32				m_dwMediaNode;
};

//启动业务失败，以及掉线退出时调用
typedef void (*ServiceCB)(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, void* param, u16 wTmp1);

//外设信息
class CServiceInfo : public CBaseService
{
public:
	CServiceInfo();
	~CServiceInfo();

public:
	BOOL32		Assign(ServiceCB cbFun, void* param);
	void				Stop();
	void				Show();

	BOOL32		AssignXmpu(ServiceCB cbFun, void* param);
	void				ReleaseMpu2();

	// Xmpu mpu2对外提供地址
	void				GetDecAddr(TServiceAddr& tAddr, u16 wChanIndex);
	void				GetEncAddr(TServiceAddr& tAddr);

	void				SetXmpuVmpTPOnline(TXmpuVmpMdyInfo tInfo);
	u16				GetMpu2MemNum() {return m_tStyleInfo.m_byMemberNum;}
	BOOL32		IsOnline() {return m_bOnLine;}
public:
	void		RunCBFun(const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wTmp1 = 0);

public:

	void        SetStatus(EmSerInfoStatus emStatus) {m_emStatus = emStatus;}
	EmSerInfoStatus GetStatus() const {return m_emStatus;}
	BOOL32		WorkStatus() const { return em_Working == m_emStatus; }
	BOOL32      IdleStatus() const { return em_Idle == m_emStatus; }
	BOOL32      AssignState() const { return em_Assigned == m_emStatus;}

	void        SaveInfo(TVmpStyleInfo& tInfo, TVmpEncParam& tParam) { m_tStyleInfo = tInfo; m_tEncParam = tParam;}
	BOOL32      IsSameInfo(const TVmpStyleInfo& tInfo, const TVmpEncParam& tParam){ return (m_tStyleInfo == tInfo && m_tEncParam == tParam);}
	
	void* Param(){ return m_param; }

private:
	EmSerInfoStatus		m_emStatus;
	ServiceCB	m_cbFun;
	void*		m_param;

	TVmpEncParam	m_tEncParam;
	TVmpStyleInfo	m_tStyleInfo;

public:
	// xmpu外设端口
	BOOL32			m_bOnLine;
	TTPTransAddr	m_atDecRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道rtp rcv
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道rtp rcv
	TTPTransAddr	m_atDecRtcpAddr[TP_VMP_MAX_IN_CHN_NUM];  // vmp解码通道 back rtcp rcv
	TTPTransAddr	m_tEncRtpAddr; // vmp编码通道rtcp rcv
	TTPTransAddr	m_tEncRtcpAddr; // vmp编码通道rtcp rcv
	TTPTransAddr	m_tEncMiddleRtcpAddr; // vmp编码通道rtcp rcv
	CDsListInfo		m_cToMpuDsInfo;
};

//外设交互接口
class CEqpService
{
public:
	static CEqpService&	Instance();

public:
	CEqpService();
	~CEqpService();

public:
	const CBaseService*		Assign(const EmServiceType emType, ServiceCB cbFun, void* param);
	void					Release(const CBaseService* pcService, const EmServiceType emType);
//	void					Release(const EmServiceType emType, const u16 wServiceID);

	// xmpu接口
	const CBaseService*		AssignXmpuMpu2(const EmServiceType emType, ServiceCB cbFun, void* param);

	void					ReleaseXmpuMpu2(const CBaseService* pcService, const EmServiceType emType);
	void					FlushXmpuMpu2();
	void					OnXmpuVmpMdyNty(CUmsConfInst* pcInst, TXmpuVmpMdyInfo tInfo);
	void					FlushXmpuMiddleAddrToMpu2(const CBaseService* pcService);
	void                  UpdateXmpuMpu2();
	void                  DisconnectXmpuMpu2(u32 dwEqpID);
public:
	BOOL32                  SetWorking(const EmServiceType emType, const u16 wServiceID);
	void                    SetError(const EmServiceType emType, const u16 wServiceID);
	u16						GetTotalNum(const EmServiceType emType) const;
	u16						GetWorkingNum(const EmServiceType emType) const;
	u16						GetIdleNum(const EmServiceType emType) const;

	void                    SaveInfo(const EmServiceType emType, const u16 wServiceID, TVmpStyleInfo& tInfo, TVmpEncParam& tParam);
	BOOL32                  IsSameInfo(const EmServiceType emType, const u16 wServiceID, TVmpStyleInfo& tInfo, TVmpEncParam& tParam);	

public:
	void					OperateRet(const EmServiceType emType, const u16 wServiceID, 
									const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wTmp1 = 0);
	void					Show();

public:
	BOOL32	Handler(CTpMsg* const pcMsg);

public:
	void	EventReg(CTpMsg* const pcMsg);
	void	EventUnReg(CTpMsg* const pcMsg);
	
	CServiceInfo&	ServeiceInfo(u16 wIndex) { return m_acInfo[wIndex];}
	CServiceInfo*	Find(const EmServiceType emType, const u16 wServiceID);

	void OnXmpuMpu2DisConnnect(u32 dwEqpID);

private:
	CServiceInfo*	FindIdle();
private:
	CServiceInfo	m_acInfo[UMS_MAX_SERVICE_NUM];
};

#endif