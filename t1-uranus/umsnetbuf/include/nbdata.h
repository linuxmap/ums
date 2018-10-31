#ifndef _h_nbdata_h__
#define _h_nbdata_h__


#include "umsinnerstruct.h"
#include "tplistbuf.h"
#include "tpsys.h"
#include "umsinnertype.h"

#define HandleNetbuf	void*
typedef struct tagTUmsNetBufPara : public TUmsNetBuf
{
	HandleNetbuf m_Handle;
	
	tagTUmsNetBufPara()
	{
		memset(this, 0, sizeof(tagTUmsNetBufPara));
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsNetBufPara));
	}
}TUmsNetBufPara;


#define CNbList CTpListBuff<TUmsNetBufPara>
#define CNbListPtr CTpListBuff<TUmsNetBufPara>::VectorDataPtr

class CConfNb
{
public:
    CConfNb()	{ Clear(); }
    ~CConfNb()	{ }
	
	void Insert(CNbListPtr ptInsertNode)
	{
		m_dwListNum++;
		if (NULL == m_pHead)
		{
			m_pHead = ptInsertNode;
			ptInsertNode->m_ptNext = NULL;
			return;
		}
		
		ptInsertNode->m_ptNext = m_pHead;
		m_pHead = ptInsertNode;
	}

	CNbListPtr DelNode(TUmsNetBuf& tNb)
	{
		if (NULL == m_pHead)
		{			
			return NULL;
		}

		CNbListPtr Itor = NULL;
		if (m_pHead->m_tData.m_tRcvRtpAddr == tNb.m_tRcvRtpAddr)
		{
			Itor = m_pHead;
			m_pHead = m_pHead->m_ptNext;

			m_dwListNum--;
			Itor->m_ptNext = NULL;
			return Itor;
		}
		
		CNbListPtr ItorPre = m_pHead;
		Itor = m_pHead->m_ptNext;
		while (Itor != NULL)
		{
			if (Itor->m_tData.m_tRcvRtpAddr == tNb.m_tRcvRtpAddr)
			{
				ItorPre->m_ptNext = Itor->m_ptNext;

				m_dwListNum--;
				Itor->m_ptNext = NULL;
				return Itor;
			}
			
			ItorPre = Itor;
			Itor = Itor->m_ptNext;
		}
		return NULL;
	}
	
	u32	GetElementNum()			{ return m_dwListNum; }
	CNbListPtr GetHead()	{	return m_pHead; }
	void SetHeadNext()	{ m_pHead = m_pHead->m_ptNext; }
	
	void Clear()
	{
		m_pHead = NULL;
		m_dwListNum = 0;
	}

	
private:
	CConfNb& operator = (const CConfNb& tRsData);
	CConfNb(const CConfNb&);
private:    
    CNbListPtr		m_pHead;
	u32				m_dwListNum;
};


class CNbData
{
public:
    CNbData();
    virtual ~CNbData();
	
public:
    BOOL32 Init(u32 dwNbNum);
	CNbListPtr AddNbData(u16 wConfID, TUmsNetBuf& tNb);
	BOOL32 DelNbData(u16 wConfID, TUmsNetBuf& tNb, HandleNetbuf& tHandle);
	void DelAllNbData();
	void Show();
	
private:
    CNbList m_tNbList;
	CConfNb m_atNbData[TP_UMS_MAX_CONFNUM+1];
	
};



#endif // _h_nbdata_h__
