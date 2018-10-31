#include "vmprcvchan.h"
#include "kdvdef.h"
#include "umsvmp.h"
#include "umsobject.h"

extern BOOL32 g_bLogon;

//////////////////////////////////////////////////////////////////////////
//vmprcvchan
CVmpRcvChan::CVmpRcvChan()
{
	m_pcUmsVmp = NULL;
	m_wChanIndex = 0;
}

CVmpRcvChan::~CVmpRcvChan()
{
	Clear();
}

void CVmpRcvChan::Clear()
{
	m_pcUmsVmp = NULL;
	m_wChanIndex = 0;
	m_bStart = FALSE;
}

BOOL32 CVmpRcvChan::Create(CUmsVmp* pcUmsVmp, u16 wChanIndex, PFRAMEPROC pCallBack, const TVmpTimeSpan& tSpan)
{
	if (NULL == pcUmsVmp)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Create Invalid param. VmpID:%d, ChnlIndx:%d\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex));
		return FALSE;
	}

	s32 wRet = m_cMedia.Create(MAX_VIDEO_FRAME_SIZE, pCallBack, (u32)this);
	if(MEDIANET_NO_ERROR !=  wRet)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Create Set call-back failed. VmpID:%d, ChnlIndx:%d, Err:%d.\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex, wRet));
		return FALSE;
	}
	else
	{
		m_cMedia.SetHDFlag(FALSE);

		TRSParam tParam;
		tParam.m_wFirstTimeSpan = tSpan.m_wFirstTimeSpan;
		tParam.m_wSecondTimeSpan = tSpan.m_wSecondTimeSpan;
		tParam.m_wThirdTimeSpan = tSpan.m_wThirdTimeSpan;
		tParam.m_wRejectTimeSpan = tSpan.m_wRejectTimeSpan;
		m_cMedia.ResetRSFlag(tParam, TRUE);

		Clear();
		m_pcUmsVmp = pcUmsVmp;
		m_wChanIndex = wChanIndex;
		m_bStart = FALSE;

		return TRUE;
	}
}

BOOL32 CVmpRcvChan::SetNetParam(u16 wLocalPort, u16 wRemotePort, u32 dwRcvIP)
{
	m_wEqpRcvPort = wLocalPort + m_wChanIndex * UMS_VMP_PORT_SPAN;
	m_wUmsRcvPort = wRemotePort + 2 + m_wChanIndex;

	TLocalNetParam tlocalNetParm;
    memset(&tlocalNetParm, 0, sizeof(TLocalNetParam));
    tlocalNetParm.m_tLocalNet.m_wRTPPort = m_wEqpRcvPort;
    tlocalNetParm.m_tLocalNet.m_wRTCPPort = m_wEqpRcvPort + 1;
    tlocalNetParm.m_dwRtcpBackAddr = dwRcvIP;
	tlocalNetParm.m_wRtcpBackPort = m_wUmsRcvPort;
	
	s32 nRet = 0;
    nRet = m_cMedia.SetNetRcvLocalParam(tlocalNetParm);
    if(MEDIANET_NO_ERROR !=  nRet)
    {
		MdlError(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Start Set net param failed. VmpID:%d, ChnlIndx:%d, Err:%d.\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex, nRet));
		return FALSE;
	}
    else
    {
		return TRUE;
    }
}

void CVmpRcvChan::Start()
{
	if (InWorking())
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Start Channel is working.VmpID:%d, ChnlIndx:%d\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex));
		return;
	}
	m_cMedia.StartRcv();
	m_bStart = TRUE;
}

void CVmpRcvChan::Stop()
{
	if (!InWorking())
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Stop Channel is not working.VmpID:%d, ChnlIndx:%d\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex));
		return ;
	}

	MdlHint(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Stop. VmpID:%d, chnlIndx:%d.\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex));

	m_cMedia.StopRcv();
	m_bStart = FALSE;
}

void CVmpRcvChan::SetDecryptKey(const TTPEncrypt& tInfo)
{
	switch (tInfo.m_emEncryptModel)
	{
	case emTPEncryptTypeNone:
		{
			m_cMedia.SetDecryptKey(NULL, 0, 0);
		}
		break;
		
	case emTPEncryptTypeDES:
		{
			m_cMedia.SetDecryptKey((s8*)tInfo.m_achEncKey, tInfo.m_byKeyLen, DES_ENCRYPT_MODE);
		}
		break;
		
	case emTPEncryptTypeAES:
		{
			m_cMedia.SetDecryptKey((s8*)tInfo.m_achEncKey, tInfo.m_byKeyLen, AES_ENCRYPT_MODE);
		}
		break;

//Protocol_file
	case emTPEncryptTypeQtEverySecond:
	case emTPEncryptTypeQtEveryMinute:
	case emTPEncryptTypeQtEveryConf:
		{
			s8 byKey[TP_ENCRYPT_KEY_LEN+1] = {0};
			sprintf(byKey, "%d", m_pcUmsVmp->GetQtHandle());
			u8 byLen = strlen(byKey);
			m_cMedia.SetDecryptKey((s8*)byKey, byLen, QT_ENCRYPT_MODE);
		}

	    break;
		
	default:
		{
			m_cMedia.SetDecryptKey(NULL, 0, 0);
			MdlHint(Ums_Mdl_Mpu2TP, ("CVmpRcvChan::Start Invalid encrypt type. VmpID:%d, ChnlIndx:%d, Type:%d.\n", 
										m_pcUmsVmp->m_wVmpID, m_wChanIndex, tInfo.m_emEncryptModel));
		}
	}
	
	m_cMedia.SetActivePT(MEDIA_TYPE_H264, MEDIA_TYPE_H264);
}

