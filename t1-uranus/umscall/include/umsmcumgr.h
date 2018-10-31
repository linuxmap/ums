#ifndef _umsmcumgr_h_
#define _umsmcumgr_h_

#include "umsconfinst.h"

#define UMS_MAX_MCU_SIZE 5
#define UMS_MAX_MT_SIZE 192

// 回传通道参数
typedef struct tagTMcuSypChan
{
	BOOL32 m_bUsed;

	TCapNode* m_ptNode;	// mcu下级会场的node节点

	u32	m_dwVidBW;		// 该Spy回传视频占用带宽
	u32 m_dwAudBW;		// 该Spy回传音频占用带宽
/*	u8 m_byVSpyDstNum;	// 记录回传源之目的数目(视频)
	u8 m_byASpyDstNum;  // 记录回传源之目的数目(音频)
	u8 m_byUseState;	// 记录是否预占用 是-1 否-0
	u8 m_byPreAddMode;	// 记录预占用模式
	s8 m_byPreAddDstNum;//记录预占用增加目的数

	TMt		       m_tSpy;		     // 回传源(Mt)
	TSimCapSet     m_tSimCapset;     // 对应回传实体的能力描述 ( 该回传源 所回传到的 回传目的端的 能力 )
	TTransportAddr m_tSpyAddr;       // 对应回传实体的回传通道地址信息
	TTransportAddr m_tVideoRtcpAddr; // [liu lijiu][20100823]记录下级接收RTCP的地址
	TTransportAddr m_tAudioRtcpAddr; // [liu lijiu][20100823]记录下级会议接收RTCP的地址
	u8		       m_bySpyMode;	     // AUDIO,VIDEO,BOTH
	u8             m_byReserved1;    // 预留字段
	u32            m_dwReserved2;    // 预留字段

*/
	tagTMcuSypChan()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTMcuSypChan));\
		m_ptNode = NULL;
	}
}TMcuSypChan;

// 下级mcu信息
typedef struct tagTMcuInfo
{
	BOOL32 m_bUsed;

	TCapNode* m_ptMcuNode;

	// mcu回传能力
	BOOL32	m_bSupMultSpy;
	u32		m_dwMaxSpyBW;					//该mcu所支持的最大回传带宽
	u32		m_dwRemainSpyBW;					//该mcu剩余回传带宽

	//u16		m_wNum;
	TMcuSypChan m_atMcuSpyChan[UMS_MAX_MT_SIZE];			// 回传通道

	tagTMcuInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_bUsed				= FALSE;
		m_ptMcuNode			= NULL;
		m_bSupMultSpy		= 0;
		m_dwMaxSpyBW		= 0;
		m_dwRemainSpyBW		= 0;
		for(u16 wIndex = 0; wIndex < UMS_MAX_MT_SIZE; ++wIndex)
		{
			m_atMcuSpyChan[wIndex].Clear();
		}
	}
}TMcuInfo;


class CUmsMcuMgr
{

public:	

	CUmsMcuMgr(CUmsConfInst* pcInst):m_pcConf(pcInst) {}

    ~CUmsMcuMgr(){}

	void Enter() {Clear();}	
 	void Exit(){}
    void OnStopConf();

	BOOL32 HandlerFromCns(CTpMsg *const ptMsg);

	BOOL32 McuCaseCadeConnect(TCapNode* ptNode);
	BOOL32 McuCaseCadeSpyBWNty(TCapNode* ptNode, u32 dwSpyBW);




	void Show();

	BOOL32 AssignMcuSpyChan(u16 wMcuLowEpId);

protected:

	void Clear();
private:


private:
	TMcuInfo m_atMcuInfo[UMS_MAX_MCU_SIZE];
    CUmsConfInst*   m_pcConf;

};



#endif // _umsmcumgr_h_