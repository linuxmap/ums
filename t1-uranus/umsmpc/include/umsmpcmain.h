#ifndef _h_umsmpcmain_h__
#define _h_umsmpcmain_h__

//结点信息
typedef struct tagTNodeInfo
{
	u16		m_wEpID;
	u16		m_wChanNum;
	u16		m_wIndex;
	
	tagTNodeInfo()
	{
		this->Clear();
	}
	
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wChanNum = 0;
		m_wIndex = TP_INVALID_INDEX;
	}
}TNodeInfo;

#endif // _h_umsmpcmain_h__



