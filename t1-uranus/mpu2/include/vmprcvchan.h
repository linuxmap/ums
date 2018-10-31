#ifndef _ums_vmp_rcv_chan_h_
#define _ums_vmp_rcv_chan_h_
#include "tpsys.h"
#include "tpcommonstruct.h"
#include "kdvmedianet.h"

class CUmsVmp;

//接收通道
class CVmpRcvChan
{
public:
	CVmpRcvChan();
	~CVmpRcvChan();
	
public:
	BOOL32 	Create(CUmsVmp* pcUmsVmp, u16 wChanIndex, PFRAMEPROC pCallBack, const TVmpTimeSpan& tSpan);
	void	Clear();
	BOOL32	SetNetParam(u16 wLocalPort, u16 wRemotePort, u32 dwRcvIP);
	void	Start();
	void	Stop();
	void	SetDecryptKey(const TTPEncrypt& tInfo);
	
public:
	BOOL32			Valid() const { return NULL != m_pcUmsVmp; }
	BOOL32			InWorking() const { return m_bStart; }
	CKdvMediaRcv*	RcvMedia() { return &m_cMedia; }
	CUmsVmp*		UmsVmp() const { return m_pcUmsVmp; }
	u16				ChanIndex() const { return m_wChanIndex; }

	u16				EqpPort() { return m_wEqpRcvPort; }
	u16				UmsPort() { return m_wUmsRcvPort; }
private:
	CVmpRcvChan(const CVmpRcvChan& );
	CVmpRcvChan& operator=(const CVmpRcvChan& );
	
private:
	CUmsVmp*		m_pcUmsVmp;
	CKdvMediaRcv	m_cMedia;
	u16				m_wChanIndex;
	BOOL32			m_bStart;

	u16				m_wEqpRcvPort;
	u16				m_wUmsRcvPort;
};

#endif
