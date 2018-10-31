#ifndef _ums_vmp_snd_chan_h_
#define _ums_vmp_snd_chan_h_
#include "tpsys.h"
#include "kdvmedianet.h"
#include "tpcommonstruct.h"

class CUmsVmp;

class CVmpSndChan
{
public:
	CVmpSndChan();
	~CVmpSndChan();

public:
	BOOL32		Init(CUmsVmp* pcUmsVmp, u16 wChanIndex);
	BOOL32		Create(u32 dwNetBand, u8 byFrameRate, u16 wRcvPort, u32 dwRcvIP, u16 wLocalPort);
	void		Clear();
	void		SetEncryptKey(const TTPEncrypt& tInfo);
	CUmsVmp*	UmsVmp() const { return m_pcUmsVmp; }

public:
	BOOL32			Valid() const { return NULL != m_pcUmsVmp; }
	u16				ChanIndex() const { return m_wChanIndex; }
	CKdvMediaSnd*	SndMedia() { return &m_cMedia; }

	u16				EqpPort() { return m_wEqpRcvPort; }
	u16				UmsPort() { return m_wUmsRcvPort; }
	
private:
	CVmpSndChan(const CVmpSndChan& );
	CVmpSndChan& operator=(const CVmpSndChan& );

private:
	CUmsVmp*		m_pcUmsVmp;
	CKdvMediaSnd	m_cMedia;
	u16				m_wChanIndex;

	BOOL32			m_wCreate;

	u16				m_wEqpRcvPort;
	u16				m_wUmsRcvPort;
};

#endif
