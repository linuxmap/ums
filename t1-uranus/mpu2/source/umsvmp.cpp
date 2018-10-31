#include "umsvmp.h"
#include "kdvdef.h"
#include "umsapi.h"

#include "codecwrapperdef_hd.h"

//Protocol_file

#include "qtinterface.h"


extern BOOL32 g_bLogon;
extern u32    g_dwBWScale;
//////////////////////////////////////////////////////////////////////////
//umsvmp
CUmsVmp::CUmsVmp()
{
	m_bAlreadyCreated = FALSE;
	m_dwRcvIP = 0;
	m_wRcvPort = 0;
	m_wLocalRcvPort = 0;
	m_wLocalSndPort = 0;
	for (u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		m_abAddChanFlag[wIndex] = FALSE;
	}
	return ;
}

CUmsVmp::~CUmsVmp()
{
	Clear();
}

BOOL32 CUmsVmp::Init(u32 dwRcvIP, u16 wRcvPort, u16 wLocalRcvPort, u16 wLocalSndPort, const TVmpTimeSpan& tSpan)
{
	MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::Init. VmpID:%d, Created:%d.\n", m_wVmpID, m_bAlreadyCreated));

	if (!m_bAlreadyCreated)
	{
		TMultiPicCreate tMPCreate;
		tMPCreate.m_dwDevVersion = (u32)en_MPU2_Board;
		tMPCreate.m_dwMode = VMP_SIMPLE;
		
		CSemInfo::GetSem()->SemIn("m_cHardMulPic.Create VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
		s32 nRet = m_cHardMulPic.Create(tMPCreate);
		CSemInfo::GetSem()->SemOut("m_cHardMulPic.Create VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);

		if (HARD_MULPIC_OK != nRet)
		{
			MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::Init Cread hardmulpic failed. Error:%d.\n", nRet));
			return FALSE;
		}

		u16 wRet = KdvSocketStartup();  
		if ( MEDIANET_NO_ERROR != wRet )
		{
			MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::Init KdvSocketStartup failed. Error:%d\n", wRet));
			CSemInfo::GetSem()->SemIn("m_cHardMulPic.Destory VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
			m_cHardMulPic.Destory();
			CSemInfo::GetSem()->SemOut("m_cHardMulPic.Destory VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
			return FALSE;
		}

		MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::Init. m_acMediaRcv Created:%d.\n", m_bAlreadyCreated));
		
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
		{
			if (!m_acMediaRcv[wIndex].Create(this, wIndex, RecvFrame, tSpan))
			{
				Clear();
				return FALSE;
			}
		}

		MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::Init. m_cSndChan Created:%d.\n", m_bAlreadyCreated));

		if (!m_cSndChan.Init(this, 0))
		{
			Clear();
			return FALSE;
		}
		//平滑发送
		SetSendUseTimer(TRUE);

		m_bAlreadyCreated = TRUE;
		MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::Init end. Created:%d.\n", m_bAlreadyCreated));	
	}
	
	m_dwRcvIP = dwRcvIP;
	m_wRcvPort = wRcvPort;
	m_wLocalRcvPort = wLocalRcvPort;
	m_wLocalSndPort = wLocalSndPort;
	m_tSpan = tSpan;
	
	return TRUE;
}

void CUmsVmp::UpdateRmtPort( u32 dwRcvIP, u16 wRcvPort)
{
	MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::UpdateRmtPort VmpID:%d, "IPFORMAT", Port:%d\n", m_wVmpID, u32ToIP(dwRcvIP), wRcvPort));
	m_dwRcvIP = dwRcvIP;
	m_wRcvPort = wRcvPort;
}

EmVmpRes CUmsVmp::Start(const TVmpStartParam& tInfo)
{
	if (em_ums_vmp_invalid == tInfo.m_tStyleInfo.m_emVmpStyle)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::Start Invalid param. VmpID:%d\n", m_wVmpID));
		return em_ums_vmp_invalid_param;
	}

	EmVmpRes emRes = SetEncParam(tInfo.m_tEncParam);
	if (em_ums_vmp_success != emRes)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::Start Set SetEncParam failed. VmpID:%d\n", m_wVmpID));
		return emRes;
 	}

	StartMerge();

	for (u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		m_acMediaRcv[wIndex].SetDecryptKey(tInfo.m_tEncrypt);
		m_acMediaRcv[wIndex].SetNetParam(m_wLocalRcvPort, m_wRcvPort, m_dwRcvIP);
	}
	
	emRes = ChangeStyleParam(tInfo.m_tStyleInfo);
	if (em_ums_vmp_success != emRes)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::Start Set vmp param failed. VmpID:%d\n", m_wVmpID));
		return emRes;
	}

	UpdateSidelineColor();

	//开启发送 放在开启合成后面  存在闪上一个风格的可能性
	if (!m_cSndChan.Create(m_tEncParam.m_wBitRate, m_tEncParam.m_byFrameRate, m_wRcvPort, m_dwRcvIP, m_wLocalRcvPort))
	{
		return em_ums_vmp_set_param_failed;
	}

	SetEncrypt(tInfo.m_tEncrypt);
 
 	m_tParam = tInfo;
 	m_cStyle.Set(tInfo.m_tStyleInfo.m_emVmpStyle);

	MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::Start end. VmpID:%d\n", m_wVmpID));

	return em_ums_vmp_success;
}

void CUmsVmp::Stop()
{
	TTPEncrypt tEncrypt;
	for (u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		m_acMediaRcv[wIndex].SetDecryptKey(tEncrypt);
		m_acMediaRcv[wIndex].Stop();
		m_abAddChanFlag[wIndex] = FALSE;
	}

	m_cSndChan.SetEncryptKey(tEncrypt);

	CSemInfo::GetSem()->SemIn("m_cHardMulPic.StopMerge VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	s32 nRetCode = m_cHardMulPic.StopMerge();
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.StopMerge VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
    if (HARD_MULPIC_OK != nRetCode)
    {
		MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::Stop VmpID:%d, Err:%d.\n", m_wVmpID, nRetCode));
    }

	for (s32 nIndex = 0; nIndex < m_cStyle.GetChanNum(); ++nIndex)
	{
		CSemInfo::GetSem()->SemIn("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
		m_cHardMulPic.RemoveChannel(nIndex);
		CSemInfo::GetSem()->SemOut("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	}

	//合成参数要清除
	memset(&m_tEncParam, 0, sizeof(m_tEncParam));
	m_cStyle.Clear();
	m_tParam.Clear();
	memset(m_abyFlag, 0, sizeof(m_abyFlag));

	//Protocol_file

    QtExitMediaKey((u32)m_wQtHandle);

}

EmVmpRes CUmsVmp::ChangeStyleParam(const TVmpStyleInfo& tInfo)
{
	u16 wIndex = 0; 
	for (wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		if (m_tParam.m_tStyleInfo.m_atMemberInfo[wIndex].Valid())
		{// 旧的成员有效
			if (m_tParam.m_tStyleInfo.m_atMemberInfo[wIndex].m_dwHandle != tInfo.m_atMemberInfo[wIndex].m_dwHandle)
			{// 新旧成员不一致时，先停止接收老的，防止出现闪上一个画面
				m_acMediaRcv[wIndex].Stop();
			}
		}
	}

	CVmpStyle cStyle(tInfo.m_emVmpStyle);

	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetMulPicType VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	s32 nRes = m_cHardMulPic.SetMulPicType(cStyle.GetHardStyle());
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetMulPicType VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	if (HARD_MULPIC_OK != nRes)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::ChangeStyleParam Set vmp style failed. VmpID:%d Err:%d.\n", m_wVmpID, nRes));
		return em_ums_vmp_set_param_failed;
	}

	if (!SetIdleChanShow(tInfo.m_emShowMode))
	{
		return	em_ums_vmp_set_param_failed;
	}

	for (wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		if (m_tParam.m_tStyleInfo.m_atMemberInfo[wIndex].Valid())
		{
			if (!tInfo.m_atMemberInfo[wIndex].Valid())
			{
				if (m_abAddChanFlag[wIndex])
				{
					m_acMediaRcv[wIndex].Stop();
					CSemInfo::GetSem()->SemIn("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
					m_cHardMulPic.RemoveChannel(m_acMediaRcv[wIndex].ChanIndex());
					CSemInfo::GetSem()->SemOut("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
					m_abAddChanFlag[wIndex] = FALSE;
				}
			}
			else
			{// 可能之前已经stop，这里确认下，保证start
				if(m_abAddChanFlag[wIndex])
				{
					m_acMediaRcv[wIndex].Start(); // 此函数里面有保护，不会重复start
				}
			}
		}
		else
		{
			if (tInfo.m_atMemberInfo[wIndex].Valid())
			{
				CSemInfo::GetSem()->SemIn("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
				if (HARD_MULPIC_OK != m_cHardMulPic.AddChannel(wIndex))
				{
					CSemInfo::GetSem()->SemOut("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
					MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::ChangeStyleParam Add channel failed. ChanIndex:%d.\n", wIndex));
				}
				else
				{
					CSemInfo::GetSem()->SemOut("m_cHardMulPic.RemoveChannel VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
					m_abAddChanFlag[wIndex] = TRUE;
					m_acMediaRcv[wIndex].Start();
				}
			}
		}
	}

	u32 adwBorder[UMS_VMP_MAX_RCV] = {0};
	u32 dwNum = 0;
	for (u8 byIndex = 1; byIndex < tInfo.m_byMemberNum; ++byIndex)
	{
		if (tInfo.m_atMemberInfo[byIndex].m_bMerged)
		{
			adwBorder[dwNum] = byIndex;
			++dwNum;
		}
	}

	MdlHint(Ums_Mdl_Mpu2TP, ("SetIgrDrawBorders VmpID:%d Style:%d, BrdNum:%d.\n", m_wVmpID, cStyle.GetHardStyle(), dwNum));
	for (u32 dwIn = 0; dwIn < dwNum; ++dwIn)
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("SetIgrDrawBorders VmpID:%d BrdIndex:%d.\n", m_wVmpID, adwBorder[dwIn]));
	}

#ifdef _LINUX12_
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetIgrDrawBorders VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	m_cHardMulPic.SetIgrDrawBorders(cStyle.GetHardStyle(), adwBorder, dwNum);
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetIgrDrawBorders VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
#endif

	m_cStyle = cStyle;
	m_tParam.m_tStyleInfo = tInfo;

	return em_ums_vmp_success;
}

void CUmsVmp::Clear()
{
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.Destory VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	m_cHardMulPic.Destory();
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.Destory VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);

	for (u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
	{
		m_acMediaRcv[wIndex].Clear();
		m_abAddChanFlag[wIndex] = FALSE;
	}

	m_cSndChan.Clear();

	memset(&m_tEncParam, 0, sizeof(m_tEncParam));

	m_dwRcvIP = 0;
	m_wRcvPort = 0;

	memset(m_abyFlag, 0, sizeof(m_abyFlag));

	m_bShowEnc = FALSE;
}

void CUmsVmp::SetEncrypt(const TTPEncrypt& tEncrypt)
{
	m_cSndChan.SetEncryptKey(tEncrypt);
}

EmVmpRes CUmsVmp::StartMerge()
{
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.StartMerge VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	s32 nRet = m_cHardMulPic.StartMerge();
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.StartMerge VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetVidDataCallback VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	m_cHardMulPic.SetVidDataCallback(0, VmpCallBack, &m_cSndChan);
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetVidDataCallback VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);

	return em_ums_vmp_success;
}

EmVmpRes CUmsVmp::SetEncParam(const TVmpEncParam& tParam)
{
	m_tParam.m_tEncParam = tParam;

	memset(&m_tEncParam, 0, sizeof(m_tEncParam));
	m_tEncParam.m_byEncType = MEDIA_TYPE_H264;
	m_tEncParam.m_byRcMode = 0;
	m_tEncParam.m_byMaxQuant = 45;
	m_tEncParam.m_byMinQuant = 20;
	

	m_tEncParam.m_wBitRate = tParam.m_wBitRate*g_dwBWScale/100;
	m_tEncParam.m_byFrameRate = tParam.m_byFrameRate;
	m_tEncParam.m_byImageQulity = 0;
	m_tEncParam.m_dwProfile = tParam.m_byProfileType;
	m_tEncParam.m_wVideoHeight = tParam.m_wVideoHeight;
	m_tEncParam.m_wVideoWidth = tParam.m_wVideoWidth;
	m_tEncParam.m_dwMaxKeyFrameInterval = 300;
	
	if ((tParam.m_wVideoWidth == 1920 && tParam.m_wVideoHeight == 1088) ||
		(tParam.m_wVideoWidth == 1920 && tParam.m_wVideoHeight == 1080))
	{
		m_tEncParam.m_dwMaxKeyFrameInterval = 3000;
	}
	else if (tParam.m_wVideoWidth == 1280 && tParam.m_wVideoHeight == 720 )
	{
		m_tEncParam.m_dwMaxKeyFrameInterval = 3000;
	}
	else if ((tParam.m_wVideoWidth == 720 || tParam.m_wVideoWidth == 704) && tParam.m_wVideoHeight == 576)
	{
		m_tEncParam.m_dwMaxKeyFrameInterval = 1000;
	}
	else if (tParam.m_wVideoWidth == 352 && tParam.m_wVideoHeight == 288)
	{
		m_tEncParam.m_dwMaxKeyFrameInterval = 500;
	}
	
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetVideoEncParam VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	s32 nRet = m_cHardMulPic.SetVideoEncParam(&m_tEncParam, 1);
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetVideoEncParam VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	if (HARD_MULPIC_OK != nRet)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::SetEncParam Hard pic set param failed. VmpID:%d Error:%d.\n", m_wVmpID, nRet));
		return em_ums_vmp_set_param_failed;
	}
	else
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::SetEncParam SetVideoEncParam ok. VmpID:%d\n", m_wVmpID));
	}

	OspPrintf(TRUE, 0, "Enc EncType:%d, Hp/Bp:%d, FrameRate:%d, BitRate:%d, W:%d, H:%d\n", 
		m_tEncParam.m_byEncType, m_tEncParam.m_dwProfile, m_tEncParam.m_byFrameRate, m_tEncParam.m_wBitRate,
		m_tEncParam.m_wVideoWidth, m_tEncParam.m_wVideoHeight);

	return em_ums_vmp_success;
}

BOOL32 CUmsVmp::SetIdleChanShow(EmVmpShowMode emShowMode)
{
	u32 dwHardShowMode = (u32)EN_PLAY_LAST;
	s8 szBmpFilePath[255] = {0};
	switch(emShowMode)
	{
	case ums_vmp_black_mode:
		{
			dwHardShowMode = (u32)EN_PLAY_BLACK;
		}
		break;

	case ums_vmp_lastframe_mode:
		{
			dwHardShowMode = (u32)EN_PLAY_LAST;
		}
		break;

	case ums_vmp_defaultpic_mode:
		{
			dwHardShowMode = (u32)EN_PLAY_BMP;
			sprintf(szBmpFilePath,"%s", DEFAULT_BMP_PATH);
		}
		break;

	case ums_vmp_userdefpic_mode:
		{
			dwHardShowMode = (u32)EN_PLAY_BMP_USR;
			sprintf(szBmpFilePath,"%s",USR_BMP_PATH);
		}
		break;

	default:
		{
			MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::SetIdleChanShow Invalid mode. VmpID:%d, Mode:%d.\n", m_wVmpID, emShowMode));
		}
		return FALSE;
	}

	u8* pBuf = NULL;
	u32 dwBmpLen = 0;
	FILE* pBmp = NULL;
	if (ums_vmp_defaultpic_mode == emShowMode || ums_vmp_userdefpic_mode == emShowMode)
	{
		pBmp = fopen(szBmpFilePath, "r");
		if (NULL != pBmp)
		{
			fseek(pBmp,0,SEEK_END);
			dwBmpLen = ftell(pBmp);
			fseek(pBmp,0,SEEK_SET);
			pBuf = new u8[dwBmpLen];
			if (NULL != pBuf)
			{
				fread(pBuf,1,dwBmpLen,pBmp);
			}
			else
			{
				MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::SetIdleChanShow New buffer failed.\n"));
				dwBmpLen = 0;
			}
		}
	}

	s32 nRes = Codec_Success;
#ifdef _LINUX12_
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetNoStreamBak VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	nRes = m_cHardMulPic.SetNoStreamBak(dwHardShowMode, pBuf, dwBmpLen);
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetNoStreamBak VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
#endif
	if (NULL != pBmp)
	{
		fclose(pBmp);
	}
	if (NULL != pBuf)
	{
		delete[] pBuf;
	}

	if (Codec_Success != nRes)
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmp::SetIdleChanShow SetNoStreamBak VmpID:%d Error:%d.\n", m_wVmpID, nRes));
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void CUmsVmp::RecvFrame(PFRAMEHDR pFrmHdr, u32 dwContext)
{
	CVmpRcvChan* pcRcvChan = (CVmpRcvChan*)dwContext;
    if (pFrmHdr == NULL || pcRcvChan == NULL)
    {
        MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::RecvFrame VmpID:%d PTFrameHeader:0x%x, dwContext:0x%x.\n", pcRcvChan->UmsVmp()->m_wVmpID, pFrmHdr, dwContext));
        return;
    }
	
	if (!pcRcvChan->Valid())
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::RecvFrame Recive channel is invalid. VmpID:%d\n", pcRcvChan->UmsVmp()->m_wVmpID));
		return ;
	}
	
	TFrameHeader tFrameHdr;
	memset( &tFrameHdr, 0, sizeof(tFrameHdr) );
	
	tFrameHdr.m_dwMediaType = pFrmHdr->m_byMediaType;
	tFrameHdr.m_dwFrameID   = pFrmHdr->m_dwFrameID;
    tFrameHdr.m_dwSSRC      = pFrmHdr->m_dwSSRC;
	tFrameHdr.m_pData       = pFrmHdr->m_pData + pFrmHdr->m_dwPreBufSize; 
	tFrameHdr.m_dwDataSize  = pFrmHdr->m_dwDataSize;
	tFrameHdr.m_tVideoParam.m_bKeyFrame    = pFrmHdr->m_tVideoParam.m_bKeyFrame;
	tFrameHdr.m_tVideoParam.m_wVideoHeight = pFrmHdr->m_tVideoParam.m_wVideoHeight;
	tFrameHdr.m_tVideoParam.m_wVideoWidth  = pFrmHdr->m_tVideoParam.m_wVideoWidth;
	
	pcRcvChan->UmsVmp()->m_cHardMulPic.SetData(pcRcvChan->ChanIndex(), tFrameHdr );
}

void CUmsVmp::VmpCallBack(PTFrameHeader pFrameInfo, void* pContext)
{
	if ( pFrameInfo == NULL || pContext == NULL )
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::VmpCallBack Invalid param.\n"));
		return ;
	}
	
	CVmpSndChan *pcSndChan = (CVmpSndChan*)pContext;
	if (!pcSndChan->Valid())
	{
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmp::VmpCallBack Invalid snd channel.VmpID:%d\n", pcSndChan->UmsVmp()->m_wVmpID));
		return ;
	}

	OspPrintf(pcSndChan->UmsVmp()->m_bShowEnc, FALSE,  "CUmsVmp::VmpCallBack. VmpID:%d\n", pcSndChan->UmsVmp()->m_wVmpID);
	
	FRAMEHDR tTempFrmHdr;
	memset(&tTempFrmHdr, 0x00, sizeof(tTempFrmHdr));
	
	tTempFrmHdr.m_byMediaType  = (u8)pFrameInfo->m_dwMediaType;
	tTempFrmHdr.m_dwFrameID    = pFrameInfo->m_dwFrameID;
	tTempFrmHdr.m_byFrameRate  = FRAME_RATE;                //帧率固定为25帧
	
	tTempFrmHdr.m_pData        = pFrameInfo->m_pData;
	tTempFrmHdr.m_dwDataSize   = pFrameInfo->m_dwDataSize;
	tTempFrmHdr.m_tVideoParam.m_bKeyFrame    = pFrameInfo->m_tVideoParam.m_bKeyFrame;
	tTempFrmHdr.m_tVideoParam.m_wVideoHeight = pFrameInfo->m_tVideoParam.m_wVideoHeight;
	tTempFrmHdr.m_tVideoParam.m_wVideoWidth  = pFrameInfo->m_tVideoParam.m_wVideoWidth;
	
	
	pcSndChan->SndMedia()->Send(&tTempFrmHdr);
}

BOOL32 CUmsVmp::CheckFrame(u16 wMemberIndx)
{
	if ( m_abAddChanFlag[wMemberIndx] )
	{
		TMulPicChnStatis tDecStatis;
		memset(&tDecStatis, 0, sizeof(TMulPicChnStatis));
		CSemInfo::GetSem()->SemIn("m_cHardMulPic.GetDecStatis VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
		m_cHardMulPic.GetDecStatis( wMemberIndx, tDecStatis );
		CSemInfo::GetSem()->SemOut("m_cHardMulPic.GetDecStatis VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
		if ( tDecStatis.m_bWaitKeyFrame	)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL32 CUmsVmp::SetFast()
{
	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetFastUpdata VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	s32 nRet = m_cHardMulPic.SetFastUpdata(0);
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetFastUpdata VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	if (nRet == HARD_MULPIC_OK)
	{
		return TRUE;
	}
	return FALSE;
}

void CUmsVmp::Show()
{
	OspPrintf(TRUE, 0, "create:%d, umsip:"TPIPFORMAT", umsport:%d, local(rcv:%d, snd:%d)\n", 
		m_bAlreadyCreated, Tpu32ToIP(m_dwRcvIP), m_wRcvPort, m_wLocalRcvPort, m_wLocalSndPort);
	OspPrintf(TRUE, 0, "Style:%d, HardStyle:%d, membernum:%d\n", 
		m_tParam.m_tStyleInfo.m_emVmpStyle, m_cStyle.GetHardStyle(), m_tParam.m_tStyleInfo.m_byMemberNum);

	OspPrintf(TRUE, 0, "OutInfo  UmsRtp:%d, EqpRtcp:%d\n", m_cSndChan.UmsPort(), m_cSndChan.EqpPort());

	for ( u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; wIndex ++ )
	{
		if ( !m_abAddChanFlag[wIndex] )
		{
			continue;
		}

		OspPrintf(TRUE, 0, "	index:%d, memberID:%d-%d, merge:%d, UmsRtcp:%d, EqpRtp:%d\n", wIndex,
				m_tParam.m_tStyleInfo.m_atMemberInfo[wIndex].GetHandleOne(), m_tParam.m_tStyleInfo.m_atMemberInfo[wIndex].GetHandleTwo(), m_tParam.m_tStyleInfo.m_atMemberInfo[wIndex].m_bMerged,
				m_acMediaRcv[wIndex].UmsPort(), m_acMediaRcv[wIndex].EqpPort());
	}

	OspPrintf(TRUE, 0, "Encry modle%d, key:%s, SndMediaAddr:%d\n", 
		m_tParam.m_tEncrypt.m_emEncryptModel, m_tParam.m_tEncrypt.m_achEncKey, m_cSndChan.SndMedia());


	OspPrintf(TRUE, 0, "Enc EncType:%d, Hp/Bp:%d, FrameRate:%d, BitRate:%d, W:%d, H:%d\n", 
		m_tEncParam.m_byEncType, m_tEncParam.m_dwProfile, m_tEncParam.m_byFrameRate, m_tEncParam.m_wBitRate,
		m_tEncParam.m_wVideoWidth, m_tEncParam.m_wVideoHeight);
}

BOOL32 CUmsVmp::UpdateSidelineColor( BOOL32 bDefault )
{
	TMulPicColor tBGDColor;
	tBGDColor.RColor = 0;
	tBGDColor.GColor = 0;
	tBGDColor.BColor = 0;

	u8 acSide[UMS_VMP_MAX_RCV] = {0};
	if ( !bDefault )
	{
		memcpy(acSide, m_abyFlag, sizeof(m_abyFlag));
	}

	BOOL32 bUpdate = FALSE;
	TMulPicColor atSlidelineColor[MULPIC_MAX_CHNS];
	for ( u8 byIndx = 0; byIndx < UMS_VMP_MAX_RCV; byIndx++ )
	{
		if ( acSide[byIndx] == 0 )
		{//默认边框
			atSlidelineColor[byIndx].RColor = 255;
			atSlidelineColor[byIndx].GColor = 255;
			atSlidelineColor[byIndx].BColor = 255;
		}
		else
		{//发言边框
			atSlidelineColor[byIndx].RColor = 0;
			atSlidelineColor[byIndx].GColor = 154;
			atSlidelineColor[byIndx].BColor = 0;
			bUpdate = TRUE;
		}
	}

	CSemInfo::GetSem()->SemIn("m_cHardMulPic.SetBGDAndSidelineColor VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);
	m_cHardMulPic.SetBGDAndSidelineColor(tBGDColor,atSlidelineColor, TRUE);
	CSemInfo::GetSem()->SemOut("m_cHardMulPic.SetBGDAndSidelineColor VmpID:%d %s:%d", m_wVmpID, __FILE__, __LINE__);

	return bUpdate;
}


//Protocol_file

void CUmsVmp::SetMediaKey( TTPQTMediaKeyInfo& tSndQ )
{
	EmQtKeyFrequency emFreq;
	switch(tSndQ.m_emKeyFrequency)
	{
	case emTPConfEncFrequencyEveryConf:
		emFreq = EmQtFrequencyEveryConf;
		break;
	case emTPConfEncFrequencyEverySeconds:
		emFreq = EmQtFrequencyEverySeconds;
		break;
	case emTPConfEncFrequencyEveryMinute:
		emFreq = EmQtFrequencyEveryMinutes;
		break;
	default:
		emFreq = EmQtFrequencyEveryConf;
	}
	
	u32 dwQtHandle = m_wQtHandle;
	QtSetMediaKey(dwQtHandle, tSndQ.m_szMediaKey, tSndQ.m_dwKeyLen, emFreq, tSndQ.m_dwQtFlag, tSndQ.m_wIndex);
}
