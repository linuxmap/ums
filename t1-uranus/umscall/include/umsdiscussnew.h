#ifndef _h_umsdiscussnew_h__
#define _h_umsdiscussnew_h__

#include "callinnerstruct.h"
#include "umscommonstruct.h"
#include "vmpserviecehandler.h"
#include "callnodemgr.h"
#include "umseapu.h"
#include "putaud.h"
#include "getvidaud.h"

#define UmsDiscuss_VmpEp_Max_Num     9  


typedef struct tagTDisVidBasUserInfo
{
    u16  m_wDisUserCount;
    u16  m_wSelUserCount;

	tagTDisVidBasUserInfo()
	{
       Clear();
	}

	void Clear()
	{
		m_wDisUserCount = 0;
        m_wSelUserCount = 0;
	}

}TDisVidBasUserInfo;

// ���ۻ᳡��Ϣ
typedef struct tagTDiscussEpInfo
{
	u16     m_wIndex;  // ��m_atDiscussEpInfo[TP_CONF_MAX_AUDMIXNUM]�е��������̶�
	u16     m_wEpID;   	
	u16     m_wStrceenNum;    // ���� 

	BOOL32  m_bUsed;
	BOOL32  m_bIsSmallChanOn;
	BOOL32  m_bMtAdjustRes;   // �û᳡�Ƿ�֧�ֽ��ֱ���

	EmTpVideoResolution m_aemVideoRes[TP_MAX_STREAMNUM];  // ����һ�½��ķֱ��ʸ�ʽ�����ڻָ�
	CScreenBasRes*      m_apcBas[TP_MAX_STREAMNUM];
	TDisVidBasUserInfo   m_awBasUserinfo[TP_MAX_STREAMNUM];

	CDsListInfo         m_cToBasDsInfo; // ��С�����Ļ᳡��������Ľ��������ϳ�Сͼ�������������ȡ�����ϳɵĴ�ͼ����������Ҫ����������

	TTPMediaTransAddr   m_atPutAuddr[TP_MAX_STREAMNUM]; // �����۳�Ա���¼��л��õ���1. �ϼ����û᳡��Ҫ����Ƶ��ַ�����2. �¼�ȡ�������Ƶ��node    
	CDsListInfo         m_cToPutAuddrDsInfo;

	TGetVidAddr			m_tGetAddr;   // ���۳�Ա�ϵ�������ַ
	u16                 m_awGetIndex[TP_MAX_STREAMNUM];  // �ϵ�������index���ͷŵ�ʱ����õ�

	tagTDiscussEpInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_wStrceenNum = 0;
		m_bUsed = FALSE;
		m_bIsSmallChanOn = FALSE;
		m_bMtAdjustRes = FALSE;
		ClearBasInfo();
		ClearGetVidAddr();
		ClearPutAuddr();
		return;
	}
	
	void ClearBasInfo()
	{
		m_cToBasDsInfo.Clear();
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_apcBas[wIndex] = NULL;
			m_aemVideoRes[wIndex] = emTPVResEnd;
			m_awBasUserinfo[wIndex].Clear();
		}
	}
	
	void ClearPutAuddr()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atPutAuddr[wIndex].Clear();
			m_cToPutAuddrDsInfo.Clear();
		}
	}

	void ClearGetVidAddr()
	{
		memset(&m_tGetAddr, 0, sizeof(tagTGetVidAddr));
		
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_awGetIndex[wIndex] = TP_INVALID_INDEX;
		}
	}

	BOOL32 IsValid()
	{
		return (IsSingleScr() || IsThreeScr());
	}

	BOOL32 IsSingleScr()
	{
		return (1 == m_wStrceenNum);
	}
	
	BOOL32 IsThreeScr()
	{
		return (3 == m_wStrceenNum);
	}

	BOOL32 IsEqualGetVidIndx(u16 wGetVidIndx)
	{
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if(m_awGetIndex[wIndex] == wGetVidIndx)
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	void SetGetVidAddr(u16 wScreenIndx, TGetVidAddr& tAddr)
	{
		m_tGetAddr.m_atVidAddr[wScreenIndx] = tAddr.m_atVidAddr[MIDSCREENINDEX];
		m_tGetAddr.m_atAudAddr[wScreenIndx] = tAddr.m_atAudAddr[MIDSCREENINDEX];
		m_tGetAddr.m_atSmallAddr[wScreenIndx] = tAddr.m_atSmallAddr[MIDSCREENINDEX];
		m_tGetAddr.m_adwMediaNode[wScreenIndx] = tAddr.m_adwMediaNode[MIDSCREENINDEX];

		if ( wScreenIndx == MIDSCREENINDEX )
		{
			m_tGetAddr.m_tMixAddr = tAddr.m_tMixAddr;
			m_tGetAddr.m_dwMedia = tAddr.m_dwMedia;
		}
	}
	
}TDiscussEpInfo;

// ÿ����Ŀ������
typedef struct tagTDiscussScreenInfo
{
	u16      m_wVmpEpNum;   // С����·��
	BOOL32   m_bThreeScr;   // ����Ŀ���Ƿ�������
	TTPAlias m_tAlias;      // ����ʾ�����ƣ���0·��ͼ��Ļ᳡��;

	// �ϳɲ���
	TVmpMemberInfo	m_atMember[UMS_VMP_MAX_RCV];  // �����dwhandle������ǽ��ϳɵ�wEpId��wSeatIndex
	TDBPayload		m_atPayload[UMS_VMP_MAX_RCV];

	tagTDiscussScreenInfo()
	{
		Clear();
	}

	tagTDiscussScreenInfo& operator=(const tagTDiscussScreenInfo& tInfo)
	{
		if (this != &tInfo)
		{
			memcpy(this, &tInfo, sizeof(tagTDiscussScreenInfo));
		}		
		return *this;
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussScreenInfo));
	}

	void ClearDstEpInfo()
	{// ��0·�Ǵ�ͼ��
		m_bThreeScr = FALSE;
		m_tAlias.Clear();
		m_atMember[0].Clear();
		m_atPayload[0].Clear();
	}

	void ClearVmpEpInfo()
	{//��1·����9·��Сͼ��
		for (u16 wIndex = 1; wIndex < UMS_VMP_MAX_RCV; wIndex++)
		{
			m_atMember[wIndex].Clear();
			m_atPayload[wIndex].Clear();
		}
		m_wVmpEpNum = 0;
	}

	void CopyDstEpInfo(const tagTDiscussScreenInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_bThreeScr = tInfo.m_bThreeScr;
			m_tAlias = tInfo.m_tAlias;
			m_atMember[0] = tInfo.m_atMember[0];
			m_atPayload[0] = tInfo.m_atPayload[0];
		}
	}

	void CopyVmpEpInfo(const tagTDiscussScreenInfo& tInfo)
	{
		if (this != &tInfo)
		{
			for (u16 wIndex = 1; wIndex < UMS_VMP_MAX_RCV; wIndex++)
			{
				m_atMember[wIndex] = tInfo.m_atMember[wIndex];
				m_atPayload[wIndex] = tInfo.m_atPayload[wIndex];
			}
			m_wVmpEpNum = tInfo.m_wVmpEpNum;
		}
	}

	void AddDstEp(TCallNode* ptDstNode, u16 wDstSeatIndex)
	{
		m_bThreeScr = ptDstNode->IsThreeVidSnd();
		m_tAlias = ptDstNode->m_tConfName;
			// �ϳɲ���
		m_atMember[0].m_bMerged = FALSE;
		m_atMember[0].MakeHandle(ptDstNode->m_wEpID, wDstSeatIndex);
		m_atPayload[0].m_byActivePayload = ptDstNode->m_tVidSndFormat.m_wDynamicPayload;
		m_atPayload[0].m_byRealPayload = ptDstNode->m_tVidSndFormat.m_wStaticPayload;
		return;
	}

	void UptateDstEpSeat(TCallNode* ptDstNode)
	{
		m_atMember[0].MakeHandle(ptDstNode->m_wEpID, ptDstNode->GetSpeaker());
		return;
	}

	void AddVmpDstEp(TCallNode* ptDstNode)
	{// ��ͬһ���������֮ǰ�Ѿ���ӣ�ֱ�ӷ���
		if (IsEpInScreen(ptDstNode->m_wEpID, 1))
		{
			return;
		}
		
		if (UmsDiscuss_VmpEp_Max_Num < m_wVmpEpNum + ptDstNode->m_wVidSndNum)
		{// ��λ�ò�����ֱ�ӷ���
			return;
		}
		
		u16 wAddIndex = m_wVmpEpNum + 1; // Сͼ��ϳɳ�Ա�ӵ�1·��ʼ
		if (ptDstNode->IsThreeVidSnd())
		{
			for (u16 wLoop = 0; wLoop  < TP_MAX_STREAMNUM; wLoop++)
			{// �ϳɲ���
				m_atMember[wAddIndex].m_bMerged = (2 != wLoop)?TRUE:FALSE;
				m_atMember[wAddIndex].MakeHandle(ptDstNode->m_wEpID, wLoop);
				m_atPayload[wAddIndex].m_byActivePayload = ptDstNode->m_tVidSndFormat.m_wDynamicPayload;
				m_atPayload[wAddIndex].m_byRealPayload = ptDstNode->m_tVidSndFormat.m_wStaticPayload;
				m_wVmpEpNum++;
				wAddIndex++;
			}
		}
		else
		{// �ϳɲ���
			m_atMember[wAddIndex].m_bMerged = FALSE;
			m_atMember[wAddIndex].MakeHandle(ptDstNode->m_wEpID, MIDSCREENINDEX);
			m_atPayload[wAddIndex].m_byActivePayload = ptDstNode->m_tVidSndFormat.m_wDynamicPayload;
			m_atPayload[wAddIndex].m_byRealPayload = ptDstNode->m_tVidSndFormat.m_wStaticPayload;
			m_wVmpEpNum++;
		}
		return;
	}

	BOOL32 IsScreenValid()
	{
		return (IsDstEpValid() || IsVmpEpValid());
	}

	BOOL32 IsVmpEpValid()
	{
		return (0 != m_wVmpEpNum);
	}

	BOOL32 IsDstEpValid()
	{
		return (0 != m_atMember[0].m_dwHandle);
	}

	BOOL32 IsDstEpThreeScr()
	{
		return m_bThreeScr;
	}

	BOOL32 IsEpInScreen(const u16 wEpId, u16 wFindIndex = 0)
	{
		u16 wIndex = wFindIndex;
		for (wIndex; wIndex < UMS_VMP_MAX_RCV; wIndex++)
		{
			if (wEpId == m_atMember[wIndex].GetHandleOne())
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL32 FindVmpIndexbyEpId(const u16 wEpId, TPOUT u8& byFindIndex)
	{
		byFindIndex = 0xFF;
		if (!IsVmpEpValid())
		{
			return FALSE;
		}
		for (u8 byIndex = 1; byIndex < UMS_VMP_MAX_RCV; byIndex++)
		{
			if (wEpId == m_atMember[byIndex].GetHandleOne())
			{
				byFindIndex = byIndex;
				if (wEpId == m_atMember[byIndex+1].GetHandleOne())
				{
					return TRUE; // ˵���˻᳡�Ǹ���������������Сͼ����ͬһ��
				}
				return FALSE;
			}
		}
		return FALSE;
	}
	
	
}TDiscussScreenInfo;

typedef struct tagTDiscussSpeakerRec
{
	u16 m_awSpeakerRec[UmsDiscuss_VmpEp_Max_Num];
	
	tagTDiscussSpeakerRec()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussSpeakerRec));
	}
	
	void AddRec(u16 wEpId)
	{// ���һ���¼�¼�����ڵ�һ��λ�ã����֮ǰ���ڣ�ҲŲ����һ��λ��
		if (wEpId == m_awSpeakerRec[0])
		{
			return;
		}
		
		u16 wIndex = 0;
		u16 wReplaceIndex = 0;
		for (wIndex = 1; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
		{// ��ȷ���Ƿ����					
			if (wEpId == m_awSpeakerRec[wIndex])
			{
				break;
			}
		}
		
		if (UmsDiscuss_VmpEp_Max_Num == wIndex)
		{// ������
			wIndex--;
		}		
		wReplaceIndex = wIndex;		
		
		for (wIndex = wReplaceIndex - 1; wIndex > 0; wIndex--)
		{// �����Ų��λ��
			m_awSpeakerRec[wIndex + 1] = m_awSpeakerRec[wIndex];
		}	
		m_awSpeakerRec[wIndex + 1] = m_awSpeakerRec[wIndex];	
		m_awSpeakerRec[0] = wEpId;
	}
	
	void DelRec(u16 wEpId)
	{// ɾ��һ����¼
		u16 wIndex = 0;
		u16 wDelIndex = 0;
		
		for (wIndex = 0; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
		{// ���ҵ�λ��								
			if (wEpId == m_awSpeakerRec[wIndex])
			{
				break;
			}
		}
		
		if (UmsDiscuss_VmpEp_Max_Num == wIndex)
		{// ���ڼ�¼�У�����
			return;
		}
		wDelIndex = wIndex;
	//	m_awSpeakerRec[wDelIndex] = 0;	
		for (wIndex = wDelIndex + 1; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
		{
			m_awSpeakerRec[wIndex - 1] = m_awSpeakerRec[wIndex];
		}
		m_awSpeakerRec[UmsDiscuss_VmpEp_Max_Num - 1] = 0;
		return;
	}
}TDiscussSpeakerRec;

typedef struct tagTDiscussDstEpInfo
{
	u16                m_wAddIndex;   // ��һ�����滻�������
	TDiscussScreenInfo m_atScreenInfo[TP_MAX_STREAMNUM];

	tagTDiscussDstEpInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wAddIndex = MIDSCREENINDEX; // ���м俪ʼ
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atScreenInfo[wIndex].Clear();
		}
	}

	u16 GetIndexByEp(u16 wEpId, u16 wScreenIndex)
	{// ȷ��ĳ���᳡�����Ƿ�����Ŀ��Ĵ�ͼ�񣨼��費��Ҫ��ͼ��
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{			
			if (wEpId == m_atScreenInfo[wIndex].m_atMember[0].GetHandleOne()
				&& wScreenIndex == m_atScreenInfo[wIndex].m_atMember[0].GetHandleTwo())
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	u16 GetIndexByEp(u16 wEpId)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{			
			if (wEpId == m_atScreenInfo[wIndex].m_atMember[0].GetHandleOne())
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	u16 FindIdleScrIndex()
	{// �ҿ��е���
		s32 symbolflag = 1;
		u16 wCurIndex = 0;		
		for (u16 wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
		{// ���м䣬����ߣ����ұ�˳�����
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;			
			if (!m_atScreenInfo[wCurIndex].IsDstEpValid())
			{
				return wCurIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	u16 FindAddScrIndex()
	{// ���ҿ��е������Ҳ���������Ŀ���������᳡�������е������Ե�ʱ�򣬻��õ���
		u16 wIndex = FindIdleScrIndex();
		if (wIndex < TP_MAX_STREAMNUM)
		{
			return wIndex;
		}

		s32 symbolflag = 1;
		u16 wCurIndex = 0;		
		for (wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
		{// ���м䣬����ߣ����ұ�˳�����
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;			
			if (m_atScreenInfo[wCurIndex].IsDstEpThreeScr())
			{
				return wCurIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	BOOL32 IsDstEpVaild()
	{// ����������һ��Ŀ����Ч���򷵻�ture
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (m_atScreenInfo[wIndex].IsDstEpValid())
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	void AddDstEp(TCallNode* ptDstNode, u16 wDstSeatIndex, u16 wScreenIndex)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (m_atScreenInfo[wIndex].m_atMember[0].GetHandleOne() == ptDstNode->m_wEpID &&
				m_atScreenInfo[wIndex].m_atMember[0].GetHandleTwo() == wDstSeatIndex)
			{// �����ظ�
				return;
			}
		}

		m_atScreenInfo[wScreenIndex].AddDstEp(ptDstNode, wDstSeatIndex);
		return;
	}

	void AddVmpDstEp(TCallNode* ptDstNode, u16 wScreenIndex)
	{
		m_atScreenInfo[wScreenIndex].AddVmpDstEp(ptDstNode);
		return;
	}

	u16 FindThreeScreenDstEp()
	{// һ��Ŀ���У���ͼ�����ֻ��һ�������᳡
		u16 wEpId = TP_INVALID_INDEX;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (m_atScreenInfo[wIndex].IsDstEpThreeScr())
			{
				wEpId = m_atScreenInfo[wIndex].m_atMember[0].GetHandleOne();
				break;
			}
		}
		return wEpId;
	}

}TDiscussDstEpInfo;

typedef struct tagTDiscussInfo
{
	u16 m_wTotalScreenNum; //������
	
	u16                m_wSpecialEp;  // �������᳡A��Ϊ����b����ʱ��A�Ļ᳡ID, �˻᳡����ֱ�Ӵ���ͨ��������ͼ�񣨱����ܿ����Լ���;
	TDiscussDstEpInfo  m_tSpecialDst; // specialep��Ŀ��

	// �����������᳡��Ŀ��
	// �з��Ի᳡ʱ���·��Ի᳡Ŀ�겻�䣬����Ŀ��ʱ��������ȡ
	TDiscussScreenInfo m_atThreeScrBak[TP_MAX_STREAMNUM];
	TDiscussScreenInfo m_tSingleScrBak;

	TDiscussSpeakerRec m_tSpeakerRec; 	     // ���Ի᳡��¼
	TAuxMixList	       m_tDiscussEpFromUI;  // �������£�Ҳ�м�¼��������һ��
	TDiscussEpInfo     m_atDiscussEpInfo[TP_CONF_MAX_AUDMIXNUM]; 	// �������۵ĳ�Ա��Index��UI��ͬ
	
	u16                m_wChairEpId; // ��ϯ��������ʱ��Ϊ��ϯ��id������Ϊ��Чֵ

	tagTDiscussInfo()
	{
		Clear();
	}

	void Clear()
	{	
		ResetDiscussInfo();
		m_tDiscussEpFromUI.Clear();
		return;
	}

	void ResetDiscussInfo()
	{
		ResetSpecialEp();
		m_wTotalScreenNum = 0;
		m_tSingleScrBak.Clear();
		m_tSpeakerRec.Clear();
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atThreeScrBak[wIndex].Clear();
		}
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			m_atDiscussEpInfo[wIndex].Clear();
		}
		m_wChairEpId = TP_INVALID_INDEX;
		return;
	}

	void ResetSpecialEp()
	{
		m_wSpecialEp = 0;
		m_tSpecialDst.Clear();
	}

	void SetSpecialEp(u16 wEpId)
	{
		m_wSpecialEp = wEpId;
	}

	BOOL32 IsSpecialEpVaild()
	{
		return (0 != m_wSpecialEp);
	}

	BOOL32 CheckSpecialEp()
	{
		if (0 != m_wSpecialEp)
		{
			TDiscussEpInfo* ptEpInfo = FindEpById(m_wSpecialEp);
			if (NULL != ptEpInfo)
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	u16 FindIdleIndex()
	{
		u16 wIndex = 0;
		for (wIndex; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			if (!m_atDiscussEpInfo[wIndex].m_bUsed)
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	TDiscussEpInfo* FindEpById(const u16 wEpId)
	{
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			if (m_atDiscussEpInfo[wIndex].m_bUsed && wEpId == m_atDiscussEpInfo[wIndex].m_wEpID)
			{
				return &m_atDiscussEpInfo[wIndex];
			}
		}
		return NULL;
	}

	TDiscussEpInfo* AddEpID(TCallNode* ptNode, u16 wUIIndex = TP_INVALID_INDEX)
	{
		u16 wAddIndex = FindIdleIndex();
		if (wAddIndex < TP_CONF_MAX_AUDMIXNUM)
		{
			m_atDiscussEpInfo[wAddIndex].m_wEpID = ptNode->m_wEpID;
			m_atDiscussEpInfo[wAddIndex].m_wIndex = wAddIndex;
			m_atDiscussEpInfo[wAddIndex].m_bUsed = TRUE;

			return &m_atDiscussEpInfo[wAddIndex];
		}
		return NULL;
	}

	void DelEpById(u16 wEpId)
	{
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			if (m_atDiscussEpInfo[wIndex].m_bUsed && wEpId == m_atDiscussEpInfo[wIndex].m_wEpID)
			{
				m_wTotalScreenNum-=m_atDiscussEpInfo[wIndex].m_wStrceenNum;
				m_atDiscussEpInfo[wIndex].Clear();
			}
		}
		return;
	}

	void AddEpChanInfo(TCallNode* ptNode, u16 wIndex)
	{
		if (m_atDiscussEpInfo[wIndex].m_wEpID == ptNode->m_wEpID && ptNode->IsChanOn())
		{
			m_wTotalScreenNum+=ptNode->m_wVidSndNum;
			m_atDiscussEpInfo[wIndex].m_wStrceenNum = ptNode->m_wVidSndNum;  // �ն˵���Ƶ����ͨ��������Ϊ����
			m_atDiscussEpInfo[wIndex].m_bIsSmallChanOn = ptNode->IsSmallVidSnd();
			m_atDiscussEpInfo[wIndex].m_bMtAdjustRes = ptNode->IsCanAdjustRes(); // ��vrs��ģ��ƴ��ն�֧�ֽ��ֱ���
		}
		return;
	}

	void DelEpChanInfo(u16 wEpId)
	{
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			if (m_atDiscussEpInfo[wIndex].m_bUsed && wEpId == m_atDiscussEpInfo[wIndex].m_wEpID)
			{
				m_wTotalScreenNum-=m_atDiscussEpInfo[wIndex].m_wStrceenNum;
				m_atDiscussEpInfo[wIndex].Clear();
			}
		}
		return;
	}

	TDiscussEpInfo* GetFirstVaildEp(u16 wExceptEpId = TP_INVALID_INDEX)
	{// �������˳������
		TDiscussEpInfo* ptEpInfo = NULL;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			if (!TP_VALID_HANDLE(m_tDiscussEpFromUI.m_awList[wIndex]))
			{
				break;
			}

			if (wExceptEpId == m_tDiscussEpFromUI.m_awList[wIndex])
			{
				continue;
			}

			ptEpInfo = FindEpById(m_tDiscussEpFromUI.m_awList[wIndex]);
			if (NULL == ptEpInfo || !ptEpInfo->IsValid())
			{
				continue;
			}
			return ptEpInfo;
		}
		return NULL;
	}
	
}TDiscussInfo;

typedef struct tagTDiscussOprInfo
{
	u16 m_wEpID;  
	EmDisChnOprType m_emOprType;

	tagTDiscussOprInfo()
	{
		memset(this, 0, sizeof(tagTDiscussOprInfo));
	}

}TDiscussOprInfo;

typedef struct tagTDiscussVmpTpRes
{
	const CBaseService* m_pcVmpTpRes;
	CDsListInfo         m_cToVmpDsInfo;
	BOOL32              m_bIsVmpStart;
	tagTDiscussVmpTpRes()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussVmpTpRes));
	}

}TDiscussVmpTpRes;

typedef struct tagTDiscussMixRes
{
	TAudMixInfo*	    m_ptMixRes;
	CDsListInfo         m_cToMixDsInfo;
	
	tagTDiscussMixRes()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussMixRes));
	}

}TDiscussMixRes;

typedef struct tagTDiscussBasRes
{
	CScreenBasRes*      m_pcBasRes;
	CDsListInfo         m_cToBasDsInfo;
	
	tagTDiscussBasRes()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussBasRes));
	}

}TDiscussBasRes;

class CUmsConfInst;
class CDiscussObjectBase;
class CVmpServiceHandler;
class CBaseService;

/////////////////////////////////////////////////////////////////////
/////////////////////��������ģʽ������//////////////////////////////
/////////////////////////////////////////////////////////////////////

class CUmsDiscussMgr
{
public:
	CUmsDiscussMgr(CUmsConfInst* pcInst):m_pcConf(pcInst) {};
	~CUmsDiscussMgr();
	void Enter();
	void Exit();

protected:
	void Init();
	CUmsConfInst* Inst(){ return (CUmsConfInst*)m_pcConf; }

public:
	void Show();

	// ����Э��ջ��Ϣ
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	// ����umc��Ϣ
	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);

	void OpenEpDownAudCmd(CTpMsg *const ptMsg);
	void OpenEpDownAudAck(CTpMsg *const ptMsg);
	void CloseEpDownAudCmd(CTpMsg *const ptMsg);

	// ������ʱ����
	void InitDiscuss(TAuxMixList& tAuxMixList);
	void ReleaseDiscuss();

	// ���ߺ����ߴ���
	void OnChanConnect(TCallNode* ptNode);
	void OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason = EmCnsCallReason_success);

	// �з��Ի᳡
	void OnChangerSpeaker(TCallNode* ptSpeakerNode);
	void OnAdjustInnerSpeaker(TCallNode* ptNode);
	void UpdateMixDepthChanID(TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum);

	void   AdjustDualAudMedia();		// ˫������˫����������ͨ����Ŀ�����û�������
	BOOL32 AdjustGetVidFailed(u16 wGetIndex); // �ϼ��ص�getvid����

	BOOL32 IsDiscussModle(){ return m_bDiscussStaus;}// ������û�л᳡����ʱ����ֻ��һ���᳡����ʱ����ʹ�������ۿ��������ֵ��ȻΪfalse (�¼���ȡ�����ϼ�֪ͨ)
	BOOL32 IsUIDiscussOn(){return m_bUIDiscussStatus;}// �ϼ�ʹ�ã�������ͬ����һ������״̬
	BOOL32 IsUIVacOn(){return m_bUIVacOn;}// �ϼ�ʹ�ã�������ͬ����һ��������������״̬

	void GetDiscussStateInfo(TConfAuxMixInfo& tInfo);
	void GetDiscussObjInfo(TCapNode* ptNode, TTpObj& tObj, u16 wScreenIndex);

	u16    GetSpeacialEp(){return m_tDiscussInfo.m_wSpecialEp;}
	BOOL32 IsSpeacialEp(const u16 wEpId){ return (m_tDiscussInfo.IsSpecialEpVaild() && m_tDiscussInfo.m_wSpecialEp == wEpId);}

	TDiscussEpInfo* GetDiscussEpInfoById(const u16 wEpId){ return m_tDiscussInfo.FindEpById(wEpId);}
	TDiscussEpInfo* GetDiscussEpInfoByIndex(u16 wIndex){ return &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];}

	void VmpCB(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wMemberIndx);
	void VmpCBForSingle(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wMemberIndx);
#ifdef _USE_XMPUEQP_
    void XmpuBasCB(u32 dwType, CScreenBasRes* ptBasRes, void *pData);
	void XmpuBasCBForSingle(u32 dwType, CScreenBasRes* ptBasRes, void *pData);
	void XmpuMixCB( u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData );
	void XmpuMixCBForSingle( u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData );
#else
	void BasCB(CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes);
	void BasCBForSingle(CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes);
	void MixCB(TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo);
	void MixCBForSingle(TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo);
#endif
	void GetDiscussEpSmallVidAddr(u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr);
	void GetDiscussEpVidAddr(u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr);
	void GetDiscussEpAudAddr(u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr);

	void GetObjVmpOutAddr(EmDiscussModleObj emType, u16 wScreenIndex, TServiceAddr& tAddr);
	void GetObjMixOutAddr(EmDiscussModleObj emType, u16 wScreenindex, u16 wEpId, BOOL32 bToVirSpeaker, TServiceAddr& tAddr, BOOL32 bFromPutAud = FALSE);

	void GetMixOutAddrForDown(TCapNode* ptNode, u16 wScreenIndex, TServiceAddr& tAddr);

	// �ؼ�֡����
	void   AskKeyFrameFromEp(TCapNode* ptNode, u16 wScreenIndex, BOOL32 bReqBySys );
	void   AskKeyFrameFromBas(u16 wScreenIndex);
    void   AskKeyFrameForConfBrdUser(u16 wScreenIndex);

	void   SetDelayStat(u8 byStat){m_byDelayStat = byStat;}
	void   FreeDsForNewAndOldSpeaker(u16 wNewSpeaker, u16 wOldSpeaker);
	BOOL32 IsNeedDelay(u16 wEpId);


	// Ϊѡ���Ļ᳡�ָ��ֱ���
	BOOL32   RestoreAdjustedResForSelEp(u16 wSelTargetEp, u16 wScreenIndex);
	// ѡ������������Ҫ��ͼ��ĵ����ۻ᳡ ���ֱ���
    BOOL32   AdjustResForUnSelEp(u16 wSelTargetEp, u16 wScreenIndex);	


protected:
	// cnc��Ϣ
	void OnDiscussStatusCmd(CTpMsg *const ptMsg); // �������ۺ͹ر����ۣ��Լ��������£����������б�
	EmDiscussRspRet OnDiscussStatusCmdFromUmc(CTpMsg* const ptMsg);
	void DiscussStatusCmdFromUmcCnc(TConfAuxMixInfo& tAudMix, EmUIType emType);

	void OnDiscussListOprCmd(CTpMsg *const ptMsg); // �����У����Ӻ�ɾ���᳡
	void OnDiscussListOprFromUmc(CTpMsg* const ptMsg);
	void DiscussListOprFormUmcCnc(TDiscussListOpr& tDisList, EmUIType emType);

	void OnDiscussMixVacOprCmd( CTpMsg *const ptMsg );
	void OnDiscussMixVacOprCmdFromUmc( CTpMsg *const ptMsg );
	void DiscussMixVacOprFormUmcCnc(TConfAuxMixVacOpr& tVacOpr);

	void OnCasecadeDiscussNtfy(CTpMsg *const ptMsg);
	void OnAskKeyFrameFromDown(CTpMsg *const ptMsg);

	// ��ʼ��ֹͣ����ģʽ
	BOOL32 StartDiscussModle(EmUIType emType);
	void   StopDiscussModle(BOOL32 bVmpError = FALSE, BOOL32 bMixError = FALSE);
	BOOL32 UpdateDiscussModle(EmUIType emType);

	// ��ӻ᳡��ɾ���᳡
	EmDiscussOprRes AddEpInListFormUI(u16 wEpId);
	EmDiscussOprRes AddEpInDiscussChan(TDiscussEpInfo* ptEpInfo);
	void            DelEpInDiscussChan(TDiscussEpInfo* ptEpInfo);	
	void            RemoveEpFromDiscussChan(TDiscussEpInfo* ptEpInfo); // 

	void   AdjustDiscussStatus(EmDisChnOprType emType, u16 wOprEpId = TP_INVALID_INDEX);
	void   AdjustAllNodeToDiscuss(BOOL32 bAdjust);
	BOOL32 AdjustAudMixVacStatus(BOOL32 bVacOn);

	void UptateDiscussListFromUI(TAuxMixList& tAuxDisList);  // ���ݽ����list, ���½��洫�������������Ա
	void UptateDiscussEpInfo();   // ���ݽ����list, �������ۻ᳡��Ϣ
	void UptateDiscussObjInfo();  // 
	void MakeCasecadeObjNtfy(TCapNode* ptUmsNode, TDiscussCasecadeNtfy& tNtfy);

	// ������Դ����
	EmDiscussRspRet AssignResource(); 
	void   ResetDiscussInfo(); // �ͷ����������Դ

	// ֪ͨ����״̬
	void DiscussInfoNotify();

	// û��С�������ն�, �����Ҫͬʱ�����С������ϳ�, ��̬����bas
	//void   AdjustBasForDiscussEp(TDiscussEpInfo* ptEpInfo);
	void   AdjustBasForDiscussEpBakMethod(TDiscussEpInfo* ptEpInfo);
	void   ReleaseBasForDiscussEp(TDiscussEpInfo* ptEpInfo);
	BOOL32 IsNeedBasForDiscussEp(u16 wEpId , u16 wScreenIndex);  // 
	

	void   AskKeyFrameToVmp(EmDiscussModleObj emType, u16 wScreenIndex);
	void   AskKeyFrameToVmpByNode(TCapNode* ptFatherNode, TCallNode* ptNode, u16 wScreenIndex, BOOL32 bReqBySys);
	BOOL32 FindDiscussObjTypebyVmpRes(u16 wResId, TPOUT EmDiscussModleObj& emType, TPOUT u16& wScreenIndex);
	BOOL32 FindDiscussObjTypebyMixRes(u16 wResId, TPOUT EmDiscussModleObj& emType, TPOUT u16& wScreenIndex);
	
	const CBaseService* GetObjVmpRes(EmDiscussModleObj emType, u16 wScreenIndex);
	TAudMixInfo*        GetObjMixRes(EmDiscussModleObj emType, u16 wScreenIndex);
public:
	BOOL32	IsMaxVmpSameEp();

private:
	CUmsConfInst*        m_pcConf; 
	CDiscussObjectBase*  m_apcDisObj[emDiscussObjEnd];
//	CPutAud*             m_pcPutAud;

	BOOL32               m_bUIVacOn;   //  �ϼ�ʹ�ã�������ͬ����һ����������״̬
	BOOL32               m_bUIDiscussStatus;  // �ϼ�ʹ�ã�������ͬ����һ������״̬
	BOOL32               m_bDiscussStaus;  // ������û�л᳡����ʱ����ֻ��һ���᳡����ʱ����ʹ�������ۿ��������ֵ��ȻΪfalse (�¼���ȡ�����ϼ�֪ͨ)

	TDiscussObjInfo      m_atDiscussObj[emDiscussObjEnd];  // ���ﱣ��һ������Ŀ�꣬��Ҫ����֪ͨ
	TDiscussInfo         m_tDiscussInfo;  // �������

	TDiscussEpAudInfo    m_tEpAudInfo;  // �¼��õ����ϼ�֪ͨ�����ģ������������л᳡�Ƿ���Ҫ��nģʽ���ϼ�����֪ͨ����ʱ������֪ͨ��ĳ��ums�����

	u8                    m_byDelayStat;  // �ϼ������������з����˵�ƽ��
	u16                   m_wNewSpeaker;
	u16                   m_wOldSpeaker;
};

/////////////////////////////////////////////////////////////////////
/////////////////////////����Ŀ�������//////////////////////////////
/////////////////////////////////////////////////////////////////////

class CDiscussObjectBase
{
public:
	CDiscussObjectBase(CUmsConfInst* pcInst, EmDiscussModleObj emDisObj):m_pcConf(pcInst), m_emDisObj(emDisObj) {Init();}
	~CDiscussObjectBase() {}

	virtual void Init();
	virtual void Show();

	virtual EmDiscussRspRet    AssignResource(CUmsConfInst* param);
	virtual void               FreeResource();
	virtual void               ShowResourse();

	virtual const CBaseService* GetVmpRes(u16 wScreenIndex);
	virtual TAudMixInfo*        GetMixRes(u16 wScreenIndex);

	virtual void AdjustDstEpInfo(TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo, u16 wSpeakerId); // ��������Ŀ��
	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId) = 0; // ������vmp�Ľ���	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId) = 0; // ������mix�Ľ���
	virtual void AdjustApu2MixForceActiveInfo(u16 wSpeakerId, BOOL32 bForceActiveOn);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo) = 0; // ˢ�µ�vmp�Ľ�����Ŀ�겻��
	virtual void UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex) = 0;

	// ����Ŀ����Ҫע�⣬�������ǵ�����ʱ�򣬷�����Ŀ�����ߵ�vmp���ܱ�֮ǰ��һ���������Ի᳡������᳡��ռ�ã����Ŀ�����TDiscussInfo��
	virtual void   GetVmpMemberEpByIndex(u16 wScreenIndex, u16 wMemberIndx, TPOUT u16& wEpId, TPOUT u16& wSeatIndex);
	virtual BOOL32 IsDiscussObjDstEp(u16 wEpId, u16 wScreenIndex);// ĳ���᳡�������Ƿ���������Ŀ��Ĵ�ͼ��	
	virtual TDiscussDstEpInfo* GetDiscussObj();

protected:
	virtual void InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0;  // ��ʼ״̬
	virtual void UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0;  // ���Ի᳡�л� 	
	virtual void UptateDstEpInfoByChangeSeat(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo) = 0; // �л�
	virtual void UptateDstEpInfoByAdd(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0; // ���
	virtual void UptateDstEpInfoByDel(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0; // ɾ��

	// some method
	virtual void FillUpSingleScrEp(TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo, TDiscussDstEpInfo* ptDstEpTemp = NULL);
	virtual void FillUpThreeScrEp(TDiscussDstEpInfo* ptDstEpInfo);
	virtual void CheckOutDstInfo(TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo);
	virtual void AdjustDstForSpecialEp(u16 wAddIndex, TCallNode* ptNode, TDiscussInfo* ptDiscussInfo);

	// Сͼ��
	virtual void AdjustVmpEpInfoForThreeScreen(TDiscussInfo* ptDiscussInfo);
	virtual void AdjustVmpEpInfoForSingleScreen(TDiscussInfo* ptDiscussInfo);
	// �ϳɲ�������
	virtual void GetVmpEncParam(TVmpEncParam& tEncParam, TCallNode* ptNode, BOOL32 bSnd);
	virtual void GetVmpStyleInfo(TVmpStyleInfo& tVmpStylle, TDiscussScreenInfo* ptInfo, BOOL32 bUseSmallSenvenStyle);
	// ������Ա����
	virtual void GetNewMixMember(TAudMixMemberInfo& tNewMixMember, TDiscussDstEpInfo* tScreenInfo, u16 wScreenIndex, u16 wThreeScreenEp);

protected:
	CUmsConfInst*	      m_pcConf;
	EmDiscussModleObj     m_emDisObj;

	TDiscussVmpTpRes      m_atVmpTp[TP_MAX_STREAMNUM]; 
	TDiscussMixRes        m_atMix[TP_MAX_STREAMNUM];

	// Ŀ��
	TDiscussDstEpInfo     m_tDstEpInfo;
};

class CDiscussObjectForSpeakerEp : public CDiscussObjectBase
{
public:
	CDiscussObjectForSpeakerEp(CUmsConfInst* pcConf):CDiscussObjectBase(pcConf, emDiscussObjForSpeakerEp) {}
	~CDiscussObjectForSpeakerEp() {}

	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId); // ������vmp�Ľ���	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo); // ˢ�µ�vmp�Ľ�����Ŀ�겻��
	virtual void UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex);

	virtual void InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSeat(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo);
	virtual void UptateDstEpInfoByAdd(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByDel(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
};

class CDiscussObjectForThreeScreenEp : public CDiscussObjectBase
{
public:
	CDiscussObjectForThreeScreenEp(CUmsConfInst* pcConf):CDiscussObjectBase(pcConf, emDiscussObjForThreeScrEp) {}
	~CDiscussObjectForThreeScreenEp() {}

	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId); // ������vmp�Ľ���	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo); // ˢ�µ�vmp�Ľ�����Ŀ�겻��
	virtual void UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex);

	virtual void InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSeat(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo){}
	virtual void UptateDstEpInfoByAdd(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByDel(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
};

class CDiscussObjectForSingleScreenEp : public CDiscussObjectBase
{
public:
	CDiscussObjectForSingleScreenEp(CUmsConfInst* pcConf):CDiscussObjectBase(pcConf, emDiscussObjForSingleScrEp) {}
	~CDiscussObjectForSingleScreenEp() {}

	virtual EmDiscussRspRet    AssignResource(CUmsConfInst* param);
	virtual void               FreeResource();
	virtual void               ShowResourse();

	virtual const CBaseService* GetVmpRes(u16 wScreenIndex);
	virtual TAudMixInfo*        GetMixRes(u16 wScreenIndex);

	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId); // ������vmp�Ľ���	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId);
	virtual void AdjustApu2MixForceActiveInfo(u16 wSpeakerId, BOOL32 bForceActiveOn);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo); // ˢ�µ�vmp�Ľ�����Ŀ�겻��
	virtual void UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex);

	virtual void InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSeat(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo);
	virtual void UptateDstEpInfoByAdd(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByDel(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
};

#endif // umsdiscussnew.h