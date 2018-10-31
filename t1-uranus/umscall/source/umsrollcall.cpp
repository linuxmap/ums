
#include "umsconfinst.h"
#include "umsrollcall.h"
#include "umsnetportmgr.h"
#include "nodefsm.h"
#include "umsbas.h"
#include "dualmgr.h"
#include "umsstackinterface.h"
#include "eventoutsipadapter.h"
#include "eventoutumscall.h"		
#include "tperrno.h"
#include "callmgr.h"
#include "pollmgr.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpumix.h"
#endif

#define UmsRollCallPrintAddr(Index, Addr) if (1){\
msgprintnotime("  Index:%d, Rtp("ADDRPORT_FORMAT"), BackRtcp("ADDRPORT_FORMAT")\n"\
	, Index, ADDRNET(Addr.m_tRtpAddr), ADDRNET(Addr.m_tBackRtcpAddr));}


#define UmsRollCallPrintAddrPoint(Index, Addr) if (NULL != Addr){\
	msgprintnotime("  Index:%d, Rtp("ADDRPORT_FORMAT"), BackRtcp("ADDRPORT_FORMAT")\n"\
	, Index, ADDRNET(Addr->m_tRtpAddr), ADDRNET(Addr->m_tBackRtcpAddr));}


#define UmsRollCallOprCycle(wIII, wIIIEnd, OprFun)\
	for (wIII = 0; wIII < wIIIEnd; wIII++)\
	{\
	    OprFun;}\


#define GetRollCallIndexBySrcIndex(SrcNode, DstNode, Index) SrcNode->m_wVidRcvNum > 1 ? Index : (DstNode)->GetSpeaker()



void RollCallMixCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
    tXmpuMixCbData* ptCbData = (tXmpuMixCbData* )param1;
    CUmsConfInst*	pInst = (CUmsConfInst*)ptCbData->pService;
    CUmsRollCallMgr* ptMgr = pInst->GetRollCallMgr();
	ptMgr->XmpuMixCB( dwType, (TAudMixInfo*) ptCbData->pRes, ptCbData->pData );	

#else
	TAudMixInfo::EmCBOprType emType = (TAudMixInfo::EmCBOprType)dwType;
	TAudMixInfo* ptMixInfo = (TAudMixInfo*)param1;

    CUmsConfInst* pconf = (CUmsConfInst*)param2;
	CUmsRollCallMgr* ptRollCallMgr = NULL;
	if (pconf)
    {
         ptRollCallMgr = pconf->GetRollCallMgr();
         if (ptRollCallMgr)
         {
              ptRollCallMgr->MixCB(emType, ptMixInfo);
         }
    }
#endif
	return;
}



//////////////////////////CUmsRollCallMgr////////////////////////////////////////////

void CUmsRollCallMgr::Clear()
{	
	m_bUIRollcallStatus = FALSE;
    m_bRollcallStaus    = FALSE;
	m_tRollCallEpList.Clear();
    m_tRollCallInfo.Clear();
	m_tMixRes.Clear();
	m_wBackSpeaker = TP_INVALID_INDEX;
    m_tNoty.Clear();

	for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++ )
	{
        m_aemPresentState[wIndex] = em_RollCallPresentState_PendingTarget;
	}
}



void CUmsRollCallMgr::StopRollCallModle()
{
	MdlHint(Ums_Mdl_Call, ("[StopRollCallModle] Conf:%d\n", Inst()->GetInsID()));

	if (m_pcConf->IsChairConf())
	{//�ϼ�

        ReleaseResoure();

		m_bUIRollcallStatus = FALSE;

        if (m_bRollcallStaus)
		{   
			m_bRollcallStaus = FALSE;
			RollCallInfoNotifyToLowUms(em_RollCallNotyUpNodeInfo);  //֪ͨ�¼��˳�����
		}


     	u16 wCaller = GetRollCallerEpId();
		u16 wTarget = GetCallTargetEpId();

        ReleaseRollCallEpChan(wCaller);
        ReleaseRollCallEpChan(wTarget);

      
        ModRestore();
	} 
	else 
	{
        m_bRollcallStaus    = FALSE;
		m_bUIRollcallStatus = FALSE;
	}
	

    Clear();

}



void CUmsRollCallMgr::Show()
{
	//����״̬
	msgprintnotime("[CUmsRollCallMgr Info] ConfID:%d, RollCallUIStatus:%d  RollCallStatus:%d\n", 
		           m_pcConf->GetInsID(),
				   m_bUIRollcallStatus, 
				   m_bRollcallStaus);

	//�����߱�������
	msgprintnotime("\n<RollCallListInfo>\n");
    msgprintnotime("CurCallerId:%d, CurCallTargetId:%d\n\n", 
		           m_tRollCallEpList.GetRollCaller(), 
				   m_tRollCallEpList.GetRollCallTarget());

	//���������б�
    msgprintnotime("CallTargetList num:%d Start:\n", m_tRollCallEpList.m_wNum);
    u16 wIndex = 0;
	u16 wLoop = 0;
	for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex ++)
	{
		if (!VALID_ALL_EPID(m_tRollCallEpList.m_awList[wIndex]))
		{
			continue;
		}
		msgprintnotime("[%d] wEpId:%d\n", wIndex, m_tRollCallEpList.m_awList[wIndex]);
	}

	msgprintnotime("CallTargetList End\n\n");

	//������ϯ
    msgprintnotime("<virchairaddr:>\n");
	if (m_pcConf->IsChairConf())
	{
		msgprintnotime("VirChair Vid:\n");
		UmsRollCallOprCycle(wLoop, TP_MAX_STREAMNUM, UmsRollCallPrintAddrPoint(wLoop, m_tRollCallInfo.m_tVirCallerAddr.m_aptVidAddr[wLoop]));
        msgprintnotime("VirChair Aud:\n");
		UmsRollCallOprCycle(wLoop, TP_MAX_STREAMNUM, UmsRollCallPrintAddrPoint(wLoop, m_tRollCallInfo.m_tVirCallerAddr.m_aptAudAddr[wLoop]));
        msgprintnotime("VirChair Small:\n");
		UmsRollCallOprCycle(wLoop, TP_MAX_STREAMNUM, UmsRollCallPrintAddrPoint(wLoop, m_tRollCallInfo.m_tVirCallerAddr.m_aptSmallAddr[wLoop]));
        msgprintnotime("VirChair medianode:\n");
		for( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			msgprintnotime("index%d : node=%d\n", wIndex, m_tRollCallInfo.m_tVirCallerAddr.m_adwMediaNode[wIndex]);
		}
        msgprintnotime("VirChair MixAddr:\n");
        UmsRollCallPrintAddrPoint(MIDSCREENINDEX, m_tRollCallInfo.m_tVirCallerAddr.m_ptMixAddr);
        msgprintnotime("VirChair mixmedianode:\n");
        msgprintnotime("mixmedianode=%d\n", m_tRollCallInfo.m_tVirCallerAddr.m_dwMedia);
	}


	//EpInfo
	msgprintnotime("\nEpInfo:\n");
	TRollCallEpInfo* pEpInfo = NULL;
	for (wIndex = 0; wIndex < em_RollCallEpMemEnd; wIndex++)
	{
        pEpInfo = m_tRollCallInfo.GetRollCallEpInfoByIndex(wIndex);

        if (NULL == pEpInfo || !VALID_ALL_EPID(pEpInfo->m_wEpID))
		{
            continue;
		}

		msgprintnotime("[%d] wEpId:%d, wScreenNum:%d, bSmallChanOn:%d, bMtAdjustRes:%d, wGetVidAudIndex:(%d), wMediaNode:%d\n", 
			           wIndex, 
			           pEpInfo->m_wEpID, 
					   pEpInfo->m_wStrceenNum, 
					   pEpInfo->m_bIsSmallChanOn, 
					   pEpInfo->m_bMtAdjustRes,
			           pEpInfo->m_wGetindex, 
					   pEpInfo->m_dwMediaNode);


		 if (!m_pcConf->IsChairConf() || !VALID_LOCAL_EPID(pEpInfo->m_wEpID))
		 {
			 msgprintnotime("PutAudAddr:\n");
			 UmsRollCallPrintAddr(MIDSCREENINDEX, pEpInfo->m_atPutAuddr[MIDSCREENINDEX]);
		 }

		 if (m_pcConf->IsChairConf())
		 {	

		     msgprintnotime("Assign Aud:\n");
			 UmsRollCallPrintAddr(MIDSCREENINDEX, pEpInfo->m_tAudAddr);

		 }

		msgprintnotime("\n");
	}


    msgprintnotime("Conf:%d RollCaller and Target info:\n", m_pcConf->GetInsID());
	if (m_pcConf->IsChairConf())
	{
		msgprintnotime("Top Conf:\n");

		TCallNode *pCallerNode = m_pcConf->GetNodeMgr()->GetNode(GetRollCallerEpId());
	    TCallNode *pTargetNode = m_pcConf->GetNodeMgr()->GetNode(GetCallTargetEpId());

	    msgprintnotime("RollCaller Info:\n");
		if (NULL != pCallerNode)
		{
			msgprintnotime("Epid:%d SndVid:%d SndAud:%d RcvVid:%d RcvAud:%d SpeakerSeate:%d alias:%s\n", 
				            pCallerNode->m_wEpID, 
							pCallerNode->m_wVidSndNum, 
							pCallerNode->m_wAudSndNum,
							pCallerNode->m_wVidRcvNum, 
							pCallerNode->m_wAudRcvNum,
							pCallerNode->GetSpeaker(), 
							pCallerNode->m_tConfName.m_abyAlias);
		}

        msgprintnotime("Target Info:\n");
		if (NULL != pTargetNode)
		{
		    msgprintnotime("Epid:%d SndVid:%d SndAud:%d RcvVid:%d RcvAud:%d SpeakerSeate:%d alias:%s\n",
				            pTargetNode->m_wEpID, 
							pTargetNode->m_wVidSndNum, 
							pTargetNode->m_wAudSndNum,
							pTargetNode->m_wVidRcvNum, 
							pTargetNode->m_wAudRcvNum,
							pTargetNode->GetSpeaker(), 
							pTargetNode->m_tConfName.m_abyAlias);
		}

	} 
	else
	{
		msgprintnotime("Low Conf:\n");
		for(wIndex = 0; wIndex < NUM_OF_CALLER_AND_TARGET; wIndex++)
		{
			if (em_RollCallerEp == wIndex)
			{
				msgprintnotime("RollCaller Info:\n");
			}else 
			{
				msgprintnotime("Target Info:\n");
			}
			
			msgprintnotime("Epid:%d SndVid:%d SndAud:%d RcvVid:%d RcvAud:%d SpeakerSeate:%d alias:%s\n",  
				            m_tNoty.m_NodeInfo[wIndex].m_wEpId, 
							m_tNoty.m_NodeInfo[wIndex].m_wVidSndNum, 
							m_tNoty.m_NodeInfo[wIndex].m_wAudSndNum,
							m_tNoty.m_NodeInfo[wIndex].m_wVidRcvNum, 
							m_tNoty.m_NodeInfo[wIndex].m_wAudRcvNum,
							m_tNoty.m_NodeInfo[wIndex].m_wSpeakerSeat, 
							m_tNoty.m_NodeInfo[wIndex].m_Alias.m_abyAlias);
			
		}


	}

	msgprintnotime("\n");
	msgprintnotime("  [PutAudMgr].\n");
	Inst()->GetPutAudMgr()->Show();
	msgprintnotime("\n[CUmsRollCallMgr Info] End!\n");

}



void CUmsRollCallMgr::Exit()
{

}


void CUmsRollCallMgr::Enter()
{
	Clear();
    return;
}

void CUmsRollCallMgr::ReleaseRollCall()
{
	if (m_pcConf->IsChairConf())
	{
        StopRollCallModle();
	}

	Clear();

	Inst()->GetPutAudMgr()->ReleaseAll(em_putauduser_rollcall);

}


void CUmsRollCallMgr::AddDelListUmcCnc(TUpdataRollCallList &tListInfo, TUpdataRollCallListRes &TRet)
{
	u16 wIndex = 0;
	u16 wEpId  = 0;
    TCallNode* ptNode = NULL;

    if (tListInfo.m_bAdd)
	{//����б�

		for (wIndex = 0; wIndex < tListInfo.m_atRollCallMemList.m_wNum; wIndex++)
		{
			wEpId = tListInfo.m_atRollCallMemList.m_awList[wIndex];
			ptNode = m_pcConf->GetNode(wEpId);
             
			if (NULL != ptNode &&
				ptNode->IsVidSndValid() &&
				ptNode->IsMtEp() &&
				!ptNode->IsVRS() && 
				!ptNode->IsG400())
			{

                TRet.m_emRet[wIndex] = em_RollCallOprRsp_Ok;

				if (m_tRollCallEpList.IsRollCallTargetInList(wEpId))
				{   //�Ѿ��������б��У����ظ����
					MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d,  add epid:%d ok   ep in list \n", m_pcConf->GetInsID(), wEpId));
                    continue;
				}
				
				if (m_bUIRollcallStatus && wEpId == GetRollCallerEpId())
				{
					TRet.m_emRet[wIndex]  = em_UpdateRollCalList_InvalidEp;
					MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d, m_bUIRollcallStatus:%d,  add epid:%d  fail, ep is  rollcaller \n", 
						                  m_pcConf->GetInsID(),m_bUIRollcallStatus,  wEpId));
    
                    continue;
				}

				if(TP_INVALID_INDEX == m_tRollCallEpList.AddRollCallTarget(wEpId))
				{
                    TRet.m_emRet[wIndex] = em_UpdateRollCalList_ListFull;
					MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d,  add epid:%d fail listfull \n", m_pcConf->GetInsID(), wEpId));
				}
				else
				{
					MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d,  add epid:%d success \n", m_pcConf->GetInsID(), wEpId));
				}

			} 
			else 
			{
                TRet.m_emRet[wIndex]  = em_UpdateRollCalList_InvalidEp;
			}
	
		 }     
	
	}
	else 
	{ //ɾ��

		for (wIndex = 0; wIndex < tListInfo.m_atRollCallMemList.m_wNum; wIndex++)
		{
			wEpId = tListInfo.m_atRollCallMemList.m_awList[wIndex];
			
	        if (TP_VALID_HANDLE(wEpId))
			{
                TRet.m_emRet[wIndex] = em_RollCallOprRsp_Ok;
				
				if (!m_tRollCallEpList.IsRollCallTargetInList(wEpId))
				{   //�������б��У�����ɾ��
                    TRet.m_emRet[wIndex]  = em_UpdateRollCalList_InvalidEp;
					MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d,  del  epid:%d invalid ep  not in list \n", m_pcConf->GetInsID(), wEpId));
                    continue;
				}

				if(wEpId == GetCallTargetEpId())
				{  // Ϊ��ǰ�����ߣ�����ɾ��
					TRet.m_emRet[wIndex]  = em_UpdateRollCalList_InvalidEp;
					MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d,  del  epid:%d fail , ep is now rollcalltarget \n", m_pcConf->GetInsID(), wEpId));

                    continue;
				}

			    
                u16 wDeleteIndex = m_tRollCallEpList.GetTargetIndex(wEpId);
				//�ӱ��������б���ɾ��
				m_tRollCallEpList.DelRollCallTarget(wEpId);
				MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d,  del  epid:%d success .rollcalllistnum:%d\n", 
					                  m_pcConf->GetInsID(), wEpId, m_tRollCallEpList.m_wNum));

		

                //����������б���ɾ��
                m_aemPresentState[wDeleteIndex] = em_RollCallPresentState_PendingTarget;
                for(u16 wInerIndex = wDeleteIndex + 1; wInerIndex < TP_MAX_ROLLCALL_NUM; ++wInerIndex)
				{
					m_aemPresentState[wInerIndex-1] = m_aemPresentState[wInerIndex];
 				    m_aemPresentState[wInerIndex] = em_RollCallPresentState_PendingTarget;
				}

			} 
			else 
			{
                TRet.m_emRet[wIndex]  = em_UpdateRollCalList_InvalidEp;
			}
			
		 }    



	}

	MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d, IsAddList:%d, UpdateListCt:%d, inrollcalllistnum:%d\n", 
		   m_pcConf->GetInsID(), 
		   tListInfo.m_bAdd,
		   tListInfo.m_atRollCallMemList.m_wNum, 
		   m_tRollCallEpList.m_wNum));	

}



void CUmsRollCallMgr::RollCallStatusCmdFromUmcCnc(TConfRollCallInfo& tRollCallInfo)
{
	CUmsConfInst* pInst = Inst();
	
	do 
	{
		if (!tRollCallInfo.m_bStart && !m_bUIRollcallStatus)
		{// ����δ������cmdֹͣ���������б�����
			tRollCallInfo.m_emRet = em_RollCallOprRsp_Ok;
			UptateRollCallListFromUI(tRollCallInfo.m_atRollCallMemList);
			MdlHint(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] UpDate RollCall List\n"));
			break;
		}

		if (tRollCallInfo.m_bStart && m_bUIRollcallStatus)
		{// �Ѿ�����������cmd���������ش���
			tRollCallInfo.m_emRet = em_StartRollCall_AlreadyStart;
			MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall AlreadyStart\n"));
			break;
		}

		if (tRollCallInfo.m_bStart)
		{// ��������
			if (pInst->GetUmsDiscuss()->IsUIDiscussOn())
			{
				tRollCallInfo.m_emRet = em_StartRollCall_DisMode;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail DiscussMode\n"));
				break;
			}

			if (pInst->GetAudMix()->IsAudMixMode())
			{
				tRollCallInfo.m_emRet = em_StartRollCall_ConfAudMixMode;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail ConfAudMixMode\n"));
				break;
			}


			TCallNode* pCaller = pInst->GetNode(tRollCallInfo.m_atRollCallMemList.m_wRollCaller);
			TCallNode* pCallerFar =  pInst->GetNodeMgr()->GetForeFatherNode(pCaller);

			if (NULL == pCaller || NULL == pCallerFar|| !pCaller->IsChanOn() || !pCallerFar->IsChanOn())
			{   //���������������˲�����
				m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_ROLLCALLER_OFFLINE, m_pcConf->chairID());
				tRollCallInfo.m_emRet = em_StartRollCall_OtherFail;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail caller is null or not chanon\n"));
				break;
			}

            if ( pCallerFar->IsMcu() )
			{
				tRollCallInfo.m_emRet = em_StartRollCall_OtherFail;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] conf:%d caller:%d StartRollCall fail caller is mcu \n",
					                    pInst->GetInsID(),  tRollCallInfo.m_atRollCallMemList.m_wRollCaller));
				break;
			}


			if(0 == tRollCallInfo.m_atRollCallMemList.m_wNum)
			{   // û�б�������
                m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_START_NO_TARGET, m_pcConf->chairID());
                tRollCallInfo.m_emRet = em_StartRollCall_OtherFail;
                MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail,  no  target\n"));
				break;
			}


			// ����ǲ����б�����������
            TCallNode* pTarget;
			u16 wIndex = 0;
            for (wIndex = 0; wIndex < tRollCallInfo.m_atRollCallMemList.m_wNum; wIndex++)
			{
				pTarget = pInst->GetNode(tRollCallInfo.m_atRollCallMemList.m_awList[wIndex]);
				if (NULL != pTarget && pTarget->IsChanOn())
				{
                    break;
				}
			}

			if(wIndex == tRollCallInfo.m_atRollCallMemList.m_wNum)
			{ // ���б������˶�������
				m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_ALLTARGET_OFFLINE, m_pcConf->chairID());
				tRollCallInfo.m_emRet = em_StartRollCall_OtherFail;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail,  all target not chanon\n"));
				break;
			}


			if (!UptateRollCallListFromUI(tRollCallInfo.m_atRollCallMemList))
			{ 
				tRollCallInfo.m_emRet = em_StartRollCall_OtherFail;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail UptateRollCallList fail\n"));
				break;
			}

			//�ж��Ƿ��п��õ�ý����Դ
			if (!CheckIdleMediaSource(0,SINGLE_NUMBER,0))
			{
				tRollCallInfo.m_emRet= em_StartRollCall_AssignMixFail;
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail No Idle Mix Media Source!\n"));
				break;
			}

			tRollCallInfo.m_emRet = AssignResource();
			if (em_RollCallOprRsp_Ok != tRollCallInfo.m_emRet)
			{
				ReleaseResoure();
				MdlError(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] StartRollCall fail AssignResource fail\n"));
				break;
			}

		    if (StartRollCallModle(tRollCallInfo))
			{

				//����һ�µ��� ǰ�ķ�����
                GetBackupSpeaker();

				MdlHint(Ums_Mdl_Call, ("\n[RollCallStatusCmdFromUmcCnc] BackupSpeaker = %d Start RollCall Success......\n\n", m_wBackSpeaker));

				//ֹͣ��ѯ
                m_pcConf->GetPollMgr()->TrySuspendPoll();

			}
		    else
			{
				MdlHint(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] create  caller chan fail \n"));
				//��ʱ������û�п���
                StopRollCallModle();
 			}

		}
		else
		{// ֹͣ����

			MdlHint(Ums_Mdl_Call, ("[RollCallStatusCmdFromUmcCnc] user stop rollcall\n"));
            tRollCallInfo.m_emRet = em_RollCallOprRsp_Ok;
			StopRollCallModle();
		}


	} while (0);


	return;
}

void CUmsRollCallMgr::MixRollCallerAndTarget()
{
     TAudMixMemberInfo tMemberInfo;
     u16 wCallerEp   = GetRollCallerEpId();
	 u16 wCallTarget = GetCallTargetEpId();

     //��ӵ����߽�����
	 tMemberInfo.AddMixMember(wCallerEp, TP_MAX_STREAMNUM);
     //��ӱ������߽�����
     tMemberInfo.AddMixMember(wCallTarget, TP_MAX_STREAMNUM);
     
	 m_pcConf->GetEapu()->AdjustAudMixMember(m_tMixRes.m_ptMixRes, &tMemberInfo);


	 CNetPortMgr::AdjustRollCallObjToMix(m_pcConf, &m_tMixRes, &tMemberInfo);
     
	 //ckeckdelmember();
}



u16 CUmsRollCallMgr::GetRollCallerToVirRollCaller()
{
    u16 wCallEpId = GetRollCallerEpId();
    
	return CNetPortMgr::AdjustRollCallerToVirRollCaller(m_pcConf, wCallEpId);
}



void CUmsRollCallMgr::GetTargetVid(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam)
{
	u16 wIndex = 0;
	if (m_pcConf->IsChairConf())
	{ //�ϼ�UMS

		if ( m_pcConf->GetBas()->IsChairInBas())
		{//��ϯ�������� pInst->IsPriNeedBas() ���ܱ�����ϯ��������
			TTPMediaTransAddr tMediaAddr;
			m_pcConf->GetBas()->GetOutChnChairVidAddr(tMediaAddr, wScreenIndex);
			tParam.m_tAddr.m_tRtpAddr =  tMediaAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tMediaAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			
		} else 
		{
			//ȡ�������������
			tParam.m_tAddr.m_tRtpAddr =  m_tRollCallInfo.m_tVirCallerAddr.m_aptVidAddr[wScreenIndex]->m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = m_tRollCallInfo.m_tVirCallerAddr.m_aptVidAddr[wScreenIndex]->m_tBackRtcpAddr;
			tParam.m_dwEqpNode = m_tRollCallInfo.m_tVirCallerAddr.m_adwMediaNode[wScreenIndex];
		}

	} else 
	{ //�¼�UMS
		if ( m_pcConf->GetBas()->IsChairInBas())
		{//��ϯ�������� pInst->IsPriNeedBas() ���ܱ�����ϯ��������
			TTPMediaTransAddr tMediaAddr;
			m_pcConf->GetBas()->GetOutChnChairVidAddr(tMediaAddr, wScreenIndex);
			tParam.m_tAddr.m_tRtpAddr =  tMediaAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tMediaAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			
		} else 
		{
			u16 wCallerEpId = m_pcConf->GetRollCallMgr()->GetRollCallerEpId();
            TCapNode*  pRollCallNode = m_pcConf->GetNodeMgr()->GetCapsetNode(wCallerEpId);

		    if (NULL != pRollCallNode)
			{ //������Ҳ�ڸ�UMS��
				if (NULL != pRollCallNode->m_aptChanAddr[wScreenIndex])
				{
					tParam.m_tAddr.m_tRtpAddr = pRollCallNode->m_aptChanAddr[wScreenIndex]->m_tVid.m_tRtpAddr;
					tParam.m_tAddr.m_tBackRtcpAddr = pRollCallNode->m_tRmtChan.m_atVidEnc[wScreenIndex].m_tChanAddr.m_tBackRtcpAddr;
					tParam.m_dwEqpNode   = pRollCallNode->m_tMediaEqp.m_dwEqpNode;
				}
				else 
				{
					MdlError(Ums_Mdl_Call, ("[GetTargetVid] Confid:%d, Get low rollcaller:%d vid fail, scrindex:%d \n", m_pcConf->GetInsID(), wCallerEpId, wScreenIndex));
				}

			} else 
			{
				TCapNode* CallerNode = m_pcConf->GetNodeMgr()->GetCaller();
				if (NULL != CallerNode && NULL != CallerNode->m_ptCasCadeChairAddr)
				{	
					tParam.m_tAddr.m_tRtpAddr = CallerNode->m_ptCasCadeChairAddr->m_atVid[wScreenIndex].m_tRtpAddr;
					tParam.m_tAddr.m_tBackRtcpAddr = CallerNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wScreenIndex].m_tChanAddr.m_tBackRtcpAddr;
					tParam.m_dwEqpNode   = CallerNode->m_tMediaEqp.m_dwEqpNode;
				}

			}

		}
         
	}
	
}


void CUmsRollCallMgr::GetSpeakertObj(TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj)
{
    TTPAlias tEpAlias;
	u16 wVidSnd = 0;
	u16 wAudSnd = 0;

    if (m_pcConf->IsChairConf())
	{
		u16 wTarget = m_pcConf->GetRollCallMgr()->GetCallTargetEpId();
        TCallNode* ptNode = m_pcConf->GetNodeMgr()->GetNode(wTarget);
	    if (NULL != ptNode )
		{
			wVidSnd  = ptNode->m_wVidSndNum;
			if (MIDSCREENINDEX == wScreenIndx) 
			{   // ����ֻ���м���һ·
                wAudSnd = 1;
			} 
		    tEpAlias = ptNode->m_tConfName;

		} 
		else 
		{
			MdlHint(Ums_Mdl_Call, ("CUmsRollCallMgr::GetSpeakertObj. rollcaller is null, ConfID:%d, rollcaller:%d\n",
				    m_pcConf->GetInsID(), wTarget));
		}

	}
	else 
	{   
		//�¼�ȡ֪ͨ������m_NodeInfo

		wVidSnd  = m_tNoty.m_NodeInfo[em_CallTargetEp].m_wVidSndNum;
		if (MIDSCREENINDEX == wScreenIndx) 
		{   // ����ֻ���м���һ·
			wAudSnd = 1;
		} 
		tEpAlias = m_tNoty.m_NodeInfo[em_CallTargetEp].m_Alias;
		
	}


	tObj.m_tAlias = tEpAlias;
	tObj.m_emObj  = emObjSpeaker;
	tObj.m_wScrIndx = wScreenIndx;
	if (wVidSnd == 0)
	{// ����Ŀ���޷���ͨ����������ߣ���ͳһ��1�������ն˺�t300���ֿ���̬ͼƬ������
		tObj.m_wVidNum = 1;
		tObj.m_wAudNum = 1;
	}
	else
	{
		tObj.m_wVidNum = IsInSndRange(wScreenIndx, wVidSnd) ? 1 : 0;
		tObj.m_wAudNum = IsInSndRange(wScreenIndx, wAudSnd) ? 1 : 0;
	}

	return;
}


void CUmsRollCallMgr::GetChairObj(TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj)
{
    TTPAlias tEpAlias;

	u16 wVidSnd = 0;
	u16 wAudSnd = 0;

	if (m_pcConf->IsChairConf())
	{
		u16 wRollCaller = m_pcConf->GetRollCallMgr()->GetRollCallerEpId();
        TCallNode* ptNode = m_pcConf->GetNodeMgr()->GetNode(wRollCaller);
	    if (NULL != ptNode )
		{
			wVidSnd  = ptNode->m_wVidSndNum;
			if (MIDSCREENINDEX == wScreenIndx) 
			{   // ����ֻ���м���һ·
                wAudSnd = 1;
			} 
		
		    tEpAlias = ptNode->m_tConfName;

		} 
		else 
		{
			MdlHint(Ums_Mdl_Call, ("CUmsRollCallMgr::GetTargetObj. rollcaller is null, ConfID:%d, rollcaller:%d\n",
				    m_pcConf->GetInsID(), wRollCaller));
		}

	}
	else 
	{   
		//�¼�ȡ֪ͨ������
		wVidSnd  = m_tNoty.m_NodeInfo[em_RollCallerEp].m_wVidSndNum;
		if (MIDSCREENINDEX == wScreenIndx) 
		{   // ����ֻ���м���һ·
			wAudSnd = 1;
		} 
		tEpAlias = m_tNoty.m_NodeInfo[em_RollCallerEp].m_Alias;
	}

    tObj.m_tAlias   = tEpAlias;
	tObj.m_emObj    = emObjChair;
	tObj.m_wScrIndx = wScreenIndx;
    
	if (wVidSnd == 0)
	{// ����Ŀ���޷���ͨ����������ߣ���ͳһ��1�������ն˺�t300���ֿ���̬ͼƬ������
		tObj.m_wVidNum = 1;
		tObj.m_wAudNum = 1;
	}
	else
	{
		tObj.m_wVidNum = IsInSndRange(wScreenIndx, wVidSnd) ? 1 : 0;
		tObj.m_wAudNum = IsInSndRange(wScreenIndx, wAudSnd) ? 1 : 0;
	}

}


void CUmsRollCallMgr::GetTargetVidSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam)
{
    u16 wCallerEpId = m_pcConf->GetRollCallMgr()->GetRollCallerEpId();

	if (m_pcConf->IsChairConf())
	{   //�¼�����ȥ���� ������
		TCallNode* ptRollCallerNode = m_pcConf->GetNode(wCallerEpId);	//�����߿���Ϊ����EP
		TCapNode* ptForeRollCaller = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptRollCallerNode);
		if (NULL == ptRollCallerNode || NULL == ptForeRollCaller)
		{
			MdlError(Ums_Mdl_Call, ("CUmsRollCallMgr::GetTargetVidSrcAddr can not find RollCaller ep.confID:%d, RollCaller:%d, rmtep:%d\n"
				, m_pcConf->GetInsID(), wCallerEpId, ptNode->m_wEpID));
			
			return ;
		}
	}


	if(!ptNode->IsVidRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CUmsRollCallMgr::GetTargetVidSrcAddr rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, vidrcv:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wVidRcvNum));
		
		return;
	}
	
	if (m_pcConf->IsChairConf())
	{ //�ϼ�
		if(ptNode->IsUms())
		{ //��ǰ���������ߡ� ���¼�UMS
			
			if (NULL != m_pcConf->GetNodeMgr()->GetNodeUnderThisUms(ptNode, wCallerEpId))
			{// ��ǰ�������ߡ�Ҳ�ڸ�UMS�£���ʱ����Ҫ���UMS ����ϯ��, ��ϯͨ������ �¼����ϼ�������������
				tParam.m_tAddr.m_tRtpAddr.Clear();
			} else 
			{// ��ǰ �������ߡ����ڸ�UMS�£���ʱӦ���UMS�ļ�����ϯͨ���򡰵����ˡ�������
				GetTargetVid(wScreenIndex,  ptNode, tParam);   
			}
			
		} else
		{ //��ǰ���������ߡ� ���ϼ�UMS �� 
			GetTargetVid(wScreenIndex,  ptNode, tParam);
		}
		
	}else
	{//�¼�
            GetTargetVid(wScreenIndex, ptNode, tParam);
	}

}



void CUmsRollCallMgr::GetTargetMixVidSrcAddr(TCapNode* ptNode, TTransParam &tParam)
{
	u16 wSpeakseat = 0;
	u16 wRollCaller = 0;
	TTPMediaTransAddr tMediaAddr;


	if (m_pcConf->IsChairConf())
	{ //�ϼ�UMS

        wRollCaller = GetRollCallerEpId();
		TCallNode*  ptCallerNode = m_pcConf->GetNode(wRollCaller);

		if ( m_pcConf->GetVmp()->IsChairInVmp() || (ptNode->IsUms() && m_pcConf->GetVmp()->IsChairOrSpeakerInVmp()))
		{// 
			TTPDsFrom tAddr;
			m_pcConf->GetVmp()->GetSpeakerVmpOutAddr(tAddr);
			tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = tAddr.m_dwEqpNode;

		}else if(m_pcConf->GetBas()->IsChairInBas())
		{
             if (NULL != ptCallerNode)
			 {
                 wSpeakseat = ptCallerNode->GetSpeaker();
				 m_pcConf->GetBas()->GetOutChnChairVidAddr(tMediaAddr, wSpeakseat);
				 
				 tParam.m_tAddr.m_tRtpAddr = tMediaAddr.m_tRtpAddr;
				 tParam.m_tAddr.m_tBackRtcpAddr = tMediaAddr.m_tBackRtcpAddr;
			     tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			 }

		} else 
		{//ȡ��ϯ

			if (NULL != ptCallerNode)
			{
                wSpeakseat = ptCallerNode->GetSpeaker();
				//ȡ������������� ȡ��ϯ
				tParam.m_tAddr.m_tRtpAddr =  m_tRollCallInfo.m_tVirCallerAddr.m_aptVidAddr[wSpeakseat]->m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = m_tRollCallInfo.m_tVirCallerAddr.m_aptVidAddr[wSpeakseat]->m_tBackRtcpAddr;
				tParam.m_dwEqpNode = m_tRollCallInfo.m_tVirCallerAddr.m_adwMediaNode[wSpeakseat];
			}
		}

	}else 
	{ //�¼�UMS

		if (m_tNoty.m_NodeInfo[em_RollCallerEp].m_wSpeakerSeat < TP_MAX_STREAMNUM)
		{
			wSpeakseat = m_tNoty.m_NodeInfo[em_RollCallerEp].m_wSpeakerSeat;
		}
		else
		{
			wSpeakseat = MIDSCREENINDEX;
		}


		if ( m_pcConf->GetVmp()->IsChairInVmp() || (ptNode->IsUms() && m_pcConf->GetVmp()->IsChairOrSpeakerInVmp()))
		{// 
			TTPDsFrom tAddr;
			m_pcConf->GetVmp()->GetSpeakerVmpOutAddr(tAddr);
			tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
		} else if ( m_pcConf->GetBas()->IsChairInBas())
		{

			m_pcConf->GetBas()->GetOutChnChairVidAddr(tMediaAddr, wSpeakseat);
			tParam.m_tAddr.m_tRtpAddr = tMediaAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tMediaAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
						
		} else
		{
			wRollCaller  = GetRollCallerEpId();
            TCapNode* ptRollCallerCapNode = m_pcConf->GetNodeMgr()->GetCapsetNode(wRollCaller);

			if (NULL != ptRollCallerCapNode)
			{ //������Ҳ�ڸ�UMS��
				wSpeakseat = ptRollCallerCapNode->GetSpeaker();
				tParam.m_tAddr.m_tRtpAddr = ptRollCallerCapNode->m_aptChanAddr[wSpeakseat]->m_tVid.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = ptRollCallerCapNode->m_tRmtChan.m_atVidEnc[wSpeakseat].m_tChanAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode   = ptRollCallerCapNode->m_tMediaEqp.m_dwEqpNode;
				
			} else 
			{
				
				TCapNode* pUms = m_pcConf->GetNodeMgr()->GetCaller();
			    if (NULL != pUms)
				{	//�¼�ȡ���������˵ķ�����ϯ����MIDSCREENINDEX
				    tParam.m_tAddr.m_tRtpAddr = pUms->m_ptCasCadeChairAddr->m_atVid[wSpeakseat].m_tRtpAddr;
				    tParam.m_tAddr.m_tBackRtcpAddr = pUms->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wSpeakseat].m_tChanAddr.m_tBackRtcpAddr;
				    tParam.m_dwEqpNode   = pUms->m_tMediaEqp.m_dwEqpNode;
				}
				
			}
		}

	}

}



void CUmsRollCallMgr::GetTargetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam )
{
	if(!ptNode->IsVidRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("RollCallMode CNodeFsmChair::GetMixSrcAddr can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
		
		return;
	}
	
	u16 wCallTarget = 0;
	TServiceAddr tMixOutAddr;

	GetTargetMixVidSrcAddr( ptNode, tVidParam);
	
	if (m_pcConf->IsChairConf())
	{ //�ϼ�
        wCallTarget = GetCallTargetEpId();

		if(ptNode->IsUms())
		{ //��ǰ���������ߡ� ���¼�UMS
		  //"������" ���������ߡ� ����Ƶͨ��PUT ��ȥ, �����᳡��N
			if(m_pcConf->GetDualMgr()->IsStart() &&  m_pcConf->GetSpeaker().m_bIsDualMixOn)
			{ // ����˫��, ��pInst->GetSpeaker().m_ptAudMix��ȡN (������ + �������� + ˫��)��ȡ�������յ�ַ
				m_pcConf->GetEapu()->GetNModeAudRcvAddr(m_pcConf->GetSpeaker().m_ptAudMix, tMixOutAddr, ptNode->m_tAudRcvFormat.m_tFormat);
				tAudParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
				tAudParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
				tAudParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
			}
            else
			{ //
				if(NULL != m_tMixRes.m_ptMixRes)
				{
					//ȡ������ʽ�� 
					m_pcConf->GetEapu()->GetNModeAudRcvAddr(m_tMixRes.m_ptMixRes, tMixOutAddr, ptNode->m_tAudRcvFormat.m_tFormat);
					tAudParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
					tAudParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
					tAudParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
				}
			}

	
		} else
		{ //��ǰ���������ߡ� ���ϼ�UMS

            if (m_pcConf->GetDualMgr()->IsStart() &&  m_pcConf->GetSpeaker().m_bIsDualMixOn)
			{ // ������˫������pInst->GetSpeaker().m_ptAudMix��ȡN-1 (������ + ˫��)
				m_pcConf->GetEapu()->GetMixerChnOutAddr(m_pcConf->GetSpeaker().m_ptAudMix, tMixOutAddr, wCallTarget, TP_MAX_STREAMNUM);
				tAudParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
				tAudParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
				tAudParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;

			}
			else
			{ // δ����˫�����ӵ�����������ȡN-1  (������)
				if (NULL != m_tMixRes.m_ptMixRes)
				{
					m_pcConf->GetEapu()->GetMixerChnOutAddr(m_tMixRes.m_ptMixRes, tMixOutAddr, wCallTarget, TP_MAX_STREAMNUM);
					tAudParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
					tAudParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
					tAudParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
				}

			}

		}
		
	}else
	{//�¼�
     // �������� ȡPUT ����Ƶ
		TRollCallEpInfo* ptEpInfo = GetRollCallEpInfoById(ptNode->m_wEpID);
		if (NULL != ptEpInfo)
		{
			tAudParam.m_tAddr.m_tRtpAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
			tAudParam.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
			tAudParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
		} 
		
	}
}



void CUmsRollCallMgr::UploadRollCallerMainVid(TCapNode* ptNodeUms, TUmsDsData *ptDsData, u16 &wDsNum)
{
    if (m_pcConf->IsChairConf())
	{
        return;
	}

	if (NULL == ptNodeUms || !ptNodeUms->IsChanOn())
	{
        return;
	}

	u16 wRollCaller = GetRollCallerEpId();
    TCapNode* ptCallerNode = m_pcConf->GetNodeMgr()->GetCapsetNode(wRollCaller);
	if (NULL == ptCallerNode)
	{//�����߲��ڸ��¼�UMs ��
         return;
	}

	u16 wIndex = 0;
	u16 wChanIndex = 0;
	s32 symbolflag = 1; 

	TTPMediaTransAddr tAddr;

	for(wIndex = 1; wIndex <= ptCallerNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
	{
        wChanIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

		tAddr.Clear();
		
		if(m_pcConf->GetBas()->IsChairInBas())
		{
			m_pcConf->GetBas()->GetOutChnChairVidAddr(tAddr, wChanIndex);
			
			ptDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			ptDsData[wDsNum].m_tSndToAddr   = ptNodeUms->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wChanIndex].m_tChanAddr.m_tRtpAddr;
			ptDsData[wDsNum].m_dwEqpNode    = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			ptDsData[wDsNum].m_emSwitchType = emRtpSwap;
			ptDsData[wDsNum].SetBasVideo();
			++wDsNum;
			
			ptDsData[wDsNum].m_tRcvFromAddr = ptNodeUms->m_ptCasCadeChairAddr->m_atVid[wChanIndex].m_tRtcpForSnd;
			ptDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			ptDsData[wDsNum].m_dwEqpNode = ptNodeUms->m_tMediaEqp.m_dwEqpNode;
			ptDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			
		} else 
		{
			ptDsData[wDsNum].m_tRcvFromAddr = ptCallerNode->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			ptDsData[wDsNum].m_tSndToAddr = ptNodeUms->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wChanIndex].m_tChanAddr.m_tRtpAddr;
			ptDsData[wDsNum].m_dwEqpNode = ptCallerNode->m_tMediaEqp.m_dwEqpNode;
			ptDsData[wDsNum].m_emSwitchType = emRtpSwap;
			ptDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
			
			ptDsData[wDsNum].m_tRcvFromAddr = ptNodeUms->m_ptCasCadeChairAddr->m_atVid[wChanIndex].m_tRtcpForSnd;
			ptDsData[wDsNum].m_tSndToAddr = ptCallerNode->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			ptDsData[wDsNum].m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			ptDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}

	return;
}


// ͨ��OBJ �������ִ���
// obj = emObjSpeaker :  ��ϯ���¼��� ������Ҳ���¼�
// obj = emObjSelp    :  ��ϯ���¼��� ���������ϼ� 
void CUmsRollCallMgr::UploadRollCallerSmallVid( TCapNode* ptNodeUms, TUmsDsData *ptDsData, u16 &wDsNum)
{
	u16 wIndex = 0;
	EMScreenObj emObj = ptNodeUms->m_emLastObj;

	if(m_pcConf->IsChairConf() || !ptNodeUms->IsSmallVidRcv() || ptNodeUms->m_wEpID != CALLER_EP_INDEX)
	{
        return;
	}

    if(emObjSpeaker == emObj)
	{ //NODE 65��Ŀ��ΪSpeaker, ���������ڱ��¼�

		if (m_pcConf->curSpeakerID() == CALLER_EP_INDEX)
		{
            return;
		}

        if (IsNeedSendRollCallerSmall())
		{   //chair �ںϳɣ������ϯ���¼�����Ҫ���ϼ�����ϯ��С����

			u16 wRollCallEp = m_pcConf->GetRollCallMgr()->GetRollCallerEpId();
			if(!VALID_ALL_EPID(wRollCallEp))
			{   // ��ϯ�������ˣ����ڱ��¼�
                return;
			}

			TCallNode* ptCallNode     = m_pcConf->GetNodeMgr()->GetNode(wRollCallEp);
			TCapNode* ptRollCallerFar = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptCallNode);
			if (NULL != ptCallNode && NULL != ptRollCallerFar && ptRollCallerFar->IsSmallVidSnd())
			{ 
				for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
				{
					
					ptDsData[wDsNum].m_tRcvFromAddr = ptRollCallerFar->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
					ptDsData[wDsNum].m_tSndToAddr = ptNodeUms->m_tRmtChan.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
					ptDsData[wDsNum].m_dwEqpNode = ptRollCallerFar->m_tMediaEqp.m_dwEqpNode;
					ptDsData[wDsNum].m_emSwitchType = emRtpSwap;
					ptDsData[wDsNum].SetSmallVideo(wIndex);
					++wDsNum;
					
					ptDsData[wDsNum].m_tRcvFromAddr = ptNodeUms->m_aptSmallChanAddr[wIndex]->m_tRtcpForSnd;
					ptDsData[wDsNum].m_tSndToAddr = ptRollCallerFar->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
					ptDsData[wDsNum].m_dwEqpNode = ptNodeUms->m_tMediaEqp.m_dwEqpNode;
					ptDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
				
			 }

		} 
		else
		{ // ������������¼�����Ҫ���ϼ������˵�С����
			TCallNode* ptSpeakerNode = m_pcConf->GetNode(m_pcConf->curSpeakerID());
			TCapNode* ptSpeakerFartherNode = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptSpeakerNode);

			if (NULL != ptSpeakerNode && NULL != ptSpeakerFartherNode && ptSpeakerNode == ptSpeakerFartherNode 
				&& ptSpeakerFartherNode->IsSmallVidSnd())
			{
				for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
				{
					
					ptDsData[wDsNum].m_tRcvFromAddr = ptSpeakerFartherNode->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
					ptDsData[wDsNum].m_tSndToAddr = ptNodeUms->m_tRmtChan.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
					ptDsData[wDsNum].m_dwEqpNode = ptSpeakerFartherNode->m_tMediaEqp.m_dwEqpNode;
					ptDsData[wDsNum].m_emSwitchType = emRtpSwap;
					ptDsData[wDsNum].SetSmallVideo(wIndex);
					++wDsNum;
					
					ptDsData[wDsNum].m_tRcvFromAddr = ptNodeUms->m_aptSmallChanAddr[wIndex]->m_tRtcpForSnd;
					ptDsData[wDsNum].m_tSndToAddr = ptSpeakerFartherNode->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
					ptDsData[wDsNum].m_dwEqpNode = ptNodeUms->m_tMediaEqp.m_dwEqpNode;
					ptDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
			}
		}

	} else if (emObjSelf == emObj)
	{//NODE 65��Ŀ��ΪemObjSelf, ����ϯ�������ˣ����¼������������ϼ�
		if (IsNeedSendRollCallerSmall())
		{//��ϯ�������ˣ�Ҳ���¼�����ϯ�ںϳɣ��¼�UMS ��Ҫ���ϼ�UMS (65)����ϯ��С����
            
			u16 wRollCallEp = m_pcConf->GetRollCallMgr()->GetRollCallerEpId();
			if(!VALID_ALL_EPID(wRollCallEp))
			{
                return;
			}

			TCallNode* ptCallNode     = m_pcConf->GetNodeMgr()->GetNode(wRollCallEp);
			TCapNode* ptRollCallerFar = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptCallNode);
			if (NULL != ptCallNode && NULL != ptRollCallerFar && ptRollCallerFar->IsSmallVidSnd())
			{ 
				for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
				{
					
					ptDsData[wDsNum].m_tRcvFromAddr = ptRollCallerFar->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
					ptDsData[wDsNum].m_tSndToAddr = ptNodeUms->m_tRmtChan.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
					ptDsData[wDsNum].m_dwEqpNode = ptRollCallerFar->m_tMediaEqp.m_dwEqpNode;
					ptDsData[wDsNum].m_emSwitchType = emRtpSwap;
					ptDsData[wDsNum].SetSmallVideo(wIndex);
					++wDsNum;
					
					ptDsData[wDsNum].m_tRcvFromAddr = ptNodeUms->m_aptSmallChanAddr[wIndex]->m_tRtcpForSnd;
					ptDsData[wDsNum].m_tSndToAddr = ptRollCallerFar->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
					ptDsData[wDsNum].m_dwEqpNode = ptNodeUms->m_tMediaEqp.m_dwEqpNode;
					ptDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
				
			}
		}
	} 


	return;
}





void CUmsRollCallMgr::GetTargetAudSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam)
{
    TServiceAddr tMixOutAddr;
	u16 wCallerEpId = 0;

    if (!ptNode->IsAudRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CUmsRollCallMgr::GetTargetAudSrcAddr rmt ep aud rcv invalid.confID:%d, rmtep:%d, audrcv:%d\n"
			, m_pcConf->GetInsID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		return;
	}

	if (m_pcConf->IsChairConf())
	{ //�ϼ�

		//TCallNode* ptCallTarget = m_pcConf->GetNode(m_pcConf->curSpeakerID());	

        if (ptNode->IsUms())
		{ // �����������¼�, �¼����������ߣ� �����ߡ���Ƶ��ͨ��PUT��ȥ��

			tParam.m_tAddr.m_tRtpAddr.Clear();
			if ((MIDSCREENINDEX == wScreenIndex) && NULL != m_tMixRes.m_ptMixRes)
			{ // �������˱������˵Ļ���ͨ����ϯͨ�����м�ͨ������ȥ
	            m_pcConf->GetEapu()->GetNModeAudRcvAddr(m_tMixRes.m_ptMixRes, tMixOutAddr, ptNode->m_tAudRcvFormat.m_tFormat);                
				tParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
                tParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
			}

		} else 
		{ // �����������ϼ�

			tParam.m_tAddr.m_tRtpAddr.Clear();
			if ((MIDSCREENINDEX == wScreenIndex) && NULL != m_tMixRes.m_ptMixRes)
			{ //�ϼ����������ߡ� ��mix ��ȡ n - 1 
				m_pcConf->GetEapu()->GetMixerChnOutAddr(m_tMixRes.m_ptMixRes, tMixOutAddr, ptNode->m_wEpID, TP_MAX_STREAMNUM);
                
				tParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
                tParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
			}
		}


	} else 
	{ //�¼�

      // ȡPUT ����Ƶ
		TRollCallEpInfo* ptEpInfo = GetRollCallEpInfoById(ptNode->m_wEpID);
		if (NULL != ptEpInfo && MIDSCREENINDEX == wScreenIndex)
		{
			tParam.m_tAddr.m_tRtpAddr = ptEpInfo->m_atPutAuddr[wScreenIndex].m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_atPutAuddr[wScreenIndex].m_tBackRtcpAddr;
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
		}  
	}


}


void CUmsRollCallMgr::GetAudSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam)
{
    if (!ptNode->IsAudRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CUmsRollCallMgr::GetOtherAudSrcAddr rmt ep aud rcv invalid.confID:%d, rmtep:%d, audrcv:%d\n"
			, m_pcConf->GetInsID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		return;
	}

    tParam.m_tAddr.m_tRtpAddr.Clear();
	if (MIDSCREENINDEX != wScreenIndex)
	{
        return;
	}

	u16 wRollCallerEp = 0;
	u16 wCallTargetEp = 0;

	if (m_pcConf->IsChairConf())
	{ //�ϼ�

		TServiceAddr tMixOutAddr;

		wRollCallerEp = GetRollCallerEpId();
		wCallTargetEp = GetCallTargetEpId();
		
		if (ptNode->m_wEpID == wRollCallerEp || ptNode->m_wEpID == wCallTargetEp)
		{ //Ϊ"������" �� "��������"  ȡN-1
			if (NULL != m_tMixRes.m_ptMixRes)
			{
				m_pcConf->GetEapu()->GetMixerChnOutAddr(m_tMixRes.m_ptMixRes, tMixOutAddr, ptNode->m_wEpID, TP_MAX_STREAMNUM);
				tParam.m_tAddr.m_tRtpAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
			}
			
		} else
		{	
			if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
			{ //��Ƶ���� ��Ҫ���Ƚ���
				TTPDsFrom tAddr;
				m_pcConf->GetBas()->GetSpeakerAudBasOutAddr(wScreenIndex, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				
				tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
				
			} else 
			{

				tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndex).m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndex).m_tBackRtcpAddr;
				//tParam.m_bMap = TRUE;    //???????
				tParam.m_dwEqpNode = m_pcConf->m_tEqpConfDs.m_dwEqpNode;
			}
		}

	} 
	else 
	{ // �¼�
		wRollCallerEp = GetRollCallerEpId();
        wCallTargetEp = GetCallTargetEpId();

		if (CALLER_EP_INDEX ==  ptNode->m_wEpID)
		{ // ����Ҫ ���ϼ��� �������ˣ������ˣ���Ƶ
           return; 
		} 
		else if (ptNode->m_wEpID == wRollCallerEp || ptNode->m_wEpID == wCallTargetEp)
		{   //�����˱�������ȡPUT��������Ƶ
			TRollCallEpInfo* ptEpInfo = GetRollCallEpInfoById(ptNode->m_wEpID);
			if (NULL != ptEpInfo)
			{
				tParam.m_tAddr.m_tRtpAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
				tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			} 
 
		} else 
		{
			if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
			{ //��Ƶ���� ��Ҫ���Ƚ���
				TTPDsFrom tAddr;
				m_pcConf->GetBas()->GetSpeakerAudBasOutAddr(wScreenIndex, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				
				tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
				
			} else 
			{
				
				tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndex).m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndex).m_tBackRtcpAddr;
				//tParam.m_bMap = TRUE;    //???????
				tParam.m_dwEqpNode = m_pcConf->m_tEqpConfDs.m_dwEqpNode;
			}
		}


	}

}




void CUmsRollCallMgr::GetRollCallSrcAud(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam)
{
	TCallNode* ptSpeaker = m_pcConf->GetNode(m_pcConf->curSpeakerID());	//�����˿���Ϊ����EP
	TCapNode* ptForeSpeaker = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptSpeaker);
	if (NULL == ptSpeaker || NULL == ptForeSpeaker)
	{
		MdlError(Ums_Mdl_Call, ("CUmsRollCallMgr::GetRollCallSrcAud can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
		return ;
	}

	if ( ptNode->m_wEpID == m_pcConf->curSpeakerID() || ptNode->m_wEpID == ptForeSpeaker->m_wEpID)
	{//������ ����ϯ(����������������)
        GetTargetAudSrcAddr(wScreenIndex, ptNode, tParam);
	} else 
	{
        GetAudSrcAddr(wScreenIndex, ptNode, tParam);
	}
		
}


void CUmsRollCallMgr::GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam )
{
    if (ptNode->IsAudRcvValid())
	{   
		if (GetRollCallerEpId() == ptNode->m_wEpID)
		{ //��ǰĿ��Ϊ������
             TServiceAddr tAudAddr;
             if (m_pcConf->IsChairConf())
			 { //�ϼ���MIX ��ȡN-1
                 if(m_pcConf->GetDualMgr()->IsStart() &&  m_pcConf->GetSpeaker().m_bIsDualMixOn)
				 {   // ����˫������˫����ȡN-1 
					 m_pcConf->GetEapu()->GetMixerChnOutAddr(m_pcConf->GetSpeaker().m_ptAudMix, tAudAddr, ptNode->m_wEpID, TP_MAX_STREAMNUM);
					 
					 tAudParam.m_tAddr.m_tRtpAddr = tAudAddr.m_tAddr.m_tRtpAddr;
					 tAudParam.m_tAddr.m_tBackRtcpAddr = tAudAddr.m_tAddr.m_tBackRtcpAddr;
				     tAudParam.m_dwEqpNode = tAudAddr.m_dwMediaNode;
				 }
				 else
				 {  // �ӵ���mix ��ȡN-1
					 if (NULL != m_tMixRes.m_ptMixRes)
					 {
						 m_pcConf->GetEapu()->GetMixerChnOutAddr(m_tMixRes.m_ptMixRes, tAudAddr, ptNode->m_wEpID, TP_MAX_STREAMNUM);
						 tAudParam.m_tAddr.m_tRtpAddr = tAudAddr.m_tAddr.m_tRtpAddr;
						 tAudParam.m_tAddr.m_tBackRtcpAddr = tAudAddr.m_tAddr.m_tBackRtcpAddr;
				         tAudParam.m_dwEqpNode = tAudAddr.m_dwMediaNode;
					 }
				 }
			 }
			 else
			 { //�¼�ȡPUT ����Ƶ

				 TRollCallEpInfo* ptEpInfo = GetRollCallEpInfoById(ptNode->m_wEpID);
				 if (NULL != ptEpInfo)
				 {
					 tAudParam.m_tAddr.m_tRtpAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
					 tAudParam.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
					 tAudParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
				 } 

			 }
		} 
		else
		{
			if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
			{//��Ƶ���� ��Ҫ���Ƚ���
				TTPDsFrom tAddr;
				m_pcConf->GetBas()->GetSpeakerMixAudBasOutAddr(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);

				tAudParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tAudParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tAudParam.m_dwEqpNode = tAddr.m_dwEqpNode;
			}
			else
			{
				//����������ϯ
				tAudParam.m_tAddr = m_pcConf->GetSpeakerAudMix();
				tAudParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
				tAudParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			}
		}
	}


	if (ptNode->IsVidRcvValid())
	{
		if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat) )
		{// ��Ҫ����
			TTPMediaTransAddr tAddr;
			if (NULL != m_pcConf->GetSpeaker().m_pcSingleBas && m_pcConf->GetVmp()->IsSpeakerInVmp())
			{// �㲥�������䣨�����˺ϳ�ͼ��
				m_pcConf->GetBas()->GetOutChnVidAddr(tAddr, m_pcConf->GetSpeaker().m_pcSingleBas, ptNode->m_tVidRcvFormat.m_tFormat);
				tVidParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tVidParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tVidParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			}
			else
			{// ȡ�������������ϯ
				TCallNode* ptSpeakerNode = m_pcConf->GetNode(m_pcConf->curSpeakerID());
				if (NULL != ptSpeakerNode && ptSpeakerNode->IsChanOn())
				{
					u16 wSeatIndex = ptSpeakerNode->GetSpeaker();
					m_pcConf->GetBas()->GetOutChnSpeakerVidAddr(tVidParam.m_tAddr, wSeatIndex, ptNode->m_tVidRcvFormat.m_tFormat);
					tVidParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
					
				}
			}
		}
		else
		{//
			tVidParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSingleVidDec().m_tRtpAddr;
			tVidParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSingleNetBuf().m_tRcvRtcpAddr;
			tVidParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			tVidParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tVidParam.m_bMap = TRUE;
		}
	}
	
	return ;
}




void CUmsRollCallMgr::AdjustRollCallStatus()
{
    CUmsConfInst* pInst = Inst();

	u16 wCallTarget = GetCallTargetEpId();

	pInst->ChangeSpeaker(wCallTarget, NULL);
    pInst->AdjustNewSpeakerToAllNode();
	
}


void CUmsRollCallMgr::OnRollCallStatusCmdFromUmc( CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TConfRollCallInfo tRollCallInfo;
	TP_SAFE_CAST( tRollCallInfo, ptMsg->GetBody()+sizeof(TLogUser));

	do 
	{
		if (!pInst->IsChairConf())
		{
			MdlError(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromUmc] ConfID:%d opr not top ums\n", pInst->GetInsID()));
			tRollCallInfo.m_emRet = em_StartRollCall_NotTopUms;
			break ;
		}
		
		MdlHint(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromUmc] ConfID:%d, CmdStart:%d, CurrentRollCallUistat:%d CurrentRollCallstat:%d\n", 
			pInst->GetInsID(), 
			tRollCallInfo.m_bStart,
			m_bUIRollcallStatus,
			m_bRollcallStaus));



		tRollCallInfo.m_emRet = em_RollCallOprRsp_Ok;
		RollCallStatusCmdFromUmcCnc(tRollCallInfo);

	}while(0);


	MdlHint(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromUmc] tRollCallInfo.m_emRet = %d\n", tRollCallInfo.m_emRet));

	pInst->NotifyMsgToServiceForUI(evtp_StartRollCall_Ind, &tRollCallInfo, sizeof(TConfRollCallInfo), &tLogUser);
    
	RollCallStatesNotify(tRollCallInfo.m_emRet);

	return;
}




// ��ϯ�������������رյ���
void CUmsRollCallMgr::OnRollCallStatusCmdFromCnc(CTpMsg *const ptMsg) 
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TConfRollCallInfo tRollCallInfo;
	TP_SAFE_CAST( tRollCallInfo, ptMsg->GetBody()+sizeof(TUmsHandle));


	do 
	{
		if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
		{
	        tRollCallInfo.m_emRet = em_StartRollCall_NotTopUms;
			break ;
		}

		MdlHint(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromCnc]  start rollcall ConfID:%d, CmdStart:%d, CurrentRollCallUIStat:%d CurrentRollCallStat:%d\n", 
			pInst->GetInsID(), 
			tRollCallInfo.m_bStart,
			m_bUIRollcallStatus,
			m_bRollcallStaus));

		

        tRollCallInfo.m_emRet = em_RollCallOprRsp_Ok;
        RollCallStatusCmdFromUmcCnc(tRollCallInfo);


	} while (0);


	MdlHint(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromCnc] tRollCallInfo.m_emRet = %d\n", tRollCallInfo.m_emRet));

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UmsConfRollCallUpdate_Ind, &tRollCallInfo, sizeof(TConfRollCallInfo));

    RollCallStatesNotify(tRollCallInfo.m_emRet);

	return;
}



void CUmsRollCallMgr::OnRollCallUpdateListFromCnc(CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TUpdataRollCallList tListInfo;

	TP_SAFE_CAST( tListInfo, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	TUpdataRollCallListRes TRet;
	TRet.m_wConfID = tListInfo.m_wConfID;
	TRet.m_bAdd    = tListInfo.m_bAdd;
	TRet.m_atRollCallMemList = tListInfo.m_atRollCallMemList;


	do{
        
		if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
		{
			MdlError(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d  opr not top ums\n", pInst->GetInsID()));
			
			for(u16 wIndex = 0 ; wIndex < TRet.m_atRollCallMemList.m_wNum; wIndex++)
			{
				TRet.m_emRet[wIndex] = em_UpdateRollCalList_NotTopUms;
			}
			break;
		}

		if (!m_bUIRollcallStatus )
		{			
			MdlError(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d update rollcalllist fail, not start CurrentRollCallUIStat:%d, CurrentRollCallStat:%d\n", 
		             pInst->GetInsID(),
		             m_bUIRollcallStatus,
					 m_bRollcallStaus));

			for(u16 wIndex = 0 ; wIndex < TRet.m_atRollCallMemList.m_wNum; wIndex++)
			{
				TRet.m_emRet[wIndex] = em_UpdateRollCalList_Fail;
			}
			break ;
		}

		MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromCnc] ConfID:%d, CurrentRollCallUIStat:%d, CurrentRollCallStat:%d, caller_target(%d_%d), Isaddlist:%d, update_list_num:%d  oldlistNUM:%d\n", 
			pInst->GetInsID(), 
			m_bUIRollcallStatus,
			m_bRollcallStaus,
			GetRollCallerEpId(),
            GetCallTargetEpId(),
			tListInfo.m_bAdd,
			tListInfo.m_atRollCallMemList.m_wNum,
			m_tRollCallEpList.m_wNum
			));

		AddDelListUmcCnc(tListInfo, TRet);
	
	}while(0);

	
	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UmsConfRollCallUpdataList_Ind, &TRet, sizeof(TUpdataRollCallListRes));

	if (m_bUIRollcallStatus)
	{
        RollCallStatesNotify(em_RollCallOprRsp_Ok);
	    //���״̬
        RollCallPresentStateNotify();
	}
}



void CUmsRollCallMgr::OnRollCallUpdatePresentStateFromCmc(CTpMsg* const ptMsg)
{
	CUmsConfInst* pInst = Inst();

	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TRollCallPresentStateMsg tInfo;
	
	TP_SAFE_CAST( tInfo, ptMsg->GetBody()+sizeof(TUmsHandle));

	u16 wEpIndex = 0;

	MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdatePresentStateFromCnc] ConfID:%d opr NUM:%d\n", pInst->GetInsID(), tInfo.m_wValidNum));
	

	if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
	{
		MdlError(Ums_Mdl_Call, ("[OnRollCallUpdatePresentStateFromCnc] ConfID:%d opr not top ums\n", pInst->GetInsID()));
		//�¼����ظ� 
		return;

	}


	for(u16 wIndex = 0; wIndex < tInfo.m_wValidNum; wIndex++)
	{
		
		wEpIndex = m_tRollCallEpList.GetTargetIndex(tInfo.m_atEpState[wIndex].m_wEpID);
		if (TP_INVALID_INDEX != wEpIndex)
		{
			m_aemPresentState[wEpIndex] = (EmRollCallPresentState)tInfo.m_atEpState[wIndex].m_wEpState;
		}
		
	}

	
    RollCallPresentStateNotify();
}





void CUmsRollCallMgr::OnRollCallNextEpFromCnc(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TRollCallNextEpInfo tNextEpInfo;
	TP_SAFE_CAST( tNextEpInfo, ptMsg->GetBody()+sizeof(TUmsHandle));
    TCallNode* ptargetNode =  NULL;
	
	tNextEpInfo.m_emRet = em_RollCallOprRsp_Ok;

	do{
        
		if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
		{
			tNextEpInfo.m_emRet =  em_RollCallNextEp_NotTopUms;
			break;
		}

		//�����ϵı������� �����ͷ�
		u16 wOldTarget = GetCallTargetEpId();

		MdlHint(Ums_Mdl_Call, ("[OnRollCallNextEpFromCnc] ConfID:%d, CurrentRollCallUIStat:%d,  CurrentRollCallStat:%d, caller:%d, newtarget:%d, oldtarget:%d\n", 
			   pInst->GetInsID(),
               m_bUIRollcallStatus,
			   m_bRollcallStaus,
			   tNextEpInfo.m_wRollCaller,
			   tNextEpInfo.m_wCallTarget,
			   wOldTarget));


		if (VALID_ALL_EPID(wOldTarget) && tNextEpInfo.m_wCallTarget == wOldTarget)
		{
            //��������û��
			MdlHint(Ums_Mdl_Call, ("[OnRollCallNextEpFromCnc] ConfID:%d, rollcalltarget not change = %d\n", pInst->GetInsID(), wOldTarget));

			ptargetNode = m_pcConf->m_pcNodeMgr->GetNode(tNextEpInfo.m_wCallTarget);
			if (NULL == ptargetNode || !ptargetNode->IsChanOn())
			{
				MdlError(Ums_Mdl_Call, ("[OnRollCallNextEpFromCnc] Confid:%d  targetep:%d  is null or not chanon\n", m_pcConf->GetInsID(), wOldTarget));
				tNextEpInfo.m_emRet = em_RollCallNextEp_EpError;
			}

			break;
		}


		if (TRUE == RollCallNextEpFromUmcCnc(tNextEpInfo))
		{
			AdjustRollCallStatus();
			//�ͷ�ǰһ���������ߵ� ��ƵPUTͨ���� GetVidAudͨ��
			ReleaseRollCallEpChan(wOldTarget);
		}
		

	}while(0);

	MdlHint(Ums_Mdl_Call, ("[OnRollCallNextEpFromCnc] ret:%d\n", tNextEpInfo.m_emRet));

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UmsConfRollCallNextEp_Ind, &tNextEpInfo, sizeof(TRollCallNextEpInfo));

	if (tNextEpInfo.m_emRet == em_RollCallNextEp_CreateChanFail)
	{
		MdlError(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromcnc] RollCallNextEp_CreateChanFail\n"));

		StopRollCallModle();

		RollCallStatesNotify(tNextEpInfo.m_emRet);

		// ��ֹ������Ϣ
		m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_CREATE_CHAN_FAIL, m_pcConf->chairID());
	}
	else if (tNextEpInfo.m_emRet == em_RollCallOprRsp_Ok)
	{
		RollCallStatesNotify(tNextEpInfo.m_emRet);
	}
	else
	{

	}
	return;
}




BOOL32 CUmsRollCallMgr::AddRollCallEpChan(u16 wEpId)
{
	TRollCallEpInfo *pEpInfo = NULL;
	CUmsConfInst* pInst = m_pcConf;
	
	
	pEpInfo = m_tRollCallInfo.GetRollCallEpInfo(wEpId);
	if (NULL == pEpInfo)
	{
		return FALSE;
	}
	
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(pEpInfo->m_wEpID);
	TCapNode* ptForeFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptForeFatherNode || !ptNode->IsChanOn() || !ptForeFatherNode->IsChanOn())
	{
		MdlHint(Ums_Mdl_Call, ("[AddRollCallEpChan] Ep erro! ConfID:%d, EpID:%d\n", pInst->GetInsID(), pEpInfo->m_wEpID));
		return FALSE;
	}
	
	//m_tRollCallInfo.AddEpChanInfo(ptNode, emEpType);
	
	
	TGetVidAddr tAddr;
	EmGetVidRes emRes = pInst->GetVidAudEx()->AssignByScreen(pInst, ptNode->m_wEpID, MIDSCREENINDEX, em_GetVid_OnlyAud,
		TCallVidFormat(), FALSE, tAddr, pEpInfo->m_wGetindex);
	if (emRes != em_GetVid_Success)
	{
		return FALSE;
	}
	
	pEpInfo->SetGetAudAddr(tAddr);

    //���ƻ᳡������
	m_pcConf->GetCallMgr()->FlowControl(wEpId, FLOW_CTROL_ALL_ENC, ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate);

	if(wEpId == GetCallTargetEpId())
	{
		m_pcConf->AskKeyByEpID(wEpId, EmAskKeySpeaker);
	}else
	{
		m_pcConf->AskKeyByEpID(wEpId, EmAskKeyChair);
	}


	if (ptNode != ptForeFatherNode && ptNode->IsAudRcvValid())
	{//�¼��᳡���򿪵��¼���һ·��Ƶͨ�� �������¼��ġ������ˡ� �� ���������ˡ���N-1 ��Ƶ��
		if (!pInst->GetPutAudMgr()->AssignAudChnl(ptNode->m_wEpID, em_putauduser_rollcall, pEpInfo->m_atPutAuddr))
		{
			MdlError(Ums_Mdl_Call, ("[AddRollCallEpChan] AssignAudChnl Fail! ConfID:%d, EpID:%d\n", 
				pInst->GetInsID(), ptNode->m_wEpID));
			return FALSE;
		}
	}
	return TRUE;
}



void CUmsRollCallMgr::ReleaseRollCallEpChan(u16 wEpId)
{
	TRollCallEpInfo *pEpInfo = NULL;
	CUmsConfInst* pInst = m_pcConf;

	if (TP_INVALID_INDEX == wEpId)
	{
         return;
	}

	pEpInfo = m_tRollCallInfo.GetRollCallEpInfo(wEpId);
	if (NULL == pEpInfo)
	{
		return;
	} 
	
	if ( pEpInfo->m_wGetindex < TP_UMS_MAX_CALLNUM )
	{
		CUmsConfInst::GetVidAudEx()->Release(pInst, pEpInfo->m_wGetindex);
		pEpInfo->m_wGetindex = TP_INVALID_INDEX;
	}

	//�ر�
	m_pcConf->GetCallMgr()->FlowControl(wEpId, FLOW_CTROL_ALL_ENC, 0);


	if (0 != pEpInfo->m_cToPutAuddrDsInfo.GetElementNum())
	{
		CNetPortMgr::FreeMediaTrans(m_pcConf, pEpInfo->m_cToPutAuddrDsInfo);
	}
	pEpInfo->m_cToPutAuddrDsInfo.Clear();

	pInst->GetPutAudMgr()->ReleaseAudChnl(pEpInfo->m_wEpID, em_putauduser_rollcall);


    pEpInfo->Clear();

}


BOOL32 CUmsRollCallMgr::RollCallNextEpFromUmcCnc(TRollCallNextEpInfo &tCallNextEpInfo)
{
	u16 wCurCaller  = tCallNextEpInfo.m_wRollCaller;
	u16 wCallTarget = tCallNextEpInfo.m_wCallTarget;

	if (!m_bUIRollcallStatus)
	{
		tCallNextEpInfo.m_emRet = em_RollCallNextEp_NotStart;
		return FALSE;
	}

	if (wCurCaller != m_tRollCallEpList.GetRollCaller())
	{
		tCallNextEpInfo.m_emRet = em_RollCallNextEp_CallerChg;
		return FALSE;
	}

	if (wCallTarget == wCurCaller)
	{
        tCallNextEpInfo.m_emRet = em_RollCallNextEp_EpError;
        return FALSE;
	}

	if (FALSE == CheckRollCallEpCap(wCallTarget))
	{
        tCallNextEpInfo.m_emRet = em_RollCallNextEp_EpError;
        return FALSE;
	}

    m_tRollCallEpList.SetRollCallTarget(wCallTarget);


    if (FALSE == UpdateRollCallEpInfo(wCallTarget))
	{
		tCallNextEpInfo.m_emRet = em_RollCallNextEp_CreateChanFail;
        return FALSE;
	}

	if (FALSE == AddRollCallEpChan(wCallTarget))
    {
		MdlError(Ums_Mdl_Call, ("[RollCallNextEpFromUmcCnc] add RollCalltarget chan fail \n"));

        tCallNextEpInfo.m_emRet = em_RollCallNextEp_CreateChanFail;
        return FALSE;
	}

	if (!m_bRollcallStaus)
	{   
		m_bRollcallStaus = TRUE;   //������������
	}

    RollCallInfoNotifyToLowUms(em_RollCallNotyUpNodeInfo);
	//���� �����ߣ���������
    MixRollCallerAndTarget();

	RollCallAudPudDown(wCurCaller);
    RollCallAudPudDown(wCallTarget);

    return TRUE;
}

void CUmsRollCallMgr::OnRollCallUpdateListFromUmc(CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUpdataRollCallList tListInfo;

	TP_SAFE_CAST( tListInfo, ptMsg->GetBody()+sizeof(TLogUser));
	
	TUpdataRollCallListRes TRet;
	TRet.m_wConfID = tListInfo.m_wConfID;
	TRet.m_bAdd    = tListInfo.m_bAdd;
	TRet.m_atRollCallMemList = tListInfo.m_atRollCallMemList;

	do 
    {
		if (!pInst->IsChairConf())
		{
			for(u16 wIndex = 0 ; wIndex < TRet.m_atRollCallMemList.m_wNum; wIndex++)
			{
				MdlError(Ums_Mdl_Call, ("[OnRollCallUpdateListFromUmc] ConfID:%d opr not top ums\n", pInst->GetInsID()));
				TRet.m_emRet[wIndex] = em_UpdateRollCalList_NotTopUms;
			}
			break ;
		}

		if (!m_bUIRollcallStatus )
		{
			MdlError(Ums_Mdl_Call, ("[OnRollCallUpdateListFromUmc] ConfID:%d update rollcalllist fail, not start CurrentRollCallUIStat:%d, CurrentRollCallStat:%d\n", 
				     pInst->GetInsID(),
				     m_bUIRollcallStatus,
				     m_bRollcallStaus));

			for(u16 wIndex = 0 ; wIndex < TRet.m_atRollCallMemList.m_wNum; wIndex++)
			{
				TRet.m_emRet[wIndex] = em_UpdateRollCalList_Fail;
			}
			break ;
		}

		MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdateListFromUmc] ConfID:%d, CurrentRollCallUIStat:%d, CurrentRollCallStat:%d, caller_target(%d_%d), Isaddlist:%d, update_list_num:%d  oldlistNUM:%d\n", 
			pInst->GetInsID(), 
			m_bUIRollcallStatus,
			m_bRollcallStaus,
			GetRollCallerEpId(),
            GetCallTargetEpId(),
			tListInfo.m_bAdd,
			tListInfo.m_atRollCallMemList.m_wNum,
			m_tRollCallEpList.m_wNum
			));


		AddDelListUmcCnc(tListInfo, TRet);
		
    } while (0);
	
	
	
	pInst->NotifyMsgToServiceForUI(evtp_RollCallUpdateList_Ind, &TRet, sizeof(TUpdataRollCallListRes), &tLogUser);
	
	if (m_bUIRollcallStatus)
	{
		//�����б�̶�noty �ɹ�
		RollCallStatesNotify(em_RollCallOprRsp_Ok);
		//���״̬
        RollCallPresentStateNotify();
	}

}



void CUmsRollCallMgr::OnRollCallUpdatePresentStateFromUmc(CTpMsg* const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TRollCallPresentStateMsg tInfo;
	
	TP_SAFE_CAST( tInfo, ptMsg->GetBody()+sizeof(TLogUser));

    u16 wEpIndex = 0;

	MdlHint(Ums_Mdl_Call, ("[OnRollCallUpdatePresentStateFromUmc] ConfID:%d opr NUM:%d\n", pInst->GetInsID(), tInfo.m_wValidNum));

	if(!m_pcConf->IsChairConf())
	{
		MdlError(Ums_Mdl_Call, ("[OnRollCallUpdatePresentStateFromUmc] ConfID:%d opr not top ums\n", pInst->GetInsID()));
		//�¼����ظ� 
		return;
	}


	for(u16 wIndex = 0; wIndex < tInfo.m_wValidNum; wIndex++)
	{

		 wEpIndex = m_tRollCallEpList.GetTargetIndex(tInfo.m_atEpState[wIndex].m_wEpID);
		 if (TP_INVALID_INDEX != wEpIndex)
		 {
              m_aemPresentState[wEpIndex] = (EmRollCallPresentState)tInfo.m_atEpState[wIndex].m_wEpState;
		 }
		 
	}

    RollCallPresentStateNotify();
}


void CUmsRollCallMgr::OnRollCallNextEpFromUmc(CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TRollCallNextEpInfo tCallNextEpInfo;
	TP_SAFE_CAST( tCallNextEpInfo, ptMsg->GetBody()+sizeof(TLogUser));
    TCallNode* ptargetNode =  NULL;

	tCallNextEpInfo.m_emRet = em_RollCallOprRsp_Ok;

    do 
    {
		if (!pInst->IsChairConf())
		{
			tCallNextEpInfo.m_emRet = em_RollCallNextEp_NotTopUms;
			break ;
		}

		//�����ϵı�������  �����ͷ�
        u16 wOldTarget = GetCallTargetEpId();

		MdlHint(Ums_Mdl_Call, ("[OnRollCallNextEpFromUmc] ConfID:%d, CurrentRollCallUIStat:%d, CurrentRollCallStat:%d, caller:%d, newtarget:%d, oldtarget:%d\n", 
			    pInst->GetInsID(),
				m_bUIRollcallStatus,
				m_bRollcallStaus,
				tCallNextEpInfo.m_wRollCaller,
				tCallNextEpInfo.m_wCallTarget, 
				wOldTarget));


		if (VALID_ALL_EPID(wOldTarget) && tCallNextEpInfo.m_wCallTarget == wOldTarget)
		{
            //��������û��
			MdlHint(Ums_Mdl_Call, ("[OnRollCallNextEpFromUmc] ConfID:%d, rollcalltarget not change = %d\n", pInst->GetInsID(), wOldTarget));

			ptargetNode = m_pcConf->m_pcNodeMgr->GetNode(tCallNextEpInfo.m_wCallTarget);
			if (NULL == ptargetNode || !ptargetNode->IsChanOn())
			{
				MdlError(Ums_Mdl_Call, ("[OnRollCallNextEpFromUmc] Confid:%d  targetep:%d  is null or not chanon\n", m_pcConf->GetInsID(), wOldTarget));
				tCallNextEpInfo.m_emRet = em_RollCallNextEp_EpError;
			}
			
			break;
		}

		
		if (TRUE == RollCallNextEpFromUmcCnc(tCallNextEpInfo))
		{
			AdjustRollCallStatus();
			
			//�ͷ�ǰһ���������ߵ� ��ƵPUTͨ���� GetVidAudͨ��  �Լ�EP
			ReleaseRollCallEpChan(wOldTarget);
			
		} 

    } while (0);


	MdlHint(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromUmc] tRollCallInfo.m_emRet = %d\n", tCallNextEpInfo.m_emRet));

	pInst->NotifyMsgToServiceForUI(evtp_RollCallNext_Ind, &tCallNextEpInfo, sizeof(TRollCallNextEpInfo), &tLogUser);


	if (tCallNextEpInfo.m_emRet == em_RollCallNextEp_CreateChanFail)
	{
		MdlError(Ums_Mdl_Call, ("[OnRollCallStatusCmdFromUmc] RollCallNextEp_CreateChanFail\n"));

		StopRollCallModle();

		RollCallStatesNotify(tCallNextEpInfo.m_emRet);
 		// ��ֹ������Ϣ
		m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_CREATE_CHAN_FAIL, m_pcConf->chairID());
	}
	else if (tCallNextEpInfo.m_emRet == em_RollCallOprRsp_Ok)
	{
		RollCallStatesNotify(tCallNextEpInfo.m_emRet);
	}
	else
	{

	}

	return;
}



BOOL32 CUmsRollCallMgr::HandlerFromUmc(CTpMsg *const ptMsg)
{
	switch (ptMsg->GetEvent())
	{

	case evtp_StartRollCall_cmd:
		{
			OnRollCallStatusCmdFromUmc(ptMsg);
            break;
		}

	case evtp_RollCallNext_cmd:          
		{    
            OnRollCallNextEpFromUmc(ptMsg);
			break;
		}

    case evtp_RollCallUpdateList_cmd:
		{
            OnRollCallUpdateListFromUmc(ptMsg);  
			break;
		}

	case evtp_RollCall_PresentState:
		{
            OnRollCallUpdatePresentStateFromUmc(ptMsg);
			break;
		}

	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}


BOOL32 CUmsRollCallMgr::HandlerFromStack( CTpMsg *const ptMsg )
{
	//Inst()->GetPutAudMgr()->Handler(ptMsg); //���������´�����Ƶͨ������Ӧ

	switch (ptMsg->GetEvent())
	{

    case ev_UmsConfRollCallUpdate_Cmd:
		{
			OnRollCallStatusCmdFromCnc(ptMsg);
			break;
		}
	
    case ev_UmsConfRollCallNextEp_Cmd:
		{
            OnRollCallNextEpFromCnc(ptMsg);
            break;
		}

    case ev_UmsConfRollCallUpdataList_Cmd:
		{
            OnRollCallUpdateListFromCnc(ptMsg);
			break;
		}

	case evtp_UmsRollUpdate_PresentState:
		{
            OnRollCallUpdatePresentStateFromCmc(ptMsg);
			break;
		}

	case evtp_UmsRollCallScreenStat_Notify:
		{
			OnCasecadeRollCallNtfy(ptMsg);
			break;
		}
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}


BOOL32 CUmsRollCallMgr::CheckRollCallEpCap(u16 wEpId)
{
	CUmsConfInst* pInst = Inst();

    TCallNode* ptNode =  pInst->m_pcNodeMgr->GetNode(wEpId);
	TCapNode* ptNodeFar =  pInst->GetNodeMgr()->GetForeFatherNode(ptNode);

	if (NULL == ptNode || NULL == ptNodeFar || !ptNode->IsChanOn() || !ptNodeFar->IsChanOn())
	{
         MdlError(Ums_Mdl_Call, ("[CheckRollCallEpCap] conf:%d  ep:%d  ep error  Node== NULL or not chanon\n", pInst->GetInsID(), wEpId));

		 return FALSE;
	}


	if (ptNodeFar->IsMcu())
	{   //mcu �Լ�����Ļ᳡������Ϊ�����˺ͱ������ˣ���Ϊ����Ƶ�������� put ��ƵҲ������
		MdlError(Ums_Mdl_Call, ("[CheckRollCallEpCap] conf:%d ep:%d ep is mcu or under mcu\n", pInst->GetInsID(),wEpId));
        return FALSE;
	}


	if (!ptNode->IsVidSndValid() || !ptNode->IsMtEp()  || ptNode->IsVRS() || ptNode->IsG400())
	{

		MdlError(Ums_Mdl_Call, ("[CheckRollCallEpCap]  conf:%d  ep:%d  ep error  IsVidSndValid:%d  isMtEp:%d isvrs:%d isg400:%d\n", 
				pInst->GetInsID(),
			    wEpId, 
				ptNode->IsVidSndValid(),
				ptNode->IsMtEp(),
                ptNode->IsVRS(),
                ptNode->IsG400()));

		
		return FALSE;
	}
	

	return TRUE;
}



BOOL32 CUmsRollCallMgr::UpdateRollCallEpInfo( u16 wEpId)
{
    TCallNode* ptNode =  m_pcConf->m_pcNodeMgr->GetNode(wEpId);

	if (NULL == m_tRollCallInfo.AddEp(ptNode))
	{
		MdlError(Ums_Mdl_Call, ("UpdateRollCallEpInfo ep:%d error, Ep Is Full \n", wEpId));	
		return FALSE;
	}

    return TRUE;
}


BOOL32 CUmsRollCallMgr::IsNeedSendRollCallerSmall()
{
     if (m_pcConf->IsChairConf())
	 {
         return FALSE;
	 }


	 u16 wRollCaller = GetRollCallerEpId();
	 u16 wCallTarget = GetCallTargetEpId();
	 TCallNode* ptCallerNode     = NULL;
	 TCallNode* ptTargetNodeNode = NULL;


     if (VALID_ALL_EPID(wRollCaller) && !VALID_ALL_EPID(wCallTarget))
	 {
		 //�������ڸ��¼�, �������߲��ڸ��¼� С����ͨ���������������
		 return TRUE;
	 }

	 if (VALID_ALL_EPID(wRollCaller) && VALID_ALL_EPID(wCallTarget))
	 { 
		 //������ �������� ���ڸ��¼�
		 ptCallerNode     = m_pcConf->GetNodeMgr()->GetNode(wRollCaller);
         ptTargetNodeNode = m_pcConf->GetNodeMgr()->GetNode(wCallTarget);

		 if (NULL != ptCallerNode
			 && ptCallerNode->IsChanOn() 
			 && ptCallerNode->IsSmallVidSnd() 
			 && ptCallerNode->IsThreeVidSnd()
			 && NULL != ptTargetNodeNode
			 && !ptTargetNodeNode->IsThreeVidSnd())
		 {   // ������ �����������������ǵ����� ���ϼ�put ������С����
             return TRUE;
		 }
	 }


     return FALSE;
}



BOOL32 CUmsRollCallMgr::StartRollCallModle(TConfRollCallInfo& tRollCallInfo)
{

    u16 wCurCaller = tRollCallInfo.m_atRollCallMemList.m_wRollCaller; 
    if(FALSE == UpdateRollCallEpInfo(wCurCaller))
    {
        tRollCallInfo.m_emRet = em_StartRollCall_CreateChanFail;
		return FALSE;
	}


	if(FALSE == AddRollCallEpChan(wCurCaller))
	{
		tRollCallInfo.m_emRet = em_StartRollCall_CreateChanFail;
		MdlError(Ums_Mdl_Call, ("[StartRollCallModle] add RollCaller chan fail\n"));
        return FALSE;
	}

	if (0 == GetRollCallerToVirRollCaller())
	{
        tRollCallInfo.m_emRet = em_StartRollCall_CreateChanFail;
		MdlError(Ums_Mdl_Call, ("[StartRollCallModle] GetRollCallerToVirRollCaller fail\n"));
        return FALSE;
	}

	m_bUIRollcallStatus = TRUE;

    return TRUE;
}


BOOL32 CUmsRollCallMgr::UptateRollCallListFromUI(TRollCallList  &tRollCallList)
{
	CUmsConfInst* pInst = Inst();
    TCallNode* ptNode = NULL;
	TCapNode*ptNodeFar = NULL;

	// �����б����
    m_tRollCallEpList.Clear();

	//�����߼�飬���õ�����
	ptNode = pInst->GetNode(tRollCallList.m_wRollCaller);
	if (NULL == ptNode )
	{
		MdlError(Ums_Mdl_Call, ("[UptateRollCallListFromUI]  caller:%d  ep error  Node== NULL \n", tRollCallList.m_wRollCaller));
		return FALSE;
	}

	if (!ptNode->IsVidSndValid() || !ptNode->IsMtEp()  || ptNode->IsVRS() || ptNode->IsG400())
	{

		MdlError(Ums_Mdl_Call, ("[UptateRollCallListFromUI]  caller:%d  ep error  IsVidSndValid:%d  isMtEp:%d isvrs:%d isg400:%d\n", 
				tRollCallList.m_wRollCaller, 
				ptNode->IsVidSndValid(),
				ptNode->IsMtEp(),
                ptNode->IsVRS(),
                ptNode->IsG400()));

		return FALSE;
	}

	m_tRollCallEpList.SetRollCaller(tRollCallList.m_wRollCaller);


// 	// �������߼��
// 	if (tRollCallList.m_wCallTarget == tRollCallList.m_wRollCaller)
// 	{
// 		MdlError(Ums_Mdl_Call, ("[UptateRollCallListFromUI]  caller %d == target %d\n", 
// 			     tRollCallList.m_wRollCaller, 
// 			     tRollCallList.m_wCallTarget));
// 
//         return FALSE;
// 	}
// 
// 	ptNode = pInst->GetNode(tRollCallList.m_wCallTarget);
// 	if (NULL == ptNode)
// 	{
// 		MdlError(Ums_Mdl_Call, ("[UptateRollCallListFromUI]  Target:%d  ep error  Node== NULL \n", tRollCallList.m_wCallTarget));
//         return FALSE;
// 	}

// 	if ( !ptNode->IsVidSndValid() || !ptNode->IsMtEp()  || ptNode->IsVRS() || ptNode->IsG400())
// 	{
// 
// 		MdlError(Ums_Mdl_Call, ("[UptateRollCallListFromUI]  Target:%d  ep error  IsVidSndValid:%d  isMtEp:%d isvrs:%d isg400:%d\n", 
// 				tRollCallList.m_wCallTarget, 
// 				ptNode->IsVidSndValid(),
// 				ptNode->IsMtEp(),
//                 ptNode->IsVRS(),
//                 ptNode->IsG400()));
// 
// 		
// 		return FALSE;
// 	}

// 	m_tRollCallEpList.AddRollCallTarget(tRollCallList.m_wCallTarget);
// 	m_tRollCallEpList.SetRollCallTarget(tRollCallList.m_wCallTarget);


	u16 wEpId = 0;
	for (u16 wIndex = 0; wIndex < tRollCallList.m_wNum; wIndex++)
	{
		wEpId = tRollCallList.m_awList[wIndex];
		ptNode = pInst->GetNode(wEpId);
		ptNodeFar = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
		if (NULL != ptNode && NULL != ptNodeFar && !ptNodeFar->IsMcu() && ptNode->IsVidSndValid() && ptNode->IsMtEp() && !ptNode->IsVRS() && !ptNode->IsG400())
		{  // mcu �Լ�����Ļ᳡������Ϊ�������ˣ���Ϊ����Ƶ�������� put ��ƵҲ������
			m_tRollCallEpList.AddRollCallTarget(wEpId);
		}
	}


// 	if (0 == m_tRollCallEpList.GetRollCallTargetNum())
// 	{
// 		m_tRollCallEpList.Clear();
// 		return FALSE;
// 	}
	

	MdlHint(Ums_Mdl_Call, ("[UptateRollCallListFromUI]  updata list ok Caller= %d totalNum = %d\n", 
		                  m_tRollCallEpList.GetRollCaller(), 
						  m_tRollCallEpList.GetRollCallTargetNum()));

	return TRUE;
}


void CUmsRollCallMgr::GetRollCallEpAudAddr(u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr)
{
	// ���
	tAddr.Clear();
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode*  ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("[GetRollCallEpAudAddr] FineNode Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	
	TRollCallEpInfo* ptEpInfo = m_tRollCallInfo.GetRollCallEpInfo(wEpId);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		MdlError(Ums_Mdl_Call, ("[GetRollCallEpAudAddr] FineEpInfo Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	

	tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tAudAddr.m_tRtpAddr;
	tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tAudAddr.m_tBackRtcpAddr;
	tAddr.m_dwMediaNode = ptEpInfo->m_dwMediaNode;

	
	return;
}


void CUmsRollCallMgr::OpenEpDownAudCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TVidChanCmd* ptVidCmd = (TVidChanCmd*)(ptMsg->GetBody() + sizeof(TUmsHandle));

	EmPutAudUser emUser = (EmPutAudUser)ptVidCmd->m_atUpRtp[1].m_tAddr.m_wPort;

	if (em_putauduser_rollcall != emUser)
	{
		return;
	}

	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(ptVidCmd->m_tEpKey.m_wEpID);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{

		return;
	}
	
	MdlHint(Ums_Mdl_Call, ("[OpenEpDownAudCmd] ConfID:%d, wEpID:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
	
	if (pInst->IsChairConf())
	{
		return;
	}

	/*
	EMRollCallEpMem emEpType;
    if (ptNode->m_wEpID == GetRollCallerEpId())
	{
        emEpType = em_RollCallerEp;
	} else if (ptNode->m_wEpID == GetCallTargetEpId())
	{
        emEpType = em_CallTargetEp;
	} else
	{
		return;
	}
    */


	TRollCallEpInfo* ptEpInfo = m_tRollCallInfo.AddEp(ptNode);
	if (NULL == ptEpInfo)
	{
		MdlError(Ums_Mdl_Call, ("[OpenEpDownAudCmd] Ep Is Full. ConfID:%d, EpId:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
		return;
	}
	
	
	m_pcConf->GetPutAudMgr()->GetAudLocalAddr(ptNode->m_wEpID, em_putauduser_rollcall, ptEpInfo->m_atPutAuddr);
	return;
}


void CUmsRollCallMgr::OpenEpDownAudAck( CTpMsg *const ptMsg )
{
	if (Inst()->IsChairConf())
	{
		TUmsHandle tInHandle = *(TUmsHandle*)(ptMsg->GetBody());
		TVidChanAck tVidAck = *(TVidChanAck*)(ptMsg->GetBody() + sizeof(TUmsHandle));
		
		EmPutAudUser emUser = tVidAck.m_atUpBackRtcp[1].m_tAddr.m_wPort;
		if (em_putauduser_rollcall != emUser)
		{
			return;
		}

		TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tInHandle.GetEpID());
		if ( NULL == ptForeNode )
		{
			MdlError(Ums_Mdl_Call, ("[OpenEpDownAudAck] ptSrcCapNode is NULL . ConfID:%d, handleEpID:%d\n", Inst()->GetInsID(), tInHandle.GetEpID()));
			return ;
		}
		
		//���Ǳ�����㣬��ȡ�øû᳡�ı���EpID
		if ( ptForeNode->IsUms() )
		{
			TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tVidAck.m_tEpKey.m_wEpID);
			if ( NULL == ptNode || !ptNode->m_bUsed )
			{
				MdlError(Ums_Mdl_Call, ("[OpenEpDownAudAck] ptNode is NULL . ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tVidAck.m_tEpKey.m_wEpID));
				return ;
			}
			tVidAck.m_tEpKey.m_wEpID = ptNode->m_wEpID;
		}
		
		MdlHint(Ums_Mdl_Call, ("[OpenEpDownAudAck] ConfID:%d, wEpID:%d\n", Inst()->GetInsID(), tVidAck.m_tEpKey.m_wEpID));
		
		TRollCallEpInfo* ptEpInfo = m_tRollCallInfo.GetRollCallEpInfo(tVidAck.m_tEpKey.m_wEpID);
		if (NULL != ptEpInfo && tVidAck.m_wReason != TP_RET_OK)
		{

			MdlError(Ums_Mdl_Call, ("[OpenEpDownAudAck]  put aud error \n"));
	
			StopRollCallModle();
        //RollCallStatesNotify(em_Error_StopRollCall);
		}

	}

	return;
}


void CUmsRollCallMgr::CloseEpDownAudCmd( CTpMsg *const ptMsg )
{
	u16 wEpID;
	u32	dwType;
	TP_SAFE_CAST( wEpID, ptMsg->GetBody() + sizeof(TUmsHandle));
	TP_SAFE_CAST( dwType, ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(u16));
	
	EmPutAudUser emUser = (EmPutAudUser)dwType;
	if (emUser != em_putauduser_rollcall)
	{
		return;
	}


	tpHint(Ums_Mdl_Call, "[CloseEpDownAudCmd] ConfID:%d, wEpID:%d, user:%d.\n", Inst()->GetInsID(), wEpID, emUser);
	
	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(wEpID);
	if (NULL == ptNode)
	{
		return;
	}
	
	m_tRollCallInfo.DelEp(wEpID);


}



void CUmsRollCallMgr::MakeNotifyMsg(TRollCallCasecadeNtfy &tNtfy, EMRollCallNotyToLowUmsType emNotyType, u16 wCaller, u16 wTarget)
{
	tNtfy.Clear();

    tNtfy.m_NotyType =  emNotyType;

    tNtfy.m_bIsRollCallModle = m_bRollcallStaus;
	if (!tNtfy.m_bIsRollCallModle)
	{
        return;
	}

    tNtfy.m_NodeInfo[em_RollCallerEp].m_wEpId = wCaller;
	tNtfy.m_NodeInfo[em_CallTargetEp].m_wEpId = wTarget;

    TCallNode *pCallerNode = m_pcConf->GetNodeMgr()->GetNode(GetRollCallerEpId());
	TCallNode *pTargetNode = m_pcConf->GetNodeMgr()->GetNode(GetCallTargetEpId());

	if (NULL != pCallerNode)
	{
        tNtfy.m_NodeInfo[em_RollCallerEp].m_wVidSndNum  = pCallerNode->m_wVidSndNum;
		tNtfy.m_NodeInfo[em_RollCallerEp].m_wVidRcvNum  = pCallerNode->m_wVidRcvNum;
		
		tNtfy.m_NodeInfo[em_RollCallerEp].m_wAudSndNum  = pCallerNode->m_wAudSndNum;
		tNtfy.m_NodeInfo[em_RollCallerEp].m_wAudRcvNum  = pCallerNode->m_wAudRcvNum;

		tNtfy.m_NodeInfo[em_RollCallerEp].m_wSpeakerSeat = pCallerNode->GetSpeaker();
		tNtfy.m_NodeInfo[em_RollCallerEp].m_Alias        = pCallerNode->m_tConfName;
	}

	if (NULL != pTargetNode)
	{
		tNtfy.m_NodeInfo[em_CallTargetEp].m_wVidSndNum  = pTargetNode->m_wVidSndNum;
		tNtfy.m_NodeInfo[em_CallTargetEp].m_wVidRcvNum  = pTargetNode->m_wVidRcvNum;
		
		tNtfy.m_NodeInfo[em_CallTargetEp].m_wAudSndNum  = pTargetNode->m_wAudSndNum;
		tNtfy.m_NodeInfo[em_CallTargetEp].m_wAudRcvNum  = pTargetNode->m_wAudRcvNum;
		
        tNtfy.m_NodeInfo[em_CallTargetEp].m_wSpeakerSeat = pTargetNode->GetSpeaker();
		tNtfy.m_NodeInfo[em_CallTargetEp].m_Alias        = pTargetNode->m_tConfName;
	}

}


void CUmsRollCallMgr::RollCallInfoNotifyToLowUms(EMRollCallNotyToLowUmsType emNotyType)
{
	CUmsConfInst* pInst = Inst();
	if (!pInst->IsChairConf())
	{
		return;
	}



	TCapNode* pNotyUms = NULL;

    u16 wCallerEpId = GetRollCallerEpId(); 
	u16 wTargetEpId = GetCallTargetEpId();
    TCallNode* pCallNode   = NULL;
	TCallNode* pTargetNode = NULL;

	u16 wCallerTmp = 0;
	u16 wTargetTmp = 0;

	if (emNotyType == em_RollCallNotyChgCallerSteat)
	{
        pNotyUms = pInst->m_pcNodeMgr->GetForeFatherNode(wCallerEpId);
	}


	TUmsHandle tHandle;
    TRollCallCasecadeNtfy tNtfy;

	for (TCapNode* ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}

        if (NULL != pNotyUms && ptNode != pNotyUms)
		{
			//���pNotyUms ��Ч����ֻ֪ͨ��pNotyUms
            continue;
		}
				
		if (ptNode->IsUms())
		{

			if (m_bRollcallStaus)
			{
				pCallNode   = Inst()->GetNodeMgr()->GetNodeUnderThisUms(ptNode, wCallerEpId);
				pTargetNode = Inst()->GetNodeMgr()->GetNodeUnderThisUms(ptNode, wTargetEpId);

				wCallerTmp = (NULL != pCallNode)?pCallNode->m_wLowChildEpID:TP_INVALID_INDEX;
				wTargetTmp = (NULL != pTargetNode)?pTargetNode->m_wLowChildEpID:TP_INVALID_INDEX;
			}
			else
			{
				wCallerTmp = TP_INVALID_INDEX;
				wTargetTmp = TP_INVALID_INDEX;
			}


            MakeNotifyMsg(tNtfy, emNotyType, wCallerTmp, wTargetTmp);
            pInst->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tHandle, evtp_UmsRollCallScreenStat_Notify, &tNtfy, sizeof(tNtfy));
		}	
	}
	
	return;
}

                      
void CUmsRollCallMgr::AdjustInnerSpeaker(TCallNode* ptNode)
{
	if (!m_pcConf->IsChairConf())
	{
        return;
	}
    
	if (ptNode->m_wEpID != GetRollCallerEpId())
	{
        return;
	}

    RollCallInfoNotifyToLowUms(em_RollCallNotyChgCallerSteat);
}



void CUmsRollCallMgr::OnCasecadeRollCallNtfy(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	if (pInst->IsChairConf())
	{
		return;
	}
	
	TRollCallCasecadeNtfy tNtfy;	
	TP_SAFE_CAST(tNtfy, ptMsg->GetBody() + sizeof(TUmsHandle));
	
	MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnCasecadeRollCallNtfy] ConfID:%d, NtfyRollCallModle:%d, CallerId:%d, TargetId:%d, NowRollCallModle:%d.\n",
		pInst->GetInsID(), tNtfy.m_bIsRollCallModle, tNtfy.m_NodeInfo[em_RollCallerEp].m_wEpId, tNtfy.m_NodeInfo[em_CallTargetEp].m_wEpId, m_bRollcallStaus));
	
	
	
	if(tNtfy.m_bIsRollCallModle)
	{

        if (!m_bRollcallStaus)
		{   //�ǵ���ģʽȴ��������ģʽ������һ��ԭʼ����ķ�����    
            m_wBackSpeaker = m_pcConf->curSpeakerID();
		}

        m_bRollcallStaus = TRUE;

		if (em_RollCallNotyChgCallerSteat == tNtfy.m_NotyType)
		{
            TCapNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetCapsetNode(m_pcConf->curSpeakerID());
			if( NULL != ptSpeaker )
			{
				m_pcConf->GetNodeFsm()->UpdateMediaTrans(ptSpeaker);
			}
		}

		m_tRollCallEpList.SetRollCaller(tNtfy.m_NodeInfo[em_RollCallerEp].m_wEpId);
		m_tRollCallEpList.SetRollCallTarget(tNtfy.m_NodeInfo[em_CallTargetEp].m_wEpId);
		m_tNoty = tNtfy;
	}
	else
	{
        StopRollCallModle();
	}
	
	return;
}


void CUmsRollCallMgr::RollCallAudPudDown(u16 wEpId)
{
	CUmsConfInst* pInst = Inst();

	if (!pInst->IsChairConf())
	{ 
         return;
	}

    TCallNode *pNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode  *pFartherNode = pInst->GetNodeMgr()->GetForeFatherNode(wEpId);
    if (pNode != pFartherNode)
	{// ���¼�
         CNetPortMgr::PutAudDownToRollCallEp(pInst, pNode);
	}
	
	return;
}


#ifdef _USE_XMPUEQP_

void CUmsRollCallMgr::XmpuMixCB( u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData )
{
	TXmpuStartMixNty  tStartInfo;
    TXmpuAddMixMemNty tAddMemInfo;
    //TXmpuVacActiveNty tVacActiveInfo;
    //TVoiceDetectionNty tVoiceDelInfo;
    //u32 wEqpId;
	
	BOOL32 bStopRollCall = FALSE;
	
    if (dwEvent == evXmpu_UmsStartMix_Nty)
	{
        memcpy(&tStartInfo, pData, sizeof(tStartInfo));
		if (!tStartInfo.m_bSuccess)
		{
            bStopRollCall = TRUE;
		}
	} else if (dwEvent == evUms_XmpuAddMixMember_Nty)
	{
		memcpy(&tAddMemInfo, pData, sizeof(TXmpuAddMixMemNty));
		if (!tAddMemInfo.m_bSuccess)
		{
			bStopRollCall = TRUE;
		}
	} else if (dwEvent == evXmpu_VacActive_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixVoiceDetection_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixDisConnect_Nty)
	{
		bStopRollCall = TRUE;
	}
	
	if (bStopRollCall)
	{
		MdlError(Ums_Mdl_Call, ("[CUmsRollCallMgr::XmpuMixCB] ConId:%d, CBType:%d(startfail:%d, addmemfail:%d, discon:%d ), StopRollCall\n",
			     Inst()->GetInsID(), dwEvent, evXmpu_UmsStartMix_Nty, evUms_XmpuAddMixMember_Nty, evXmpu_MixDisConnect_Nty));
	    StopRollCallModle();
        RollCallStatesNotify(em_RollCallMixer_Error);
	    Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_MIX_ERROR, Inst()->chairID());
	}
}

#else
void CUmsRollCallMgr::MixCB( TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo )
{// mixCB
	
	if (NULL == ptMixInfo)
	{
		return;
	}

	MdlError(Ums_Mdl_Call, ("[MixCB] ConId:%d, EqpId:%d, CBType:%d\n", 
		Inst()->GetInsID(), ptMixInfo->m_tEqpRes.m_byEqpID, emType));


	StopRollCallModle();

    RollCallStatesNotify(em_RollCallMixer_Error);

	Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_MIX_ERROR, Inst()->chairID());
	return;
}
#endif

void CUmsRollCallMgr::GetRollCallStateInfo(TConfRollCallInfo& tRollCallInfo, EmRollCallRspRet	emRspState)
{

	tRollCallInfo.m_emRet  = emRspState;
	tRollCallInfo.m_bStart = m_bUIRollcallStatus;
	tRollCallInfo.m_wConfID = Inst()->GetInsID();
	memcpy(&tRollCallInfo.m_atRollCallMemList, &m_tRollCallEpList, sizeof(TRollCallList));
	
	return;
}


void CUmsRollCallMgr::RollCallStatesNotify(EmRollCallRspRet	emRspState)
{
	CUmsConfInst* pcInst = Inst();
	
	if (!pcInst->IsChairConf())
	{
		return;
	}
	
	TConfRollCallInfo tRollCallInfo;

	GetRollCallStateInfo(tRollCallInfo, emRspState);


	// ֪ͨ��ϯ����״̬
	Inst()->NotifyConfCtrlMsgToCns(ev_UmsConfRollCallUpdate_Nty,  Inst()->chairID(), &tRollCallInfo, sizeof(tRollCallInfo));
	
	// ֪ͨumc����״̬
	Inst()->NotifyMsgToServiceForUI(evtp_RollCallState_Notify, &tRollCallInfo, sizeof(tRollCallInfo));
	return;

}



void CUmsRollCallMgr::GetAllRollCallPresentStateInfo(TRollCallPresentStateMsg&  tPresentState)
{
	tPresentState.m_wConfID   = m_pcConf->GetInsID();
	tPresentState.m_wValidNum = m_tRollCallEpList.m_wNum;
	
	for(u16 wIndex = 0; wIndex < tPresentState.m_wValidNum; wIndex++ )
	{
		tPresentState.m_atEpState[wIndex].m_wEpID    =  m_tRollCallEpList.m_awList[wIndex];
		tPresentState.m_atEpState[wIndex].m_wEpState =  m_aemPresentState[wIndex];
	}
	
	return;
}




void CUmsRollCallMgr::RollCallPresentStateNotify()
{
	CUmsConfInst* pcInst = Inst();
	
	if (!pcInst->IsChairConf())
	{
		return;
	}
	
    TRollCallPresentStateMsg tmpPresentState;
    TRollCallPresentStateMsg *pSendPresentState = NULL;
	
	//�����л᳡�����֪ͨ��ȥ
    GetAllRollCallPresentStateInfo(tmpPresentState);
    pSendPresentState = &tmpPresentState;

	// ֪ͨ��ϯ������״̬
	Inst()->NotifyConfCtrlMsgToCns(evtp_UmsRoll_PresentState_Notify,  Inst()->chairID(), pSendPresentState, sizeof(TRollCallPresentStateMsg));	
	
	// ֪ͨumc������״̬
	Inst()->NotifyMsgToServiceForUI(evtp_RollCall_PresentState_Notify, pSendPresentState, sizeof(TRollCallPresentStateMsg));
}



EmRollCallRspRet CUmsRollCallMgr::AssignResource()
{
#ifndef Test_No_Res
#define MAX_ROLLCALL_MIX_NUM   2

	if (NULL == m_tMixRes.m_ptMixRes)
	{
		m_tMixRes.m_ptMixRes = Inst()->GetEapu()->AssignMixer(RollCallMixCB, Inst(), MAX_ROLLCALL_MIX_NUM);
		if (NULL == m_tMixRes.m_ptMixRes)
		{
			return em_StartRollCall_AssignMixFail;
		}
	}

	if (!m_tRollCallInfo.m_tVirCallerAddr.AssignAddr(m_pcConf))
	{
		return em_StartRollCall_AssignAddrFail;
	}

#endif

	MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::AssignResource]  AssignResource  Success\n"));

	return em_RollCallOprRsp_Ok;;
}

void CUmsRollCallMgr::ReleaseResoure()
{
	if (NULL != m_tMixRes.m_ptMixRes)
	{
		Inst()->GetEapu()->ReleaseMixer(m_tMixRes.m_ptMixRes);
		if (0 != m_tMixRes.m_cToMixDsInfo.GetElementNum())
		{
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_tMixRes.m_cToMixDsInfo);
		}
		m_tMixRes.Clear();
	}

	if (0 != m_tRollCallInfo.m_cToVirCallerDsInfo.GetElementNum())
	{
		CNetPortMgr::FreeMediaTrans(m_pcConf, m_tRollCallInfo.m_cToVirCallerDsInfo);
		m_tRollCallInfo.m_cToVirCallerDsInfo.Clear();
	}
	m_tRollCallInfo.m_tVirCallerAddr.Release();

	return;
}


void CUmsRollCallMgr::GetBackupSpeaker()
{
    m_wBackSpeaker = m_pcConf->curSpeakerID();
}


void CUmsRollCallMgr::ModRestore()
{
    u16 wBackSpeaker = 0;
    TCallNode *pBackSpeakerNode = NULL;;

    wBackSpeaker     = m_wBackSpeaker;
	pBackSpeakerNode = m_pcConf->GetNodeMgr()->GetNode(wBackSpeaker);
	if (NULL != pBackSpeakerNode &&  pBackSpeakerNode->IsChanOn())
	{
		m_pcConf->ChangeSpeaker(m_wBackSpeaker, NULL);
        m_pcConf->AdjustNewSpeakerToAllNode();
		return;
	}


    //����ķ����˲����߳����л�������Ϊ��ϯ
    wBackSpeaker     = m_pcConf->chairID();
	pBackSpeakerNode = m_pcConf->GetNodeMgr()->GetNode(wBackSpeaker);
	if (NULL != pBackSpeakerNode &&  pBackSpeakerNode->IsChanOn())
	{
		m_pcConf->ChangeSpeaker(m_wBackSpeaker, NULL);
        m_pcConf->AdjustNewSpeakerToAllNode();
		return;
	}


    return;
}


// �����ˣ��������ˣ�
BOOL32 CUmsRollCallMgr::AskKeyFrameToChair(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys)
{
	
	TCallNode* pRollCallerNode = NULL;
    u16 wDstChanIndex = MIDSCREENINDEX;
    u16 wRollCaller = GetRollCallerEpId();

	if (m_pcConf->IsChairConf())
	{//�ϼ�
		pRollCallerNode = m_pcConf->GetNodeMgr()->GetNode(wRollCaller); 
		if (NULL == pRollCallerNode)
		{
			MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::AskKeyFrameToChair]  AskKeyFrame Failed! ConfID:%d, RollCaller:%d, SrcID:%d\n", 
				   m_pcConf->GetInsID(), wRollCaller, ptNode->m_wEpID));

			return FALSE;
		}

		wDstChanIndex = ptNode->m_wVidRcvNum > 1 ? wDecIndex : pRollCallerNode->GetSpeaker();

		if ( m_pcConf->GetVmp()->IsChairInVmp() && ptNode->IsSingleVidRcv() )
		{//��Vmp ����
			m_pcConf->GetVmp()->AskFrameToSpeakerVmp(ptNode->m_tVidRcvFormat.m_tFormat);
		}	
		else if ( m_pcConf->GetBas()->IsChairInBas() && pRollCallerNode->IsVidSndValid() )
		{//��ϯ�������� ������ϯ����ͨ������
			m_pcConf->GetBas()->SeeChairAskFrameToBas(wDstChanIndex);
		}
		else
		{//��Ŀ���ն�����
            m_pcConf->AskKeyByScreen(wRollCaller, wDstChanIndex, EmAskKeyChair, 0, 0, bReqBySys);
		} 
	}
	else
	{//�¼�

		wDstChanIndex = ptNode->m_wVidRcvNum > 1 ? wDecIndex : (m_tNoty.m_NodeInfo[em_RollCallerEp].GetSpeaker());

        if (m_pcConf->GetVmp()->IsChairInVmp() && ptNode->IsSingleVidRcv())
		{
			m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeySpeakerVmp);
		}
		else if ( m_pcConf->GetBas()->IsChairInBas() && m_tNoty.m_NodeInfo[em_RollCallerEp].IsVidSndValid() )
		{//��ϯ�������� ������ϯ����ͨ������
			m_pcConf->GetBas()->SeeChairAskFrameToBas(wDstChanIndex);
		} else 
		{
             if (NULL != m_pcConf->GetNodeMgr()->GetCapsetNode(wRollCaller))
			 { // ������Ҳ�ڴ��¼�,ֱ������¼��᳡����
                 m_pcConf->AskKeyByScreen(wRollCaller, wDstChanIndex, EmAskKeySpeaker, 0, 0, bReqBySys);
			 } 
			 else
			 { //���ϼ��᳡����

                 TCapNode* ptUms = m_pcConf->GetNodeMgr()->GetCaller();
				 if (NULL == ptUms)
				 {
					 MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::AskKeyFrameToChair]  AskKeyFrame to top Failed! ConfID:%d, RollCaller:%d, SrcID:%d\n", 
						     m_pcConf->GetInsID(), wRollCaller, ptNode->m_wEpID));
					 return FALSE;
				 }

				 m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, wDstChanIndex, EmAskKeyChair, 0, 0, bReqBySys);
			 }
		}

	}

	return TRUE;
}



void CUmsRollCallMgr::OnChanConnect(TCallNode* ptNode)
{
	if (NULL == ptNode)
	{
        return;
	}

	if (!m_pcConf->IsChairConf())
	{
        return;
	}

	if (!m_bRollcallStaus)
	{ 
        return;
	}

    
    // �����ߣ�������ߵ�farther ����Ӧ��������Ϊ�����ʱ��Ӧ��ֹ����ģʽ
	u16 wRollCaller = GetRollCallerEpId();
	//TCallNode *pRollCallerNode = m_pcConf->GetNodeMgr()->GetNode(wRollCaller);
	//TCapNode  *pRollCallerFar  = m_pcConf->GetNodeMgr()->GetForeFatherNode(pRollCallerNode);
    //if (ptNode == pRollCallerNode || ptNode == pRollCallerFar)
	//{
    //    return;
	//}

	u16 wCallTarget = GetCallTargetEpId();
	TCallNode *pCallTargetNode = m_pcConf->GetNodeMgr()->GetNode(wCallTarget);
	TCapNode  *pCallTargetFar  = m_pcConf->GetNodeMgr()->GetForeFatherNode(pCallTargetNode);

	TRollCallNextEpInfo tCallNextEpInfo;


	if (ptNode == pCallTargetNode || ptNode == pCallTargetFar)
	{  // ������������

		if( pCallTargetFar->IsCallOn() && pCallTargetNode->IsCallOn())
		{
			tCallNextEpInfo.m_wRollCaller = wRollCaller;
			tCallNextEpInfo.m_wCallTarget = wCallTarget;
            tCallNextEpInfo.m_emRet       = em_RollCallOprRsp_Ok;

			if (TRUE == RollCallNextEpFromUmcCnc(tCallNextEpInfo))
			{
				AdjustRollCallStatus();	
				//RollCallStatesNotify(em_CallTarget_ReConnect_Success);

			} else 
			{	
				if (tCallNextEpInfo.m_emRet == em_RollCallNextEp_CreateChanFail)
				{
					
					StopRollCallModle();
					RollCallStatesNotify(tCallNextEpInfo.m_emRet);
					//m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_ROLLCALLER_OFFLINE, m_pcConf->chairID());
					
				    return;
				}

			}
		}

	}


	if (ptNode->m_wEpID == m_pcConf->chairID())
	{ // ��ϯ���ߣ�ͬ��һ��״̬
        RollCallStatesNotify(em_Chair_ReConnect_notice);

        RollCallPresentStateNotify();
	}


    return;
}


void CUmsRollCallMgr::OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason)
{
	if (NULL == ptNode)
	{
        return;
	}

	MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] Confid:%d  ep:%d HungUpNode.\n", m_pcConf->GetInsID(), ptNode->m_wEpID));

	if (m_pcConf->m_bIsQuiting)
	{
		MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] Now Is Quiting Conf! ConfId:%d, epId:%d\n", m_pcConf->GetInsID(), ptNode->m_wEpID));
		return;
	}

	if (m_pcConf->IsChairConf())
	{
         if (!IsUIRollCallOn())
		 {
			 MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] confid:%d epid:%d topconf notrollcallmode (uimode:%d  mode:%d)\n", 
				 m_pcConf->GetInsID(), ptNode->m_wEpID, IsUIRollCallOn(), IsRollCallModle()));
		     return;
		 }
	}
	else 
	{
		if (!IsRollCallModle())
		{
			MdlHint(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] confid:%d epid:%d  lowconf notrollcallmode (uimode:%d  mode:%d)\n", 
				m_pcConf->GetInsID(), ptNode->m_wEpID, IsUIRollCallOn(), IsRollCallModle()));
			return;
		}

        m_tRollCallInfo.DelEp(ptNode->m_wEpID);
        return;
	}


    u16 wRollCaller = GetRollCallerEpId();
	TCallNode *pRollCallerNode = m_pcConf->GetNodeMgr()->GetNode(wRollCaller);
	TCapNode  *pRollCallerFar  = m_pcConf->GetNodeMgr()->GetForeFatherNode(pRollCallerNode);
	if (ptNode == pRollCallerNode || ptNode == pRollCallerFar)
	{//������ �� �����ߵ�farther ����, �˳�����

		MdlError(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] Caller Off line ,stop rollcallmod ConfId:%d, epId:%d\n", m_pcConf->GetInsID(), ptNode->m_wEpID));
		StopRollCallModle();
		RollCallStatesNotify(em_RollCaller_OffLine);
		m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_ROLLCALLER_OFFLINE, m_pcConf->chairID());
		return;
	}


	u16 wCallTarget = GetCallTargetEpId();
	TCallNode *pCallTargetNode = m_pcConf->GetNodeMgr()->GetNode(wCallTarget);
	TCapNode  *pCallTargetFar  = m_pcConf->GetNodeMgr()->GetForeFatherNode(pCallTargetNode);
	if (ptNode == pCallTargetNode || ptNode == pCallTargetFar)
	{   //�����һ֡
		MdlError(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] Calltaget Off line ConfId:%d, epId:%d\n", m_pcConf->GetInsID(), ptNode->m_wEpID));
        ReleaseRollCallEpChan(wCallTarget);
        
		//m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALLTARGET_OFFLINE, m_pcConf->chairID());
        //RollCallStatesNotify(em_RollCallTarget_OffLine);
	}


    u16 windex = 0;
	TCallNode *pNodeTemp = NULL;
    TCapNode *pFarNodeTemp = NULL;
	BOOL32 bHaveTargetOnLine  =  FALSE;
	if (ptNode->IsUms())
	{  //��ǰ���ߵ���UMS
       for (windex = 0; windex < m_tRollCallEpList.m_wNum; windex++)
	   {
		   pNodeTemp    = m_pcConf->GetNodeMgr()->GetNode(m_tRollCallEpList.m_awList[windex]);
           pFarNodeTemp = m_pcConf->GetNodeMgr()->GetForeFatherNode(pNodeTemp);
           if (NULL != pNodeTemp && NULL != pFarNodeTemp && ptNode != pFarNodeTemp && pNodeTemp->IsChanOn())
		   {  // �С����������᳡���ߣ����Ҳ��ڸ�UMS��
               bHaveTargetOnLine = TRUE;
			   break;   
		   }
	   }

	   if (!bHaveTargetOnLine)
	   {
		   //�������ߵĻ᳡���ڸ�UMS��
		   MdlError(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] UMS off line, all rollcallTarge Off line  ,stop rollcallmod ConfId:%d, lastepId:%d\n",
			       m_pcConf->GetInsID(), ptNode->m_wEpID));
		   StopRollCallModle();
		   RollCallStatesNotify(em_RollCallTarget_OffLine);
		   m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_ALLTARGET_OFFLINE, m_pcConf->chairID());
	   }

	}
	else 
	{
		u16  wOnLineRollCallTarget = 0;
	    u16  wLastOnLineIndex = TP_INVALID_INDEX;

		for (windex = 0; windex < m_tRollCallEpList.m_wNum; windex++)
		{
			pNodeTemp    = m_pcConf->GetNodeMgr()->GetNode(m_tRollCallEpList.m_awList[windex]);
			if (NULL != pNodeTemp && pNodeTemp->IsCallOn() && pNodeTemp->IsChanOn())
			{    //�����ߵı������᳡��
                 wOnLineRollCallTarget++;
			     wLastOnLineIndex = windex;
			}
		}

		if (wOnLineRollCallTarget == 1 && 
			ptNode->m_wEpID == m_tRollCallEpList.m_awList[wLastOnLineIndex])
		{
			//�������һ�����ߵġ��������᳡�� ��������᳡Ҳ��Ҫ������
			MdlError(Ums_Mdl_Call, ("[CUmsRollCallMgr::OnHungUpNode] all rollcallTarge Off line ,stop rollcallmod ConfId:%d, lastepId:%d\n", m_pcConf->GetInsID(), ptNode->m_wEpID));
			StopRollCallModle();
			RollCallStatesNotify(em_RollCallTarget_OffLine);
			m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, Tp_ROLLCALL_ALLTARGET_OFFLINE, m_pcConf->chairID());
		}


	}

}
