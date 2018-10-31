#ifndef _umsmcumgr_h_
#define _umsmcumgr_h_

#include "umsconfinst.h"

#define UMS_MAX_MCU_SIZE 5
#define UMS_MAX_MT_SIZE 192

// �ش�ͨ������
typedef struct tagTMcuSypChan
{
	BOOL32 m_bUsed;

	TCapNode* m_ptNode;	// mcu�¼��᳡��node�ڵ�

	u32	m_dwVidBW;		// ��Spy�ش���Ƶռ�ô���
	u32 m_dwAudBW;		// ��Spy�ش���Ƶռ�ô���
/*	u8 m_byVSpyDstNum;	// ��¼�ش�Դ֮Ŀ����Ŀ(��Ƶ)
	u8 m_byASpyDstNum;  // ��¼�ش�Դ֮Ŀ����Ŀ(��Ƶ)
	u8 m_byUseState;	// ��¼�Ƿ�Ԥռ�� ��-1 ��-0
	u8 m_byPreAddMode;	// ��¼Ԥռ��ģʽ
	s8 m_byPreAddDstNum;//��¼Ԥռ������Ŀ����

	TMt		       m_tSpy;		     // �ش�Դ(Mt)
	TSimCapSet     m_tSimCapset;     // ��Ӧ�ش�ʵ����������� ( �ûش�Դ ���ش����� �ش�Ŀ�Ķ˵� ���� )
	TTransportAddr m_tSpyAddr;       // ��Ӧ�ش�ʵ��Ļش�ͨ����ַ��Ϣ
	TTransportAddr m_tVideoRtcpAddr; // [liu lijiu][20100823]��¼�¼�����RTCP�ĵ�ַ
	TTransportAddr m_tAudioRtcpAddr; // [liu lijiu][20100823]��¼�¼��������RTCP�ĵ�ַ
	u8		       m_bySpyMode;	     // AUDIO,VIDEO,BOTH
	u8             m_byReserved1;    // Ԥ���ֶ�
	u32            m_dwReserved2;    // Ԥ���ֶ�

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

// �¼�mcu��Ϣ
typedef struct tagTMcuInfo
{
	BOOL32 m_bUsed;

	TCapNode* m_ptMcuNode;

	// mcu�ش�����
	BOOL32	m_bSupMultSpy;
	u32		m_dwMaxSpyBW;					//��mcu��֧�ֵ����ش�����
	u32		m_dwRemainSpyBW;					//��mcuʣ��ش�����

	//u16		m_wNum;
	TMcuSypChan m_atMcuSpyChan[UMS_MAX_MT_SIZE];			// �ش�ͨ��

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