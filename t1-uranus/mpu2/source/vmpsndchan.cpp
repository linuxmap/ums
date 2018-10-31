#include "vmpsndchan.h"
#include "kdvdef.h"
#include "tpcommonstruct.h"
#include "umsvmp.h"
#include "umsobject.h"

extern BOOL32 g_bLogon;

extern u32 g_dwMpu2tpNetBandMul;

CVmpSndChan::CVmpSndChan()
{
	m_pcUmsVmp = NULL;
	m_wChanIndex = 0;
	m_wCreate = FALSE;
}

CVmpSndChan::~CVmpSndChan()
{
	Clear();
}

BOOL32 CVmpSndChan::Init(CUmsVmp* pcUmsVmp, u16 wChanIndex)
{
	if (NULL == pcUmsVmp)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CVmpSndChan::Init Invalid param. VmpID:%d, ChnlIndx:%d\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex));
		return FALSE;
	}

	m_pcUmsVmp = pcUmsVmp;
	m_wChanIndex = wChanIndex;

	return TRUE;
}

BOOL32 CVmpSndChan::Create(u32 dwNetBand, u8 byFrameRate, u16 wRcvPort, u32 dwRcvIP, u16 wLocalPort)
{

	u32 dwNetBandBig = dwNetBand*1024;

    // 在配置中：15 代表1.5 倍，所有将倍数除10
    dwNetBandBig = (u32)(dwNetBandBig*g_dwMpu2tpNetBandMul/10.0);


	s32 wRet = m_cMedia.Create(MAX_VIDEO_FRAME_SIZE, dwNetBandBig, byFrameRate, MEDIA_TYPE_H264);
	if (MEDIANET_NO_ERROR != wRet)
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("CVmpSndChan::Create Creat snd-media failed. Err:%d. VmpID:%d, ChnlIndx:%d\n", wRet, m_pcUmsVmp->m_wVmpID, m_wChanIndex));
		return FALSE;
	}

	m_cMedia.SetActivePT(MEDIA_TYPE_H264);
	m_cMedia.ResetRSFlag(2000, TRUE);
	
	m_cMedia.SetHDFlag(m_pcUmsVmp->GetEncParam()->m_dwProfile);

	TNetSndParam tNetParam;
	memset(&tNetParam, 0, sizeof(tNetParam));
	
	m_wEqpRcvPort = wLocalPort + 3 + m_wChanIndex * UMS_VMP_PORT_SPAN;
	m_wUmsRcvPort = wRcvPort;
	
	tNetParam.m_byNum = 1;
	tNetParam.m_tLocalNet.m_wRTPPort = m_wEqpRcvPort+1;
	tNetParam.m_tLocalNet.m_wRTCPPort = m_wEqpRcvPort;
	tNetParam.m_tRemoteNet[0].m_dwRTPAddr = dwRcvIP;
	tNetParam.m_tRemoteNet[0].m_wRTPPort = m_wUmsRcvPort;
	tNetParam.m_tRemoteNet[0].m_dwRTCPAddr = dwRcvIP;
	tNetParam.m_tRemoteNet[0].m_wRTCPPort = m_wUmsRcvPort + 1;
	
	MdlHint(Ums_Mdl_Mpu2TP, ("CVmpSndChan::Create VmpID:%d, ChnlIndx:%d, RcvIP:%d, RcvPort:%d.\n", m_pcUmsVmp->m_wVmpID, m_wChanIndex, dwRcvIP, wRcvPort));

	u16 wRes = m_cMedia.SetNetSndParam(tNetParam);
	if (MEDIANET_NO_ERROR != wRes)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CVmpSndChan::Create Set snd-media net param failed. VmpID:%d, ChnlIndx:%d, Err:%d.\n", wRes, m_pcUmsVmp->m_wVmpID, m_wChanIndex));
		return FALSE;
	}

	return TRUE;
}

void CVmpSndChan::Clear()
{
	m_pcUmsVmp = NULL;
	m_wChanIndex = 0;
}

void CVmpSndChan::SetEncryptKey(const TTPEncrypt& tInfo)
{
	
	switch (tInfo.m_emEncryptModel)
	{
	case emTPEncryptTypeNone:
		{
			m_cMedia.SetEncryptKey(NULL, 0, 0);
		}
		break;
		
	case emTPEncryptTypeDES:
		{
			m_cMedia.SetEncryptKey((s8*)tInfo.m_achEncKey, tInfo.m_byKeyLen, DES_ENCRYPT_MODE);
		}
		break;
		
	case emTPEncryptTypeAES:
		{
			m_cMedia.SetEncryptKey((s8*)tInfo.m_achEncKey, tInfo.m_byKeyLen, AES_ENCRYPT_MODE);
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
			m_cMedia.SetEncryptKey((s8*)byKey, byLen, QT_ENCRYPT_MODE);
		}
		break;

	default:
		{
			MdlError(Ums_Mdl_Mpu2TP, ("CVmpSndChan::SetEncryptKey Invalid mode. VmpID:%d, ChnlIndx:%d, Mode:%d.\n", 
				m_pcUmsVmp->m_wVmpID, m_wChanIndex, tInfo.m_emEncryptModel));
			m_cMedia.SetEncryptKey(NULL, 0, 0);
		}
		break;
	}
}
