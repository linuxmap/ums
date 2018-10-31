#ifndef _h_mpdata_h__
#define _h_mpdata_h__
#include "mpstruct.h"
#include "dataswitch.h"

#ifdef WIN32
#pragma warning(disable : 4786) 
#endif
#include <list>

typedef struct tagTSwitchRulesInfo
{
	DSRTPSID					m_dLocalID; // ds库本地监听所分配的id，根据srcaddr唯一确定
	TTPTransAddr				m_tSrcAddr;
	std::list<TUmsDsData>		m_lSndList;
	
	tagTSwitchRulesInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_dLocalID = INVALID_RTPSWITCHID;
		m_tSrcAddr.Clear();
		m_lSndList.clear();
	}

	tagTSwitchRulesInfo& operator = (const tagTSwitchRulesInfo& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dLocalID = tRhs.m_dLocalID;
		this->m_tSrcAddr = tRhs.m_tSrcAddr;
		this->m_lSndList = tRhs.m_lSndList;
		return *this;
	}

	BOOL32 operator == (tagTSwitchRulesInfo& tRsData)
	{
		return (tRsData.m_tSrcAddr == tRsData.m_tSrcAddr);
	}

	BOOL32 operator < (tagTSwitchRulesInfo& tRsData)
	{
		if (m_tSrcAddr.m_dwIP > tRsData.m_tSrcAddr.m_dwIP)
		{
			return FALSE;
		}
		else if (m_tSrcAddr.m_dwIP == tRsData.m_tSrcAddr.m_dwIP)
		{
			if (m_tSrcAddr.m_wPort > tRsData.m_tSrcAddr.m_wPort)
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	BOOL32 operator > (tagTSwitchRulesInfo& tRsData)
	{
		if (m_tSrcAddr.m_dwIP < tRsData.m_tSrcAddr.m_dwIP)
		{
			return FALSE;
		}
		else if (m_tSrcAddr.m_dwIP == tRsData.m_tSrcAddr.m_dwIP)
		{
			if (m_tSrcAddr.m_wPort < tRsData.m_tSrcAddr.m_wPort)
			{
				return FALSE;
			}
		}
		return TRUE;
	}

}TSwitchRulesInfo;

#define CSwitchRulesBuf CTpListBuff<TSwitchRulesInfo>
#define CSwitchRulesBufItor CTpListBuff<TSwitchRulesInfo>::VectorDataPtr

class CConfSwitchRulesInfo
{
public:
	CConfSwitchRulesInfo(u32 dwMaxListNum);
	~CConfSwitchRulesInfo();

	BOOL32 Insert(const DSID idMediaDsID, const TUmsDsData tUmsDsData, DSRTPSID& dLocalId);

	BOOL32 DelNode(TUmsDsData* ptDs, DSRTPSID& dLocalId);

	void FreeALL();

	u32	GetListNum()			{ return m_dwListNum; }
	u32	GetMaxListNum()			{ return m_dwMaxListNum; }
	u32 GetDsNum()			{ return m_dwDsNum;}
	CSwitchRulesBufItor GetHead()	{	return m_pHead; }

	u32 GetListBufTotalNum(){return m_tSwitchRulesList.GetTotalNum();}
	u32 GetListBufMinFreeNum(){return m_tSwitchRulesList.GetMinFreeBlocks();}
	u32 GetListBufFreeNum(){return m_tSwitchRulesList.GetFreeBlocks();}
	
protected:
	BOOL32 DelMemberFromSndList(std::list<TUmsDsData>& tList, TUmsDsData* ptDs);

private:
	CConfSwitchRulesInfo& operator = (const CConfSwitchRulesInfo& tRsData);
	CConfSwitchRulesInfo(const CConfSwitchRulesInfo&);
private:    
	CSwitchRulesBufItor		m_pHead;
	u32						m_dwListNum;
	u32						m_dwMaxListNum;
	u32						m_dwDsNum;
	CSwitchRulesBuf			m_tSwitchRulesList;
};

class CMpData
{
public:
    CMpData();
    virtual ~CMpData();

public:
    BOOL32 Init(u32 dwSwitchNum, u16 wIframePortNum);
	BOOL32 Quit(DSID idMediaDsID);

	BOOL32 AddSwitch(DSID idMediaDsID, u16 wConfID, TUmsDsData* ptDs, DSRTPSID& dLocalId);
	BOOL32 DelSwitch(u16 wConfID, TUmsDsData* ptDs, DSRTPSID& dLocalId);

	void   ClearConfSwitch(u16 wConfID, DSID dwMediaID);
	
public:
	void ShowSwitch(DSID dwMediaID, u8 byPrintType  = 0);

private:

	CConfSwitchRulesInfo* m_aptSwitchRulesInfo[TP_UMS_MAX_CONFNUM];

};


#endif // _h_mpdata_h__