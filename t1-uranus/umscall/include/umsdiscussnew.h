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

// 讨论会场信息
typedef struct tagTDiscussEpInfo
{
	u16     m_wIndex;  // 在m_atDiscussEpInfo[TP_CONF_MAX_AUDMIXNUM]中的索引，固定
	u16     m_wEpID;   	
	u16     m_wStrceenNum;    // 屏数 

	BOOL32  m_bUsed;
	BOOL32  m_bIsSmallChanOn;
	BOOL32  m_bMtAdjustRes;   // 该会场是否支持降分辨率

	EmTpVideoResolution m_aemVideoRes[TP_MAX_STREAMNUM];  // 保存一下降的分辨率格式，用于恢复
	CScreenBasRes*      m_apcBas[TP_MAX_STREAMNUM];
	TDisVidBasUserInfo   m_awBasUserinfo[TP_MAX_STREAMNUM];

	CDsListInfo         m_cToBasDsInfo; // 无小码流的会场，到适配的交换；进合成小图像的码流从适配取，进合成的大图像码流，需要重新升回来

	TTPMediaTransAddr   m_atPutAuddr[TP_MAX_STREAMNUM]; // 此讨论成员在下级中会用到；1. 上级将该会场需要的音频地址打到这里；2. 下级取这里的音频给node    
	CDsListInfo         m_cToPutAuddrDsInfo;

	TGetVidAddr			m_tGetAddr;   // 讨论成员上调码流地址
	u16                 m_awGetIndex[TP_MAX_STREAMNUM];  // 上调码流的index，释放的时候会用到

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

// 每个屏目标描述
typedef struct tagTDiscussScreenInfo
{
	u16      m_wVmpEpNum;   // 小画面路数
	BOOL32   m_bThreeScr;   // 所看目标是否是三屏
	TTPAlias m_tAlias;      // 屏显示的名称，第0路大图像的会场名;

	// 合成参数
	TVmpMemberInfo	m_atMember[UMS_VMP_MAX_RCV];  // 这里的dwhandle储存的是进合成的wEpId和wSeatIndex
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
	{// 第0路是大图像
		m_bThreeScr = FALSE;
		m_tAlias.Clear();
		m_atMember[0].Clear();
		m_atPayload[0].Clear();
	}

	void ClearVmpEpInfo()
	{//第1路到第9路是小图像
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
			// 合成参数
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
	{// 对同一个屏，如果之前已经添加，直接返回
		if (IsEpInScreen(ptDstNode->m_wEpID, 1))
		{
			return;
		}
		
		if (UmsDiscuss_VmpEp_Max_Num < m_wVmpEpNum + ptDstNode->m_wVidSndNum)
		{// 空位置不够，直接返回
			return;
		}
		
		u16 wAddIndex = m_wVmpEpNum + 1; // 小图像合成成员从第1路开始
		if (ptDstNode->IsThreeVidSnd())
		{
			for (u16 wLoop = 0; wLoop  < TP_MAX_STREAMNUM; wLoop++)
			{// 合成参数
				m_atMember[wAddIndex].m_bMerged = (2 != wLoop)?TRUE:FALSE;
				m_atMember[wAddIndex].MakeHandle(ptDstNode->m_wEpID, wLoop);
				m_atPayload[wAddIndex].m_byActivePayload = ptDstNode->m_tVidSndFormat.m_wDynamicPayload;
				m_atPayload[wAddIndex].m_byRealPayload = ptDstNode->m_tVidSndFormat.m_wStaticPayload;
				m_wVmpEpNum++;
				wAddIndex++;
			}
		}
		else
		{// 合成参数
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
					return TRUE; // 说明此会场是个三屏，连续三个小图像是同一个
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
	{// 添加一个新记录，放在第一个位置，如果之前存在，也挪到第一个位置
		if (wEpId == m_awSpeakerRec[0])
		{
			return;
		}
		
		u16 wIndex = 0;
		u16 wReplaceIndex = 0;
		for (wIndex = 1; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
		{// 先确定是否存在					
			if (wEpId == m_awSpeakerRec[wIndex])
			{
				break;
			}
		}
		
		if (UmsDiscuss_VmpEp_Max_Num == wIndex)
		{// 不存在
			wIndex--;
		}		
		wReplaceIndex = wIndex;		
		
		for (wIndex = wReplaceIndex - 1; wIndex > 0; wIndex--)
		{// 再逐次挪动位置
			m_awSpeakerRec[wIndex + 1] = m_awSpeakerRec[wIndex];
		}	
		m_awSpeakerRec[wIndex + 1] = m_awSpeakerRec[wIndex];	
		m_awSpeakerRec[0] = wEpId;
	}
	
	void DelRec(u16 wEpId)
	{// 删除一个记录
		u16 wIndex = 0;
		u16 wDelIndex = 0;
		
		for (wIndex = 0; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
		{// 先找到位置								
			if (wEpId == m_awSpeakerRec[wIndex])
			{
				break;
			}
		}
		
		if (UmsDiscuss_VmpEp_Max_Num == wIndex)
		{// 不在记录中，返回
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
	u16                m_wAddIndex;   // 下一个可替换的屏序号
	TDiscussScreenInfo m_atScreenInfo[TP_MAX_STREAMNUM];

	tagTDiscussDstEpInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wAddIndex = MIDSCREENINDEX; // 从中间开始
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atScreenInfo[wIndex].Clear();
		}
	}

	u16 GetIndexByEp(u16 wEpId, u16 wScreenIndex)
	{// 确定某个会场的屏是否属于目标的大图像（即需不需要大图像）
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
	{// 找空闲的屏
		s32 symbolflag = 1;
		u16 wCurIndex = 0;		
		for (u16 wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
		{// 先中间，再左边，后右边顺序查找
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;			
			if (!m_atScreenInfo[wCurIndex].IsDstEpValid())
			{
				return wCurIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	u16 FindAddScrIndex()
	{// 先找空闲的屏，找不到，再找目标是三屏会场的屏（切单屏发言的时候，会用到）
		u16 wIndex = FindIdleScrIndex();
		if (wIndex < TP_MAX_STREAMNUM)
		{
			return wIndex;
		}

		s32 symbolflag = 1;
		u16 wCurIndex = 0;		
		for (wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
		{// 先中间，再左边，后右边顺序查找
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;			
			if (m_atScreenInfo[wCurIndex].IsDstEpThreeScr())
			{
				return wCurIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	BOOL32 IsDstEpVaild()
	{// 三个屏中有一个目标有效，则返回ture
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
			{// 避免重复
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
	{// 一份目标中，大图像最多只有一个三屏会场
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
	u16 m_wTotalScreenNum; //总屏数
	
	u16                m_wSpecialEp;  // 在三屏会场A切为单屏b发言时，A的会场ID, 此会场不能直接从普通三屏中收图像（避免能看到自己）;
	TDiscussDstEpInfo  m_tSpecialDst; // specialep的目标

	// 单屏和三屏会场的目标
	// 切发言会场时，新发言会场目标不变，计算目标时，从这里取
	TDiscussScreenInfo m_atThreeScrBak[TP_MAX_STREAMNUM];
	TDiscussScreenInfo m_tSingleScrBak;

	TDiscussSpeakerRec m_tSpeakerRec; 	     // 发言会场记录
	TAuxMixList	       m_tDiscussEpFromUI;  // 非讨论下，也有记录，跟界面一致
	TDiscussEpInfo     m_atDiscussEpInfo[TP_CONF_MAX_AUDMIXNUM]; 	// 进入讨论的成员，Index与UI不同
	
	u16                m_wChairEpId; // 主席在讨论中时，为主席的id，否则为无效值

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
			m_atDiscussEpInfo[wIndex].m_wStrceenNum = ptNode->m_wVidSndNum;  // 终端的视频发送通道数，即为屏数
			m_atDiscussEpInfo[wIndex].m_bIsSmallChanOn = ptNode->IsSmallVidSnd();
			m_atDiscussEpInfo[wIndex].m_bMtAdjustRes = ptNode->IsCanAdjustRes(); // 除vrs外的，科达终端支持降分辨率
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
	{// 按界面的顺序来找
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
/////////////////////会议讨论模式管理类//////////////////////////////
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

	// 处理协议栈消息
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	// 处理umc消息
	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);

	void OpenEpDownAudCmd(CTpMsg *const ptMsg);
	void OpenEpDownAudAck(CTpMsg *const ptMsg);
	void CloseEpDownAudCmd(CTpMsg *const ptMsg);

	// 开会结会时调用
	void InitDiscuss(TAuxMixList& tAuxMixList);
	void ReleaseDiscuss();

	// 上线和下线处理
	void OnChanConnect(TCallNode* ptNode);
	void OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason = EmCnsCallReason_success);

	// 切发言会场
	void OnChangerSpeaker(TCallNode* ptSpeakerNode);
	void OnAdjustInnerSpeaker(TCallNode* ptNode);
	void UpdateMixDepthChanID(TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum);

	void   AdjustDualAudMedia();		// 双流处理（双流声音进普通单屏目标所用混音器）
	BOOL32 AdjustGetVidFailed(u16 wGetIndex); // 上级回调getvid处理

	BOOL32 IsDiscussModle(){ return m_bDiscussStaus;}// 讨论中没有会场在线时或者只有一个会场在线时，即使界面讨论开启，这个值依然为false (下级，取决于上级通知)
	BOOL32 IsUIDiscussOn(){return m_bUIDiscussStatus;}// 上级使用：跟界面同步的一个讨论状态
	BOOL32 IsUIVacOn(){return m_bUIVacOn;}// 上级使用：跟界面同步的一个语音激励开关状态

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

	// 关键帧处理
	void   AskKeyFrameFromEp(TCapNode* ptNode, u16 wScreenIndex, BOOL32 bReqBySys );
	void   AskKeyFrameFromBas(u16 wScreenIndex);
    void   AskKeyFrameForConfBrdUser(u16 wScreenIndex);

	void   SetDelayStat(u8 byStat){m_byDelayStat = byStat;}
	void   FreeDsForNewAndOldSpeaker(u16 wNewSpeaker, u16 wOldSpeaker);
	BOOL32 IsNeedDelay(u16 wEpId);


	// 为选看的会场恢复分辨率
	BOOL32   RestoreAdjustedResForSelEp(u16 wSelTargetEp, u16 wScreenIndex);
	// 选看结束，不需要大图像的的讨论会场 降分辨率
    BOOL32   AdjustResForUnSelEp(u16 wSelTargetEp, u16 wScreenIndex);	


protected:
	// cnc消息
	void OnDiscussStatusCmd(CTpMsg *const ptMsg); // 开启讨论和关闭讨论，以及非讨论下，更新讨论列表
	EmDiscussRspRet OnDiscussStatusCmdFromUmc(CTpMsg* const ptMsg);
	void DiscussStatusCmdFromUmcCnc(TConfAuxMixInfo& tAudMix, EmUIType emType);

	void OnDiscussListOprCmd(CTpMsg *const ptMsg); // 讨论中，增加和删除会场
	void OnDiscussListOprFromUmc(CTpMsg* const ptMsg);
	void DiscussListOprFormUmcCnc(TDiscussListOpr& tDisList, EmUIType emType);

	void OnDiscussMixVacOprCmd( CTpMsg *const ptMsg );
	void OnDiscussMixVacOprCmdFromUmc( CTpMsg *const ptMsg );
	void DiscussMixVacOprFormUmcCnc(TConfAuxMixVacOpr& tVacOpr);

	void OnCasecadeDiscussNtfy(CTpMsg *const ptMsg);
	void OnAskKeyFrameFromDown(CTpMsg *const ptMsg);

	// 开始和停止讨论模式
	BOOL32 StartDiscussModle(EmUIType emType);
	void   StopDiscussModle(BOOL32 bVmpError = FALSE, BOOL32 bMixError = FALSE);
	BOOL32 UpdateDiscussModle(EmUIType emType);

	// 添加会场和删除会场
	EmDiscussOprRes AddEpInListFormUI(u16 wEpId);
	EmDiscussOprRes AddEpInDiscussChan(TDiscussEpInfo* ptEpInfo);
	void            DelEpInDiscussChan(TDiscussEpInfo* ptEpInfo);	
	void            RemoveEpFromDiscussChan(TDiscussEpInfo* ptEpInfo); // 

	void   AdjustDiscussStatus(EmDisChnOprType emType, u16 wOprEpId = TP_INVALID_INDEX);
	void   AdjustAllNodeToDiscuss(BOOL32 bAdjust);
	BOOL32 AdjustAudMixVacStatus(BOOL32 bVacOn);

	void UptateDiscussListFromUI(TAuxMixList& tAuxDisList);  // 根据界面的list, 更新界面传过来的讨论组成员
	void UptateDiscussEpInfo();   // 根据界面的list, 更新讨论会场信息
	void UptateDiscussObjInfo();  // 
	void MakeCasecadeObjNtfy(TCapNode* ptUmsNode, TDiscussCasecadeNtfy& tNtfy);

	// 讨论资源分配
	EmDiscussRspRet AssignResource(); 
	void   ResetDiscussInfo(); // 释放讨论相关资源

	// 通知讨论状态
	void DiscussInfoNotify();

	// 没有小码流的终端, 如果需要同时大画面和小画面进合成, 动态申请bas
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

	BOOL32               m_bUIVacOn;   //  上级使用：跟界面同步的一个语音开关状态
	BOOL32               m_bUIDiscussStatus;  // 上级使用：跟界面同步的一个讨论状态
	BOOL32               m_bDiscussStaus;  // 讨论中没有会场在线时或者只有一个会场在线时，即使界面讨论开启，这个值依然为false (下级，取决于上级通知)

	TDiscussObjInfo      m_atDiscussObj[emDiscussObjEnd];  // 这里保存一份讨论目标，主要用于通知
	TDiscussInfo         m_tDiscussInfo;  // 讨论相关

	TDiscussEpAudInfo    m_tEpAudInfo;  // 下级用到，上级通知下来的，本级在讨论中会场是否需要听n模式；上级当做通知的临时变量，通知完某个ums后清空

	u8                    m_byDelayStat;  // 上级用于讨论内切发言人的平滑
	u16                   m_wNewSpeaker;
	u16                   m_wOldSpeaker;
};

/////////////////////////////////////////////////////////////////////
/////////////////////////讨论目标操作类//////////////////////////////
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

	virtual void AdjustDstEpInfo(TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo, u16 wSpeakerId); // 调整讨论目标
	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId) = 0; // 调整到vmp的交换	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId) = 0; // 调整到mix的交换
	virtual void AdjustApu2MixForceActiveInfo(u16 wSpeakerId, BOOL32 bForceActiveOn);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo) = 0; // 刷新到vmp的交换，目标不变
	virtual void UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex) = 0;

	// 处理目标需要注意，发言人是单屏的时候，发言人目标两边的vmp可能被之前的一个三屏发言会场（特殊会场）占用，这个目标存在TDiscussInfo中
	virtual void   GetVmpMemberEpByIndex(u16 wScreenIndex, u16 wMemberIndx, TPOUT u16& wEpId, TPOUT u16& wSeatIndex);
	virtual BOOL32 IsDiscussObjDstEp(u16 wEpId, u16 wScreenIndex);// 某个会场的屏，是否属于讨论目标的大图像	
	virtual TDiscussDstEpInfo* GetDiscussObj();

protected:
	virtual void InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0;  // 初始状态
	virtual void UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0;  // 发言会场切换 	
	virtual void UptateDstEpInfoByChangeSeat(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo) = 0; // 切换
	virtual void UptateDstEpInfoByAdd(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0; // 添加
	virtual void UptateDstEpInfoByDel(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo) = 0; // 删除

	// some method
	virtual void FillUpSingleScrEp(TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo, TDiscussDstEpInfo* ptDstEpTemp = NULL);
	virtual void FillUpThreeScrEp(TDiscussDstEpInfo* ptDstEpInfo);
	virtual void CheckOutDstInfo(TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo);
	virtual void AdjustDstForSpecialEp(u16 wAddIndex, TCallNode* ptNode, TDiscussInfo* ptDiscussInfo);

	// 小图像
	virtual void AdjustVmpEpInfoForThreeScreen(TDiscussInfo* ptDiscussInfo);
	virtual void AdjustVmpEpInfoForSingleScreen(TDiscussInfo* ptDiscussInfo);
	// 合成参数处理
	virtual void GetVmpEncParam(TVmpEncParam& tEncParam, TCallNode* ptNode, BOOL32 bSnd);
	virtual void GetVmpStyleInfo(TVmpStyleInfo& tVmpStylle, TDiscussScreenInfo* ptInfo, BOOL32 bUseSmallSenvenStyle);
	// 混音成员处理
	virtual void GetNewMixMember(TAudMixMemberInfo& tNewMixMember, TDiscussDstEpInfo* tScreenInfo, u16 wScreenIndex, u16 wThreeScreenEp);

protected:
	CUmsConfInst*	      m_pcConf;
	EmDiscussModleObj     m_emDisObj;

	TDiscussVmpTpRes      m_atVmpTp[TP_MAX_STREAMNUM]; 
	TDiscussMixRes        m_atMix[TP_MAX_STREAMNUM];

	// 目标
	TDiscussDstEpInfo     m_tDstEpInfo;
};

class CDiscussObjectForSpeakerEp : public CDiscussObjectBase
{
public:
	CDiscussObjectForSpeakerEp(CUmsConfInst* pcConf):CDiscussObjectBase(pcConf, emDiscussObjForSpeakerEp) {}
	~CDiscussObjectForSpeakerEp() {}

	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId); // 调整到vmp的交换	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo); // 刷新到vmp的交换，目标不变
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

	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId); // 调整到vmp的交换	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo); // 刷新到vmp的交换，目标不变
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

	virtual void AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId); // 调整到vmp的交换	
	virtual void AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId);
	virtual void AdjustApu2MixForceActiveInfo(u16 wSpeakerId, BOOL32 bForceActiveOn);

	virtual void UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo); // 刷新到vmp的交换，目标不变
	virtual void UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex);

	virtual void InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByChangeSeat(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo);
	virtual void UptateDstEpInfoByAdd(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
	virtual void UptateDstEpInfoByDel(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo);
};

#endif // umsdiscussnew.h