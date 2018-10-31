#include "umsmcumgr.h"
#include "callnodemgr.h"
#include "umsstackinterface.h"
#include "eventoutumsmcucasecade.h"

extern CUmsCallMgrApp g_cUmsCallMgrApp;

void CUmsMcuMgr::OnStopConf()
{
	
}

BOOL32 CUmsMcuMgr::HandlerFromCns( CTpMsg *const ptMsg )
{
/*	switch (ptMsg->GetEvent())
	{
	case :
		{
			
		}
		break;
	default:
		{
			return FALSE;
		}
	}

	*/
	return FALSE;
}

BOOL32 CUmsMcuMgr::McuCaseCadeConnect( TCapNode* ptNode )
{
	if (NULL == ptNode)
	{	
		return FALSE;
	}
	TMcuInfo* ptInfo = NULL;
	u16 wIndex = 0;
	for (; wIndex < UMS_MAX_MCU_SIZE; ++wIndex)
	{
		if (!m_atMcuInfo[wIndex].m_bUsed)
		{
			ptInfo = &m_atMcuInfo[wIndex];
			break;;
		}
	}

	if (NULL == ptInfo)
	{
		return FALSE;
	}

	ptInfo->Clear();
	ptInfo->m_bUsed				= TRUE;
	ptInfo->m_ptMcuNode = ptNode;

	return TRUE;
}

BOOL32 CUmsMcuMgr::McuCaseCadeSpyBWNty( TCapNode* ptNode, u32 dwSpyBW )
{
	if (NULL == ptNode || 0 == dwSpyBW)
	{
		MdlError(Ums_Mdl_Call, ("CUmsMcuMgr::McuCaseCadeSpyBWNty. ptNode is null or dwSpyBW is 0!\n"));
		return FALSE;
	}

	TMcuInfo* ptInfo = NULL;
	u16 wIndex = 0;
	for (; wIndex < UMS_MAX_MCU_SIZE; ++wIndex)
	{
		if (m_atMcuInfo[wIndex].m_bUsed && ptNode == m_atMcuInfo[wIndex].m_ptMcuNode)
		{
			ptInfo = &m_atMcuInfo[wIndex];
			break;
		}
	}
	
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("CUmsMcuMgr::McuCaseCadeSpyBWNty. no match mcu !\n"));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsMcuMgr::McuCaseCadeSpyBWNty. wConfId:%d, wEpID:%d, dwSpyBW:%d!\n", 
					m_pcConf->GetInsID(), ((TCallNode*)ptNode)->m_wEpID, dwSpyBW));

	ptInfo->m_bSupMultSpy		= TRUE;
	ptInfo->m_dwMaxSpyBW		= dwSpyBW;
	ptInfo->m_dwRemainSpyBW		= dwSpyBW;

	return TRUE;
}

void CUmsMcuMgr::Show()
{
	msgprintnotime("[CUmsMcuMgr:]\n");
	
	TMcuInfo* ptInfo = NULL;
	u16 wIndex = 0;
	for (; wIndex < UMS_MAX_MCU_SIZE; ++wIndex)
	{	
		ptInfo = &m_atMcuInfo[wIndex];
		if (!ptInfo->m_bUsed)
		{
			continue;
		}
		msgprintnotime("  wEpID:%d, bSupMulSpy:%d, dwMaxSpyBW:%d, dwReamainSpyBW:%d\n", 
			((TCallNode*)ptInfo->m_ptMcuNode)->m_wEpID, ptInfo->m_bSupMultSpy, ptInfo->m_dwMaxSpyBW, ptInfo->m_dwRemainSpyBW
			);
		
		u16 wChanInde = 0;
		TMcuSypChan* ptChan = NULL;
		for (; wChanInde < UMS_MAX_MT_SIZE; ++wChanInde)
		{
			ptChan = &m_atMcuInfo[wIndex].m_atMcuSpyChan[wChanInde];
			if (!ptChan->m_bUsed)
			{
				continue;
			}
			msgprintnotime("  dwVidBW:%d, dwAudBW:%d\n", 
				ptChan->m_dwVidBW, ptChan->m_dwAudBW);
		}

		//msgprintnotime("  rtp("ADDRPORT_FORMAT")\n\n", ADDRNET(ptVmpInfo->m_tRtpAddr));
	}
	
	
}


void CUmsMcuMgr::Clear()
{
	u16 wIndex = 0;
	for (; wIndex < UMS_MAX_MCU_SIZE; ++wIndex)
	{
		m_atMcuInfo[wIndex].Clear();
	}
}

BOOL32 CUmsMcuMgr::AssignMcuSpyChan(u16 wMcuLowEpId)
{// to do ...
	if (NULL == m_pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CUmsMcuMgr::TestGetMcuSpyChan. conf is NULL!\n"));
		return FALSE;
	}
	MdlHint(Ums_Mdl_Call, ("CUmsMcuMgr::TestGetMcuSpyChan. ConfID:%d, wMcuLowEpId:%d!\n", 
				m_pcConf->GetInsID(), wMcuLowEpId));

	TCallNode* ptNode	= m_pcConf->GetNodeMgr()->GetNode(wMcuLowEpId);
	TCapNode* ptParent	= m_pcConf->GetNodeMgr()->GetForeFatherNode(ptNode);
	
	if (!ptNode || ptNode == ptParent || !ptParent->IsMcu())
	{
		MdlError(Ums_Mdl_Call, ("CUmsMcuMgr::TestGetMcuSpyChan sel ep is not mcu low ep. wMcuLowEpId:%d!\n",
						wMcuLowEpId));
		return FALSE;
	}

	TUmsHandle tOutHandle;
	TUmsMcuChan tOutChan;
	m_pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptParent->m_wEpID);
	tOutChan.m_hMcuChan = ptParent->m_hMcuChan;
	tOutChan.m_hMcuAppChan = ptParent->m_hMcuAppChan;
	
	EmTpVideoResolution emRes = ptParent->m_tVidSndFormat.m_tFormat.m_emRes;

	// 
	u32 dwPID = MAKEIID(UMS_MCU_PART_MAX_NUM, ptParent->m_wLowChildEpID);//
	TMcuSpyReq tReq;
	tReq.m_dwPID = dwPID;
	tReq.m_emRes = emRes;

	// to do ...
	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_MultSpyReq, &tReq, sizeof(TMcuSpyReq));
	return TRUE;
}

API void getmcuspy(u16 wConf, u16 wMcuLowEpId)
{
	CUmsConfInst* pInst = (CUmsConfInst*)((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConf);
	if (NULL == pInst || NULL == pInst->GetMcuMgr())
	{
		msgprintnotime("inst or mcu mgr is null!\n");
		return;
	}
	
	pInst->GetMcuMgr()->AssignMcuSpyChan(wMcuLowEpId);
}