#include "selviewmgr.h"
#include "callnodemgr.h"
#include "umsstackinterface.h"
#include "eventoutumsselview.h"
#include "nodefsm.h"
#include "umsbas.h"
#include "tperrno.h"
#include "umsdiscussnew.h"

void SelViewBrdVmpCB(void* param1, void* param2, void* param3)
{
	CSelView* ptSelView = (CSelView*)param1;
	TBrdVmpRes* ptRes = (TBrdVmpRes*)param2;
	
	ptSelView->BrdVmpCB(ptRes, *(EmBrdVmpCBOprType *)param3);
}

BOOL32 CSelView::Handler( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case ev_UMC_UMS_SelView_Req:
		OnSelViewUmc(ptMsg);
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL32 CSelView::HandlerFromStack( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case ev_CNC_UMS_SelView_Req:
		OnSelViewCnc(ptMsg);
		break;
	case ev_UMS_CNC_SelView_Ind:
		OnSelViewCasecadeInd(ptMsg);
		break;
	case ev_UMS_CNC_SelView_Ntfy:
		OnSelViewNtfy(ptMsg);
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CSelView::Show()
{
	msgprintnotime("Conf view info:\n");
	TEpViewInfo* ptViewInfo = NULL;
	TSelViewMgr* ptViewMgr = NULL; 
	for ( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		ptViewInfo = &m_atSelView[wIndex];
		if ( !ptViewInfo->Valid() )
		{
			continue;
		}

		msgprintnotime(" EpID:%d\n", ptViewInfo->m_wEpID);
		for (u16 wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; ++wScreenIndex)
		{
			if (!ptViewInfo->m_atViewMgr[wScreenIndex].IsValid())
			{
				continue;
			}

			ptViewMgr = &(ptViewInfo->m_atViewMgr[wScreenIndex]);
			msgprintnotime("  ScreenIndx:%d, DstType:%d ( MT:1, VMP:2 ), DstID:%d, DstScrIndx:%d, bSelEp:%d, GetVidIndx:%d\n", 
				ptViewMgr->m_tSelView.m_wScreenIndx, ptViewMgr->m_tSelView.m_emType, 
				ptViewMgr->m_tSelView.m_wDstID, ptViewMgr->m_tSelView.m_wDstScrIndx, ptViewMgr->m_bEpSel, ptViewMgr->m_wGetIndex);
		}
		msgprintnotime("\n");
	}

	return ;
}

void CSelView::OnSelViewUmc( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	TTPSelViewReq tSelview;
	TP_SAFE_CAST(tSelview, ptMsg->GetBody() + sizeof(TLogUser));
	
	EmViewRetReason emRet = EmViewRetReason_Success;
	if( tSelview.m_bSel )
	{
		TEpViewInfo tInfo;
		emRet = SelView(tSelview, &tInfo);

		if ( TP_VALID_HANDLE(tInfo.m_wEpID) )
		{//防止：替换选看操作，老的被删除，而且新又失败时，老的删除状态没通知到界面
			NtfySelInfoToUI(&tInfo);
			TCapNode* ptSelEp = Inst()->GetNodeMgr()->GetCapsetNode(tInfo.m_wEpID);
			if( ptSelEp != NULL )
			{
				Inst()->GetNodeFsm()->UnView((TCapNode*)ptSelEp, tSelview.m_wScreenIndx);
			}
		}
	}
	else
	{
		if( TP_VALID_HANDLE(tSelview.m_wEpID) )
		{
			emRet = UnSelView(tSelview);
		}
		else
		{
			emRet = EmViewRetReason_Success;
			OnUnSelAllView(ptMsg);  
		}
	}

	if ( emRet != EmViewRetReason_Success )
	{//失败则回应
		TTPSelViewInd tRet;
		tRet.SetView(tSelview);
		tRet.m_emRet = emRet;
		//Ind UMC
		Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SelView_Ind, &tRet, sizeof(tRet), &tUsr);
	}

	MdlHint(Ums_Mdl_Call, ("CSelView::OnSelViewUmc. confID:%d, Sel:%d, EpID:%d, ScreenIndx:%d, DstType:%d, DstID:%d, DstScreen:%d, Ret:%d\n"
				, tSelview.m_wConfID, tSelview.m_bSel, tSelview.m_wEpID, tSelview.m_wScreenIndx, tSelview.m_emType, tSelview.m_wDstID, tSelview.m_wDstScrIndx, emRet));

	return ;
}

void CSelView::OnSelViewCnc( CTpMsg *const ptMsg )
{
	TUmsHandle thanlde;
	TP_SAFE_CAST(thanlde, ptMsg->GetBody());
	TTPSelViewReq tSelview;
	TP_SAFE_CAST(tSelview, ptMsg->GetBody() + sizeof(TUmsHandle));
	
	tSelview.m_wConfID = thanlde.GetConfID();

	EmViewRetReason emRet = EmViewRetReason_Success;
	if( tSelview.m_bSel )
	{
		TEpViewInfo tInfo;
		emRet = SelView(tSelview, &tInfo);

		if ( TP_VALID_HANDLE(tInfo.m_wEpID) )
		{//防止：替换选看操作，老的被删除，而且新又失败时，老的删除状态没通知到界面
			NtfySelInfoToUI(&tInfo);
			TCapNode* ptSelEp = Inst()->GetNodeMgr()->GetCapsetNode(tInfo.m_wEpID);
			if( ptSelEp != NULL )
			{
				Inst()->GetNodeFsm()->UnView((TCapNode*)ptSelEp, tSelview.m_wScreenIndx);
			}
		}
	}
	else
	{
		emRet = UnSelView(tSelview);
	}

	if ( emRet != EmViewRetReason_Success )
	{
		TTPSelViewInd tRet;
		tRet.SetView(tSelview);
		tRet.m_emRet = emRet;
		
		//Ind CNC
		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, thanlde.GetEpID());
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SelView_Ind, &tRet, sizeof(tRet));
	}
	
	MdlHint(Ums_Mdl_Call, ("CSelView::OnSelViewCnc. confID:%d, Sel:%d, EpID:%d, ScreenIndx:%d, DstType:%d, DstID:%d, Ret:%d\n"
		, Inst()->GetInsID(), tSelview.m_bSel, tSelview.m_wEpID, tSelview.m_wScreenIndx, tSelview.m_emType, tSelview.m_wDstID, emRet));

	return ;
}

EmViewRetReason CSelView::SelView( TTPSelViewReq& tView, TEpViewInfo* ptOutInfo)
{
	EmViewRetReason emRet = EmViewRetReason_Success;
	
	MdlHint(Ums_Mdl_Call, ("CSelView::SelView. confID:%d, Sel:%d, src:%d_%d,  DstType:%d, Dst:%d_%d.\n"
		   , Inst()->GetInsID(), tView.m_bSel, tView.m_wEpID, tView.m_wScreenIndx, tView.m_emType, tView.m_wDstID, tView.m_wDstScrIndx));

	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(tView.m_wEpID);
	TCapNode* ptNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(tView.m_wEpID);
	if ( NULL == ptNode || !ptNode->IsChanOn() || NULL == ptNodeFather )
	{
		return EmViewRetReason_EpNotLine;
	}

	if ( !ptNode->IsVidRcvValid() )
	{
		return EmViewRetReason_SelNoVid;
	}
	
	if ( ptNode->IsUms())
	{
		return EmViewRetReason_InValidEp;
	}

	if ( ptNode != ptNodeFather )
	{//下级会场
		if( tView.m_emType == EmEpType_Ter )
		{
			TCallNode* ptDstNode = Inst()->GetNodeMgr()->GetNode(tView.m_wDstID);
			TCapNode* ptDstNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(tView.m_wDstID);
			if ( NULL == ptDstNode || !ptDstNode->IsChanOn() || NULL == ptDstNodeFather )
			{
				return EmViewRetReason_DstEpNotLine;
			}

			if (ptDstNodeFather->IsMcu() && ptDstNode!=ptDstNodeFather)
			{
                 //选看者不可以为mcu下级会场
				 return EmViewRetReason_InValidEp;
			}

			if ( !ptDstNode->IsVidSndValid() )
			{
				return EmViewRetReason_SelDstNoVid;
			}
			
			if ( ptNodeFather != ptDstNodeFather )
			{//选看会场和目标会场不在同一级 拒绝
				return EmViewRetReason_SelDstNotLvl;
			}
			
			TTPSelViewReq tSelReq;
			memcpy(&tSelReq, &tView, sizeof(TTPSelViewReq));
			
			tSelReq.m_wDstID = ptDstNode->m_wLowChildEpID;
			tSelReq.m_wEpID = ptNode->m_wLowChildEpID;
			
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
			UmsSendConfCtrl(tOutHandle, ev_CNC_UMS_SelView_Req, &tSelReq, sizeof(tSelReq));
		}
		else if( tView.m_emType == EmEpType_Eqp )
		{//下级不能选看合成
			emRet = EmViewRetReason_SelDstNotLvl;
		}
		else
		{
			emRet = EmViewRetReason_EpTypeError;
		}
	}//if ( ptNode != ptNodeFather )
	else
	{//本级会场
        
		u16 wProScreen = TP_INVALID_INDEX;

		TEpViewInfo* ptInfo = FindByEP(tView.m_wEpID);
		if (NULL != ptInfo
			&& (TP_MAX_STREAMNUM == tView.m_wScreenIndx || (TP_MAX_STREAMNUM != tView.m_wScreenIndx &&ptInfo->m_atViewMgr[tView.m_wScreenIndx].IsValid()))
			)
		{//选看状态已经存在，则先删除老的。只在本级处理，防止状态和界面闪中间态。
			TTPSelViewReq tUnSel;
			tUnSel.m_bSel = FALSE;
			tUnSel.m_emType = tView.m_emType;
			tUnSel.m_emUIType = tView.m_emUIType;
			tUnSel.m_wConfID = tView.m_wConfID;
			tUnSel.m_wEpID = tView.m_wEpID;
			tUnSel.m_wScreenIndx = tView.m_wScreenIndx;
			
			//保存老的
			ptOutInfo->m_wEpID = ptInfo->m_wEpID;
			
			UnSelView(tUnSel, FALSE);
			
			memcpy(ptOutInfo->m_atViewMgr, ptInfo->m_atViewMgr, sizeof(TSelViewMgr)*TP_MAX_STREAMNUM);
		}

		if (NULL == ptInfo)
		{
			ptInfo = FindIdle();
		}

		if ( NULL == ptInfo )
		{
			return EmViewRetReason_SelFull;
		}

		if ( ptNode->IsSingleVidRcv() )
		{//选看会场是单屏 按照屏选看处理
			tView.m_wScreenIndx = MIDSCREENINDEX;
		}
		
		if( tView.m_emType == EmEpType_Ter )
		{
			TCallNode* ptDstNode = Inst()->GetNodeMgr()->GetNode(tView.m_wDstID);
			TCapNode* ptDstNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(tView.m_wDstID);
			if ( NULL == ptDstNode || !ptDstNode->IsVidSndValid() || NULL == ptDstNodeFather )
			{
				return EmViewRetReason_DstEpNotLine;
			}

			if (ptDstNode->IsUms() || 
				(ptDstNodeFather->IsMcu() && ptDstNode!=ptDstNodeFather))
			{  //被选看者不可以为mcu下级会场
                return EmViewRetReason_InValidEp;
			}

			if (ptDstNode->IsSingleVidSnd())
			{
				tView.m_wDstScrIndx = MIDSCREENINDEX;
			}

			ptDstNodeFather->m_tRmtChan.ResetFastStatis();

			EmGetVidType emVidType;
			if (TP_MAX_STREAMNUM == tView.m_wScreenIndx)
			{//会场选看 全部调度
				emVidType = em_GetVid_ViewEp;
			}
			else
			{//屏选看 调度合成或者坐席
				if (IsInSndRange(tView.m_wDstScrIndx, ptDstNode->m_wVidSndNum))
				{// 固定调用一个屏
					emVidType  = em_GetVid_ViewEp;
					wProScreen = tView.m_wDstScrIndx;

				}
				else
				{
					emVidType  = em_GetVid_View;
				    wProScreen = ptDstNode->GetSpeaker();
					tView.m_wDstScrIndx = TP_MAX_STREAMNUM;
				}  
			}

			ptInfo->m_wEpID = tView.m_wEpID;

			EmGetVidRes emRes = em_GetVid_Success;
			if ( tView.m_wScreenIndx == TP_MAX_STREAMNUM )
			{//会场选看
				BOOL32 bError = FALSE;
				ForEachChanList(ptNode->m_wVidRcvNum,
					if ( IsInSndRange(ewIndex, ptDstNode->m_wVidSndNum) )\
					{\
						emRes = CUmsConfInst::GetVidAudEx()->AssignByScreen(Inst(), ptDstNode->m_wEpID, ewIndex, emVidType, 
							ptNodeFather->m_tVidRcvFormat, TRUE, ptInfo->m_atViewMgr[ewIndex].m_tGetAddr, 
							ptInfo->m_atViewMgr[ewIndex].m_wGetIndex);\
							if ( em_GetVid_Success != emRes )\
							{\
							bError = TRUE;\
							break;\
							}\
						CUmsConfInst::GetVidAudEx()->AskKeyFrame(ptInfo->m_atViewMgr[ewIndex].m_wGetIndex, TRUE);
					}\
					ptInfo->m_atViewMgr[ewIndex].SetView(tView);\
					ptInfo->m_atViewMgr[ewIndex].m_tSelView.m_wScreenIndx = ewIndex;\
					ptInfo->m_atViewMgr[ewIndex].m_tSelView.m_wDstScrIndx = ptDstNode->IsSingleVidSnd()?MIDSCREENINDEX:ewIndex;\
					ptInfo->m_atViewMgr[ewIndex].m_bEpSel = TRUE;\
					);


				if ( bError )
				{
					ForEachChanList(ptNode->m_wVidRcvNum,
									if ( ptInfo->m_atViewMgr[ewIndex].m_wGetIndex < TP_UMS_MAX_CALLNUM )\
									{\
										CUmsConfInst::GetVidAudEx()->Release(Inst(), ptInfo->m_atViewMgr[ewIndex].m_wGetIndex, emVidType);\
									}\
									);

					ptInfo->Clear();

					return ConvertGetVidReason(emRes);
				}
				ptDstNode->IncreaseSelNum(TP_MAX_STREAMNUM);
			}
			else
			{//屏选看
				emRes = CUmsConfInst::GetVidAudEx()->AssignByScreen(Inst(), ptDstNode->m_wEpID, wProScreen, emVidType, 
													ptNodeFather->m_tVidRcvFormat, TRUE, 
													ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_tGetAddr, 
													ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_wGetIndex);

				if ( em_GetVid_Success != emRes )
				{
					ptInfo->m_atViewMgr[tView.m_wScreenIndx].Clear();
					return 	ConvertGetVidReason(emRes);
				}

				ptDstNode->IncreaseSelNum(1);

				ptInfo->m_atViewMgr[tView.m_wScreenIndx].SetView(tView);
				ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_tSelView.m_wDstScrIndx =  tView.m_wDstScrIndx;;
				ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_bEpSel = emVidType == em_GetVid_ViewEp?TRUE:FALSE;

				CUmsConfInst::GetVidAudEx()->AskKeyFrame(ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_wGetIndex, TRUE);

				Inst()->AskKeyByEpID(ptDstNode->m_wEpID, EmAskKeyGetVid, ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_wGetIndex, TRUE, TRUE);

				if (ptDstNode == ptDstNodeFather && ptDstNode->IsThreeVidSnd() && CUmsConfInst::GetVidAudEx()->IsNeedNotifyNoVmp(ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_wGetIndex) )
				{
					//提示界面
					Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_View_NoVmp, ptInfo->m_wEpID, ptInfo->m_wEpID);
				}
			}
		}//if( tView.m_emType == EmEpType_Ter )
		else if ( tView.m_emType == EmEpType_Eqp )
		{
			//取得合成器
			TBrdVmpRes* ptVmpRes = Inst()->GetVmp()->SelViewVmp(tView.m_wDstID, SelViewBrdVmpCB, this);
			if ( NULL == ptVmpRes )
			{
				return EmViewRetReason_DstEqpNoExists;
			}

			ptInfo->m_wEpID = tView.m_wEpID;

			if ( tView.m_wScreenIndx == TP_MAX_STREAMNUM )
			{//会场选看
				ForEachChanList(ptNode->m_wVidRcvNum,
					if ( ewIndex == MIDSCREENINDEX )\
					{\
						ptInfo->m_atViewMgr[ewIndex].m_ptItor = ptVmpRes;\
					}\
					ptInfo->m_atViewMgr[ewIndex].SetView(tView);\
					ptInfo->m_atViewMgr[ewIndex].m_tSelView.m_wScreenIndx = ewIndex;\
					ptInfo->m_atViewMgr[ewIndex].m_bEpSel = TRUE;
					);
			}
			else
			{//屏选看
				ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_ptItor = ptVmpRes;
				ptInfo->m_atViewMgr[tView.m_wScreenIndx].SetView(tView);
			}

			Inst()->GetVmp()->AskFrameToBrdVmp(ptVmpRes, ptNode->m_tVidRcvFormat.m_tFormat);
		}//if( tView.m_emType == EmEpType_Ter )
		else
		{
			return EmViewRetReason_EpTypeError;
		}

		if ( emRet == EmViewRetReason_Success )
		{
            if (Inst()->IsChairConf() && tView.m_emType == EmEpType_Ter)
			{    // 选看尝试恢复分辨率
				MdlHint(Ums_Mdl_Call, ("CSelView::RestoreAdjustedResForSelEp para. confID:%d, restoreep:%d, restorescr:%d.\n"
					 , Inst()->GetInsID(), tView.m_wDstID, tView.m_wDstScrIndx));

                 RestoreAdjustedResForSelEp(tView.m_wDstID, tView.m_wDstScrIndx);
				

			}

			//切目标
			Inst()->GetNodeFsm()->SelView((TCapNode*)ptNodeFather, tView.m_wScreenIndx);
		}

		//外面不必提示
		ptOutInfo->Clear();

		NtfySelInfoToUI(ptInfo);
	}//if ( ptNode != ptNodeFather )

	return emRet;
}

EmViewRetReason CSelView::UnSelView(TTPSelViewReq& tView, BOOL32 bNtfy)
{
	EmViewRetReason emRet = EmViewRetReason_Success;
	
	MdlHint(Ums_Mdl_Call, ("CSelView::UnSelView. confID:%d, Sel:%d, src:%d_%d,  DstType:%d, Dst:%d_%d.\n"
		, Inst()->GetInsID(), tView.m_bSel, tView.m_wEpID, tView.m_wScreenIndx, tView.m_emType, tView.m_wDstID, tView.m_wDstScrIndx));

	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(tView.m_wEpID);
	TCallNode* ptNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(tView.m_wEpID);
	if ( NULL == ptNode || !ptNode->IsChanOn() || NULL == ptNodeFather )
	{
		return EmViewRetReason_EpNotLine;
	}
	
	TEpViewInfo* ptInfo = FindByEP(tView.m_wEpID);
	if ( NULL == ptInfo || (TP_MAX_STREAMNUM != tView.m_wScreenIndx && !ptInfo->m_atViewMgr[tView.m_wScreenIndx].IsValid()))
	{
		return EmViewRetReason_UnSelected;
	}

	TCallNode* ptDstNode = NULL;
	
	tView.m_bSel = FALSE;

	u16 awRestoreResSrcIndx[TP_MAX_STREAMNUM] = {TP_INVALID_INDEX, TP_INVALID_INDEX, TP_INVALID_INDEX};
	u16 awRestoreResEpId[TP_MAX_STREAMNUM] = {TP_INVALID_INDEX, TP_INVALID_INDEX, TP_INVALID_INDEX};

	if ( ptNode != ptNodeFather )
	{//下级会场
// 		if( tView.m_emType == EmEpType_Ter )
// 		{//取消
// 			TTPSelViewReq tSelReq;
// 			memcpy(&tSelReq, &tView, sizeof(TTPSelViewReq));
// 			
// 			tSelReq.m_wEpID = ptNode->m_wLowChildEpID;
// 			
// 			TUmsHandle tOutHandle;
// 			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
// 			UmsSendConfCtrl(tOutHandle, ev_CNC_UMS_SelView_Req, &tSelReq, sizeof(tSelReq));
// 		}
// 		else if( tView.m_emType == EmEpType_Eqp )
// 		{//下级不能选看合成
// 			emRet = EmViewRetReason_SelDstNotLvl;
// 		}
// 		else
// 		{
// 			emRet = EmViewRetReason_EpTypeError;
// 		}

		//不做判断 直接取消
		TTPSelViewReq tSelReq;
		memcpy(&tSelReq, &tView, sizeof(TTPSelViewReq));
		
		tSelReq.m_wEpID = ptNode->m_wLowChildEpID;
		
		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
		UmsSendConfCtrl(tOutHandle, ev_CNC_UMS_SelView_Req, &tSelReq, sizeof(tSelReq));
	}
	else
	{//本级会场
		EmGetVidType emVidType;

		if (tView.m_wScreenIndx != TP_MAX_STREAMNUM)
		{//取消屏
			if( tView.m_emType == EmEpType_Ter )
			{
				TSelViewMgr* ptMgr = &(ptInfo->m_atViewMgr[tView.m_wScreenIndx]);
				if (ptMgr->m_bEpSel)
				{//会场选看 全部调度
					emVidType = em_GetVid_ViewEp;
				}
				else
				{//屏选看 调度合成或者坐席
					emVidType = em_GetVid_View;
				}
				if ( ptMgr->m_wGetIndex < TP_UMS_MAX_CALLNUM )
				{
					// 选看结束，调整分辨率
					if (Inst()->IsChairConf())
					{
						awRestoreResEpId[tView.m_wScreenIndx]    = CUmsConfInst::GetVidAudEx()->GetDstEpByIndex(ptMgr->m_wGetIndex);
                        awRestoreResSrcIndx[tView.m_wScreenIndx] = CUmsConfInst::GetVidAudEx()->GetScreenIndex(ptMgr->m_wGetIndex);
					}

					CUmsConfInst::GetVidAudEx()->Release(Inst(), ptMgr->m_wGetIndex, emVidType);
					ptDstNode = Inst()->GetNode(ptMgr->m_tSelView.m_wDstID);
					if (NULL != ptDstNode)
					{
						ptDstNode->DiscreaseSelNum(1);
					}
				}
				ptMgr->Clear();
			}
			else
			{
				ptInfo->m_atViewMgr[tView.m_wScreenIndx].m_ptItor = NULL;
				ptInfo->m_atViewMgr[tView.m_wScreenIndx].Clear();
			}
		}
		else
		{//取消全部
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				if ( !ptInfo->m_atViewMgr[wIndex].IsValid() )
				{
					continue;
				}
				if ( ptInfo->m_atViewMgr[wIndex].m_tSelView.m_emType == EmEpType_Eqp )
				{
					ptInfo->m_atViewMgr[wIndex].m_ptItor = NULL;
				}
				else
				{
					if (ptInfo->m_atViewMgr[wIndex].m_bEpSel)
					{//会场选看 全部调度
						emVidType = em_GetVid_ViewEp;
					}
					else
					{//屏选看 调度合成或者坐席
						emVidType = em_GetVid_View;
					}
					if ( ptInfo->m_atViewMgr[wIndex].m_wGetIndex < TP_UMS_MAX_CALLNUM )
					{
						// 选看结束，调整分辨率
						if (Inst()->IsChairConf())
						{
							awRestoreResEpId[wIndex]    = CUmsConfInst::GetVidAudEx()->GetDstEpByIndex(ptInfo->m_atViewMgr[wIndex].m_wGetIndex);
						    awRestoreResSrcIndx[wIndex] = CUmsConfInst::GetVidAudEx()->GetScreenIndex(ptInfo->m_atViewMgr[wIndex].m_wGetIndex);
						}

						CUmsConfInst::GetVidAudEx()->Release(Inst(), ptInfo->m_atViewMgr[wIndex].m_wGetIndex, emVidType);
						ptDstNode = Inst()->GetNode(ptInfo->m_atViewMgr[wIndex].m_tSelView.m_wDstID);
						if (NULL != ptDstNode)
						{
							ptDstNode->DiscreaseSelNum(1);
						}
					}
				}
				
				ptInfo->m_atViewMgr[wIndex].Clear();
			}
		}

		if ( bNtfy )
		{
			NtfySelInfoToUI(ptInfo);

			if ( emRet == EmViewRetReason_Success )
			{//切目标
				Inst()->GetNodeFsm()->UnView((TCapNode*)ptNodeFather, tView.m_wScreenIndx);
			}
		}


        // 选看结束，调整分辨率
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
            if (awRestoreResEpId[wIndex] != TP_INVALID_INDEX && awRestoreResSrcIndx[wIndex] != TP_INVALID_INDEX)
			{
                 AdjustResForUnSelEp(awRestoreResEpId[wIndex], awRestoreResSrcIndx[wIndex]);
			}
		}


		if ( !ptInfo->IsHavView() )
		{
			ptInfo->Clear();
		}
	}

	return emRet;
}

TEpViewInfo* CSelView::FindIdle()
{
	for(u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++)
	{
		if ( m_atSelView[wIndex].Valid() )
		{
			continue;
		}

		return &m_atSelView[wIndex];
	}
	return NULL;
}

TEpViewInfo* CSelView::FindByEP( u16 wEpID)
{
	for( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		if ( m_atSelView[wIndex].m_wEpID == wEpID)
		{
			return &(m_atSelView[wIndex]);
		}
	}
	return NULL;
}

void CSelView::InstClear()
{
	for ( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		m_atSelView[wIndex].Clear();
	}
}

void CSelView::StopConf()
{
	TTPSelViewReq tReq;

	for ( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		if( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}
		tReq.m_bSel = FALSE;
		tReq.m_wConfID = Inst()->GetInsID();
		tReq.m_wScreenIndx = TP_MAX_STREAMNUM;
		tReq.m_wEpID = m_atSelView[wIndex].m_wEpID;
		UnSelView(tReq);
	}

	return ;
}

void CSelView::AskKeyFrame( u16 wEpID, u16 wScreenIndx )
{
	TEpViewInfo* ptInfo = FindByEP(wEpID);
	if ( NULL == ptInfo || !ptInfo->m_atViewMgr[wScreenIndx].IsValid() )
	{
		return ;
	}

	TSelViewMgr* ptMgr = &(ptInfo->m_atViewMgr[wScreenIndx]);
	if ( ptMgr->m_tSelView.m_emType == EmEpType_Eqp )
	{
		//向外设请求
		Inst()->GetVmp()->AskFrameToBrdVmp( ptMgr->m_ptItor, wEpID);
	}
	else if ( ptMgr->m_tSelView.m_emType == EmEpType_Ter )
	{
		CUmsConfInst::m_pcGetVidEx->AskKeyFrame(ptMgr->m_wGetIndex);
	}
	else
	{
		//出错
		MdlError(Ums_Mdl_Call, ("CSelView::AskKeyFrame. DstType Invalid! ConfID:%d, SelEp:%d, ScrIndx:%d, Dst:%d, DstType:%d\n", 
			Inst()->GetInsID(), ptMgr->m_tSelView.m_wEpID, ptMgr->m_tSelView.m_wScreenIndx, ptMgr->m_tSelView.m_wDstID, ptMgr->m_tSelView.m_emType));
	}

	return ;
}

void CSelView::OnSelViewNtfy( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TTPSelViewNtfy tSelview;
	TP_SAFE_CAST(tSelview, ptMsg->GetBody() + sizeof(TUmsHandle));

	TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tHandle.GetEpID());
	if ( NULL == ptForeNode )
	{
		MdlError(Ums_Mdl_Call, ("CSelView::OnSelViewNtfy ptSrcCapNode is NULL . ConfID:%d, EpID:%d, handleEpID:%d\n", Inst()->GetInsID(), tSelview.m_wEpID, tHandle.GetEpID()));
		return ;
	}

	//不是本级结点，则取得该会场的本级EpID
	if ( ptForeNode->IsUms() )
	{
		TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tSelview.m_wEpID);
		if ( NULL == ptNode || !ptNode->m_bUsed )
		{
			MdlError(Ums_Mdl_Call, ("CSelView::OnSelViewNtfy ptNode is NULL . ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tSelview.m_wEpID));
			return ;
		}
		tSelview.m_wEpID = ptNode->m_wEpID;

		//转成上级结点ID
		TCallNode* ptDstNode = NULL;
		for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
		{
			
			ptDstNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tSelview.m_atSelView[wIndex].m_wDstID);
			if ( NULL != ptDstNode && ptDstNode->m_bUsed )
			{
				tSelview.m_atSelView[wIndex].m_wEpID = ptNode->m_wEpID;
				tSelview.m_atSelView[wIndex].m_wDstID = ptDstNode->m_wEpID;
			}		
			tSelview.m_atSelView[wIndex].m_wConfID = Inst()->GetInsID();
		}
	}

	MdlHint(Ums_Mdl_Call, ("CSelView::OnSelViewNtfy. ConfID:%d, SelEp:%d\n", Inst()->GetInsID(), tSelview.m_wEpID));

	BOOL32 bValid = tSelview.IsHaveValid();

	TEpViewInfo* ptInfo = FindByEP(tSelview.m_wEpID);
	
	if ( NULL == ptInfo )
	{
		if ( bValid )
		{//添加
			ptInfo = FindIdle();
			if ( NULL != ptInfo )
			{
				ptInfo->m_wEpID = tSelview.m_wEpID;
				for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
				{
					memcpy(&ptInfo->m_atViewMgr[wIndex].m_tSelView, &tSelview.m_atSelView[wIndex], sizeof(TTPSelViewReq));
				}
				NtfySelInfoToUI(ptInfo);
			}
		}
	}
	else
	{
		if ( bValid )
		{//更新
			for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
			{
				memcpy(&ptInfo->m_atViewMgr[wIndex].m_tSelView, &tSelview.m_atSelView[wIndex], sizeof(TTPSelViewReq));
			}
			NtfySelInfoToUI(ptInfo);
		}
		else
		{//删除
			ptInfo->Clear();
			ptInfo->m_wEpID = tSelview.m_wEpID;
			NtfySelInfoToUI(ptInfo);
			ptInfo->m_wEpID = TP_INVALID_INDEX;
		}
	}

	return ;
}

void CSelView::NtfySelInfoToUI( TEpViewInfo* ptView )
{
	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(ptView->m_wEpID);
	TCallNode* ptNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(ptView->m_wEpID);
	if ( NULL == ptNode || !ptNode->IsChanOn() || NULL == ptNodeFather )
	{
		MdlError(Ums_Mdl_Call, ("CSelView::NtfySelInfoToUI. DstEP Not Line!, ConfID:%d, EpID:%d\n", Inst()->GetInsID(), ptView->m_wEpID));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CSelView::NtfySelInfoToUI. ConfID:%d, EpID:%d\n", Inst()->GetInsID(), ptView->m_wEpID));

	TTPSelViewNtfy tNtfy;
	tNtfy.m_wConfID = Inst()->GetInsID();
	tNtfy.m_wEpID = ptView->m_wEpID;
	
	for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		memcpy(&tNtfy.m_atSelView[wIndex], &ptView->m_atViewMgr[wIndex].m_tSelView, sizeof(TTPSelViewReq));
	}
	
	//通知所有UMC
	Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SelView_Ntfy, &tNtfy, sizeof(tNtfy));
	
	TUmsHandle tOutHandle;
	if ( ptNodeFather == ptNode )
	{
		//通知CNC
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SelView_Ntfy, &tNtfy, sizeof(tNtfy));
	}

	if ( !Inst()->IsChairConf() )
	{
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SelView_Ntfy, &tNtfy, sizeof(tNtfy));
	}

	return ;
}

void CSelView::NtfyAllSelInfoToUI(EmTpOprType emType, TLogUser* ptUser)
{
	MdlHint(Ums_Mdl_Call, ("CSelView::NtfyAllSelInfoToUI. ConfID:%d, Type:%d\n", Inst()->GetInsID(), emType));

	TTPSelViewNtfy tNtfy;
	tNtfy.m_wConfID = Inst()->GetInsID();
	for ( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		if ( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}

		tNtfy.m_wEpID = m_atSelView[wIndex].m_wEpID;

		for(u16 wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; wScreenIndex ++)
		{
			memcpy(&tNtfy.m_atSelView[wScreenIndex], &m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView, sizeof(TTPSelViewReq));
		}

		//通知UMC
		Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SelView_Ntfy, &tNtfy, sizeof(tNtfy), ptUser);
	}

	return ;
}

//上级收到 下级处理后给上级的回应 失败后才有回应
void CSelView::OnSelViewCasecadeInd( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TTPSelViewInd tInd;
	TP_SAFE_CAST(tInd, ptMsg->GetBody() + sizeof(TUmsHandle));

	TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tHandle.GetEpID());
	if ( NULL == ptForeNode )
	{
		MdlError(Ums_Mdl_Call, ("CSelView::OnSelViewCasecadeInd ptSrcCapNode is NULL . ConfID:%d, EpID:%d, handleEpID:%d\n", Inst()->GetInsID(), tInd.m_tSelView.m_wEpID, tHandle.GetEpID()));
		return ;
	}
	
	//不是本级结点，则取得该会场的本级EpID
	if ( ptForeNode->IsUms() )
	{
		TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tInd.m_tSelView.m_wEpID);
		if ( NULL == ptNode || !ptNode->m_bUsed )
		{
			MdlError(Ums_Mdl_Call, ("CSelView::OnSelViewCasecadeInd ptNode is NULL . ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tInd.m_tSelView.m_wEpID));
			return ;
		}
		tInd.m_tSelView.m_wEpID = ptNode->m_wEpID;
	}

	MdlHint(Ums_Mdl_Call, ("CSelView::OnSelViewCasecadeInd. ConfID:%d, EpID:%d, ScrIndx:%d, DstID:%d, DstType:%d, Ret:%d, UI:%d\n", 
		Inst()->GetInsID(), tInd.m_tSelView.m_wEpID, tInd.m_tSelView.m_wScreenIndx, tInd.m_tSelView.m_wDstID, tInd.m_tSelView.m_emType,
		tInd.m_emRet, tInd.m_tSelView.m_emUIType));

	//回应给 UMC或者CNC
	if( tInd.m_tSelView.m_emUIType == EmUI_UMC )
	{
		Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SelView_Ind, &tInd, sizeof(tInd));
	}
	else
	{
		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, tInd.m_tSelView.m_wEpID);
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SelView_Ind, &tInd, sizeof(tInd));
	}

	return ;
}

void CSelView::HungUpNode( TCallNode* ptNode )
{
	if ( NULL == ptNode )
	{
		return ;
	}

	if ( !ptNode->IsMtEp() )
	{
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CSelView::HungUpNode. ConfID:%d, EpID:%d\n", Inst()->GetInsID(), ptNode->m_wEpID));

	TTPSelViewReq tReq;
	for(u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++)
	{
		if ( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}

		if ( m_atSelView[wIndex].m_wEpID == ptNode->m_wEpID)
		{
			tReq.m_bSel = FALSE;
			tReq.m_wConfID = Inst()->GetInsID();
			tReq.m_wScreenIndx = TP_MAX_STREAMNUM;
			tReq.m_wEpID = m_atSelView[wIndex].m_wEpID;
			UnSelView(tReq);
			continue;
		}

		for (u16 wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; ++wScreenIndex)
		{
			if (!m_atSelView[wIndex].m_atViewMgr[wScreenIndex].IsValid())
			{
				continue;
			}

			if (m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wDstID != ptNode->m_wEpID)
			{
				continue;
			}

			if(m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType != EmEpType_Ter)
			{
                continue;
			}
			
			tReq.m_bSel = FALSE;
			tReq.m_wConfID = Inst()->GetInsID();
			tReq.m_emType = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType;
			tReq.m_wScreenIndx = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wScreenIndx;
			tReq.m_wEpID = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wEpID;
			UnSelView(tReq);
		}
	}
	
	return ;
}

void CSelView::GetSelSrcAddr( u16 wEpID, u16 wScreenIndx, TTPMediaTransAddr& tAddr, u32& dwEqpNode )
{
	TEpViewInfo* ptInfo = FindByEP(wEpID);
	if ( NULL == ptInfo || !ptInfo->m_atViewMgr[wScreenIndx].IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CSelView::GetSelSrcAddr. ptMgr is NULL!! ConfID:%d, EpID:%d, ScrIndx:%d\n", 
			Inst()->GetInsID(), wEpID, wScreenIndx));
		return ;
	}

	TSelViewMgr* ptMgr = &(ptInfo->m_atViewMgr[wScreenIndx]);
	if ( ptMgr->m_tSelView.m_emType == EmEpType_Eqp )
	{
		TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(ptInfo->m_wEpID);
		TCapNode* ptNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(ptInfo->m_wEpID);
		if ( NULL == ptNode || !ptNode->IsChanOn() || NULL == ptNodeFather )
		{
			MdlError(Ums_Mdl_Call, ("CSelView::GetSelSrcAddr. ViewEP Not Line!, ConfID:%d, EpID:%d\n", Inst()->GetInsID(), ptInfo->m_wEpID));
			return ;
		}

		if ( NULL == ptMgr->m_ptItor )
		{
			return ;
		}

		TTPDsFrom tAddrOut;
		if (ptMgr->m_bEpSel)
		{//会场选看
			if ( wScreenIndx == MIDSCREENINDEX )
			{
				Inst()->GetVmp()->GetBrdVmpOutAddr(ptMgr->m_ptItor, tAddrOut, ptNodeFather->m_tVidRcvFormat.m_tFormat);
			}
		}
		else
		{
			Inst()->GetVmp()->GetBrdVmpOutAddr(ptMgr->m_ptItor, tAddrOut, ptNodeFather->m_tVidRcvFormat.m_tFormat);
		}

		tAddr.m_tRtpAddr = tAddrOut.m_tRtpAddr;
		tAddr.m_tBackRtcpAddr = tAddrOut.m_tBackRtcpAddr;
		dwEqpNode = tAddrOut.m_dwEqpNode;
	}
	else if( ptMgr->m_tSelView.m_emType == EmEpType_Ter )
	{
		if ( ptMgr->m_wGetIndex >= TP_UMS_MAX_CALLNUM )
		{
			return ;
		}
		tAddr = ptMgr->m_tGetAddr.m_atVidAddr[MIDSCREENINDEX];
		dwEqpNode = ptMgr->m_tGetAddr.m_adwMediaNode[MIDSCREENINDEX];
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CSelView::GetSelSrcAddr. SelType Error!! ConfID:%d, EpID:%d, ScrIndx:%d, type:%d\n", 
							Inst()->GetInsID(), wEpID, wScreenIndx, ptMgr->m_tSelView.m_emType));
	}

	return ;
}

void CSelView::AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetVideIndex, EmGetVidRet emRet)
{
	BOOL32 bUi = FALSE;

	u32 dwReason = TP_UMS_View_VmpDisCnnt;
	if ( emRet == EmGetVidRet_BasDisCnnt )
	{
		dwReason = TP_UMS_View_BasDisCnnt;
	}
	else if( emRet == EmGetVidRet_VmpDisCnnt )
	{
		dwReason = TP_UMS_View_VmpDisCnnt;
	}
	else if ( emRet == EmGetVidRet_BWFull )
	{
		dwReason = TP_UMS_View_BWFull;
	}
	else if ( emRet == EmGetVidRet_NoVid )
	{
		dwReason = TP_UMS_View_NoVid;
	}
	else if ( emRet == EmGetVidRet_NoVmp )
	{
		dwReason = TP_UMS_View_NoVmp;
	}
	else if ( emRet == EmGetVidRet_VmpDisConnect )
	{
		dwReason = TP_UMS_View_VmpDisCnnt;
	}

	TTPSelViewReq tReq;

	u16 wDstEpID = TP_INVALID_INDEX;
	for( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		if ( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}

		bUi = FALSE;
		wDstEpID = TP_INVALID_INDEX;
		for (u16 wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; ++wScreenIndex)
		{
			if ( m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_wGetIndex == wGetVideIndex )
			{
				bUi = TRUE;
				wDstEpID = m_atSelView[wIndex].m_wEpID;

				if ( emRet == EmGetVidRet_NoVmp )
				{//这种原因只提示
					break;
				}

				tReq.m_bSel = FALSE;
				tReq.m_wConfID = Inst()->GetInsID();
				tReq.m_emType = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType;
				tReq.m_wScreenIndx = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wScreenIndx;
				tReq.m_wEpID = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wEpID;

				if (MIDSCREENINDEX == wScreenIndex && 
					m_atSelView[wIndex].IsNoGetVidView(0) && 
					m_atSelView[wIndex].IsNoGetVidView(2))
				{
					tReq.m_wScreenIndx = TP_MAX_STREAMNUM;
				}

				UnSelView(tReq);
			}
		}

		if ( !bUi || !TP_VALID_HANDLE(wDstEpID) )
		{
			continue;
		}

		Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, dwReason, wDstEpID, wDstEpID);
	}
}

void CSelView::BrdVmpCB( TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr)
{
	TTPSelViewReq tReq;
	u16 wDstEpID = TP_INVALID_INDEX;
	BOOL32 bUi = FALSE;
	for( u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++ )
	{
		if ( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}

		bUi = FALSE;
		wDstEpID = TP_INVALID_INDEX;
		for (u16 wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; ++wScreenIndex)
		{
			if ( m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_ptItor == ptRes || 
				(m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wDstID == ptRes->m_tEqpInfo.m_byEqpID &&
				 m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType == EmEpType_Eqp))
			{
				bUi = TRUE;
				wDstEpID = m_atSelView[wIndex].m_wEpID;

				tReq.m_bSel = FALSE;
				tReq.m_wConfID = Inst()->GetInsID();
				tReq.m_emType = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType;
				tReq.m_wScreenIndx = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wScreenIndx;
				tReq.m_wEpID = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wEpID;
				UnSelView(tReq);
			}
		}

		if ( !bUi || !TP_VALID_HANDLE(wDstEpID) )
		{
			continue;
		}

		if (EmBrdVmpCBOprType_Stop == emOpr)
		{
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_View_VmpStop, wDstEpID, wDstEpID);
		} else
		{
            Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_View_VmpDisCnnt, wDstEpID, wDstEpID);
		}
		//提示 选看取消
	}
	return ;
}

s8* CSelView::GetSelObj( u16 wEpID, u16 wScreenIndx, u16& wVidNum )
{
	TEpViewInfo* ptInfo = FindByEP(wEpID);
	if ( NULL == ptInfo || !ptInfo->m_atViewMgr[wScreenIndx].IsValid())
	{
		MdlError(Ums_Mdl_Call, ("CSelView::GetSelAlias. ptMgr is NULL!! ConfID:%d, EpID:%d, ScrIndx:%d\n", 
			Inst()->GetInsID(), wEpID, wScreenIndx));
		return NULL;
	}
	
	TSelViewMgr* ptMgr = &(ptInfo->m_atViewMgr[wScreenIndx]);
	
	if ( ptMgr->m_tSelView.m_emType == EmEpType_Eqp )
	{
		if ( NULL != ptMgr->m_ptItor )
		{
			wVidNum = 1;
			return ptMgr->m_ptItor->m_tEqpInfo.m_szEqpAlias;
		}
	}
	else if( ptMgr->m_tSelView.m_emType == EmEpType_Ter )
	{
		TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(ptMgr->m_tSelView.m_wDstID);
		if ( NULL == ptNode || !ptNode->IsChanOn() )
		{
			MdlError(Ums_Mdl_Call, ("CSelView::GetSelAlias. DstEP Not Line!, ConfID:%d, EpID:%d\n", Inst()->GetInsID(), ptMgr->m_tSelView.m_wEpID));
			return NULL;
		}

		if ( ptMgr->m_wGetIndex < TP_UMS_MAX_CALLNUM )
		{
			wVidNum = 1;
		}
		
		return ptNode->m_tConfName.m_abyAlias;
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CSelView::GetSelAlias. SelType Error!! ConfID:%d, EpID:%d, ScrIndx:%d, type:%d\n", 
														Inst()->GetInsID(), wEpID, wScreenIndx, ptMgr->m_tSelView.m_emType));
	}
	return NULL;
}

void CSelView::OnUnSelAllView( CTpMsg *const ptMsg )
{
	TTPSelViewReq tReq;

	for(u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++)
	{
		if ( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}
		
		tReq.m_bSel = FALSE;
		tReq.m_wConfID = Inst()->GetInsID();
		tReq.m_wScreenIndx = TP_MAX_STREAMNUM;
		tReq.m_wEpID = m_atSelView[wIndex].m_wEpID;
		UnSelView(tReq);
	}
}

void CSelView::AdjustCnsSpeaker( TCallNode* ptNode )
{//ptNode 被选看会场

	for(u16 wIndex = 0; wIndex < UMS_MAX_SELVIEW_NUM; wIndex ++)
	{
		if ( !m_atSelView[wIndex].Valid() )
		{
			continue;
		}

		TCapNode* ptNodeFather = Inst()->GetNodeMgr()->GetForeFatherNode(m_atSelView[wIndex].m_wEpID);
		if ( NULL == ptNodeFather || !ptNodeFather->IsChanOn())
		{
			continue;
		}
		for (u16 wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; ++wScreenIndex)
		{
			if (!m_atSelView[wIndex].m_atViewMgr[wScreenIndex].IsValid())
			{
				continue;
			}
			
			if (m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType != EmEpType_Ter)
			{
				continue;
			}

			if (m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wDstID != ptNode->m_wEpID)
			{
				continue;
			}

			if ( m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_bEpSel )
			{//会场选看，发言坐席不需要对应切换
				continue;
			}

			if(m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_wGetIndex >= TP_UMS_MAX_CALLNUM)
			{
                continue;
			}

			EmGetVidRes emRet = CUmsConfInst::GetVidAudEx()->UpdateAddr( Inst(), em_GetVid_View, m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_wGetIndex, 
				m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tGetAddr, ptNode->GetSpeaker(), ptNodeFather->m_tVidRcvFormat);
			if ( emRet != EmGetVidRet_Success )
			{//分配失败，释放
				TTPSelViewReq tReq;
				tReq.m_bSel = FALSE;
				tReq.m_wConfID = Inst()->GetInsID();
				tReq.m_emType = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_emType;
				tReq.m_wScreenIndx = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wScreenIndx;
				tReq.m_wEpID = m_atSelView[wIndex].m_atViewMgr[wScreenIndex].m_tSelView.m_wEpID;
				UnSelView(tReq);
				continue ;
			}

			Inst()->GetNodeFsm()->UpdateMediaTrans(m_atSelView[wIndex].m_wEpID);
		}
	}
}

EmViewRetReason CSelView::ConvertGetVidReason(const EmGetVidRes emGetVid)
{
	
	if (em_GetVid_Invalid_Param == emGetVid)
	{
		return EmViewRetReason_InValidEp;
	}
	else if (em_GetVid_No_BandWidth == emGetVid)
	{
		return EmViewRetReason_NoBwRes;
	}
	else if (em_GetVide_No_BasResource == emGetVid)
	{
		return EmViewRetReason_NoBasRes;
	}
	else if (em_GitVid_No_Resource == emGetVid || em_GetVid_No_AddrResource == emGetVid)
	{
		return EmViewRetReason_SelFull;
	}
	else
	{
		MdlError(Ums_Mdl_Call,("CSelView::GetFailReason GetType Error!!\n"));
		return EmViewRetReason_InValidEp;
	}
 
}


BOOL32 CSelView::RestoreAdjustedResForSelEp(u16 wSelTargetEp, u16 wScreenIndex)
{
    return Inst()->GetUmsDiscuss()->RestoreAdjustedResForSelEp(wSelTargetEp, wScreenIndex);
}


BOOL32 CSelView::AdjustResForUnSelEp(u16 wSelTargetEp, u16 wScreenIndex)
{
    return Inst()->GetUmsDiscuss()->AdjustResForUnSelEp(wSelTargetEp, wScreenIndex);
}