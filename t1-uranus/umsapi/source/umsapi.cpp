#include "umsapi.h"
#include "umsxmltype.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)
#include "brdwrapper.h"
#endif

CSemInfo* CSemInfo::m_pcSem = NULL;
API void showsem()
{
	CSemInfo::GetSem()->Show();

	return ;
}

API void semlogon()
{
	CSemInfo::GetSem()->LogOn();
	
	return ;
}

API void semlogoff()
{
	CSemInfo::GetSem()->LogOff();
	
	return ;
}

u8 CTpTypeAdpt::GetVidPayloadValue(EmTpVideoFormat emFormat)
{
	switch(emFormat)
	{
	case emTPVH264: return MEDIA_TYPE_H264; break;
	case emTPVH263:	return MEDIA_TYPE_H263; break;
	case emTPVH263plus: return MEDIA_TYPE_H263PLUS;	break;
	case emTPVMPEG4:	return MEDIA_TYPE_MP4; break;
	default:
		break;
	}
	return MEDIA_TYPE_NULL;
}

u8 CTpTypeAdpt::GetAudPayloadValue(EmTpAudioFormat emFormat)
{
	switch(emFormat)
	{
	case emTPAG711a: return MEDIA_TYPE_PCMA; break;
	case emTPAG711u:	return MEDIA_TYPE_PCMU; break;
	case emTPAG722: return MEDIA_TYPE_G722;	break;

	case emTPAG7231: return MEDIA_TYPE_G7231; break;
	case emTPAG728:	return MEDIA_TYPE_G728; break;
	case emTPAG729: return MEDIA_TYPE_G729;	break;

	case emTPAMP3: return MEDIA_TYPE_MP3; break;
	case emTPAG721:	return MEDIA_TYPE_G721; break;
	case emTPAG7221: return MEDIA_TYPE_G7221C;	break;

	case emTPAG719: return MEDIA_TYPE_G719; break;
	case emTPAMpegAACLC:	return MEDIA_TYPE_AACLC; break;
	case emTPAMpegAACLD: return MEDIA_TYPE_AACLD;	break;
	default:
		break;
	}
	return MEDIA_TYPE_NULL;
}

EmTpAudioFormat CTpTypeAdpt::GetAudioFormat( u16 wAFormat )
{
	EmTpAudioFormat emRet = emTPAEnd;
	switch( wAFormat ) 
	{
	case emPAG711a:		emRet = emTPAG711a;		break;
	case emPAG711u:		emRet = emTPAG711u;		break;
	case emPAG722:		emRet = emTPAG722;		break;
	case emPAG7231:		emRet = emTPAG7231;		break;
	case emPAG728:		emRet = emTPAG728;		break;
	case emPAG729:		emRet = emTPAG729;		break;
	case emPAMp3:		    emRet = emTPAMP3;		    break;
	case emPAG7221:       emRet = emTPAG7221;       break;
	case emPAMpegaaclc:		emRet = emTPAMpegAACLC;	    break;
	case emPAMpegaacld:       emRet = emTPAMpegAACLD;       break;
	case emPAG719:		emRet = emTPAG719;		break;
	default:		    emRet = emTPAEnd;         break;
	}
	return emRet;
}


EmDualReason CTpTypeAdpt::GetDualReason(EmTPDualReason emType)
{
	switch( emType ) 
	{
	case emTpDualAccept:
		return emDualAccept;
		break;
	case emTpDualBusy:
		return emDualBusy;
		break;
	case emTpDualPreemptive:
		return emDualPreemptive;
		break;
	case emTpDualPeerReject:
		return emDualPeerReject; 
		break;
	case emTpDualPeerStop:
		return emDualPeerStop;
		break;
	case emTpDualNoVideo:
		return emDualNoVideo;
		break;
	default:
		return emDualPeerReject;
	}
	return emDualPeerReject;
}

EmTPDualReason CTpTypeAdpt::GetDualReason(EmDualReason emType)
{
	switch( emType ) 
	{
	case emDualAccept:
		return emTpDualAccept;
		break;
	case emDualBusy:
		return emTpDualBusy;
		break;
	case emDualPreemptive:
		return emTpDualPreemptive;
		break;
	case emDualPeerReject:
		return emTpDualPeerReject; 
		break;
	case emDualPeerStop:
		return emTpDualPeerStop;
		break;
	case emDualNoVideo:
		return emTpDualNoVideo;
		break;
	default:
		return emTpDualPeerReject;
	}
	return emTpDualPeerReject;
}


u32 CTpTypeAdpt::GetChannelHandle(const EmChannelHandle& emChHandle, u16 wIndex)
{
	return u32(emChHandle + wIndex);
}

void CTpTypeAdpt::GetChannelIndex(u32 dwHandle, EmChannelHandle& emChHandle, u16& wIndex)
{
	if (dwHandle >= em_video_send_handle && dwHandle < em_video_recv_handle)
	{
		emChHandle = em_video_send_handle;
		wIndex = u16(dwHandle - em_video_send_handle);
	}
	else if (dwHandle >= em_video_recv_handle && dwHandle < em_audio_send_handle)
	{
		emChHandle = em_video_recv_handle;
		wIndex = u16(dwHandle - em_video_recv_handle);
	}
	else if (dwHandle >= em_audio_send_handle && dwHandle < em_audio_recv_handle)
	{
		emChHandle = em_audio_send_handle;
		wIndex = u16(dwHandle - em_audio_send_handle);
	}
	else if (dwHandle >= em_audio_recv_handle && dwHandle < em_audio_send_mix_handle)
	{
		emChHandle = em_audio_recv_handle;
		wIndex = u16(dwHandle - em_audio_recv_handle);
	}

	else if (dwHandle == em_audio_send_mix_handle)
	{
		emChHandle = em_audio_send_mix_handle;
		wIndex = 0;
	}
	else if (dwHandle == em_audio_recv_mix_handle)
	{
		emChHandle = em_audio_recv_mix_handle;
		wIndex = 0;
	}
	else if (dwHandle == em_second_vidsnd_handle)
	{
		emChHandle = em_second_vidsnd_handle;
		wIndex = 0;
	}
	else if (dwHandle == em_second_vidrcv_handle)
	{
		emChHandle = em_second_vidrcv_handle;
		wIndex = 0;
	}
	else if (dwHandle == em_second_audsnd_handle)
	{
		emChHandle = em_second_audsnd_handle;
		wIndex = 0;
	}
	else if (dwHandle == em_second_audrcv_handle)
	{
		emChHandle = em_second_audrcv_handle;
		wIndex = 0;
	}
	else
	{
		emChHandle = em_channel_handle_end;
		wIndex = TP_INVALID_INDEX;
	}
}

BOOL32 CTpTypeAdpt::IsDualChannel(u32 dwChanHandle)
{
	if (em_second_vidsnd_handle <= dwChanHandle && em_channel_handle_end > dwChanHandle)
	{
		return TRUE;
	}
	return FALSE;
}


void CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_info type, u8* pBuf, const TUmsHandle& tHandle, s8* sign)
{
	if(!IsCanPrint(Ums_Mdl_Stack, enLogLowest))
	{
		return;
	}

	tpLowHint(Ums_Mdl_Stack, "%s ConfID:%d, EpID:%d, ChanID:%d \n", sign, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan);
	switch(type)
	{
	case ums_stack_print_makecall:
		{
			TMakeCallPara* pPara = (TMakeCallPara*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s MakeCall->TMakeCallPara Info, BitRate:%d, bIPAlias:%d.\n", sign, pPara->m_tCallInfo.m_wBitRate, pPara->m_tCallInfo.m_tDestAddr.m_bAliasIP);

			tpLowHint(Ums_Mdl_Stack, "  %s aud snd:%d[%s,%s,%s,%s],  vid snd:%d([%s,%s,%d,%d  Dload:%d] [%s,%s,%d,%d])\n", sign, pPara->m_tCapSet.m_wAudEncNum
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[1].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[2].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[3].m_emFormat)
							, pPara->m_tCapSet.m_wVidEncNum, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_emRes), pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_wFrameRate
							, pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_wBitrate, pPara->m_tCapSet.m_tVidSndCap.m_wDynamicPayload
							, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_emRes), pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_wFrameRate
							, pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_wBitrate);

			tpLowHint(Ums_Mdl_Stack, "  %s aud rcv:%d[%s,%s,%s,%s],  vid rcv:%d([%s,%s,%d,%d Dload:%d] [%s,%s,%d,%d]).\n", sign, pPara->m_tCapSet.m_wAudDecNum
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[1].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[2].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[3].m_emFormat)
							, pPara->m_tCapSet.m_wVidDecNum, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_emRes), pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_wFrameRate
							, pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_wBitrate, pPara->m_tCapSet.m_tVidRcvCap.m_wDynamicPayload
							, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_emRes), pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_wFrameRate
							, pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_wBitrate);

			tpLowHint(Ums_Mdl_Stack, "  %s Src Calltype:%d(1:164,2:alias,3:ip), Alias:%s, E164:%s,IP:"IPFORMAT"\n", sign, pPara->m_tCallInfo.m_tSrcAddr.m_byCallType, pPara->m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias
							,pPara->m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias,Tpu32ToIP(pPara->m_tCallInfo.m_tSrcAddr.m_dwIP));
			tpLowHint(Ums_Mdl_Stack, "  %s Dst Calltype:%d(1:164,2:alias,3:ip), Alias:%s, E164:%s,IP:"IPFORMAT"\n", sign, pPara->m_tCallInfo.m_tDestAddr.m_byCallType, pPara->m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias
							,pPara->m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(pPara->m_tCallInfo.m_tDestAddr.m_dwIP));

			TTPTransAddr* ptRtpAddr;
			TTPTransAddr* ptBackRtcpAddr;
			TTPTransAddr* ptSmallRtp;
			TTPTransAddr* ptSmallBackRtcp;
			u16 wIndex;
			//视频
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				ptRtpAddr = &pPara->m_tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_tCapSet.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				ptSmallRtp = &pPara->m_tCapSet.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptSmallBackRtcp = &pPara->m_tCapSet.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s vid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT", small rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT"\n", sign, wIndex
						, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)), ADDRNET((*ptSmallRtp)), ADDRNET((*ptSmallBackRtcp)));
							
			}
			//音频
			for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				ptRtpAddr = &pPara->m_tCapSet.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_tCapSet.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;

				tpLowHint(Ums_Mdl_Stack, " %s aud %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, wIndex
								, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
			//混音
			ptRtpAddr = &pPara->m_tCapSet.m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &pPara->m_tCapSet.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			tpLowHint(Ums_Mdl_Stack, " %s audmix %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, 1
								, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			//双流
			TUmsDualCapsetMc* ptDualCap = &pPara->m_tDualCapSet;
			tpLowHint(Ums_Mdl_Stack, "  %s DualInfo MaxBitRate:%d, AudFormat:%s,%s,%s,%s.\n", sign, ptDualCap->m_wMaxBitRate
							, UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[0].m_emFormat)
							, UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[1].m_emFormat)
							, UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[2].m_emFormat)
							, UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[3].m_emFormat));
			
			tpLowHint(Ums_Mdl_Stack, "  %s DualSnd:([%s,%s,%d  Dload:%d] [%s,%s,%d] ).\n", sign, UmsVidProfilePrint(ptDualCap->m_tVidSndCap.m_tHp.m_emQualityLvl)
							, UmsVidResPrint(ptDualCap->m_tVidSndCap.m_tHp.m_emRes), ptDualCap->m_tVidSndCap.m_tHp.m_wFrameRate
							, ptDualCap->m_tVidSndCap.m_wDynamicPayload
							, UmsVidProfilePrint(ptDualCap->m_tVidSndCap.m_tBp.m_emQualityLvl), UmsVidResPrint(ptDualCap->m_tVidSndCap.m_tBp.m_emRes)
							, ptDualCap->m_tVidSndCap.m_tBp.m_wFrameRate);
					
			tpLowHint(Ums_Mdl_Stack, "  %s DualRcv:([%s,%s,%d  Dload:%d] [%s,%s,%d]).\n", sign, UmsVidProfilePrint(ptDualCap->m_tVidRcvCap.m_tHp.m_emQualityLvl)
							, UmsVidResPrint(ptDualCap->m_tVidRcvCap.m_tHp.m_emRes), ptDualCap->m_tVidRcvCap.m_tHp.m_wFrameRate
							, ptDualCap->m_tVidRcvCap.m_wDynamicPayload
							, UmsVidProfilePrint(ptDualCap->m_tVidRcvCap.m_tBp.m_emQualityLvl), UmsVidResPrint(ptDualCap->m_tVidRcvCap.m_tBp.m_emRes)
							, ptDualCap->m_tVidRcvCap.m_tBp.m_wFrameRate);
			//双流视频地址
			ptRtpAddr = &ptDualCap->m_tVidDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &ptDualCap->m_tVidEnc.m_tChanAddr.m_tBackRtcpAddr;
			tpLowHint(Ums_Mdl_Stack, "  %s DualVid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, 1
							, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			//双流音频地址
			ptRtpAddr = &ptDualCap->m_tVidDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &ptDualCap->m_tVidEnc.m_tChanAddr.m_tBackRtcpAddr;
			tpLowHint(Ums_Mdl_Stack, "  %s DualAud %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, 1
						, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
		}
		break;

	case ums_stack_print_answercall:
		{
			TMakeCallPara* pPara = (TMakeCallPara*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s AnswerCall->TMakeCallPara Info, BitRate:%d.\n", sign, pPara->m_tCallInfo.m_wBitRate);
			tpLowHint(Ums_Mdl_Stack, "  %s Src:(%d->%s), Alias:%s,E164:%s,IP:"TPIPFORMAT" ", sign, TpEnumIdString(EmTpAliasType, pPara->m_tCallInfo.m_tSrcAddr.m_byCallType), pPara->m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias
						,pPara->m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias, Tpu32ToIP(pPara->m_tCallInfo.m_tSrcAddr.m_dwIP));

			tpLowHint(Ums_Mdl_Stack, "  %s Dst:(%d->%s), Alias:%s,E164:%s,IP:"TPIPFORMAT" \n", sign, TpEnumIdString(EmTpAliasType, pPara->m_tCallInfo.m_tDestAddr.m_byCallType), pPara->m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias
						,pPara->m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(pPara->m_tCallInfo.m_tDestAddr.m_dwIP));
			
			tpLowHint(Ums_Mdl_Stack, "  %s aud snd:%d[%s,%s,%s,%s], vid snd:%d([%s,%s,%d Dload:%d] [%s,%s,%d]).\n", sign, pPara->m_tCapSet.m_wAudEncNum
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[1].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[2].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudSndCap.m_atAudFmt[3].m_emFormat)
						, pPara->m_tCapSet.m_wVidEncNum, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_emQualityLvl)
						, UmsVidResPrint(pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_emRes), pPara->m_tCapSet.m_tVidSndCap.m_tHp.m_wFrameRate
						, pPara->m_tCapSet.m_tVidSndCap.m_wDynamicPayload
						, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_emQualityLvl), UmsVidResPrint(pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_emRes)
						, pPara->m_tCapSet.m_tVidSndCap.m_tBp.m_wFrameRate);

			tpLowHint(Ums_Mdl_Stack, "  %s aud rcv:%d[%s,%s,%s,%s], vid rcv:%d([%s,%s,%d  Dload:%d] [%s,%s,%d]).\n", sign, pPara->m_tCapSet.m_wAudDecNum
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[1].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[2].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tCapSet.m_tAudRcvCap.m_atAudFmt[3].m_emFormat)
						, pPara->m_tCapSet.m_wVidDecNum	, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_emQualityLvl)
						, UmsVidResPrint(pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_emRes), pPara->m_tCapSet.m_tVidRcvCap.m_tHp.m_wFrameRate
						, pPara->m_tCapSet.m_tVidRcvCap.m_wDynamicPayload
						, UmsVidProfilePrint(pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_emQualityLvl)
						, UmsVidResPrint(pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_emRes), pPara->m_tCapSet.m_tVidRcvCap.m_tBp.m_wFrameRate);

			TTPTransAddr* ptRtpAddr;
			//TTPTransAddr* ptRtcpAddr;
			TTPTransAddr* ptBackRtcpAddr;
			u16 wIndex;
			//主流视频地址
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				ptRtpAddr = &pPara->m_tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_tCapSet.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s vid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, wIndex
								, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
			//主流音频地址
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				ptRtpAddr = &pPara->m_tCapSet.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_tCapSet.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s vid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, wIndex
								, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
			//主流混音地址
			ptRtpAddr = &pPara->m_tCapSet.m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &pPara->m_tCapSet.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			tpLowHint(Ums_Mdl_Stack, "%s audmix %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, 1, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));

			TUmsDualCapsetMc* ptDualCap = &pPara->m_tDualCapSet;
			tpLowHint(Ums_Mdl_Stack, "  %s DualInfo MaxBitRate:%d, AudFormat:%s,%s,%s,%s\n", sign, ptDualCap->m_wMaxBitRate, 
				UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[0].m_emFormat), UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[1].m_emFormat),
				UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[2].m_emFormat), UmsAudFormatPrint(ptDualCap->m_tAudCap.m_atAudFmt[3].m_emFormat));
			//双流视频地址
			ptRtpAddr = &ptDualCap->m_tVidDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &ptDualCap->m_tAudEnc.m_tChanAddr.m_tBackRtcpAddr;
			tpLowHint(Ums_Mdl_Stack, "  %s DualVid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, 1, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			//双流视频地址
			ptRtpAddr = &ptDualCap->m_tAudDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &ptDualCap->m_tAudEnc.m_tChanAddr.m_tRtpAddr;
			tpLowHint(Ums_Mdl_Stack, "  %s DualAud %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign, 1, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
		}
		break;

	case ums_stack_print_makesenddual:
		{
			TUmsNodeCapset* pPara = (TUmsNodeCapset*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s MakeSendDual Info:\n", sign);
			
			tpLowHint(Ums_Mdl_Stack, "  %s aud snd:(%s,%s,%s,%s) vid snd([%s,%s,%d,%d, Dload:%d] [%s,%s,%d,%d]).\n", sign
							, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[0].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[1].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[2].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[3].m_emFormat)
							, UmsVidProfilePrint(pPara->m_tVidSndCap.m_tHp.m_emQualityLvl), UmsVidResPrint(pPara->m_tVidSndCap.m_tHp.m_emRes)
							, pPara->m_tVidSndCap.m_tHp.m_wFrameRate, pPara->m_tVidSndCap.m_tHp.m_wBitrate, pPara->m_tVidSndCap.m_wDynamicPayload
							, UmsVidProfilePrint(pPara->m_tVidSndCap.m_tBp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tVidSndCap.m_tBp.m_emRes), pPara->m_tVidSndCap.m_tBp.m_wFrameRate, pPara->m_tVidSndCap.m_tBp.m_wBitrate);
			
			tpLowHint(Ums_Mdl_Stack, "  %s aud rcv:(%s,%s,%s,%s) vid rcv:([%s,%s,%d,%d  Dload:%d] [%s,%s,%d,%d]).\n", sign
							, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[0].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[1].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[2].m_emFormat)
							, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[3].m_emFormat)
							, UmsVidProfilePrint(pPara->m_tVidRcvCap.m_tHp.m_emQualityLvl), UmsVidResPrint(pPara->m_tVidRcvCap.m_tHp.m_emRes)
							, pPara->m_tVidRcvCap.m_tHp.m_wFrameRate, pPara->m_tVidRcvCap.m_tHp.m_wBitrate, pPara->m_tVidRcvCap.m_wDynamicPayload
							, UmsVidProfilePrint(pPara->m_tVidRcvCap.m_tBp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tVidRcvCap.m_tBp.m_emRes), pPara->m_tVidRcvCap.m_tBp.m_wFrameRate, pPara->m_tVidRcvCap.m_tBp.m_wBitrate);

			TTPTransAddr* ptRtpAddr;
			TTPTransAddr* ptRtcpAddr;
			TTPTransAddr* ptBackRtcpAddr;
			u16 wIndex;
			//双流视频
			for (wIndex = 0; wIndex < pPara->m_wVidEncNum; wIndex++)
			{
				ptRtpAddr = &pPara->m_atVidEnc[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcpAddr = &pPara->m_atVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcpAddr = &pPara->m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s vsnd %d, ID:%d, RTP:"ADDRPORT_FORMAT" RTCP:"ADDRPORT_FORMAT" \n"
					, sign, wIndex, pPara->m_atVidEnc[wIndex].m_tPAHandle, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}

			for (wIndex = 0; wIndex < pPara->m_wAudEncNum; wIndex++)
			{
				ptRtpAddr = &pPara->m_atAudEnc[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcpAddr = &pPara->m_atAudEnc[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcpAddr = &pPara->m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s asnd %d, ID:%d, RTP:"ADDRPORT_FORMAT" RTCP:"ADDRPORT_FORMAT" \n"
					, sign, wIndex, pPara->m_atAudEnc[wIndex].m_tPAHandle, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
			for (wIndex = 0; wIndex < pPara->m_wAudDecNum; wIndex++)
			{
				ptRtpAddr = &pPara->m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcpAddr = &pPara->m_atAudDec[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcpAddr = &pPara->m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s arcv %d, ID:%d, RTP:"ADDRPORT_FORMAT" RTCP:"ADDRPORT_FORMAT" \n"
					, sign, wIndex, pPara->m_atAudDec[wIndex].m_tPAHandle, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
		}
		break;
	case ums_stack_print_channelconnect:
		{
			BOOL32 bIsIn = strcmp(sign, INSIGN) == 0;
			tpLowHint(Ums_Mdl_Stack, "%s channel connect Info:\n", sign);

			TUmsNodeCapset* pPara = (TUmsNodeCapset*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "  %s aud snd:%d(%s,%s,%s,%s), vid snd:%d([%s,%s,%d,%d Dload:%d] [%s,%s,%d,%d]).\n", sign, pPara->m_wAudEncNum
						, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[0].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[1].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[2].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tAudSndCap.m_atAudFmt[3].m_emFormat)
						, pPara->m_wVidEncNum, UmsVidProfilePrint(pPara->m_tVidSndCap.m_tHp.m_emQualityLvl), UmsVidResPrint(pPara->m_tVidSndCap.m_tHp.m_emRes)
						, pPara->m_tVidSndCap.m_tHp.m_wFrameRate, pPara->m_tVidSndCap.m_tHp.m_wBitrate, pPara->m_tVidSndCap.m_wDynamicPayload
						, UmsVidProfilePrint(pPara->m_tVidSndCap.m_tBp.m_emQualityLvl)
						, UmsVidResPrint(pPara->m_tVidSndCap.m_tBp.m_emRes), pPara->m_tVidSndCap.m_tBp.m_wFrameRate, pPara->m_tVidSndCap.m_tBp.m_wBitrate);
				
			tpLowHint(Ums_Mdl_Stack, "  %s aud rcv:%d(%s,%s,%s,%s), vid rcv:%d([%s,%s,%d,%d Dload:%d] [%s,%s,%d,%d]).\n", sign, pPara->m_wAudDecNum
						, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[0].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[1].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[2].m_emFormat)
						, UmsAudFormatPrint(pPara->m_tAudRcvCap.m_atAudFmt[3].m_emFormat)
						, pPara->m_wVidDecNum, UmsVidProfilePrint(pPara->m_tVidRcvCap.m_tHp.m_emQualityLvl), UmsVidResPrint(pPara->m_tVidRcvCap.m_tHp.m_emRes)
						, pPara->m_tVidRcvCap.m_tHp.m_wFrameRate, pPara->m_tVidRcvCap.m_tHp.m_wBitrate, pPara->m_tVidRcvCap.m_wDynamicPayload
						, UmsVidProfilePrint(pPara->m_tVidRcvCap.m_tBp.m_emQualityLvl)
						, UmsVidResPrint(pPara->m_tVidRcvCap.m_tBp.m_emRes), pPara->m_tVidRcvCap.m_tBp.m_wFrameRate, pPara->m_tVidRcvCap.m_tBp.m_wBitrate);

			TTPTransAddr* ptRtpAddr;
/*			TTPTransAddr* ptRtcpAddr;*/
			TTPTransAddr* ptBackRtcpAddr;

			TTPTransAddr* ptSmallRtpAddr;
			TTPTransAddr* ptSmallRtcpAddr;
			u16 wIndex;
			//视频
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				if (!pPara->m_atVidEnc[wIndex].m_bIsChanOn && bIsIn)
				{
					continue;
				}

				ptRtpAddr = &pPara->m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				ptSmallRtpAddr = &pPara->m_atSmallVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				ptSmallRtcpAddr = &pPara->m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s vid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" small rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT"\n", sign
								, wIndex, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)), ADDRNET((*ptSmallRtpAddr)), ADDRNET((*ptSmallRtcpAddr)));

			}
			//音频
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
			{
				if (!pPara->m_atAudEnc[wIndex].m_bIsChanOn && bIsIn)
				{
					continue;
				}

				ptRtpAddr = &pPara->m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s aud %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign
								, wIndex, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
			//混音

			ptRtpAddr = &pPara->m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
			ptBackRtcpAddr = &pPara->m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			tpLowHint(Ums_Mdl_Stack,  "%s audmix, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign
				, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));

			//小码流
// 			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
// 			{
// 				ptRtpAddr = &pPara->m_atSmallVid[wIndex][TP_STREAM_LEFT].m_tChanAddr.m_tRtpAddr;
// 			
// 				if (ptRtpAddr->m_dwIP != 0)
// 				{
// 					tpLowHint(Ums_Mdl_Stack, "%s, smallVid(L): RTP:"ADDRPORT_FORMAT".\n", sign, ADDRNET((*ptRtpAddr)));
// 				}
// 
// 				ptRtpAddr = &pPara->m_atSmallVid[wIndex][TP_STRAEM_RIGHT].m_tChanAddr.m_tRtpAddr;
// 				if (ptRtpAddr->m_dwIP != 0)
// 				{
// 					tpLowHint(Ums_Mdl_Stack, "%s, smallVid(R): RTP:"ADDRPORT_FORMAT".\n", sign, ADDRNET((*ptRtpAddr)));
// 				}
// 			}
		}
		break;
	case ums_stack_print_makechan:
		{
			TUmsNodeCapset* pPara = (TUmsNodeCapset*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s MakeChan->TMakeChan Info:\n", sign);

			tpLowHint(Ums_Mdl_Stack, "  %s aud snd:%d, vid snd:%d([%s,%s,%d] [%s,%s,%d]).\n", sign, pPara->m_wAudEncNum, pPara->m_wVidEncNum
							, UmsVidProfilePrint(pPara->m_tVidSndCap.m_tHp.m_emQualityLvl), UmsVidResPrint(pPara->m_tVidSndCap.m_tHp.m_emRes)
							, pPara->m_tVidSndCap.m_tHp.m_wFrameRate, UmsVidProfilePrint(pPara->m_tVidSndCap.m_tBp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tVidSndCap.m_tBp.m_emRes), pPara->m_tVidSndCap.m_tBp.m_wFrameRate);

			tpLowHint(Ums_Mdl_Stack, "  %s aud rcv:%d, vid rcv:%d([%s,%s,%d]	[%s,%s,%d]).\n", sign, pPara->m_wAudDecNum, pPara->m_wVidDecNum
							, UmsVidProfilePrint(pPara->m_tVidRcvCap.m_tHp.m_emQualityLvl), UmsVidResPrint(pPara->m_tVidRcvCap.m_tHp.m_emRes)
							, pPara->m_tVidRcvCap.m_tHp.m_wFrameRate, UmsVidProfilePrint(pPara->m_tVidRcvCap.m_tBp.m_emQualityLvl)
							, UmsVidResPrint(pPara->m_tVidRcvCap.m_tBp.m_emRes), pPara->m_tVidRcvCap.m_tBp.m_wFrameRate);

			TTPTransAddr* ptRtpAddr;
//			TTPTransAddr* ptRtcpAddr;
			TTPTransAddr* ptBackRtcpAddr;
			u16 wIndex;

			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				ptRtpAddr = &pPara->m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptBackRtcpAddr = &pPara->m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				tpLowHint(Ums_Mdl_Stack, " %s vid %d, rcvRTP:"ADDRPORT_FORMAT" sndRTCP:"ADDRPORT_FORMAT" \n", sign
								, wIndex, ADDRNET((*ptRtpAddr)), ADDRNET((*ptBackRtcpAddr)));
			}
		}
		break;
	case ums_stack_print_ConfEpCallInfo:
		{
			TConfNodeCallUpdateTrList* pList = (TConfNodeCallUpdateTrList*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s TConfNodeTr CallInfo Num:%d\n", sign, pList->m_wNum);
			for (u16 wIndex = 0; wIndex < pList->m_wNum; ++wIndex)
			{
				TConfNodeCallUpdateTr& tTemp = pList->m_atList[wIndex];
				tpLowHint(Ums_Mdl_Stack, "  %s Index:%d, EpId:%d, Called:Alias:%s,E164:%s,IP:"TPIPFORMAT", confName:%s, type:%d, callstate:%d\n", sign, wIndex+1, tTemp.m_wEpID
							, tTemp.m_tCalledAddr.m_tAlias.m_abyAlias, tTemp.m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(tTemp.m_tCalledAddr.m_dwIP), tTemp.m_tConfName.m_abyAlias, tTemp.m_emEpType, tTemp.m_emCallState);
			}

		}
		break;
	case ums_stack_print_ConfEpChanInfo:
		{
			TConfNodeChanUpdateTrList* pList = (TConfNodeChanUpdateTrList*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s TConfNodeTr ChanInfo Num:%d\n", sign, pList->m_wNum);
			for (u16 wIndex = 0; wIndex < pList->m_wNum; wIndex++)
			{
				TConfNodeChanUpdateTr& tTmp = pList->m_atList[wIndex];
				tpLowHint(Ums_Mdl_Stack, "  %s Index:%d, EpId:%d, chanstate:%d, num(vs:%d,vr:%d,as:%d,ar:%d), vidFormat:(%s,%s,%d,%d)\n", sign
							, wIndex+1, tTmp.wEpID, tTmp.bChanOpen, tTmp.wVidSnd, tTmp.wVidRcv, tTmp.wAudSnd, tTmp.wAudRcv
							, UmsVidProfilePrint(tTmp.tVidSnd.m_emQualityLvl), UmsVidResPrint(tTmp.tVidSnd.m_emRes)
							, tTmp.tVidSnd.m_wFrameRate, tTmp.tVidSnd.m_wBitrate);
			}
		}
		break;
	case ums_stack_print_ConfEpIDInfo:
		{
			TConfNodeDelTrList* pList = (TConfNodeDelTrList*)pBuf;
			tpLowHint(Ums_Mdl_Stack, "%s TConf DeleteNodeTr id Num:%d\n", sign, pList->m_wNum);
			for (u16 wIndex = 0; wIndex < pList->m_wNum; ++wIndex)
			{
				tpLowHint(Ums_Mdl_Stack, "  %s wIndex:%d, KeyID:%d\n", sign, wIndex+1, pList->m_atList[wIndex].m_wEpID);
			}
		}
		break;
		
	case ums_stack_print_CallIncoming:
		{
			TUmsCallInfo* ptCallInfo = (TUmsCallInfo*)pBuf;
			TTPConfTemplate* ptTemp = (TTPConfTemplate*)(pBuf + sizeof(TUmsCallInfo));

			tpLowHint(Ums_Mdl_Stack, " %s EndPointType:%d,  Ver:%d.\n", 
					  sign, ptCallInfo->m_emSrcEpType, ptCallInfo->m_byVer);
			if (ptTemp->m_atEpList.m_wNum > 0)
			{
				tpLowHint(Ums_Mdl_Stack, "  %s CreatConf Num:%d, ConfInfo(vid<%s,%s,%d>, DualVid<%s,%s,%d>).\n", sign, ptTemp->m_atEpList.m_wNum
								, UmsVidProfilePrint(ptTemp->m_atTpMainVideoRes[0].m_emQualityLvl), UmsVidResPrint(ptTemp->m_atTpMainVideoRes[0].m_emRes)
								, ptTemp->m_atTpMainVideoRes[0].m_wFrameRate, UmsVidProfilePrint(ptTemp->m_atTpMinorVideoRes[0].m_emQualityLvl)
								, UmsVidResPrint(ptTemp->m_atTpMinorVideoRes[0].m_emRes), ptTemp->m_atTpMinorVideoRes[0].m_wFrameRate);
			}
		}
		break;
	}
}


#ifdef _LINUX_
BOOL tpPathExist(const s8* path)
{
	s8  achCurPath[256] ={0};
	s8* pStr = getcwd(achCurPath,sizeof(achCurPath));
	if(NULL == pStr) return FALSE;
	BOOL bRet = (chdir(path) >= 0);
	chdir(achCurPath);
	return bRet;
}
#endif

BOOL TpMakeDir(const s8* path )
{
	int nRet = 0;
	
#ifdef WIN32
	nRet = CreateDirectory( path, 0 );
	if(nRet != 1)                 
	{
		printf("%s created failled,error no. = %d\n", path, nRet);
	}
	else
	{
		printf("%s created success\n", path);
	}
	return TRUE;
#endif
#ifdef _VXWORKS_
	nRet = mkdir( path  );
#endif
#ifdef _LINUX_
	if(tpPathExist(path)) return FALSE;
	
	nRet = mkdir(path,  S_IRUSR//文件所有者具可读取权限
		|S_IWUSR//文件所有者具可写入权限
		    	 |S_IXUSR//文件所有者具可执行权限
				 |S_IRGRP// 用户组具可读取权限
				 |S_IWGRP//用户组具可写入权限
				 |S_IXGRP//用户组具可执行权限
				 |S_IROTH//其他用户具可读取权限
				 |S_IWOTH//其他用户具可写入权限
				 |S_IXOTH);//他用户具可执行权限
#endif
	if(nRet != 0)                 
	{
		printf("%s created failled,error no. = %d\n",path,nRet);
		OspPrintf(TRUE, FALSE, "%s created failled,error no. = %d\n",path,nRet);
	}
	else
	{
		printf("%s created success\n",path);
		OspPrintf(TRUE, FALSE, "%s created success\n",path);
	}	
	return TRUE;
}


#ifdef _LINUX_
#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#endif


u32 CTpTypeAdpt::GetLocalIP( u8 byIndex, u8 bySubIndex /*= 1*/ )
{
	u32 dwLocalIP = 0;
#if defined(WIN32)

    u32 adwLocalIP[2] = {0};
    if( OspAddrListGet( adwLocalIP, 2 ) == 0 )
	{
        dwLocalIP = 0;
	}
    else
    {
        if(adwLocalIP[0] == inet_addr("127.0.0.1"))
            dwLocalIP = adwLocalIP[1];
        else
            dwLocalIP = adwLocalIP[0];
    }

#else

	if (0 == bySubIndex)
	{// 用途：网口配置了多个ip的情形下，子索引用于标识获取第几个，子索引从1开始
		msgprint("CTpTypeAdpt::GetLocalIP byIndex:%d, bySubIndex:%d, bySubIndex should more than zero!!!\n", 
			byIndex, bySubIndex);
		return 0;
	}

	register int fd, intrface, loopnum;
	struct ifreq buf[16];
	struct ifconf ifc;
	s8* pEth = NULL;
	u8 byFindSubIndex = 0;
  
	//IS2.2的板子是geth0,其余的板子是feth0
    if (byIndex == 0)
    {
        pEth = "eth0";
    }
    else
    {
        pEth = "eth1";
    }
	
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0)
	{
		ifc.ifc_len = sizeof buf;
		ifc.ifc_buf = (caddr_t) buf;
		if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc))
		{
			//获取接口信息
			loopnum = ifc.ifc_len / sizeof (struct ifreq);
			intrface = 0;
			//根据接口信息循环获取设备IP
			while (intrface < loopnum)
			{
				if (strstr(buf[intrface].ifr_name, pEth) == NULL)
				{
					intrface++;
					continue;
				}
				
				struct ifreq ifr;
				strncpy(ifr.ifr_name, buf[intrface].ifr_name, IFNAMSIZ-1);
				if (!ioctl (fd, SIOCGIFFLAGS, (char*)&ifr))
				{
					if ((ifr.ifr_flags & IFF_UP) == 0)
					{//网口被禁用, UMS需要使用次限制
						break;
					}
				}
				else
				{
					break;
				}
				
				//获取当前网卡的IP地址
				if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))
				{
					byFindSubIndex++;
					if (byFindSubIndex < bySubIndex)
					{
						intrface++;
						continue;
					}
					// 找到此网口的第bySubIndex个ip，则跳出循环返回
					dwLocalIP = ((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr.s_addr;
					break;
				}

				intrface++;
			}
		}

		close (fd);
	}
	msgprint("CTpTypeAdpt::GetLocalIP byIndex:%d, bySubIndex:%d, byFindSubIndex:%d, LocalIp:"IPFORMAT".\n", 
			byIndex, bySubIndex, byFindSubIndex, Tpu32ToIP(dwLocalIP));
#endif
	return dwLocalIP;
}

u32 CTpTypeAdpt::GetLocalIPPerfer( u8 byIndex, u8 bySubIndex )
{
	if (1 == bySubIndex || 0 == bySubIndex)
	{
		return GetLocalIP(byIndex);
	}

	u32 dwLocalIp = GetLocalIP(byIndex, bySubIndex);
	if (0 == dwLocalIp)
	{
		dwLocalIp = GetLocalIP(byIndex);
	}
	return dwLocalIp;
}

u32 CTpTypeAdpt::GetLocalNetMask( u8 byIndex, u8 bySubIndex /*= 1*/ )
{
	u32 dwNetMask = 0;
#if defined(WIN32)
	return 0;
#else
	
	if (0 == bySubIndex)
	{// 用途：网口配置了多个ip的情形下，子索引用于标识获取第几个，子索引从1开始
		msgprint("CTpTypeAdpt::GetLocalNetMask byIndex:%d, bySubIndex:%d, bySubIndex should more than zero!!!\n", 
			byIndex, bySubIndex);
		return 0;
	}

	register int fd, intrface, loopnum;
	struct ifreq buf[16];
	struct ifconf ifc;
	s8* pEth = NULL;
	u8 byFindSubIndex = 0;
	
	//IS2.2的板子是geth0,其余的板子是feth0
	if (byIndex == 0)
	{
		pEth = "eth0";
	}
	else
	{
		pEth = "eth1";
	}
	
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0)
	{
		ifc.ifc_len = sizeof buf;
		ifc.ifc_buf = (caddr_t) buf;
		if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc))
		{
			//获取接口信息
			loopnum = ifc.ifc_len / sizeof (struct ifreq);
			intrface = 0;
			//根据接口信息循环获取设备IP
			while (intrface < loopnum)
			{
				if (strstr(buf[intrface].ifr_name, pEth) == NULL)
				{
					intrface++;
					continue;
				}
				
				struct ifreq ifr;
				strncpy(ifr.ifr_name, buf[intrface].ifr_name, IFNAMSIZ-1);
				if (!ioctl (fd, SIOCGIFFLAGS, (char*)&ifr))
				{
					if ((ifr.ifr_flags & IFF_UP) == 0)
					{//网口被禁用, UMS需要使用次限制
						break;
					}
				}
				else
				{
					break;
				}

				//获取当前网卡的NetMask
				if (!(ioctl (fd, SIOCGIFNETMASK, (char *) &buf[intrface])))
				{
					byFindSubIndex++;
					if (byFindSubIndex < bySubIndex)
					{
						intrface++;
						continue;
					}
					// 找到此网口的第bySubIndex个ip，则跳出循环返回
					dwNetMask = ((struct sockaddr_in*)(&buf[intrface].ifr_netmask))->sin_addr.s_addr;
					break;
				}

				intrface++;
			}
		}
		
		close (fd);
	}
	msgprint("CTpTypeAdpt::GetLocalNetMask byIndex:%d, bySubIndex:%d, byFindSubIndex:%d, NetMask:"IPFORMAT".\n", 
			byIndex, bySubIndex, byFindSubIndex, Tpu32ToIP(dwNetMask));
#endif
	return dwNetMask;
}
void CTpTypeAdpt::GetLocalMacAddr(u8 byIndex,  u8* pszMacAddr)
{
   #if defined(WIN32)
	  return ;
   #else
	if (pszMacAddr == NULL)
	{
		return;
	}
	struct ifreq ifreq;
	int sock;
	s8* pEth = NULL;

	if (byIndex == 0)
	{
		pEth = "eth0";
	}
	else
	{
		pEth = "eth1";
	}
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror ("socket");
		return ;
	}
	strcpy (ifreq.ifr_name, pEth);    

	if (ioctl (sock, SIOCGIFHWADDR, &ifreq) < 0)
	{
		perror ("ioctl");
		return ;
	}
    memcpy(pszMacAddr,ifreq.ifr_hwaddr.sa_data,sizeof(ifreq.ifr_hwaddr.sa_data));
#endif
	return ;

}
u32 CTpTypeAdpt::GetLocalNetMaskPerfer( u8 byIndex, u8 bySubIndex )
{
	if (1 == bySubIndex || 0 == bySubIndex)
	{
		return GetLocalNetMask(byIndex);
	}
	u32 dwNetMask = GetLocalNetMask(byIndex, bySubIndex);
	if (0 == dwNetMask)
	{
		dwNetMask = GetLocalNetMask(byIndex);
	}
	return dwNetMask;
}

void CTpTypeAdpt::GetWHByVidResolution( EmTpVideoResolution emResolution, u16 &wWidth, u16 &wHeight )
{
	wWidth = 352;
	wHeight = 288;

	switch( emResolution )
	{
	case emTPVResEnd:
		wWidth = 0;
		wHeight = 0;		
		break;

	case emTPVResolutionAuto: // Only Mpeg4
		wWidth = 0;
		wHeight = 0;		
		break;

	case emTPVSQCIF:
		wWidth = 88;
		wHeight = 72;
		break;

	case emTPVQCIF:
		wWidth = 176;
		wHeight = 144;
		break;
		
	case emTPVCIF:
		wWidth = 352;
		wHeight = 288;
		break;
		
	case emTPV2CIF:
		wWidth = 352;
		wHeight = 576;
		break;

	case emTPV4CIF:
		wWidth = 704;
		wHeight = 576;
		break;

	case emTPV16CIF:
		wWidth = 1408;
		wHeight = 1152;
		break;

	case emTPVHD480i720x480:
		wWidth = 720;
		wHeight = 480;
		break;

	case emTPVHD480p720x480:
		wWidth = 720;
		wHeight = 480;
		break;

	case emTPVHD576i720x576:
		wWidth = 720;
		wHeight = 576;
		break;

	case emTPVHD576p720x576:
		wWidth = 720;
		wHeight = 576;
		break;

	case emTPVHD720p1280x720:
		wWidth = 1280;
		wHeight = 720;
		break;
		
	case emTPVHD1080i1920x1080:
		wWidth = 1920;
		wHeight = 544;
		break;

	case emTPVHD1080p1920x1080:
		wWidth = 1920;
		wHeight = 1080;
		break;	

	case emTPVGA352x240:
		wWidth = 352;
		wHeight = 240;
		break;
		
	case emTPVGA704x480:
		wWidth = 704;
		wHeight = 480;
		break;
		
	case emTPVGA640x480:
		wWidth = 640;
		wHeight = 480;
		break;
		
	case emTPVGA800x600:
		wWidth = 800;
		wHeight = 600;
		break;
		
	case emTPVGA1024x768:
		wWidth = 1024;
		wHeight = 768;
		break;

	case emTPVGA1280x768:
		wWidth = 1280;
		wHeight = 768;
		break;
	case emTPVGA1280x800:
		wWidth = 1280;
		wHeight = 800;
		break;

	case emTPVGA1366x768:
		wWidth = 1366;
		wHeight = 768;
		break;
	case emTPVGA1280x854:
		wWidth = 1280;
		wHeight = 854;
		break;

	case emTPVGA1440x900:
		wWidth = 1440;
		wHeight = 900;
		break;

	case emTPVGA1280x1024:
		wWidth = 1280;
		wHeight = 1024;
		break;

	case emTPVGA1680x1050:
		wWidth = 1680;
		wHeight = 1050;
		break;

	case emTPVGA1600x1200:
		wWidth = 1600;
		wHeight = 1200;
		break;

	case emTPVGA1920x1200:
		wWidth = 1920;
		wHeight = 1200;
		break;

	case emTPVSQCIF112x96:
		wWidth = 112;
		wHeight = 96;
		break;

	case emTPVSQCIF96x80:
		wWidth = 96;
		wHeight = 80;
		break;

	case emTPV320x192:
		wWidth = 320;
		wHeight = 192;
		break;

	case emTPV432x240:
		wWidth = 432;
		wHeight = 240;
		break;

	case emTPV480x272:
		wWidth = 480;
		wHeight = 272;
		break;

	case emTPV640x368:
		wWidth = 640;
		wHeight = 368;
		break;

	case emTPV864x480:
		wWidth = 864;
		wHeight = 480;
		break;

	case emTPV960x544:
		wWidth = 964;
		wHeight = 544;
		break;

	case emTPV1440x816:
		wWidth = 1440;
		wHeight = 816;
		break;
	}
}

BOOL32 CTpTypeAdpt::ResolutionSmallOpr( EmTpVideoResolution emLeft, EmTpVideoResolution emRight )
{
	u16 wLeftWidth = 0;
	u16 wLeftHeight = 0;

	u16 wRightWidth = 0;
	u16 wRightHeight = 0;

	GetWHByVidResolution(emLeft, wLeftWidth, wLeftHeight);
	GetWHByVidResolution(emRight, wRightWidth, wRightHeight);

	return (wLeftWidth * wLeftHeight) < (wRightWidth * wRightHeight);
}

BOOL32 CTpTypeAdpt::ResolutionEqualOpr( EmTpVideoResolution emLeft, EmTpVideoResolution emRight )
{
	u16 wLeftWidth = 0;
	u16 wLeftHeight = 0;
	
	u16 wRightWidth = 0;
	u16 wRightHeight = 0;
	
	GetWHByVidResolution(emLeft, wLeftWidth, wLeftHeight);
	GetWHByVidResolution(emRight, wRightWidth, wRightHeight);
	
	return (wLeftWidth * wLeftHeight) == (wRightWidth * wRightHeight);
}
BOOL32 CTpTypeAdpt::ResolutionMaxOpr( EmTpVideoResolution emLeft, EmTpVideoResolution emRight )
{
	u16 wLeftWidth = 0;
	u16 wLeftHeight = 0;
	
	u16 wRightWidth = 0;
	u16 wRightHeight = 0;
	
	GetWHByVidResolution(emLeft, wLeftWidth, wLeftHeight);
	GetWHByVidResolution(emRight, wRightWidth, wRightHeight);
	
	return (wLeftWidth * wLeftHeight) > (wRightWidth * wRightHeight);
}

BOOL32 CTpTypeAdpt::CapMaxOpr( TUmsVidFormat* ptLeft, TUmsVidFormat* ptRight )
{
	u16 wLeftWidth = 0;
	u16 wLeftHeight = 0;
	
	u16 wRightWidth = 0;
	u16 wRightHeight = 0;
	
	GetWHByVidResolution(ptLeft->m_emRes, wLeftWidth, wLeftHeight);
	GetWHByVidResolution(ptRight->m_emRes, wRightWidth, wRightHeight);
	
	return (wLeftWidth * wLeftHeight * ptLeft->m_wFrameRate) > (wRightWidth * wRightHeight * ptRight->m_wFrameRate);
}

//返回TURE表示需要适配
BOOL32 CTpTypeAdpt::IsVidTransNeedBas(const TUmsVidFormat& tSnd, const TUmsVidFormat& tRcv)
{
	//格式不同 必须适配
	if (tRcv.m_emQualityLvl == tSnd.m_emQualityLvl)
	{
		if ( ResolutionMaxOpr( tSnd.m_emRes, tRcv.m_emRes ) )
		{//如果发送分辨率大于接收分辨率，则适配
			return TRUE;
		}
		else if ( ResolutionSmallOpr( tSnd.m_emRes, tRcv.m_emRes ) )
		{//分辨率小 则肯定不需要适配
			return FALSE;
		}
		
		//发送分辨率小于或等于接收分辨率
		if ( abs(tSnd.m_wFrameRate - tRcv.m_wFrameRate) > 10 )
		{//发送帧率 接收帧率 相差10以外
			if ( tSnd.m_wFrameRate < tRcv.m_wFrameRate )
			{
				return FALSE;
			}
			return TRUE;
		}
		
		return FALSE;
	}

	return TRUE;


	//////////////////////////////////////////////////////////////////////////
	//如果码率相等
	if (tRcv.m_wBitrate >= tSnd.m_wBitrate)
	{
		//格式相同
		if (tRcv.m_emQualityLvl == tSnd.m_emQualityLvl)
		{
			if ( ResolutionMaxOpr( tSnd.m_emRes, tRcv.m_emRes ) )
			{//如果发送分辨率大于接收分辨率，则适配
				return TRUE;
			}

			//发送分辨率小于或等于接收分辨率

			if ( tSnd.m_wFrameRate > tRcv.m_wFrameRate )
			{//发送帧率大于接收帧率，则适配
				return TRUE;
			}
			return FALSE;
		}
		
		//下面格式不同		
		//如果接收是HP，则和发送同等分辨率和帧率时，可以解BP
		if (emTPH264HP == tRcv.m_emQualityLvl)
		{
			if ( ResolutionMaxOpr( tSnd.m_emRes, tRcv.m_emRes ) )
			{//如果发送分辨率大于接收分辨率，则适配
				return TRUE;
			}

			//发送分辨率小于或等于接收分辨率

			if ( tSnd.m_wFrameRate > tRcv.m_wFrameRate )
			{//发送帧率大于接收帧率，则适配
				return TRUE;
			}
			return FALSE;
		}

		//下面是当接收为BP时
		
		if (emTPH264HP == tSnd.m_emQualityLvl)
		{//如果发送是HP，则适配
			return TRUE;
		}

		if ( ResolutionMaxOpr( tSnd.m_emRes, tRcv.m_emRes ) )
		{//发送分辨率大于接收分辨率，则适配
			return TRUE;
		}

		if ( tSnd.m_wFrameRate > tRcv.m_wFrameRate )
		{//发送帧率大于接收帧率，则适配
			return TRUE;
		}
			
		return FALSE;
	}
	else
	{//
		return TRUE;
	}

	return TRUE;
}

const u16 CTpTypeAdpt::GetRcvFormat(const TUmsVidFormat& tRcv, const TUmsVidFormat tSnd[], u16 wNum)
{
	const TUmsVidFormat* ptFormat = NULL;
	u16 wRetIndx = TP_INVALID_INDEX;//返回一个最适合的格式索引

	u16 wRcvWidth, wRcvHeight, wSndWidth, wSndHeight;
	CTpTypeAdpt::GetWHByVidResolution(tRcv.m_emRes, wRcvWidth, wRcvHeight);

	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
		if (tRcv.m_wBitrate < tSnd[wIndex].m_wBitrate - 100 )
		{//适配出来的包含音频
			continue;
		}

		//接收是BP，发送是HP
		if ( tRcv.m_emQualityLvl != tSnd[wIndex].m_emQualityLvl)
		{
			continue;
		}

		CTpTypeAdpt::GetWHByVidResolution(tSnd[wIndex].m_emRes, wSndWidth, wSndHeight);

		if (wRcvWidth*wRcvHeight < wSndWidth*wSndHeight)
		{//分辨率小于tRight
			if (wRcvWidth*wRcvHeight*tRcv.m_wFrameRate < wSndWidth*wSndHeight*tSnd[wIndex].m_wFrameRate)
			{
				continue;
			}
		}
		else if (wRcvWidth*wRcvHeight == wSndWidth*wSndHeight)
		{//分辨率相等
			if (tRcv.m_wFrameRate == tSnd[wIndex].m_wFrameRate)
			{//帧率相等则直接返回
				//return &tRight[wIndex];
				return wIndex;
			}
			else if (tRcv.m_wFrameRate < tSnd[wIndex].m_wFrameRate)
			{//不合法
				if( tSnd[wIndex].m_wFrameRate - tRcv.m_wFrameRate <= 10 )
				{//50和60 25和30 也是可以互转的
					return wIndex; 
				}
				continue;
			}
		}

		if (NULL == ptFormat)
		{
			ptFormat = &tSnd[wIndex];
			wRetIndx = wIndex;
		}
		else
		{//与上一个格式取大值
			if (ResolutionSmallOpr(ptFormat->m_emRes, tSnd[wIndex].m_emRes))
			{
				ptFormat = &tSnd[wIndex];
				wRetIndx = wIndex;
			}
			else if (ResolutionEqualOpr(ptFormat->m_emRes, tSnd[wIndex].m_emRes))
			{
				if (ptFormat->m_wFrameRate < tSnd[wIndex].m_wFrameRate)
				{
					ptFormat = &tSnd[wIndex];
					wRetIndx = wIndex;
				}
			}
		}
	}
	
	return wRetIndx;
}

//验证协商的能力是否符合模板的能力
BOOL32 CTpTypeAdpt::IsValidPriFormat(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase, BOOL32 bIsCns, BOOL32 bIsSnd)
{//B3 tConfBase范围:
 //HP: 1080P(60/50/30/25)fps、720P(60/50/30/25)fps
 //BP: 1080P(60/50/30/25)fps、720P(60/50/30/25)fps、4CIF 25fps
	u16 wIndex = 0;

	u16 wMaxHpIndex = 0;
	u16 wMaxBpIndex = 0;
	u16 wMinHpIndex = 0;
	u16 wMinBpIndex = 0;

	const TUmsVidFormat* ptVidMax = NULL;
	const TUmsVidFormat* ptVidMin = NULL;

	if (emTPVResEnd == tLeft.m_emRes)
	{
		return FALSE;
	}

	//目前带宽策略为：对于发送，只要对端带宽大于会议带宽，算不合法；对端接收带宽还是按照先前的判断策略
	if (bIsSnd)
	{
		if (emTPH264HP == tLeft.m_emQualityLvl && tLeft.m_wBitrate > tConfBase.m_wConfBitRate)
		{
			return FALSE;
		}

		if (emTPH264BP == tLeft.m_emQualityLvl && tLeft.m_wBitrate > tConfBase.m_wBpConfBitRate)
		{
			return FALSE;
		}
	}
	else
	{
		if (emTPH264HP == tLeft.m_emQualityLvl && 100 < abs(tConfBase.m_wConfBitRate - tLeft.m_wBitrate))
		{
			return FALSE;
		}
		
		if (emTPH264BP == tLeft.m_emQualityLvl && 100 < abs(tConfBase.m_wBpConfBitRate - tLeft.m_wBitrate))
		{
			return FALSE;
		}
	}
	//分别得到会议模板中最大的能力和最小的能力
	GetConfBaseMaxCap(tConfBase, wMaxHpIndex, wMaxBpIndex);
	GetConfBaseMinCap(tConfBase, wMinHpIndex, wMinBpIndex);

	//会场发送通道的能力在会议模板置下就合法
	BOOL32 bIsMax = FALSE;
	BOOL32 bIsMin = FALSE;

	if (tLeft.m_emQualityLvl == emTPH264HP)
	{
		//与HP最大的比较
		if (wMaxHpIndex != TP_INVALID_INDEX)
		{
			if (tLeft.m_emRes == tConfBase.m_atTpMainVideoRes[wMaxHpIndex].m_emRes)
			{
				if (tLeft.m_wFrameRate == tConfBase.m_atTpMainVideoRes[wMaxHpIndex].m_wFrameRate)
				{
					return TRUE;
				}
				if (tLeft.m_wFrameRate < tConfBase.m_atTpMainVideoRes[wMaxHpIndex].m_wFrameRate)
				{
					bIsMax = TRUE;
				}
			}
			else if (ResolutionSmallOpr(tLeft.m_emRes, tConfBase.m_atTpMainVideoRes[wMaxHpIndex].m_emRes))
			{
				bIsMax = TRUE;
			}
		}

		//与HP最小的比较
		if (wMinHpIndex != TP_INVALID_INDEX)
		{
			if (tLeft.m_emRes == tConfBase.m_atTpMainVideoRes[wMinHpIndex].m_emRes)
			{
				if (tLeft.m_wFrameRate == tConfBase.m_atTpMainVideoRes[wMinHpIndex].m_wFrameRate)
				{
					return TRUE;
				}
				if (tLeft.m_wFrameRate > tConfBase.m_atTpMainVideoRes[wMinHpIndex].m_wFrameRate)
				{
					bIsMin = TRUE;
				}
			}
			else if (ResolutionMaxOpr(tLeft.m_emRes, tConfBase.m_atTpMainVideoRes[wMinHpIndex].m_emRes))
			{
				bIsMin = TRUE;
			}
		}
	}

	else if (tLeft.m_emQualityLvl == emTPH264BP)
	{
		//与BP最大的比较
		if (wMaxBpIndex != TP_INVALID_INDEX)
		{
			if (tLeft.m_emRes == tConfBase.m_atTpMainVideoRes[wMaxBpIndex].m_emRes)
			{
				if (tLeft.m_wFrameRate == tConfBase.m_atTpMainVideoRes[wMaxBpIndex].m_wFrameRate)
				{
					return TRUE;
				}
				if (tLeft.m_wFrameRate < tConfBase.m_atTpMainVideoRes[wMaxBpIndex].m_wFrameRate)
				{
					bIsMax = TRUE;
				}
			}
			else if (ResolutionSmallOpr(tLeft.m_emRes, tConfBase.m_atTpMainVideoRes[wMaxBpIndex].m_emRes))
			{
				bIsMax = TRUE;
			}
		}
			
		//与BP最小的比较
		if (wMinBpIndex != TP_INVALID_INDEX)
		{
			if (tLeft.m_emRes == tConfBase.m_atTpMainVideoRes[wMinBpIndex].m_emRes)
			{
				if (tLeft.m_wFrameRate == tConfBase.m_atTpMainVideoRes[wMinBpIndex].m_wFrameRate)
				{
					return TRUE;
				}
				if (tLeft.m_wFrameRate > tConfBase.m_atTpMainVideoRes[wMinBpIndex].m_wFrameRate)
				{
					bIsMin = TRUE;
				}
			}
			else if (ResolutionMaxOpr(tLeft.m_emRes, tConfBase.m_atTpMainVideoRes[wMinBpIndex].m_emRes))
			{
				bIsMin = TRUE;
			}
		}
	}

	if (bIsSnd && bIsCns && bIsMax)
	{//对于CNS发送通道，只要比模板中最高能力小就合法
		return TRUE;
	}
	else if (bIsMax && bIsMin)
	{//其它情况，介于模板最高能力和最小能力间就合法
		return TRUE;
	}
	return FALSE;
}

BOOL32 CTpTypeAdpt::IsValidDualFormat(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase, BOOL32 bIsCns, BOOL32 bIsSnd)
{//B3 tConfBase双流范围
 //HP: 1080P(60/50/30/25)fps、720P(60/50/30/25)fps
 //BP: 1080P(60/50/30/25)fps、720P(60/50/30/25)fps、UXGA 60fps、WXGA(30/5)fps、SXGA(30/5)fps、XGA 5fps、4CIF 25fps

	if (emTPVResEnd == tLeft.m_emRes)
	{
		return FALSE;
	}
	
	//对于发送，只要对端带宽大于会议带宽，算不合法；对端接收带宽还是按照先前的判断策略
	if (bIsSnd)
	{
		if (emTPH264HP == tLeft.m_emQualityLvl && tLeft.m_wBitrate > tConfBase.m_wHpDualBitRate)
		{
			return FALSE;
		}

		if (emTPH264BP == tLeft.m_emQualityLvl && tLeft.m_wBitrate > tConfBase.m_wBpDualBitRate)
		{
			return FALSE;
		}
	}
	else
	{
		if (emTPH264HP == tLeft.m_emQualityLvl && 100 < abs(tConfBase.m_wHpDualBitRate - tLeft.m_wBitrate))
		{
			return FALSE;
		}
		
		if (emTPH264BP == tLeft.m_emQualityLvl && 100 < abs(tConfBase.m_wBpDualBitRate - tLeft.m_wBitrate))
		{
			return FALSE;
		}
	}

	BOOL32 bMin = FALSE;
	BOOL32 bMax = FALSE;
	for (u16 wIndex = 0; wIndex < tConfBase.m_wMinorNum; ++wIndex)
	{
		if (tLeft.m_emQualityLvl != tConfBase.m_atTpMinorVideoRes[wIndex].m_emQualityLvl)
		{
			continue;
		}

		if (ResolutionSmallOpr(tLeft.m_emRes, tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes))
		{
			bMax = TRUE;
		}
		else if (ResolutionMaxOpr(tLeft.m_emRes, tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes))
		{
			bMin = TRUE;
		}
		else
		{
			if (tLeft.m_wFrameRate == tConfBase.m_atTpMinorVideoRes[wIndex].m_wFrameRate)
			{
				return TRUE;
			}
			else if (tLeft.m_wFrameRate < tConfBase.m_atTpMinorVideoRes[wIndex].m_wFrameRate)
			{
				bMax = TRUE;
			}
			else
			{
				bMin = TRUE;
			}
		}
	}
	
	if (bIsCns && bIsSnd && bMax)
	{//会场为CNS且为发送 只要能力在模板能力之下就合法
		return TRUE;
	}
	else if (bMin && bMax)
	{
		return TRUE;
	}
	return FALSE;
}

u16	CTpTypeAdpt::CalcBasOutChnEncRes( u8 byOutChnNum, TUmsVidFormat atVidParam[] )
{
	if ( atVidParam == NULL || byOutChnNum == 0 )
	{
		return 0;
	}

	EmTpVideoResolution emRes = emTPVResolutionAuto;
	u16 wFrameRate = 0;
	u16 wEncRes = TP_INVALID_INDEX;
	u16 wTotalEncRes = 0;
	for ( u8 byIndx = 0; byIndx < byOutChnNum; byIndx++ )
	{
		emRes = atVidParam[byIndx].m_emRes;
		wFrameRate = atVidParam[byIndx].m_wFrameRate;

		switch (emRes)
		{
		case emTPVHD1080p1920x1080: //1080p
			{
				if ( wFrameRate == 60 || wFrameRate == 50 )
				{
					wEncRes = 1000;
				} 
				else if (wFrameRate ==30  || wFrameRate ==25 )
				{
					wEncRes = 500;
				}
				else
				{
					wEncRes = TP_INVALID_INDEX;
				}
			}
			break;
		case emTPVHD720p1280x720: //720p
			{
				if ( wFrameRate == 60 || wFrameRate == 50 )
				{
					wEncRes = 444;
				} 
				else if (wFrameRate ==30  || wFrameRate ==25 )
				{
					wEncRes = 222;
				}
				else
				{
					wEncRes = TP_INVALID_INDEX;
				}
			}
			break;
		case emTPVGA1600x1200: //UXGA 
			{
				if ( wFrameRate == 60  )
				{
					wEncRes = 926;
				} 
				else if ( wFrameRate == 30 )
				{
					wEncRes = 463;
				}
				else if ( wFrameRate == 20 )
				{
					wEncRes = 309;
				}
				else if ( wFrameRate == 15 )
				{
					wEncRes = 232;
				}
				else if ( wFrameRate == 10 )
				{
					wEncRes = 154;
				}
				else if ( wFrameRate == 5 )
				{
					wEncRes = 77;
				}
				else
				{
					wEncRes = TP_INVALID_INDEX;
				}
			}
			break;
		case emTPVGA1280x1024: //SXGA
			{
				if ( wFrameRate == 30 )
				{
					wEncRes = 463;
				}
				else if ( wFrameRate == 5 )
				{
					wEncRes = 53;
				}
				else
				{
					wEncRes = TP_INVALID_INDEX;
				}
			}
			break;
		case emTPVGA1024x768: //XGA
			{
				if ( wFrameRate == 5 )
				{
					wEncRes = 32;
				}
				else
				{
					wEncRes = TP_INVALID_INDEX;
				}
			}
			break;
		case emTPVGA1280x768: //WXGA
		case emTPVGA1280x800:
		case emTPVGA1366x768:
			{
				if ( wFrameRate == 30 )
				{
					wEncRes = 316;
				}
				else if ( wFrameRate == 5 )
				{
					wEncRes = 43;//42.2??
				}
				else
				{
					wEncRes = TP_INVALID_INDEX;
				}
			}
			break;
		case emTPV4CIF:
			{
				wEncRes = 80;
			}
			break;
		default:
			wEncRes = TP_INVALID_INDEX;
			break;
		}

		if ( wEncRes != TP_INVALID_INDEX )
		{
			wTotalEncRes += wEncRes;
		}
		wEncRes = TP_INVALID_INDEX;
	}

	return wTotalEncRes;
}

//add
BOOL32 CTpTypeAdpt::IsEqualConfBaseCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase)
{
	for (u16 wIndex = 0; wIndex < tConfBase.m_wMainNum; wIndex++)
	{
		if (tLeft.m_emQualityLvl != tConfBase.m_atTpMainVideoRes[wIndex].m_emQualityLvl)
		{
			continue;
		}
		if (tLeft.m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
		{
			if (tLeft.m_wFrameRate == tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

//验证模板中双流的能力是否有与该能力相等
BOOL32 CTpTypeAdpt::IsEqualDualConfCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase)
{
	for (u16 wIndex = 0; wIndex < tConfBase.m_wMinorNum; wIndex++)
	{
		if (tLeft.m_emQualityLvl != tConfBase.m_atTpMinorVideoRes[wIndex].m_emQualityLvl)
		{
			continue;
		}

		if (tLeft.m_emRes == tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes)
		{
			if (tLeft.m_wFrameRate == tConfBase.m_atTpMinorVideoRes[wIndex].m_wFrameRate)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

//会议模板中选取合适的双流能力
u16 CTpTypeAdpt::GetSuitDualConfCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase)
{
	const	TUmsVidFormat* ptVid = NULL;
	u16		wRet = TP_INVALID_INDEX;

	for (u16 wIndex = 0; wIndex < tConfBase.m_wMinorNum; wIndex++)
	{
		if (tLeft.m_emQualityLvl != tConfBase.m_atTpMinorVideoRes[wIndex].m_emQualityLvl)
		{
			continue;	
		}
		if (ResolutionSmallOpr(tLeft.m_emRes, tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes))
		{
			if (NULL == ptVid)
			{
				ptVid = &tConfBase.m_atTpMinorVideoRes[wIndex];
				wRet = wIndex;
			}
			else
			{
				if (ResolutionSmallOpr(ptVid->m_emRes, tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes))
				{
					ptVid = &tConfBase.m_atTpMinorVideoRes[wIndex];
					wRet = wIndex;
				}
				else if (ptVid->m_emRes == tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes)
				{
					if (ptVid->m_wFrameRate < tConfBase.m_atTpMinorVideoRes[wIndex].m_wFrameRate)
					{
						ptVid = &tConfBase.m_atTpMinorVideoRes[wIndex];
						wRet =wIndex;
					}
				}
			}
		}
		else if (tLeft.m_emRes == tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes)
		{
			if (tLeft.m_wFrameRate < tConfBase.m_atTpMinorVideoRes[wIndex].m_wFrameRate)
			{
				if (NULL == ptVid)
				{
					ptVid = &tConfBase.m_atTpMinorVideoRes[wIndex];
					wRet = wIndex;
				}
				else
				{
					if (ResolutionSmallOpr(ptVid->m_emRes, tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes))
					{
						ptVid = &tConfBase.m_atTpMinorVideoRes[wIndex];
						wRet = wIndex;
					}
					else if (ptVid->m_emRes == tConfBase.m_atTpMinorVideoRes[wIndex].m_emRes)
					{
						if (ptVid->m_wFrameRate < tConfBase.m_atTpMinorVideoRes[wIndex].m_wFrameRate)
						{
							ptVid = &tConfBase.m_atTpMinorVideoRes[wIndex];
							wRet = wIndex;
						}
					}
				}
			}
		}
	}
	return wRet;
}

u16 CTpTypeAdpt::GetSuitConfBaseCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase)
{
	const TUmsVidFormat* ptFormat = NULL;
	const TUmsVidFormat* ptFormatRes = NULL; //1080p的
	u16	 wRetIndex = TP_INVALID_INDEX;
	for (u16 wIndex = 0; wIndex < tConfBase.m_wMainNum; wIndex++)
	{
		if (tLeft.m_emQualityLvl != tConfBase.m_atTpMainVideoRes[wIndex].m_emQualityLvl)
		{
			continue;
		}

		if (tLeft.m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
		{
			//分辨率相等比较码率
			if (tLeft.m_wFrameRate > tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
			{
				if (NULL == ptFormat)
				{
					ptFormat = &tConfBase.m_atTpMainVideoRes[wIndex];
					wRetIndex = wIndex;
				}
				else
				{//比较ptFormat和当前的能力
					if (ResolutionSmallOpr(ptFormat->m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
					{//ptFormat的分辨率小于当前所比较的，置ptFormat为当前的能力
						ptFormat = &tConfBase.m_atTpMainVideoRes[wIndex];
						wRetIndex = wIndex;
					}
					else if (ptFormat->m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
					{//ptFormat的分辨率等于当前所比较的，那么就比较帧率
						if (ptFormat->m_wFrameRate < tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
						{//ptFormat的帧率小于当前所比较的帧率，置ptFormat为当前能力
							ptFormat = &tConfBase.m_atTpMainVideoRes[wIndex];
							wRetIndex = wIndex;
						}
					}
				}
			}
		}

		else if (ResolutionMaxOpr(tLeft.m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
		{//
			if (NULL == ptFormat)
			{
				ptFormat = &tConfBase.m_atTpMainVideoRes[wIndex];
				wRetIndex = wIndex;
			}
			else
			{
				if (ptFormat->m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
				{
					if (ptFormat->m_wFrameRate < tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
					{
						ptFormat = &tConfBase.m_atTpMainVideoRes[wIndex];
						wRetIndex = wIndex;
					}
				}

				else if (ResolutionSmallOpr(ptFormat->m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
				{
					ptFormat = &tConfBase.m_atTpMainVideoRes[wIndex];
					wRetIndex = wIndex;
				}
			}
		}
	}

	return wRetIndex;
}

EmTpStartConfRet CTpTypeAdpt::GetConfRetByCallReason( const EmCnsCallReason& emCallRet )
{
	EmTpStartConfRet emRet;
	switch(emCallRet)
	{
	case EmCnsCallReason_success:
		emRet = TP_StartConf_Success;
		break;
	case EmCnsCallReason_dstnotfind:
		emRet = TP_StartConf_ConfTemplateUnExist;
		break;
	case EmCnsCallReason_resourcefull:
		emRet = TP_StartConf_ResourceFull;
		break;
	case EmCnsCallReason_Busy:
		emRet = TP_StartConf_ConfExist;
		break;
	default:
		emRet = TP_StartConf_UnKonw;
		break;
	}
	return emRet;
}

void CTpTypeAdpt::GetConfBaseMaxCap(const TUmsConfBase& tConfBase, u16& wMaxHp, u16& wMaxBp)
{
	u16 wIndex = 0;
	const TUmsVidFormat* ptVidHpMax = NULL;
	const TUmsVidFormat* ptVidBpMax = NULL;

	wMaxHp = TP_INVALID_INDEX;
	wMaxBp = TP_INVALID_INDEX;
	for (wIndex = 0; wIndex < tConfBase.m_wMainNum; wIndex++)
	{
		if (tConfBase.m_atTpMainVideoRes[wIndex].m_emQualityLvl == emTPH264HP)
		{
			if (NULL == ptVidHpMax)
			{
				ptVidHpMax = &tConfBase.m_atTpMainVideoRes[wIndex];
				wMaxHp = wIndex;
			}
			else
			{//ptVidHpMax与该模板能力比较
				if (ptVidHpMax->m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
				{//分辨率相等
					if (ptVidHpMax->m_wFrameRate < tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
					{
						ptVidHpMax = &tConfBase.m_atTpMainVideoRes[wIndex];
						wMaxHp = wIndex;
					}
				}
				else if (ResolutionSmallOpr(ptVidHpMax->m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
				{//分辨率小于
					ptVidHpMax = &tConfBase.m_atTpMainVideoRes[wIndex];
					wMaxHp = wIndex;
				}
			}
		}
		else if (tConfBase.m_atTpMainVideoRes[wIndex].m_emQualityLvl == emTPH264BP)
		{
			if (NULL == ptVidBpMax)
			{
				ptVidBpMax = &tConfBase.m_atTpMainVideoRes[wIndex];
				wMaxBp = wIndex;
			}
			else
			{
				if (ptVidBpMax->m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
				{//分辨率相等
					if (ptVidBpMax->m_wFrameRate < tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
					{
						ptVidBpMax = &tConfBase.m_atTpMainVideoRes[wIndex];
						wMaxBp = wIndex;
					}
				}
				else if (ResolutionSmallOpr(ptVidBpMax->m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
				{
					ptVidBpMax = &tConfBase.m_atTpMainVideoRes[wIndex];
					wMaxBp = wIndex;
				}
			}
		}
	}
}

void CTpTypeAdpt::GetConfBaseMinCap(const TUmsConfBase& tConfBase, u16& wMinHp, u16& wMinBp)
{
	u16 wIndex = 0;
	const TUmsVidFormat* ptVidHpMin = NULL;
	const TUmsVidFormat* ptVidBpMin = NULL;

	wMinHp = TP_INVALID_INDEX;
	wMinBp = TP_INVALID_INDEX;

	for (wIndex = 0; wIndex < tConfBase.m_wMainNum; wIndex++)
	{
		if (tConfBase.m_atTpMainVideoRes[wIndex].m_emQualityLvl == emTPH264HP)
		{
			if (NULL == ptVidHpMin)
			{
				ptVidHpMin = &tConfBase.m_atTpMainVideoRes[wIndex];
				wMinHp = wIndex;
			}
			else
			{
				if (ptVidHpMin->m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
				{//分辨率相等
					if (ptVidHpMin->m_wFrameRate > tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
					{//帧率大于
						ptVidHpMin = &tConfBase.m_atTpMainVideoRes[wIndex];
						wMinHp = wIndex;
					}	
				}
				else if (ResolutionMaxOpr(ptVidHpMin->m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
				{//分辨率大于
					ptVidHpMin = &tConfBase.m_atTpMainVideoRes[wIndex];
					wMinHp = wIndex;
				}
			}
		}
		else if (tConfBase.m_atTpMainVideoRes[wIndex].m_emQualityLvl == emTPH264BP)
		{
			if (NULL == ptVidBpMin)
			{
				ptVidBpMin = &tConfBase.m_atTpMainVideoRes[wIndex];
				wMinBp = wIndex;
			}
			else
			{
				if (ptVidBpMin->m_emRes == tConfBase.m_atTpMainVideoRes[wIndex].m_emRes)
				{//分辨率相等
					if (ptVidBpMin->m_wFrameRate > tConfBase.m_atTpMainVideoRes[wIndex].m_wFrameRate)
					{
						ptVidBpMin = &tConfBase.m_atTpMainVideoRes[wIndex];
						wMinBp = wIndex;
					}
				}
				else if (ResolutionMaxOpr(ptVidBpMin->m_emRes, tConfBase.m_atTpMainVideoRes[wIndex].m_emRes))
				{
					ptVidBpMin = &tConfBase.m_atTpMainVideoRes[wIndex];
					wMinBp = wIndex;
				}
			}
		}
	}
}

u16 CTpTypeAdpt::GetVmpMemberNumByStyle( const EMVmpStyle& emStyle )
{
	switch(emStyle)
	{
	case tp_VmpStyle_ONE:
		return 1;
	case tp_VmpStyle_VTWO:
	case tp_VmpStyle_HTWO:
		return 2;
	case tp_VmpStyle_THREE:
	case tp_VmpStyle_leftBig:
	case tp_VmpStyle_MidBig:
	case tp_VmpStyle_RightBig:
	case tp_VmpStyle_3VERTICAL:
		return 3;
	case tp_VmpStyle_FOUR:
	case tp_VmpStyle_SPECFOUR:
	case tp_VmpStyle_FOUR_3BOTTOMMIDDLE:
		return 4;
	case tp_VmpStyle_SIX:
	case tp_VmpStyle_SIX_L2UP_S4DOWN:
	case tp_VmpStyle_SIX_DIVIDE:
		return 6;
	case tp_VmpStyle_EIGHT:
		return 8;
	case tp_VmpStyle_NINE:
		return 9;
	case tp_VmpStyle_TEN:
	case tp_VmpStyle_TEN_H:
	case tp_VmpStyle_TEN_M:
		return 10;
	case tp_VmpStyle_THIRTEEN:
	case tp_VmpStyle_THIRTEEN_M:
		return 13;
	case tp_VmpStyle_SIXTEEN:
		return 16;
	case tp_VmpStyle_SEVEN:
		return 7;
	case tp_VmpStyle_TWENTY:
		return 20;
	case tp_VmpStyle_FOURTEEN:
		return 14;
	case tp_VmpStyle_FIFTEEN:
		return 15;
	case tp_VmpStyle_TWENTYFIVE:
		return 25;
	default:
		return 0;
	}
}

EmTpVideoResolution CTpTypeAdpt::GetVmpMemberResByChnlIndx( const EMVmpStyle& emStyle, u16 wChnIndx)
{//0 路 在最下一起处理
	if ( wChnIndx == 0 )
	{
		return emTPVHD1080p1920x1080;
	}
	switch(emStyle)
	{
	case tp_VmpStyle_SIX:
	case tp_VmpStyle_SIX_L2UP_S4DOWN:
	case tp_VmpStyle_SIX_DIVIDE:
		{
			return emTPV640x368;
		}
		break;
	case tp_VmpStyle_EIGHT:
		{
			return emTPV480x272;
		}
		break;
	case tp_VmpStyle_NINE:
		{
			return emTPV640x368;
		}
		break;
	case tp_VmpStyle_TEN:
		{
			if ( wChnIndx == 5 )
			{
				return emTPV960x544;
			}
			else
			{
				return emTPV480x272;
			}
		}
		break;
	case tp_VmpStyle_TEN_H:
		{
			if ( wChnIndx == 1 )
			{
				return emTPV960x544;
			}
			else
			{
				return emTPV480x272;
			}
		}
		break;
	case tp_VmpStyle_TEN_M:
		{
			if ( wChnIndx == 1 )
			{
				return emTPV960x544;
			}
			else
			{
				return emTPV480x272;
			}
		}
		break;
	case tp_VmpStyle_THIRTEEN:
	case tp_VmpStyle_THIRTEEN_M:
		{
			return emTPV480x272;
		}
		break;
	case tp_VmpStyle_SIXTEEN:
		{
			return emTPV480x272;
		}
		break;
	case tp_VmpStyle_SEVEN:
		{
			if( wChnIndx > 0 && wChnIndx < 3 )
			{
				return emTPV960x544;
			}
			else if ( wChnIndx > 2 && wChnIndx < 7 )
			{
				return emTPV480x272;
			}
		}
		break;
	case tp_VmpStyle_TWENTY:
		{
			return emTPV480x272;
		}
		break;
	case tp_VmpStyle_FOURTEEN:
		{
			return emTPV480x272;
		}
		break;
	case tp_VmpStyle_FIFTEEN:
		{
			return emTPV480x272;
		}
		break;
	case tp_VmpStyle_TWENTYFIVE:
		{
			return emTPVCIF;
		}
		break;
	default:
		{
			return emTPVHD1080p1920x1080;
		}
		break;
	}

	return emTPVHD1080p1920x1080;
}

BOOL32 CTpTypeAdpt::PortIsVaild( u16 wPort )
{
	SOCKHANDLE sock  = INVALID_SOCKET;
    SOCKADDR_IN tSockAddr;
	
	memset(&tSockAddr, 0, sizeof(tSockAddr));
	tSockAddr.sin_family      = AF_INET; 
	tSockAddr.sin_port        = htons (wPort);
    tSockAddr.sin_addr.s_addr = 0;
	
	//Allocate a socket
    sock = socket ( AF_INET, SOCK_DGRAM , 0);
	if( sock == INVALID_SOCKET )
	{
		msgprint("[CTpTypeAdpt::PortIsVaild] Create UDP Socket Error.\n");
		return FALSE;
	}
	
	if( bind(sock, (SOCKADDR *)&tSockAddr, sizeof(tSockAddr)) == SOCKET_ERROR )
	{
		msgprint("[CTpTypeAdpt::PortIsVaild] Bind error.\n");
		SockClose(sock);//bind failed!
		return FALSE;
	}
	SockClose(sock);
	return TRUE;
}

const u16 CTpTypeAdpt::GetRcvFormatForSnd(const TUmsVidFormat& tSnd, const TUmsConfBase& tConfBase)
{
	u16 wRetIndx = TP_INVALID_INDEX;//返回一个最适合的格式索引

	wRetIndx = GetRcvFormat(tSnd, tConfBase.m_atTpMainVideoRes, tConfBase.m_wMainNum);

	if (TP_INVALID_INDEX == wRetIndx)
	{
		u16 wMinHp = TP_INVALID_INDEX;
		u16 wMinBp = TP_INVALID_INDEX;
		GetConfBaseMinCap(tConfBase, wMinHp, wMinBp);

		if (emTPH264HP == tSnd.m_emQualityLvl)
		{
			wRetIndx = wMinHp;
		}
		else
		{
			wRetIndx = wMinBp;
		}
	}

	return wRetIndx;
}

void CTpTypeAdpt::StartNtpd( u32_ip dwServerIp )
{
#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)

#define NTP_START_SH "/usr/bin/startntp.sh"
	// 通过脚本启动ntpd
	s8 abyBuf[MAX_MSG_LEN_TMP] = {0};
	sprintf(abyBuf, "%s "TPIPFORMAT" &", NTP_START_SH, u32ToIP(dwServerIp));

	msgprint("[StartNtpd] system cmd:%s.\n", abyBuf);
	system(abyBuf);

#else

#define NTP_START_SH "/tp/modifyntpserver.sh"
	// 通过脚本修改ntp server ip
	s8 abyBuf[MAX_MSG_LEN_TMP] = {0};
	sprintf(abyBuf, "%s "TPIPFORMAT" &", NTP_START_SH, u32ToIP(dwServerIp));

	msgprint("[StartNtpd] system cmd: %s.\n", abyBuf);
	system(abyBuf);
#endif

#endif
}

void CTpTypeAdpt::GetMaxCap( const TUmsVidFormat* ptFormat, u8 byNum, u16& wMaxIndex )
{
	if (ptFormat == NULL || byNum == 0)
	{
		return;
	}
	u16 wIndex = 0;
	const TUmsVidFormat* ptMaxForamt = NULL;

	wMaxIndex = TP_INVALID_INDEX;
	for (wIndex = 0; wIndex < byNum; wIndex++)
	{
		if (NULL == ptMaxForamt)
		{
			ptMaxForamt = &ptFormat[wIndex];
			wMaxIndex = wIndex;
		}
		else
		{//ptVidHpMax与该模板能力比较
			if (ptMaxForamt->m_emRes == ptFormat[wIndex].m_emRes)
			{//分辨率相等
				if (ptMaxForamt->m_wFrameRate < ptFormat[wIndex].m_wFrameRate)
				{
					ptMaxForamt = &ptFormat[wIndex];
					wMaxIndex = wIndex;
				}
			}
			else if (ResolutionSmallOpr(ptMaxForamt->m_emRes, ptFormat[wIndex].m_emRes))
			{//分辨率小于
				ptMaxForamt = &ptMaxForamt[wIndex];
				wMaxIndex = wIndex;
			}
		}
	}
}

void TPSetSysTime(TTPTime& tTime)
{
#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)
	
#define TIME_ZONE_BEIING 60*60*8
	struct tm time;
	time.tm_year = tTime.m_wYear - 1900;
	time.tm_mon = tTime.m_byMonth - 1;
	time.tm_mday = tTime.m_byMDay;
	time.tm_hour = tTime.m_byHour;
	time.tm_min = tTime.m_byMinute;
	time.tm_sec = tTime.m_bySecond;
	
	time_t tt = mktime(&time);//先转成1970到现在的秒数
	tt -= TIME_ZONE_BEIING;
	struct tm tmTmp = *(localtime(&tt));//转成北京时间：年月日时分秒
	::BrdTimeSet( &tmTmp );
#else
	tm _tm;
	time_t timep;
	timeval tv;
	_tm.tm_sec  =  tTime.m_bySecond;
	_tm.tm_min  =  tTime.m_byMinute;
	_tm.tm_hour =  tTime.m_byHour;
	_tm.tm_mday =  tTime.m_byMDay;
	_tm.tm_mon  =  tTime.m_byMonth - 1;
	_tm.tm_year =  tTime.m_wYear - 1900;
	
	timep   =   mktime( &_tm );
	
	tv.tv_sec   =   timep;
	tv.tv_usec   =   0;
	if( settimeofday ( &tv,   (struct   timezone   *)   0 )   <   0)
	{
		OspPrintf(TRUE, FALSE, "Set   system   datatime   error!\n ");
		return;
	}
#endif
#endif
}

void TPGetSysTime(TTPTime& tTime)
{
#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)

#define TIME_ZONE_BEIING 60*60*8
	struct tm time;
	::BrdTimeGet( &time );
	
	time_t tt = mktime(&time);//先转成1970到现在的秒数
	tt += TIME_ZONE_BEIING;
	struct tm tmTmp = *(localtime(&tt));//转成北京时间：年月日时分秒

	tTime.m_wYear = tmTmp.tm_year + 1900;
	tTime.m_byMonth = tmTmp.tm_mon + 1;
	tTime.m_byMDay = tmTmp.tm_mday;
	tTime.m_byHour = tmTmp.tm_hour;
	tTime.m_byMinute = tmTmp.tm_min;
	tTime.m_bySecond = tmTmp.tm_sec;

#else
	tm _tm;
	time_t timep;
	timeval tv;
	
	if( gettimeofday ( &tv,   (struct   timezone   *)   0 )   <   0)
	{
		OspPrintf(TRUE, FALSE, "get   system   datatime   error!\n");
		return;
	}	
	
	memcpy(&_tm,localtime( &tv.tv_sec ),sizeof(_tm));
	
	tTime.m_bySecond = _tm.tm_sec ;
	tTime.m_byMinute = _tm.tm_min;
	tTime.m_byHour   = _tm.tm_hour ;
	tTime.m_byMDay   = _tm.tm_mday;
	tTime.m_byMonth  = _tm.tm_mon + 1 ;
	tTime.m_wYear	   = _tm.tm_year + 1900 ;
#endif
#endif
	
#ifdef WIN32
	SYSTEMTIME tSysTime;
	::GetLocalTime( &tSysTime );
	
	tTime.m_wYear = tSysTime.wYear;
	tTime.m_byMonth = (u8)tSysTime.wMonth;
	tTime.m_byMDay = (u8)tSysTime.wDay;
	tTime.m_byHour = (u8)tSysTime.wHour ;
	tTime.m_byMinute = (u8)tSysTime.wMinute;
	tTime.m_bySecond = (u8)tSysTime.wSecond;	
#endif
}

s8 *ConvertDateFormat()
{
	s8 achMon[16] = {0};
	u32 byDay = 0;
	u32 byMonth = 0;
	u32 wYear = 0;
	static s8 achFullDate[24] = {0};
	sscanf(__DATE__, "%s %d %d", achMon, &byDay, &wYear );
//	wYear %= 100; //年份要后两位
	if ( 0 == strcmp( achMon, "Jan") )		 
		byMonth = 1;
	else if ( 0 == strcmp( achMon, "Feb") )
		byMonth = 2;
	else if ( 0 == strcmp( achMon, "Mar") )
		byMonth = 3;
	else if ( 0 == strcmp( achMon, "Apr") )		 
		byMonth = 4;
	else if ( 0 == strcmp( achMon, "May") )
		byMonth = 5;
	else if ( 0 == strcmp( achMon, "Jun") )
		byMonth = 6;
	else if ( 0 == strcmp( achMon, "Jul") )
		byMonth = 7;
	else if ( 0 == strcmp( achMon, "Aug") )
		byMonth = 8;
	else if ( 0 == strcmp( achMon, "Sep") )		 
		byMonth = 9;
	else if ( 0 == strcmp( achMon, "Oct") )
		byMonth = 10;
	else if ( 0 == strcmp( achMon, "Nov") )
		byMonth = 11;
	else if ( 0 == strcmp( achMon, "Dec") )
		byMonth = 12;
	
	sprintf(achFullDate, "%d%02d%02d", wYear, byMonth, byDay);
	return achFullDate;
}

s8* UmsVidProfilePrint(EmTpVideoQualityLevel emProfile)
{
	switch(emProfile)
	{
	case emTPH264HP:
		return "Hp";
	case emTPH264BP:
		return "Bp";
	default:
		return "default";
	}
	return "default";
}

s8* UmsVidFormatPrint(EmTpVideoFormat emFormat)
{
	switch(emFormat)
	{
	case emTPVH261:
		return "H261";
	case emTPVH262:
		return "H262";
	case emTPVH263:
		return "H263";
	case emTPVH263plus:
		return "H263Plus";
	case emTPVH264:
		return "H264";
	case emTPVMPEG4:
		return "MPEG4";
	default:
		return "default";
	}
	return "default";
}

s8* UmsVidResPrint(EmTpVideoResolution emRes)
{
	switch(emRes)
	{
	case emTPVSQCIF:
		return "SQCIF";
	case emTPVQCIF:
		return "QCIF";
	case emTPVCIF:
		return "CIF";
	case emTPV2CIF:
		return "2CIF";
	case emTPV4CIF:
		return "4CIF";
	case emTPV16CIF:
		return "16CIF";
	case emTPVHD480i720x480:
		return "480I";
	case emTPVHD480p720x480:
		return "480P";
	case emTPVHD576i720x576:
		return "576I";
	case emTPVHD576p720x576:
		return "576P";
	case emTPVHD720p1280x720:
		return "720P";
	case emTPVHD1080i1920x1080:
		return "1080I";
	case emTPVHD1080p1920x1080:
		return "1080P";
	case emTPVGA352x240:
		return "VGA352*240";
	case emTPVGA704x480:
		return "VGA704*480";
	case emTPVGA640x480:
		return "VGA640*480";
	case emTPVGA800x600:
		return "SVGA800*600";
	case emTPVGA1024x768:
		return "XGA1024*768";
	case emTPVGA1280x768:
		return "WXGA1280*768";
	case emTPVGA1280x800:
		return "WXGA1280*800";
	case emTPVGA1366x768:
		return "WXGA1366*768";
	case emTPVGA1280x854:
		return "WSXGA1280*854";
	case emTPVGA1440x900:
		return "WSXGA1440*900";
	case emTPVGA1280x1024:
		return "SXGA1280*1024";
	case emTPVGA1680x1050:
		return "SXGA1680*1050";
	case emTPVGA1600x1200:
		return "UXGA1600*1200";
	case emTPVGA1920x1200:
		return "WUXGA1920*1200";
	case emTPVSQCIF112x96:
		return "SQCIF112*96";
	case emTPVSQCIF96x80:
		return "SQCIF96*80";
	case emTPV320x192:
		return "320*192";
	case emTPV432x240:
		return "432*240";
	case emTPV480x272:
		return "480*272";
	case emTPV640x368:
		return "640*368";
	case emTPV864x480:
		return "864*480";
	case emTPV960x544:
		return "960*544";
	case emTPV1440x816:
		return "1440*816";
	default:
		return "default";
	}
	return "default";
}
s8* UmsAudFormatPrint(EmTpAudioFormat emFormat)
{
	switch(emFormat)
	{
	case emTPAG711a:
		return "711a";
	case emTPAG711u:
		return "711u";
	case emTPAG722:
		return "722";
	case emTPAG7231:
		return "7231";
	case emTPAG728:
		return "728";
	case emTPAG729:
		return "729";
	case emTPAMP3:
		return "mp3";
	case emTPAG721:
		return "721";
	case emTPAG7221:
		return "7221.c";
	case emTPAG719:
		return "719";
	case emTPAMpegAACLC:
		return "MpegAACLC";
	case emTPAMpegAACLD:
		return "MpegAACLD";
	default:
		return "default";
	}
	return "default";
}

s8* UmsPrintVendor( const EmTpVendorID& emUms )
{
	switch (emUms)
	{
	case EmTp_vendor_MICROSOFT_NETMEETING:
		{
			return "MICROSOFT";
		}
		break;
		
	case EmTp_vendor_KEDA:
		{
			return "KEDA";
		}
		break;
		
	case EmTp_vendor_HUAWEI:
		{
			return "HUAWEI";
		}
		break;
		
	case EmTp_vendor_POLYCOM:
		{
			return "POLYCOM";
		}
		break;
	case EmTp_vendor_POLYCOM_MCU:
		{
			return "POLYCOM_MCU";
		}
		break;
		
	case EmTp_vendor_TANDBERG:
		{
			return "TANDBERG";
		}
		break;
		
	case EmTp_vendor_RADVISION:
		{
			return "RADVISION";
		}
		break;
		
	case EmTp_vendor_VCON:
		{
			return "VCON";
		}
		break;
	case EmTp_vendor_SONY:
		{
			return "SONY";
		}
		break;
		
	case EmTp_vendor_VTEL:
		{
			return "VTEL";
		}
		break;
		
	case EmTp_vendor_ZTE:
		{
			return "ZTE";
		}
		break;
		
	case EmTp_vendor_ZTE_MCU:
		{
			return "ZTE_MCU";
		}
		break;
	case EmTp_vendor_CODIAN:
		{
			return "CODIAN";
		}
		break;
		
	case EmTp_vendor_AETHRA:
		{
			return "AETHRA";
		}
		break;
		
	case EmTp_vendor_CHAORAN:
		{
			return "CHAORAN";
		}
		break;
		
	case EmTp_vendor_UNKNOWN:
		{
			return "unknow";
		}
		break;
	case EmTp_vendor_END:
		{
			return "unknow";
		}
		break;
	default:
		{
			return "unknow";
			break;
		}
	}
	return "unknow";
}