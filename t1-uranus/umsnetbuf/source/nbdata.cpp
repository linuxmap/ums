#include "tpobject.h"
#include "nbdata.h"
#include "netbuf.h"

CNbData::CNbData()
{
	
}
CNbData::~CNbData()
{
	
}
BOOL32 CNbData::Init(u32 dwNbNum)
{
	//不可重复创建
	if(!m_tNbList.Create(dwNbNum))
	{
		msgprint("CNbData::Init Create switch chan failed!\n");
		return FALSE;
	}
	
	for (u16 wIndex = 0; wIndex <=TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		m_atNbData[wIndex].Clear();
	}
	return TRUE;
}

CNbListPtr CNbData::AddNbData(u16 wConfID, TUmsNetBuf& tNb)
{
	if (wConfID > TP_UMS_MAX_CONFNUM)
	{
		return NULL;
	}

	TUmsNetBufPara tPara;
	tPara.m_tRcvRtcpAddr = tNb.m_tRcvRtcpAddr;
	tPara.m_tRcvRtpAddr = tNb.m_tRcvRtpAddr;
	tPara.m_tRmtRtcpAddr = tNb.m_tRmtRtcpAddr;
	tPara.m_wSndAddr = tNb.m_wSndAddr;
	
	CNbListPtr pPtr = m_tNbList.WriteBuffItor(tPara);
	if (NULL == pPtr)
	{
		return NULL;
	}

	m_atNbData[wConfID].Insert(pPtr);
	return pPtr;
}

BOOL32 CNbData::DelNbData(u16 wConfID, TUmsNetBuf& tNb, HandleNetbuf& tHandle)
{
	if (wConfID > TP_UMS_MAX_CONFNUM)
	{
		return FALSE;
	}

	CNbListPtr pPtr = m_atNbData[wConfID].DelNode(tNb);
	if (NULL == pPtr)
	{
		return FALSE;
	}
	
	m_tNbList.FreeBuff(pPtr);	

	tHandle = pPtr->m_tData.m_Handle;
	pPtr->m_tData.Clear();

	return TRUE;
}


void CNbData::Show()
{
	msgprint("Show nb begin..............\n");
	CConfNb* ptNb;
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		ptNb = &m_atNbData[wIndex];

		if (ptNb->GetElementNum() == 0)
		{
			continue;
		}
		msgprint("  Conf:%d Total:%dbegin..............\n", wIndex, ptNb->GetElementNum());

		CNbListPtr itor = ptNb->GetHead();
		u16 wCount = 1;
		while (NULL != itor)
		{
			msgprint("    Index:%d Handle:0x%x, RcvAddr("ADDRPORT_FORMAT")\n", wCount, itor->m_tData.m_Handle, ADDRNET(itor->m_tData.m_tRcvRtpAddr));

			itor = itor->Next();
			wCount++;
		}

		msgprint("  Conf:%d end..............\n\n", wIndex);	
		
	}
	msgprint("Show nb end..............\n");
}

void CNbData :: DelAllNbData()
{

	CConfNb* ptNb = NULL;
	CNbListPtr ptItor = NULL;
	HandleNetbuf ptHandle = NULL;
	u16 wcount = 0;
	for (u16 wIndex = 0; wIndex <=TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		ptNb = &m_atNbData[wIndex]; 
		ptItor = NULL;
		while(NULL != ptNb->GetHead())
		{			
			ptItor = ptNb->GetHead();
			ptNb->SetHeadNext();
			ptItor->m_ptNext = NULL;
			ptHandle = ptItor->m_tData.m_Handle;
			if (NULL != ptHandle)
			{			
				CNetBuf* pNetBuf = (CNetBuf*)ptHandle;
				delete pNetBuf;
			}
			ptItor->m_tData.Clear();
			m_tNbList.FreeBuff(ptItor);			
			wcount++;
			msgprint("CNbData::clean num is ....%d!\n",wcount);

		}
		
		ptNb->Clear();
		msgprint("CNbData::cleaning  conf Id %d!\n",wIndex);
	}
	msgprint("CNbData::Delet all netbuf data!\n");

}
